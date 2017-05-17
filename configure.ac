#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([openastro], [1.0.0], [james@openastro.org])
AC_USE_SYSTEM_EXTENSIONS
AC_CONFIG_SRCDIR([liboademosaic/oademosaic.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])
AM_MAINTAINER_MODE([disable])

AC_DISABLE_SHARED

# Checks for programs.

PKG_PROG_PKG_CONFIG

AC_PROG_AWK
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AC_CHECK_PROGS(MOC, [moc-qt5 moc-qt4 moc])
AC_CHECK_PROGS(UIC, [uic-qt5 uic-qt4 uic])
AC_CHECK_PROGS(RCC, [rcc])
if test -z "$MOC" || test -z "$UIC" || test -z "$RCC"; then
AC_MSG_ERROR([Qt utility programs moc, uic, and rcc are required.])
fi

# Retrieve Qt compilation and linker flags
have_qt5=no
if test "$MOC" == "moc-qt5"
then
  have_qt5=yes
fi

if test "$have_qt5" == "yes"
then
  PKG_CHECK_MODULES(QT5, [Qt5Core, Qt5Gui, Qt5Network, Qt5Widgets], [], [
    AC_MSG_ERROR([Qt5 libraries are required.])])
  AC_MSG_NOTICE([Building using Qt5])
  CPPFLAGS="`$PKG_CONFIG --cflags-only-I Qt5Core Qt5Gui Qt5Network Qt5Widgets` $CPPFLAGS"
  LDFLAGS="`$PKG_CONFIG --libs-only-L Qt5Core Qt5Gui Qt5Network Qt5Widgets` $LDFLAGS"
  LIBS="`$PKG_CONFIG --libs-only-l Qt5Core Qt5Gui Qt5Network Qt5Widgets` $LIBS"
  AC_DEFINE([HAVE_QT5],[1],[Have Qt5])
else
  PKG_CHECK_MODULES(QT, [QtCore, QtGui, QtNetwork], [], [
    AC_MSG_ERROR([Qt libraries are required.])])
  if ! `$PKG_CONFIG --atleast-version=4.8.0 QtCore`; then
    AC_MSG_ERROR([Qt >= 4.8.0 is required.])
  fi
  AC_MSG_NOTICE([Building using Qt4])
  CPPFLAGS="`$PKG_CONFIG --cflags-only-I QtCore QtGui QtNetwork` $CPPFLAGS"
  LDFLAGS="`$PKG_CONFIG --libs-only-L QtCore QtGui QtNetwork` $LDFLAGS"
  LIBS="`$PKG_CONFIG --libs-only-l QtCore QtGui QtNetwork` $LIBS"
  AC_DEFINE([HAVE_QT4],[1],[Have Qt4])
fi

# Checks for libraries.

have_v4l2=no
#have_dc1394=no
have_dc1394=yes
have_cfitsio=no
have_udev=no
have_ftdi1=no
have_exp10=no
have_flycapture2=no
have_dl=no
have_toupcam=no
have_mallincam=no
have_altaircam=no

case $host in
  x86_64-apple-*)
    CPPFLAGS="-I/opt/local/include $CPPFLAGS"
    LDFLAGS="-L/opt/local/lib $LDFLAGS"
    ;;
  i?86-apple-*)
    CPPFLAGS="-I/opt/local/include $CPPFLAGS"
    LDFLAGS="-L/opt/local/lib $LDFLAGS"
    ;;
esac

if `$PKG_CONFIG --exists libv4l2`; then
  CPPFLAGS="`$PKG_CONFIG --cflags-only-I libv4l2` $CPPFLAGS"
  LDFLAGS="`$PKG_CONFIG --libs-only-L libv4l2` $LDFLAGS"
  LIBS="`$PKG_CONFIG --libs-only-l libv4l2` $LIBS"
  have_v4l2=yes
  AC_DEFINE([HAVE_LIBV4L2],[1],[Have V4L2 library])
else
  AC_CHECK_LIB([v4l2],[v4l2_open],[
    LIBS="-lv4l2 $LIBS"
    AC_DEFINE([HAVE_LIBV4L2],[1],[Have V4L2 library])
    have_v4l2=yes
  ],[
    AC_MSG_WARN([No V4L2 library found.  V4L2 cameras will not be supported])])
fi

if `$PKG_CONFIG --exists libtiff-4`; then
  CPPFLAGS="`$PKG_CONFIG --cflags-only-I libtiff-4` $CPPFLAGS"
  LDFLAGS="`$PKG_CONFIG --libs-only-L libtiff-4` $LDFLAGS"
  LIBS="`$PKG_CONFIG --libs-only-l libtiff-4` $LIBS"
  have_tiff=yes
