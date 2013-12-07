// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <eos/ip.h>

// address constants
static char const ADDR1234[] = "1.2.3.4";
static unsigned int const ADDR1234_DEC = 16909060;
static char const ADDR6_LOCAL[] = "::1";
static char const ADDR4_LOCAL[] = "127.0.0.1";

// test cases return true if they succeeded, else false

bool test_parse_ip_addr_v4() {
   eos::ip_addr_t addr;
   // Parse '1.2.3.4' into an IPv4 address
   eos::parse_ip_addr(ADDR1234, &addr);
   // Convert the address value back to a string
   if (ADDR1234 == addr.to_string()) {
      printf("OK: test_parse_ip_addr_v4\n");
      return true;
   }
   printf("FAIL: test_parse_ip_addr_v4\n");
   return false;
}

bool test_parse_ip_addr_v6() {
   eos::ip_addr_t addr;
   // Parse '::1' into an IPV6 address
   eos::parse_ip_addr(ADDR6_LOCAL, &addr);
   // Convert the address value back to a string
   if (ADDR6_LOCAL == addr.to_string()) {
      printf("OK: test_parse_ip_addr_v6\n");
      return true;
   }
   printf("FAIL: test_parse_ip_addr_v6\n");
   return false;
}

bool test_valid_addr_v4() {
   eos::ip_addr_t addr;
   // Check that valid IPv4 addresses parse and never crash
   if ((eos::parse_ip_addr("1.1.1.1", &addr)) &&
       (eos::parse_ip_addr("0.0.0.0", &addr)) &&
       (eos::parse_ip_addr("255.255.255.255", &addr)) &&
       (eos::parse_ip_addr("192.0.2.1", &addr)) &&
       (eos::parse_ip_addr("203.32.8.1", &addr)) &&
       (eos::parse_ip_addr("255.0.0.0", &addr))) {
      printf("OK: test_valid_addr_v4\n");
      return true;
   }
   printf("FAIL: test_valid_addr_v4\n");
   return false;
}

bool test_invalid_addr_v4() {
   eos::ip_addr_t addr;
   // Check that invalid IPv4 addresses do not parse or crash
   if ((!eos::parse_ip_addr("-1", &addr)) &&
       (!eos::parse_ip_addr("a.b.c.d", &addr)) &&
       (!eos::parse_ip_addr("127.0.0.256", &addr)) &&
       (!eos::parse_ip_addr("257.257.257.257", &addr)) &&
       (!eos::parse_ip_addr("2", &addr))) {
      printf("OK: test_invalid_addr_v4\n");
      return true;
   }
   printf("FAIL: test_invalid_addr_v4\n");
   return false;
}

bool test_valid_addr_v6() {
   eos::ip_addr_t addr;
   // Check that valid IPv6 addresses parse and never crash
   if ((eos::parse_ip_addr("::1", &addr)) &&
       (eos::parse_ip_addr("::2001", &addr)) &&
       (eos::parse_ip_addr("2001:0db8:85a3:0042:1000:8a2e:0370:7334", &addr))) {
      printf("OK: test_valid_addr_v6\n");
      return true;
   }
   printf("FAIL: test_valid_addr_v6\n");
   return false;
}

bool test_invalid_addr_v6() {
   eos::ip_addr_t addr;
   // Check that invalid IPv6 addresses do not parse or crash
   if ((!eos::parse_ip_addr("hhhh:0db8:85a3:0042:1001:882e:0370:1337", &addr)) &&
       (!eos::parse_ip_addr("::::", &addr))) {
      printf("OK: test_invalid_addr_v6\n");
      return true;
   }
   printf("FAIL: test_invalid_addr_v6\n");
   return false;
}

bool test_ip_addr_string_constructor_v4() {
   eos::ip_addr_t addr = eos::ip_addr_t("1.2.3.4");  // decimal 16909060
   // Convert the address value back to a string
   // Compare the string buffer is the same as the string input, and that
   // the string input was converted to the correct IPv4 address value
   if (ADDR1234 == addr.to_string() &&
       addr.addr_v4() == ADDR1234_DEC) {
      printf("OK: test_ip_addr_string_constructor_v4\n");
      return true;
   }
   printf("FAIL: test_ip_addr_string_constructor_v4\n");
   return false;
}

