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
#include "bslProjectTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectTestCase);

void ProjectTestCase::CreateDelete()
{
    CBSLProject* pProject = new CBSLProject();
    CPPUNIT_ASSERT(pProject != NULL);
    delete pProject;
}

void ProjectTestCase::Equality()
{
    CBSLProject* pProject = new CBSLProject();
    CBSLProject* pProject2 = new CBSLProject();
    CPPUNIT_ASSERT(*pProject == *pProject2);
    delete pProject;
    delete pProject2;
}

void ProjectTestCase::Inequality()
{
    CBSLProject* pProject = new CBSLProject();
    CBSLProject* pProject2 = new CBSLProject();
    wxString strProjectName = wxT("Blah@Home");
    pProject->SetProjectName(strProjectName);
    CPPUNIT_ASSERT(*pProject != *pProject2);
    delete pProject;
    delete pProject2;
}

void ProjectTestCase::AssignmentOperator()
{
    CBSLProject* pProject = new CBSLProject();
    CBSLProject* pProject2 = new CBSLProject();
    wxString strProjectName = wxT("Blah@Home");
    pProject->SetProjectName(strProjectName);
    *pProject2 = *pProject;
    CPPUNIT_ASSERT(pProject->GetProjectName() == pProject2->GetProjectName());
    delete pProject;
    delete pProject2;
}

void ProjectTestCase::GetSetATIBackoffInterval()
{
    CBSLProject* pProject = new CBSLProject();
    wxUint32 uiATIBackoffInterval = 31416;
    pProject->SetATIBackoffInterval(uiATIBackoffInterval);
    CPPUNIT_ASSERT(uiATIBackoffInterval == pProject->GetATIBackoffInterval());
    delete pProject;
}

void ProjectTestCase::GetSetATIBackoffTime()
{
    CBSLProject* pProject = new CBSLProject();
    wxDateTime dtNow = wxDateTime::Now();
    pProject->SetATIBackoffTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pProject->GetATIBackoffTime());
    delete pProject;
}

void ProjectTestCase::GetSetCPUBackoffInterval()
{
    CBSLProject* pProject = new CBSLProject();
    wxUint32 uiCPUBackoffInterval = 31416;
    pProject->SetCPUBackoffInterval(uiCPUBackoffInterval);
    CPPUNIT_ASSERT(uiCPUBackoffInterval == pProject->GetCPUBackoffInterval());
    delete pProject;
}

void ProjectTestCase::GetSetCPUBackoffTime()
{
    CBSLProject* pProject = new CBSLProject();
    wxDateTime dtNow = wxDateTime::Now();
    pProject->SetCPUBackoffTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pProject->GetCPUBackoffTime());
    delete pProject;
}

void ProjectTestCase::GetSetCreditHostTotal()
{
    CBSLProject* pProject = new CBSLProject();
    wxDouble dCreditHostTotal = 3.1416;
    pProject->SetCreditHostTotal(dCreditHostTotal);
    CPPUNIT_ASSERT(dCreditHostTotal == pProject->GetCreditHostTotal());
    delete pProject;
}

void ProjectTestCase::GetSetCreditHostAverage()
{
    CBSLProject* pProject = new CBSLProject();
    wxDouble dCreditHostAverage = 3.1416;
    pProject->SetCreditHostAverage(dCreditHostAverage);
    CPPUNIT_ASSERT(dCreditHostAverage == pProject->GetCreditHostAverage());
    delete pProject;
}

void ProjectTestCase::GetSetCreditUserTotal()
{
    CBSLProject* pProject = new CBSLProject();
    wxDouble dCreditUserTotal = 3.1416;
    pProject->SetCreditUserTotal(dCreditUserTotal);
    CPPUNIT_ASSERT(dCreditUserTotal == pProject->GetCreditUserTotal());
    delete pProject;
}

void ProjectTestCase::GetSetCreditUserAverage()
{
    CBSLProject* pProject = new CBSLProject();
    wxDouble dCreditUserAverage = 3.1416;
    pProject->SetCreditUserAverage(dCreditUserAverage);
    CPPUNIT_ASSERT(dCreditUserAverage == pProject->GetCreditUserAverage());
    delete pProject;
}

void ProjectTestCase::GetSetCrossProjectID()
{
    CBSLProject* pProject = new CBSLProject();
    wxString strCrossProjectID = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");
    pProject->SetCrossProjectID(strCrossProjectID);
    CPPUNIT_ASSERT(strCrossProjectID == pProject->GetCrossProjectID());
    delete pProject;
}

void ProjectTestCase::GetSetCrossProjectIdTimestamp()
{
    CBSLProject* pProject = new CBSLProject();
    wxDateTime dtNow = wxDateTime::Now();
    pProject->SetCrossProjectIdTimestamp(dtNow);
    CPPUNIT_ASSERT(dtNow == pProject->GetCrossProjectIdTimestamp());
    delete pProject;
}

