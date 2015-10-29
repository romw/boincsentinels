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


#define BSLXMLTAGHASH_GUIURLS \
    0xce2fc17b


CBSLProject::RPCREASON MapRPCReason(wxInt32 iRPCReason)
{
    switch (iRPCReason)
    {
        case 1:
            return CBSLProject::RPCReasonUserRequest;
            break;
        case 2:
            return CBSLProject::RPCReasonTaskInstanceDue;
            break;
        case 3:
            return CBSLProject::RPCReasonNeedWork;
            break;
        case 4:
            return CBSLProject::RPCReasonTrickleUp;
            break;
        case 5:
            return CBSLProject::RPCReasonAccountManagerRequest;
            break;
        case 6:
            return CBSLProject::RPCReasonInitialization;
            break;
        case 7:
            return CBSLProject::RPCReasonProjectRequest;
            break;
    }
    return CBSLProject::RPCReasonUnknown;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLProject, CBSLProjectEventData);

CBSLProject::CBSLProject() :
CBSLProjectEventData()
{
    Clear();
}

CBSLProject::~CBSLProject()
{
}

bool CBSLProject::operator== (const CBSLProject& bslProject) const
{
    if (m_dCreditUserTotal != bslProject.m_dCreditUserTotal) return false;
    if (m_dCreditUserAverage != bslProject.m_dCreditUserAverage) return false;
    if (m_dCreditHostTotal != bslProject.m_dCreditHostTotal) return false;
    if (m_dCreditHostAverage != bslProject.m_dCreditHostAverage) return false;
    if (m_dtSchedulerRPCMinimumTime != bslProject.m_dtSchedulerRPCMinimumTime) return false;
    if (m_dtSchedulerRPCNextTime != bslProject.m_dtSchedulerRPCNextTime) return false;
    if (m_dtSchedulerRPCLastSuccess != bslProject.m_dtSchedulerRPCLastSuccess) return false;
    if (m_iSchedulerRPCPending != bslProject.m_iSchedulerRPCPending) return false;
    if (m_uiSchedulerRPCFailureCount != bslProject.m_uiSchedulerRPCFailureCount) return false;
    if (m_uiHostID != bslProject.m_uiHostID) return false;
    if (m_uiResourceShare != bslProject.m_uiResourceShare) return false;
    if (m_dDCF != bslProject.m_dDCF) return false;
    if (m_dtCrossProjectIdTimestamp != bslProject.m_dtCrossProjectIdTimestamp) return false;
    if (m_bMasterFetchInProgress != bslProject.m_bMasterFetchInProgress) return false;
    if (m_uiMasterFetchFailureCount != bslProject.m_uiMasterFetchFailureCount) return false;
    if (m_bTricklePending != bslProject.m_bTricklePending) return false;
    if (m_uiATIBackoffInterval != bslProject.m_uiATIBackoffInterval) return false;
    if (m_dtATIBackoffTime != bslProject.m_dtATIBackoffTime) return false;
    if (m_bATIUsageDisabled != bslProject.m_bATIUsageDisabled) return false;
    if (m_uiCPUBackoffInterval != bslProject.m_uiCPUBackoffInterval) return false;
    if (m_dtCPUBackoffTime != bslProject.m_dtCPUBackoffTime) return false;
    if (m_bCPUUsageDisabled != bslProject.m_bCPUUsageDisabled) return false;
    if (m_uiNvidiaBackoffInterval != bslProject.m_uiNvidiaBackoffInterval) return false;
    if (m_dtNvidiaBackoffTime != bslProject.m_dtNvidiaBackoffTime) return false;
    if (m_bNvidiaUsageDisabled != bslProject.m_bNvidiaUsageDisabled) return false;
    if (m_bNonCPUIntensive != bslProject.m_bNonCPUIntensive) return false;
    if (m_bAccountManagementEnabled != bslProject.m_bAccountManagementEnabled) return false;
    if (m_bAnonymousPlatformEnabled != bslProject.m_bAnonymousPlatformEnabled) return false;
    if (m_bSchedulerRPCInProgress != bslProject.m_bSchedulerRPCInProgress) return false;
    if (m_bTaskAccumulationDisabled != bslProject.m_bTaskAccumulationDisabled) return false;
    if (m_bInterfaceSuspensionEnabled != bslProject.m_bInterfaceSuspensionEnabled) return false;
    if (m_uiMasterURLHash != bslProject.m_uiMasterURLHash) return false;
    if (m_uiProjectNameHash != bslProject.m_uiProjectNameHash) return false;
    if (m_uiUserNameHash != bslProject.m_uiUserNameHash) return false;
    if (m_uiTeamNameHash != bslProject.m_uiTeamNameHash) return false;
    if (m_uiCrossProjectIDHash != bslProject.m_uiCrossProjectIDHash) return false;
    if (m_oProjectLinks != bslProject.m_oProjectLinks) return false;
    return true;
}

