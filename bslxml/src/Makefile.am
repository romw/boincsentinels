## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

lib_LTLIBRARIES = libbslxml.la

# Package Info Installation
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ../bslxml.pc

# Public Headers
library_includedir=$(includedir)/bslxml-$(BOINCSENTINELS_VERSION_MAJOR).$(BOINCSENTINELS_VERSION_MINOR)/bslxml
library_include_HEADERS = \
	../include/bslxml/bslXMLAttributeEx.h \
	../include/bslxml/bslXMLConverterEx.h \
	../include/bslxml/bslXMLDictionaryEx.h \
	../include/bslxml/bslXMLDocumentEx.h \
	../include/bslxml/bslXMLElementEx.h \
	../include/bslxml/bslXMLTestUtil.h \
	../include/bslxml/bslXMLTypes.h \
	../include/bslxml/bslXMLUtil.h

libbslxml_la_SOURCES = \
    bslStrChr.cpp \
    bslStrHash.cpp \
	bslXMLAttributeEx.cpp \
	bslXMLConverterEx.cpp \
	bslXMLDictionaryEx.cpp \
	bslXMLDocumentEx.cpp \
	bslXMLElementEx.cpp \
	bslXMLTestUtil.cpp \
	FNV1Hash.h \
	LookupTables.cpp \
	LookupTables.h

libbslxml_la_CPPFLAGS = $(AM_CPPFLAGS) $(PICFLAGS) $(PROJECTINCLUDE) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CFLAGS)
libbslxml_la_CXXFLAGS = $(AM_CXXFLAGS) $(PICFLAGS) $(PROJECTINCLUDE) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CFLAGS)
libbslxml_la_LDFLAGS = -version-info $(BOINCSENTINELS_VERSION_MAJOR):$(BOINCSENTINELS_VERSION_MINOR):0 

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

