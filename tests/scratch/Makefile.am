## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

bin_PROGRAMS = scratch

scratch_SOURCES = \
	ScratchMain.cpp


scratch_DEPENDENCIES = $(LIBBSLXML) $(LIBBSLCOMMON) 
scratch_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(CPPUNIT_CFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
scratch_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(CPPUNIT_CFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
scratch_LDFLAGS = $(AM_LDFLAGS) -static $(LIBBSLXML_LIBS) $(LIBBSLCOMMON_LIBS) $(CPPUNIT_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

scratch_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

scratch_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


TESTS = scratch


CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov
