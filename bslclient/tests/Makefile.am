## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

bin_PROGRAMS = bslclient_tests

bslclient_tests_SOURCES = \
	bslClientTestMain.cpp \
	bslClientTest.cpp \
	bslClientTest.h \
	ConnectDisconnectTest.cpp \
	ConnectDisconnectTest.h \
	EnumerateAppsTest.cpp \
	EnumerateAppsTest.h \
	EnumerateAppVersionsTest.cpp \
	EnumerateAppVersionsTest.h \
	EnumerateHostsTest.cpp \
	EnumerateHostsTest.h \
	EnumerateMessagesTest.cpp \
	EnumerateMessagesTest.h \
	EnumerateNotificationsTest.cpp \
	EnumerateNotificationsTest.h \
	EnumerateProjectsTest.cpp \
	EnumerateProjectsTest.h \
	EnumerateTaskInstancesTest.cpp \
	EnumerateTaskInstancesTest.h \
	EnumerateTasksTest.cpp \
	EnumerateTasksTest.h \
	EnumerateTransfersTest.cpp \
	EnumerateTransfersTest.h \
	GetAppTest.cpp \
	GetAppTest.h \
	GetAppVersionTest.cpp \
	GetAppVersionTest.h \
	GetHostTest.cpp \
	GetHostTest.h \
	GetMessageTest.cpp \
	GetMessageTest.h \
	GetNotificationTest.cpp \
	GetNotificationTest.h \
	GetProjectStatisticTest.cpp \
	GetProjectStatisticTest.h \
	GetProjectTest.cpp \
	GetProjectTest.h \
	GetTaskInstanceTest.cpp \
	GetTaskInstanceTest.h \
	GetTaskTest.cpp \
	GetTaskTest.h \
	GetTransferTest.cpp \
	GetTransferTest.h


bslclient_tests_DEPENDENCIES = $(LIBBSLXML) $(LIBBSLCOMMON) $(LIBBSLCLIENT) 
bslclient_tests_CPPFLAGS = $(AM_CPPFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CPPFLAGS) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(CPPUNIT_CFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CPPFLAGS)
bslclient_tests_CXXFLAGS = $(AM_CXXFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CXXFLAGS) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(CPPUNIT_CFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CXXFLAGS)
bslclient_tests_LDFLAGS = $(AM_LDFLAGS) -static $(LIBBSLXML_LIBS) $(LIBBSLCOMMON_LIBS) $(LIBBSLCLIENT_LIBS) $(CPPUNIT_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


if OS_WIN32_MINGW

bslclient_tests_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


if OS_WIN64_MINGW

bslclient_tests_LDFLAGS +=-Wl,--subsystem,console -mwindows 

endif


TESTS = bslclient_tests


CLEANFILES = \
	*.gcda \
	*.gcno \
	*.gcov \
	*.xml
