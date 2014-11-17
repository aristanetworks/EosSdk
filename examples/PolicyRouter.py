#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

"""The EOS SDK Policy Router.

The policy router is an EOS SDK application usable on Arista switches
supporting policy based routing, such as the Arista 7500E with second
generation linecards.

This long-running agent monitors its JSON formatted configuration file
and when that file changes parses the configuration and if successful
changes policy based routing configuration to match the provided
config.

To operate, the 'pyinotify' module must be installed first, e.g.,:

   # pip install pyinotify

To install this on a switch build an RPM also containing pyinotify and
install that using the EOS extension manager.
"""

import cjson
import collections
import datetime
import functools
import os
import sys

import pyinotify

import eossdk


class Error(Exception):
   pass


class ConfigError(Error):
   pass


PROTOCOLS = {'icmp': 1,
             'ip': 4,  # IP-in-IP
             'tcp': 6,
             'udp': 17,
             'gre': 47,
             'esp': 50,
             'ah': 51,
             'ospf': 89}


NEXTHOP_GROUP_TYPE = {'ipinip': eossdk.NEXTHOP_GROUP_IP_IN_IP,
                      'gre': eossdk.NEXTHOP_GROUP_GRE,
                      }
                      #'mpls': eossdk.NEXTHOP_GROUP_MPLS} # not yet supported


CONFIG_SECTIONS = frozenset(('match',
                             'classifier',
                             'action',
                             'policy',
                             'nexthop_group',
                             'interface_policy'))

MANDATORY_CONFIG_SECTIONS = CONFIG_SECTIONS - set(['nexthop_group'])

# Configuration data structures
Filter = collections.namedtuple(
   'Filter', 'src_ip dst_ip src_mac dst_mac sport dport proto')

Match = collections.namedtuple(
   'Match', 'type acl_name')

Classifier = collections.namedtuple(
   'Classifier', 'matches')

Action = collections.namedtuple('Action', 'type nexthop_group nexthops mpls_labels')

Policy = collections.namedtuple('Policy', 'classifier actions')

Apply = collections.namedtuple('Apply', 'policy')

NexthopGroup = collections.namedtuple('NexthopGroup',
                                      'type src_intf src_ips dst_ips mpls_labels')

Config = collections.namedtuple('Config',
                                'match classifiers actions nexthop_groups policy '
                                'interface_policy')


def load_match(d):
   acls = {}
   for k, vs in sorted(d.iteritems()):
      acls.setdefault(k, [])
      for v in vs:
         ace = Filter(src_ip=v.get('src_ip'),
                       dst_ip=v.get('dst_ip'),
                       src_mac=v.get('src_mac'),
                       dst_mac=v.get('dst_mac'),
                       sport=v.get('sport'),
                       dport=v.get('dport'),
                       proto=v.get('proto'))
         acls[k].append(ace)
   return acls

def load_classifier(d):
   c = {}
   for k, v in d.iteritems():
      matches = [Match(type=None, acl_name=x.get('match')) for x in v]
      c[k] = Classifier(matches=matches)
   return c

def load_action(d):
   a = {}
   for k, v in d.iteritems():
      a[k] = Action(v.get('type'),
                    nexthop_group=v.get('nexthop_group'),
                    nexthops=v.get('nexthops'),
                    mpls_labels=v.get('mpls_labels'))
   return a

def load_policy(d):
   p = {}
   for k, v in d.iteritems():
      p[k] = Policy(**v)
   return p

def load_apply(d):
   a = {}
   for k, v in d.iteritems():
      a[k] = Apply(policy=v)
   return a

def load_nexthop_group(d):
   g = {}
   for k, v in d.iteritems():
      g[k] = NexthopGroup(type=v.get('type', 'ipinip'),
                          src_intf=v.get('src_intf'),
                          src_ips=v.get('src_ips', []),
                          dst_ips=v.get('dst_ips', []),
                          mpls_labels=v.get('mpls_labels', []))
   return g

