// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_FPGA_H
#define EOS_FPGA_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>

#include <eos/types/fpga.h>

namespace eos {

class fpga_mgr;

class EOS_SDK_PUBLIC fpga_handler : public base_handler<fpga_mgr, fpga_handler> {

   public:
      explicit fpga_handler(fpga_mgr *);
      fpga_mgr * get_fpga_mgr() const;

      void watch_all_fpga(bool);
      void watch_fpga(const fpga_t&, bool);
      virtual void on_fpga_load_image(const fpga_t&);
      virtual void on_fpga_load_image_failed(const fpga_t&);
      virtual void on_fpga_unload_image(const fpga_t&);
};

class fpga_iter_impl;

class EOS_SDK_PUBLIC fpga_iter_t : public iter_base<fpga_t,
                                                    fpga_iter_impl> {
   private:
      friend class fpga_iter_impl;
      explicit fpga_iter_t(fpga_iter_impl * const) EOS_SDK_PRIVATE;

};

class EOS_SDK_PUBLIC fpga_mgr : public base_mgr<fpga_handler, fpga_t> {
   public:
      virtual ~fpga_mgr();

      virtual fpga_iter_t fpga_status_iter() const = 0;
   protected:
      fpga_mgr() EOS_SDK_PRIVATE;
      friend class fpga_handler;

   private:
      EOS_SDK_DISALLOW_COPY_CTOR(fpga_mgr);
};

} // end namespace eos

#include <eos/inline/fpga.h>

#endif // EOS_FPGA_H

