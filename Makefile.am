## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

## make sure rebuilding uses the right aclocal-switches
ACLOCAL_AMFLAGS = -I m4

SUBDIRS =  

if SUPPORTED_PRECOMPILED_HEADER
SUBDIRS += include
endif

# ORDER MATTERS below.  One must build dependencies FIRST, then things
# that depend on them later
SUBDIRS += m4 bslxml bslcommon bslclient hunter valkyrie vulture

if ENABLE_TESTS
SUBDIRS += tests
endif

SUBDIRS += tools benchmarks

EXTRA_DIST = autogen.sh
