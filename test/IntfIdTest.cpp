// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <eos/intf.h>

int main() {
   printf( "Starting IntfIdTest\n" );

   // Create an intf_id_t
   const char *intf1_str = "Ethernet1";
   eos::intf_id_t intf1(intf1_str);
   const char *intf2_str = "Ethernet2";;
   eos::intf_id_t intf2(intf2_str);

   printf( "Checking to_string\n" );
   char buf[eos::INTF_NAME_MAX];
   intf1.to_string(buf, sizeof(buf));
   assert( strcmp(intf1_str, buf) == 0 );

   printf( "Checking equality\n" );
   assert(intf1 == intf1);
   assert(intf1 != intf2);
   eos::intf_id_t intf1_dup(intf1_str);
   assert(intf1 == intf1_dup);

   printf( "Checking copy constructor\n" );
   eos::intf_id_t intf1_copy = intf1;
   assert(intf1 == intf1_copy);
   
   printf( "PASS\n" );
}
