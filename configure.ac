# Autoconf requirements
# Force autoconf to be at least this version number:
AC_PREREQ([2.69])
# Initialize, but use more options.  Note parameters brackets and whitespace.
m4_define([permute_PACKAGE_NAME], [permute])
m4_define([permute_PACKAGE_BUGREPORT], [w7og@yahoo.com])
m4_define([permute_TAR_NAME], [permute])
m4_define([permute_URL], [http://www.kuras-pen.net/passwin])

AC_INIT(
	m4_defn([permute_PACKAGE_NAME]),
	[m4_esyscmd([build-aux/git-version-gen --fallback v2.1 .tarball-version])],
	m4_defn([permute_PACKAGE_BUGREPORT]),
	m4_defn([permute_TAR_NAME]),
	m4_defn([permute_URL])
)

AC_CANONICAL_TARGET
# AC_CANONICAL_HOST is needed to access the 'host_os' variable
AC_CANONICAL_HOST

# Put autotools auxiliary files in a subdir, so they don't clutter top dir:
AC_CONFIG_AUX_DIR([build-aux])

# Enable "automake" to simplify creating makefiles:
AM_INIT_AUTOMAKE([
	1.11
	readme-alpha
	subdir-objects
	-Wall -Werror
])

# Put configuration results here, so we can easily #include them:
AC_CONFIG_HEADERS([config.h:config.in])

# Safety check - list a source file that wouldn't be in other directories:
AC_CONFIG_SRCDIR([src/permute.cpp])

AC_CONFIG_MACRO_DIR([m4])

# Look for a C compiler:
AC_PROG_CC([gcc cl cc])

dnl Since we use gnulib: gl_EARLY must be called as soon as possible after
dnl the C compiler is checked.  The others could be later, but we just
dnl keep everything together.
#gl_EARLY
#gl_INIT

dnl Are we building from git checked-out sources, or a tarball ?
dnl This is used in "Makefile.am" to avoid re-generating the manpage
dnl when building from tarballs.
AM_CONDITIONAL([BUILD_FROM_GIT], [test -d "$srcdir/.git"])
AM_CONDITIONAL([GIT_CROSS_COMPILING],
               [test -d "$srcdir/.git" && test $cross_compiling = yes])

dnl GNU help2man creates man pages from --help output; in many cases, this
dnl is sufficient, and obviates the need to maintain man pages separately.
dnl However, this means invoking executables, which we generally cannot do
dnl when cross-compiling, so we test to avoid that (the variable
dnl "cross_compiling" is set by AC_PROG_CC).
AS_IF([test $cross_compiling = no], [
  AM_MISSING_PROG([HELP2MAN], [help2man])
], [
  HELP2MAN=:
])

dnl Ensure VLAs are not used.
AC_DEFINE([GNULIB_NO_VLA], [1], [Define to 1 to disable use of VLAs])

# Gettext.
AM_GNU_GETTEXT_VERSION([0.21])
AM_GNU_GETTEXT([external], [need-formatstring-macros])

AC_CONFIG_TESTDIR(tests)

# other files to creat
#AC_CONFIG_FILES([tests/m4], [chmod +x tests/m4])
#AC_CONFIG_FILES([src/Makefile tests/Makefile tests/atlocal man/Makefile])
AC_CONFIG_FILES([Makefile
	m4/Makefile
	build-aux/Makefile
	tests/Makefile
	tests/atlocal
	po/Makefile.in
	src/Makefile
	man/Makefile
])


PERMUTE_TESTSUITES="core"
AC_SUBST([PERMUTE_TESTSUITES])

build_linux=no
build_windows=no
build_freebsd=no
build_darwin=no

# Detect the target system
case "${host_os}" in
    linux*)
        build_linux=yes
        ;;
    cygwin*|mingw*)
        build_windows=yes
        ;;
    freebsd*)
        build_freebsd=yes
        ;;
    darwin*)
        build_darwin=yes
        ;;
    *)
        AC_MSG_ERROR(["OS $host_os is not supported"])
        ;;
esac

# Pass the conditionals to automake
AM_CONDITIONAL([LINUX], [test "$build_linux" = "yes"])
AM_CONDITIONAL([WINDOWS], [test "$build_windows" = "yes"])
AM_CONDITIONAL([FREEBSD], [test "$build_freebsd" = "yes"])
AM_CONDITIONAL([DARWIN], [test "$build_darwin" = "yes"])

# see GNU autoconf archive = perdefined macros
if test "$build_linux" = "yes"; then
AX_GENERATE_CHANGELOG
fi

# Set C compiler options:
AC_PROG_CXX
AM_PROG_AS
AC_PROG_INSTALL
AC_PROG_CPP
AC_PROG_AWK
#AC_PROG_LN_S
#AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AM_PROG_CC_C_O
AC_C_BIGENDIAN

permute_version_1=`echo $PACKAGE_VERSION | cut -d . -f 1`
permute_version_2=`echo $PACKAGE_VERSION | cut -d . -f 2`
permute_version_3=`echo $PACKAGE_VERSION | cut -d . -f 3`
permute_version=$permute_version_1.$permute_version_2.$permute_version_3
AC_DEFINE_UNQUOTED(PERMUTE_VERSION,  "$permute_version",  [ PERMUTE version string.  ])
AC_DEFINE_UNQUOTED(PERMUTE_VERSION_1, $permute_version_1, [ PERMUTE version level 1. ])
AC_DEFINE_UNQUOTED(PERMUTE_VERSION_2, $permute_version_2, [ PERMUTE version level 2. ])
AC_DEFINE_UNQUOTED(PERMUTE_VERSION_3, $permute_version_3, [ PERMUTE version level 3. ])
AC_SUBST(PERMUTE_VERSION, $permute_version)
# Perhaps check for: (more) programs, libraries, header files, types,
# structures, compiler characteristics, library functions, system services.

