/* Platform independent version definitions... */

#ifndef BOINCSENTINELS_VERSION_H
#define BOINCSENTINELS_VERSION_H

#if (defined(_WIN32) || defined(__APPLE__))

/* String representation of BOINC version number we are compatible with */
#define BOINCCOMPAT_VERSION "6.13.8"

/* Major part of BOINC version number we are compatible with */
#define BOINCCOMPAT_VERSION_MAJOR 6

/* Minor part of BOINC version number we are compatible with */
#define BOINCCOMPAT_VERSION_MINOR 13

/* Release part of BOINC version number we are compatible with */
#define BOINCCOMPAT_VERSION_RELEASE 8

/* The branch used to build the software */
#define BOINCSENTINELS_BRANCH ": https://projects.romwnet.org/boincsentinels-svn/trunk/configure.ac $"

/* The date/time when the software was archived */
#define BOINCSENTINELS_ID ": configure.ac 627 2013-12-19 17:45:36Z romw $"

/* String representation of BOINC Sentinels version number */
#define BOINCSENTINELS_VERSION "1.0.1"

/* Build part of BOINC Sentinels version number */
#define BOINCSENTINELS_VERSION_BUILD 1

/* Major part of BOINC Sentinels version number */
#define BOINCSENTINELS_VERSION_MAJOR 1

/* Minor part of BOINC Sentinels version number */
#define BOINCSENTINELS_VERSION_MINOR 0

/* Name of package */
#define PACKAGE "boinc-sentinels"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "boinc-sentinels-bug@lists.romwnet.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "BOINC-Sentinels"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "BOINC-Sentinels 1.0.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "boinc-sentinels"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.0.1"

/* Define to the URL of this package. */
#define PACKAGE_URL "https://projects.romwnet.org/boincsentinels"

#else /* #if (defined(_WIN32) || defined(__APPLE__)) */

#include "../bsconfig.h"

#endif

#endif