void ProjectTestCase::GetSetDCF()
{
    CBSLProject* pProject = new CBSLProject();
    wxDouble dDCF = 3.1416;
    pProject->SetDCF(dDCF);
    CPPUNIT_ASSERT(dDCF == pProject->GetDCF());
    delete pProject;
}

void ProjectTestCase::GetSetHostID()
{
    CBSLProject* pProject = new CBSLProject();
    wxUint32 uiHostID = 31416;
    pProject->SetHostID(uiHostID);
    CPPUNIT_ASSERT(uiHostID == pProject->GetHostID());
    delete pProject;
}

void ProjectTestCase::GetSetMasterFetchFailureCount()
{
    CBSLProject* pProject = new CBSLProject();
    wxUint32 uiMasterFetchFailureCount = 31416;
    pProject->SetMasterFetchFailureCount(uiMasterFetchFailureCount);
    CPPUNIT_ASSERT(uiMasterFetchFailureCount == pProject->GetMasterFetchFailureCount());
    delete pProject;
}

void ProjectTestCase::GetSetMasterURL()
{
    CBSLProject* pProject = new CBSLProject();
    wxString strMasterURL = wxT("http://rick.example.com/");
    pProject->SetMasterURL(strMasterURL);
    CPPUNIT_ASSERT(strMasterURL == pProject->GetMasterURL());
    delete pProject;
}

void ProjectTestCase::GetSetNvidiaBackoffInterval()
{
    CBSLProject* pProject = new CBSLProject();
    wxUint32 uiNvidiaBackoffInterval = 31416;
    pProject->SetNvidiaBackoffInterval(uiNvidiaBackoffInterval);
    CPPUNIT_ASSERT(uiNvidiaBackoffInterval == pProject->GetNvidiaBackoffInterval());
    delete pProject;
}

void ProjectTestCase::GetSetNvidiaBackoffTime()
{
    CBSLProject* pProject = new CBSLProject();
    wxDateTime dtNow = wxDateTime::Now();
    pProject->SetNvidiaBackoffTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pProject->GetNvidiaBackoffTime());
    delete pProject;
}

void ProjectTestCase::GetSetProjectName()
{
    CBSLProject* pProject = new CBSLProject();
    wxString strProjectName = wxT("Blah@Home");
    pProject->SetProjectName(strProjectName);
    CPPUNIT_ASSERT(strProjectName == pProject->GetProjectName());
    delete pProject;
}

void ProjectTestCase::GetSetResourceShare()
{
    CBSLProject* pProject = new CBSLProject();
    wxUint32 uiResourceShare = 31416;
    pProject->SetResourceShare(uiResourceShare);
    CPPUNIT_ASSERT(uiResourceShare == pProject->GetResourceShare());
    delete pProject;
}

void ProjectTestCase::GetSetSchedulerRPCFailureCount()
{
    CBSLProject* pProject = new CBSLProject();
    wxUint32 uiSchedulerRPCFailureCount = 31416;
    pProject->SetSchedulerRPCFailureCount(uiSchedulerRPCFailureCount);
    CPPUNIT_ASSERT(uiSchedulerRPCFailureCount == pProject->GetSchedulerRPCFailureCount());
    delete pProject;
}

void ProjectTestCase::GetSetSchedulerRPCPending()
{
    CBSLProject* pProject = new CBSLProject();
    CBSLProject::RPCREASON iSchedulerRPCPending = CBSLProject::RPCReasonProjectRequest;
    pProject->SetSchedulerRPCPending(iSchedulerRPCPending);
    CPPUNIT_ASSERT(iSchedulerRPCPending == pProject->GetSchedulerRPCPending());
    delete pProject;
}

void ProjectTestCase::GetSetSchedulerRPCLastSuccess()
{
    CBSLProject* pProject = new CBSLProject();
    wxDateTime dtNow = wxDateTime::Now();
    pProject->SetSchedulerRPCLastSuccess(dtNow);
    CPPUNIT_ASSERT(dtNow == pProject->GetSchedulerRPCLastSuccess());
    delete pProject;
}

void ProjectTestCase::GetSetSchedulerRPCMinimumTime()
{
    CBSLProject* pProject = new CBSLProject();
    wxDateTime dtNow = wxDateTime::Now();
    pProject->SetSchedulerRPCMinimumTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pProject->GetSchedulerRPCMinimumTime());
    delete pProject;
}

void ProjectTestCase::GetSetSchedulerRPCNextTime()
{
    CBSLProject* pProject = new CBSLProject();
    wxDateTime dtNow = wxDateTime::Now();
    pProject->SetSchedulerRPCNextTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pProject->GetSchedulerRPCNextTime());
    delete pProject;
}

void ProjectTestCase::GetSetTeamName()
{
    CBSLProject* pProject = new CBSLProject();
    wxString strTeamName = wxT("blah blah blah");
    pProject->SetTeamName(strTeamName);
    CPPUNIT_ASSERT(strTeamName == pProject->GetTeamName());
    delete pProject;
}

void ProjectTestCase::GetSetUserName()
{
    CBSLProject* pProject = new CBSLProject();
    wxString strUserName = wxT("blah blah blah");
    pProject->SetUserName(strUserName);
    CPPUNIT_ASSERT(strUserName == pProject->GetUserName());
    delete pProject;
}

void ProjectTestCase::IsSetAccountManagementEnabled()
{
    CBSLProject* pProject = new CBSLProject();
    bool bAccountManagementEnabled = true;
    pProject->SetAccountManagementEnabled(bAccountManagementEnabled);
    CPPUNIT_ASSERT(bAccountManagementEnabled == pProject->IsAccountManagementEnabled());
    delete pProject;
}

void ProjectTestCase::IsSetAnonymousPlatformEnabled()
{
    CBSLProject* pProject = new CBSLProject();
    bool bAnonymousPlatformEnabled = true;
    pProject->SetAnonymousPlatformEnabled(bAnonymousPlatformEnabled);
    CPPUNIT_ASSERT(bAnonymousPlatformEnabled == pProject->IsAnonymousPlatformEnabled());
    delete pProject;
}

void ProjectTestCase::IsSetATIUsageDisabled()
{
    CBSLProject* pProject = new CBSLProject();
    bool bATIUsageDisabled = true;
    pProject->SetATIUsageDisabled(bATIUsageDisabled);
    CPPUNIT_ASSERT(bATIUsageDisabled == pProject->IsATIUsageDisabled());
    delete pProject;
}

void ProjectTestCase::IsSetCPUUsageDisabled()
{
    CBSLProject* pProject = new CBSLProject();
    bool bCPUUsageDisabled = true;
    pProject->SetCPUUsageDisabled(bCPUUsageDisabled);
    CPPUNIT_ASSERT(bCPUUsageDisabled == pProject->IsCPUUsageDisabled());
    delete pProject;
}

void ProjectTestCase::IsSetInterfaceSuspensionEnabled()
{
    CBSLProject* pProject = new CBSLProject();
    bool bInterfaceSuspensionEnabled = true;
    pProject->SetInterfaceSuspensionEnabled(bInterfaceSuspensionEnabled);
    CPPUNIT_ASSERT(bInterfaceSuspensionEnabled == pProject->IsInterfaceSuspensionEnabled());
    delete pProject;
}

void ProjectTestCase::IsSetMasterFetchInProgress()
{
    CBSLProject* pProject = new CBSLProject();
    bool bMasterFetchInProgress = true;
    pProject->SetMasterFetchInProgress(bMasterFetchInProgress);
    CPPUNIT_ASSERT(bMasterFetchInProgress == pProject->IsMasterFetchInProgress());
    delete pProject;
}

void ProjectTestCase::IsSetNonCPUIntensive()
{
    CBSLProject* pProject = new CBSLProject();
    bool bNonCPUIntensive = true;
    pProject->SetNonCPUIntensive(bNonCPUIntensive);
    CPPUNIT_ASSERT(bNonCPUIntensive == pProject->IsNonCPUIntensive());
    delete pProject;
}

void ProjectTestCase::IsSetNvidiaUsageDisabled()
{
    CBSLProject* pProject = new CBSLProject();
    bool bNvidiaUsageDisabled = true;
    pProject->SetNvidiaUsageDisabled(bNvidiaUsageDisabled);
    CPPUNIT_ASSERT(bNvidiaUsageDisabled == pProject->IsNvidiaUsageDisabled());
    delete pProject;
}

void ProjectTestCase::IsSetSchedulerRPCInProgress()
{
    CBSLProject* pProject = new CBSLProject();
    bool bSchedulerRPCInProgress = true;
    pProject->SetSchedulerRPCInProgress(bSchedulerRPCInProgress);
    CPPUNIT_ASSERT(bSchedulerRPCInProgress == pProject->IsSchedulerRPCInProgress());
    delete pProject;
}

void ProjectTestCase::IsSetTaskAccumulationDisabled()
{
    CBSLProject* pProject = new CBSLProject();
    bool bTaskAccumulationDisabled = true;
    pProject->SetTaskAccumulationDisabled(bTaskAccumulationDisabled);
    CPPUNIT_ASSERT(bTaskAccumulationDisabled == pProject->IsTaskAccumulationDisabled());
    delete pProject;
}

void ProjectTestCase::IsSetTricklePending()
{
    CBSLProject* pProject = new CBSLProject();
    bool bTricklePending = true;
    pProject->SetTricklePending(bTricklePending);
    CPPUNIT_ASSERT(bTricklePending == pProject->IsTricklePending());
    delete pProject;
}