def load_config(d):
   for section in MANDATORY_CONFIG_SECTIONS:
      if d.get(section) is None:
         raise ValueError('Configuration missing %r section' % section)
   config = Config(
      match=load_match(d['match']),
      policy=load_policy(d['policy']),
      interface_policy=load_apply(d['interface_policy']),
      actions=load_action(d['action']),
      nexthop_groups=load_nexthop_group(d.get('nexthop_group', {})),
      classifiers=load_classifier(d['classifier']))
   return config

def load_config_file(filename):
   config = {}
   with open(filename) as f:
      try:
         config = load_config(cjson.decode(f.read()))
      except (TypeError, ValueError, cjson.Error) as e:
         sys.stderr.write('error reading config: %s\n' % e)
   return config

def load_config_file_obj(f):
   try:
      return load_config(cjson.decode(f.read()))
   except (TypeError, ValueError, cjson.Error) as e:
      sys.stderr.write('error reading config: %s\n' % e)
      return None


class PolicyRouter(object):
   """The policy router state and context."""

   def __init__(self, acl_mgr, agent_mgr, class_map_mgr,
                policy_map_mgr, intf_mgr, nexthop_group_mgr, tag='PR'):
      self.config_ = None
      self.t_ = tag or ''
      self.built_ = False
      self.acl_mgr = acl_mgr
      self.agent_mgr = agent_mgr
      self.class_map_mgr = class_map_mgr
      self.policy_map_mgr = policy_map_mgr
      self.intf_mgr = intf_mgr
      self.nexthop_group_mgr = nexthop_group_mgr
      self.actions_ = {}

   @property
   def config(self):
      return self.config_

   def config_is(self, value):
      if value != self.config_:
         self.config_ = value
      if self.config_:
         self.buildPolicy()

   def _buildAcls(self):
      for aclname, aclrules in self.config.match.iteritems():
         key = eossdk.AclKey(aclname, eossdk.ACL_TYPE_IPV4)

         # todo support ipv6 also
         for i, rule in enumerate(aclrules):
            aclRule = eossdk.AclRuleIp()

            if rule.proto:
               pr = PROTOCOLS.get(rule.proto.lower())
               if pr:
                  aclRule.ip_protocol_is(pr)
               else:
                  sys.stderr.write('Invalid protocol name "%s"', rule.proto)

            if rule.src_ip:
               try:
                  srcPfx = eossdk.IpPrefix(rule.src_ip)
                  addr = eossdk.IpAddrMask(srcPfx.network(),
                                            srcPfx.prefix_length())
                  aclRule.source_addr_is(addr)
               except eossdk.Error:
                  sys.stderr.write('bad IP address: %s\n', rule.src_ip)
                  continue

            if rule.dst_ip:
               try:
                  dstPfx = eossdk.IpPrefix(rule.dst_ip)
                  addr = eossdk.IpAddrMask(dstPfx.network(),
                                            dstPfx.prefix_length())
                  aclRule.destination_addr_is(addr)
               except eossdk.Error:
                  sys.stderr.write('bad IP address: %s\n', rule.dst_ip)
                  continue

            if rule.sport:
               try:
                  spec = self._buildPortSpec(rule.sport)
               except ConfigError as e:
                  sys.stderr.write('Invalid port spec %r: %s\n', spec, e)
               else:
                  aclRule.source_port_is(spec)

            if rule.dport:
               try:
                  spec = self._buildPortSpec(rule.dport)
               except ConfigError as e:
                  sys.stderr.write('Invalid port spec %r: %s\n', spec, e)
               else:
                  aclRule.destination_port_is(spec)

            self.acl_mgr.acl_rule_set(key, i, aclRule)
      self.acl_mgr.acl_commit()

   def _buildPortSpec(self, portspec):
      # pylint:disable-msg=E1101
      op = portspec.get('op', 'eq').lower()  # default to port equals
      ports = portspec.get('ports', [])
      if op == 'eq':
         return eossdk.AclPortSpecEq(ports)
      elif op == 'neq':
         return eossdk.AclPortSpecNeq(ports)
      elif op == 'range':
         if len(ports) != 2:
            raise ConfigError('Must provide exactly two ports for "eq"')
         return eossdk.AclPortSpecRange(ports[0], ports[1])
      elif op == 'gt':
         if len(ports) != 1:
            raise ConfigError('Must provide only one port for "gt"')
         return eossdk.AclPortSpecGt(ports[0])
      elif op == 'lt':
         if len(ports) != 1:
            raise ConfigError('Must provide only one port for "lt"')
         return eossdk.AclPortSpecLt(ports[0])
      else:
         raise ConfigError('Unknown port match operation "%s"' % op)

   def _buildClassMaps(self):
      classifiers = self.config_.classifiers
      for name, classifier in classifiers.iteritems():
         key = eossdk.PolicyMapKey(name, eossdk.POLICY_FEATURE_PBR)
         class_map = eossdk.ClassMap(key)

         for rule_index, match in enumerate(classifier.matches):
            print 'Adding to class map:', name, 'seq:', str(rule_index + 1), match
            rule_key = eossdk.AclKey(match.acl_name, eossdk.ACL_TYPE_IPV4)
            rule = eossdk.ClassMapRule(rule_key)
            # Set the action for the rule
            class_map.rule_set(rule_index + 1, rule)
         self.class_map_mgr.class_map_is(class_map)
         cm = self.class_map_mgr.class_map(key)
         print 'Set class map:', name, 'now with', len(cm.rules()), 'rules'

   def _buildActions(self):
      for name, action in self.config_.actions.iteritems():
         if action.type == 'drop':
            act = eossdk.PolicyMapAction(eossdk.POLICY_ACTION_DROP)
         elif action.type == 'nexthop_group' and action.nexthop_group:
            act = eossdk.PolicyMapAction(eossdk.POLICY_ACTION_NEXTHOP_GROUP)
            act.nexthop_group_name_is(action.nexthop_group)
         elif action.type == 'nexthop' and action.nexthops:
            act = eossdk.PolicyMapAction(eossdk.POLICY_ACTION_NEXTHOP)
            for nh in action.nexthops:
               hop = getIpAddr(nh)
               if hop is not None:
                  act.nexthop_set(hop)
         else:
            raise ConfigError('Action type="%s" not supported' % action.type)
         self.actions_[name] = act

   def _buildNexthopGroups(self):
      groups = self.config_.nexthop_groups
      for name, data in groups.iteritems():
         if data.type not in NEXTHOP_GROUP_TYPE:
            sys.stderr.write('Unknown nexthop group type="%s"' % data.type)
            continue
         t = data.type.lower()
         group = eossdk.NexthopGroup(name, NEXTHOP_GROUP_TYPE.get(t))
         # Set common parameters
         for i, dst in enumerate(data.dst_ips):
            ip = getIpAddr(dst)
            if ip is not None:
               print 'Adding IP'
               group.destination_ip_set(i, ip)

         if t == 'ipinip' or t == 'gre':
            if data.src_intf:
               if self.intf_mgr.exists(eossdk.IntfId(data.src_intf)):
                  group.source_intf_is(eossdk.IntfId(data.src_intf))
            elif data.src_ips:
               pass  # not yet supported
         elif t == 'mpls':
            sys.stderr.write('MPLS nexthop-groups are not yet supported\n')
         # Set the nexthop group
         print 'Setting nexthop group:', name
         self.nexthop_group_mgr.nexthop_group_set(group)

   def _buildPolicyMaps(self):
      policies = self.config_.policy
      for name, data in policies.iteritems():
         # add the class map
         rule_key = eossdk.PolicyMapKey(data.classifier,
                                        eossdk.POLICY_FEATURE_PBR)
         rule = eossdk.PolicyMapRule(rule_key)

         for actionName in data.actions:
            # raises KeyError on uknown action names
            action = self.actions_[actionName]
            rule.action_set(action)
         key = eossdk.PolicyMapKey(name, eossdk.POLICY_FEATURE_PBR)
         policy_map = eossdk.PolicyMap(key)
         policy_map.rule_set(1, rule)
         self.policy_map_mgr.policy_map_is(policy_map)

   def _applyToInterfaces(self):
      interface_policy = self.config_.interface_policy
      for intf_name, data in interface_policy.iteritems():
         policy_map_key = eossdk.PolicyMapKey(data.policy, eossdk.POLICY_FEATURE_PBR)
         intf_id = eossdk.IntfId(intf_name)
         if self.intf_mgr.exists(intf_id):
            print 'Interface %s exists, applying policy' % intf_id.to_string()
            self.policy_map_mgr.policy_map_apply(
               policy_map_key, intf_id, eossdk.ACL_IN, True)
         else:
            print 'Interface %s does not exist' % intf_id.to_string()
      print 'Finished applying policy'

   def buildPolicy(self):
      assert self.config_
      self.built_ = False
      print 'Building ACLs'
      self._buildAcls()
      print 'Building class maps'
      self._buildClassMaps()
      print 'Building actions for policy maps'
      self._buildActions()
      print 'Building nexthop groups'
      self._buildNexthopGroups()
      print 'Building policy maps'
      self._buildPolicyMaps()
      print 'Applying policy to interfaces'
      self._applyToInterfaces()
      self.built_ = True
      print 'Finished building policy'

   @property
   def built(self):
      return self.built_

   def applyPolicy(self):
      assert self.built_
      self._applyToInterfaces()


