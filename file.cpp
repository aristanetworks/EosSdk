// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/file.h>
#include <eos/panic.h>
#include <FileSm.h>
#include <map>
#include <Tac/Tracing.h>

DEFAULT_TRACE_HANDLE( "EosSdkFile" )

namespace eos {

static std::map< file_handler *, FileHandlerSm::Ptr >
file_handler_to_file_handler_sm;

static std::map< FileHandlerSm *, file_handler * >
file_handler_sm_to_file_handler;

file_handler::file_handler() {
   FileHandlerSm::Ptr fileHandlerSm = FileHandlerSm::FileHandlerSmIs();
   file_handler_sm_to_file_handler[ fileHandlerSm.ptr() ] = this;
   file_handler_to_file_handler_sm[ this ] = fileHandlerSm;
}

file_handler::~file_handler() {
   FileHandlerSm::Ptr fileHandlerSm = file_handler_to_file_handler_sm[ this ];
   file_handler_sm_to_file_handler.erase( fileHandlerSm.ptr() );
   file_handler_to_file_handler_sm.erase( this );
}

FileDescriptorSm::Ptr
get_file_descriptor_sm( file_handler *file_handler, int fd ) {
   FileHandlerSm::Ptr fhSm = file_handler_to_file_handler_sm[ file_handler ];
   assert( fhSm );
   // Get or create a file descriptor sm for this descriptor
   FileDescriptorSm::Ptr fdSm = fhSm->fileDescriptorSm( fd );
   if( !fdSm ) {
      fdSm = fhSm->fileDescriptorSmIs(
         fd,
         Tac::FileDescriptor::FileDescriptorIs( "FileDescriptor" ),
         fhSm.ptr() );
      fdSm->fileDescriptor()->descriptorIs( fd );
      fdSm->fileDescriptor()->notifyOnReadableIs( false );
      fdSm->fileDescriptor()->notifyOnWritableIs( false );
      fdSm->fileDescriptor()->notifyOnExceptionIs( false );
   }
   return fdSm;
}

void
file_handler::read_interest_is(int fd, bool interest) {
   FileDescriptorSm::Ptr fdSm = get_file_descriptor_sm( this, fd );
   fdSm->fileDescriptor()->notifyOnReadableIs( interest );
   if( !interest ) {
      // If we aren't interested in anything about this file descriptor
      // anymore, cleanup the sm
      fdSm->fileHandlerSm()->maybeCleanupAfterFileDescriptor( fd );
   }
}

void
file_handler::write_interest_is(int fd, bool interest) {
   FileDescriptorSm::Ptr fdSm = get_file_descriptor_sm( this, fd );
   fdSm->fileDescriptor()->notifyOnWritableIs( interest );
   if( !interest ) {
      // If we aren't interested in anything about this file descriptor
      // anymore, cleanup the sm
      fdSm->fileHandlerSm()->maybeCleanupAfterFileDescriptor( fd );
   }
}

void
file_handler::exception_interest_is(int fd, bool interest) {
   FileDescriptorSm::Ptr fdSm = get_file_descriptor_sm( this, fd );
   fdSm->fileDescriptor()->notifyOnExceptionIs( interest );
   if( !interest ) {
      // If we aren't interested in anything about this file descriptor
      // anymore, cleanup the sm
      fdSm->fileHandlerSm()->maybeCleanupAfterFileDescriptor( fd );
   }
}

//
// FileDescriptorSm and FileHandlerSm method implementations
//

void
FileHandlerSm::maybeCleanupAfterFileDescriptor( int fd ) {
   FileDescriptorSm::Ptr fdSm = fileDescriptorSm( fd );
   // I'm guaranteed that the fdSm exists at this point (because
   // we called get_file_descriptor_sm earlier to get the sm,
   // which creates it if it doesn't exist), so this should be
   // an assert not a panic.
   assert( fdSm );
   if( !fdSm->fileDescriptor()->notifyOnReadable() &&
       !fdSm->fileDescriptor()->notifyOnWritable() &&
       !fdSm->fileDescriptor()->notifyOnException() ) {
      TRACE1("Cleaning up after fd " << fd);
      fileDescriptorSmDel( fd );
   }
}

void
FileDescriptorSm::handleReadable() {
   file_handler *fh = file_handler_sm_to_file_handler[ fileHandlerSm() ];
   assert( fh );

   fh->on_readable( fd() );
}

void
FileDescriptorSm::handleWritable() {
   file_handler *fh = file_handler_sm_to_file_handler[ fileHandlerSm() ];
   assert( fh );

   fh->on_writable( fd() );
}

void
FileDescriptorSm::handleExceptionPending() {
   file_handler *fh = file_handler_sm_to_file_handler[ fileHandlerSm() ];
   assert( fh );

   fh->on_exception( fd() );
}

}
