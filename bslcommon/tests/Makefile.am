## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

bin_PROGRAMS = bslcommon_tests

bslcommon_tests_SOURCES = \
	bslCommonTestMain.cpp \
	bslAppEventDataTest.cpp \
	bslAppEventDataTest.h \
	bslAppTest.cpp \
	bslAppTest.h \
	bslAppVersionEventDataTest.cpp \
	bslAppVersionEventDataTest.h \
	bslAppVersionTest.cpp \
	bslAppVersionTest.h \
	bslHostEventDataTest.cpp \
	bslHostEventDataTest.h \
	bslHostTest.cpp \
	bslHostTest.h \
	bslMessageEventDataTest.cpp \
	bslMessageEventDataTest.h \
	bslMessageTest.cpp \
	bslMessageTest.h \
	bslNotificationEventDataTest.cpp \
	bslNotificationEventDataTest.h \
	bslNotificationTest.cpp \
	bslNotificationTest.h \
	bslProjectEventDataTest.cpp \
	bslProjectEventDataTest.h \
	bslProjectLinkTest.cpp \
	bslProjectLinkTest.h \
	bslProjectListItemEventDataTest.cpp \
	bslProjectListItemEventDataTest.h \
	bslProjectListItemTest.cpp \
	bslProjectListItemTest.h \
	bslProjectStatisticEventDataTest.cpp \
	bslProjectStatisticEventDataTest.h \
	bslProjectStatisticTest.cpp \
	bslProjectStatisticTest.h \
	bslProjectTest.cpp \
	bslProjectTest.h \
	bslTaskEventDataTest.cpp \
	bslTaskEventDataTest.h \
	bslTaskInstanceEventDataTest.cpp \
	bslTaskInstanceEventDataTest.h \
	bslTaskInstanceTest.cpp \
	bslTaskInstanceTest.h \
	bslTaskTest.cpp \
	bslTaskTest.h \
	bslTransferEventDataTest.cpp \
	bslTransferEventDataTest.h \
	bslTransferTest.cpp \
	bslTransferTest.h


bslcommon_tests_DEPENDENCIES = $(LIBBSLXML) $(LIBBSLCOMMON) 
bslcommon_tests_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(CPPUNIT_CFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
bslcommon_tests_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(CPPUNIT_CFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
bslcommon_tests_LDFLAGS = $(AM_LDFLAGS) -static $(LIBBSLXML_LIBS) $(LIBBSLCOMMON_LIBS) $(CPPUNIT_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

bslcommon_tests_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

bslcommon_tests_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


TESTS = bslcommon_tests


CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov \
	*.xml
