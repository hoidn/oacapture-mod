# Makefile.in generated by automake 1.15 from Makefile.am.
# liboacam/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994-2014 Free Software Foundation, Inc.

# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



#
# Makefile.am -- liboacam Makefile template
#
# Copyright 2013,2014,2015,2016 James Fidell (james@openastroproject.org)
#
# License:
#
# This file is part of the Open Astro Project.
#
# The Open Astro Project is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# The Open Astro Project is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with the Open Astro Project.  If not, see
# <http://www.gnu.org/licenses/>.
#


am__is_gnu_make = { \
  if test -z '$(MAKELEVEL)'; then \
    false; \
  elif test -n '$(MAKE_HOST)'; then \
    true; \
  elif test -n '$(MAKE_VERSION)' && test -n '$(CURDIR)'; then \
    true; \
  else \
    false; \
  fi; \
}
am__make_running_with_option = \
  case $${target_option-} in \
      ?) ;; \
      *) echo "am__make_running_with_option: internal error: invalid" \
              "target option '$${target_option-}' specified" >&2; \
         exit 1;; \
  esac; \
  has_opt=no; \
  sane_makeflags=$$MAKEFLAGS; \
  if $(am__is_gnu_make); then \
    sane_makeflags=$$MFLAGS; \
  else \
    case $$MAKEFLAGS in \
      *\\[\ \	]*) \
        bs=\\; \
        sane_makeflags=`printf '%s\n' "$$MAKEFLAGS" \
          | sed "s/$$bs$$bs[$$bs $$bs	]*//g"`;; \
    esac; \
  fi; \
  skip_next=no; \
  strip_trailopt () \
  { \
    flg=`printf '%s\n' "$$flg" | sed "s/$$1.*$$//"`; \
  }; \
  for flg in $$sane_makeflags; do \
    test $$skip_next = yes && { skip_next=no; continue; }; \
    case $$flg in \
      *=*|--*) continue;; \
        -*I) strip_trailopt 'I'; skip_next=yes;; \
      -*I?*) strip_trailopt 'I';; \
        -*O) strip_trailopt 'O'; skip_next=yes;; \
      -*O?*) strip_trailopt 'O';; \
        -*l) strip_trailopt 'l'; skip_next=yes;; \
      -*l?*) strip_trailopt 'l';; \
      -[dEDm]) skip_next=yes;; \
      -[JT]) skip_next=yes;; \
    esac; \
    case $$flg in \
      *$$target_option*) has_opt=yes; break;; \
    esac; \
  done; \
  test $$has_opt = yes
