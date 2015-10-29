## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

SUFFIXES =

bin_PROGRAMS = vulture

vulture_SOURCES = \
	Vulture.cpp \
	Vulture.h 

vulture_DEPENDENCIES = $(LIBBSLCLIENT) $(LIBBSLCOMMON) $(LIBBSLXML) 
vulture_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CPPFLAGS) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
vulture_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CXXFLAGS) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
vulture_LDFLAGS = $(AM_LDFLAGS) -static-libgcc -static-libstdc++ -static $(LIBBSLCLIENT_LIBS) $(LIBBSLCOMMON_LIBS) $(LIBBSLXML_LIBS) $(WX_LIBS) $(PTHREAD_LIBS) 
vulture_LDADD = 


if OS_WIN32_MINGW

vulture_LDFLAGS += -Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

vulture_LDFLAGS += -Wl,--subsystem,console -mwindows 

endif


if SUPPORTED_WINDOWS_RESOURCES 

SUFFIXES += .rc
vulture_SOURCES += \
	Vulture.rc

.rc.o:
	$(RC) -I=. $(WX_CPPFLAGS) $< -o $@

endif

EXTRA_DIST = \
	res

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