else
  AC_CHECK_LIB([tiff],[TIFFOpen],[],[
    AC_MSG_ERROR([libtiff is required])])
fi

if `$PKG_CONFIG --exists libbz2`; then
  CPPFLAGS="`$PKG_CONFIG --cflags-only-I libbz2` $CPPFLAGS"
  LDFLAGS="`$PKG_CONFIG --libs-only-L libbz2` $LDFLAGS"
  LIBS="`$PKG_CONFIG --libs-only-l libbz2` $LIBS"
  have_bz2=yes
else
  AC_CHECK_LIB([bz2],[BZ2_bzDecompress],[],[
    AC_MSG_WARN([No bz2 library found])])
fi

if `$PKG_CONFIG --exists zlib`; then
  CPPFLAGS="`$PKG_CONFIG --cflags-only-I zlib` $CPPFLAGS"
  LDFLAGS="`$PKG_CONFIG --libs-only-L zlib` $LDFLAGS"
  LIBS="`$PKG_CONFIG --libs-only-l zlib` $LIBS"
  have_zlib=yes
else
  AC_CHECK_LIB([z],[uncompress],[],[
    AC_MSG_ERROR([libz is required])])
fi

if `$PKG_CONFIG --exists liblzma`; then
  CPPFLAGS="`$PKG_CONFIG --cflags-only-I liblzma` $CPPFLAGS"
  LDFLAGS="`$PKG_CONFIG --libs-only-L liblzma` $LDFLAGS"
  LIBS="`$PKG_CONFIG --libs-only-l liblzma` $LIBS"
  have_lzma=yes
else
  AC_CHECK_LIB([lzma],[lzma_code],[],[
    AC_MSG_ERROR([liblzma is required])])
fi

#if `$PKG_CONFIG --exists libdc1394-2`; then
#  CPPFLAGS="`$PKG_CONFIG --cflags-only-I libdc1394-2` $CPPFLAGS"
#  LDFLAGS="`$PKG_CONFIG --libs-only-L libdc1394-2` $LDFLAGS"
#  LIBS="`$PKG_CONFIG --libs-only-l libdc1394-2` $LIBS"
#  have_dc1394=yes
#  AC_DEFINE([HAVE_LIBDC1394],[1],[Have dc1394 library])
#else
#  AC_CHECK_LIB([dc1394],[dc1394_new],[
#    LIBS="-ldc1394 $LIBS"
#    AC_DEFINE([HAVE_LIBDC1394],[1],[Have dc1394 library])
#    have_dc1394=yes
#  ],[
#    AC_MSG_WARN([No dc1394 library found.  IIDC cameras will not be supported])])
#fi

AC_CHECK_LIB([m],[exp10],[
  AC_DEFINE([HAVE_EXP10],[1],[Have exp10 function in libm])
],[
  AC_MSG_WARN([No exp10() function found.  Using internal version])])

flycaplib="-lflycapture-c "
AC_CHECK_LIB([dl],[dlopen],[
  LIBS="-ldl $LIBS"
  AC_DEFINE([HAVE_LIBDL],[1],[Have dl library])
  have_dl=yes
  flycaplib=""
],[
  AC_MSG_WARN([No dl library found.  No big deal])])

AC_CHECK_LIB([flycapture-c],[fc2CreateGigEContext],[
  LIBS="$flycaplib$LIBS"
  AC_DEFINE([HAVE_LIBFLYCAPTURE2],[1],[Have flycapture2-c library])
  have_flycapture2=yes
],[
  AC_MSG_WARN([No flycapture2 library found.  Point Grey Gig-E cameras will not be supported])])

if test "x$have_dl" == "xyes" -a "x$have_flycapture2" == "xyes"
then
  LDFLAGS="-rdynamic $LDFLAGS"
fi