am__make_dryrun = (target_option=n; $(am__make_running_with_option))
am__make_keepgoing = (target_option=k; $(am__make_running_with_option))
pkgdatadir = $(datadir)/openastro
pkgincludedir = $(includedir)/openastro
pkglibdir = $(libdir)/openastro
pkglibexecdir = $(libexecdir)/openastro
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-unknown-linux-gnu
host_triplet = x86_64-unknown-linux-gnu
subdir = liboacam
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/m4/libtool.m4 \
	$(top_srcdir)/m4/ltoptions.m4 $(top_srcdir)/m4/ltsugar.m4 \
	$(top_srcdir)/m4/ltversion.m4 $(top_srcdir)/m4/lt~obsolete.m4 \
	$(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
DIST_COMMON = $(srcdir)/Makefile.am $(am__DIST_COMMON)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__vpath_adj_setup = srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`;
am__vpath_adj = case $$p in \
    $(srcdir)/*) f=`echo "$$p" | sed "s|^$$srcdirstrip/||"`;; \
    *) f=$$p;; \
  esac;
am__strip_dir = f=`echo $$p | sed -e 's|^.*/||'`;
am__install_max = 40
am__nobase_strip_setup = \
  srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*|]/\\\\&/g'`
am__nobase_strip = \
  for p in $$list; do echo "$$p"; done | sed -e "s|$$srcdirstrip/||"
am__nobase_list = $(am__nobase_strip_setup); \
  for p in $$list; do echo "$$p $$p"; done | \
  sed "s| $$srcdirstrip/| |;"' / .*\//!s/ .*/ ./; s,\( .*\)/[^/]*$$,\1,' | \
  $(AWK) 'BEGIN { files["."] = "" } { files[$$2] = files[$$2] " " $$1; \
    if (++n[$$2] == $(am__install_max)) \
      { print $$2, files[$$2]; n[$$2] = 0; files[$$2] = "" } } \
    END { for (dir in files) print dir, files[dir] }'
am__base_list = \
  sed '$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;s/\n/ /g' | \
  sed '$$!N;$$!N;$$!N;$$!N;s/\n/ /g'
am__uninstall_files_from_dir = { \
  test -z "$$files" \
    || { test ! -d "$$dir" && test ! -f "$$dir" && test ! -r "$$dir"; } \
    || { echo " ( cd '$$dir' && rm -f" $$files ")"; \
         $(am__cd) "$$dir" && rm -f $$files; }; \
  }
am__installdirs = "$(DESTDIR)$(libdir)"
LTLIBRARIES = $(lib_LTLIBRARIES)
liboacam_la_LIBADD =
am__liboacam_la_SOURCES_DIST = control.c debug.c oacam.c \
	unimplemented.c utils.c V4L2oacam.c V4L2connect.c V4L2ioctl.c \
	V4L2cameras.c V4L2getState.c V4L2controller.c V4L2callback.c \
	V4L2control.c ZWASIoacam.c ZWASIconnect.c ZWASIcontroller.c \
	ZWASIcallback.c ZWASIcontrol.c ZWASIgetState.c ZWASIroi.c \
	ZWASI2oacam.c ZWASI2connect.c ZWASI2controller.c \
	ZWASI2getState.c ZWASI2control.c UVCoacam.c UVCconnect.c \
	UVCgetState.c UVCcontrol.c UVCcontroller.c UVCcallback.c \
	IIDCoacam.c IIDCconnect.c IIDCgetState.c IIDCcontrol.c \
	IIDCcontroller.c IIDCcallback.c atikSerialgetState.c \
	atikSerialcallback.c atikSerialcontrol.c \
	atikSerialcontroller.c atikSerialoacam-udev.c \
	atikSerialconnect-udev.c atikSerialIO-udev.c \
	atikSerialoacam-ftdi.c atikSerialconnect-ftdi.c \
	atikSerialIO-ftdi.c PGEoacam.c PGEconnect.c PGEgetState.c \
	PGEcontrol.c PGEcontroller.c PGEcallback.c PGEroi.c \
	Touptekoacam.c Touptekconnect.c Touptekcallback.c \
	Touptekcontrol.c Touptekcontroller.c TouptekgetState.c \
	Touptekroi.c Mallincamoacam.c Mallincamconnect.c \
	Mallincamcallback.c Mallincamcontrol.c Mallincamcontroller.c \
	MallincamgetState.c Mallincamroi.c Altairoacam.c \
	Altairconnect.c Altaircallback.c Altaircontrol.c \
	Altaircontroller.c AltairgetState.c Altairroi.c PWCgetState.c \
	PWCconnect.c PWCoacam.c QHYoacam.c QHYconnect.c QHYfirmware.c \
	QHYcontrol.c QHYcallback.c QHYgetState.c QHYusb.c QHY5.c \
	QHY5controller.c QHY5II.c QHY5IIcontroller.c QHY5LII.c \
	QHY5LIIcontroller.c QHY6.c QHY6controller.c SXoacam.c \
	SXconnect.c SXcallback.c SXcontroller.c SXcontrol.c \
	SXgetState.c EUVCoacam.c EUVCconnect.c EUVCcontrol.c \
	EUVCcallback.c EUVCgetState.c EUVCcontroller.c EUVCusb.c \
	EUVCroi.c
#am__objects_1 = V4L2oacam.lo V4L2connect.lo \
#	V4L2ioctl.lo V4L2cameras.lo V4L2getState.lo \
#	V4L2controller.lo V4L2callback.lo \
#	V4L2control.lo
am__objects_2 = ZWASIoacam.lo ZWASIconnect.lo \
	ZWASIcontroller.lo ZWASIcallback.lo \
	ZWASIcontrol.lo ZWASIgetState.lo ZWASIroi.lo
am__objects_3 = ZWASI2oacam.lo ZWASI2connect.lo \
	ZWASI2controller.lo ZWASI2getState.lo \
	ZWASI2control.lo
am__objects_4 = UVCoacam.lo UVCconnect.lo \
	UVCgetState.lo UVCcontrol.lo \
	UVCcontroller.lo UVCcallback.lo
am__objects_5 = IIDCoacam.lo IIDCconnect.lo \
	IIDCgetState.lo IIDCcontrol.lo \
	IIDCcontroller.lo IIDCcallback.lo
am__objects_6 =  \
	atikSerialgetState.lo \
	atikSerialcallback.lo \
	atikSerialcontrol.lo \
	atikSerialcontroller.lo
#am__objects_6 = atikSerialgetState.lo \
#	atikSerialcallback.lo atikSerialcontrol.lo \
#	atikSerialcontroller.lo
am__objects_7 = atikSerialoacam-udev.lo \
	atikSerialconnect-udev.lo \
	atikSerialIO-udev.lo
#am__objects_8 = atikSerialoacam-ftdi.lo \
#	atikSerialconnect-ftdi.lo \
#	atikSerialIO-ftdi.lo
#am__objects_9 = PGEoacam.lo PGEconnect.lo \
#	PGEgetState.lo PGEcontrol.lo \
#	PGEcontroller.lo PGEcallback.lo \
#	PGEroi.lo
#am__objects_10 = Touptekoacam.lo \
#	Touptekconnect.lo Touptekcallback.lo \
#	Touptekcontrol.lo Touptekcontroller.lo \
#	TouptekgetState.lo Touptekroi.lo
#am__objects_11 = Mallincamoacam.lo \
#	Mallincamconnect.lo \
#	Mallincamcallback.lo \
#	Mallincamcontrol.lo \
#	Mallincamcontroller.lo \
#	MallincamgetState.lo Mallincamroi.lo
#am__objects_12 = Altairoacam.lo \
#	Altairconnect.lo Altaircallback.lo \
#	Altaircontrol.lo Altaircontroller.lo \
#	AltairgetState.lo Altairroi.lo
am_liboacam_la_OBJECTS = control.lo debug.lo oacam.lo unimplemented.lo \
	utils.lo $(am__objects_1) $(am__objects_2) $(am__objects_3) \
	$(am__objects_4) $(am__objects_5) $(am__objects_6) \
	$(am__objects_7) $(am__objects_8) $(am__objects_9) \
	$(am__objects_10) $(am__objects_11) $(am__objects_12) \
	PWCgetState.lo PWCconnect.lo PWCoacam.lo QHYoacam.lo \
	QHYconnect.lo QHYfirmware.lo QHYcontrol.lo QHYcallback.lo \
	QHYgetState.lo QHYusb.lo QHY5.lo QHY5controller.lo QHY5II.lo \
	QHY5IIcontroller.lo QHY5LII.lo QHY5LIIcontroller.lo QHY6.lo \
	QHY6controller.lo SXoacam.lo SXconnect.lo SXcallback.lo \
	SXcontroller.lo SXcontrol.lo SXgetState.lo EUVCoacam.lo \
	EUVCconnect.lo EUVCcontrol.lo EUVCcallback.lo EUVCgetState.lo \
	EUVCcontroller.lo EUVCusb.lo EUVCroi.lo
liboacam_la_OBJECTS = $(am_liboacam_la_OBJECTS)
AM_V_lt = $(am__v_lt_$(V))
am__v_lt_ = $(am__v_lt_$(AM_DEFAULT_VERBOSITY))
am__v_lt_0 = --silent
am__v_lt_1 = 
AM_V_P = $(am__v_P_$(V))
am__v_P_ = $(am__v_P_$(AM_DEFAULT_VERBOSITY))
am__v_P_0 = false
am__v_P_1 = :
AM_V_GEN = $(am__v_GEN_$(V))
am__v_GEN_ = $(am__v_GEN_$(AM_DEFAULT_VERBOSITY))
am__v_GEN_0 = @echo "  GEN     " $@;
am__v_GEN_1 = 
AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_VERBOSITY))
am__v_at_0 = @
am__v_at_1 = 
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=compile $(CC) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CFLAGS) $(CFLAGS)
AM_V_CC = $(am__v_CC_$(V))
am__v_CC_ = $(am__v_CC_$(AM_DEFAULT_VERBOSITY))
am__v_CC_0 = @echo "  CC      " $@;
am__v_CC_1 = 
CCLD = $(CC)
LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CCLD = $(am__v_CCLD_$(V))
am__v_CCLD_ = $(am__v_CCLD_$(AM_DEFAULT_VERBOSITY))
am__v_CCLD_0 = @echo "  CCLD    " $@;
am__v_CCLD_1 = 
SOURCES = $(liboacam_la_SOURCES)
DIST_SOURCES = $(am__liboacam_la_SOURCES_DIST)
am__can_run_installinfo = \
  case $$AM_UPDATE_INFO_DIR in \
    n|no|NO) false;; \
    *) (install-info --version) >/dev/null 2>&1;; \
  esac
