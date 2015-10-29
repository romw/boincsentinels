## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

SUFFIXES =

bin_PROGRAMS = hunter

hunter_SOURCES = \
	BOINCListCtrl.cpp \
	BOINCListCtrl.h \
	BOINCTaskCtrl.cpp \
	BOINCTaskCtrl.h \
	ConfigManager.cpp \
	ConfigManager.h \
	DlgConnection.cpp \
	DlgConnection.h \
	DlgEventLog.cpp \
	DlgEventLog.h \
	Hunter.cpp \
	Hunter.h \
	Events.h \
	Interface.cpp \
	Interface.h \
	LogManager.cpp \
	LogManager.h \
	SkinManager.cpp \
	SkinManager.h \
	Utils.cpp \
	Utils.h \
	ViewBase.cpp \
	ViewBase.h \
	ViewNotifications.cpp \
	ViewNotifications.h \
	ViewProjects.cpp \
	ViewProjects.h \
	ViewResources.cpp \
	ViewResources.h \
	ViewStatistics.cpp \
	ViewStatistics.h \
	ViewTasks.cpp \
	ViewTasks.h \
	ViewTransfers.cpp \
	ViewTransfers.h

hunter_DEPENDENCIES = $(LIBBSLCLIENT) $(LIBBSLCOMMON) $(LIBBSLXML) 
hunter_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CPPFLAGS) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
hunter_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CXXFLAGS) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
hunter_LDFLAGS = $(AM_LDFLAGS) -static-libgcc -static-libstdc++ -static 
hunter_LDADD = $(LIBBSLCLIENT_LIBS) $(LIBBSLCOMMON_LIBS) $(LIBBSLXML_LIBS) $(WX_LIBS_STATIC) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

hunter_LDFLAGS += -Wl,--subsystem,windows -mwindows 

endif


if OS_WIN64_MINGW

hunter_LDFLAGS += -Wl,--subsystem,windows -mwindows 

endif


if SUPPORTED_WINDOWS_RESOURCES 

SUFFIXES += .rc
hunter_SOURCES += \
	Hunter.rc

.rc.o:
	$(RC) -I=. $(WX_CPPFLAGS) $< -o $@

endif

EXTRA_DIST = \
	res 

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

