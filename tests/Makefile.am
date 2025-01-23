##
##  passwin
##
##  Created by dad on Apr 28, 2023
##  Copyright (c) 22023 John Kuras
##

MAINTAINERCLEANFILES    = Makefile.in

testsubdir              = testSubDir

TESTS_ENVIRONMENT       = top_builddir=$(top_builddir)

#TESTSUITEFLAGS=-k

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	:;{ \
	  echo '# Signature of the current package.' && \
	  echo 'm4_define([AT_PACKAGE_NAME],' && \
	  echo '  [$(PACKAGE_NAME)])' && \
	  echo 'm4_define([AT_PACKAGE_TARNAME],' && \
	  echo '  [$(PACKAGE_TARNAME)])' && \
	  echo 'm4_define([AT_PACKAGE_VERSION],' && \
	  echo '  [$(PACKAGE_VERSION)])' && \
	  echo 'm4_define([AT_PACKAGE_STRING],' && \
	  echo '  [$(PACKAGE_STRING)])' && \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
	  echo '  [$(PACKAGE_BUGREPORT)])'; \
	  echo 'm4_define([AT_PACKAGE_URL],' && \
	  echo '  [$(PACKAGE_URL)])'; \
	} >'$(srcdir)/package.m4'

TESTSUITES_SRC = $(srcdir)/testsuite.at

EXTRA_DIST = $(TESTSUITES_SRC) $(srcdir)/package.m4 $(TESTSUITE) $(INSTTESTSUITE) atlocal.in

TESTSUITE = $(srcdir)/testsuite

DISTCLEANFILES = atconfig

check-local: atconfig atlocal $(TESTSUITE)
	+$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)

#installcheck-local: atconfig atlocal $(INSTTESTSUITE)
#	+$(SHELL) '$(INSTTESTSUITE)' AUTOTEST_PATH='$(bindir):..' \
#	$(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
	$(SHELL) '$(TESTSUITE)' --clean


distclean-local:
	-rm -rf $(testsubdir)


AUTOM4TE = $(SHELL) $(top_srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest 

$(TESTSUITE): $(TESTSUITES_SRC) $(srcdir)/package.m4 $(srcdir)/m4/atenv.m4
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@





