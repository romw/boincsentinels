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

#ifndef _BSLCOMMONPROJECT_H_
#define _BSLCOMMONPROJECT_H_

#include "bslProjectLink.h"

#define BSLXMLTAGHASH_PROJECT \
    0xe2447c34

class CBSLProject: public CBSLProjectEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLProject)

public:

    /// \brief Reason for the Scheduler RPC
    /// \note  Values are directly compatible with default BOINC message values.
    enum RPCREASON
    {
        RPCReasonUnknown = 0,
        RPCReasonUserRequest = 1,
        RPCReasonTaskInstanceDue = 2,
        RPCReasonNeedWork = 3,
        RPCReasonTrickleUp = 4,
        RPCReasonAccountManagerRequest = 5,
        RPCReasonInitialization = 6,
        RPCReasonProjectRequest = 7
    };

    CBSLProject();
    virtual ~CBSLProject();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLProject&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLProject&) const;

    /// \brief Initialize CBSLProject state.
    void Clear();

    /// \brief
    wxUint32 GetATIBackoffInterval();
    /// \brief
    wxDateTime& GetATIBackoffTime();
    /// \brief
    wxUint32 GetCPUBackoffInterval();
    /// \brief
    wxDateTime& GetCPUBackoffTime();
    /// \brief
    wxDouble GetCreditHostTotal();
    /// \brief
    wxDouble GetCreditHostAverage();
    /// \brief
    wxDouble GetCreditUserTotal();
    /// \brief
    wxDouble GetCreditUserAverage();
    /// \brief
    wxString& GetCrossProjectID();
    /// \brief
    wxDateTime& GetCrossProjectIdTimestamp();
    /// \brief
    wxDouble GetDCF();
    /// \brief
    wxUint32 GetHostID();
    /// \brief
    wxUint32 GetMasterFetchFailureCount();
    /// \brief
    wxString& GetMasterURL();
    /// \brief
    wxUint32 GetMasterURLHash();
    /// \brief
    wxUint32 GetNvidiaBackoffInterval();
    /// \brief
    wxDateTime& GetNvidiaBackoffTime();
    /// \brief
    wxString& GetProjectName();
    /// \brief
    wxUint32 GetProjectNameHash();
    /// \brief
    wxUint32 GetResourceShare();
    /// \brief
    wxUint32 GetSchedulerRPCFailureCount();
    /// \brief
    RPCREASON GetSchedulerRPCPending();
    /// \brief
    wxDateTime& GetSchedulerRPCLastSuccess();
    /// \brief
    wxDateTime& GetSchedulerRPCMinimumTime();
    /// \brief
    wxDateTime& GetSchedulerRPCNextTime();
    /// \brief
    wxString& GetTeamName();
    /// \brief
    wxUint32 GetTeamNameHash();
    /// \brief
    wxString& GetUserName();
    /// \brief
    wxUint32 GetUserNameHash();
    /// \brief
    std::vector<CBSLProjectLink>& GetProjectLinks();
    /// \brief
    bool IsAccountManagementEnabled();
    /// \brief
    bool IsAnonymousPlatformEnabled();
    /// \brief
    bool IsATIUsageDisabled();
    /// \brief
    bool IsCPUUsageDisabled();
    /// \brief
    bool IsInterfaceSuspensionEnabled();
    /// \brief
    bool IsMasterFetchInProgress();
    /// \brief
    bool IsNonCPUIntensive();
    /// \brief
    bool IsNvidiaUsageDisabled();
    /// \brief
    bool IsSchedulerRPCInProgress();
    /// \brief
    bool IsTaskAccumulationDisabled();
    /// \brief
    bool IsTricklePending();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief
    void SetAccountManagementEnabled(bool bAccountManagementEnabled);
    /// \brief
    void SetAnonymousPlatformEnabled(bool bAnonymousPlatformEnabled);
    /// \brief
    void SetATIBackoffInterval(wxUint32 uiATIBackoffInterval);
    /// \brief
    void SetATIBackoffTime(wxDateTime dtATIBackoffTime);
    /// \brief
    void SetATIUsageDisabled(bool bATIUsageDisabled);
    /// \brief
    void SetCPUBackoffInterval(wxUint32 uiCPUBackoffInterval);
    /// \brief
    void SetCPUBackoffTime(wxDateTime dtCPUBackoffTime);
    /// \brief
    void SetCPUUsageDisabled(bool bCPUUsageDisabled);
    /// \brief
    void SetCreditHostTotal(wxDouble dCreditHostTotal);
    /// \brief
    void SetCreditHostAverage(wxDouble dCreditHostAverage);
    /// \brief
    void SetCreditUserTotal(wxDouble dCreditUserTotal);
    /// \brief
    void SetCreditUserAverage(wxDouble dCreditUserAverage);
    /// \brief
    void SetCrossProjectID(wxString strCrossProjectID);
    /// \brief
    void SetCrossProjectIdTimestamp(wxDateTime dtCrossProjectIdTimestamp);
    /// \brief
    void SetDCF(wxDouble dDCF);
    /// \brief
    void SetHostID(wxUint32 uiHostID);
    /// \brief
    void SetInterfaceSuspensionEnabled(bool bInterfaceSuspensionEnabled);
    /// \brief
    void SetMasterFetchFailureCount(wxUint32 uiMasterFetchFailureCount);
    /// \brief
    void SetMasterFetchInProgress(bool bMasterFetchInProgress);
    /// \brief
    void SetMasterURL(wxString strMasterURL);
    /// \brief
    void SetNonCPUIntensive(bool bNonCPUIntensive);
    /// \brief
    void SetNvidiaBackoffInterval(wxUint32 uiNvidiaBackoffInterval);
    /// \brief
    void SetNvidiaBackoffTime(wxDateTime dtNvidiaBackoffTime);
    /// \brief
    void SetNvidiaUsageDisabled(bool bNvidiaUsageDisabled);
    /// \brief
    void SetProjectLinks(std::vector<CBSLProjectLink>& oProjectLinks);
    /// \brief
    void SetProjectName(wxString strProjectName);
    /// \brief
    void SetResourceShare(wxUint32 uiResourceShare);
    /// \brief
    void SetSchedulerRPCFailureCount(wxUint32 uiSchedulerRPCFailureCount);
    /// \brief
    void SetSchedulerRPCPending(RPCREASON iSchedulerRPCPending);
    /// \brief
    void SetSchedulerRPCInProgress(bool bSchedulerRPCInProgress);
    /// \brief
    void SetSchedulerRPCLastSuccess(wxDateTime dtSchedulerRPCLastSuccess);
    /// \brief
    void SetSchedulerRPCMinimumTime(wxDateTime dtSchedulerRPCMinimumTime);
    /// \brief
    void SetSchedulerRPCNextTime(wxDateTime dtSchedulerRPCNextTime);
    /// \brief
    void SetTaskAccumulationDisabled(bool bTaskAccumulationDisabled);
    /// \brief
    void SetTeamName(wxString strTeamName);
    /// \brief
    void SetTricklePending(bool bTricklePending);
    /// \brief
    void SetUserName(wxString strUserName);

