# Arista's EOS SDK

![EOS SDK logo](http://i.imgur.com/fNQ07mr.png)

The EOS Software Development Kit (EOS SDK) lets you program native,
high-performance apps that run on your Arista switch. These apps, or
"agents," harness the full power of EOS, including event-driven,
asynchronous behavior, high availability, and complete access to both
Linux and EOS's APIs.

This package provides a self-contained implementation of stubs for the EOS
SDK.  The stubs mock how the real EOS SDK behaves on a real switch, to a
certain extent.  They are useful to build and test software in your favorite
Linux environment, with your preferred build tools.


## Documentation
Documentation is hosted on this project's [wiki](https://github.com/aristanetworks/EosSdk/wiki). It includes a [quickstart guide](https://github.com/aristanetworks/EosSdk/wiki/Quickstart%3A-Hello-World), [build](https://github.com/aristanetworks/EosSdk/wiki/Build-and-Development-Environment) and [install](https://github.com/aristanetworks/EosSdk/wiki/Downloading-and-Installing-the-SDK) instructions, along with an [EOS overview](https://github.com/aristanetworks/EosSdk/wiki/Understanding-EOS-and-Sysdb) and high-level [SDK usage](https://github.com/aristanetworks/EosSdk/wiki/Using-the-SDK) information.

Detailed, per-release API Documentation is also available via the
release page.

## Releases

Releases are available via the [GitHub release
page](https://github.com/aristanetworks/EosSdk/releases). From that
page you can download specific tarballs for a given release so you can
build your agent. The corresponding EosSdk RPMs (that provide the
functionality for interacting with Arista devices) for a given EOS SDK
release is available via the [Arista download
page](https://www.arista.com/en/support/software-download) on a
per-EOS-release basis.

## Exploring the code

The directory structure is as follows: `eos/` contains the headers
that define the APIs you'll be using. In this directory, each `.h`
file is a module that provides access to a specific subset of EOS's
functionality. Most modules also have a companion file in
`eos/types/<module_name>.h`. This file defines the various value types
used by the module.

For a variety of `C++` and `Python` examples, see the `examples/`
directory. The stub `.cpp` files at the top level directory can be
ignored or extended to provide mock functionality, as you'd like.


