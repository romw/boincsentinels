## -*- mode: makefile; tab-width: 4 -*-

include $(top_srcdir)/Makefile.incl

lib_LTLIBRARIES = libbslclient.la

# Package Info Installation
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ../bslclient.pc

# Public Headers
library_includedir=$(includedir)/bslclient-$(BOINCSENTINELS_VERSION_MAJOR).$(BOINCSENTINELS_VERSION_MINOR)/bslclient
library_include_HEADERS = \
	../include/bslclient/bslClient.h \
	../include/bslclient/bslClientEventDefs.hxx \
	../include/bslclient/bslClientEvents.h

libbslclient_la_SOURCES = \
	bslClient.cpp \
	bslClientEvents.cpp \
	ClientState.cpp \
	ClientState.h \
	ClientStateApp.cpp \
	ClientStateApp.h \
	ClientStateAppVersion.cpp \
	ClientStateAppVersion.h \
	ClientStateDatabase.cpp \
	ClientStateDatabase.h \
	ClientStateEventDefs.hxx \
	ClientStateEvents.cpp \
	ClientStateEvents.h \
	ClientStateHost.cpp \
	ClientStateHost.h \
	ClientStateHostStatus.cpp \
	ClientStateHostStatus.h \
	ClientStateMessage.cpp \
	ClientStateMessage.h \
	ClientStateNotification.cpp \
	ClientStateNotification.h \
	ClientStateObject.cpp \
	ClientStateObject.h \
	ClientStateProject.cpp \
	ClientStateProject.h \
	ClientStateProjectLink.cpp \
	ClientStateProjectLink.h \
	ClientStateProjectListItem.cpp \
	ClientStateProjectListItem.h \
	ClientStateProjectStatistic.cpp \
	ClientStateProjectStatistic.h \
	ClientStateRPCProfile.cpp \
	ClientStateRPCProfile.h \
	ClientStateSyncProfile.cpp \
	ClientStateSyncProfile.h \
	ClientStateTask.cpp \
	ClientStateTask.h \
	ClientStateTaskInstance.cpp \
	ClientStateTaskInstance.h \
	ClientStateTransfer.cpp \
	ClientStateTransfer.h \
	ClientStateTypes.h \
	EventManager.cpp \
	EventManager.h \
	EventManagerTypes.h \
	GarbageCollector.cpp \
	GarbageCollector.h \
	Instance.cpp \
	Instance.h \
	RPCAuthorize.cpp \
	RPCAuthorize.h \
	RPCConnection.cpp \
	RPCConnection.h \
	RPCCreateAccount.cpp \
	RPCCreateAccount.h \
	RPCCreateAccountPoll.cpp \
	RPCCreateAccountPoll.h \
	RPCExchangeVersions.cpp \
	RPCExchangeVersions.h \
	RPCLookupAccount.cpp \
	RPCLookupAccount.h \
	RPCLookupAccountPoll.cpp \
	RPCLookupAccountPoll.h \
	RPCManager.cpp \
	RPCManager.h \
	RPCNetworkAvailable.cpp \
	RPCNetworkAvailable.h \
	RPCProjectAllowMoreWork.cpp \
	RPCProjectAllowMoreWork.h \
	RPCProjectAttach.cpp \
	RPCProjectAttach.h \
	RPCProjectAttachPoll.cpp \
	RPCProjectAttachPoll.h \
	RPCProjectDetach.cpp \
	RPCProjectDetach.h \
	RPCProjectDetachWhenDone.cpp \
	RPCProjectDetachWhenDone.h \
	RPCProjectDontDetachWhenDone.cpp \
	RPCProjectDontDetachWhenDone.h \
	RPCProjectNoMoreWork.cpp \
	RPCProjectNoMoreWork.h \
	RPCProjectOperation.cpp \
	RPCProjectOperation.h \
	RPCProjectReset.cpp \
	RPCProjectReset.h \
	RPCProjectResume.cpp \
	RPCProjectResume.h \
	RPCProjectSuspend.cpp \
	RPCProjectSuspend.h \
	RPCProjectUpdate.cpp \
	RPCProjectUpdate.h \
	RPCProtocol.cpp \
	RPCProtocol.h \
	RPCRunBenchmarks.cpp \
	RPCRunBenchmarks.h \
	RPCSetModeCPU.h \
	RPCSetModeCPU.cpp \
	RPCSetModeGPU.h \
	RPCSetModeGPU.cpp \
	RPCSetModeNetwork.h \
	RPCSetModeNetwork.cpp \
	RPCSetModeOperation.h \
	RPCSetModeOperation.cpp \
	RPCShutdown.cpp \
	RPCShutdown.h \
	RPCSyncHost.cpp \
	RPCSyncHost.h \
	RPCSyncHostStatus.cpp \
	RPCSyncHostStatus.h \
	RPCSyncMessages.cpp \
	RPCSyncMessages.h \
	RPCSyncNotifications.cpp \
	RPCSyncNotifications.h \
	RPCSyncProjectList.cpp \
	RPCSyncProjectList.h \
	RPCSyncProjects.cpp \
	RPCSyncProjects.h \
	RPCSyncProjectStatistics.cpp \
	RPCSyncProjectStatistics.h \
	RPCSyncState.cpp \
	RPCSyncState.h \
	RPCSyncTaskInstances.cpp \
	RPCSyncTaskInstances.h \
	RPCSyncTransfers.cpp \
	RPCSyncTransfers.h \
	RPCTaskInstanceAbort.cpp \
	RPCTaskInstanceAbort.h \
	RPCTaskInstanceOperation.cpp \
	RPCTaskInstanceOperation.h \
	RPCTaskInstanceResume.cpp \
	RPCTaskInstanceResume.h \
	RPCTaskInstanceSuspend.cpp \
	RPCTaskInstanceSuspend.h \
	RPCTransferAbort.cpp \
	RPCTransferAbort.h \
	RPCTransferOperation.cpp \
	RPCTransferOperation.h \
	RPCTransferRetry.cpp \
	RPCTransferRetry.h \
	RPCTypes.h \
	StateManager.cpp \
	StateManager.h \
	StateManagerJob.cpp \
	StateManagerJob.h \
	StateManagerThread.cpp \
	StateManagerThread.h \
	StateWorkerThread.cpp \
	StateWorkerThread.h \
	wxMD5.cpp \
	wxMD5.h

libbslclient_la_DEPENDENCIES = $(LIBBSLCOMMON) 
libbslclient_la_CPPFLAGS = $(AM_CPPFLAGS) $(PICFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CPPFLAGS) $(LIBBSLCOMMON_CPPFLAGS) $(LIBBSLXML_CPPFLAGS) $(WX_CPPFLAGS) $(PTHREAD_CFLAGS)
libbslclient_la_CXXFLAGS = $(AM_CXXFLAGS) $(PICFLAGS) $(PROJECTINCLUDE) $(LIBBSLCLIENT_CXXFLAGS) $(LIBBSLCOMMON_CXXFLAGS) $(LIBBSLXML_CXXFLAGS) $(WX_CXXFLAGS) $(PTHREAD_CFLAGS) 
libbslclient_la_LDFLAGS = -version-info $(BOINCSENTINELS_VERSION_MAJOR):$(BOINCSENTINELS_VERSION_MINOR):0 
libbslclient_la_LIBADD = $(LIBBSLXML_LIBS) $(LIBBSLCOMMON_LIBS) $(WX_LIBS) $(PTHREAD_LIBS)


CLEANFILES = \
	src/*.gcda \
	src/*.gcno \
	src/*.gcov
