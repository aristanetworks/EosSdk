# Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

#-----------------------------------------------------------------------------------
# This Dockerfile can be used to build a docker image. 
# Docker containers of this image can be used to build EosSdk applications.
# The following build options are provided:
#       arch : Use 'm32' to build a 32-bit EosSdk application otherwise use 'm64'
#              to build a 64-bit EosSdk application.
#              Default value is set to 'm32'.
# Example:
# Steps to build an application using EosSdk docker container.
# 1) Build Docker image with tag as arista-eossdk:latest:
#    a) Docker image with a 32-bit libeos.so
#       "docker build -t arista-eossdk --build-arg arch=m32 ."
#       or "docker build -t arista-eossdk ."
#       
#    OR
#    b) Docker image with a 64-bit libeos.so
#       "docker build -t arista-eossdk --build-arg arch=m64 ."
#
# 2) Run Docker container:
#    docker run -v /home/sdk-app:/sdk-app --name <name> -it arista-eossdk bash
#    This will mount /home/sdk-app as sdk-app inside the container.
#    Place the application code and necessary dependencies in /home/sdk-app
#
# 3) Compile application binary:
#    Run the following command from /sdk-app.
#    For 32-bit binary: "g++ -m32 --std=gnu++0x -o <target> <source file> -leos"
#    For 64-bit binary: "g++ -m64 --std=gnu++0x -o <target> <source file> -leos"
#    The generated binary will also be available in /home/sdk-app on the host
#    machine.
#
#4) Load the application on Arista switch:
#    Further instructions to run the application on Arista switch can be found here:
#    https://github.com/aristanetworks/EosSdk/wiki/Quickstart%3A-Hello-World
#
# To learn more about EosSdk visit the following link.
# https://github.com/aristanetworks/EosSdk/wiki
#-----------------------------------------------------------------------------------

FROM centos:7
ARG version=2.22.2
ARG arch="m32"

# Set eossdk version as label and environ variable.
LABEL version=$version
ENV EOS_SDK_VERSION=$version

# Install necessary utilities.
RUN \
   yum -y install which \
   && yum -y install file \
   && yum -y install make \
   && yum -y install automake \
   && yum -y install vim \
   && yum -y install wget \
   && yum -y install patch \
   && yum -y install libtool \
   && yum -y install diffutils \
   && yum -y install swig3 \
   && yum -y install python-devel \
   && yum -y install python3-devel

WORKDIR /usr/src/EosSdk-stubs-$version
ADD ./ ./

# Download cross-compiler.
RUN \
 wget -O /tmp/arista-cross-compiler.rpm \
 https://github.com/aristanetworks/EosSdk-cross-compiler/releases/download/v4.25.0/arista-centos7.5-gcc8.4.0-glibc2.17-1.0-0.i686.rpm

# Install the cross compiler.
RUN yum -y install /tmp/arista-cross-compiler.rpm

ENV PATH=/opt/arista/centos7.5-gcc8.4.0-glibc2.17/bin:$PATH

RUN test -f Makefile && rm -f Makefile
RUN test -f configure && rm -f configure
# Build EosSdk stubs.
RUN ./build.sh --$arch
RUN make install

# Delete the cross compiler rpm.
RUN rm -f /tmp/arista-cross-compiler.rpm
