## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

SUFFIXES =

bin_PROGRAMS = lancer

lancer_SOURCES = \
	Lancer.cpp \
	Lancer.h \
	Events.h \
	LogManager.cpp \
	LogManager.h \

lancer_DEPENDENCIES = $(LIBBSLCLIENT) $(LIBBSLCOMMON) $(LIBBSLXML) 
lancer_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CPPFLAGS) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
lancer_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CXXFLAGS) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
lancer_LDFLAGS = $(AM_LDFLAGS) -static-libgcc -static-libstdc++ -static 
lancer_LDADD = $(LIBBSLCLIENT_LIBS) $(LIBBSLCOMMON_LIBS) $(LIBBSLXML_LIBS) $(WX_LIBS_STATIC) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

lancer_LDFLAGS += -Wl,--subsystem,windows -mwindows 

endif


if OS_WIN64_MINGW

lancer_LDFLAGS += -Wl,--subsystem,windows -mwindows 

endif


if SUPPORTED_WINDOWS_RESOURCES 

SUFFIXES += .rc
lancer_SOURCES += \
	lancerResource.rc

.rc.o:
	$(RC) -I=. $(WX_CPPFLAGS) $< -o $@

endif

EXTRA_DIST = \
	res 

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

