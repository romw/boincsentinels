## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

lib_LTLIBRARIES = libbslcommon.la

# Package Info Installation
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ../bslcommon.pc

# Public Headers
library_includedir=$(includedir)/bslcommon-$(BOINCSENTINELS_VERSION_MAJOR).$(BOINCSENTINELS_VERSION_MINOR)/bslcommon
library_include_HEADERS = \
	../include/bslcommon/bslApp.h \
	../include/bslcommon/bslAppEvents.h \
	../include/bslcommon/bslAppVersion.h \
	../include/bslcommon/bslAppVersionEvents.h \
	../include/bslcommon/bslCommonTypes.h \
	../include/bslcommon/bslEventBase.h \
	../include/bslcommon/bslErrors.h \
	../include/bslcommon/bslHandles.h \
	../include/bslcommon/bslHostCoprocAMD.h \
	../include/bslcommon/bslHostCoprocNvidia.h \
	../include/bslcommon/bslHostCoprocOpenCL.h \
	../include/bslcommon/bslHost.h \
	../include/bslcommon/bslHostEvents.h \
	../include/bslcommon/bslHostStatus.h \
	../include/bslcommon/bslHostStatusEvents.h \
	../include/bslcommon/bslMessage.h \
	../include/bslcommon/bslMessageEvents.h \
	../include/bslcommon/bslNotification.h \
	../include/bslcommon/bslNotificationEvents.h \
	../include/bslcommon/bslProject.h \
	../include/bslcommon/bslProjectEvents.h \
	../include/bslcommon/bslProjectLink.h \
	../include/bslcommon/bslProjectListItem.h \
	../include/bslcommon/bslProjectListItemEvents.h \
	../include/bslcommon/bslProjectStatistic.h \
	../include/bslcommon/bslProjectStatisticEvents.h \
	../include/bslcommon/bslTask.h \
	../include/bslcommon/bslTaskEvents.h \
	../include/bslcommon/bslTaskInstance.h \
	../include/bslcommon/bslTaskInstanceEvents.h \
	../include/bslcommon/bslTransfer.h \
	../include/bslcommon/bslTransferEvents.h

libbslcommon_la_SOURCES = \
	bslApp.cpp \
	bslAppEvents.cpp \
	bslAppVersion.cpp \
	bslAppVersionEvents.cpp \
	bslEventBase.cpp \
	bslHostCoprocAMD.cpp \
	bslHostCoprocNvidia.cpp \
	bslHostCoprocOpenCL.cpp \
	bslHost.cpp \
	bslHostEvents.cpp \
	bslHostStatus.cpp \
	bslHostStatusEvents.cpp \
	bslMessage.cpp \
	bslMessageEvents.cpp \
	bslNotification.cpp \
	bslNotificationEvents.cpp \
	bslProject.cpp \
	bslProjectEvents.cpp \
	bslProjectLink.cpp \
	bslProjectListItem.cpp \
	bslProjectListItemEvents.cpp \
	bslProjectStatistic.cpp \
	bslProjectStatisticEvents.cpp \
	bslTask.cpp \
	bslTaskEvents.cpp \
	bslTaskInstance.cpp \
	bslTaskInstanceEvents.cpp \
	bslTransfer.cpp \
	bslTransferEvents.cpp

libbslcommon_la_DEPENDENCIES = $(LIBBSLXML) 
libbslcommon_la_CPPFLAGS = $(AM_CPPFLAGS) $(PICFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CFLAGS)
libbslcommon_la_CXXFLAGS = $(AM_CXXFLAGS) $(PICFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CFLAGS)
libbslcommon_la_LDFLAGS = -version-info $(BOINCSENTINELS_VERSION_MAJOR):$(BOINCSENTINELS_VERSION_MINOR):0 
libbslcommon_la_LIBADD = $(LIBBSLXML_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)

CLEANFILES = \
	src/*.gcda \
	src/*.gcno \
	src/*.gcov