class InotifyPoller(eossdk.TimeoutHandler):

   def __init__(self, sdk, config_file, policy_handler, poll_interval=0.5):
      self.config_file_ = config_file
      self.sdk_ = sdk
      self.policy_handler_ = policy_handler
      self.poll_interval_ = poll_interval
      self.wm_ = pyinotify.WatchManager()
      # pylint:disable-msg=E1101
      mask = pyinotify.IN_MODIFY | pyinotify.IN_CREATE | pyinotify.IN_DELETE
      # pylint:enable-msg=E1101
      handler = functools.partial(InotifyHandler, handler=policy_handler)
      # Allow coalescing, so that delete/recreate (as opposed to modify) doesn't
      # cause us to delete the policy.
      self.notifier_ = pyinotify.Notifier(self.wm_, handler, timeout=10)
      self.notifier_.coalesce_events()
      self.watch_ = self.wm_.watch_transient_file(self.config_file_, mask, handler)
      eossdk.TimeoutHandler.__init__(self, self.sdk_.get_timeout_mgr())
      self.timeout_time_is(eossdk.now())

   def poll(self):
      self.notifier_.process_events()
      while self.notifier_.check_events():
         self.notifier_.read_events()
         self.notifier_.process_events()

   def on_timeout(self):
      self.poll()
      self.timeout_time_is(eossdk.now() + self.poll_interval_)


