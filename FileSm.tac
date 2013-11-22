// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("Tac::FileDescriptor");

eos : Tac::Namespace {

FileHandlerSm : Tac::Type : Tac::PtrInterface;

FileDescriptorSm : Tac::Type(fd, fileDescriptor, fileHandlerSm) : Tac::Constrainer {
   tacFwkActivity = 0;

   fd : int;
   fileDescriptor : inout Tac::FileDescriptor::Ptr;
   fileHandlerSm : FileHandlerSm::RawPtr;

   handleReadable : extern invasive void();
   fileDescriptor::readableCount => handleReadable();

   handleWritable : extern invasive void();
   fileDescriptor::writableCount => handleWritable();

   handleExceptionPending : extern invasive void();
   fileDescriptor::exceptionPendingCount => handleExceptionPending();
   
}

FileHandlerSm : Tac::Type() : Tac::PtrInterface {
   fileDescriptorSm : FileDescriptorSm[ fd ];

   maybeCleanupAfterFileDescriptor : extern invasive void( fd : int );
}

}