am__tagged_files = $(HEADERS) $(SOURCES) $(TAGS_FILES) $(LISP)
# Read a list of newline-separated strings from the standard input,
# and print each of them once, without duplicates.  Input order is
# *not* preserved.
am__uniquify_input = $(AWK) '\
  BEGIN { nonempty = 0; } \
  { items[$$0] = 1; nonempty = 1; } \
  END { if (nonempty) { for (i in items) print i; }; } \
'
# Make sure the list of sources is unique.  This is necessary because,
# e.g., the same source file might be shared among _SOURCES variables
# for different programs/libraries.
am__define_uniq_tagged_files = \
  list='$(am__tagged_files)'; \
  unique=`for i in $$list; do \
    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
  done | $(am__uniquify_input)`
ETAGS = etags
CTAGS = ctags
am__DIST_COMMON = $(srcdir)/Makefile.in $(top_srcdir)/depcomp
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} /home/oliver/dev/oacapture-1.0.0/missing aclocal-1.15
AMTAR = $${TAR-tar}
AM_DEFAULT_VERBOSITY = 1
APP_PATH_CFLAGS = 
AR = ar
AUTOCONF = ${SHELL} /home/oliver/dev/oacapture-1.0.0/missing autoconf
AUTOHEADER = ${SHELL} /home/oliver/dev/oacapture-1.0.0/missing autoheader
AUTOMAKE = ${SHELL} /home/oliver/dev/oacapture-1.0.0/missing automake-1.15
AWK = gawk
CC = gcc
CCDEPMODE = depmode=gcc3
CFLAGS = -g -O2
CPP = gcc -E
CPPFLAGS =    -I/usr/include/qt5/QtNetwork -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5 -I/usr/include/qt5/QtGui -I/usr/include/qt5 -I/usr/include/qt5/QtCore -I/usr/include/qt5  
CXX = g++
CXXCPP = g++ -E
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -fPIC
CYGPATH_W = echo
DEFAULT_PATH_CFLAGS = 
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DLLTOOL = false
DSYMUTIL = 
DUMPBIN = 
DYNLIB_EXTN_CFLAGS = -DDYNLIB_EXT_SO
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /usr/bin/grep -E
EXEEXT = 
FFMPEG_CFLAGS = -I $(top_srcdir)/ext/ffmpeg/libavformat                -I $(top_srcdir)/ext/ffmpeg/libavutil                -I $(top_srcdir)/ext/ffmpeg/libavcodec                -I $(top_srcdir)/ext/ffmpeg                -I $(top_builddir)/ext/ffmpeg 	       -Wno-deprecated-declarations
FFMPEG_LIBS = $(top_builddir)/ext/ffmpeg/libavformat/libavformat.a                $(top_builddir)/ext/ffmpeg/libavcodec/libavcodec.a                $(top_builddir)/ext/ffmpeg/libswresample/libswresample.a                $(top_builddir)/ext/ffmpeg/libavutil/libavutil.a
FFMPEG_SUBDIRS = 
FGREP = /usr/bin/grep -F
FXLOAD_CFLAGS = -DFXLOAD_PATH=\"$(bindir)/fxload\" -DFIRMWARE_QHY_PATH=\"$(libdir)/firmware/qhy\"
GREP = /usr/bin/grep
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LD = /usr/bin/ld -m elf_x86_64
LDFLAGS =  -L/usr/lib64    
LIBASI2_CFLAGS = -DHAVE_LIBASI2=1
LIBASI2_LIBS = $(top_builddir)/ext/libASICamera/libASICamera2.a
LIBASI_CFLAGS = -DHAVE_LIBASI=1
LIBASI_LIBS = $(top_builddir)/ext/libASICamera/libASICamera.a
LIBDC1394_CFLAGS = -I $(top_srcdir)/ext/libdc1394
LIBDC1394_LIBS = $(top_builddir)/ext/libdc1394/dc1394/libdc1394.la
LIBDC1394_SUBDIRS = 
LIBHIDAPI_CFLAGS = -I $(top_srcdir)/ext/libhidapi/hidapi
LIBHIDAPI_LIBS = $(top_builddir)/ext/libhidapi/libusb/libhidapi-libusb.la
LIBHIDAPI_SUBDIRS = 
LIBOBJS = 
LIBS = -ludev -ldl -llzma  -lz  -ltiff  -lQt5Network -lQt5Widgets -lQt5Gui -lQt5Core  
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIBTOUPCAM_CFLAGS = 
LIBUSB_CFLAGS = -I $(top_srcdir)/ext/libusb
LIBUSB_LIBS = $(top_builddir)/ext/libusb/libusb-1.0/libusb-1.0.la
LIBUSB_SUBDIRS = 
LIBUVC_CFLAGS = -DHAVE_LIBUVC=1 -I $(top_srcdir)/ext/libuvc/include
LIBUVC_LIBS = $(top_builddir)/ext/libuvc/src/libuvc.la
LIBWINDIB_CFLAGS = -I $(top_srcdir)/ext/libwindib
LIBWINDIB_LIBS = $(top_builddir)/ext/libwindib/libwindib.la
LIPO = 
LN_S = ln -s
LTLIBOBJS = 
LT_SYS_LIBRARY_PATH = 
MAINT = #
MAKEINFO = ${SHELL} /home/oliver/dev/oacapture-1.0.0/missing makeinfo
MANIFEST_TOOL = :
MKDIR_P = /usr/bin/mkdir -p
MOC = moc-qt5
NM = /usr/bin/nm -B
NMEDIT = 
OBJDUMP = objdump
OBJEXT = o
OSX_FRAMEWORKS = 
OTOOL = 
OTOOL64 = 
PACKAGE = openastro
PACKAGE_BUGREPORT = james@openastro.org
PACKAGE_NAME = openastro
PACKAGE_STRING = openastro 1.0.0
PACKAGE_TARNAME = openastro
PACKAGE_URL = 
PACKAGE_VERSION = 1.0.0
PATH_SEPARATOR = :
PKG_CONFIG = /usr/bin/pkg-config
PKG_CONFIG_LIBDIR = 
PKG_CONFIG_PATH = 
QT5_CFLAGS = -I/usr/include/qt5/QtNetwork -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5 -I/usr/include/qt5/QtGui -I/usr/include/qt5 -I/usr/include/qt5/QtCore -I/usr/include/qt5 
QT5_LIBS = -lQt5Network -lQt5Widgets -lQt5Gui -lQt5Core 
QT_CFLAGS = 
QT_LIBS = 
RANLIB = ranlib
RCC = rcc
SED = /usr/bin/sed
SET_MAKE = 
SHELL = /bin/sh
STRIP = strip
UIC = uic-qt5
VERSION = 1.0.0
abs_builddir = /home/oliver/dev/oacapture-1.0.0/liboacam
abs_srcdir = /home/oliver/dev/oacapture-1.0.0/liboacam
abs_top_builddir = /home/oliver/dev/oacapture-1.0.0
abs_top_srcdir = /home/oliver/dev/oacapture-1.0.0
ac_ct_AR = ar
ac_ct_CC = gcc
ac_ct_CXX = g++
ac_ct_DUMPBIN = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = $${TAR-tar} chof - "$$tardir"
am__untar = $${TAR-tar} xf -
bindir = ${exec_prefix}/bin
build = x86_64-unknown-linux-gnu
build_alias = 
build_cpu = x86_64
build_os = linux-gnu
build_vendor = unknown
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = x86_64-unknown-linux-gnu
host_alias = 
host_cpu = x86_64
host_os = linux-gnu
host_vendor = unknown
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /home/oliver/dev/oacapture-1.0.0/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(MKDIR_P)
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr/local
program_transform_name = s,x,x,
psdir = ${docdir}
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = ../
top_builddir = ..
top_srcdir = ..
AM_CPPFLAGS = \
  -I$(top_srcdir)/include \
  -I$(top_srcdir)/ext/libusb \
  -I$(top_srcdir)/ext/libASICamera/include \
  -I$(top_srcdir)/ext/libtoupcam/include \
  $(LIBASI_CFLAGS) $(LIBASI2_CFLAGS) $(LIBUSB_CFLAGS) $(FXLOAD_CFLAGS) \
  $(LIBUVC_CFLAGS) $(LIBDC1394_CFLAGS) $(LIBTOUPCAM_CFLAGS) \
  $(DYNLIB_EXTN_CFLAGS)

