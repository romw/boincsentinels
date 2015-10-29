## -*- mode: makefile; tab-width: 4 -*-

AC_INIT([BOINC-Sentinels],[1.0.1],[boinc-sentinels-bug@lists.romwnet.org],[boinc-sentinels],[https://projects.romwnet.org/boincsentinels])
AC_PREREQ([2.63])
AC_REVISION($Revision$)
AC_COPYRIGHT([Copyright (c) 2009-2013 BOINC Sentinels Development Team])


# Checks for options
AM_OPTIONS_WXCONFIG

AC_ARG_ENABLE(
	[debug],
	AS_HELP_STRING([--enable-debug],
				   [enable building with debug support]),
	[enable_debug="yes"],
	[enable_debug="no"]
)

AC_ARG_ENABLE(
	[gprof],
	AS_HELP_STRING([--enable-gprof],
				   [build binaries with gprof support]),
	[enable_gprof="yes"],
	[enable_gprof="no"]
)

AC_ARG_ENABLE(
    [gcov],
    AS_HELP_STRING([--enable-gcov],
                   [build binaries with gcov support]),
    [enable_gcov="yes"],
    [enable_gcov="no"]
)


# Determine platform information
AC_CANONICAL_TARGET

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([bslcommon/include/bslcommon/bslCommonTypes.h])
AM_INIT_AUTOMAKE(dist-bzip2 dist-zip)

# Reduce output spew
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Store tree information for later use
AC_DEFINE(BOINCSENTINELS_BRANCH, ["$URL$"], [The branch used to build the software])
AC_DEFINE(BOINCSENTINELS_ID, ["$Id$"], [The date/time when the software was archived])

AC_SUBST([BOINCSENTINELS_BRANCH], "$URL$")
AC_SUBST([BOINCSENTINELS_ID], "$Id$")

# Autoconf version helper functions
AC_DEFUN([STRIP_LEADING_ZEROS],[m4_bregexp([$*],[^0*\(..*\)],\1)])
AC_DEFUN([SETVERSION],[
AC_SUBST([SETVERSION_MAJOR],  STRIP_LEADING_ZEROS([$1]))
AC_SUBST([SETVERSION_MINOR],  STRIP_LEADING_ZEROS([$2]))
AC_SUBST([SETVERSION_BUILD],  STRIP_LEADING_ZEROS([$3]))
AC_SUBST([SETVERSION_STRING], ["$1.$2.$3"])
])

# Store component parts of the version number in seperate defines
SETVERSION(translit(AC_PACKAGE_VERSION, [.], [,]))

AC_DEFINE_UNQUOTED([BOINCSENTINELS_VERSION_MAJOR], $SETVERSION_MAJOR, [Major part of BOINC Sentinels version number])
AC_DEFINE_UNQUOTED([BOINCSENTINELS_VERSION_MINOR], $SETVERSION_MINOR, [Minor part of BOINC Sentinels version number])
AC_DEFINE_UNQUOTED([BOINCSENTINELS_VERSION_BUILD], $SETVERSION_BUILD, [Build part of BOINC Sentinels version number])
AC_DEFINE_UNQUOTED([BOINCSENTINELS_VERSION], "$SETVERSION_STRING", [String representation of BOINC Sentinels version number])

AC_SUBST([BOINCSENTINELS_VERSION_MAJOR], "$SETVERSION_MAJOR")
AC_SUBST([BOINCSENTINELS_VERSION_MINOR], "$SETVERSION_MINOR")
AC_SUBST([BOINCSENTINELS_VERSION_BUILD], "$SETVERSION_BUILD")
AC_SUBST([BOINCSENTINELS_VERSION], "$SETVERSION_STRING")

# Store components parts of the version number of BOINC we are compatible with
SETVERSION(translit([6.13.8], [.], [,]))

AC_DEFINE_UNQUOTED([BOINCCOMPAT_VERSION_MAJOR], $SETVERSION_MAJOR, [Major part of BOINC version number we are compatible with])
AC_DEFINE_UNQUOTED([BOINCCOMPAT_VERSION_MINOR], $SETVERSION_MINOR, [Minor part of BOINC version number we are compatible with])
AC_DEFINE_UNQUOTED([BOINCCOMPAT_VERSION_RELEASE], $SETVERSION_BUILD, [Release part of BOINC version number we are compatible with])
AC_DEFINE_UNQUOTED([BOINCCOMPAT_VERSION], "$SETVERSION_STRING", [String representation of BOINC version number we are compatible with])

AC_SUBST([BOINCCOMPAT_VERSION_MAJOR], "$SETVERSION_MAJOR")
AC_SUBST([BOINCCOMPAT_VERSION_MINOR], "$SETVERSION_MINOR")
AC_SUBST([BOINCCOMPAT_VERSION_RELEASE], "$SETVERSION_BUILD")
AC_SUBST([BOINCCOMPAT_VERSION], "$SETVERSION_STRING")

# Setup alternate OS specific stuff
AM_CONDITIONAL(OS_LINUX, [echo $host_os | grep '^linux' > /dev/null])
AM_CONDITIONAL(OS_WIN32_MINGW, [echo $host_os | grep '^mingw32' > /dev/null])
AM_CONDITIONAL(OS_WIN64_MINGW, [echo $host_os | grep '^mingw32' > /dev/null] && [echo $host_os | grep '^x86_64' > /dev/null])

# Check for precompiled header support
AM_CONDITIONAL(SUPPORTED_PRECOMPILED_HEADER, [echo $host_os | grep '^linux' > /dev/null] || [echo $host_os | grep '^mingw32' > /dev/null])

# Check for precompiled header support
AM_CONDITIONAL(SUPPORTED_WINDOWS_RESOURCES, [echo $host_os | grep '^mingw32' > /dev/null])


# Checks for programs.
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AS
AM_PROG_CC_C_O


# Check for libtool
AC_PROG_LIBTOOL
AC_LIBTOOL_WIN32_DLL
AC_LIBTOOL_RC


# Enable debugging suport.
AC_MSG_CHECKING(for whether debugging should be enabled)
AM_CONDITIONAL(ENABLE_DEBUG, test "$enable_debug" = "yes")
if test "$enable_debug" = "yes"; then
  CFLAGS="$CFLAGS -g -O0"
  CXXFLAGS="$CXXFLAGS -g -O0"
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
fi


# Enable profiling suport.
AC_MSG_CHECKING(for whether profiling should be enabled)
AM_CONDITIONAL(ENABLE_GPROF, test "$enable_gprof" = "yes")
if test "$enable_gprof" = "yes"; then
  CFLAGS="$CFLAGS -pg"
  CXXFLAGS="$CXXFLAGS -pg"
  LDFLAGS="$LDFLAGS -pg"
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
fi


# Enable code coverage suport.
AC_MSG_CHECKING(for whether code coverage should be enabled)
AM_CONDITIONAL(ENABLE_GCOV, test "$enable_gcov" = "yes")
if test "$enable_gcov" = "yes"; then
  CFLAGS="$CFLAGS -coverage"
  CXXFLAGS="$CXXFLAGS -coverage"
  LDFLAGS="$LDFLAGS -coverage"
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
fi


# Checks for wxWidgets libraries.
AM_PATH_WXCONFIG([2.8.10], [libwxWidgets="yes"], [libwxWidgets="no"], --unicode=yes --debug=$enable_debug)
AM_CONDITIONAL(ENABLE_WXWIDGETS, test "$libwxWidgets" = "yes")
if test "$libwxWidgets" != "yes"; then
	AC_MSG_ERROR([
		wxWidgets must be installed on your system.

		Please check that wx-config is in path, the directory
		where wxWidgets libraries are installed (returned by
		'wx-config --libs' or 'wx-config --static --libs' command)
		is in LD_LIBRARY_PATH or equivalent variable and
		wxWidgets version is 2.8.10 or above.
	])
fi


# Checks for CPPUnit libraries.
AM_PATH_CPPUNIT([1.12.0], [libCPPUnit="yes"], [libCPPUnit="no"])
AM_CONDITIONAL(ENABLE_TESTS, test "$libCPPUnit" = "yes")
if test "$libCPPUnit" != "yes"; then
	AC_MSG_WARN([
		CPPUnit must be installed on your system to build unit tests.

		Please check that cppunit-config is in path, the directory
		where CPPUnit libraries are installed is in LD_LIBRARY_PATH
		or equivalent variable and CPPUnit version is 1.12.0 or above.
	])
fi


# Components
AC_CONFIG_FILES([
     m4/Makefile
     include/Makefile
     include/bslversion.h
     bslxml/Makefile
     bslxml/src/Makefile
     bslxml/tests/Makefile
     bslxml/bslxml.pc
     bslcommon/Makefile
     bslcommon/src/Makefile
     bslcommon/tests/Makefile
     bslcommon/bslcommon.pc
     bslclient/Makefile
     bslclient/src/Makefile
     bslclient/tests/Makefile
     bslclient/bslclient.pc
     hunter/Makefile
     valkyrie/Makefile
     vulture/Makefile
     tests/Makefile
     tests/parseperf/Makefile
     tests/scratch/Makefile
     tools/Makefile
     tools/fnv1hash/Makefile
     benchmarks/xmlreader/Makefile
     benchmarks/Makefile
     Makefile
])


# Dump output
AC_CONFIG_HEADERS([bsconfig.h])
AC_OUTPUT