# Checks for header files.
AC_CHECK_HEADERS([errno.h fcntl.h float.h limits.h math.h stdint.h stdlib.h string.h strings.h sys/ioctl.h sys/time.h unistd.h fitsio.h cfitsio/fitsio.h ftdi.h libftdi/ftdi.h libftdi1/ftdi.h sys/sendfile.h sys/time.h syslog.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([getcwd gettimeofday select sqrt])
AC_CHECK_FUNCS([bzero memset memcpy])
AC_CHECK_FUNCS([fopen64 fseeko64 ftello64 stat64 freopen64])
AC_CHECK_FUNCS([fseeki64 ftelli64])
AC_CHECK_FUNCS([clock_gettime mkdir pow strcasecmp strchr strcspn strdup])
AC_CHECK_FUNCS([strerror strncasecmp strndup strrchr strstr strtoul])

# A whole pile of ugly stuff to make sure we get the FFmpeg we want
FFMPEG_CFLAGS="-I \$(top_srcdir)/ext/ffmpeg/libavformat \
               -I \$(top_srcdir)/ext/ffmpeg/libavutil \
               -I \$(top_srcdir)/ext/ffmpeg/libavcodec \
               -I \$(top_srcdir)/ext/ffmpeg \
               -I \$(top_builddir)/ext/ffmpeg \
	       -Wno-deprecated-declarations"

FFMPEG_LIBS="\$(top_builddir)/ext/ffmpeg/libavformat/libavformat.a \
               \$(top_builddir)/ext/ffmpeg/libavcodec/libavcodec.a \
               \$(top_builddir)/ext/ffmpeg/libswresample/libswresample.a \
               \$(top_builddir)/ext/ffmpeg/libavutil/libavutil.a"

AC_ARG_WITH(ffmpeg-extra-configure, 
  AC_HELP_STRING([--with-ffmpeg-extra-configure="xxx"],
  [extra configure options for internal ffmpeg ./configure script]),,
  with_ffmpeg_extra_configure=no)

embffmpeg_configure_args="--prefix=$prefix"

embffmpeg_configure_args="$embffmpeg_configure_args --enable-memalign-hack --enable-static --disable-debug --disable-programs --disable-network --disable-encoders --enable-encoder=utvideo --enable-encoder=rawvideo --disable-doc --disable-muxers --enable-muxer=avi --enable-muxer=mov --disable-bsfs --disable-indevs --disable-protocols --enable-protocol=file --disable-iconv --disable-vaapi --disable-vda --disable-decoders --disable-demuxers --disable-filters --disable-devices"

if test "$enable_shared" = "yes"; then
  embffmpeg_configure_args="$embffmpeg_configure_args --enable-shared"
else
  embffmpeg_configure_args="$embffmpeg_configure_args --disable-shared"
fi

if test "x$cross_compiling" = xyes; then
  embffmpeg_configure_args="$embffmpeg_configure_args --enable-cross-compile \
      --target-os=$host_os --arch=$host_cpu --cross-prefix=$host_alias-"
fi

FFMPEG_OPTS="`$srcdir/ext/ffmpeg/configure --help`"
can_disable=`echo "$FFMPEG_OPTS" | grep 'disable-ffmpeg'`
if test "$can_disable" != ""; then
  embffmpeg_configure_args="$embffmpeg_configure_args --disable-ffmpeg"
fi

if test "x$with_ffmpeg_extra_configure" != "xno"; then
  embffmpeg_configure_args="$embffmpeg_configure_args $with_ffmpeg_extra_configure"
fi

AC_CONFIG_COMMANDS([configure-embedded-ffmpeg],
  [echo "Configuring included FFmpeg instance with args $embffmpeg_configure_args"
   origdir=`pwd`
   dnl Don't put path on the configure call when not needed, as FFmpeg's configure relies on it
   dnl to detect out-of-tree builds
   if test -z "$srcdir" -o "$srcdir" = .; then
     confcmd=./configure
   else
     confcmd="$origdir"/"$ac_top_srcdir"/ext/ffmpeg/configure
   fi

   AS_MKDIR_P(["$ac_top_build_prefix"ext/ffmpeg])
   cd "$ac_top_build_prefix"ext/ffmpeg &&
       $confcmd $embffmpeg_configure_args ||
       AC_MSG_ERROR([Failed to configure embedded FFmpeg tree])
   cd "$origdir"
  ],
  [embffmpeg_configure_args="$embffmpeg_configure_args"])
AC_MSG_NOTICE([Using included FFMpeg code])

AC_SUBST(FFMPEG_CFLAGS)
AC_SUBST(FFMPEG_LIBS)
AC_SUBST(FFMPEG_SUBDIRS)

# Same play again, but this time for libusb-1.0

LIBUSB_CFLAGS="-I \$(top_srcdir)/ext/libusb"
LIBUSB_LIBS="\$(top_builddir)/ext/libusb/libusb-1.0/libusb-1.0.la"

AC_ARG_WITH(libusb-extra-configure, 
  AC_HELP_STRING([--with-libusb-extra-configure="xxx"],
  [extra configure options for internal libusb ./configure script]),,
  with_libusb_extra_configure=no)

emblibusb_configure_args="--prefix=$prefix"

if test "$enable_shared" = "yes"; then
  emblibusb_configure_args="$emblibusb_configure_args --enable-shared --enable-examples-build"
else
  emblibusb_configure_args="$emblibusb_configure_args --disable-shared --enable-examples-build"
fi

if test "x$cross_compiling" = xyes; then
  emblibusb_configure_args="$emblibusb_configure_args --enable-cross-compile \
      --target-os=$host_os --arch=$host_cpu --cross-prefix=$host_alias-"
fi

if test "x$with_libusb_extra_configure" != "xno"; then
  emblibusb_configure_args="$emblibusb_configure_args $with_libusb_extra_configure"
fi

AC_CONFIG_COMMANDS([configure-embedded-libusb],
  [echo "Configuring included libusb-1.0 instance with args $emblibusb_configure_args"
   origdir=`pwd`
   dnl Don't put path on the configure call when not needed
   if test -z "$srcdir" -o "$srcdir" = .; then
     confcmd=./configure
   else
     confcmd="$origdir"/"$ac_top_srcdir"/ext/libusb/configure
   fi

   AS_MKDIR_P(["$ac_top_build_prefix"ext/libusb])
   cd "$ac_top_build_prefix"ext/libusb &&
       $confcmd $emblibusb_configure_args ||
       AC_MSG_ERROR([Failed to configure embedded libusb-1.0 tree])
   cd "$origdir"
  ],
  [emblibusb_configure_args="$emblibusb_configure_args"])
AC_MSG_NOTICE([Using included libusb-1.0 code])

AC_SUBST(LIBUSB_CFLAGS)
AC_SUBST(LIBUSB_LIBS)
AC_SUBST(LIBUSB_SUBDIRS)

# And again, for libhidapi this time

LIBHIDAPI_CFLAGS="-I \$(top_srcdir)/ext/libhidapi/hidapi"
LIBHIDAPI_LIBS="\$(top_builddir)/ext/libhidapi/libusb/libhidapi-libusb.la"

AC_ARG_WITH(libhidapi-extra-configure,
  AC_HELP_STRING([--with-libhidapi-extra-configure="xxx"],
  [extra configure options for internal libhidapi ./configure script]),,
  with_libhidapi_extra_configure=no)

emblibhidapi_configure_args="--prefix=$prefix"

if test "$enable_shared" = "yes"; then
  emblibhidapi_configure_args="$emblibhidapi_configure_args --enable-shared"
else
  emblibhidapi_configure_args="$emblibhidapi_configure_args --disable-shared"
fi

if test "x$cross_compiling" = xyes; then
  emblibhidapi_configure_args="$emblibhidapi_configure_args --enable-cross-compile \
      --target-os=$host_os --arch=$host_cpu --cross-prefix=$host_alias-"
fi

if test "x$with_libhidapi_extra_configure" != "xno"; then
  emblibhidapi_configure_args="$emblibhidapi_configure_args $with_libhidapi_extra_configure"
fi


AC_CONFIG_COMMANDS([configure-embedded-libhidapi],
  [echo "Configuring included libhidapi instance with args $emblibhidapi_configure_args"
   origdir=`pwd`
   dnl Don't put path on the configure call when not needed
   if test -z "$srcdir" -o "$srcdir" = .; then
     confcmd=./configure
   else
     confcmd="$origdir"/"$ac_top_srcdir"/ext/libhidapi/configure
   fi

   AS_MKDIR_P(["$ac_top_build_prefix"ext/libhidapi])
  cd "$ac_top_build_prefix"ext/libhidapi && ./bootstrap &&
       libusb_CFLAGS=-I"$origdir"/ext/libusb libusb_LIBS="$origdir"/ext/libusb/libusb-1.0/libusb-1.0.la $confcmd $emblibhidapi_configure_args ||
       AC_MSG_ERROR([Failed to configure embedded libhidapi-1.0 tree])
   cd "$origdir"
  ],
  [emblibhidapi_configure_args="$emblibhidapi_configure_args"])
AC_MSG_NOTICE([Using included libhidapi code])

AC_SUBST(LIBHIDAPI_CFLAGS)
AC_SUBST(LIBHIDAPI_LIBS)
AC_SUBST(LIBHIDAPI_SUBDIRS)

# And once more, for libdc1394

LIBDC1394_CFLAGS="-I \$(top_srcdir)/ext/libdc1394"
LIBDC1394_LIBS="\$(top_builddir)/ext/libdc1394/dc1394/libdc1394.la"
have_dc1394=yes

AC_ARG_WITH(libdc1394-extra-configure,
  AC_HELP_STRING([--with-libdc1394-extra-configure="xxx"],
  [extra configure options for internal libdc1394 ./configure script]),,
  with_libdc1394_extra_configure=no)

emblibdc1394_configure_args="--prefix=$prefix --disable-shared --disable-sdltest --disable-examples"

if test "$enable_shared" = "yes"; then
  emblibdc1394_configure_args="$emblibdc1394_configure_args --enable-shared"
else
  emblibdc1394_configure_args="$emblibdc1394_configure_args --disable-shared"
fi

if test "x$cross_compiling" = xyes; then
  emblibdc1394_configure_args="$emblibdc1394_configure_args --enable-cross-compile \
      --target-os=$host_os --arch=$host_cpu --cross-prefix=$host_alias-"
fi

if test "x$with_libdc1394_extra_configure" != "xno"; then
  emblibdc1394_configure_args="$emblibdc1394_configure_args $with_libdc1394_extra_configure"
fi


AC_CONFIG_COMMANDS([configure-embedded-libdc1394],
  [echo "Configuring included libdc1394 instance with args $emblibdc1394_configure_args"
   origdir=`pwd`
   dnl Don't put path on the configure call when not needed
   if test -z "$srcdir" -o "$srcdir" = .; then
     confcmd=./configure
   else
     confcmd="$origdir"/"$ac_top_srcdir"/ext/libdc1394/configure
   fi

   AS_MKDIR_P(["$ac_top_build_prefix"ext/libdc1394])
  cd "$ac_top_build_prefix"ext/libdc1394 &&
       LIBUSB_CFLAGS=-I"$origdir"/ext/libusb/libusb-1.0 LIBUSB_LIBS="$origdir"/ext/libusb/libusb-1.0/libusb-1.0.la $confcmd $emblibdc1394_configure_args ||
       AC_MSG_ERROR([Failed to configure embedded libdc1394 tree])
   cd "$origdir"
  ],
  [emblibdc1394_configure_args="$emblibdc1394_configure_args"])
AC_DEFINE([HAVE_LIBDC1394],[1],[Using included libdc1394 library])

AC_SUBST(LIBDC1394_CFLAGS)
AC_SUBST(LIBDC1394_LIBS)
AC_SUBST(LIBDC1394_SUBDIRS)

LIBWINDIB_CFLAGS="-I \$(top_srcdir)/ext/libwindib"
LIBWINDIB_LIBS="\$(top_builddir)/ext/libwindib/libwindib.la"
AC_SUBST(LIBWINDIB_CFLAGS)
AC_SUBST(LIBWINDIB_LIBS)

AC_CANONICAL_HOST

OSX_FRAMEWORKS=""
FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"\$(bindir)/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"\$(libdir)/firmware/qhy\\\""
LIBASI_CFLAGS="-DHAVE_LIBASI=1"
LIBASI2_CFLAGS="-DHAVE_LIBASI2=1"
APP_PATH_CFLAGS=""
DEFAULT_PATH_CFLAGS=""
DYNLIB_EXTN_CFLAGS="-DDYNLIB_EXT_SO"
LIBASI_LIBS="\$(top_builddir)/ext/libASICamera/libASICamera.a"
LIBASI2_LIBS="\$(top_builddir)/ext/libASICamera/libASICamera2.a"

libuvc_default=yes
libcfitsio_default=yes
libftdi1_default=yes
libudev_default=yes
# work around broken autoconf
ext1=ext; ext2=ext; ext3=ext; ext4=ext; ext5=ext; ext6=ext
ext7=ext; ext8=ext; ext9=ext; extA=ext; extB=ext; extC=ext
extD=ext; extE=ext; extF=ext; extG=ext; extH=ext; extI=ext
extJ=ext; extK=ext; extL=ext; extM=ext
case $host in
  x86_64-apple-*)
    AC_CONFIG_LINKS([$ext1/libASICamera/libASICamera.a:ext/libASICamera/mac64/libASICamera.a])
    AC_CONFIG_LINKS([$ext7/libASICamera/libASICamera2.a:ext/libASICamera/mac64/libASICamera2.a])
    AC_CONFIG_LINKS([$extH/libtoupcam/libtoupcam.dylib:ext/libtoupcam/mac64/libtoupcam.dylib])
    AC_CONFIG_LINKS([$extI/libaltaircam/libaltaircam.dylib:ext/libaltaircam/mac64/libaltaircam.dylib])
    OSX_FRAMEWORKS="-framework Carbon -framework CoreVideo -framework IOKit"
    FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"/MacOS/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/Resources/firmware/qhy\\\""
    # LIBUVC_CFLAGS="-DHAVE_LIBUVC=1 -I \$(top_srcdir)/ext/libuvc/include"
    # LIBUVC_LIBS="\$(top_builddir)/ext/libuvc/src/libuvc.la"
    LIBHIDAPI_LIBS="\$(top_builddir)/ext/libhidapi/mac/libhidapi.la"
    libuvc_default=yes
    have_toupcam=yes
    have_mallincam=yes
    have_altaircam=yes
    APP_PATH_CFLAGS="-DUSE_APP_PATH=1"
    DEFAULT_PATH_CFLAGS="-DUSE_HOME_DEFAULT=1"
    DYNLIB_EXTN_CFLAGS="-DDYNLIB_EXT_DYLIB"
    ;;
  i?86-apple-*)
    AC_CONFIG_LINKS([$ext2/libASICamera/libASICamera.a:ext/libASICamera/mac32/libASICamera.a])
    AC_CONFIG_LINKS([$ext8/libASICamera/libASICamera2.a:ext/libASICamera/mac32/libASICamera2.a])
    OSX_FRAMEWORKS="-framework Carbon -framework CoreVideo -framework IOKit"
    FXLOAD_CFLAGS="-DFXLOAD_PATH=\\\"/MacOS/fxload\\\" -DFIRMWARE_QHY_PATH=\\\"/Resources/firmware/qhy\\\""
    # LIBUVC_CFLAGS="-DHAVE_LIBUVC=1 -I \$(top_srcdir)/ext/libuvc/include"
    # LIBUVC_LIBS="\$(top_builddir)/ext/libuvc/src/libuvc.la"
    LIBHIDAPI_LIBS="\$(top_builddir)/ext/libhidapi/mac/libhidapi.la"
    libuvc_default=yes
    APP_PATH_CFLAGS="-DUSE_APP_PATH=1"
    DEFAULT_PATH_CFLAGS="-DUSE_HOME_DEFAULT=1"
    DYNLIB_EXTN_CFLAGS="-DDYNLIB_EXT_DYLIB"
    ;;
  i?86-*-*)
    AC_CONFIG_LINKS([$ext3/libASICamera/libASICamera.a:ext/libASICamera/x86/libASICamera.a])
    AC_CONFIG_LINKS([$ext9/libASICamera/libASICamera2.a:ext/libASICamera/x86/libASICamera2.a])
    AC_CONFIG_LINKS([$extF/libtoupcam/libtoupcam.so:ext/libtoupcam/x86/libtoupcam.so])
    # AC_CONFIG_LINKS([$extJ/libmallincam/libmallincam.so:ext/libmallincam/x86/libmallincam.so])
    AC_CONFIG_LINKS([$extK/libaltaircam/libaltaircam.so:ext/libaltaircam/x86/libaltaircam.so])
    have_toupcam=yes
    have_mallincam=yes
    have_altaircam=yes
    ;;
  x86_64-*-*)
    # LIBUVC_CFLAGS="-DHAVE_LIBUVC=1 -I \$(top_srcdir)/ext/libuvc/include"
    # LIBUVC_LIBS="\$(top_builddir)/ext/libuvc/src/libuvc.la"
    AC_CONFIG_LINKS([$ext4/libASICamera/libASICamera.a:ext/libASICamera/x64/libASICamera.a])
    AC_CONFIG_LINKS([$extA/libASICamera/libASICamera2.a:ext/libASICamera/x64/libASICamera2.a])
    AC_CONFIG_LINKS([$extG/libtoupcam/libtoupcam.so:ext/libtoupcam/x64/libtoupcam.so])
    #AC_CONFIG_LINKS([$extL/libmallincam/libmallincam.so:ext/libmallincam/x64/libmallincam.so])
    AC_CONFIG_LINKS([$extM/libaltaircam/libaltaircam.so:ext/libaltaircam/x64/libaltaircam.so])
    ;;
  armv7l-*-*)
    AC_CONFIG_LINKS([$extD/libASICamera/libASICamera.a:ext/libASICamera/armv7/libASICamera.a])
    AC_CONFIG_LINKS([$extE/libASICamera/libASICamera2.a:ext/libASICamera/armv7/libASICamera2.a])
    have_toupcam=yes
    have_mallincam=yes
    have_altaircam=yes
    ;;
  armv6l-*-*)
    AC_CONFIG_LINKS([$ext5/libASICamera/libASICamera.a:ext/libASICamera/armv6/libASICamera.a])
    AC_CONFIG_LINKS([$extB/libASICamera/libASICamera2.a:ext/libASICamera/armv6/libASICamera2.a])
    ;;
  armv5l-*-*)
    AC_CONFIG_LINKS([$ext6/libASICamera/libASICamera.a:ext/libASICamera/armv5/libASICamera.a])
    AC_CONFIG_LINKS([$extC/libASICamera/libASICamera2.a:ext/libASICamera/armv5/libASICamera2.a])
    ;;
  *)
    LIBASI_LIBS=""
    LIBASI_CFLAGS="-DHAVE_LIBASI=0"
    LIBASI2_LIBS=""
    LIBASI2_CFLAGS="-DHAVE_LIBASI2=0"
    AC_MSG_NOTICE([No compatible ASI library for architecture $host.  Support for ASI cameras not included])
    ;;