bool CBSLProject::operator!= (const CBSLProject& bslProject) const
{
    return !(*this == bslProject);
}

void CBSLProject::Clear()
{
    m_strMasterURL.clear();
    m_uiMasterURLHash = 0;
    m_strProjectName.clear();
    m_uiProjectNameHash = 0;
    m_strUserName.clear();
    m_uiUserNameHash = 0;
    m_strTeamName.clear();
    m_uiTeamNameHash = 0;
    m_uiHostID = 0;
    m_uiResourceShare = 0;
    m_dDCF = 0.0;
    m_strCrossProjectID.clear();
    m_uiCrossProjectIDHash = 0;
    m_dtCrossProjectIdTimestamp = wxDateTime((time_t)0);
    m_dCreditUserTotal = 0.0;
    m_dCreditUserAverage = 0.0;
    m_dCreditHostTotal = 0.0;
    m_dCreditHostAverage = 0.0;
    m_bMasterFetchInProgress = false;
    m_uiMasterFetchFailureCount = 0;
    m_dtSchedulerRPCMinimumTime = wxDateTime((time_t)0);
    m_dtSchedulerRPCNextTime = wxDateTime((time_t)0);
    m_dtSchedulerRPCLastSuccess = wxDateTime((time_t)0);
    m_iSchedulerRPCPending = RPCReasonUnknown;
    m_uiSchedulerRPCFailureCount = 0;
    m_bTricklePending = false;
    m_uiATIBackoffInterval = 0;
    m_dtATIBackoffTime = wxDateTime((time_t)0);
    m_bATIUsageDisabled = false;
    m_uiCPUBackoffInterval = 0;
    m_dtCPUBackoffTime = wxDateTime((time_t)0);
    m_bCPUUsageDisabled = false;
    m_uiNvidiaBackoffInterval = 0;
    m_dtNvidiaBackoffTime = wxDateTime((time_t)0);
    m_bNvidiaUsageDisabled = false;
    m_bNonCPUIntensive = false;
    m_bAccountManagementEnabled = false;
    m_bAnonymousPlatformEnabled = false;
    m_bSchedulerRPCInProgress = false;
    m_bTaskAccumulationDisabled = false;
    m_bInterfaceSuspensionEnabled = false;
    m_oProjectLinks.clear();
}

wxUint32 CBSLProject::GetATIBackoffInterval()
{
    return m_uiATIBackoffInterval;
}

wxDateTime& CBSLProject::GetATIBackoffTime()
{
    return m_dtATIBackoffTime;
}

wxUint32 CBSLProject::GetCPUBackoffInterval()
{
    return m_uiCPUBackoffInterval;
}

wxDateTime& CBSLProject::GetCPUBackoffTime()
{
    return m_dtCPUBackoffTime;
}

wxDouble CBSLProject::GetCreditHostTotal()
{
    return m_dCreditHostTotal;
}

wxDouble CBSLProject::GetCreditHostAverage()
{
    return m_dCreditHostAverage;
}

wxDouble CBSLProject::GetCreditUserTotal()
{
    return m_dCreditUserTotal;
}

wxDouble CBSLProject::GetCreditUserAverage()
{
    return m_dCreditUserAverage;
}

wxString& CBSLProject::GetCrossProjectID()
{
    return m_strCrossProjectID;
}

wxDateTime& CBSLProject::GetCrossProjectIdTimestamp()
{
    return m_dtCrossProjectIdTimestamp;
}

wxDouble CBSLProject::GetDCF()
{
    return m_dDCF;
}

wxUint32 CBSLProject::GetHostID()
{
    return m_uiHostID;
}

wxUint32 CBSLProject::GetMasterFetchFailureCount()
{
    return m_uiMasterFetchFailureCount;
}

wxString& CBSLProject::GetMasterURL()
{
    return m_strMasterURL;
}

wxUint32 CBSLProject::GetMasterURLHash()
{
    return m_uiMasterURLHash;
}

wxUint32 CBSLProject::GetNvidiaBackoffInterval()
{
    return m_uiNvidiaBackoffInterval;
}

wxDateTime& CBSLProject::GetNvidiaBackoffTime()
{
    return m_dtNvidiaBackoffTime;
}

wxString& CBSLProject::GetProjectName()
{
    return m_strProjectName;
}

wxUint32 CBSLProject::GetProjectNameHash()
{
    return m_uiProjectNameHash;
}

wxUint32 CBSLProject::GetResourceShare()
{
    return m_uiResourceShare;
}

wxUint32 CBSLProject::GetSchedulerRPCFailureCount()
{
    return m_uiSchedulerRPCFailureCount;
}

CBSLProject::RPCREASON CBSLProject::GetSchedulerRPCPending()
{
    return m_iSchedulerRPCPending;
}

wxDateTime& CBSLProject::GetSchedulerRPCLastSuccess()
{
    return m_dtSchedulerRPCLastSuccess;
}

wxDateTime& CBSLProject::GetSchedulerRPCMinimumTime()
{
    return m_dtSchedulerRPCMinimumTime;
}

wxDateTime& CBSLProject::GetSchedulerRPCNextTime()
{
    return m_dtSchedulerRPCNextTime;
}

wxString& CBSLProject::GetTeamName()
{
    return m_strTeamName;
}

wxUint32 CBSLProject::GetTeamNameHash()
{
    return m_uiTeamNameHash;
}

wxString& CBSLProject::GetUserName()
{
    return m_strUserName;
}

wxUint32 CBSLProject::GetUserNameHash()
{
    return m_uiUserNameHash;
}

std::vector<CBSLProjectLink>& CBSLProject::GetProjectLinks()
{
    return m_oProjectLinks;
}

bool CBSLProject::IsAccountManagementEnabled()
{
    return m_bAccountManagementEnabled;
}

bool CBSLProject::IsAnonymousPlatformEnabled()
{
    return m_bAnonymousPlatformEnabled;
}

bool CBSLProject::IsATIUsageDisabled()
{
    return m_bATIUsageDisabled;
}

bool CBSLProject::IsCPUUsageDisabled()
{
    return m_bCPUUsageDisabled;
}

bool CBSLProject::IsInterfaceSuspensionEnabled()
{
    return m_bInterfaceSuspensionEnabled;
}

bool CBSLProject::IsMasterFetchInProgress()
{
    return m_bMasterFetchInProgress;
}

bool CBSLProject::IsNonCPUIntensive()
{
    return m_bNonCPUIntensive;
}

bool CBSLProject::IsNvidiaUsageDisabled()
{
    return m_bNvidiaUsageDisabled;
}

bool CBSLProject::IsSchedulerRPCInProgress()
{
    return m_bSchedulerRPCInProgress;
}

bool CBSLProject::IsTaskAccumulationDisabled()
{
    return m_bTaskAccumulationDisabled;
}

bool CBSLProject::IsTricklePending()
{
    return m_bTricklePending;
}

BSLERRCODE CBSLProject::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;
    CBSLProjectLink bslProjectLink;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECT == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        if (BSLXMLTAGHASH_GUIURLS == oElement.GetNameHash())
        {
            while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
            {
                if (BSLXMLTAGHASH_GUIURLS == oElement.GetNameHash()) break;
                if (BSLXMLTAGHASH_PROJECTLINK == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType())
                {
                    bslProjectLink.ParseEx(oDocument);
                    m_oProjectLinks.push_back(bslProjectLink);
                }
            }
        }
        else
        {
            switch(oElement.GetNameHash())
            {
                case 0xda55ae25:    // master_url
                    m_strMasterURL = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiMasterURLHash = oElement.GetValueHash();
                    break;
                case 0x443f1326:    // project_name
                    m_strProjectName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiProjectNameHash = oElement.GetValueHash();
                    break;
                case 0x4ecb8436:    // user_name
                    m_strUserName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiUserNameHash = oElement.GetValueHash();
                    break;
                case 0x097cb868:    // team_name
                    m_strTeamName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiTeamNameHash = oElement.GetValueHash();
                    break;
                case 0x8707d144:    // hostid
                    m_uiHostID = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x7a63081d:    // resource_share
                    m_uiResourceShare = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x57358bce:    // duration_correction_factor
                    m_dDCF = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                    break;
                case 0x21811787:    // cross_project_id
                    m_strCrossProjectID = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiCrossProjectIDHash = oElement.GetValueHash();
                    break;
                case 0xc3c1a7b9:    // cpid_time
                    m_dtCrossProjectIdTimestamp = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                    break;
                case 0x511c9d55:    // user_total_credit
                    m_dCreditUserTotal = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                    break;
                case 0xdab7f530:    // user_expavg_credit
                    m_dCreditUserAverage = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                    break;
                case 0x018aff20:    // host_total_credit
                    m_dCreditHostTotal = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                    break;
                case 0xd105bfe3:    // host_expavg_credit
                    m_dCreditHostAverage = CBSLXMLConverterEx::ConvertToDouble(oElement.GetValue());
                    break;
                case 0x5fca5184:    // master_url_fetch_pending
                    m_bMasterFetchInProgress = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0x9f441c8c:    // master_fetch_failures
                    m_uiMasterFetchFailureCount = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xc02db20e:    // sched_rpc_pending
                    m_iSchedulerRPCPending = MapRPCReason(CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue()));
                    break;
                case 0xe7db6551:    // min_rpc_time
                    m_dtSchedulerRPCMinimumTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                    break;
                case 0xdbe40dfe:    // next_rpc_time
                    m_dtSchedulerRPCNextTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                    break;
                case 0x1be6d977:    // last_rpc_time
                    m_dtSchedulerRPCLastSuccess = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                    break;
                case 0xc559b390:    // nrpc_failures
                    m_uiSchedulerRPCFailureCount = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x7a0e6811:    // trickle_up_pending
                    m_bTricklePending = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0x540e2ee9:    // non_cpu_intensive
                    m_bNonCPUIntensive = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0xe602b99d:    // attached_via_acct_mgr
                    m_bAccountManagementEnabled = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0x061362b6:    // anonymous_platform
                    m_bAnonymousPlatformEnabled = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0xdc05a676:    // dont_request_more_work
                    m_bTaskAccumulationDisabled = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0xd3920721:    // suspended_via_gui
                    m_bInterfaceSuspensionEnabled = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0x09c0d214:    // scheduler_rpc_in_progress
                    m_bSchedulerRPCInProgress = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                default:
#ifdef __WXDEBUG__
                    wxLogTrace(
                        wxT("BSLCommon Parser"),
                        wxT("CBSLProject::ParseEx: Hash: '0x%x', Name: '%s'"),
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
    }

    return BSLERR_SUCCESS;
}

void CBSLProject::SetAccountManagementEnabled(bool bAccountManagementEnabled)
{
    m_bAccountManagementEnabled = bAccountManagementEnabled;
}

void CBSLProject::SetAnonymousPlatformEnabled(bool bAnonymousPlatformEnabled)
{
    m_bAnonymousPlatformEnabled = bAnonymousPlatformEnabled;
}

void CBSLProject::SetATIBackoffInterval(wxUint32 uiATIBackoffInterval)
{
    m_uiATIBackoffInterval = uiATIBackoffInterval;
}

void CBSLProject::SetATIBackoffTime(wxDateTime dtATIBackoffTime)
{
    m_dtATIBackoffTime = dtATIBackoffTime;
}

void CBSLProject::SetATIUsageDisabled(bool bATIUsageDisabled)
{
    m_bATIUsageDisabled = bATIUsageDisabled;
}

void CBSLProject::SetCPUBackoffInterval(wxUint32 uiCPUBackoffInterval)
{
    m_uiCPUBackoffInterval = uiCPUBackoffInterval;
}

void CBSLProject::SetCPUBackoffTime(wxDateTime dtCPUBackoffTime)
{
    m_dtCPUBackoffTime = dtCPUBackoffTime;
}

void CBSLProject::SetCPUUsageDisabled(bool bCPUUsageDisabled)
{
    m_bCPUUsageDisabled = bCPUUsageDisabled;
}

void CBSLProject::SetCreditHostTotal(wxDouble dCreditHostTotal)
{
    m_dCreditHostTotal = dCreditHostTotal;
}

void CBSLProject::SetCreditHostAverage(wxDouble dCreditHostAverage)
{
    m_dCreditHostAverage = dCreditHostAverage;
}

void CBSLProject::SetCreditUserTotal(wxDouble dCreditUserTotal)
{
    m_dCreditUserTotal = dCreditUserTotal;
}

void CBSLProject::SetCreditUserAverage(wxDouble dCreditUserAverage)
{
    m_dCreditUserAverage = dCreditUserAverage;
}

void CBSLProject::SetCrossProjectID(wxString strCrossProjectID)
{
    m_strCrossProjectID = strCrossProjectID;
    m_uiCrossProjectIDHash = bslXMLStrHash32(m_strCrossProjectID.c_str(), m_strCrossProjectID.size());
}

