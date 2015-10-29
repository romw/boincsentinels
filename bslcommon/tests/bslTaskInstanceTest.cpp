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
#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>
#include "bslcommon/bslCommonTypes.h"
#include "bslTaskInstanceTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TaskInstanceTestCase);

void TaskInstanceTestCase::CreateDelete()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    CPPUNIT_ASSERT(pTaskInstance != NULL);
    delete pTaskInstance;
}

void TaskInstanceTestCase::Equality()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    CBSLTaskInstance* pTaskInstance2 = new CBSLTaskInstance();
    CPPUNIT_ASSERT(*pTaskInstance == *pTaskInstance2);
    delete pTaskInstance;
    delete pTaskInstance2;
}

void TaskInstanceTestCase::Inequality()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    CBSLTaskInstance* pTaskInstance2 = new CBSLTaskInstance();
    wxString strTaskInstanceName = wxT("Blah");
    pTaskInstance->SetName(strTaskInstanceName);
    CPPUNIT_ASSERT(*pTaskInstance != *pTaskInstance2);
    delete pTaskInstance;
    delete pTaskInstance2;
}

void TaskInstanceTestCase::AssignmentOperator()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    CBSLTaskInstance* pTaskInstance2 = new CBSLTaskInstance();
    wxString strTaskInstanceName = wxT("Blah");
    pTaskInstance->SetName(strTaskInstanceName);
    *pTaskInstance2 = *pTaskInstance;
    CPPUNIT_ASSERT(pTaskInstance->GetName() == pTaskInstance2->GetName());
    delete pTaskInstance;
    delete pTaskInstance2;
}

void TaskInstanceTestCase::GetSetActiveTaskState()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    CBSLTaskInstance::ACTIVETASKSTATE iActiveTaskState = CBSLTaskInstance::ActiveTaskStateQuitPending;
    pTaskInstance->SetActiveTaskState(iActiveTaskState);
    CPPUNIT_ASSERT(iActiveTaskState == pTaskInstance->GetActiveTaskState());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetCheckpointCPUTime()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxTimeSpan tsCheckpointCPUTime = 31416;
    pTaskInstance->SetCheckpointCPUTime(tsCheckpointCPUTime);
    CPPUNIT_ASSERT(tsCheckpointCPUTime == pTaskInstance->GetCheckpointCPUTime());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetCurrentCPUTime()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxTimeSpan tsCurrentCPUTime = 31416;
    pTaskInstance->SetCurrentCPUTime(tsCurrentCPUTime);
    CPPUNIT_ASSERT(tsCurrentCPUTime == pTaskInstance->GetCurrentCPUTime());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetElapsedTime()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxTimeSpan tsElapsedTime = 31416;
    pTaskInstance->SetElapsedTime(tsElapsedTime);
    CPPUNIT_ASSERT(tsElapsedTime == pTaskInstance->GetElapsedTime());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetEstimatedElapsedTimeRemaining()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxTimeSpan tsEstimatedElapsedTimeRemaining = 31416;
    pTaskInstance->SetEstimatedElapsedTimeRemaining(tsEstimatedElapsedTimeRemaining);
    CPPUNIT_ASSERT(tsEstimatedElapsedTimeRemaining == pTaskInstance->GetEstimatedElapsedTimeRemaining());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetExitStatus()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxInt32 iExitStatus = 31416;
    pTaskInstance->SetExitStatus(iExitStatus);
    CPPUNIT_ASSERT(iExitStatus == pTaskInstance->GetExitStatus());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetFinalCPUTime()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxTimeSpan tsFinalCPUTime = 31416;
    pTaskInstance->SetFinalCPUTime(tsFinalCPUTime);
    CPPUNIT_ASSERT(tsFinalCPUTime == pTaskInstance->GetFinalCPUTime());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetFinalElapsedTime()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxTimeSpan tsFinalElapsedTime = 31416;
    pTaskInstance->SetFinalElapsedTime(tsFinalElapsedTime);
    CPPUNIT_ASSERT(tsFinalElapsedTime == pTaskInstance->GetFinalElapsedTime());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetFractionDone()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxDouble dFractionDone = 3.1416;
    pTaskInstance->SetFractionDone(dFractionDone);
    CPPUNIT_ASSERT(dFractionDone == pTaskInstance->GetFractionDone());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetGraphicsApplication()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxString strGraphicsApplication = wxT("c:/temp/graphics.exe");
    pTaskInstance->SetGraphicsApplication(strGraphicsApplication);
    CPPUNIT_ASSERT(strGraphicsApplication == pTaskInstance->GetGraphicsApplication());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetName()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxString strName = wxT("blah blah blah");
    pTaskInstance->SetName(strName);
    CPPUNIT_ASSERT(strName == pTaskInstance->GetName());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetPageFaultRate()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxUint64 ullPageFaultRate = 31416;
    pTaskInstance->SetPageFaultRate(ullPageFaultRate);
    CPPUNIT_ASSERT(ullPageFaultRate == pTaskInstance->GetPageFaultRate());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetProcessID()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxUint32 uiProcessID = 31416;
    pTaskInstance->SetProcessID(uiProcessID);
    CPPUNIT_ASSERT(uiProcessID == pTaskInstance->GetProcessID());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetReceivedTime()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxDateTime dtNow = wxDateTime::Now();
    pTaskInstance->SetReceivedTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pTaskInstance->GetReceivedTime());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetReportDeadline()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxDateTime dtNow = wxDateTime::Now();
    pTaskInstance->SetReportDeadline(dtNow);
    CPPUNIT_ASSERT(dtNow == pTaskInstance->GetReportDeadline());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetResourcesUtilized()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxString strResourcesUtilized = wxT("blah blah blah");
    pTaskInstance->SetResourcesUtilized(strResourcesUtilized);
    CPPUNIT_ASSERT(strResourcesUtilized == pTaskInstance->GetResourcesUtilized());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetSchedulerState()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    CBSLTaskInstance::SCHEDULERSTATE iSchedulerState = CBSLTaskInstance::SchedulerStateScheduled;
    pTaskInstance->SetSchedulerState(iSchedulerState);
    CPPUNIT_ASSERT(iSchedulerState == pTaskInstance->GetSchedulerState());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetSlotDirectory()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxString strSlotDirectory = wxT("c:/temp/");
    pTaskInstance->SetSlotDirectory(strSlotDirectory);
    CPPUNIT_ASSERT(strSlotDirectory == pTaskInstance->GetSlotDirectory());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetSlotID()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxUint32 uiSlotID = 31416;
    pTaskInstance->SetSlotID(uiSlotID);
    CPPUNIT_ASSERT(uiSlotID == pTaskInstance->GetSlotID());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetSwapSize()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxUint64 ullSwapSize = 31416;
    pTaskInstance->SetSwapSize(ullSwapSize);
    CPPUNIT_ASSERT(ullSwapSize == pTaskInstance->GetSwapSize());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetTaskState()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    CBSLTaskInstance::TASKSTATE iTaskState = CBSLTaskInstance::TaskStateAborted;
    pTaskInstance->SetTaskState(iTaskState);
    CPPUNIT_ASSERT(iTaskState == pTaskInstance->GetTaskState());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetWorkingSetSize()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxUint64 ullWorkingSetSize = 31416;
    pTaskInstance->SetWorkingSetSize(ullWorkingSetSize);
    CPPUNIT_ASSERT(ullWorkingSetSize == pTaskInstance->GetWorkingSetSize());
    delete pTaskInstance;
}