esac

AC_ARG_WITH(libuvc,
  AC_HELP_STRING([--with-libuvc],[build with libuvc]),,with_libuvc=$libuvc_default)

if test "x$with_libuvc" != "xno"; then
  LIBUVC_CFLAGS="-DHAVE_LIBUVC=1 -I \$(top_srcdir)/ext/libuvc/include"
  LIBUVC_LIBS="\$(top_builddir)/ext/libuvc/src/libuvc.la"
else
  LIBUVC_CFLAGS="-DHAVE_LIBUVC=0"
  LIBUVC_LIBS=""
fi

AC_ARG_WITH(libcfitsio,
  AC_HELP_STRING([--with-libcfitsio],[build with libcfitsio]),have_cfitsio=$with_libcfitsio,with_libcfitsio=$libcfitsio_default)

if test "x$with_libcfitsio" != "xno"; then
  with_libcfitsio=no
  if `$PKG_CONFIG --exists cfitsio`; then
    CPPFLAGS="`$PKG_CONFIG --cflags-only-I cfitsio` $CPPFLAGS"
    LDFLAGS="`$PKG_CONFIG --libs-only-L cfitsio` $LDFLAGS"
    LIBS="`$PKG_CONFIG --libs-only-l cfitsio` $LIBS"
    have_cfitsio=yes
    AC_DEFINE([HAVE_LIBCFITSIO],[1],[Have CFITSIO library])
  else
    AC_CHECK_LIB([cfitsio],[ffopen],[
      LIBS="-lcfitsio $LIBS"
      AC_DEFINE([HAVE_LIBCFITSIO],[1],[Have CFITSIO library])
      have_cfitsio=yes
    ],[
      AC_MSG_WARN([No CFITSIO library found.  FITS output will not be supported])])
  fi