void CBSLProject::SetCrossProjectIdTimestamp(wxDateTime dtCrossProjectIdTimestamp)
{
    m_dtCrossProjectIdTimestamp = dtCrossProjectIdTimestamp;
}

void CBSLProject::SetDCF(wxDouble dDCF)
{
    m_dDCF = dDCF;
}

void CBSLProject::SetHostID(wxUint32 uiHostID)
{
    m_uiHostID = uiHostID;
}

void CBSLProject::SetInterfaceSuspensionEnabled(bool bInterfaceSuspensionEnabled)
{
    m_bInterfaceSuspensionEnabled = bInterfaceSuspensionEnabled;
}

void CBSLProject::SetMasterFetchFailureCount(wxUint32 uiMasterFetchFailureCount)
{
    m_uiMasterFetchFailureCount = uiMasterFetchFailureCount;
}

void CBSLProject::SetMasterFetchInProgress(bool bMasterFetchInProgress)
{
    m_bMasterFetchInProgress = bMasterFetchInProgress;
}

void CBSLProject::SetMasterURL(wxString strMasterURL)
{
    m_strMasterURL = strMasterURL;
    m_uiMasterURLHash = bslXMLStrHash32(m_strMasterURL.c_str(), m_strMasterURL.size());
}

void CBSLProject::SetNonCPUIntensive(bool bNonCPUIntensive)
{
    m_bNonCPUIntensive = bNonCPUIntensive;
}

void CBSLProject::SetNvidiaBackoffInterval(wxUint32 uiNvidiaBackoffInterval)
{
    m_uiNvidiaBackoffInterval = uiNvidiaBackoffInterval;
}

void CBSLProject::SetNvidiaBackoffTime(wxDateTime dtNvidiaBackoffTime)
{
    m_dtNvidiaBackoffTime = dtNvidiaBackoffTime;
}

void CBSLProject::SetNvidiaUsageDisabled(bool bNvidiaUsageDisabled)
{
    m_bNvidiaUsageDisabled = bNvidiaUsageDisabled;
}

void CBSLProject::SetProjectName(wxString strProjectName)
{
    m_strProjectName = strProjectName;
    m_uiProjectNameHash = bslXMLStrHash32(m_strProjectName.c_str(), m_strProjectName.size());
}

void CBSLProject::SetResourceShare(wxUint32 uiResourceShare)
{
    m_uiResourceShare = uiResourceShare;
}

void CBSLProject::SetSchedulerRPCFailureCount(wxUint32 uiSchedulerRPCFailureCount)
{
    m_uiSchedulerRPCFailureCount = uiSchedulerRPCFailureCount;
}

void CBSLProject::SetSchedulerRPCPending(RPCREASON iSchedulerRPCPending)
{
    m_iSchedulerRPCPending = iSchedulerRPCPending;
}

void CBSLProject::SetSchedulerRPCInProgress(bool bSchedulerRPCInProgress)
{
    m_bSchedulerRPCInProgress = bSchedulerRPCInProgress;
}

void CBSLProject::SetSchedulerRPCLastSuccess(wxDateTime dtSchedulerRPCLastSuccess)
{
    m_dtSchedulerRPCLastSuccess = dtSchedulerRPCLastSuccess;
}

void CBSLProject::SetSchedulerRPCMinimumTime(wxDateTime dtSchedulerRPCMinimumTime)
{
    m_dtSchedulerRPCMinimumTime = dtSchedulerRPCMinimumTime;
}

void CBSLProject::SetSchedulerRPCNextTime(wxDateTime dtSchedulerRPCNextTime)
{
    m_dtSchedulerRPCNextTime = dtSchedulerRPCNextTime;
}

void CBSLProject::SetTaskAccumulationDisabled(bool bTaskAccumulationDisabled)
{
    m_bTaskAccumulationDisabled = bTaskAccumulationDisabled;
}

void CBSLProject::SetTeamName(wxString strTeamName)
{
    m_strTeamName = strTeamName;
    m_uiTeamNameHash = bslXMLStrHash32(m_strTeamName.c_str(), m_strTeamName.size());
}

void CBSLProject::SetTricklePending(bool bTricklePending)
{
    m_bTricklePending = bTricklePending;
}

void CBSLProject::SetUserName(wxString strUserName)
{
    m_strUserName = strUserName;
    m_uiUserNameHash = bslXMLStrHash32(m_strUserName.c_str(), m_strUserName.size());
}

void CBSLProject::SetProjectLinks(std::vector<CBSLProjectLink>& oProjectLinks)
{
    m_oProjectLinks = oProjectLinks;
}
