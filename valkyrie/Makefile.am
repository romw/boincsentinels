## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

SUFFIXES =

bin_PROGRAMS = valkyrie

valkyrie_SOURCES = \
	ClientPage.cpp \
	ClientPage.h \
	ConfigManager.cpp \
	ConfigManager.h \
	DlgActiveTask.cpp \
	DlgActiveTask.h \
	DlgActiveTransfer.cpp \
	DlgActiveTransfer.h \
	DlgConnection.cpp \
	DlgConnection.h \
	DlgControls.cpp \
	DlgControls.h \
	DlgEventLog.cpp \
	DlgEventLog.h \
	DlgNotification.cpp \
	DlgNotification.h \
	DlgNotifications.cpp \
	DlgNotifications.h \
	Events.h \
	Interface.cpp \
	Interface.h \
	LogManager.cpp \
	LogManager.h \
	NotificationManager.cpp \
	NotificationManager.h \
	SkinManager.cpp \
	SkinManager.h \
	StatusPage.cpp \
	StatusPage.h \
	Utils.cpp \
	Utils.h \
	Valkyrie.cpp \
	Valkyrie.h \
	WidgetActiveTask.cpp \
	WidgetActiveTask.h \
	WidgetActiveTasks.cpp \
	WidgetActiveTasks.h \
	WidgetActiveTransfer.cpp \
	WidgetActiveTransfer.h \
	WidgetActiveTransfers.cpp \
	WidgetActiveTransfers.h \
	WidgetBase.cpp \
	WidgetBase.h \
	WidgetControls.cpp \
	WidgetControls.h \
	WidgetEventLog.cpp \
	WidgetEventLog.h \
	WidgetNews.cpp \
	WidgetNews.h \
	WidgetProject.cpp \
	WidgetProject.h \
	WidgetProjects.cpp \
	WidgetProjects.h \
	WidgetStatus.cpp \
	WidgetStatus.h \
	WidgetUsage.cpp \
	WidgetUsage.h 

valkyrie_DEPENDENCIES = $(LIBBSLCLIENT) $(LIBBSLCOMMON) $(LIBBSLXML) 
valkyrie_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CPPFLAGS) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
valkyrie_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CXXFLAGS) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
valkyrie_LDFLAGS = $(AM_LDFLAGS) -static-libgcc -static-libstdc++ -static 
valkyrie_LDADD = $(LIBBSLCLIENT_LIBS) $(LIBBSLCOMMON_LIBS) $(LIBBSLXML_LIBS) $(WX_LIBS_STATIC) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

valkyrie_LDFLAGS += -Wl,--subsystem,windows -mwindows 

endif


if OS_WIN64_MINGW

valkyrie_LDFLAGS += -Wl,--subsystem,windows -mwindows 

endif


if SUPPORTED_WINDOWS_RESOURCES 

SUFFIXES += .rc
valkyrie_SOURCES += \
	Valkyrie.rc

.rc.o:
	$(RC) -I=. $(WX_CPPFLAGS) $< -o $@

endif

EXTRA_DIST = \
	res 

CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov

