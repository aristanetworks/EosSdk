Summary: EOS Software Development Kit
Name: EosSdk
Version: 1.0.0
Release: %{?release:%{release}}%{!?release:eng}
Source0: %{name}-%{version}.tar.gz
License: Arista Networks
Group: dev/Arista Networks
BuildRoot: %{_tmppath}/%{name}-root
Url: http://www.AristaNetworks.com
Requires: libtac
Requires: Agent
Requires: Arnet
Requires: EthIntf
Requires: Intf
BuildRequires: tacc
BuildRequires: Agent-devel
BuildRequires: Ark-devel
BuildRequires: Arnet-devel
BuildRequires: EthIntf-devel
BuildRequires: Intf-devel

# NOTE: Please do NOT put the names of macros into any comments in this
#       file, or you will find yourself wading through very baffling RPM
#       error messages.

%description
The EOS Software Development Kit provides a set of stable C++ interfaces for
high-performance access to EOS primitives, for on-box programming beyond what
can be done with Python.

%package devel
Summary: EosSdk devel package
Group: dev/Arista Networks
Requires: EosSdk

%description devel
Provides the files necessary development with the EOS Software Development Kit.

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
%{_bindir}/EosSdk
%{_libdir}/libEosSdk*.so*
%{_libdir}/tacc/map.d/EosSdk.map

%files devel
%defattr(-,root,root)
%{_includedir}/EosSdk
