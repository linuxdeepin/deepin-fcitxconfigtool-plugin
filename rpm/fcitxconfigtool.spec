%global _xinputconf %{_sysconfdir}/X11/xinit/xinput.d/fcitx.conf
%{!?gtk2_binary_version: %global gtk2_binary_version %(pkg-config  --variable=gtk_binary_version gtk+-2.0)}
%{!?gtk3_binary_version: %global gtk3_binary_version %(pkg-config  --variable=gtk_binary_version gtk+-3.0)}

Name:			deepin-fcitxconfigtool-plugin
Summary:		An input method framework
Version:		0.1.17
Release:		1%{?dist}
License:		GPLv2+
URL:			https://fcitx-im.org/wiki/Fcitx
Source0:		%{name}-%{version}.tar.xz
BuildRequires:		gcc-c++
BuildRequires:		pango-devel, dbus-devel
%if 0%{?rhel} < 8
%else
%ifarch aarch64 s390x
%else
BuildRequires:		enchant-devel
%endif
%endif
BuildRequires:		qt5-qmake,libqt5widgets5,
BuildRequires:		libqt5network5, libdtkwidget-dev,
BuildRequires:		libdtkgui-dev, libdtkgui5,
BuildRequires:		libdtkgui5-bin, libdtkcore5-bin,
BuildRequires:		libdtkcore-dev, qttools5-dev,
BuildRequires:		qttools5-dev-tools, pkg-config,
BuildRequires:		cmake, debhelper
BuildRequires:		fcitx-bin, fcitx-libs-dev
BuildRequires:		libfcitx-qt5-1, libfcitx-qt5-data,
BuildRequires:		libfcitx-qt5-dev, iso-codes,  libdbus-glib-1-dev,
BuildRequires:		libgtk-3-dev, libgtk2.0-dev
BuildRequires:		libunique-dev, libdframeworkdbus-dev,
BuildRequires:		libgtest-dev, libgmock-dev, dde-control-center-dev,

%description
Fcitx is an input method framework with extension support. Currently it
supports Linux and Unix systems like FreeBSD.

Fcitx tries to provide a native feeling under all desktop as well as a light
weight core. You can easily customize it to fit your requirements.

%package data
Summary:		fcitx-config-tools and multilanguages translations
BuildArch:		noarch
Requires:	 	fcitx

%description data
The %{name} package provides fcitx-config-tools and multilanguages translations

%prep

%setup -q

%build
mkdir -p build
pushd build
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/usr  && make VERBOSE=1 %{?_smp_mflags}
%install
%make_install INSTALL="install -p" -C build

%post 

%postun  

%files 
%doc README.md
%license
%{_exec_prefix}/*
/lib/*

%exclude %{_sysconfdir}/*

