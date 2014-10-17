// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <unordered_map>

#include <eos/directflow.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

/**
 * The DirectFlowReprogrammer library helps reprogram a DirectFlow
 * entry with no downtime. The process uses a temporary flow entry
 * with a higher priority and different name, and once that is
 * programmed, programs the correctly named entry and deletes the
 * temporary one. The steps require leeway of at least one priorty
 * point in order to program the temporary entry, and results in
 * reset counters for that entry (along with missing counter data
 * while the temporary entry is accepting traffic).
 * 
 *  To use, create and store an instance of the library. 
 *     myDfr = DirectFlowReprogrammer(sdk);
 *  When you want to update an entry, call
 *     myDfr.updateFlow(myFlow);
 *  within the context of the event loop.
 * 
 * The process is as follows:
 * 0) Assume an existing myFlow(match="src ip 1.1.1.1", action="output intf et1",
 *                              priority=50),
 *    and we want to change its action to, say, send out of et3.
 *    [ Status: all 1.1.1.1 traffic goes to et1 ]
 * 1) Add myFlow-tmp-entry(match="src ip 1.1.1.1", action="output intf et3",
 *                         priority=51)
 *    [ Now myFlow and myFlow-tmp-entry exist. The latter's priority is higher, 
 *      so now all traffic goes to et3 ]
 * 2) Delete myFlow
 *    [ now myFlow-tmp-entry is the only existing flow ]
 * 3) Add myFlow(match="src ip 1.1.1.1", action="output intf et3", priority=50)
 *    [ myFlow is back, with the right data! myFlow-tmp-entry is still the entry
 *      being hit]
 * 4) Delete myFlow-tmp-entry
 *    [ traffic now hits myFlow ]
 *
 * If any errors are hit, the library falls back to the naive way of
 * reprogramming the entry.
 */

static const std::string TMP_ENTRY_SUFFIX = "-tmp-entry";

class DirectFlowReprogrammer : public eos::flow_handler {
 public:
   std::unordered_map<std::string, eos::flow_entry_t> requests;
   eos::directflow_mgr * mgr_;
   eos::tracer tracer;
   explicit DirectFlowReprogrammer(eos::sdk & sdk)
         : eos::flow_handler(sdk.get_directflow_mgr()),
           requests(),
           mgr_(sdk.get_directflow_mgr()),
           tracer("EosSdkDirectFlowReprogrammer") {
      watch_all_flows(true);
      tracer.trace0("Constructed");
   }

   void updateFlow(eos::flow_entry_t const & entry) {
      if(mgr_->exists(entry.name())) {
         if(mgr_->flow_entry(entry.name()) == entry) {
            tracer.trace0("Flow not changed %s", entry.name().c_str());
            return;
         }
         tracer.trace0("Updating flow %s", entry.name().c_str());
         // Let's update this flow!
         requests[entry.name()] = entry;
         eos::flow_entry_t entryCopy(entry.name() + TMP_ENTRY_SUFFIX,
                                     entry.match(),
                                     entry.action(),
                                     entry.priority() + 1);
         mgr_->flow_entry_set(entryCopy);
      } else {
         // This is a new flow, so all we have to do is set it.
         tracer.trace0("Creating flow %s", entry.name().c_str());
         mgr_->flow_entry_set(entry);
      }
   }

   void on_flow_status(std::string const & name, eos::flow_status_t status) {
      tracer.trace0("Flow %s changed", name.c_str());
      bool tmpEntry = false;
      std::string entryName = name;
      size_t suffixSize = TMP_ENTRY_SUFFIX.size();
      if(name.size() > suffixSize &&
         name.substr(name.size() - suffixSize, suffixSize) == TMP_ENTRY_SUFFIX) {
         // Entry is one of our tmp entries!
         tmpEntry = true;
         entryName = name.substr(0, name.size() - suffixSize);
         tracer.trace0("  [Entry %s]", entryName.c_str());
      }
      if(requests.count(entryName) == 0) {
         // We're not tracking this flow.
         tracer.trace0("  %s is not tracked. Ignoring.", entryName.c_str());
         return;
      }
      if(status == eos::FLOW_CREATED) {
         if(tmpEntry) {
            // Okay, our temporary entry is now programmed. Let's
            // program the real entry over the old entry.
            tracer.trace0("  %s temp flow programmed to hardware",
                          entryName.c_str());
            mgr_->flow_entry_set(requests[entryName]);
         } else {
            // We got the originally requested entry programmed!
            // Delete the temporary entry and stop tracking this
            // request.
            tracer.trace0("  %s programmed to hardware", entryName.c_str());
            mgr_->flow_entry_del(entryName + TMP_ENTRY_SUFFIX);
            requests.erase(requests.find(entryName));
         }
      } else if(status == eos::FLOW_DELETED) {
         if(!tmpEntry) {
            // Someone deleted the flow after we were requested to
            // change it. Delete the tmp flow (if it exists), and stop
            // tracking this flow.
            tracer.trace0("  %s flow deleted", entryName.c_str());
            mgr_->flow_entry_del(entryName + TMP_ENTRY_SUFFIX);
            requests.erase(requests.find(entryName));            
         }
      } else if(status == eos::FLOW_REJECTED) {
         tracer.trace0("  Flow rejected");
         if(tmpEntry) {
            // Could not create the temporary entry, likely do to
            // HW_TABLE_FULL. In any case, let's fall back to the old
            // way of doing things. Remove this and the original flow,
            // and add requested flow.
            mgr_->flow_entry_del(name);
            mgr_->flow_entry_del(entryName);
            mgr_->flow_entry_set(requests[entryName]);
            requests.erase(requests.find(entryName));            
         }
      }
   }
};

