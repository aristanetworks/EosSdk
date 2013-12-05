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
   assert(intf1_str == intf1.to_string());

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
   assert("" == default_intf.to_string());

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

   printf( "Checking intf type conversion\n" );
   assert(eos::intf_id_t("").intf_type() == eos::INTF_TYPE_NULL);
   assert(eos::intf_id_t("Ethernet1").intf_type() == eos::INTF_TYPE_ETH);
   assert(eos::intf_id_t("Ethernet5/10/1").intf_type() == eos::INTF_TYPE_ETH);
   assert(eos::intf_id_t("Vlan54").intf_type() == eos::INTF_TYPE_VLAN);
   assert(eos::intf_id_t("Management1/2").intf_type() == eos::INTF_TYPE_MANAGEMENT);
   assert(eos::intf_id_t("Loopback3").intf_type() == eos::INTF_TYPE_LOOPBACK);
   assert(eos::intf_id_t("Port-Channel3").intf_type() == eos::INTF_TYPE_LAG);
   assert(eos::intf_id_t("Null0").intf_type() == eos::INTF_TYPE_NULL0);
   assert(eos::intf_id_t("Vxlan2").intf_type() == eos::INTF_TYPE_OTHER);

   printf( "PASS\n" );
}