class PolicyHandler(eossdk.AgentHandler, eossdk.PolicyMapHandler, eossdk.AclHandler):

   def __init__(self, sdk, config_file=None):
      self.config_file_ = config_file
      self.sdk_ = sdk
      self.config_ = None
      self.acl_mgr = sdk.get_acl_mgr()
      self.agent_mgr = sdk.get_agent_mgr()
      self.policy_map_mgr = sdk.get_policy_map_mgr()
      self.router_ = PolicyRouter(
         self.acl_mgr, self.agent_mgr, sdk.get_class_map_mgr(),
         self.policy_map_mgr, sdk.get_intf_mgr(), sdk.get_nexthop_group_mgr())
      self.timeout_ = None
      self.watches_ = frozenset()
      # pylint: disable-msg=W0233
      eossdk.PolicyMapHandler.__init__(self, self.policy_map_mgr)
      eossdk.AclHandler.__init__(self, self.acl_mgr)
      eossdk.AgentHandler.__init__(self, self.agent_mgr)
      # pylint: enable-msg=W0233

   @property
   def config(self):
      return self.config_

   def config_is(self, config):
      self.config_ = config
      self.router_.config_is(config)
      self.watch_policy()

   def watch_policy(self):
      print 'Removing all watches for %s' % self.watches_
      for name in self.watches_:
         # pylint:disable-msg=E1101
         self.watch_policy_map(
            eossdk.PolicyMapKey(name, eossdk.POLICY_FEATURE_PBR), False)
      self.watches_ = frozenset(self.config_.policy.iterkeys())
      print 'Adding new watches for %s' % self.config_.policy.keys()
      for name in self.config_.policy:
         # pylint: disable-msg=E1101
         self.watch_policy_map(
            eossdk.PolicyMapKey(name, eossdk.POLICY_FEATURE_PBR), True)

   def on_initialized(self):
      print self.__class__.__name__, 'was initialized by the SDK'
      print 'Loading initial config'
      config = load_config_file(self.config_file_)
      if config is None:
         raise Error('Invalid configuration')
      self.config_is(config)
      print 'Finished loading initial config'
      print 'Starting Inotify notifier'
      self.timeout_ = InotifyPoller(self.sdk_, self.config_file_, self)

   # pylint: disable-msg=W0221
   def on_agent_option(self, name, value):
      if name == 'config_file':
         config = load_config_file(value)
         if config != self.config:
            self.agent_mgr.status_set('config_changed', datetime.datetime.today())
            self.config_is(config)

   def on_policy_map_sync(self, key):
      self.agent_mgr.status_set('last_policy_map_sync_state', 'PASS')
      self.agent_mgr.status_set('last_policy_map_sync_at',
                                str(datetime.datetime.today()))
      self.agent_mgr.status_set('last_policy_map_sync_key', str(key))

   def on_policy_map_sync_fail(self, key, message):
      self.agent_mgr.status_set('last_policy_map_sync_state', 'FAIL')
      self.agent_mgr.status_set('last_policy_map_sync_key', str(key))
      self.agent_mgr.status_set('last_policy_map_sync_error_message', message)

   # pylint: disable-msg=W0221
   def on_agent_enabled(self, enabled):
      self.agent_mgr.status_set('enabled', enabled)

   def on_acl_sync(self):
      self.agent_mgr.status_set('last_acl_sync', str(datetime.datetime.today()))

   def on_acl_sync_fail(self, linecard, message):
      self.agent_mgr.status_set('last_acl_sync_err_linecard', linecard)
      self.agent_mgr.status_set('last_acl_sync_err_message', message)


