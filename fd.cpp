// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/fd.h>
#include <EosSdk/panic.h>
#include <FileSm.h>
#include <map>
#include <Tac/Tracing.h>

DEFAULT_TRACE_HANDLE( "EosSdkFile" )

namespace eos {

static std::map< fd_handler *, FileHandlerSm::Ptr >
fd_handler_to_fd_handler_sm;

static std::map< FileHandlerSm *, fd_handler * >
fd_handler_sm_to_fd_handler;

fd_handler::fd_handler() {
   FileHandlerSm::Ptr fileHandlerSm = FileHandlerSm::FileHandlerSmIs();
   fd_handler_sm_to_fd_handler[ fileHandlerSm.ptr() ] = this;
   fd_handler_to_fd_handler_sm[ this ] = fileHandlerSm;
}

fd_handler::~fd_handler() {
   FileHandlerSm::Ptr fileHandlerSm = fd_handler_to_fd_handler_sm[ this ];
   fd_handler_sm_to_fd_handler.erase( fileHandlerSm.ptr() );
   fd_handler_to_fd_handler_sm.erase( this );
}

FileDescriptorSm::Ptr
get_fd_sm( fd_handler *fd_handler, int fd ) {
   FileHandlerSm::Ptr fhSm = fd_handler_to_fd_handler_sm[ fd_handler ];
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
fd_handler::watch_readable(int fd, bool interest) {
   FileDescriptorSm::Ptr fdSm = get_fd_sm( this, fd );
   fdSm->fileDescriptor()->notifyOnReadableIs( interest );
   if( !interest ) {
      // If we aren't interested in anything about this file descriptor
      // anymore, cleanup the sm
      fdSm->fileHandlerSm()->maybeCleanupAfterFileDescriptor( fd );
   }
}

void
fd_handler::watch_writable(int fd, bool interest) {
   FileDescriptorSm::Ptr fdSm = get_fd_sm( this, fd );
   fdSm->fileDescriptor()->notifyOnWritableIs( interest );
   if( !interest ) {
      // If we aren't interested in anything about this file descriptor
      // anymore, cleanup the sm
      fdSm->fileHandlerSm()->maybeCleanupAfterFileDescriptor( fd );
   }
}

void
fd_handler::watch_exception(int fd, bool interest) {
   FileDescriptorSm::Ptr fdSm = get_fd_sm( this, fd );
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
   // we called get_fd_sm earlier to get the sm,
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
   fd_handler *fh = fd_handler_sm_to_fd_handler[ fileHandlerSm() ];
   assert( fh );

   fh->on_readable( fd() );
}

void
FileDescriptorSm::handleWritable() {
   fd_handler *fh = fd_handler_sm_to_fd_handler[ fileHandlerSm() ];
   assert( fh );

   fh->on_writable( fd() );
}

void
FileDescriptorSm::handleExceptionPending() {
   fd_handler *fh = fd_handler_sm_to_fd_handler[ fileHandlerSm() ];
   assert( fh );

   fh->on_exception( fd() );
}

}
