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

#include "stdwx.h"
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"


#define BSLXMLTAGHASH_ACTIVETASK \
    0x867d3c6d


CBSLTaskInstance::ACTIVETASKSTATE MapActiveTaskState(wxInt32 iActiveTaskState)
{
    switch (iActiveTaskState)
    {
        case 1:
            return CBSLTaskInstance::ActiveTaskStateExecuting;
            break;
        case 9:
            return CBSLTaskInstance::ActiveTaskStateSuspended;
            break;
        case 5:
            return CBSLTaskInstance::ActiveTaskStateAbortPending;
            break;
        case 8:
            return CBSLTaskInstance::ActiveTaskStateQuitPending;
            break;
    }
    return CBSLTaskInstance::ActiveTaskStateUninitialized;
}

CBSLTaskInstance::SCHEDULERSTATE MapSchedulerState(wxInt32 iSchedulerState)
{
    switch (iSchedulerState)
    {
        case 1:
            return CBSLTaskInstance::SchedulerStatePreempted;
            break;
        case 2:
            return CBSLTaskInstance::SchedulerStateScheduled;
            break;
    }
    return CBSLTaskInstance::SchedulerStateUninitialized;
}

CBSLTaskInstance::TASKSTATE MapTaskState(wxInt32 iTaskState)
{
    switch (iTaskState)
    {
        case 1:
            return CBSLTaskInstance::TaskStateFilesDownloading;
            break;
        case 2:
            return CBSLTaskInstance::TaskStateFilesDownloaded;
            break;
        case 3:
            return CBSLTaskInstance::TaskStateComputeError;
            break;
        case 4:
            return CBSLTaskInstance::TaskStateFilesUploading;
            break;
        case 5:
            return CBSLTaskInstance::TaskStateFilesUploaded;
            break;
        case 6:
            return CBSLTaskInstance::TaskStateAborted;
            break;
    }
    return CBSLTaskInstance::TaskStateNew;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLTaskInstance, CBSLTaskInstanceEventData);

CBSLTaskInstance::CBSLTaskInstance() :
CBSLTaskInstanceEventData()
{
    Clear();
}

CBSLTaskInstance::~CBSLTaskInstance()
{
}

CBSLTaskInstance& CBSLTaskInstance::operator= (const CBSLTaskInstance& bslTaskInstance)
{
    CBSLTaskInstanceEventData::operator=(bslTaskInstance);

    m_uiAppVersion = bslTaskInstance.m_uiAppVersion;
    m_iTaskState = bslTaskInstance.m_iTaskState;
    m_iExitStatus = bslTaskInstance.m_iExitStatus;
    m_dtReportDeadline = bslTaskInstance.m_dtReportDeadline;
    m_dtReceivedTime = bslTaskInstance.m_dtReceivedTime;
    m_dtCompletedTime = bslTaskInstance.m_dtCompletedTime;
    m_tsFinalCPUTime = bslTaskInstance.m_tsFinalCPUTime;
    m_tsFinalElapsedTime = bslTaskInstance.m_tsFinalElapsedTime;
    m_bReadyToReport = bslTaskInstance.m_bReadyToReport;
    m_bServerAcknowledged = bslTaskInstance.m_bServerAcknowledged;
    m_bInterfaceSuspensionEnabled = bslTaskInstance.m_bInterfaceSuspensionEnabled;
    m_bCoprocMissing = bslTaskInstance.m_bCoprocMissing;
    m_bTaskActive = bslTaskInstance.m_bTaskActive;
    m_iSchedulerState = bslTaskInstance.m_iSchedulerState;
    m_iActiveTaskState = bslTaskInstance.m_iActiveTaskState;
    m_uiSlotID = bslTaskInstance.m_uiSlotID;
    m_uiProcessID = bslTaskInstance.m_uiProcessID;
    m_tsCheckpointCPUTime = bslTaskInstance.m_tsCheckpointCPUTime;
    m_tsCurrentCPUTime = bslTaskInstance.m_tsCurrentCPUTime;
    m_dFractionDone = bslTaskInstance.m_dFractionDone;
    m_tsElapsedTime = bslTaskInstance.m_tsElapsedTime;
    m_ullSwapSize = bslTaskInstance.m_ullSwapSize;
    m_ullWorkingSetSize = bslTaskInstance.m_ullWorkingSetSize;
    m_ullWorkingSetSizeSmoothed = bslTaskInstance.m_ullWorkingSetSizeSmoothed;
    m_ullPageFaultRate = bslTaskInstance.m_ullPageFaultRate;
    m_tsEstimatedElapsedTimeRemaining = bslTaskInstance.m_tsEstimatedElapsedTimeRemaining;
    m_bSupportsGraphics = bslTaskInstance.m_bSupportsGraphics;
    m_bWaitingOnScheduler = bslTaskInstance.m_bWaitingOnScheduler;
    m_bWaitingOnMemory = bslTaskInstance.m_bWaitingOnMemory;
    m_bWaitingOnSharedMemory = bslTaskInstance.m_bWaitingOnSharedMemory;
    m_bEDFScheduled = bslTaskInstance.m_bEDFScheduled;
    m_strProject = bslTaskInstance.m_strProject;
    m_uiProjectHash = bslTaskInstance.m_uiProjectHash;
    m_strTaskName = bslTaskInstance.m_strTaskName;
    m_uiTaskNameHash = bslTaskInstance.m_uiTaskNameHash;
    m_strName = bslTaskInstance.m_strName;
    m_uiNameHash = bslTaskInstance.m_uiNameHash;
    m_strAppPlanClass = bslTaskInstance.m_strAppPlanClass;
    m_uiAppPlanClassHash = bslTaskInstance.m_uiAppPlanClassHash;
    m_strGraphicsApplication = bslTaskInstance.m_strGraphicsApplication;
    m_uiGraphicsApplicationHash = bslTaskInstance.m_uiGraphicsApplicationHash;
    m_strWebGraphicsApplication = bslTaskInstance.m_strWebGraphicsApplication;
    m_uiWebGraphicsApplicationHash = bslTaskInstance.m_uiWebGraphicsApplicationHash;
    m_strRemoteDesktopAddress = bslTaskInstance.m_strRemoteDesktopAddress;
    m_uiRemoteDesktopAddressHash = bslTaskInstance.m_uiRemoteDesktopAddressHash;
    m_strSlotDirectory = bslTaskInstance.m_strSlotDirectory;
    m_uiSlotDirectoryHash = bslTaskInstance.m_uiSlotDirectoryHash;
    m_strResourcesUtilized = bslTaskInstance.m_strResourcesUtilized;
    m_uiResourcesUtilizedHash = bslTaskInstance.m_uiResourcesUtilizedHash;

    if (!bslTaskInstance.m_strAppName.IsEmpty())
    {
        m_strAppName = bslTaskInstance.m_strAppName;
        m_uiAppNameHash = bslTaskInstance.m_uiAppNameHash;
    }

    return *this;
}

bool CBSLTaskInstance::operator== (const CBSLTaskInstance& bslTaskInstance) const
{
    if (m_uiAppVersion != bslTaskInstance.m_uiAppVersion) return false;
    if (m_iTaskState != bslTaskInstance.m_iTaskState) return false;
    if (m_iExitStatus != bslTaskInstance.m_iExitStatus) return false;
    if (m_dtReportDeadline != bslTaskInstance.m_dtReportDeadline) return false;
    if (m_dtReceivedTime != bslTaskInstance.m_dtReceivedTime) return false;
    if (m_dtCompletedTime != bslTaskInstance.m_dtCompletedTime) return false;
    if (m_tsFinalCPUTime != bslTaskInstance.m_tsFinalCPUTime) return false;
    if (m_tsFinalElapsedTime != bslTaskInstance.m_tsFinalElapsedTime) return false;
    if (m_bReadyToReport != bslTaskInstance.m_bReadyToReport) return false;
    if (m_bServerAcknowledged != bslTaskInstance.m_bServerAcknowledged) return false;
    if (m_bInterfaceSuspensionEnabled != bslTaskInstance.m_bInterfaceSuspensionEnabled) return false;
    if (m_bCoprocMissing != bslTaskInstance.m_bCoprocMissing) return false;
    if (m_bTaskActive != bslTaskInstance.m_bTaskActive) return false;
    if (m_iSchedulerState != bslTaskInstance.m_iSchedulerState) return false;
    if (m_iActiveTaskState != bslTaskInstance.m_iActiveTaskState) return false;
    if (m_uiSlotID != bslTaskInstance.m_uiSlotID) return false;
    if (m_uiProcessID != bslTaskInstance.m_uiProcessID) return false;
    if (m_tsCheckpointCPUTime != bslTaskInstance.m_tsCheckpointCPUTime) return false;
    if (m_tsCurrentCPUTime != bslTaskInstance.m_tsCurrentCPUTime) return false;
    if (m_dFractionDone != bslTaskInstance.m_dFractionDone) return false;
    if (m_tsElapsedTime != bslTaskInstance.m_tsElapsedTime) return false;
    if (m_ullSwapSize != bslTaskInstance.m_ullSwapSize) return false;
    if (m_ullWorkingSetSize != bslTaskInstance.m_ullWorkingSetSize) return false;
    if (m_ullWorkingSetSizeSmoothed != bslTaskInstance.m_ullWorkingSetSizeSmoothed) return false;
    if (m_ullPageFaultRate != bslTaskInstance.m_ullPageFaultRate) return false;
    if (m_tsEstimatedElapsedTimeRemaining != bslTaskInstance.m_tsEstimatedElapsedTimeRemaining) return false;
    if (m_bSupportsGraphics != bslTaskInstance.m_bSupportsGraphics) return false;
    if (m_bWaitingOnScheduler != bslTaskInstance.m_bWaitingOnScheduler) return false;
    if (m_bWaitingOnMemory != bslTaskInstance.m_bWaitingOnMemory) return false;
    if (m_bWaitingOnSharedMemory != bslTaskInstance.m_bWaitingOnSharedMemory) return false;
    if (m_bEDFScheduled != bslTaskInstance.m_bEDFScheduled) return false;
    if (m_uiProjectHash != bslTaskInstance.m_uiProjectHash) return false;
    if (m_uiTaskNameHash != bslTaskInstance.m_uiTaskNameHash) return false;
    if (m_uiNameHash != bslTaskInstance.m_uiNameHash) return false;
    if (m_uiAppPlanClassHash != bslTaskInstance.m_uiAppPlanClassHash) return false;
    if (m_uiGraphicsApplicationHash != bslTaskInstance.m_uiGraphicsApplicationHash) return false;
    if (m_uiWebGraphicsApplicationHash != bslTaskInstance.m_uiWebGraphicsApplicationHash) return false;
    if (m_uiRemoteDesktopAddressHash != bslTaskInstance.m_uiRemoteDesktopAddressHash) return false;
    if (m_uiSlotDirectoryHash != bslTaskInstance.m_uiSlotDirectoryHash) return false;
    if (m_uiResourcesUtilizedHash != bslTaskInstance.m_uiResourcesUtilizedHash) return false;

    if (!bslTaskInstance.m_strAppName.IsEmpty())
    {
        if (m_uiAppNameHash != bslTaskInstance.m_uiAppNameHash) return false;
    }

    return true;
}

bool CBSLTaskInstance::operator!= (const CBSLTaskInstance& bslTaskInstance) const
{
    return !(*this == bslTaskInstance);
}

void CBSLTaskInstance::Clear()
{
    m_strProject.clear();
    m_uiProjectHash = 0;
    m_strAppName.clear();
    m_uiAppNameHash = 0;
    m_strTaskName.clear();
    m_uiTaskNameHash = 0;
    m_strName.empty();
    m_uiNameHash = 0;
    m_uiAppVersion = 0;
    m_strAppVersion.clear();
    m_uiAppVersionHash = 0;
    m_strAppPlanClass.clear();
    m_uiAppPlanClassHash = 0;
    m_iTaskState = CBSLTaskInstance::TaskStateNew;
    m_iExitStatus = 0;
    m_dtReportDeadline = wxDateTime((time_t)0);
    m_dtReceivedTime = wxDateTime((time_t)0);
    m_dtCompletedTime = wxDateTime((time_t)0);
    m_tsFinalCPUTime = 0;
    m_tsFinalElapsedTime = 0;
    m_bReadyToReport = false;
    m_bServerAcknowledged = false;
    m_bInterfaceSuspensionEnabled = false;
    m_bCoprocMissing = false;
    m_bTaskActive = false;
    m_iSchedulerState = CBSLTaskInstance::SchedulerStateUninitialized;
    m_iActiveTaskState = CBSLTaskInstance::ActiveTaskStateUninitialized;
    m_uiSlotID = 0;
    m_uiProcessID = 0;
    m_tsCheckpointCPUTime = 0;
    m_tsCurrentCPUTime = 0;
    m_dFractionDone = 0.0;
    m_tsElapsedTime = 0;
    m_ullSwapSize = 0;
    m_ullWorkingSetSize = 0;
    m_ullWorkingSetSizeSmoothed = 0;
    m_ullPageFaultRate = 0;
    m_tsEstimatedElapsedTimeRemaining = 0;
    m_bSupportsGraphics = false;
    m_bWaitingOnScheduler = false;
    m_bWaitingOnMemory = false;
    m_bWaitingOnSharedMemory = false;
    m_bEDFScheduled = false;
    m_strGraphicsApplication.clear();
    m_uiGraphicsApplicationHash = 0;
    m_strWebGraphicsApplication.clear();
    m_uiWebGraphicsApplicationHash = 0;
    m_strRemoteDesktopAddress.clear();
    m_uiRemoteDesktopAddressHash = 0;
    m_strSlotDirectory.clear();
    m_uiSlotDirectoryHash = 0;
    m_strResourcesUtilized.clear();
    m_uiResourcesUtilizedHash = 0;
}

CBSLTaskInstance::ACTIVETASKSTATE CBSLTaskInstance::GetActiveTaskState()
{
    return m_iActiveTaskState;
}

wxTimeSpan& CBSLTaskInstance::GetCheckpointCPUTime()
{
    return m_tsCheckpointCPUTime;
}

wxTimeSpan& CBSLTaskInstance::GetCurrentCPUTime()
{
    return m_tsCurrentCPUTime;
}

wxTimeSpan& CBSLTaskInstance::GetElapsedTime()
{
    return m_tsElapsedTime;
}

wxTimeSpan& CBSLTaskInstance::GetEstimatedElapsedTimeRemaining()
{
    return m_tsEstimatedElapsedTimeRemaining;
}

wxInt32 CBSLTaskInstance::GetExitStatus()
{
    return m_iExitStatus;
}

wxTimeSpan& CBSLTaskInstance::GetFinalCPUTime()
{
    return m_tsFinalCPUTime;
}

wxTimeSpan& CBSLTaskInstance::GetFinalElapsedTime()
{
    return m_tsFinalElapsedTime;
}

wxDouble CBSLTaskInstance::GetFractionDone()
{
    return m_dFractionDone;
}

wxString& CBSLTaskInstance::GetGraphicsApplication()
{
    return m_strGraphicsApplication;
}

wxString& CBSLTaskInstance::GetWebGraphicsApplication()
{
    return m_strWebGraphicsApplication;
}

wxString& CBSLTaskInstance::GetRemoteDesktopAddress()
{
    return m_strRemoteDesktopAddress;
}

wxString& CBSLTaskInstance::GetName()
{
    return m_strName;
}

wxUint32 CBSLTaskInstance::GetNameHash()
{
    return m_uiNameHash;
}

wxString& CBSLTaskInstance::GetProject()
{
    return m_strProject;
}

wxUint32 CBSLTaskInstance::GetProjectHash()
{
    return m_uiProjectHash;
}

wxString& CBSLTaskInstance::GetTaskName()
{
    return m_strTaskName;
}

