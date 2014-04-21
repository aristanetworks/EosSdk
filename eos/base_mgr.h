// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BASE_MGR_H
#define EOS_BASE_MGR_H

#include <eos/base.h>

#include <map>
#include <set>

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
   virtual ~base_mgr() {
      for (auto it = watchAllHandlers_.begin(); it != watchAllHandlers_.end();
            ++it) {
         (*it)->unregister_mgr();
      }
      for (auto set = keySpecificHandlers_.begin();
            set != keySpecificHandlers_.end(); ++set) {
         for (auto it = set->second.begin(); it != set->second.end(); ++it) {
            (*it)->unregister_mgr();
         }
      }
   }

   void add_handler(T *handler) {
      // no specific ordering
      watchAllHandlers_.insert(handler);

      // The handler is now registered in the "watchAll" set. The key-specific
      // registration needs to be cleaned to avoid calling the handler twice.
      for (auto it = keySpecificHandlers_.begin(); it != keySpecificHandlers_.end();
            ++it) {
         it->second.erase(handler);
         if (it->second.empty()) {
            keySpecificHandlers_.erase(it);
         }
      }
   }

   // We don't allow a handler to be registered both as generic and key-specific.
   // We always favor generic over key-specific.
   void add_handler(Key key, T *handler) {
      if (!watchAllHandlers_.count(handler)) {
         keySpecificHandlers_[key].insert(handler);
      }
   }

   void remove_handler(T *handler) {
      watchAllHandlers_.erase(handler);
   }

   void remove_handler(Key key, T *handler) {
      auto entry = keySpecificHandlers_.find(key);
      if (entry != keySpecificHandlers_.end()) {
         entry->second.erase(handler);
         if (entry->second.empty()) {
            keySpecificHandlers_.erase(entry);
         }
      }
   }

   // Run the function f for each registered handler, with no specific ordering
   template <typename Func> void handler_foreach(Func f) {
      for (auto i = watchAllHandlers_.begin(); i != watchAllHandlers_.end(); ++i) {
         f(*i);
      }
   }

   // Run the function f for each registered handler on the given key, with no
   // specific ordering
   template <typename Func> void handler_foreach(Key key, Func f) {
      for (auto i = watchAllHandlers_.begin(); i != watchAllHandlers_.end(); ++i) {
         f(*i);
      }

      // Since we don't allow a handler to be both key-specific and generic, we
      // don't have to check if F was already executed for a given handler.
      auto entry = keySpecificHandlers_.find(key);
      if (entry != keySpecificHandlers_.end()) {
         for (auto i = entry->second.begin(); i != entry->second.end(); ++i) {
            if (!watchAllHandlers_.count(*i)) {
               f(*i);
            }
         }
      }
   }

 private:
   template <typename U, typename V> friend class base_handler;

   std::set<T *> watchAllHandlers_;
   std::map<Key, std::set<T *> > keySpecificHandlers_;
};

}

#endif // EOS_BASE_MGR_H
