// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_HARDWARE_TABLE_H
#define EOS_TYPES_HARDWARE_TABLE_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

#ifdef SWIG
%ignore eos::hardware_table_key_t(eos::hardware_table_key_t &&) noexcept;
%ignore eos::hardware_table_key_t::operator=(eos::hardware_table_key_t &&) noexcept;
%ignore eos::hardware_table_high_watermark_t(
   eos::hardware_table_high_watermark_t &&) noexcept;
%ignore eos::hardware_table_high_watermark_t::operator=(
   eos::hardware_table_high_watermark_t &&) noexcept;
%ignore eos::hardware_table_usage_t(eos::hardware_table_usage_t &&) noexcept;
%ignore eos::hardware_table_usage_t::operator=(eos::hardware_table_usage_t &&)
   noexcept;
%ignore eos::hardware_table_entry_t(eos::hardware_table_entry_t &&) noexcept;
%ignore eos::hardware_table_entry_t::operator=(eos::hardware_table_entry_t &&)
   noexcept;
#endif

namespace eos {

class hardware_table_key_impl_t;
/** The unique identifier for a hardware table. */
class EOS_SDK_PUBLIC hardware_table_key_t {
 public:
   hardware_table_key_t();
   hardware_table_key_t(std::string const & table_name,
                        std::string const & feature, std::string const & chip);
   hardware_table_key_t(std::string const & table_name,
                        std::string const & feature);
   explicit hardware_table_key_t(std::string const & table_name);
   hardware_table_key_t(const hardware_table_key_t& other);
   hardware_table_key_t& operator=(
      hardware_table_key_t const & other);

   hardware_table_key_t(hardware_table_key_t && other) noexcept;
   hardware_table_key_t & operator=(hardware_table_key_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /**
    * Getter for 'table_name': the name of the hardware resource. For example, this
    * value could be 'TCAM', 'LEM', 'ECMP', 'LPM' etc.
    */
   std::string table_name() const;

   /**
    * Getter for 'feature': the name of the feature using the table, such as
    * 'Multicast', 'IPv6' or 'MPLS'.
    */
   std::string feature() const;

   /**
    * Getter for 'chip': which chip this table is located on. If empty, then this
    * feature's usage is identical across chips.
    */
   std::string chip() const;

   bool operator==(hardware_table_key_t const & other) const;
   bool operator!=(hardware_table_key_t const & other) const;
   bool operator<(hardware_table_key_t const & other) const;
   /** The hash function for type hardware_table_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type hardware_table_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * hardware_table_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const hardware_table_key_t& obj);

 private:
   std::shared_ptr<hardware_table_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const hardware_table_key_t& obj);

class hardware_table_high_watermark_impl_t;
/** The compound high watermark statistics. */
class EOS_SDK_PUBLIC hardware_table_high_watermark_t {
 public:
   hardware_table_high_watermark_t();
   hardware_table_high_watermark_t(uint32_t max_entries, time_t timestamp);
   hardware_table_high_watermark_t(const hardware_table_high_watermark_t& other);
   hardware_table_high_watermark_t& operator=(
      hardware_table_high_watermark_t const & other);

   hardware_table_high_watermark_t(hardware_table_high_watermark_t && other)
      noexcept;
   hardware_table_high_watermark_t & operator=(
      hardware_table_high_watermark_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'max_entries': the maximum number of entries used so far. */
   uint32_t max_entries() const;

   /** Getter for 'timestamp': the last time when high watermark reached. */
   time_t timestamp() const;

   bool operator==(hardware_table_high_watermark_t const & other) const;
   bool operator!=(hardware_table_high_watermark_t const & other) const;
   bool operator<(hardware_table_high_watermark_t const & other) const;
   /** The hash function for type hardware_table_high_watermark_t. */
   uint32_t hash() const;
   /** The hash mix function for type hardware_table_high_watermark_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * hardware_table_high_watermark_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const hardware_table_high_watermark_t& obj);

 private:
   std::shared_ptr<hardware_table_high_watermark_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os,
                         const hardware_table_high_watermark_t& obj);

class hardware_table_usage_impl_t;
/** The usage statistics for a given table (or partition of a table). */
class EOS_SDK_PUBLIC hardware_table_usage_t {
 public:
   hardware_table_usage_t();
   hardware_table_usage_t(uint32_t used_entries, uint32_t free_entries,
                          uint32_t committed_entries);
   hardware_table_usage_t(const hardware_table_usage_t& other);
   hardware_table_usage_t& operator=(
      hardware_table_usage_t const & other);

   hardware_table_usage_t(hardware_table_usage_t && other) noexcept;
   hardware_table_usage_t & operator=(hardware_table_usage_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /**
    * Getter for 'used_entries': number of entries used by this feature on this
    * table.
    */
   uint32_t used_entries() const;

   /**
    * Getter for 'free_entries': the number of free entries available for this
    * feature to use. For features that share a table, if a feature increases its
    * used or committed entries, all other features' free entries will decrease.
    */
   uint32_t free_entries() const;

   /**
    * Getter for 'committed_entries': the number of entries currently allocated for
    * this feature. For tables that have no explicit partitions, this value will be
    * 0.
    */
   uint32_t committed_entries() const;

   bool operator==(hardware_table_usage_t const & other) const;
   bool operator!=(hardware_table_usage_t const & other) const;
   bool operator<(hardware_table_usage_t const & other) const;
   /** The hash function for type hardware_table_usage_t. */
   uint32_t hash() const;
   /** The hash mix function for type hardware_table_usage_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * hardware_table_usage_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const hardware_table_usage_t& obj);

 private:
   std::shared_ptr<hardware_table_usage_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const hardware_table_usage_t& obj);

class hardware_table_entry_impl_t;
/** The hardware table entry for a given table key. */
class EOS_SDK_PUBLIC hardware_table_entry_t {
 public:
   hardware_table_entry_t();
   hardware_table_entry_t(hardware_table_usage_t const & usage,
                          uint32_t max_entries,
                          hardware_table_high_watermark_t const & high_watermark);
   hardware_table_entry_t(const hardware_table_entry_t& other);
   hardware_table_entry_t& operator=(
      hardware_table_entry_t const & other);

   hardware_table_entry_t(hardware_table_entry_t && other) noexcept;
   hardware_table_entry_t & operator=(hardware_table_entry_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'usage': the compound usage statistics. */
   hardware_table_usage_t usage() const;

   /**
    * Getter for 'max_entries': the theoretical maximum number of entries
    * available.
    */
   uint32_t max_entries() const;

   /** Getter for 'high_watermark': the compound high watermark statistics. */
   hardware_table_high_watermark_t high_watermark() const;

   bool operator==(hardware_table_entry_t const & other) const;
   bool operator!=(hardware_table_entry_t const & other) const;
   bool operator<(hardware_table_entry_t const & other) const;
   /** The hash function for type hardware_table_entry_t. */
   uint32_t hash() const;
   /** The hash mix function for type hardware_table_entry_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * hardware_table_entry_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const hardware_table_entry_t& obj);

 private:
   std::shared_ptr<hardware_table_entry_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const hardware_table_entry_t& obj);
}

#endif // EOS_TYPES_HARDWARE_TABLE_H