wxUint32 CBSLTaskInstance::GetTaskNameHash()
{
    return m_uiTaskNameHash;
}

wxString& CBSLTaskInstance::GetAppName()
{
    return m_strAppName;
}

wxUint32 CBSLTaskInstance::GetAppNameHash()
{
    return m_uiAppNameHash;
}

wxUint32 CBSLTaskInstance::GetAppVersion()
{
    return m_uiAppVersion;
}

wxString& CBSLTaskInstance::GetAppVersionString()
{
    if (m_strAppVersion.empty())
    {
        m_strAppVersion.Printf(wxT("%d.%d"), m_uiAppVersion / 100, m_uiAppVersion % 100);
    }
    return m_strAppVersion;
}

wxString& CBSLTaskInstance::GetAppPlanClass()
{
    return m_strAppPlanClass;
}

wxUint32 CBSLTaskInstance::GetAppPlanClassHash()
{
    return m_uiAppPlanClassHash;
}

wxUint64 CBSLTaskInstance::GetPageFaultRate()
{
    return m_ullPageFaultRate;
}

wxUint32 CBSLTaskInstance::GetProcessID()
{
    return m_uiProcessID;
}

wxDateTime& CBSLTaskInstance::GetReceivedTime()
{
    return m_dtReceivedTime;
}

wxDateTime& CBSLTaskInstance::GetCompletedTime()
{
    return m_dtCompletedTime;
}

wxDateTime& CBSLTaskInstance::GetReportDeadline()
{
    return m_dtReportDeadline;
}

wxString& CBSLTaskInstance::GetResourcesUtilized()
{
    return m_strResourcesUtilized;
}

CBSLTaskInstance::SCHEDULERSTATE CBSLTaskInstance::GetSchedulerState()
{
    return m_iSchedulerState;
}

wxString& CBSLTaskInstance::GetSlotDirectory()
{
    return m_strSlotDirectory;
}

wxUint32 CBSLTaskInstance::GetSlotID()
{
    return m_uiSlotID;
}

wxUint64 CBSLTaskInstance::GetSwapSize()
{
    return m_ullSwapSize;
}

CBSLTaskInstance::TASKSTATE CBSLTaskInstance::GetTaskState()
{
    return m_iTaskState;
}

wxUint64 CBSLTaskInstance::GetWorkingSetSize()
{
    return m_ullWorkingSetSize;
}

wxUint64 CBSLTaskInstance::GetWorkingSetSizeSmoothed()
{
    return m_ullWorkingSetSizeSmoothed;
}

bool CBSLTaskInstance::IsTaskActive()
{
    return m_bTaskActive;
}

bool CBSLTaskInstance::IsCoprocMissing()
{
    return m_bCoprocMissing;
}

bool CBSLTaskInstance::IsEDFScheduled()
{
    return m_bEDFScheduled;
}

bool CBSLTaskInstance::IsInterfaceSuspensionEnabled()
{
    return m_bInterfaceSuspensionEnabled;
}

bool CBSLTaskInstance::IsReadyToReport()
{
    return m_bReadyToReport;
}

bool CBSLTaskInstance::IsServerAcknowledged()
{
    return m_bServerAcknowledged;
}

bool CBSLTaskInstance::IsSupportsGraphics()
{
    return m_bSupportsGraphics;
}

bool CBSLTaskInstance::IsWaitingOnScheduler()
{
    return m_bWaitingOnScheduler;
}

bool CBSLTaskInstance::IsWaitingOnMemory()
{
    return m_bWaitingOnMemory;
}

bool CBSLTaskInstance::IsWaitingOnSharedMemory()
{
    return m_bWaitingOnSharedMemory;
}

