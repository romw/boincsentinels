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


CBSLHostStatus::NETWORKSTATUS MapNetworkStatus(wxInt32 iNetworkStatus)
{
    switch (iNetworkStatus)
    {
        case 1:
            return CBSLHostStatus::NetworkStatusWantConnection;
            break;
        case 2:
            return CBSLHostStatus::NetworkStatusWantDisconnect;
            break;
        case 3:
            return CBSLHostStatus::NetworkStatusVerification;
            break;
    }
    return CBSLHostStatus::NetworkStatusOnline;
}

CBSLHostStatus::SUSPENDREASON MapSuspendReason(wxInt32 iSuspendReason)
{
    switch (iSuspendReason)
    {
        case 1:
            return CBSLHostStatus::SuspendReasonBatteries;
            break;
        case 2:
            return CBSLHostStatus::SuspendReasonUserActive;
            break;
        case 4:
            return CBSLHostStatus::SuspendReasonUserRequest;
            break;
        case 8:
            return CBSLHostStatus::SuspendReasonTimeOfDay;
            break;
        case 16:
            return CBSLHostStatus::SuspendReasonBenchmarks;
            break;
        case 32:
            return CBSLHostStatus::SuspendReasonDiskSpace;
            break;
        case 64:
            return CBSLHostStatus::SuspendReasonCPUThrottle;
            break;
        case 128:
            return CBSLHostStatus::SuspendReasonUserInactive;
            break;
        case 256:
            return CBSLHostStatus::SuspendReasonInitialDelay;
            break;
        case 512:
            return CBSLHostStatus::SuspendReasonExclusiveApplicationRunning;
            break;
        case 1024:
            return CBSLHostStatus::SuspendReasonCPUUsage;
            break;
        case 2048:
            return CBSLHostStatus::SuspendReasonNetworkQuotaExceeded;
            break;
        case 4096:
            return CBSLHostStatus::SuspendReasonOS;
            break;
    }
    return CBSLHostStatus::SuspendReasonUnknown;
}

CBSLHostStatus::RUNMODE MapRunMode(wxInt32 iRunMode)
{
    switch (iRunMode)
    {
        case 1:
            return CBSLHostStatus::RunModeAlways;
            break;
        case 2:
            return CBSLHostStatus::RunModeAuto;
            break;
        case 3:
            return CBSLHostStatus::RunModeNever;
            break;
        case 4:
            return CBSLHostStatus::RunModeRestore;
            break;
    }
    return CBSLHostStatus::RunModeUnknown;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLHostStatus, CBSLHostStatusEventData);

CBSLHostStatus::CBSLHostStatus() :
CBSLHostStatusEventData()
{
    Clear();
}

CBSLHostStatus::~CBSLHostStatus()
{
}

bool CBSLHostStatus::operator== (const CBSLHostStatus& bslHostStatus) const
{
    if (m_iNetworkStatus != bslHostStatus.m_iNetworkStatus) return false;
    if (m_iTaskSuspendReason != bslHostStatus.m_iTaskSuspendReason) return false;
    if (m_iTaskMode != bslHostStatus.m_iTaskMode) return false;
    if (m_iTaskModePermanent != bslHostStatus.m_iTaskModePermanent) return false;
    if (m_ullTaskSuspendTimeout != bslHostStatus.m_ullTaskSuspendTimeout) return false;
    if (m_iGPUSuspendReason != bslHostStatus.m_iGPUSuspendReason) return false;
    if (m_iGPUMode != bslHostStatus.m_iGPUMode) return false;
    if (m_iGPUModePermanent != bslHostStatus.m_iGPUModePermanent) return false;
    if (m_ullGPUSuspendTimeout != bslHostStatus.m_ullGPUSuspendTimeout) return false;
    if (m_iNetworkSuspendReason != bslHostStatus.m_iNetworkSuspendReason) return false;
    if (m_iNetworkMode != bslHostStatus.m_iNetworkMode) return false;
    if (m_iNetworkModePermanent != bslHostStatus.m_iNetworkModePermanent) return false;
    if (m_ullNetworkSuspendTimeout != bslHostStatus.m_ullNetworkSuspendTimeout) return false;
    if (m_bAttachDisabled != bslHostStatus.m_bAttachDisabled) return false;
    return true;
}

