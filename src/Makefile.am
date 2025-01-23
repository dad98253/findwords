## Process this file with automake to produce Makefile.in

#SUBDIRS = build-aux
#AC_CONFIG_AUX_DIR = build-aux

ACLOCAL_AMFLAGS = -I m4 --install

#build findwords
bin_PROGRAMS = $(top_builddir)/bin/findwords
#add in main()
__top_builddir__bin_findwords_SOURCES = findwords.cpp permute.cpp
if FREEBSD
__top_builddir__bin_findwords_LDFLAGS = -Wl,-Map,loadmap.txt 
else
__top_builddir__bin_findwords_LDFLAGS = -Wl,-Map,loadmap.txt 
endif

#add header files
noinst_HEADERS = findwords.h gitversion.h

AM_CPPFLAGS = $(DEPS_CFLAGS) $(MY_CPPFLAGS)
AM_CXXFLAGS = -W -Wall -fmessage-length=0

	
