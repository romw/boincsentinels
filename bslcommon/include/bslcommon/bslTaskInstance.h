// BOINC Sentinels.
// https://projects.romwnet.org/boincsentinels
// Copyright (C) 2009-2014 Rom Walton
//
// BOINC Sentinels is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC Sentinels is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC Sentinels.  If not, see <http://www.gnu.org/licenses/>.
//

///
/// \defgroup BSLCommon BOINC Sentinels Common Library Interface
/// \{

#ifndef _BSLCOMMONTASKINSTANCE_H_
#define _BSLCOMMONTASKINSTANCE_H_

#define BSLXMLTAGHASH_TASKINSTANCE \
    0x37d1d802

class CBSLTaskInstance: public CBSLTaskInstanceEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLTaskInstance)

public:

    /// \brief State of a given task
    /// \note  Values are directly compatible with default BOINC task state values.
    enum TASKSTATE
    {
        TaskStateNew = 0,
        TaskStateFilesDownloading = 1,
        TaskStateFilesDownloaded = 2,
        TaskStateComputeError = 3,
        TaskStateFilesUploading = 4,
        TaskStateFilesUploaded = 5,
        TaskStateAborted = 6
    };

    /// \brief State of the task seen from the BOINC client scheduler
    /// \note  Values are directly compatible with default BOINC scheduler state values.
    enum SCHEDULERSTATE
    {
        SchedulerStateUninitialized = 0,
        SchedulerStatePreempted = 1,
        SchedulerStateScheduled = 2
    };

    /// \brief State of the active task
    /// \note  Values are directly compatible with default BOINC active task state values.
    enum ACTIVETASKSTATE
    {
        ActiveTaskStateUninitialized = 0,
        ActiveTaskStateExecuting = 1,
        ActiveTaskStateSuspended = 9,
        ActiveTaskStateAbortPending = 5,
        ActiveTaskStateQuitPending = 8
    };

    CBSLTaskInstance();
    virtual ~CBSLTaskInstance();

    /// \brief Assignment Operator
    virtual CBSLTaskInstance& operator= (const CBSLTaskInstance&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLTaskInstance&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLTaskInstance&) const;

    /// \brief Initialize CBSLTaskInstance state.
    void Clear();

    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    ACTIVETASKSTATE GetActiveTaskState();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxTimeSpan& GetCheckpointCPUTime();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxTimeSpan& GetCurrentCPUTime();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxTimeSpan& GetElapsedTime();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxTimeSpan& GetEstimatedElapsedTimeRemaining();
    /// \brief
    wxInt32 GetExitStatus();
    /// \brief
    wxTimeSpan& GetFinalCPUTime();
    /// \brief
    wxTimeSpan& GetFinalElapsedTime();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxDouble GetFractionDone();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxString& GetGraphicsApplication();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxString& GetWebGraphicsApplication();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxString& GetRemoteDesktopAddress();
    /// \brief
    wxString& GetName();
    /// \brief
    wxUint32 GetNameHash();
    /// \brief Returns the URL of the project that generated the task instance.
    wxString& GetProject();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief
    wxString& GetTaskName();
    /// \brief
    wxUint32 GetTaskNameHash();
    /// \brief
    wxString& GetAppName();
    /// \brief
    wxUint32 GetAppNameHash();
    /// \brief
    wxUint32 GetAppVersion();
    /// \brief
    wxString& GetAppVersionString();
    /// \brief
    wxString& GetAppPlanClass();
    /// \brief
    wxUint32 GetAppPlanClassHash();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxUint64 GetPageFaultRate();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxUint32 GetProcessID();
    /// \brief
    wxDateTime& GetReceivedTime();
    /// \brief
    wxDateTime& GetCompletedTime();
    /// \brief
    wxDateTime& GetReportDeadline();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxString& GetResourcesUtilized();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    SCHEDULERSTATE GetSchedulerState();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxString& GetSlotDirectory();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxUint32 GetSlotID();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxUint64 GetSwapSize();
    /// \brief
    TASKSTATE GetTaskState();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxUint64 GetWorkingSetSize();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    wxUint64 GetWorkingSetSizeSmoothed();
    /// \brief
    bool IsTaskActive();
    /// \brief
    bool IsCoprocMissing();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    bool IsEDFScheduled();
    /// \brief
    bool IsInterfaceSuspensionEnabled();
    /// \brief
    bool IsReadyToReport();
    /// \brief
    bool IsServerAcknowledged();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    bool IsSupportsGraphics();
    /// \brief
    bool IsWaitingOnScheduler();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    bool IsWaitingOnMemory();
    /// \brief
    /// \note  This is only valid if IsActiveTask() returns true
    bool IsWaitingOnSharedMemory();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief
    void SetActiveTaskState(ACTIVETASKSTATE iActiveTaskState);
    /// \brief
    void SetCheckpointCPUTime(wxTimeSpan tsCheckpointCPUTime);
    /// \brief
    void SetCoprocMissing(bool bCoprocMissing);
    /// \brief
    void SetCurrentCPUTime(wxTimeSpan tsCurrentCPUTime);
    /// \brief
    void SetEDFScheduled(bool bEDFScheduled);
    /// \brief
    void SetElapsedTime(wxTimeSpan tsElapsedTime);
    /// \brief
    void SetEstimatedElapsedTimeRemaining(wxTimeSpan tsEstimatedElapsedTimeRemaining);
    /// \brief
    void SetExitStatus(wxInt32 iExitStatus);
    /// \brief
    void SetFinalCPUTime(wxTimeSpan tsFinalCPUTime);
    /// \brief
    void SetFinalElapsedTime(wxTimeSpan tsFinalElapsedTime);
    /// \brief
    void SetFractionDone(wxDouble dFractionDone);
    /// \brief
    void SetGraphicsApplication(wxString strGraphicsApplication);
    /// \brief
    void SetWebGraphicsApplication(wxString strWebGraphicsApplication);
    /// \brief
    void SetRemoteDesktopAddress(wxString strRemoteDesktopAddress);
    /// \brief
    void SetInterfaceSuspensionEnabled(bool bInterfaceSuspensionEnabled);
    /// \brief
    void SetName(wxString strName);
    /// \brief Sets the URL of the project that generated the task instance.
    void SetProject(wxString strProject);
    /// \brief
    void SetTaskActive(bool bTaskActive);
    /// \brief
    void SetTaskName(wxString strTaskName);
    /// \brief
    void SetAppName(wxString strAppName);
    /// \brief
    void SetAppVersion(wxUint32 uiAppVersion);
    /// \brief
    void SetAppPlanClass(wxString strAppPlanClass);
    /// \brief
    void SetPageFaultRate(wxUint64 ullPageFaultRate);
    /// \brief
    void SetProcessID(wxUint32 uiProcessID);
    /// \brief
    void SetReadyToReport(bool bReadyToReport);
    /// \brief
    void SetReceivedTime(wxDateTime dtReceivedTime);
    /// \brief
    void SetCompletedTime(wxDateTime dtCompletedTime);
    /// \brief
    void SetReportDeadline(wxDateTime dtReportDeadline);
    /// \brief
    void SetResourcesUtilized(wxString strResourcesUtilized);
    /// \brief
    void SetSchedulerState(SCHEDULERSTATE iSchedulerState);
    /// \brief
    void SetServerAcknowledged(bool bServerAcknowledged);
    /// \brief
    void SetSlotDirectory(wxString strSlotDirectory);
    /// \brief
    void SetSlotID(wxUint32 uiSlotID);
    /// \brief
    void SetSupportsGraphics(bool bSupportsGraphics);
    /// \brief
    void SetSwapSize(wxUint64 ullSwapSize);
    /// \brief
    void SetTaskState(TASKSTATE iTaskState);
    /// \brief
    void SetWaitingOnScheduler(bool bWaitingOnScheduler);
    /// \brief
    void SetWaitingOnMemory(bool bWaitingOnMemory);
    /// \brief
    void SetWaitingOnSharedMemory(bool bWaitingOnSharedMemory);
    /// \brief
    void SetWorkingSetSize(wxUint64 ullWorkingSetSize);
    /// \brief
    void SetWorkingSetSizeSmoothed(wxUint64 ullWorkingSetSizeSmoothed);