BSLERRCODE CBSLTaskInstance::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_TASKINSTANCE == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        if (BSLXMLTAGHASH_ACTIVETASK == oElement.GetNameHash()) continue;
        switch(oElement.GetNameHash())
        {
            case 0x2f8b3bf4:    // name
                m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiNameHash = oElement.GetValueHash();
                break;
            case 0xa0081a8e:    // project_url
                m_strProject = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiProjectHash = oElement.GetValueHash();
                break;
            case 0xbdfce7d9:    // wu_name
                m_strTaskName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiTaskNameHash = oElement.GetValueHash();
                break;
            case 0x4e93e126:    // version_num
                m_uiAppVersion = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0xe4839045:    // plan_class
                m_strAppPlanClass = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiAppPlanClassHash = oElement.GetValueHash();
                break;
            case 0x487cc08f:    // active_task_state
                m_bTaskActive = true;
                m_iActiveTaskState = MapActiveTaskState(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x9d57795c:    // checkpoint_cpu_time
                m_tsCheckpointCPUTime = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0x19e19e86:    // coproc_missing
                m_bCoprocMissing = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0x066f45a9:    // current_cpu_time
                m_tsCurrentCPUTime = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0x0fc76278:    // edf_scheduled
                m_bEDFScheduled = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0xb2bec7bd:    // elapsed_time
                m_tsElapsedTime = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0xd040cba3:    // estimated_cpu_time_remaining
                m_tsEstimatedElapsedTimeRemaining = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0xa8bf4356:    // exit_status
                m_iExitStatus = CBSLXMLConverterEx::ConvertToI32(oElement.GetValue());
                break;
            case 0x4365d554:    // final_cpu_time
                m_tsFinalCPUTime = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0x5761959e:    // final_elapsed_time
                m_tsFinalElapsedTime = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0xb647266e:    // fraction_done
                m_dFractionDone = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                break;
            case 0x05877530:    // graphics_exec_path
                m_strGraphicsApplication = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiGraphicsApplicationHash = oElement.GetValueHash();
                break;
            case 0x34df0ced:    // web_graphics_url
                m_strWebGraphicsApplication = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiWebGraphicsApplicationHash = oElement.GetValueHash();
                break;
            case 0xcd19ab64:    // remote_desktop_addr
                m_strRemoteDesktopAddress = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiRemoteDesktopAddressHash = oElement.GetValueHash();
                break;
            case 0xd3920721:    // suspended_via_gui
                m_bInterfaceSuspensionEnabled = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0x6c200992:    // page_fault_rate
                m_ullPageFaultRate = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x42775cd8:    // pid
                m_uiProcessID = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0x1a9fadef:    // ready_to_report
                m_bReadyToReport = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0x5df48774:    // received_time
                m_dtReceivedTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0x48b68d4c:    // completed_time
                m_dtCompletedTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0xa62266de:    // report_deadline
                m_dtReportDeadline = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0x023f1028:    // resources
                m_strResourcesUtilized = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiResourcesUtilizedHash = oElement.GetValueHash();
                break;
            case 0x68d18d63:    // got_server_ack
                m_bServerAcknowledged = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0xc95d3786:    // scheduler_state
                m_iSchedulerState = MapSchedulerState(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x1290df81:    // slot_path
                m_strSlotDirectory = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiSlotDirectoryHash = oElement.GetValueHash();
                break;
            case 0x2ef1e401:    // slot
                m_uiSlotID = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0x5266ea90:    // state
                m_iTaskState = MapTaskState(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0xa744035b:    // supports_graphics
                m_bSupportsGraphics = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0xb42a4af4:    // swap_size
                m_ullSwapSize = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x8c0ae964:    // scheduler_wait
                m_bWaitingOnScheduler = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0xd9e72b25:    // too_large
                m_bWaitingOnMemory = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0x93ba90b1:    // needs_shmem
                m_bWaitingOnSharedMemory = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0xf7379239:    // working_set_size
                m_ullWorkingSetSize = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x44de2d99:    // working_set_size_smoothed
                m_ullWorkingSetSizeSmoothed = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLTaskInstance::ParseEx: Hash: '0x%x', Name: '%s'"),
                    oElement.GetNameHash(),
                    oElement.GetName()
                );
#endif
                if (CBSLXMLElementEx::ElementTypeContainer == oElement.GetType())
                {
                    oDocument.SkipContainer(oElement);
                }
                break;
        }
    }

    return BSLERR_SUCCESS;
}

void CBSLTaskInstance::SetActiveTaskState(CBSLTaskInstance::ACTIVETASKSTATE iActiveTaskState)
{
    m_iActiveTaskState = iActiveTaskState;
}

void CBSLTaskInstance::SetCheckpointCPUTime(wxTimeSpan tsCheckpointCPUTime)
{
    m_tsCheckpointCPUTime = tsCheckpointCPUTime;
}

void CBSLTaskInstance::SetCoprocMissing(bool bCoprocMissing)
{
    m_bCoprocMissing = bCoprocMissing;
}

void CBSLTaskInstance::SetCurrentCPUTime(wxTimeSpan tsCurrentCPUTime)
{
    m_tsCurrentCPUTime = tsCurrentCPUTime;
}

void CBSLTaskInstance::SetEDFScheduled(bool bEDFScheduled)
{
    m_bEDFScheduled = bEDFScheduled;
}

void CBSLTaskInstance::SetElapsedTime(wxTimeSpan tsElapsedTime)
{
    m_tsElapsedTime = tsElapsedTime;
}

void CBSLTaskInstance::SetEstimatedElapsedTimeRemaining(wxTimeSpan tsEstimatedElapsedTimeRemaining)
{
    m_tsEstimatedElapsedTimeRemaining = tsEstimatedElapsedTimeRemaining;
}

void CBSLTaskInstance::SetExitStatus(wxInt32 iExitStatus)
{
    m_iExitStatus = iExitStatus;
}

void CBSLTaskInstance::SetFinalCPUTime(wxTimeSpan tsFinalCPUTime)
{
    m_tsFinalCPUTime = tsFinalCPUTime;
}

void CBSLTaskInstance::SetFinalElapsedTime(wxTimeSpan tsFinalElapsedTime)
{
    m_tsFinalElapsedTime = tsFinalElapsedTime;
}

void CBSLTaskInstance::SetFractionDone(wxDouble dFractionDone)
{
    m_dFractionDone = dFractionDone;
}

void CBSLTaskInstance::SetGraphicsApplication(wxString strGraphicsApplication)
{
    m_strGraphicsApplication = strGraphicsApplication;
    m_uiGraphicsApplicationHash = bslXMLStrHash32(m_strGraphicsApplication.c_str(), m_strGraphicsApplication.size());
}

void CBSLTaskInstance::SetWebGraphicsApplication(wxString strWebGraphicsApplication)
{
    m_strWebGraphicsApplication = strWebGraphicsApplication;
    m_uiWebGraphicsApplicationHash = bslXMLStrHash32(m_strWebGraphicsApplication.c_str(), m_strWebGraphicsApplication.size());
}

void CBSLTaskInstance::SetRemoteDesktopAddress(wxString strRemoteDesktopAddress)
{
    m_strRemoteDesktopAddress = strRemoteDesktopAddress;
    m_uiRemoteDesktopAddressHash = bslXMLStrHash32(m_strRemoteDesktopAddress.c_str(), m_strRemoteDesktopAddress.size());
}

void CBSLTaskInstance::SetInterfaceSuspensionEnabled(bool bInterfaceSuspensionEnabled)
{
    m_bInterfaceSuspensionEnabled = bInterfaceSuspensionEnabled;
}

void CBSLTaskInstance::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLTaskInstance::SetProject(wxString strProject)
{
    m_strProject = strProject;
    m_uiProjectHash = bslXMLStrHash32(m_strProject.c_str(), m_strProject.size());
}

void CBSLTaskInstance::SetTaskActive(bool bTaskActive)
{
    m_bTaskActive = bTaskActive;
}

void CBSLTaskInstance::SetTaskName(wxString strTaskName)
{
    m_strTaskName = strTaskName;
    m_uiTaskNameHash = bslXMLStrHash32(m_strTaskName.c_str(), m_strTaskName.size());
}

