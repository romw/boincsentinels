## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

bin_PROGRAMS = parseperf

parseperf_SOURCES = \
	ParsePerfMain.cpp \
	TaskInstancePerf.cpp \
	TaskInstancePerf.h


parseperf_DEPENDENCIES = $(LIBBSLXML) $(LIBBSLCOMMON) 
parseperf_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(CPPUNIT_CFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
parseperf_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(CPPUNIT_CFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
parseperf_LDFLAGS = $(AM_LDFLAGS) -static $(LIBBSLXML_LIBS) $(LIBBSLCOMMON_LIBS) $(CPPUNIT_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

parseperf_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

parseperf_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


TESTS = parseperf


CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov
