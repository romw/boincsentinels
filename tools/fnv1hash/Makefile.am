## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

bin_PROGRAMS = fnv1hash

fnv1hash_SOURCES = \
	fnv1hash.cpp 


fnv1hash_DEPENDENCIES = $(LIBBSLXML) $(LIBBSLCOMMON) 
fnv1hash_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
fnv1hash_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
fnv1hash_LDFLAGS = $(AM_LDFLAGS) -static-libgcc -static-libstdc++ -static $(LIBBSLXML_LIBS) $(LIBBSLCOMMON_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

fnv1hash_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

fnv1hash_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov
