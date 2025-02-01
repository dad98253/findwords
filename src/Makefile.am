## Process this file with automake to produce Makefile.in

#SUBDIRS = build-aux
#AC_CONFIG_AUX_DIR = build-aux

ACLOCAL_AMFLAGS = -I m4 --install

#build permute
bin_PROGRAMS = $(top_builddir)/bin/permute
#add in main()
__top_builddir__bin_permute_SOURCES = permute.cpp FindPermutations.cpp
if FREEBSD
__top_builddir__bin_permute_LDFLAGS = -Wl,-Map,loadmap.txt 
else
__top_builddir__bin_permute_LDFLAGS = -Wl,-Map,loadmap.txt 
endif

#add header files
noinst_HEADERS = permute.h gitversion.h ../config.h

AM_CPPFLAGS = $(DEPS_CFLAGS) $(MY_CPPFLAGS)
AM_CXXFLAGS = -W -Wall -fmessage-length=0

	
