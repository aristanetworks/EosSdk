// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <eos/intf.h>
#include <eos/panic.h>

void handle_panic(char const * msg) {
   throw 1;
}

int main() {
   printf( "Starting IntfIdTest\n" );

   eos::panic_handler_is( handle_panic );

   // Create an intf_id_t
   const char *intf1_str = "Ethernet1";
   eos::intf_id_t intf1(intf1_str);
   const char *intf2_str = "Ethernet2/2";
   eos::intf_id_t intf2(intf2_str);

   printf( "Checking to_string\n" );
   char buf[eos::INTF_NAME_MAX];
   intf1.to_string(buf, sizeof(buf));
   assert(strcmp(intf1_str, buf) == 0);

   printf( "Checking equality\n" );
   assert(intf1 == intf1);
   assert(intf1 != intf2);
   eos::intf_id_t intf1_dup(intf1_str);
   assert(intf1 == intf1_dup);

   printf( "Checking copy constructor\n" );
   eos::intf_id_t intf1_copy = intf1;
   assert(intf1 == intf1_copy);
   
   printf( "Checking default constructor\n" );
   eos::intf_id_t default_intf;
   default_intf.to_string(buf, sizeof(buf));
   assert(strcmp("", buf) == 0);

   printf( "Checking boolean evaluation\n" );
   assert( !!intf1 );
   assert( !default_intf );

   printf( "Checking Null0 intf\n" );
   eos::intf_id_t null0_intf( "Null0" );
   assert(null0_intf.is_null0());
   assert(!intf1.is_null0());

   printf( "Checking invalid intf\n" );
   try {
      eos::intf_id_t bad_intf("InvalidIntf1");
      assert( false );
   } catch(int err) {
      assert(err==1);
   }
   // Currently unable to find an invalid IntfId
   // try {
   //    eos::intf_id_t bad_intf(0xabcdef12);
   //    assert( false );
   // } catch(int err) {
   //    assert(err==1);
   // }

   printf( "PASS\n" );
}