void TaskInstanceTestCase::GetSetWorkingSetSizeSmoothed()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    wxUint64 ullWorkingSetSizeSmoothed = 31416;
    pTaskInstance->SetWorkingSetSizeSmoothed(ullWorkingSetSizeSmoothed);
    CPPUNIT_ASSERT(ullWorkingSetSizeSmoothed == pTaskInstance->GetWorkingSetSizeSmoothed());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetTaskActive()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bTaskActive = true;
    pTaskInstance->SetTaskActive(bTaskActive);
    CPPUNIT_ASSERT(bTaskActive == pTaskInstance->IsTaskActive());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetCoprocMissing()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bCoprocMissing = true;
    pTaskInstance->SetCoprocMissing(bCoprocMissing);
    CPPUNIT_ASSERT(bCoprocMissing == pTaskInstance->IsCoprocMissing());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetEDFScheduled()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bEDFScheduled = true;
    pTaskInstance->SetEDFScheduled(bEDFScheduled);
    CPPUNIT_ASSERT(bEDFScheduled == pTaskInstance->IsEDFScheduled());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetInterfaceSuspensionEnabled()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bInterfaceSuspensionEnabled = true;
    pTaskInstance->SetInterfaceSuspensionEnabled(bInterfaceSuspensionEnabled);
    CPPUNIT_ASSERT(bInterfaceSuspensionEnabled == pTaskInstance->IsInterfaceSuspensionEnabled());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetReadyToReport()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bReadyToReport = true;
    pTaskInstance->SetReadyToReport(bReadyToReport);
    CPPUNIT_ASSERT(bReadyToReport == pTaskInstance->IsReadyToReport());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetServerAcknowledged()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bServerAcknowledged = true;
    pTaskInstance->SetServerAcknowledged(bServerAcknowledged);
    CPPUNIT_ASSERT(bServerAcknowledged == pTaskInstance->IsServerAcknowledged());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetSupportsGraphics()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bSupportsGraphics = true;
    pTaskInstance->SetSupportsGraphics(bSupportsGraphics);
    CPPUNIT_ASSERT(bSupportsGraphics == pTaskInstance->IsSupportsGraphics());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetWaitingOnScheduler()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bWaitingOnScheduler = true;
    pTaskInstance->SetWaitingOnScheduler(bWaitingOnScheduler);
    CPPUNIT_ASSERT(bWaitingOnScheduler == pTaskInstance->IsWaitingOnScheduler());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetWaitingOnMemory()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bWaitingOnMemory = true;
    pTaskInstance->SetWaitingOnMemory(bWaitingOnMemory);
    CPPUNIT_ASSERT(bWaitingOnMemory == pTaskInstance->IsWaitingOnMemory());
    delete pTaskInstance;
}

void TaskInstanceTestCase::IsSetWaitingOnSharedMemory()
{
    CBSLTaskInstance* pTaskInstance = new CBSLTaskInstance();
    bool bWaitingOnSharedMemory = true;
    pTaskInstance->SetWaitingOnSharedMemory(bWaitingOnSharedMemory);
    CPPUNIT_ASSERT(bWaitingOnSharedMemory == pTaskInstance->IsWaitingOnSharedMemory());
    delete pTaskInstance;
}