void CBSLTaskInstance::SetAppName(wxString strAppName)
{
    m_strAppName = strAppName;
    m_uiAppNameHash = bslXMLStrHash32(m_strAppName.c_str(), m_strAppName.size());
}

void CBSLTaskInstance::SetAppVersion(wxUint32 uiAppVersion)
{
    m_uiAppVersion = uiAppVersion;
}

void CBSLTaskInstance::SetAppPlanClass(wxString strAppPlanClass)
{
    m_strAppPlanClass = strAppPlanClass;
    m_uiAppPlanClassHash = bslXMLStrHash32(m_strAppPlanClass.c_str(), m_strAppPlanClass.size());
}

void CBSLTaskInstance::SetPageFaultRate(wxUint64 ullPageFaultRate)
{
    m_ullPageFaultRate = ullPageFaultRate;
}

void CBSLTaskInstance::SetProcessID(wxUint32 uiProcessID)
{
    m_uiProcessID = uiProcessID;
}

void CBSLTaskInstance::SetReadyToReport(bool bReadyToReport)
{
    m_bReadyToReport = bReadyToReport;
}

void CBSLTaskInstance::SetReceivedTime(wxDateTime dtReceivedTime)
{
    m_dtReceivedTime = dtReceivedTime;
}

void CBSLTaskInstance::SetCompletedTime(wxDateTime dtCompletedTime)
{
    m_dtCompletedTime = dtCompletedTime;
}

void CBSLTaskInstance::SetReportDeadline(wxDateTime dtReportDeadline)
{
    m_dtReportDeadline = dtReportDeadline;
}

void CBSLTaskInstance::SetResourcesUtilized(wxString strResourcesUtilized)
{
    m_strResourcesUtilized = strResourcesUtilized;
    m_uiResourcesUtilizedHash = bslXMLStrHash32(m_strResourcesUtilized.c_str(), m_strResourcesUtilized.size());
}

void CBSLTaskInstance::SetSchedulerState(CBSLTaskInstance::SCHEDULERSTATE iSchedulerState)
{
    m_iSchedulerState = iSchedulerState;
}

void CBSLTaskInstance::SetServerAcknowledged(bool bServerAcknowledged)
{
    m_bServerAcknowledged = bServerAcknowledged;
}

void CBSLTaskInstance::SetSlotDirectory(wxString strSlotDirectory)
{
    m_strSlotDirectory = strSlotDirectory;
    m_uiSlotDirectoryHash = bslXMLStrHash32(m_strSlotDirectory.c_str(), m_strSlotDirectory.size());
}

void CBSLTaskInstance::SetSlotID(wxUint32 uiSlotID)
{
    m_uiSlotID = uiSlotID;
}

void CBSLTaskInstance::SetSupportsGraphics(bool bSupportsGraphics)
{
    m_bSupportsGraphics = bSupportsGraphics;
}

void CBSLTaskInstance::SetSwapSize(wxUint64 ullSwapSize)
{
    m_ullSwapSize = ullSwapSize;
}

void CBSLTaskInstance::SetTaskState(CBSLTaskInstance::TASKSTATE iTaskState)
{
    m_iTaskState = iTaskState;
}

void CBSLTaskInstance::SetWaitingOnScheduler(bool bWaitingOnScheduler)
{
    m_bWaitingOnScheduler = bWaitingOnScheduler;
}

void CBSLTaskInstance::SetWaitingOnMemory(bool bWaitingOnMemory)
{
    m_bWaitingOnMemory = bWaitingOnMemory;
}

void CBSLTaskInstance::SetWaitingOnSharedMemory(bool bWaitingOnSharedMemory)
{
    m_bWaitingOnSharedMemory = bWaitingOnSharedMemory;
}

void CBSLTaskInstance::SetWorkingSetSize(wxUint64 ullWorkingSetSize)
{
    m_ullWorkingSetSize = ullWorkingSetSize;
}

void CBSLTaskInstance::SetWorkingSetSizeSmoothed(wxUint64 ullWorkingSetSizeSmoothed)
{
    m_ullWorkingSetSizeSmoothed = ullWorkingSetSizeSmoothed;
}