lib_LTLIBRARIES = liboacam.la
ASISRC = ZWASIoacam.c ZWASIconnect.c ZWASIcontroller.c ZWASIcallback.c \
  ZWASIcontrol.c ZWASIgetState.c ZWASIroi.c

ASI2SRC = ZWASI2oacam.c ZWASI2connect.c ZWASI2controller.c ZWASI2getState.c \
  ZWASI2control.c

#V4L2SRC = V4L2oacam.c V4L2connect.c V4L2ioctl.c V4L2cameras.c \
#  V4L2getState.c V4L2controller.c V4L2callback.c V4L2control.c

UVCSRC = UVCoacam.c UVCconnect.c UVCgetState.c UVCcontrol.c \
  UVCcontroller.c UVCcallback.c

IIDCSRC = IIDCoacam.c IIDCconnect.c IIDCgetState.c IIDCcontrol.c \
  IIDCcontroller.c IIDCcallback.c

#PGESRC = PGEoacam.c PGEconnect.c PGEgetState.c PGEcontrol.c \
#  PGEcontroller.c PGEcallback.c PGEroi.c

ATIKSERIALUDEVSRC = atikSerialoacam-udev.c atikSerialconnect-udev.c \
  atikSerialIO-udev.c

#ATIKSRC = atikSerialgetState.c atikSerialcallback.c atikSerialcontrol.c \
#  atikSerialcontroller.c

