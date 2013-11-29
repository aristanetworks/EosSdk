// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <eos/eth.h>

int main() {
   printf( "Starting EthAddrTest\n" );
   
   // Create an eth_addr_t
   const char *addr1_str = "00:11:22:33:44:55";
   eos::eth_addr_t addr1(addr1_str);
   const char *addr2_str = "ff:ff:ff:ff:ff:ff";
   eos::eth_addr_t addr2(addr2_str);

   printf( "Checking to_string\n" );
   char buf[18];
   addr1.to_string(buf, sizeof(buf));
   assert( strcmp(addr1_str, buf) == 0 );

   printf( "Checking equality\n" );
   assert(addr1 == addr1);
   assert(addr1 != addr2);
   eos::eth_addr_t addr1_dup(addr1_str);
   assert(addr1 == addr1_dup);

   printf( "Checking copy constructor\n" );
   eos::eth_addr_t addr1_copy = addr1;
   assert(addr1 == addr1_copy);
   
   printf( "PASS\n" );
}
