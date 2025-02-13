## Process this file with automake to produce Makefile.in

#SUBDIRS = build-aux
#AC_CONFIG_AUX_DIR = build-aux

ACLOCAL_AMFLAGS = -I m4 --install

AM_CPPFLAGS = $(DEPS_CFLAGS) $(MY_CPPFLAGS) -Ilib -I$(top_srcdir)/lib -Isrc -I$(top_srcdir)/src
AM_CXXFLAGS = -W -Wall -fmessage-length=0

# Additional files to distribute.
EXTRA_DIST = $(top_srcdir)/.version \
	m4/Makefile.in \
	build-aux/Makefile.in \
	build-aux/git-version-gen \
	build-aux/gitlog-to-changelog \
	man/permute.x \
	dodeb.sh \
	README.md \
	BUILD \
	gengitver.sh \
	tests/m4/atenv.m4
	
# Subdirectories to descend into.
SUBDIRS= src tests man po

CLEANFILES =
MAINTAINERCLEANFILES =

noinst_LIBRARIES =
MOSTLYCLEANFILES =
MOSTLYCLEANDIRS =
BUILT_SOURCES = $(top_srcdir)/.version

$(top_srcdir)/.version:
	echo '$(VERSION)' > $@-t
	mv $@-t $@

LOG_COMPILER = $(SHELL)

TESTS_ENVIRONMENT = \
  top_srcdir=$(top_srcdir) \
  PATH=.$(PATH_SEPARATOR)$(PATH_SEPARATOR)$$PATH \
  PERMUTE=`echo permute | sed '$(transform)'`; \
  export PERMUTE PATH top_srcdir;

include $(top_srcdir)/doc/local.mk

dist-hook: gen-ChangeLog
	chmod u+w $(distdir)/$(man_MANS)
	echo '$(VERSION)' > $(distdir)/.tarball-version

gen_start_date = 2011-12-17
.PHONY: gen-ChangeLog
gen-ChangeLog:
	$(AM_V_GEN)if test -d .git; then				\
	  log_fix="$(srcdir)/build-aux/git-log-fix";			\
	  test -e "$$log_fix"						\
	    && amend_git_log="--amend=$$log_fix"			\
	    || amend_git_log=;						\
	  $(top_srcdir)/build-aux/gitlog-to-changelog			\
	    $$amend_git_log --since=$(gen_start_date) > $(distdir)/cl-t && \
	    { rm -f $(distdir)/ChangeLog &&				\
	      mv $(distdir)/cl-t $(distdir)/ChangeLog; }		\
	fi





distclean-local:
	@rm -r autom4te.cache/
	@rm aclocal.m4

help:
	-@echo "make                    --> build permute"
	-@echo "make clean              --> delete what was built"
	-@echo "make distclean          --> delete auto tools products"
	-@echo "make dist               --> build distribution package"


	