# Checks for libraries.

#PKG_CHECK_MODULES([],[])

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdint.h ctype.h stdlib.h stdio.h string.h unistd.h getopt.h])
# Checks for typedefs, structures, macros, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for compiler characteristics.
AC_C_CONST
AC_C_INLINE

AC_DEFINE(_GNU_SOURCE, 1, [ Define to enable GNU extensions in glibc ])
AC_HEADER_STDC

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_CHECK_FUNCS([ printf fprintf atoi __FUNC__ __FUNCTION__])
AC_CHECK_FUNCS([getopt_long],,
  [ # FreeBSD has a "gnugetopt" library.
    AC_CHECK_LIB([gnugetopt], [getopt_long],
                 [ AC_DEFINE([HAVE_GETOPT_LONG]) ]) ])


# Options
AC_ARG_ENABLE(debug,
  AC_HELP_STRING(
    [--enable-debug],
    [enable development-time debugging @<:@default=disabled@:>@]),
  [ permute_debug="$enableval" ],
  [ permute_debug="no" ])
if test "$permute_debug" = "yes"; then
  AM_CONDITIONAL(DEBUG, true)
  AC_DEFINE(DEBUG, 1,
    [ Define if you want permute to print debug messages to stdout. ])
  CFLAGS="$CFLAGS -g"
else
  AM_CONDITIONAL(DEBUG, false)
  AC_DEFINE(NDEBUG, 1, [ Define if you want to disable debug assertions. ])
  CFLAGS="$CFLAGS -g -O2"
  CXXFLAGS="-g -O2"
fi

AC_ARG_ENABLE(profile,
  AC_HELP_STRING([--enable-profile],
                 [enable profiling with gprof @<:@default=disabled@:>@]),
  [ permute_profile="$enableval" ],
  [ permute_profile="no" ])
if test "$permute_profile" = "yes"; then
  CFLAGS="$CFLAGS -pg"
  AM_CONDITIONAL(PERMUTE_PROFILE, true)
else
  AM_CONDITIONAL(PERMUTE_PROFILE, false)
fi

AC_ARG_ENABLE(warnings,
  AC_HELP_STRING(
    [--disable-warnings],
    [disable C compiler warning messages @<:@default=enabled@:>@]),
  [ permute_cc_warnings="$enableval" ],
  [ permute_cc_warnings="yes" ])
if test "$permute_cc_warnings" = "yes"; then
  VL_PROG_CC_WARNINGS()
  AM_CONDITIONAL(PERMUTE_WARNINGS, true)
else
  AM_CONDITIONAL(PERMUTE_WARNINGS, false)
fi

# check the permute compile defines

AC_ARG_ENABLE(windoze,
  AC_HELP_STRING(
    [--enable-windoze],
    [enable Windows code @<:@default=disabled@:>@]),
  [ permute_windoze="$enableval" ],
  [ permute_windoze="no" ])
if test "$permute_windoze" = "yes"; then
  AM_CONDITIONAL(WINDOZE, true)
  AC_DEFINE(WINDOZE, 1,
    [ Define if you wish to generate code for the Microsoft Windows gui. ])
else
  AM_CONDITIONAL(WINDOZE, false)
fi

AC_ARG_ENABLE(win32,
  AC_HELP_STRING(
    [--enable-win32],
    [enable Win32 support @<:@default=disabled@:>@]),
  [ permute_win32="$enableval" ],
  [ permute_win32="no" ])
if test "$permute_win32" = "yes"; then
  AM_CONDITIONAL(WIN32, true)
  AC_DEFINE(WIN32, 1,
    [ Define if you are using an older Windows (XT) Microsoft C compiler. ])
else
  AM_CONDITIONAL(WIN32, false)
fi

AC_SYS_LARGEFILE

#AC_LIBTOOL_TAGS([])
#AC_LIBTOOL_WIN32_DLL
AM_PROG_AR
LT_INIT([disable-shared])
AC_SUBST([LIBTOOL_DEPS])
#AC_PROG_LIBTOOL


# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

MY_CPPFLAGS=""
AC_SUBST(MY_CPPFLAGS)

# Do final output.
AC_OUTPUT


# Print configuration summary
#myPACKAGE_VERSION: $PACKAGE_VERSION
#version: $PERMUTE_VERSION, $PERMUTE_VERSION_1, $PERMUTE_VERSION_2, $PERMUTE_VERSION_3
#myPACKAGE_NAME: m4_defn([permute_PACKAGE_NAME])

cat <<EOF


Configuration summary
=====================

Building for $host_os

permute is now configured as follows:

* Compilation environment

  CC       = $CC
  CFLAGS   = $CFLAGS
  CPP      = $CPP
  CPPFLAGS = $CPPFLAGS
  LD       = $LD
  LDFLAGS  = $LDFLAGS
  LIBS     = $LIBS

* permute options

  Development-time debugging:		$permute_debug
  Compile for Windows gui:		$permute_windoze
  Compile for older Windows XT:		$permute_win32

EOF
