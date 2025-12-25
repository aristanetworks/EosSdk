# Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

#-----------------------------------------------------------------------------------
# This Dockerfile can be used to build a docker image that can then be used to create
# a docker container that will be able to compile EosSdk applications in exactly the
# same way as EOS native applications are compiled (and thus binary compatible with
# EOS libraries).
#
# 1) Build Docker image (we will call it 'arista-eossdk')
#  docker build . -f <this Dockerfile> -t arista-eossdk
#
# 2) Create container: (assuming application code to be compiled is at /code on the
#    host machine that starts the container)
#  docker run -v /code:/code -itd --name arista-eossdk-c1 arista-eossdk
#
# 3) Go into the container and build the application
#  docker exec -it arista-eossdk-c1 /bin/bash
#  cd /code
#  g++      -std=gnu++20 -o /code/build/HelloWorld.o -c /code/HelloWorld.cpp
#  g++      -std=gnu++20 -o /code/build/HelloWorld      /code/HelloWorld.o  -leos -lrt
#  g++ -m32 -std=gnu++20 -o /code/build/HelloWorld.o -c /code/HelloWorld.cpp
#  g++ -m32 -std=gnu++20 -o /code/build/HelloWorld32    /code/HelloWorld.o  -leos -lrt
#
# 4) Load the application (in /code/build on your host) onto an Arista switch
#    Further instructions to run the application on Arista switch can be found here:
#    https://github.com/aristanetworks/EosSdk/wiki/Quickstart%3A-Hello-World
#
# 5) Cleanup
#    docker rm arista-eossdk-c1
#    docker rmi arista-eossdk
#
# To learn more about EosSdk visit the following link.
# https://github.com/aristanetworks/EosSdk/wiki
#-----------------------------------------------------------------------------------

FROM almalinux:9
ARG version=2.23.5

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
   && yum -y install diffutils

# Download cross-compiler.
RUN wget -O /tmp/arista-cross-compiler.rpm \
       https://github.com/aristanetworks/EosSdk-cross-compiler/releases/download/v4.32.0/arista-gcc11.i686.rpm

# Install the cross compiler.
RUN rpm --force --nodeps -Uvh /tmp/arista-cross-compiler.rpm

# Delete the cross compiler rpm.
RUN rm -f /tmp/arista-cross-compiler.rpm

ENV PATH=/opt/arista/gcc11/bin:$PATH

# Download the EosSdk stubs
RUN wget -O /tmp/stubs.tar.gz \
       https://github.com/aristanetworks/EosSdk/archive/refs/tags/v$version.tar.gz

# Build EosSdk stubs and install libeos and headerfiles for both m32 and m64
RUN cd /tmp; tar -xzf stubs.tar.gz; cd EosSdk-* ;\
    ./build.sh -m32 >& ../build32.log           ;\
    make install >& ../install32.log            ;\
    rm -rf /tmp/EosSdk-*                        ;\
    cd /tmp; tar -xzf stubs.tar.gz; cd EosSdk-* ;\
    ./build.sh -m64 >& ../build64.log           ;\
    make install >& ../install64.log            ;\
    cd ..                                       ;\
    rm -rf /tmp/EosSdk-*                        ;\
    rm stubs.tar.gz
