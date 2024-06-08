# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

# pylint: disable=consider-using-f-string

import jsonrpclib
import time
import sys

# A library to help users test their agents using eapi infrastructure.
# For example, user can use this library to issue some configuration
# commands, expecting their agents to respond to those commands, and
# then again use this library to check the corresponding status (as
# the result of their agents' action).
#
# This library also contains utilities to manage users' agents.

SERVER_PROTOCOL_HTTP = "http"
SERVER_PROTOCOL_HTTPS = "https"
JSON = "json"
TEXT = "text"


class Error(Exception):
   pass


class ProtocolError(Error):
   """ EosSdk JSONRPC or HTTP error, such as HTTP 401 Unauthorized user error.

       And these are JSON-RPC 2.0 Defined Errors:
       Code             Description
       -32700           Parse Error
       -32600           Invalid Request
       -32601           Method not found
       -32602           Invalid params
       -32603           Internal server error
   """
   def __init__(self, code, message, data):
      Error.__init__(self, (code, message, data))


class ConnectionError(Error):  # pylint: disable=redefined-builtin
   """ Connection exception, 'error' gives out error details """
   def __init__(self, error):
      Error.__init__(self,
                     "Connection not accepted by server: %s" % error)


class ClientError(Error):
   """ EosSdk eapi error, the data and message correspond to those in
       jsonrpc response['error'].

       Code    Description
       1000    General error
       1001    Command caused internal exception
       1002    Invalid command: the string does not match any command
       1003    Command not ready: attempted to get json from a showcommand, however
               the command has not been converted to be compatible with the Command
               API yet. Use format = text to run this command and get ASCII output.
       1004    Command incompatible: cannot run command over the Command API
       1005    Command unauthorized: user has insufficient permissions to run the
               command
   """
   def __init__(self, code, msg=None, data=None):
      Error.__init__(self, (code, msg, data))


class TimeoutError(Error):  # pylint: disable=redefined-builtin
   """ This error can be raised whenever something not happening within a specified
       time period. One example can be if user changes some configuration and
       expects the corresponding status to be changed.
       Check function 'wait_for" to see how it's used. """
   def __init__(self, msg):
      Error.__init__(self, msg)


class TestLib:
   def __init__( self, host_name, user_name, password, port=None, is_secure=False ):
      """ Establish the eAPI session.

          host_name: the host name or ip address of the switch against which the
                    test is run.
          user_name: the user name used to log on switch. It must be configured
                    on switch already.
          password: the password of the user.
          port: the port number of the EOS eAPI.
          is_secure: whether http or https to be used for EOS eAPI.

          returns: list of outputs """
      # remember the args so we can re-init after rebooting the dut
      self.host_name_ = host_name
      self.user_name_ = user_name
      self.password_ = password
      self.port_ = port
      self.is_secure_ = is_secure
      self.eapi_ = None

      self.setupEapi()

   def setupEapi(self):
      # setup the eApi connection
      proto = SERVER_PROTOCOL_HTTPS if self.is_secure_ else SERVER_PROTOCOL_HTTP
      port_string = self.port_ if self.port_ else ''
      url = "{}://{}:{}@{}{}/command-api".format( proto,
                                                  self.user_name_, self.password_,
                                                  self.host_name_, port_string )
      self.history_ = jsonrpclib.history.History()
      self.eapi_ = jsonrpclib.Server(url, history=self.history_)

      # After a reboot it might take a while before the http server is operational
      # probe and ignore errors until we get a response, or timeout and burn
      def testEapiConnection():
         try:
            self.run_cmds(["show version"])
            return True
         except (ProtocolError, ConnectionError):
            return False

      wait_for(testEapiConnection,
               "switch to be reachable via http command-api\n",
               timeout=600)

   def reset(self):
      """ re-initialize the eApi connection (for example after a reboot) """
      self.setupEapi()

   def eapi(self):
      return self.eapi_

   def run_cmds(self, cmds, data_format=JSON):
      """ Run the commands in the 'cmds' list. The list should contain commands
          to enter submodes too.

          cmds: list of command to be run
          data_format: output data format type (json/text)

          returns: list of outputs """

      try:
         response_list = self.eapi_.runCmds(1, cmds, data_format)
      except OSError as e:
         raise ConnectionError( e.strerror )  # pylint: disable=raise-missing-from
      except jsonrpclib.jsonrpc.TransportError as e:
         # pylint: disable-next=raise-missing-from
         raise ProtocolError(e.errcode, e.errmsg, str(e.msg))
      except jsonrpclib.jsonrpc.ProtocolError:
         response_list = jsonrpclib.loads(self.history_.response)
         code = response_list['error']['code']
         msg = response_list['error']['message']
         data = response_list['error']['data']
         # pylint: disable-next=no-else-raise
         if code < -32000:  # JSON-RPC 2.0 defined errors
            # pylint: disable-next=raise-missing-from
            raise ProtocolError(code, msg, data)
         else:  # eapi errors
            raise ClientError(code, msg, data)  # pylint: disable=raise-missing-from

      return response_list


