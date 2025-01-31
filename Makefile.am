## Process this file with automake to produce Makefile.in

#SUBDIRS = build-aux
#AC_CONFIG_AUX_DIR = build-aux

ACLOCAL_AMFLAGS = -I m4 --install

# Generate the ChangeLog from git history.
gen_start_date = 2025-01-01 00:00:00 UTC
.PHONY: gen-ChangeLog
gen-ChangeLog:
	if test -d $(top_srcdir)/.git; then \
	  $(top_srcdir)/build-aux/gitlog-to-changelog \
	    --since='$(gen_start_date)' > $(distdir)/cl-t \
	    && rm -f $(distdir)/ChangeLog \
	    && mv $(distdir)/cl-t $(distdir)/ChangeLog; \
	fi

# Dummy rule, to pacify automake "gnu" strictness and allow a clean
# bootstrap.  Creates a dummy ChangeLog (unless one is already present,
# that will be overridden with a proper one at distribution time.
ChangeLog:
	@echo dummy > $@

#   Version string management.  There are two files to be aware of:
#
#   .tarball-version - present only in a distribution tarball, and not in
#   a checked-out repository.  Created with contents that were learned at
#   the last time autoconf was run, and used by git-version-gen.  Must not
#   be present in either $(srcdir) or $(builddir) for git-version-gen to
#   give accurate answers during normal development with a checked out tree,
#   but must be present in a tarball when there is no version control system.
#   Therefore, it cannot be used in any dependencies.  GNUmakefile has
#   hooks to force a reconfigure at distribution time to get the value
#   correct, without penalizing normal development with extra reconfigures.
#
#   .version - present in a checked-out repository and in a distribution
#   tarball.  At least as current as the most recent .tarball-version
#   creation.  Usable in dependencies, particularly for files that don't
#   want to depend on config.h but do want to track version changes.

BUILT_SOURCES = $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo '$(VERSION)' > $@-t
	mv $@-t $@

# Arrange so that .tarball-version appears only in distribution tarballs,
# never in a checked-out repository.
dist-hook:
	echo '$(VERSION)' > $(distdir)/.tarball-version


SUBDIRS=. src tests man


EXTRA_DIST = $(top_srcdir)/.version m4/Makefile.in \
	     build-aux/Makefile.in \
	     build-aux/git-version-gen \
	     build-aux/gitlog-to-changelog \
	     man/Makefile.am \
             tests/m4/atenv.m4
	

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool


@GENERATE_CHANGELOG_RULES@
  CHANGELOG_START = origin/main
  dist-hook: dist-ChangeLog

distclean-local:
	@rm config.status configure config.log
	@rm Makefile
	@rm -r autom4te.cache/
	@rm aclocal.m4
	@rm Makefile.in
	@rm tests/Makefile.in
	@rm man/Makefile.in
	@rm tests/Makefile
	@rm man/Makefile

help:
	-@echo "make                    --> build findwords"
	-@echo "make clean              --> delete what was built"
	-@echo "make distclean          --> delete auto tools products"
	-@echo "make dist               --> build distribution package"

AM_CPPFLAGS = $(DEPS_CFLAGS) $(MY_CPPFLAGS)
AM_CXXFLAGS = -W -Wall -fmessage-length=0

	
