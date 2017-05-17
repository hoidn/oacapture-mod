AM_CPPFLAGS = -I$(top_srcdir)/hidapi $(libusb_CFLAGS)

if OS_LINUX
lib_LTLIBRARIES = libhidapi-libusb.la
libhidapi_libusb_la_SOURCES = hid.c
libhidapi_libusb_la_LDFLAGS = $(LTLDFLAGS) $(PTHREAD_CFLAGS)
libhidapi_libusb_la_LIBADD = $(libusb_LIBS)
endif

if OS_FREEBSD
lib_LTLIBRARIES = libhidapi.la
libhidapi_la_SOURCES = hid.c
libhidapi_la_LDFLAGS = $(LTLDFLAGS)
libhidapi_la_LIBADD = $(libusb_LIBS)
endif

if OS_KFREEBSD
lib_LTLIBRARIES = libhidapi.la
libhidapi_la_SOURCES = hid.c
libhidapi_la_LDFLAGS = $(LTLDFLAGS)
libhidapi_la_LIBADD = $(libusb_LIBS)
endif

hdrdir = $(includedir)/hidapi
hdr_HEADERS = $(top_srcdir)/hidapi/hidapi.h

EXTRA_DIST = Makefile-manual
