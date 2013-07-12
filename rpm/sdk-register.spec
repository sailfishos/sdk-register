Name: sdk-register
Version: 0.1
Release: 1
Summary: SDK SSU register utility
Group: Development/Tools
License: GPL v2
Source0: %{name}-%{version}.tar.gz
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: ssu-devel
BuildRequires: qt5-qmake

%description
%{summary}.

%files
%defattr(-,root,root,-)
%{_bindir}/sdk-register

%prep
%setup -q -n %{name}-%{version}

%build
%qmake5
make %{?_smp_mflags}


%install
%qmake5_install
