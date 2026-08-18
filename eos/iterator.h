// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ITERATOR_H
#define EOS_ITERATOR_H

#include <string>
#include <list>
#include <iterator>
#include <eos/base.h>

// c++17 deprecated classes inheriting from std::iterator, this is now being
// enforced by gcc14 toolchain
// But since this is a public API, we are concern that might affect the ABI
// so for now we request the compiler to ignore the warning
#if defined(__GNUC__) && __GNUC__ >= 14
#define ALLOW_DEPRECATED_STD_ITERATOR(...)                             \
   _Pragma("GCC diagnostic push")                                      \
       _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"") \
           __VA_ARGS__ _Pragma("GCC diagnostic pop")
#else
#define ALLOW_DEPRECATED_STD_ITERATOR(...) __VA_ARGS__
#endif

namespace eos {

ALLOW_DEPRECATED_STD_ITERATOR(template <typename T, typename Impl>
                              class EOS_SDK_PUBLIC iter_base
                              : public std::iterator<std::input_iterator_tag, T> {
                                public:
                                 iter_base(iter_base const&);
                                 ~iter_base();
                                 iter_base& operator=(iter_base const& other);
                                 iter_base& operator++();
                                 iter_base operator++(int);
                                 bool operator==(iter_base const& rhs) const;
                                 bool operator!=(iter_base const& rhs) const;
                                 operator bool() const;
                                 T operator*() const;
                                 T const* operator->() const;
                                 T* operator->();

                                protected:
                                 Impl* impl;
                                 explicit iter_base(Impl* const) EOS_SDK_PRIVATE;
                                 iter_base() EOS_SDK_PRIVATE;
                              };)

ALLOW_DEPRECATED_STD_ITERATOR(template <typename V> class mocked_iter
                              : public std::iterator<std::input_iterator_tag, V> {
                                private:
                                 std::list<V> li;
                                 typename std::list<V>::iterator it;
                                 int count = 0;  // it != li.end() does not work!
                                 int max;

                                public:
                                 mocked_iter(std::list<V> l) : li(l) {
                                    it = li.begin();
                                    max = li.size();
                                 }
                                 operator bool() const {
                                    return it != li.end() && count < max;
                                 }
                                 mocked_iter operator++() {
                                    auto i = *this;
                                    it++;
                                    count++;
                                    return i;
                                 }
                                 mocked_iter operator++(int dummy) {
                                    it++;
                                    count++;
                                    return *this;
                                 }
                                 V operator*() {
                                    return *it;
                                 }
                                 V const* operator->() const {
                                    return &(*it);
                                 }
                                 V* operator->() {
                                    return &(*it);
                                 }
                                 bool operator==(const mocked_iter& rhs) const {
                                    return *it == *rhs.it;
                                 }
                                 bool operator!=(const mocked_iter& rhs) const {
                                    return *it != *rhs.it;
                                 }
                              };)
}

#include <eos/inline/iterator.h>

#endif // EOS_ITERATOR_H
