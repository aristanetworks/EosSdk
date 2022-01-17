// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * The bfd module manages BFD sessions
 *
 * Bi-directional Forwarding Detection (BFD) is a low-latency protocol designed
 * to detect faults between two forwarding planes. The protocol itself is
 * independent from media, link and routing protocols. In EOS, BFD is
 * implemented on top of IP encapuslations, conforming to RFC5881.
 *
 * This module provides APIs to provision BFD. APIs include
 *  - BFD session creation
 *  - BFD session getter
 *  - BFD session deletion
 *  - BFD global interval timers setter/getter
 *  - BFD interface timers setter/getter
 *  - BFD session status getter
 *  
 *  An iterator is also provided to iterate through all BFD sessions that are
 *  configured via EosSdk in the system.
 *
 */

#ifndef EOS_BFD_H
#define EOS_BFD_H

#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>
#include <eos/mpls.h>

#include <eos/types/bfd.h>

namespace eos {

class bfd_session_mgr;

/**
 *  The BFD handler.
 *
 *  This class provides handler APIs to react to a BFD's session state change.
 *
 **/
class EOS_SDK_PUBLIC bfd_session_handler : 
   public base_handler<bfd_session_mgr, bfd_session_handler> {
 public:
   explicit bfd_session_handler(bfd_session_mgr *mgr);
   bfd_session_mgr * get_bfd_session_mgr() const;

   /**
    * Registers this class to receive change updates on all BFD sessions.
    *
    * Expects a boolean signifying whether notifications should be generated
    * for all BFD sessions created by EosSdk or not.
    *
    * This controls notifications on:
    *  - on_bfd_session_status()
    *  - on_bfd_session_set()
    *  - on_bfd_session_del()
    */
   void watch_all_bfd_sessions(bool);

  /**
    * Registers this class to receive change updates on the given BFD session.
    *
    * Expects the session key of the corresponding BFD session and a boolean
    * signifying whether notifications should be propagated to this BFD session
    * or not.
    */
   void watch_bfd_session(bfd_session_key_t const &, bool);

   /**
    * Handler called when the status of a BFD session status changes.
    *
    * Possible status are:
    *   BFD_SESSION_STATUS_NULL
    *   BFD_SESSION_STATUS_DOWN
    *   BFD_SESSION_STATUS_INIT
    *   BFD_SESSION_STATUS_UP
    *   BFD_SESSION_STATUS_ADMIN_DOWN
    *
    */
   virtual void on_bfd_session_status(bfd_session_key_t const &,
                                      bfd_session_status_t);

   /**
    * Handler called when a BFD session is created
    */
   virtual void on_bfd_session_set(bfd_session_key_t const &);

   /**
    * Handler called when a BFD session is deleted
    */
   virtual void on_bfd_session_del(bfd_session_key_t const &);

   /**
    * Registers this class to receive change updates on all sBFD echo
    * sessions created by EosSdk.
    *
    * Expects a boolean signifying whether notifications should be generated
    * for all sBFD echo sessions created by EosSdk or not.
    *
    * This controls notifications on:
    *  - on_sbfd_echo_session_status()
    *  - on_sbfd_echo_session_set()
    *  - on_sbfd_echo_session_del()
    */
   void watch_all_sbfd_echo_sessions(bool);

   /**
    * Registers this class to receive change updates on the given sBFD
    * echo session.
    *
    * Expects the session key of the corresponding sBFD echo session.
    * and a boolean signifying whether notifications should be
    * propagated to this sBFD echo session or not.
    */
   void watch_sbfd_echo_session(sbfd_echo_session_key_t const &, bool);

   /**
    * Handler called when the status of a sBFD echo session status changes.
    *
    * Possible status are:
    *   BFD_SESSION_STATUS_NULL
    *   BFD_SESSION_STATUS_DOWN
    *   BFD_SESSION_STATUS_INIT
    *   BFD_SESSION_STATUS_UP
    *   BFD_SESSION_STATUS_ADMIN_DOWN
    *
    */
   virtual void on_sbfd_echo_session_status(sbfd_echo_session_key_t const &,
                                            bfd_session_status_t);

   /**
    * Handler called when a sBFD echo session is created.
    */
   virtual void on_sbfd_echo_session_set(sbfd_echo_session_key_t const &);

   /**
    * Handler called when a sBFD echo session is deleted.
    */
   virtual void on_sbfd_echo_session_del(sbfd_echo_session_key_t const &);

   /**
    * Handler called periodically for sBFD echo sessions where RTT
    * statistics have been enabled with sbfd_echo_rtt_enabled_set.
    */
   virtual void on_sbfd_echo_session_rtt(sbfd_echo_session_key_t const &,
                                         sbfd_echo_session_rtt_stats_t const &);
};

class bfd_session_iter_impl;

/**
 * An iterator that yields an bfd_session_key_t for each configured BFD session
 */
class EOS_SDK_PUBLIC bfd_session_iter_t:
      public iter_base<bfd_session_key_t, bfd_session_iter_impl> {
 private:
   friend class bfd_session_iter_impl;
   explicit bfd_session_iter_t(bfd_session_iter_impl * const) EOS_SDK_PRIVATE;
};

class sbfd_echo_session_iter_impl;

/**
 * An iterator that yields an sbfd_echo_session_key_t for each
 * configured sBFD echo session
 */
class EOS_SDK_PUBLIC sbfd_echo_session_iter_t
      : public iter_base< sbfd_echo_session_key_t, sbfd_echo_session_iter_impl > {
 private:
   friend class sbfd_echo_session_iter_impl;
   explicit sbfd_echo_session_iter_t( sbfd_echo_session_iter_impl * const )
      EOS_SDK_PRIVATE;
};

/**
 * A manager of BFD session configurations for EosSdk client
 *
 * Create one of these via an sdk object prior to starting the agent main loop.
 * When your eos::agent_handler::on_initialized virtual function is called, the
 * manager is valid for use.
 */
class EOS_SDK_PUBLIC bfd_session_mgr :
      public base_mgr<bfd_session_handler, bfd_session_key_t> {
 public:
   virtual ~bfd_session_mgr();

   /**
    * Returns an iterator over all BFD sessions configured through EosSdk on
    * the system.
    */
   virtual bfd_session_iter_t session_iter() const = 0;

   /**
    * Return true if the BFD session is configured.
    */
   virtual bool exists(bfd_session_key_t const &) const = 0;

   /**
    * Creates a BFD session. If an existing session has already been created by
    * other client (i.e. BGP, OSPF), no new BFD session will be created.
    * Instead, EsoSdk will be added to the list of clients that will receive
    * BFD session status change notifications.
    */
   virtual void session_set(bfd_session_key_t const &) = 0;

   /**
    * Returns the BFD session with the specified key. Will return an empty
    * bfd_session_t if the BFD session does not exist already.
    */
   virtual bfd_session_t session(bfd_session_key_t const &) const = 0;

   /**
    * Remove a BFD session if it exists. It is a no-op if the specified BFD
    * session does not exist.
    */
   virtual void session_del(bfd_session_key_t const &) = 0;

   /**
    * Set BFD default interval value. It will be applied to all interface
    * unless overridden by per-interface interval configuration.
    */
   virtual void default_interval_is(bfd_interval_t const &) = 0;

   /**
    * Get global BFD interval configuration. 
    */
   virtual bfd_interval_t default_interval() const = 0;

   /**
    * Set BFD interval on an interface.
    */
   virtual void interval_is(intf_id_t intf, bfd_interval_t const &) = 0;

   /**
    * Get BFD interval configuration on an interface.
    */
   virtual bfd_interval_t interval(intf_id_t intf) const = 0;

   /**
    * Reset BFD interval configuration on an interface back to value configured
    * by bfd_default_interval_is(). If bfd_default_interval_is() has not been
    * explicitly called to configure a default interval, the interval will be
    * reset to tx=300ms, rx=300ms and mult=3.
    */
   virtual void interval_reset(intf_id_t intf) = 0;

   /**
    * Return the BFD status given a BFD session key.
    */
   virtual bfd_session_status_t session_status(bfd_session_key_t const &) const = 0;

   /**
    * sBFD echo sessions.
    *
    * Only a single EosSdk application can use the sbfd_echo_* APIs,
    * if a second application attempts to use them, it will result in
    * a panic / exception.
    */

   /**
    * Returns an iterator over all sBFD echo sessions configured
    * through EosSdk on the system.
    */
   virtual sbfd_echo_session_iter_t sbfd_echo_session_iter() const = 0;

   /**
    * Return true if the sBFD echo session is configured.
    */
   virtual bool sbfd_echo_session_exists(sbfd_echo_session_key_t const &) const = 0;

   /**
    * Create a sBFD echo session.
    */
   virtual void sbfd_echo_session_set(sbfd_echo_session_key_t const &) = 0;

   /**
    * Remove a sBFD echo session if it exists. It is a no-op if the
    * specified sBFD session does not exist.
    */
   virtual void sbfd_echo_session_del(sbfd_echo_session_key_t const &) = 0;

   /**
    * Set sBFD echo session default interval value. It will be applied
    * to all sBFD echo session.
    */
   virtual void sbfd_echo_default_interval_set(sbfd_interval_t const &) = 0;

   /**
    * Get global sBFD echo session interval configuration.
    */
   virtual sbfd_interval_t sbfd_echo_default_interval() const = 0;

   /**
    * Set sBFD echo session interval value per session
    */
   virtual void sbfd_echo_interval_set(sbfd_echo_session_key_t const &,
                                       sbfd_interval_t const &) = 0;

   /**
    * Get sBFD echo session interval configuration.
    */
   virtual sbfd_interval_t
      sbfd_echo_interval(sbfd_echo_session_key_t const &) const = 0;

   /**
    * Reset sBFD echo session interval configuration on a session back to
    * value configured by sbfd_echo_default_interval_set(). If
    * sbfd_echo_default_interval_set() has not been explicitly called
    * to configure a default interval, the interval will be reset to
    * tx=300ms and mult=3.
    */
   virtual void sbfd_echo_interval_reset(sbfd_echo_session_key_t const &) = 0;

   /**
    * Request RTT measurements for the sBFD probe packets.
    *
    * RTTs will be reported via the on_sbfd_echo_session_rtt at
    * intervals configured by
    *
    * router bfd
    *  session stats snapshot interval ((dangerous <1-9>)|<10-3600 seconds>)
    */
   virtual void sbfd_echo_rtt_enabled_set(sbfd_echo_session_key_t const &, bool) = 0;

   /**
    * Is sBFD RTT measurements enabled?
    */
   virtual bool sbfd_echo_rtt_enabled(sbfd_echo_session_key_t const &) const = 0;

   /**
    * Return the BFD status given a sBFD echo session key.
    */
   virtual bfd_session_status_t sbfd_echo_session_status(
      sbfd_echo_session_key_t const &) const = 0;

 protected:
   bfd_session_mgr() EOS_SDK_PRIVATE;
   friend class bfd_session_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(bfd_session_mgr);
};

} // end namespace eos

#include <eos/inline/bfd.h>

#endif // EOS_BFD_H

