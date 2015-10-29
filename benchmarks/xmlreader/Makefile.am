## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

bin_PROGRAMS = xmlreader

xmlreader_SOURCES = \
	XMLBenchmarksMain.cpp \
	BOINCNativeParsers.cpp \
	BOINCNativeParsers.h \
	BOINCNativeTaskInstance.cpp \
	BOINCNativeTaskInstance.h \
	BOINCParsers.cpp \
	BOINCParsers.h \
	BOINCSentinelsParserEx.cpp \
	BOINCSentinelsParserEx.h \
	BOINCXMLStream.cpp \
	BOINCXMLStream.h \
	LookupTables.h


xmlreader_DEPENDENCIES = $(LIBBSLXML) $(LIBBSLCOMMON) 
xmlreader_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
xmlreader_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
xmlreader_LDFLAGS = $(AM_LDFLAGS) -static $(LIBBSLXML_LIBS) $(LIBBSLCOMMON_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

xmlreader_LDFLAGS += -Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

xmlreader_LDFLAGS += -Wl,--subsystem,console -mwindows 

endif


TESTS = xmlreader


CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov
