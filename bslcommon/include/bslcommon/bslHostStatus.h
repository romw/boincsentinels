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

#ifndef _BSLCOMMONHOSTSTATUS_H_
#define _BSLCOMMONHOSTSTATUS_H_

#define BSLXMLTAGHASH_HOSTSTATUS \
    0xf4466f80

class CBSLHostStatus: public CBSLHostStatusEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLHostStatus)

public:

    /// \brief Status of network connectivity
    /// \note  Values are directly compatible with default BOINC network status values.
    enum NETWORKSTATUS
    {
        NetworkStatusOnline = 0,
        NetworkStatusWantConnection = 1,
        NetworkStatusWantDisconnect = 2,
        NetworkStatusVerification = 3
    };

    /// \brief Reason for being suspended
    /// \note  Values are directly compatible with default BOINC suspend reason values.
    enum SUSPENDREASON
    {
        SuspendReasonUnknown = 0,
        SuspendReasonBatteries = 1,
        SuspendReasonUserActive = 2,
        SuspendReasonUserRequest = 4,
        SuspendReasonTimeOfDay = 8,
        SuspendReasonBenchmarks = 16,
        SuspendReasonDiskSpace = 32,
        SuspendReasonCPUThrottle = 64,
        SuspendReasonUserInactive = 128,
        SuspendReasonInitialDelay = 256,
        SuspendReasonExclusiveApplicationRunning = 512,
        SuspendReasonCPUUsage = 1024,
        SuspendReasonNetworkQuotaExceeded = 2048,
        SuspendReasonOS = 4096
    };

    /// \brief Run mode
    /// \note  Values are directly compatible with default BOINC run mode values.
    enum RUNMODE
    {
        RunModeUnknown = 0,
        RunModeAlways = 1,
        RunModeAuto = 2,
        RunModeNever = 3,
        RunModeRestore = 4
    };

    CBSLHostStatus();
    virtual ~CBSLHostStatus();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLHostStatus&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLHostStatus&) const;

    /// \brief Initialize CBSLHostStatus state.
    void Clear();

    /// \brief
    NETWORKSTATUS GetNetworkStatus();
    /// \brief
    SUSPENDREASON GetTaskSuspendReason();
    /// \brief
    RUNMODE GetTaskMode();
    /// \brief
    RUNMODE GetTaskModePermanent();
    /// \brief
    wxUint64 GetTaskSuspendTimeout();
    /// \brief
    SUSPENDREASON GetGPUSuspendReason();
    /// \brief
    RUNMODE GetGPUMode();
    /// \brief
    RUNMODE GetGPUModePermanent();
    /// \brief
    wxUint64 GetGPUSuspendTimeout();
    /// \brief
    SUSPENDREASON GetNetworkSuspendReason();
    /// \brief
    RUNMODE GetNetworkMode();
    /// \brief
    RUNMODE GetNetworkModePermanent();
    /// \brief
    wxUint64 GetNetworkSuspendTimeout();
    /// \brief
    bool IsAttachDisabled();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief
    void SetNetworkStatus(NETWORKSTATUS iNetworkStatus);
    /// \brief
    void SetTaskSuspendReason(SUSPENDREASON iTaskSuspendReason);
    /// \brief
    void SetTaskMode(RUNMODE iTaskMode);
    /// \brief
    void SetTaskModePermanent(RUNMODE iTaskModePermanent);
    /// \brief
    void SetTaskSuspendTimeout(wxUint64 ullTaskSuspendTimeout);
    /// \brief
    void SetGPUSuspendReason(SUSPENDREASON iGPUSuspendReason);
    /// \brief
    void SetGPUMode(RUNMODE iGPUMode);
    /// \brief
    void SetGPUModePermanent(RUNMODE iGPUModePermanent);
    /// \brief
    void SetGPUSuspendTimeout(wxUint64 ullGPUSuspendTimeout);
    /// \brief
    void SetNetworkSuspendReason(SUSPENDREASON iNetworkSuspendReason);
    /// \brief
    void SetNetworkMode(RUNMODE iNetworkMode);
    /// \brief
    void SetNetworkModePermanent(RUNMODE iNetworkModePermanent);
    /// \brief
    void SetNetworkSuspendTimeout(wxUint64 ullNetworkSuspendTimeout);
    /// \brief
    void SetAttachDisabled(bool bAttachDisabled);

private:
    NETWORKSTATUS m_iNetworkStatus;
    SUSPENDREASON m_iTaskSuspendReason;
    RUNMODE m_iTaskMode;
    RUNMODE m_iTaskModePermanent;
    wxUint64 m_ullTaskSuspendTimeout;
    SUSPENDREASON m_iGPUSuspendReason;
    RUNMODE m_iGPUMode;
    RUNMODE m_iGPUModePermanent;
    wxUint64 m_ullGPUSuspendTimeout;
    SUSPENDREASON m_iNetworkSuspendReason;
    RUNMODE m_iNetworkMode;
    RUNMODE m_iNetworkModePermanent;
    wxUint64 m_ullNetworkSuspendTimeout;
    bool m_bAttachDisabled;
};

#endif

///
/// \}
