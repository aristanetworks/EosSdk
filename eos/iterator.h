// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ITERATOR_H
#define EOS_ITERATOR_H

#include <iterator>
#include <eos/base.h>

namespace eos {

template <typename T, typename Impl>
class EOS_SDK_PUBLIC iter_base : public std::iterator<std::input_iterator_tag, T> {
 public:
   iter_base(iter_base const &);
   ~iter_base();
   iter_base & operator++();
   iter_base operator++(int);
   bool operator==(iter_base const & rhs) const;
   bool operator!=(iter_base const & rhs) const;
   operator bool() const;
   T operator*();
   T * operator->();

 protected:
   Impl * const impl;
   explicit iter_base(Impl * const) EOS_SDK_PRIVATE;
   iter_base() EOS_SDK_PRIVATE;
};

}

#include <eos/inline/iterator.h>

#endif // EOS_ITERATOR_H