bool test_ip_addr_string_constructor_v6() {
   eos::ip_addr_t addr = eos::ip_addr_t(ADDR6_LOCAL);
   // Convert the address value back to a string
   if (ADDR6_LOCAL == addr.to_string()) {
      printf("OK: test_ip_addr_string_constructor_v6\n");
      return true;
   }
   printf("FAIL: test_ip_addr_string_constructor_v6\n");
   return false;
}

bool test_valid_ip_prefix_v4() {
   eos::ip_prefix_t prefix;
   if ((eos::parse_ip_prefix("127.0.0.0/8", &prefix)) &&
       (eos::parse_ip_prefix("203.147.0.0/16", &prefix)) &&
       (eos::parse_ip_prefix("192.0.2.0/24", &prefix)) &&
       (eos::parse_ip_prefix("192.0.2.1/32", &prefix))) {
      if (prefix.af() == eos::AF_IPV4) {
         printf("OK: test_valid_ip_prefix_v4\n");
         return true;
      }
   }
   printf("FAIL: test_valid_ip_prefix_v4\n");
   return false;
}

bool test_invalid_ip_prefix_v4() {
   eos::ip_prefix_t prefix;
   eos::parse_ip_prefix("127.0.0.0/33", &prefix);
   if ((!eos::parse_ip_prefix("127.0.0.0/33", &prefix)) &&
       (!eos::parse_ip_prefix("256.0.0.0/8", &prefix)) &&
       (!eos::parse_ip_prefix("192.0.2.0/1", &prefix))) {  // not a strict prefix
      // test that at least the last one had AF_NULL on the result
      if (prefix.af() == eos::AF_NULL) {
         printf("OK: test_invalid_ip_prefix_v4\n");
         return true;
      }
   }
   printf("FAIL: test_invalid_ip_prefix_v4\n");
   return false;
}

bool test_ip_addr_t_compare_construction_methods() {
   uint8_t a1[4] = { 1, 0, 0, 127 };  // network word order
   auto ipv4_addr1 = eos::ip_addr_t(eos::AF_IPV4, a1);
   auto ipv4_addr2 = eos::ip_addr_t("127.0.0.1");

   uint8_t a2[16] = { 255, 255, 0, 0,  // ffff::1
                      0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 1 };
   auto ipv6_addr1 = eos::ip_addr_t(eos::AF_IPV6, a2);
   auto ipv6_addr2 = eos::ip_addr_t("ffff::1");

   if (ipv4_addr1 == ipv4_addr2 &&
       ipv6_addr1 == ipv6_addr2) {
      printf("OK: test_ip_addr_t_compare_construction_methods\n");
      return true;
   } else {
      printf("FAIL: test_ip_addr_t_compare_construction_methods\n");
   }
   return false;
}

bool test_ip_prefix_to_string_v4() {
   eos::ip_addr_t addr = eos::ip_addr_t("192.0.2.0");
   eos::ip_prefix_t prefix = eos::ip_prefix_t(addr, 24);
   // Convert the prefix value back to a string and check it's what we expect
   return prefix.to_string() == "192.0.2.0/24";
}


int main() {
   printf("Starting IpAddrTest\n");
   if (test_parse_ip_addr_v4() &&
       test_parse_ip_addr_v6() &&
       test_invalid_addr_v4() &&
       test_valid_addr_v4() &&
       test_invalid_addr_v6() &&
       test_valid_addr_v6() &&
       test_valid_ip_prefix_v4() &&
       test_invalid_ip_prefix_v4() &&
       test_ip_prefix_to_string_v4() &&
       test_ip_addr_string_constructor_v4() &&
       test_ip_addr_string_constructor_v6() &&
       test_ip_addr_t_compare_construction_methods()) {
      printf("PASS\n");
   } else {
      printf("FAIL\n");
      // signal to test runner that we failed
      exit(1);
   }
}