ATIKSRC = atikSerialgetState.c atikSerialcallback.c atikSerialcontrol.c \
  atikSerialcontroller.c

#ATIKSERIALFTDISRC = atikSerialoacam-ftdi.c atikSerialconnect-ftdi.c \
#  atikSerialIO-ftdi.c

#TOUPCAMSRC = Touptekoacam.c Touptekconnect.c Touptekcallback.c \
#  Touptekcontrol.c Touptekcontroller.c TouptekgetState.c Touptekroi.c

#MALLINCAMSRC = Mallincamoacam.c Mallincamconnect.c Mallincamcallback.c \
#  Mallincamcontrol.c Mallincamcontroller.c MallincamgetState.c Mallincamroi.c

#ALTAIRSRC = Altairoacam.c Altairconnect.c Altaircallback.c \
#  Altaircontrol.c Altaircontroller.c AltairgetState.c Altairroi.c

liboacam_la_SOURCES = \
  control.c debug.c oacam.c unimplemented.c utils.c \
  $(V4L2SRC) $(ASISRC) $(ASI2SRC) $(UVCSRC) $(IIDCSRC) $(ATIKSRC) \
  $(ATIKSERIALUDEVSRC) $(ATIKSERIALFTDISRC) $(PGESRC) $(TOUPCAMSRC) \
  $(MALLINCAMSRC) $(ALTAIRSRC) \
  PWCgetState.c PWCconnect.c PWCoacam.c \
  QHYoacam.c QHYconnect.c QHYfirmware.c QHYcontrol.c QHYcallback.c \
  QHYgetState.c QHYusb.c \
  QHY5.c QHY5controller.c \
  QHY5II.c QHY5IIcontroller.c \
  QHY5LII.c QHY5LIIcontroller.c \
  QHY6.c QHY6controller.c \
  SXoacam.c SXconnect.c SXcallback.c SXcontroller.c SXcontrol.c \
  SXgetState.c \
  EUVCoacam.c EUVCconnect.c EUVCcontrol.c EUVCcallback.c EUVCgetState.c \
  EUVCcontroller.c EUVCusb.c EUVCroi.c