fi

AC_ARG_WITH(libftdi1,
  AC_HELP_STRING([--with-libftdi1],[build with libftdi1]),have_libftdi1=$with_libftdi1,with_libftdi1=$libftdi1_default)

if test "x$with_libftdi1" != "xno"; then
  with_libftdi1=no
#
# Temporarily comment these out as they cause the system libusb to get
# pulled in
#
# if `$PKG_CONFIG --exists libftdi1`; then
#   CPPFLAGS="`$PKG_CONFIG --cflags-only-I libftdi1` $CPPFLAGS"
#   LDFLAGS="`$PKG_CONFIG --libs-only-L libftdi1` $LDFLAGS"
#   LIBS="`$PKG_CONFIG --libs-only-l libftdi1` $LIBS"
#   have_ftdi1=yes
#   AC_DEFINE([HAVE_LIBFTDI],[1],[Have ftdi1 library])
# else
#   if `$PKG_CONFIG --exists libftdi`; then
#     CPPFLAGS="`$PKG_CONFIG --cflags-only-I libftdi` $CPPFLAGS"
#     LDFLAGS="`$PKG_CONFIG --libs-only-L libftdi` $LDFLAGS"
#     LIBS="`$PKG_CONFIG --libs-only-l libftdi` $LIBS"
#     have_ftdi1=yes
#     AC_DEFINE([HAVE_LIBFTDI],[1],[Have ftdi1 library])
#   else
      AC_CHECK_LIB([ftdi1],[ftdi_new],[
        LIBS="-lftdi1 $LIBS"
        AC_DEFINE([HAVE_LIBFTDI],[1],[Have ftdi1 library])
        have_ftdi1=yes
      ],[
        AC_CHECK_LIB([ftdi],[ftdi_new],[
          LIBS="-lftdi $LIBS"
          AC_DEFINE([HAVE_LIBFTDI],[1],[Have ftdi1 library])
          have_ftdi1=yes
        ],[
          AC_MSG_WARN([No ftdi1 library found.  Xagyl filter wheels can not be supported using libftdi1])])])