class InotifyHandler(pyinotify.ProcessEvent):
   """Handles inotify events."""

   # satisfy pylint's W0201 warnings
   handler_ = None

   def process_IN_CREATE(self, event):
      print 'Config file created:', event.pathname
      config = load_config_file(event.pathname)
      if config:
         self.handler_.config_is(config)

   def process_IN_MODIFY(self, event):
      config = load_config_file(event.pathname)
      if config == self.handler_.config:
         print 'Config file modified but not changed: ', event.pathname
      else:
         print 'Config file updated:', event.pathname
         self.handler_.config_is(config)

   def my_init(self, **kwargs):
      self.handler_ = kwargs['handler']


def getIpAddr(ip_addr):
   try:
      return eossdk.IpAddr(ip_addr)
   except eossdk.Error as e:
      sys.stderr.write('Invalid IP address: %s (%s)' % (ip_addr, e))


# Called by the script 'PolicyRouter'
def main():
   # Config file path has to be provided by the environment variable
   envvar = 'POLICY_ROUTER_CONFIG'
   filename = os.environ.get(envvar)

   if filename is not None:
      # Obtain a reference to the EOS SDK
      sdk = eossdk.Sdk()
      # Instantiate the policy router application
      _ = PolicyHandler(sdk, filename)
      # Run the agent until terminated by a signal
      sdk.main_loop('PolicyRouter')
   else:
      sys.stderr.write(
         'Usage: %s=<path_to_json_config> %s\n\n' % (envvar, sys.argv[0]))