all: all-am

.SUFFIXES:
.SUFFIXES: .c .lo .o .obj
$(srcdir)/Makefile.in: # $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --foreign liboacam/Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --foreign liboacam/Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure: # $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4): # $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):

install-libLTLIBRARIES: $(lib_LTLIBRARIES)
	@$(NORMAL_INSTALL)
	@list='$(lib_LTLIBRARIES)'; test -n "$(libdir)" || list=; \
	list2=; for p in $$list; do \
	  if test -f $$p; then \
	    list2="$$list2 $$p"; \
	  else :; fi; \
	done; \
	test -z "$$list2" || { \
	  echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) $$list2 '$(DESTDIR)$(libdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) $$list2 "$(DESTDIR)$(libdir)"; \
	}

uninstall-libLTLIBRARIES:
	@$(NORMAL_UNINSTALL)
	@list='$(lib_LTLIBRARIES)'; test -n "$(libdir)" || list=; \
	for p in $$list; do \
	  $(am__strip_dir) \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=uninstall rm -f '$(DESTDIR)$(libdir)/$$f'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=uninstall rm -f "$(DESTDIR)$(libdir)/$$f"; \
	done

clean-libLTLIBRARIES:
	-test -z "$(lib_LTLIBRARIES)" || rm -f $(lib_LTLIBRARIES)
	@list='$(lib_LTLIBRARIES)'; \
	locs=`for p in $$list; do echo $$p; done | \
	      sed 's|^[^/]*$$|.|; s|/[^/]*$$||; s|$$|/so_locations|' | \
	      sort -u`; \
	test -z "$$locs" || { \
	  echo rm -f $${locs}; \
	  rm -f $${locs}; \
	}

