// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_EAPI_H
#define EOS_EAPI_H

#include <eos/base.h>
#include <eos/types/eapi.h>

/**
 * @file
 * EOS eAPI interaction module.
 * This module allows interaction with the CLI via eAPI command requests.
 * This allows EOS SDK applications access to configuration and status of EOS state 
 * for which EOS SDK APIs do not yet exist.
 * Note that each method is a synchronous call, and opens a unix-domain socket.
 * Therefore, this is not intended to be a replacement for other EosSdk modules.
 *
 * For more information about eAPI, please visit
 * https://eos.arista.com/arista-eapi-101/
 *
 * The following snippet shows how to load an eAPI response into a json_t object from
 * the jansson library, although any json library to convert from json-formatted text
 * will do.
 * Based on the jansson library documentation:
 * https://jansson.readthedocs.io/en/2.10/tutorial.html
 * @code
 * eapi_response_t show_interfaces = eapiMgr->run_show_cmd("show interfaces");
 * json_t* root;
 * json_error_t error;
 * if (show_interfaces.success()) {
 *    root = json_loads(show_interfaces.responses()[0], 0, &error);
 * }
 * if (!root) {
 *    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
 * }
 * json_t* interfaces = json_object_get(root, "interfaces");
 * json_t* intf1 = json_object_get(interfaces, "Ethernet1");
 * json_t* desc1 = json_object_get(intf1, "description");
 *
 * printf("Ethernet1's description: " << json_string_value(desc1));
 * ...
 * @endcode
 */

namespace eos {
/**
 * eAPI manager.
 */
class EOS_SDK_PUBLIC eapi_mgr {
 public:
   virtual ~eapi_mgr();

   /// Executes a "show" CLI command in enable mode.
   virtual eapi_response_t run_show_cmd(std::string const &) const = 0;

   /// Executes one or many CLI commands in configuration mode.
   virtual eapi_response_t run_config_cmds(
         std::vector<std::string> const &) const = 0;

   /// like "run_show_cmd" but returns "text" formatted output (instead of json)
   virtual eapi_response_t run_show_cmd_text(std::string const &) const = 0;

 protected:
   eapi_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eapi_mgr);
};

}  // end namespace eos

#endif // EOS_EAPI_H
