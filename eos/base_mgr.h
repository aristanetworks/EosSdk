// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BASE_MGR_H
#define EOS_BASE_MGR_H

#include <eos/base.h>

#include <map>

namespace eos {

/*
 * This class is not part of the public API of the SDK. You should NOT use it
 * directly. It is subclassed by the different managers that have handlers.
 *
 * Manages handler. The handler can register themselves to receive notifications
 * following two different modes:
 * - "watch all": the handler will receive every notifications.
 * - "key specific": the handler will only receive notifications for the keys it
 *   directly registered to.
 *
 * It is not possible for a handler to be in both modes. The "watch all" mode is
 * always favored over "key specific". Thus you have to manually deactivate the
 * "watch all" mode to enter the "key specific" mode.
 */
template <typename T, typename Key=int> // `int' is an arbitrary default for classes
class EOS_SDK_PRIVATE base_mgr {        // that don't use key-specific notifications
 protected:
   base_mgr() : inForeach_(false) {
   }

   virtual ~base_mgr() {
      for (auto it = watchAllHandlers_.begin(); it != watchAllHandlers_.end();
            ++it) {
         if (it->second) {
            // mgr may want to do so specific work in the remove_handler function.
            // We need to call it there so that handlers that did not unsubscribe
            // are still correctly cleaned.
            remove_handler(it->first);
            it->first->unregister_mgr();
         }
      }
      for (auto map = keySpecificHandlers_.begin();
            map != keySpecificHandlers_.end(); ++map) {
         for (auto it = map->second.begin(); it != map->second.end(); ++it) {
            if (it->second) {
               // mgr may want to do so specific work in the remove_handler
               // function. We need to call it there so that handlers that did not
               // unsubscribe are still correctly cleaned.
               remove_handler(map->first, it->first);
               it->first->unregister_mgr();
            }
         }
      }
   }

   virtual void add_handler(T *handler) {
      // no specific ordering
      watchAllHandlers_.insert(std::make_pair(handler, true));

      // The handler is now registered in the "watchAll" set. The key-specific
      // registration needs to be cleaned to avoid calling the handler twice.
      for (auto it = keySpecificHandlers_.begin(); it != keySpecificHandlers_.end();
            ++it) {
         auto element = it->second.find(handler);
         if (element != it->second.end()) {
            element->second = false;
         }
      }
   }

   // We don't allow a handler to be registered both as generic and key-specific.
   // We always favor generic over key-specific.
   virtual void add_handler(Key const & key, T *handler) {
      if (!watchAllHandlers_.count(handler)) {
         keySpecificHandlers_[key].insert(std::make_pair(handler, true));
      }
   }

   virtual void remove_handler(T *handler) {
      auto element = watchAllHandlers_.find(handler);
      if (element != watchAllHandlers_.end()) {
         element->second = false;
      }
   }

   virtual void remove_handler(Key const & key, T *handler) {
      auto entry = keySpecificHandlers_.find(key);
      if (entry != keySpecificHandlers_.end()) {
         auto element = entry->second.find(handler);
         if (element != entry->second.end()) {
            element->second = false;
         }
      }
   }

   // Run the function f for each registered handler, with no specific ordering
   template <typename Func> void handler_foreach(Func f) {
      bool wasInForeach = inForeach_;
      inForeach_ = true;

      auto currentIt = watchAllHandlers_.begin();
      for (auto it = currentIt; it != watchAllHandlers_.end();) {
         currentIt = it++;
         if (currentIt->second) {
            f(currentIt->first);
         } else if (!wasInForeach) {
            // If we are not in a nested foreach, we can clean up the lazy work left
            // to us
            watchAllHandlers_.erase(currentIt);
         }
      }

      inForeach_ = wasInForeach;
   }

   // Run the function f for each registered handler on the given key, with no
   // specific ordering
   template <typename Func> void handler_foreach(Key key, Func f) {
      bool wasInForeach = inForeach_;
      inForeach_ = true;

      auto currentIt = watchAllHandlers_.begin();
      for (auto it = currentIt; it != watchAllHandlers_.end();) {
         currentIt = it++;
         if (currentIt->second) {
            f(currentIt->first);
         } else if (!wasInForeach) {
            // If we are not in a nested foreach, we can clean up the lazy work left
            // to us
            watchAllHandlers_.erase(currentIt);
         }
      }

      // Since we don't allow a handler to be both key-specific and generic, we
      // don't have to check if F was already executed for a given handler.
      auto entry = keySpecificHandlers_.find(key);
      if (entry != keySpecificHandlers_.end()) {
         auto currentIt= entry->second.begin();
         for (auto it = currentIt; it != entry->second.end();) {
            currentIt = it++;
            if (currentIt->second) {
               f(currentIt->first);
            } else if (!wasInForeach) {
               // If we are not in a nested foreach, we can clean up the lazy work
               // left to us
               entry->second.erase(currentIt);
            }
         }
         if (entry->second.empty()) {
            keySpecificHandlers_.erase(entry);
         }
      }

      inForeach_ = wasInForeach;
   }

 private:
   template <typename U, typename V> friend class base_handler;

   bool inForeach_;
   std::map<T *, bool> watchAllHandlers_;
   std::map<Key, std::map<T *, bool> > keySpecificHandlers_;
};

}

#endif // EOS_BASE_MGR_H