bool CBSLHostStatus::operator!= (const CBSLHostStatus& bslHostStatus) const
{
    return !(*this == bslHostStatus);
}

void CBSLHostStatus::Clear()
{
    m_iNetworkStatus = CBSLHostStatus::NetworkStatusOnline;
    m_iTaskSuspendReason = CBSLHostStatus::SuspendReasonUnknown;
    m_iTaskMode = CBSLHostStatus::RunModeUnknown;
    m_iTaskModePermanent = CBSLHostStatus::RunModeUnknown;
    m_ullTaskSuspendTimeout = 0;
    m_iGPUSuspendReason = CBSLHostStatus::SuspendReasonUnknown;
    m_iGPUMode = CBSLHostStatus::RunModeUnknown;
    m_iGPUModePermanent = CBSLHostStatus::RunModeUnknown;
    m_ullGPUSuspendTimeout = 0;
    m_iNetworkSuspendReason = CBSLHostStatus::SuspendReasonUnknown;
    m_iNetworkMode = CBSLHostStatus::RunModeUnknown;
    m_iNetworkModePermanent = CBSLHostStatus::RunModeUnknown;
    m_ullNetworkSuspendTimeout = 0;
    m_bAttachDisabled = false;
}

CBSLHostStatus::NETWORKSTATUS CBSLHostStatus::GetNetworkStatus()
{
    return m_iNetworkStatus;
}

CBSLHostStatus::SUSPENDREASON CBSLHostStatus::GetTaskSuspendReason()
{
    return m_iTaskSuspendReason;
}

CBSLHostStatus::RUNMODE CBSLHostStatus::GetTaskMode()
{
    return m_iTaskMode;
}

CBSLHostStatus::RUNMODE CBSLHostStatus::GetTaskModePermanent()
{
    return m_iTaskModePermanent;
}

wxUint64 CBSLHostStatus::GetTaskSuspendTimeout()
{
    return m_ullTaskSuspendTimeout;
}

CBSLHostStatus::SUSPENDREASON CBSLHostStatus::GetGPUSuspendReason()
{
    return m_iGPUSuspendReason;
}

CBSLHostStatus::RUNMODE CBSLHostStatus::GetGPUMode()
{
    return m_iGPUMode;
}

CBSLHostStatus::RUNMODE CBSLHostStatus::GetGPUModePermanent()
{
    return m_iGPUModePermanent;
}

wxUint64 CBSLHostStatus::GetGPUSuspendTimeout()
{
    return m_ullGPUSuspendTimeout;
}

CBSLHostStatus::SUSPENDREASON CBSLHostStatus::GetNetworkSuspendReason()
{
    return m_iNetworkSuspendReason;
}

CBSLHostStatus::RUNMODE CBSLHostStatus::GetNetworkMode()
{
    return m_iNetworkMode;
}

CBSLHostStatus::RUNMODE CBSLHostStatus::GetNetworkModePermanent()
{
    return m_iNetworkModePermanent;
}

wxUint64 CBSLHostStatus::GetNetworkSuspendTimeout()
{
    return m_ullNetworkSuspendTimeout;
}

bool CBSLHostStatus::IsAttachDisabled()
{
    return m_bAttachDisabled;
}

BSLERRCODE CBSLHostStatus::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_HOSTSTATUS == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0x74f8b97e:    // network_status
                m_iNetworkStatus = MapNetworkStatus(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0xc2b53cc2:    // task_suspend_reason
                m_iTaskSuspendReason = MapSuspendReason(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x7df8efdc:    // task_mode
                m_iTaskMode = MapRunMode(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x56e2ee9d:    // task_mode_perm
                m_iTaskModePermanent = MapRunMode(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x883da0ac:    // task_mode_delay
                m_ullTaskSuspendTimeout = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x0b08bb7f:    // gpu_suspend_reason
                m_iGPUSuspendReason = MapSuspendReason(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0xca3d6d59:    // gpu_mode
                m_iGPUMode = MapRunMode(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0xd97a0f0e:    // gpu_mode_perm
                m_iGPUModePermanent = MapRunMode(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x52f21b69:    // gpu_mode_delay
                m_ullGPUSuspendTimeout = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0xecb2710f:    // network_suspend_reason
                m_iNetworkSuspendReason = MapSuspendReason(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0xa84ba6c9:    // network_mode
                m_iNetworkMode = MapRunMode(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x46e62ffe:    // network_mode_perm
                m_iNetworkModePermanent = MapRunMode(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0xc6c5cb99:    // network_mode_delay
                m_ullNetworkSuspendTimeout = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x096b0322:    // disallow_attach
                m_bAttachDisabled = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLHostStatus::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLHostStatus::SetNetworkStatus(CBSLHostStatus::NETWORKSTATUS iNetworkStatus)
{
    m_iNetworkStatus = iNetworkStatus;
}

void CBSLHostStatus::SetTaskSuspendReason(CBSLHostStatus::SUSPENDREASON iTaskSuspendReason)
{
    m_iTaskSuspendReason = iTaskSuspendReason;
}

void CBSLHostStatus::SetTaskMode(CBSLHostStatus::RUNMODE iTaskMode)
{
    m_iTaskMode = iTaskMode;
}

void CBSLHostStatus::SetTaskModePermanent(CBSLHostStatus::RUNMODE iTaskModePermanent)
{
    m_iTaskModePermanent = iTaskModePermanent;
}

void CBSLHostStatus::SetTaskSuspendTimeout(wxUint64 ullTaskSuspendTimeout)
{
    m_ullTaskSuspendTimeout = ullTaskSuspendTimeout;
}

void CBSLHostStatus::SetGPUSuspendReason(CBSLHostStatus::SUSPENDREASON iGPUSuspendReason)
{
    m_iGPUSuspendReason = iGPUSuspendReason;
}

void CBSLHostStatus::SetGPUMode(CBSLHostStatus::RUNMODE iGPUMode)
{
    m_iGPUMode = iGPUMode;
}

void CBSLHostStatus::SetGPUModePermanent(CBSLHostStatus::RUNMODE iGPUModePermanent)
{
    m_iGPUModePermanent = iGPUModePermanent;
}

void CBSLHostStatus::SetGPUSuspendTimeout(wxUint64 ullGPUSuspendTimeout)
{
    m_ullGPUSuspendTimeout = ullGPUSuspendTimeout;
}

void CBSLHostStatus::SetNetworkSuspendReason(CBSLHostStatus::SUSPENDREASON iNetworkSuspendReason)
{
    m_iNetworkSuspendReason = iNetworkSuspendReason;
}

void CBSLHostStatus::SetNetworkMode(CBSLHostStatus::RUNMODE iNetworkMode)
{
    m_iNetworkMode = iNetworkMode;
}

void CBSLHostStatus::SetNetworkModePermanent(CBSLHostStatus::RUNMODE iNetworkModePermanent)
{
    m_iNetworkModePermanent = iNetworkModePermanent;
}

void CBSLHostStatus::SetNetworkSuspendTimeout(wxUint64 ullNetworkSuspendTimeout)
{
    m_ullNetworkSuspendTimeout = ullNetworkSuspendTimeout;
}

void CBSLHostStatus::SetAttachDisabled(bool bAttachDisabled)
{
    m_bAttachDisabled = bAttachDisabled;
}

