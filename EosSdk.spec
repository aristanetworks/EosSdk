Summary: EOS Software Development Kit
Name: EosSdk
Version: 1.0.1
Release: %{?release:%{release}}%{!?release:eng}
Source0: %{name}-%{version}.tar.gz
License: Arista Networks
Group: dev/Arista Networks
BuildRoot: %{_tmppath}/%{name}-root
Url: http://www.AristaNetworks.com
Requires: libtac
Requires: Agent
Requires: Ark
Requires: Arnet
Requires: EthIntf
Requires: Intf
Requires: Lag
Requires: Ira
BuildRequires: tacc
BuildRequires: Agent-devel
BuildRequires: Ark-devel
BuildRequires: Arnet-devel
BuildRequires: EthIntf-devel
BuildRequires: Intf-devel
BuildRequires: Lag-devel
BuildRequires: Ira-devel

# NOTE: Please do NOT put the names of macros into any comments in this
#       file, or you will find yourself wading through very baffling RPM
#       error messages.

%description
The EOS Software Development Kit provides a set of stable C++ interfaces for
high-performance access to EOS primitives, for on-box programming beyond what
can be done with Python.

%package headers
Summary: Public development headers for the EOS SDK
Group: dev/Arista Networks
Requires: EosSdk = %{version}
Obsoletes: eos-sdk

%description headers
Provides the files necessary for development with the EOS Software Development Kit.

%package devel
Summary: EosSdk internal devel package
Group: dev/Arista Networks
Requires: EosSdk-headers
Requires: EosSdk

%description devel
Provides the files necessary for EosSdk package development (internal to Arista).

%package test
Summary: EosSdk test package
Group: dev/Arista Networks
Requires: EosSdk
Requires: EosSdk-devel

%description test
Provides the test libraries that are internal to Arista and not needed to use the SDK.

%prep
%setup -q

%build
%configure
%{__make} %{?_smp_mflags} all

%install
rm -rf "$RPM_BUILD_ROOT"
make "DESTDIR=$RPM_BUILD_ROOT" install
rm -f "$RPM_BUILD_ROOT"%{_libdir}/*.la
# Please do not change this section.

%clean

%files
%defattr(-,root,root)
%{_libdir}/libeos.so*
%{_libdir}/tacc/map.d/EosSdk.map

%files headers
%defattr(-,root,root)
%{_includedir}/eos

%files devel
%defattr(-,root,root)
%{_bindir}/eossdkpublish
%{python_sitelib}/EosSdkTestLib.py*
%{_includedir}/EosSdk

%files test
%defattr(-,root,root)
%{_bindir}/EchoBot
%{_bindir}/EthAddrTest
%{_bindir}/EthIntfTestAgent
%{_bindir}/IntfIdTest
%{_bindir}/IntfTestAgent