private:
    wxString m_strProject;
    wxUint32 m_uiProjectHash;
    wxString m_strTaskName;
    wxUint32 m_uiTaskNameHash;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strAppName;
    wxUint32 m_uiAppNameHash;
    wxUint32 m_uiAppVersion;
    wxString m_strAppVersion;
    wxUint32 m_uiAppVersionHash;
    wxString m_strAppPlanClass;
    wxUint32 m_uiAppPlanClassHash;
    TASKSTATE m_iTaskState;
    wxInt32 m_iExitStatus;
    wxDateTime m_dtReportDeadline;
    wxDateTime m_dtReceivedTime;
    wxDateTime m_dtCompletedTime;
    wxTimeSpan m_tsFinalCPUTime;
    wxTimeSpan m_tsFinalElapsedTime;
    bool m_bReadyToReport;
    bool m_bServerAcknowledged;
    bool m_bInterfaceSuspensionEnabled;
    bool m_bCoprocMissing;
    bool m_bTaskActive;
    SCHEDULERSTATE m_iSchedulerState;
    ACTIVETASKSTATE m_iActiveTaskState;
    wxUint32 m_uiSlotID;
    wxUint32 m_uiProcessID;
    wxTimeSpan m_tsCheckpointCPUTime;
    wxTimeSpan m_tsCurrentCPUTime;
    wxDouble m_dFractionDone;
    wxTimeSpan m_tsElapsedTime;
    wxUint64 m_ullSwapSize;
    wxUint64 m_ullWorkingSetSize;
    wxUint64 m_ullWorkingSetSizeSmoothed;
    wxUint64 m_ullPageFaultRate;
    wxTimeSpan m_tsEstimatedElapsedTimeRemaining;
    bool m_bSupportsGraphics;
    bool m_bWaitingOnScheduler;
    bool m_bWaitingOnMemory;
    bool m_bWaitingOnSharedMemory;
    bool m_bEDFScheduled;
    wxString m_strGraphicsApplication;
    wxUint32 m_uiGraphicsApplicationHash;
    wxString m_strWebGraphicsApplication;
    wxUint32 m_uiWebGraphicsApplicationHash;
    wxString m_strRemoteDesktopAddress;
    wxUint32 m_uiRemoteDesktopAddressHash;
    wxString m_strSlotDirectory;
    wxUint32 m_uiSlotDirectoryHash;
    wxString m_strResourcesUtilized;
    wxUint32 m_uiResourcesUtilizedHash;
};

#endif

///
/// \}
