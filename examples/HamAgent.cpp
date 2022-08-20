// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/sdk.h>
#include <eos/tracing.h>
#include <eos/ham.h>
#include <eos/types/ham.h>
#include <assert.h>
#include <unistd.h>
#include <string>

class ham_agent : public eos::agent_handler {

 public:
   eos::tracer t;
   eos::ham_mgr *ham_mgr_;

   explicit ham_agent(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
         t("HamAgent"),
         ham_mgr_(sdk.get_ham_mgr()){
      t.trace0("Agent constructed");
   }

   void on_initialized(){
      t.enabled_is(eos::Level0, true);
      t.trace0("Initialized");
      get_agent_mgr()->status_set("Ready_for_testing", "True");
      t.trace0("Set the status to ready for testing");
   }

   void on_agent_option(std::string const & option_name,
                        std::string const & value ){
      // Create ham using createFromAddress funciton call
      // Create aham_address_t to pass in
      auto aham_address = eos::aham_address_t();
      // Initialize aham_address to be passed to HAM constructor
      // Initialize bus ID to 0 and address to 0x48 because those are
      // the corresponding values for the temperature sensor we will be
      // writing to/reading from
      aham_address.bus_is( 1 );
      aham_address.accelerator_is( 0 );
      aham_address.address_is( 0x48 );
      // Initialize pci_address to be passed to HAM constructor
      // Initialize all fields to 0 because we are testing on
      // dropbear duts, which have all fields for pci addr as 0
      auto pci_address = eos::pci_address_t();
      pci_address.domain_is( 0 );
      pci_address.bus_is( 0 );
      pci_address.device_is( 0 );
      pci_address.function_is( 0 );
      auto eossdk_ham_from_address = eos::eossdk_ham_t( aham_address, pci_address );
      if(option_name == "test_write_and_read_8"){
         // Hardcode address at 0x03, which represents the address of the
         // overtemperature sensor on a lm75 temperature sensor on a 7130,
         // to write to/read from in the test
         auto reg = eos::register_t() ;
         reg.reg_is(0x03);
         // Convert value to appropriate type to pass to write8
         uint8_t val = stoi(value);
         ham_mgr_->write8(eossdk_ham_from_address,reg, val, true);
         auto retVal = ham_mgr_->read8(eossdk_ham_from_address, reg);
         uint8_t valueRead = retVal.result();
         t.trace0("Value read was: %d", valueRead);
         assert(retVal.status() == eos::STATUS_OK);
         assert (valueRead == val);
         get_agent_mgr()->status_set("test_write_and_read_8",
                                      "Value successfully written and read.");
      }
      else if(option_name == "test_write_and_read_16"){
         // Hardcode address to write to/read from into test
         auto reg = eos::register_t() ;
         reg.reg_is(0x03);
         // Convert value to appropriate type to pass to write16
         uint16_t val = stoi(value);
         ham_mgr_->write16(eossdk_ham_from_address, reg, val, true);
         auto retVal = ham_mgr_->read16(eossdk_ham_from_address, reg);
         uint16_t valueRead = retVal.result();
         t.trace0( "Value read was: %d", valueRead );
         assert(valueRead == val);
         assert(retVal.status() == eos::STATUS_OK);
         get_agent_mgr()->status_set("test_write_and_read_16",
                                      "Value successfully written and read.");
      }
   }

};

int main(int argc, char ** argv){
   eos::sdk sdk;
   ham_agent agent(sdk);
   sdk.main_loop(argc, argv);
}
