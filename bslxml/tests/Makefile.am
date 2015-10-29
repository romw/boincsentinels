## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

bin_PROGRAMS = bslxml_tests

bslxml_tests_SOURCES = \
	bslXMLTestMain.cpp \
	bslXMLAttributeExTest.cpp \
	bslXMLAttributeExTest.h \
	bslXMLDictionaryExTest.cpp \
	bslXMLDictionaryExTest.h \
	bslXMLDocumentExTest.cpp \
	bslXMLDocumentExTest.h \
	bslXMLElementExTest.cpp \
	bslXMLElementExTest.h


bslxml_tests_DEPENDENCIES = $(LIBBSLXML) 
bslxml_tests_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLXML_CPPFLAGS) $(CPPUNIT_CFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
bslxml_tests_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLXML_CXXFLAGS) $(CPPUNIT_CFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
bslxml_tests_LDFLAGS = $(AM_LDFLAGS) -static $(LIBBSLXML_LIBS) $(CPPUNIT_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

bslxml_tests_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

bslxml_tests_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


TESTS = bslxml_tests


CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov \
	*.xml