#   fi
# fi
fi

AC_ARG_WITH(libudev,
  AC_HELP_STRING([--with-libudev],[build with libudev]),have_libudev=$with_libudev,with_libudev=$libudev_default)

if test "x$with_libudev" != "xno"; then
  with_libudev=no
  AC_CHECK_LIB([udev],[udev_new],[
    LIBS="-ludev $LIBS"
    AC_DEFINE([HAVE_LIBUDEV],[1],[Have udev library])
    have_udev=yes
  ],[
    AC_MSG_WARN([No udev library found.  Xagyl filter wheels can not be supported using libudev])])
fi

## Deal with Toupcam libtoupcam library
#
#AC_ARG_WITH(toupcam_cflags,
#  AC_HELP_STRING([--with-toupcam-cflags="xxx"],
#  [CFLAGS for toupcam library]),,
#  with_toupcam_cflags=no)
#AC_ARG_WITH(toupcam_ldflags,
#  AC_HELP_STRING([--with-toupcam-ldflags="xxx"],
#  [LDFLAGS for toupcam library]),,
#  with_toupcam_ldflags=no)

#LIBTOUPCAM_LDFLAGS="-L \$(top_srcdir)/ext/libtoupcam"
#if test "x$with_toupcam_cflags" != "xno"
#then
#  LIBTOUPCAM_CFLAGS="$with_toupcam_cflags"
#fi
#if test "x$with_toupcam_ldflags" != "xno"
#then
#  LIBTOUPCAM_LDFLAGS="$with_toupcam_ldflags"
#fi

#oldLIBS=$LIBS
#LIBS="$LIBTOUPCAM_LDFLAGS $LIBS"
#AC_CHECK_LIB([toupcam],[Toupcam_Enum],[
#  LIBS="-lv4l2 $LIBS"
if test "x$have_toupcam" != "xno"
then
  LIBTOUPCAM_CFLAGS="-I \$(top_srcdir)/ext/libtoupcam/include"
  AC_DEFINE([HAVE_LIBTOUPCAM],[1],[Have Toupcam library])
  AC_DEFINE([HAVE_LIBMALLINCAM],[1],[Have Mallincam library])
  AC_DEFINE([HAVE_LIBALTAIRCAM],[1],[Have Altair camera library])
#],[
#  AC_MSG_WARN([No toupcam library found.  Touptek cameras will not be supported])])
fi
#LIBS=$oldLIBS
AC_SUBST(LIBTOUPCAM_CFLAGS)
#AC_SUBST(LIBTOUPCAM_LDFLAGS)

AC_SUBST(OSX_FRAMEWORKS)
AC_SUBST(FXLOAD_CFLAGS)
AC_SUBST(FXLOAD_CFLAGS)
AC_SUBST(LIBUVC_CFLAGS)
AC_SUBST(LIBUVC_LIBS)
AC_SUBST(LIBASI_CFLAGS)
AC_SUBST(LIBASI_LIBS)
AC_SUBST(LIBASI2_CFLAGS)
AC_SUBST(LIBASI2_LIBS)
AC_SUBST(APP_PATH_CFLAGS)
AC_SUBST(DEFAULT_PATH_CFLAGS)
AC_SUBST(DYNLIB_EXTN_CFLAGS)

AM_CONDITIONAL([LIBUVC_COND], [test "x$LIBUVC_LIBS" != "x"])
AM_CONDITIONAL([LIBASI_COND], [test "x$LIBASI_LIBS" != "x"])
AM_CONDITIONAL([LIBASI2_COND], [test "x$LIBASI2_LIBS" != "x"])
AM_CONDITIONAL([LIBV4L2_COND], [test "x$have_v4l2" == "xyes"])
AM_CONDITIONAL([LIBCFITSIO_COND], [test "x$have_cfitsio" == "xyes"])
AM_CONDITIONAL([LIBDC1394_COND], [test "x$have_dc1394" == "xyes"])
AM_CONDITIONAL([LIBUDEV_COND], [test "x$have_udev" == "xyes"])
AM_CONDITIONAL([LIBFTDI_COND], [test "x$have_ftdi1" == "xyes"])
AM_CONDITIONAL([LIBFLYCAPTURE2_COND], [test "x$have_flycapture2" == "xyes"])
AM_CONDITIONAL([LIBDL_COND], [test "x$have_dl" == "xyes"])
AM_CONDITIONAL([LIBTOUPCAM_COND], [test "x$have_toupcam" == "xyes"])
AM_CONDITIONAL([LIBMALLINCAM_COND], [test "x$have_mallincam" == "xyes"])
AM_CONDITIONAL([LIBALTAIRCAM_COND], [test "x$have_altaircam" == "xyes"])

AC_CONFIG_FILES([Makefile liboautil/Makefile liboacam/Makefile liboademosaic/Makefile liboaSER/Makefile liboavideo/Makefile liboafilterwheel/Makefile liboaimgproc/Makefile liboaPTR/Makefile oacapture/Makefile ext/Makefile ext/libuvc/Makefile ext/libuvc/src/Makefile ext/libwindib/Makefile oalive/Makefile])
AC_OUTPUT