liboacam.la: $(liboacam_la_OBJECTS) $(liboacam_la_DEPENDENCIES) $(EXTRA_liboacam_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(LINK) -rpath $(libdir) $(liboacam_la_OBJECTS) $(liboacam_la_LIBADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/Altaircallback.Plo
include ./$(DEPDIR)/Altairconnect.Plo
include ./$(DEPDIR)/Altaircontrol.Plo
include ./$(DEPDIR)/Altaircontroller.Plo
include ./$(DEPDIR)/AltairgetState.Plo
include ./$(DEPDIR)/Altairoacam.Plo
include ./$(DEPDIR)/Altairroi.Plo
include ./$(DEPDIR)/EUVCcallback.Plo
include ./$(DEPDIR)/EUVCconnect.Plo
include ./$(DEPDIR)/EUVCcontrol.Plo
include ./$(DEPDIR)/EUVCcontroller.Plo
include ./$(DEPDIR)/EUVCgetState.Plo
include ./$(DEPDIR)/EUVCoacam.Plo
include ./$(DEPDIR)/EUVCroi.Plo
include ./$(DEPDIR)/EUVCusb.Plo
include ./$(DEPDIR)/IIDCcallback.Plo
include ./$(DEPDIR)/IIDCconnect.Plo
include ./$(DEPDIR)/IIDCcontrol.Plo
include ./$(DEPDIR)/IIDCcontroller.Plo
include ./$(DEPDIR)/IIDCgetState.Plo
include ./$(DEPDIR)/IIDCoacam.Plo
include ./$(DEPDIR)/Mallincamcallback.Plo
include ./$(DEPDIR)/Mallincamconnect.Plo
include ./$(DEPDIR)/Mallincamcontrol.Plo
include ./$(DEPDIR)/Mallincamcontroller.Plo
include ./$(DEPDIR)/MallincamgetState.Plo
include ./$(DEPDIR)/Mallincamoacam.Plo
include ./$(DEPDIR)/Mallincamroi.Plo
include ./$(DEPDIR)/PGEcallback.Plo
include ./$(DEPDIR)/PGEconnect.Plo
include ./$(DEPDIR)/PGEcontrol.Plo
include ./$(DEPDIR)/PGEcontroller.Plo
include ./$(DEPDIR)/PGEgetState.Plo
include ./$(DEPDIR)/PGEoacam.Plo
include ./$(DEPDIR)/PGEroi.Plo
include ./$(DEPDIR)/PWCconnect.Plo
include ./$(DEPDIR)/PWCgetState.Plo
include ./$(DEPDIR)/PWCoacam.Plo
include ./$(DEPDIR)/QHY5.Plo
include ./$(DEPDIR)/QHY5II.Plo
include ./$(DEPDIR)/QHY5IIcontroller.Plo
include ./$(DEPDIR)/QHY5LII.Plo
include ./$(DEPDIR)/QHY5LIIcontroller.Plo
include ./$(DEPDIR)/QHY5controller.Plo
include ./$(DEPDIR)/QHY6.Plo
include ./$(DEPDIR)/QHY6controller.Plo
include ./$(DEPDIR)/QHYcallback.Plo
include ./$(DEPDIR)/QHYconnect.Plo
include ./$(DEPDIR)/QHYcontrol.Plo
include ./$(DEPDIR)/QHYfirmware.Plo
include ./$(DEPDIR)/QHYgetState.Plo
include ./$(DEPDIR)/QHYoacam.Plo
include ./$(DEPDIR)/QHYusb.Plo
include ./$(DEPDIR)/SXcallback.Plo
include ./$(DEPDIR)/SXconnect.Plo
include ./$(DEPDIR)/SXcontrol.Plo
include ./$(DEPDIR)/SXcontroller.Plo
include ./$(DEPDIR)/SXgetState.Plo
include ./$(DEPDIR)/SXoacam.Plo
include ./$(DEPDIR)/Touptekcallback.Plo
include ./$(DEPDIR)/Touptekconnect.Plo
include ./$(DEPDIR)/Touptekcontrol.Plo
include ./$(DEPDIR)/Touptekcontroller.Plo
include ./$(DEPDIR)/TouptekgetState.Plo
include ./$(DEPDIR)/Touptekoacam.Plo
include ./$(DEPDIR)/Touptekroi.Plo
include ./$(DEPDIR)/UVCcallback.Plo
include ./$(DEPDIR)/UVCconnect.Plo
include ./$(DEPDIR)/UVCcontrol.Plo
include ./$(DEPDIR)/UVCcontroller.Plo
include ./$(DEPDIR)/UVCgetState.Plo
include ./$(DEPDIR)/UVCoacam.Plo
include ./$(DEPDIR)/V4L2callback.Plo
include ./$(DEPDIR)/V4L2cameras.Plo
include ./$(DEPDIR)/V4L2connect.Plo
include ./$(DEPDIR)/V4L2control.Plo
include ./$(DEPDIR)/V4L2controller.Plo
include ./$(DEPDIR)/V4L2getState.Plo
include ./$(DEPDIR)/V4L2ioctl.Plo
include ./$(DEPDIR)/V4L2oacam.Plo
include ./$(DEPDIR)/ZWASI2connect.Plo
include ./$(DEPDIR)/ZWASI2control.Plo
include ./$(DEPDIR)/ZWASI2controller.Plo
include ./$(DEPDIR)/ZWASI2getState.Plo
include ./$(DEPDIR)/ZWASI2oacam.Plo
include ./$(DEPDIR)/ZWASIcallback.Plo
include ./$(DEPDIR)/ZWASIconnect.Plo
include ./$(DEPDIR)/ZWASIcontrol.Plo
include ./$(DEPDIR)/ZWASIcontroller.Plo
include ./$(DEPDIR)/ZWASIgetState.Plo
include ./$(DEPDIR)/ZWASIoacam.Plo
include ./$(DEPDIR)/ZWASIroi.Plo
include ./$(DEPDIR)/atikSerialIO-ftdi.Plo
include ./$(DEPDIR)/atikSerialIO-udev.Plo
include ./$(DEPDIR)/atikSerialcallback.Plo
include ./$(DEPDIR)/atikSerialconnect-ftdi.Plo
include ./$(DEPDIR)/atikSerialconnect-udev.Plo
include ./$(DEPDIR)/atikSerialcontrol.Plo
include ./$(DEPDIR)/atikSerialcontroller.Plo
include ./$(DEPDIR)/atikSerialgetState.Plo
include ./$(DEPDIR)/atikSerialoacam-ftdi.Plo
include ./$(DEPDIR)/atikSerialoacam-udev.Plo
include ./$(DEPDIR)/control.Plo
include ./$(DEPDIR)/debug.Plo
include ./$(DEPDIR)/oacam.Plo
include ./$(DEPDIR)/unimplemented.Plo
include ./$(DEPDIR)/utils.Plo

.c.o:
	$(AM_V_CC)$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ $<

.c.obj:
	$(AM_V_CC)$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

.c.lo:
	$(AM_V_CC)$(LTCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Plo
#	$(AM_V_CC)source='$<' object='$@' libtool=yes \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(LTCOMPILE) -c -o $@ $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

ID: $(am__tagged_files)
	$(am__define_uniq_tagged_files); mkid -fID $$unique
tags: tags-am
TAGS: tags

tags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	set x; \
	here=`pwd`; \
	$(am__define_uniq_tagged_files); \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: ctags-am

CTAGS: ctags
ctags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	$(am__define_uniq_tagged_files); \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"
cscopelist: cscopelist-am

cscopelist-am: $(am__tagged_files)
	list='$(am__tagged_files)'; \
	case "$(srcdir)" in \
	  [\\/]* | ?:[\\/]*) sdir="$(srcdir)" ;; \
	  *) sdir=$(subdir)/$(srcdir) ;; \
	esac; \
	for i in $$list; do \
	  if test -f "$$i"; then \
	    echo "$(subdir)/$$i"; \
	  else \
	    echo "$$sdir/$$i"; \
	  fi; \
	done >> $(top_builddir)/cscope.files

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile $(LTLIBRARIES)
installdirs:
	for dir in "$(DESTDIR)$(libdir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	if test -z '$(STRIP)'; then \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	      install; \
	else \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	    "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'" install; \
	fi
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-libLTLIBRARIES clean-libtool \
	mostlyclean-am

distclean: distclean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am: install-libLTLIBRARIES

install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-libLTLIBRARIES

.MAKE: install-am install-strip

.PHONY: CTAGS GTAGS TAGS all all-am check check-am clean clean-generic \
	clean-libLTLIBRARIES clean-libtool cscopelist-am ctags \
	ctags-am distclean distclean-compile distclean-generic \
	distclean-libtool distclean-tags distdir dvi dvi-am html \
	html-am info info-am install install-am install-data \
	install-data-am install-dvi install-dvi-am install-exec \
	install-exec-am install-html install-html-am install-info \
	install-info-am install-libLTLIBRARIES install-man install-pdf \
	install-pdf-am install-ps install-ps-am install-strip \
	installcheck installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool pdf pdf-am ps ps-am \
	tags tags-am uninstall uninstall-am uninstall-libLTLIBRARIES

.PRECIOUS: Makefile


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
