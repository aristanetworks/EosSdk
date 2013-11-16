// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_ENUMCAST_H
#define EOSSDK_ENUMCAST_H

template<typename R, typename T,
         bool B1 = std::is_enum<R>::value,
         bool B2 = std::is_enum<T>::value>
struct EnumCast {
   static_assert(B1, "enum_cast must convert to an enum type");
   static_assert(B2, "enum_cast must convert to an enum type");
   static const R cast(T value);
};

template<typename R, typename T>
struct EnumCast<R, T, true, true> {
   static const R cast(T value) {
      return static_cast<R>(static_cast<int>(value));
   }
};

template<typename R, typename T>
R enum_cast(T value) {
   return EnumCast<R, T>::cast(value);
}

#endif // EOSSDK_ENUMCAST_H
