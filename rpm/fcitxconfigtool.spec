%global _xinputconf %{_sysconfdir}/X11/xinit/xinput.d/fcitx.conf
%{!?gtk2_binary_version: %global gtk2_binary_version %(pkg-config  --variable=gtk_binary_version gtk+-2.0)}
%{!?gtk3_binary_version: %global gtk3_binary_version %(pkg-config  --variable=gtk_binary_version gtk+-3.0)}

Name:			deepin-fcitxconfigtool-plugin
Summary:		An input method framework
Version:		0.1.17	
Release:		1%{?dist}
License:		GPLv2+
URL:			https://fcitx-im.org/wiki/Fcitx
Source0:		%{name}_%{version}.tar.xz
BuildRequires:		gcc-c++
BuildRequires:		pango-devel, dbus-devel
%if 0%{?rhel} < 8
%else
%ifarch aarch64 s390x
%else
BuildRequires:		enchant-devel
%endif
%endif
BuildRequires:		wget, intltool, chrpath
BuildRequires:		cmake, libtool, doxygen, libicu-devel
BuildRequires:		gtk3-devel, gtk2-devel, libicu
BuildRequires:		xorg-x11-proto-devel, xorg-x11-xtrans-devel
BuildRequires:		gobject-introspection-devel, libxkbfile-devel
BuildRequires:		iso-codes-devel, libicu-devel
BuildRequires:		libX11-devel, dbus-glib-devel, dbus-x11
BuildRequires:		desktop-file-utils, libxml2-devel
BuildRequires:		lua-devel, extra-cmake-modules
BuildRequires:		xkeyboard-config-devel
BuildRequires:		libuuid-devel
BuildRequires:		json-c-devel
Requires:		%{name}-data = %{version}-%{release}
Requires:		imsettings
Requires(post):		%{_sbindir}/alternatives
Requires(postun):	%{_sbindir}/alternatives
Requires:		%{name}-libs%{?_isa} = %{version}-%{release}
Requires:		%{name}-gtk3 = %{version}-%{release}
Requires:		%{name}-gtk2 = %{version}-%{release}

%description
Fcitx is an input method framework with extension support. Currently it
supports Linux and Unix systems like FreeBSD.

Fcitx tries to provide a native feeling under all desktop as well as a light
weight core. You can easily customize it to fit your requirements.

%package data
Summary:		Data files of Fcitx
BuildArch:		noarch
Requires:		hicolor-icon-theme
Requires:		dbus

%description data
The %{name}-data package provides shared data for Fcitx.

%package libs
Summary:		Shared libraries for Fcitx
Provides:		%{name}-keyboard = %{version}-%{release}
Obsoletes:		%{name}-keyboard =< 4.2.3

%description libs
The %{name}-libs package provides shared libraries for Fcitx

%package devel
Summary:		Development files for Fcitx
Requires:		%{name}-libs%{?_isa} = %{version}-%{release}
Requires:		libX11-devel%{?_isa}

%description devel
The %{name}-devel package contains libraries and header files necessary for
developing programs using Fcitx libraries.

%package table-chinese
Summary:		Chinese table of Fcitx
BuildArch:		noarch
Requires:		%{name}-table = %{version}-%{release}

%description table-chinese
The %{name}-table-chinese package provides other Chinese table for Fcitx.

%package gtk2
Summary:		Fcitx IM module for gtk2
Requires:		%{name} = %{version}-%{release}
Requires:		%{name}-libs%{?_isa} = %{version}-%{release}

%description gtk2
This package contains Fcitx IM module for gtk2.

%package gtk3
Summary:		Fcitx IM module for gtk3
Requires:		%{name} = %{version}-%{release}
Requires:		%{name}-libs%{?_isa} = %{version}-%{release}
Requires:		imsettings-gnome

%description gtk3
This package contains Fcitx IM module for gtk3.

%if 0%{?rhel} < 8

%endif

%package pinyin
Summary:		Pinyin Engine for Fcitx
URL:			https://fcitx-im.org/wiki/Built-in_Pinyin
Requires:		%{name} = %{version}-%{release}
Requires:		%{name}-libs%{?_isa} = %{version}-%{release}
Requires:		%{name}-data = %{version}-%{release}

%description pinyin
This package contains pinyin engine for Fcitx.

%package qw
Summary:		Quwei Engine for Fcitx
URL:			https://fcitx-im.org/wiki/QuWei
Requires:		%{name} = %{version}-%{release}
Requires:		%{name}-libs%{?_isa} = %{version}-%{release}
Requires:		%{name}-data = %{version}-%{release}

%description qw
This package contains Quwei engine for Fcitx.

%package table
Summary:		Table Engine for Fcitx
URL:			https://fcitx-im.org/wiki/Table
Requires:		%{name} = %{version}-%{release}
Requires:		%{name}-libs%{?_isa} = %{version}-%{release}
Requires:		%{name}-data = %{version}-%{release}
Requires:		%{name}-pinyin = %{version}-%{release}

%description table
This package contains table engine for Fcitx.

%prep

cat > %{_sourcedir}/xinput_fcitx <<EOF
XIM=fcitx
XIM_PROGRAM=/usr/bin/fcitx
ICON="/usr/share/pixmaps/fcitx.png"
XIM_ARGS="-D"
PREFERENCE_PROGRAM=/usr/bin/fcitx-configtool
SHORT_DESC="FCITX"
GTK_IM_MODULE=fcitx
if test -f /usr/lib/qt4/plugins/inputmethods/qtim-fcitx.so || \
   test -f /usr/lib64/qt4/plugins/inputmethods/qtim-fcitx.so || \
   test -f /usr/lib/qt5/plugins/platforminputcontexts/libfcitxplatforminputcontextplugin.so || \
   test -f /usr/lib64/qt5/plugins/platforminputcontexts/libfcitxplatforminputcontextplugin.so;
then
    QT_IM_MODULE=fcitx
else
    QT_IM_MODULE=xim
fi
EOF

%setup -q

%build
mkdir -p build
pushd build
cmake .. -DENABLE_GTK3_IM_MODULE=On -DENABLE_QT_IM_MODULE=On -DENABLE_QT=Off -DENABLE_OPENCC=Off -DENABLE_ENCHANT=Off -DENABLE_LUA=On -DENABLE_GIR=On  -DENABLE_XDGAUTOSTART=Off -DCMAKE_INSTALL_PREFIX:PATH=/usr  && make VERBOSE=1 %{?_smp_mflags}
%install
%make_install INSTALL="install -p" -C build
install -pm 644 -D %{_sourcedir}/xinput_fcitx %{buildroot}%{_xinputconf}

%post 
%{_sbindir}/alternatives --install %{_sysconfdir}/X11/xinit/xinputrc xinputrc %{_xinputconf} 55 || :

%postun  
if [ "$1" = "0" ]; then
  %{_sbindir}/alternatives --remove xinputrc %{_xinputconf} || :
  # if alternative was set to manual, reset to auto
  [ -L %{_sysconfdir}/alternatives/xinputrc -a "`readlink %{_sysconfdir}/alternatives/xinputrc`" = "%{_xinputconf}" ] && %{_sbindir}/alternatives --auto xinputrc || :
fi

%ldconfig_scriptlets libs

#%%files -f %%{name}.lang
%doc AUTHORS ChangeLog THANKS TODO
%config %{_xinputconf}

%files 
%{_exec_prefix}/*
/lib/*

%exclude %{_sysconfdir}/*

%if 0%{?rhel} < 8
%endif