private:
    wxString m_strMasterURL;
    wxUint32 m_uiMasterURLHash;
    wxString m_strProjectName;
    wxUint32 m_uiProjectNameHash;
    wxString m_strUserName;
    wxUint32 m_uiUserNameHash;
    wxString m_strTeamName;
    wxUint32 m_uiTeamNameHash;
    wxUint32 m_uiHostID;
    wxUint32 m_uiResourceShare;
    wxDouble m_dDCF;
    wxString m_strCrossProjectID;
    wxUint32 m_uiCrossProjectIDHash;
    wxDateTime m_dtCrossProjectIdTimestamp;
    wxDouble m_dCreditUserTotal;
    wxDouble m_dCreditUserAverage;
    wxDouble m_dCreditHostTotal;
    wxDouble m_dCreditHostAverage;
    bool m_bMasterFetchInProgress;
    wxUint32 m_uiMasterFetchFailureCount;
    wxDateTime m_dtSchedulerRPCMinimumTime;
    wxDateTime m_dtSchedulerRPCNextTime;
    wxDateTime m_dtSchedulerRPCLastSuccess;
    RPCREASON m_iSchedulerRPCPending;
    wxUint32 m_uiSchedulerRPCFailureCount;
    bool m_bTricklePending;
    wxUint32 m_uiATIBackoffInterval;
    wxDateTime m_dtATIBackoffTime;
    bool m_bATIUsageDisabled;
    wxUint32 m_uiCPUBackoffInterval;
    wxDateTime m_dtCPUBackoffTime;
    bool m_bCPUUsageDisabled;
    wxUint32 m_uiNvidiaBackoffInterval;
    wxDateTime m_dtNvidiaBackoffTime;
    bool m_bNvidiaUsageDisabled;
    bool m_bNonCPUIntensive;
    bool m_bAccountManagementEnabled;
    bool m_bAnonymousPlatformEnabled;
    bool m_bSchedulerRPCInProgress;
    bool m_bTaskAccumulationDisabled;
    bool m_bInterfaceSuspensionEnabled;
    std::vector<CBSLProjectLink> m_oProjectLinks;
};

#endif

///
/// \}