class AgentLib:
   def __init__(self, test_lib, agent_name, agent_binary_path, args=None):
      """ This class handles all functions needed for an agent.

          agent_name: the name for this (third party) agent.
          agent_binary_path: the full path of the agent executable, for instance,
                             it can be /mnt/flash/cpp_bin or
                             /mnt/flash/python_script.py
                             Note, this agent executable should have been copied
                             to this location already.
          args: a list of arguments to the agent. """

      self.test_lib = test_lib
      self.agent_name = agent_name
      self.agent_binary_path = agent_binary_path
      self.args = ''.join(args) if args else ''

   def __enter__(self):
      return self

   def __exit__(self, typ, value, traceback):
      """ Cleans up the daemon, if configured """
      r = self.test_lib.run_cmds(["enable", "show daemon"])
      if self.agent_name not in r[1]['daemons']:
         return
      if r[1]['daemons'][self.agent_name]['running']:
         self.stop_agent()
      self.remove_agent()

   def start_agent(self):
      """ Starts an agent on switch. Note, to start an agent, the EosSdk.i686.rpm
          extension should have been installed already, otherwise, the agent
          won't be started.
          Once started, the agent is running as a daemon on switch. """

      cmds = [ "enable", "configure terminal",
               "daemon %s" % self.agent_name,
               f"exec {self.agent_binary_path} {self.args}",
               "no shutdown" ]

      self.test_lib.run_cmds( cmds )
      wait_for(self.agent_running, "agent running", timeout=600)

   def stop_agent(self):
      """ Disable an agent by running shutdown"""
      self.test_lib.run_cmds(["enable", "configure terminal",
                              "daemon %s" % self.agent_name,
                              "shutdown"])
      wait_for(lambda: not self.agent_running(),
               "agent running", timeout=600)

   def remove_agent(self):
      """ This function removes a agent and its configuration from switch """
      self.test_lib.run_cmds(["enable", "configure terminal",
                             "no daemon %s" % self.agent_name])

   def agent_option_is(self, key, value):
      """ Configures an option/value pair for this agent by issuing
          'option opt value val' command."""
      self.test_lib.run_cmds( [ "enable", "configure terminal",
                                "daemon %s" % self.agent_name,
                                f"option {key} value {value}" ] )

   def agent_option_del( self, key ):
      """ Removes an option/value pair from this daemon's configuration. """
      self.test_lib.run_cmds(["enable", "configure terminal",
                              "daemon %s" % self.agent_name,
                              "no option %s" % key])

   def agent_data(self):
      """ Returns the JSON data for the current agent. If the agent does not exist,
          raises ClientError exception with error message 'daemon not
          configured'. """
      data = self.test_lib.run_cmds(["enable",
                                    "show daemon %s" % self.agent_name])
      return data[1]['daemons'][self.agent_name]

   def agent_option(self, key):
      """ Returns the agent's configured value for the given key, or the empty
          string if that key doesn't exist.
          Note ClientError is thrown if the agent is not configured on
          the switch. """
      data = self.agent_data()
      if key not in data['option']:
         return ''
      return data['option'][key]

   def agent_running(self):
      """ Returns True if the agent specified is running, False otherwise.
          Note it returns False if the agent is not configured. """
      try:
         data = self.agent_data()
         return data['running']
      except ClientError:
         return False

   def pid(self):  # pylint: disable=inconsistent-return-statements
      """Returns the PID of the agent if found"""
      try:
         data = self.agent_data()
         return data['pid']
      except ClientError:
         pass
      except KeyError:
         # Agent PID probably not in AgentDirectory yet
         return

   def wait_for_status_exists(self, key, timeout=600):
      """ This function keeps checking the agent's status to see if the
          specified 'key' exists, and returns if it finds it.
          It throws TimeoutError if the 'key' doesn't exist within the
          spedified time."""
      def see_key():
         data = self.agent_data()
         return key in data['data']
      wait_for(see_key, "status '%s' to appear" % key, timeout=timeout)

   def wait_for_status_del(self, key, timeout=600):
      """ This function keeps checking the agent's status to see if the
          specified 'key' is not existing, it returns if it doesn't find the
          'key'.
          It throws TimeoutError if the 'key' still shows up after the
          specified timeout value."""
      def not_see_key():
         data = self.agent_data()
         return key not in data['data']
      wait_for(not_see_key, "status %s to appear" % key, timeout=timeout)

   def wait_for_status(self, key, expected_value):
      """ This is a convenience function for checking the value of the specified
          'key' in agent status database (called 'data').

          Agent can set the status based on its business logic, such as responding
          to the 'option/value' configuration command. """
      self.wait_for_status_exists(key)

      def get_status():
         data = self.agent_data()
         return expected_value == data['data'][key]
      wait_for( get_status,
                f"status '{key}' to be '{expected_value}'",
                timeout=600 )

   def wait_for( self, func, description, timeout=300.0 ):
      """ The jump from EosSdkGenericTestLib.AgentLib.wait_for to
          EosSdkGenericTestLib.wait_for is kept for legacy reasons in case some
          customers were relying on it.
      """
      wait_for(func, description, timeout)


def wait_for(func, description, timeout=300.0):
   """ Run 'func' repeatedly till it returns a true value, or raise
       TimeoutError if we reach the given timeout before it returns a true
       value.

       description: description of what we are waiting for.
       timeout: the timeout value in seconds, after which we raise exception

       Note, if the system time clock gets changed, this function may behave
       incorrectly.
   """
   # statically define backoff values, max delay is 5 seconds
   backoff = [0, 0.1, 0.5, 1, 2, 5]
   begin_time = time.time()
   end_time = begin_time + timeout
   index = 0
   while time.time() < end_time:
      r = func()
      if r:
         if index >= 3:
            sys.stderr.write(" Success!\n")
            sys.stderr.flush()
         return r
      sys.stderr.write(".")
      sys.stderr.flush()
      if index == 3:  # After 3 retries, tell user what we are waiting for
         sys.stderr.write("Checking %s" % description)
         sys.stderr.flush()
      wait_time = backoff[index]
      index = index + 1 if backoff[index] != backoff[-1] else index
      time.sleep(wait_time)
   raise TimeoutError("Timed out waiting for %s." % description)
