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
#include "Instance.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateEvents.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "EventManager.h"
#include "RPCTypes.h"
#include "RPCManager.h"
#include "StateManager.h"

IMPLEMENT_DYNAMIC_CLASS(CClientState, wxObject);

CClientState::CClientState()
{
    m_bShutdownInitiated = false;

    m_pHostsDatabase = new CDatabase<CHost*>();
    wxASSERT(m_pHostsDatabase);
}

CClientState::~CClientState()
{
    // Cleanup the hosts before deleting the lock.
    delete m_pHostsDatabase;
    m_pHostsDatabase = NULL;

    m_bShutdownInitiated = true;
}

bool CClientState::OnInit()
{
    // Initialize the socket interfaces
    //
    wxSocketBase::Initialize();

    // Cache the local host names for future use.
    m_strLocalHostName = ::wxGetHostName().Lower();
    if (m_strLocalHostName.IsEmpty())
    {
        m_strLocalHostName = wxT("localhost");
    }
    m_strLocalFullHostName = ::wxGetFullHostName().Lower();
    if (m_strLocalFullHostName.IsEmpty())
    {
        m_strLocalFullHostName = wxT("localhost");
    }
    return true;
}

bool CClientState::OnExit()
{
    // Shutdown the socket interfaces
    // NOTE: We don't do this anymore, if the component that is using us also attempts to
    //   communicate with any other host machines using the wxWidget network stack we'll cause
    //   them to blow up by shutting down here.  It is best to let wxWidgets clean up the
    //   network stack as part of its normal shutdown procedure.
    //
    // wxSocketBase::Shutdown();
    return true;
}

BSLERRCODE CClientState::Connect(wxString& strName, wxString& strPassword, long lPort, bool bWait, BSLHOST* phHost)
{
    BSLERRCODE rc;
    CHost* pHost = NULL;
    CHost* pFindHost = NULL;
    std::vector<BSLHOST> oHosts;
    std::vector<BSLHOST>::iterator iter;

    if (strName.empty())
        return BSLERR_INVALID_PARAMETER;
    if (lPort < 0)
        return BSLERR_INVALID_PARAMETER;
    if (lPort > 65536)
        return BSLERR_INVALID_PARAMETER;


    // Do we already have a host entry?
    EnumerateHosts(oHosts);
    for (iter = oHosts.begin(); iter != oHosts.end(); iter++)
    {
        pFindHost = wxDynamicCast(*iter, CHost);
        if (0 == strName.CmpNoCase(pFindHost->GetName()))
        {
            pHost = pFindHost;
        }
    }

    if (pHost)
    {
        // Use existing host entry and re-populate its connection settings
        pHost->SetConnectionProperties(strName, strPassword, lPort);
    }
    else
    {
        // Create new host entry if we do not already have one
        pHost = new CHost();
        pHost->SetHostHandle((BSLHOST) pHost);
        pHost->SetConnectionProperties(strName, strPassword, lPort);

        // Add host to the hosts database
        AddHost(pHost);
    }

    // Notify the caller of the new host handle
    if (phHost)
    {
        *phHost = (BSLHOST) pHost;
    }

    if (bWait)
    {
        // Begin the connection process in the UI thread
        rc = GetRPCManager()->OnConnect(pHost);

        // Overwrite the password in memory before leaving the function.
        ClearMemory((wxChar*)strPassword.wx_str(), strPassword.size());
        strPassword.Empty();
    }
    else
    {
        // Notify state manager of a new host, which in turn should begin the connection
        // process in a different thread
        GetEventManager()->FireEvent(wxEVT_BSLHOST_CONNECTPENDING, pHost->GetHostHandle(), NULL);
        rc = BSLERR_SUCCESS;
    }

    return rc;
}

BSLERRCODE CClientState::CreateAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword, wxString& strName, wxString& strTeamName, wxString& strInviteCode)
{
    CRPCCreateAccount rpcCreateAccount;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcCreateAccount.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, strProjectURL, strIdentifier, strPassword, strName, strTeamName, strInviteCode);
}

BSLERRCODE CClientState::CreateAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator)
{
    CRPCCreateAccountPoll rpcCreateAccountPoll;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcCreateAccountPoll.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, uiReturnCode, oMessages, strAuthenticator);
}

BSLERRCODE CClientState::Disconnect(BSLHOST hHost)
{
    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    // Notify state manager of a host delete
    GetEventManager()->FireEvent(wxEVT_BSLHOST_DISCONNECTPENDING, pHost->GetHostHandle(), NULL);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::AddHost(CHost* pHost)
{
    CHost* pSrc = wxDynamicCast(pHost, CHost);
    if (!pSrc)
        return BSLERR_INVALID_PARAMETER;

    // Add host record
    m_pHostsDatabase->Add(pSrc);

    // Notify subscribers that a new host is being monitored
    GetEventManager()->FireEvent(wxEVT_BSLHOST_ADD, pSrc->GetHostHandle(), NULL);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::DeleteHost(CHost* pHost)
{
    CHost* pSrc = wxDynamicCast(pHost, CHost);
    if (!pSrc)
        return BSLERR_INVALID_PARAMETER;

    // Notify subscribers that a host is going to be deleted
    GetEventManager()->FireEvent(wxEVT_BSLHOST_DELETE, pSrc->GetHostHandle(), NULL);

    // Delete host record
    m_pHostsDatabase->Delete(pSrc);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateApps(BSLHOST hHost, std::vector<BSLAPP>& oApps)
{
    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    std::vector<CApp*> dbApps;
    pHost->EnumerateApps(dbApps);

    oApps.reserve(dbApps.size());

    for (std::vector<CApp*>::iterator iter = dbApps.begin(); iter != dbApps.end(); iter++)
    {
        oApps.push_back((*iter)->GetAppHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateAppVersions(BSLHOST hHost, std::vector<BSLAPPVERSION>& oAppVersions)
{
    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    std::vector<CAppVersion*> dbAppVersions;
    pHost->EnumerateAppVersions(dbAppVersions);

    oAppVersions.reserve(dbAppVersions.size());

    for (std::vector<CAppVersion*>::iterator iter = dbAppVersions.begin(); iter != dbAppVersions.end(); iter++)
    {
        oAppVersions.push_back((*iter)->GetAppVersionHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateHosts(std::vector<BSLHOST>& oHosts)
{
    std::vector<CHost*> dbHosts;
    m_pHostsDatabase->Enumerate(dbHosts);

    oHosts.reserve(dbHosts.size());

    for (std::vector<CHost*>::iterator iter = dbHosts.begin(); iter != dbHosts.end(); iter++)
    {
        oHosts.push_back((*iter)->GetHostHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateMessages(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLMESSAGE>& oMessages, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncMessages rpcSyncMessages;
    std::vector<CMessage*> dbMessages;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncMessages.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate, iSequenceNumber);
        }
        else
        {
            rc = rpcSyncMessages.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, iSequenceNumber);
        }
        if (rc) return rc;
    }

    pHost->EnumerateMessages(dbMessages);
    oMessages.reserve(dbMessages.size());

    for (std::vector<CMessage*>::iterator iter = dbMessages.begin(); iter != dbMessages.end(); iter++)
    {
        CMessage* pMessage = (*iter);
        if (pMessage->GetSequenceNumber() > iSequenceNumber)
        {
            oMessages.push_back(pMessage->GetMessageHandle());
        }
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateNotifications(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLNOTIFICATION>& oNotifications, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncNotifications rpcSyncNotifications;
    std::vector<CNotification*> dbNotifications;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncNotifications.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate, iSequenceNumber);
        }
        else
        {
            rc = rpcSyncNotifications.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, iSequenceNumber);
        }
        if (rc) return rc;
    }

    pHost->EnumerateNotifications(dbNotifications);
    oNotifications.reserve(dbNotifications.size());

    for (std::vector<CNotification*>::iterator iter = dbNotifications.begin(); iter != dbNotifications.end(); iter++)
    {
        CNotification* pNotification = (*iter);
        if (pNotification->GetSequenceNumber() > iSequenceNumber)
        {
            oNotifications.push_back(pNotification->GetNotificationHandle());
        }
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateProjectList(BSLHOST hHost, std::vector<BSLPROJECTLISTITEM>& oProjectListItems, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncProjectList rpcSyncProjectList;
    std::vector<CProjectListItem*> dbProjectListItems;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncProjectList.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate);
        }
        else
        {
            rc = rpcSyncProjectList.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
        }
        if (rc) return rc;
    }

    pHost->EnumerateProjectList(dbProjectListItems);
    oProjectListItems.reserve(dbProjectListItems.size());

    for (std::vector<CProjectListItem*>::iterator iter = dbProjectListItems.begin(); iter != dbProjectListItems.end(); iter++)
    {
        CProjectListItem* pProjectListItem = (*iter);
        oProjectListItems.push_back(pProjectListItem->GetProjectListItemHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateProjectStatistics(BSLHOST hHost, BSLPROJECT hProject, std::vector<BSLPROJECTSTATISTIC>& oProjectStatistics, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncProjectStatistics rpcSyncProjectStatistics;
    std::vector<CProjectStatistic*> dbProjectStatistics;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    CProject* pProject = wxDynamicCast(hProject, CProject);
    if (!bBackgroundOperation && !pProject)
        return BSLERR_PROJECT_NOT_FOUND;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncProjectStatistics.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate);
        }
        else
        {
            rc = rpcSyncProjectStatistics.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
        }
        if (rc) return rc;
    }

    // Background threads will pass a NULL handle for the project handle.
    // We still want to perform the RPC in that case.
    if (bBackgroundOperation && !pProject)
        return BSLERR_SUCCESS;

    pProject->EnumerateProjectStatistics(dbProjectStatistics);
    oProjectStatistics.reserve(dbProjectStatistics.size());

    for (std::vector<CProjectStatistic*>::iterator iter = dbProjectStatistics.begin(); iter != dbProjectStatistics.end(); iter++)
    {
        CProjectStatistic* pProjectStatistic = (*iter);
        oProjectStatistics.push_back(pProjectStatistic->GetProjectStatisticHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateProjects(BSLHOST hHost, std::vector<BSLPROJECT>& oProjects, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncProjects rpcSyncProjects;
    std::vector<CProject*> dbProjects;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncProjects.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate);
        }
        else
        {
            rc = rpcSyncProjects.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
        }
        if (rc) return rc;
    }

    pHost->EnumerateProjects(dbProjects);
    oProjects.reserve(dbProjects.size());

    for (std::vector<CProject*>::iterator iter = dbProjects.begin(); iter != dbProjects.end(); iter++)
    {
        CProject* pProject = (*iter);
        oProjects.push_back(pProject->GetProjectHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateTasks(BSLHOST hHost, std::vector<BSLTASK>& oTasks)
{
    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    std::vector<CTask*> dbTasks;
    pHost->EnumerateTasks(dbTasks);

    oTasks.reserve(dbTasks.size());

    for (std::vector<CTask*>::iterator iter = dbTasks.begin(); iter != dbTasks.end(); iter++)
    {
        oTasks.push_back((*iter)->GetTaskHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateTaskInstances(BSLHOST hHost, std::vector<BSLTASKINSTANCE>& oTaskInstances, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncTaskInstances rpcSyncTaskInstances;
    std::vector<CTaskInstance*> dbTaskInstances;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncTaskInstances.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate);
        }
        else
        {
            rc = rpcSyncTaskInstances.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
        }
        if (rc) return rc;
    }

    pHost->EnumerateTaskInstances(dbTaskInstances);
    oTaskInstances.reserve(dbTaskInstances.size());

    for (std::vector<CTaskInstance*>::iterator iter = dbTaskInstances.begin(); iter != dbTaskInstances.end(); iter++)
    {
        CTaskInstance* pTaskInstance = (*iter);
        oTaskInstances.push_back(pTaskInstance->GetTaskInstanceHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::EnumerateTransfers(BSLHOST hHost, std::vector<BSLTRANSFER>& oTransfers, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncTransfers rpcSyncTransfers;
    std::vector<CTransfer*> dbTransfers;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncTransfers.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate);
        }
        else
        {
            rc = rpcSyncTransfers.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
        }
        if (rc) return rc;
    }

    pHost->EnumerateTransfers(dbTransfers);
    oTransfers.reserve(dbTransfers.size());

    for (std::vector<CTransfer*>::iterator iter = dbTransfers.begin(); iter != dbTransfers.end(); iter++)
    {
        CTransfer* pTransfer = (*iter);
        oTransfers.push_back(pTransfer->GetTransferHandle());
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::FireEvent(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    // Notify state manager of a host delete
    GetEventManager()->FireEvent(etEventType, hHost, hHandle);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetApp(BSLAPP hApp, CBSLApp* pApp)
{
    CApp* pSrc = wxDynamicCast(hApp, CApp);
    if (!pSrc)
        return BSLERR_APP_NOT_FOUND;

    CBSLApp* pDest = wxDynamicCast(pApp, CBSLApp);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetAppEventData(BSLAPP hApp, wxUIntPtr* ppData)
{
    CApp* pSrc = wxDynamicCast(hApp, CApp);
    if (!pSrc)
        return BSLERR_APP_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetAppVersion(BSLAPPVERSION hAppVersion, CBSLAppVersion* pAppVersion)
{
    CAppVersion* pSrc = wxDynamicCast(hAppVersion, CAppVersion);
    if (!pSrc)
        return BSLERR_APPVERSION_NOT_FOUND;

    CBSLAppVersion* pDest = wxDynamicCast(pAppVersion, CBSLAppVersion);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr* ppData)
{
    CAppVersion* pSrc = wxDynamicCast(hAppVersion, CAppVersion);
    if (!pSrc)
        return BSLERR_APPVERSION_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetBOINCDataDirectory(wxString& strData)
{
    BSLERRCODE rc = BSLERR_FAILURE;

#ifdef __WXMSW__
    LONG lReturnValue;
    HKEY hkSetupHive;
    LPTSTR lpszRegistryValue = NULL;
    DWORD dwSize = 0;

    lReturnValue = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        _T("SOFTWARE\\Space Sciences Laboratory, U.C. Berkeley\\BOINC Setup"), 0, KEY_READ, &hkSetupHive);
    if (lReturnValue == ERROR_SUCCESS)
    {
        // How large does our buffer need to be?
        lReturnValue = RegQueryValueEx(hkSetupHive, _T("DATADIR"), NULL, NULL, NULL, &dwSize);
        if (lReturnValue != ERROR_FILE_NOT_FOUND)
        {
            // Allocate the buffer space.
            lpszRegistryValue = (LPTSTR)malloc(dwSize);

            // Now get the data
            lReturnValue = RegQueryValueEx(hkSetupHive, _T("DATADIR"), NULL, NULL, (LPBYTE)lpszRegistryValue,
                &dwSize);

            // Store the root directory for later use.
            strData = lpszRegistryValue;
            rc = BSLERR_SUCCESS;
        }
    }

    // Cleanup
    if (hkSetupHive)
        RegCloseKey(hkSetupHive);
    if (lpszRegistryValue)
        free(lpszRegistryValue);
#endif
#ifdef __WXMAC__
    strData = wxT("/Library/Application Support/BOINC Data");
    rc = BSLERR_SUCCESS;
#endif

    return rc;
}

BSLERRCODE CClientState::GetBOINCInstallDirectory(wxString& strInstall)
{
    BSLERRCODE rc = BSLERR_FAILURE;

#ifdef __WXMSW__
    LONG lReturnValue;
    HKEY hkSetupHive;
    LPTSTR lpszRegistryValue = NULL;
    DWORD dwSize = 0;

    lReturnValue = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        _T("SOFTWARE\\Space Sciences Laboratory, U.C. Berkeley\\BOINC Setup"), 0, KEY_READ, &hkSetupHive);
    if (lReturnValue == ERROR_SUCCESS)
    {
        // How large does our buffer need to be?
        lReturnValue = RegQueryValueEx(hkSetupHive, _T("INSTALLDIR"), NULL, NULL, NULL, &dwSize);
        if (lReturnValue != ERROR_FILE_NOT_FOUND)
        {
            // Allocate the buffer space.
            lpszRegistryValue = (LPTSTR)malloc(dwSize);

            // Now get the data
            lReturnValue = RegQueryValueEx(hkSetupHive, _T("INSTALLDIR"), NULL, NULL, (LPBYTE)lpszRegistryValue,
                &dwSize);

            // Store the root directory for later use.
            strInstall = lpszRegistryValue;
            rc = BSLERR_SUCCESS;
        }
    }

    // Cleanup
    if (hkSetupHive)
        RegCloseKey(hkSetupHive);
    if (lpszRegistryValue)
        free(lpszRegistryValue);
#endif
#ifdef __WXMAC__
    strInstall = wxT("/Applications/BOINCManager.app/Contents/Resources");
    rc = BSLERR_SUCCESS;
#endif

    return rc;
}

BSLERRCODE CClientState::GetHost(BSLHOST hHost, CBSLHost* pHost, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncHost rpcSyncHost;

    CHost* pSrc = wxDynamicCast(hHost, CHost);
    if (!pSrc)
        return BSLERR_HOST_NOT_FOUND;

    CBSLHost* pDest = wxDynamicCast(pHost, CBSLHost);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncHost.Execute(pSrc, CRPCConnection::ConnectionTypeStatusUpdate);
        }
        else
        {
            rc = rpcSyncHost.Execute(pSrc, CRPCConnection::ConnectionTypeOnDemand);
        }
        if (rc) return rc;
    }

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetHostEventData(BSLHOST hHost, wxUIntPtr* ppData)
{
    CHost* pSrc = wxDynamicCast(hHost, CHost);
    if (!pSrc)
        return BSLERR_HOST_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetHostStatus(BSLHOST hHost, CBSLHostStatus* pHostStatus, bool bUpdateCache, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncHostStatus rpcSyncHostStatus;

    CHost* pSrc = wxDynamicCast(hHost, CHost);
    if (!pSrc)
        return BSLERR_HOST_NOT_FOUND;

    CBSLHostStatus* pDest = wxDynamicCast(pHostStatus, CBSLHostStatus);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    if (bUpdateCache)
    {
        if (bBackgroundOperation)
        {
            rc = rpcSyncHostStatus.Execute(pSrc, CRPCConnection::ConnectionTypeStatusUpdate);
        }
        else
        {
            rc = rpcSyncHostStatus.Execute(pSrc, CRPCConnection::ConnectionTypeOnDemand);
        }
        if (rc) return rc;
    }

    CObjectLocker olLock(pSrc);
    *pDest = pSrc->GetHostStatus();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetHostStatusEventData(BSLHOST hHost, wxUIntPtr* ppData)
{
    CHost* pSrc = wxDynamicCast(hHost, CHost);
    if (!pSrc)
        return BSLERR_HOST_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetHostStatus().GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetLocalHostName(wxString& strName)
{
    strName = m_strLocalHostName;
    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetLocalHostPassword(wxString& strPassword)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    wxString strPasswordFile;

    if (BSLERR_SUCCESS == GetBOINCDataDirectory(strPasswordFile))
    {
        strPasswordFile += wxT("/gui_rpc_auth.cfg");
    }
    else
    {
        strPasswordFile = wxT("gui_rpc_auth.cfg");
    }

    if (wxFile::Exists(strPasswordFile))
    {
        wxFFile file(strPasswordFile, wxT("r"));
        if (file.IsOpened())
        {
            file.ReadAll(&strPassword, wxConvUTF8);

            // Delete any special characters
            strPassword.Replace(wxT("\r"), wxT(""));
            strPassword.Replace(wxT("\n"), wxT(""));

            rc = BSLERR_SUCCESS;
        }
    }

    return rc;
}

BSLERRCODE CClientState::GetLocalHostPort(long& lPort)
{
    lPort = 31416;
    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetMessage(BSLMESSAGE hMessage, CBSLMessage* pMessage)
{
    CMessage* pSrc = wxDynamicCast(hMessage, CMessage);
    if (!pSrc)
        return BSLERR_MESSAGE_NOT_FOUND;

    CBSLMessage* pDest = wxDynamicCast(pMessage, CBSLMessage);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr* ppData)
{
    CMessage* pSrc = wxDynamicCast(hMessage, CMessage);
    if (!pSrc)
        return BSLERR_MESSAGE_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetNotification(BSLNOTIFICATION hNotification, CBSLNotification* pNotification)
{
    CNotification* pSrc = wxDynamicCast(hNotification, CNotification);
    if (!pSrc)
        return BSLERR_NOTIFICATION_NOT_FOUND;

    CBSLNotification* pDest = wxDynamicCast(pNotification, CBSLNotification);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr* ppData)
{
    CNotification* pSrc = wxDynamicCast(hNotification, CNotification);
    if (!pSrc)
        return BSLERR_NOTIFICATION_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetProject(BSLPROJECT hProject, CBSLProject* pProject)
{
    CProject* pSrc = wxDynamicCast(hProject, CProject);
    if (!pSrc)
        return BSLERR_PROJECT_NOT_FOUND;

    CBSLProject* pDest = wxDynamicCast(pProject, CBSLProject);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetProjectEventData(BSLPROJECT hProject, wxUIntPtr* ppData)
{
    CProject* pSrc = wxDynamicCast(hProject, CProject);
    if (!pSrc)
        return BSLERR_PROJECT_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetProjectListItem(BSLPROJECTLISTITEM hProjectListItem, CBSLProjectListItem* pProjectListItem)
{
    CProjectListItem* pSrc = wxDynamicCast(hProjectListItem, CProjectListItem);
    if (!pSrc)
        return BSLERR_PROJECTLISTITEM_NOT_FOUND;

    CBSLProjectListItem* pDest = wxDynamicCast(pProjectListItem, CBSLProjectListItem);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr* ppData)
{
    CProjectListItem* pSrc = wxDynamicCast(hProjectListItem, CProjectListItem);
    if (!pSrc)
        return BSLERR_PROJECTLISTITEM_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetProjectStatistic(BSLPROJECTSTATISTIC hProjectStatistic, CBSLProjectStatistic* pProjectStatistic)
{
    CProjectStatistic* pSrc = wxDynamicCast(hProjectStatistic, CProjectStatistic);
    if (!pSrc)
        return BSLERR_PROJECTSTATISTIC_NOT_FOUND;

    CBSLProjectStatistic* pDest = wxDynamicCast(pProjectStatistic, CBSLProjectStatistic);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr* ppData)
{
    CProjectStatistic* pSrc = wxDynamicCast(hProjectStatistic, CProjectStatistic);
    if (!pSrc)
        return BSLERR_PROJECTSTATISTIC_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetTask(BSLTASK hTask, CBSLTask* pTask)
{
    CTask* pSrc = wxDynamicCast(hTask, CTask);
    if (!pSrc)
        return BSLERR_TASK_NOT_FOUND;

    CBSLTask* pDest = wxDynamicCast(pTask, CBSLTask);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetTaskEventData(BSLTASK hTask, wxUIntPtr* ppData)
{
    CTask* pSrc = wxDynamicCast(hTask, CTask);
    if (!pSrc)
        return BSLERR_TASK_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetTaskInstance(BSLTASKINSTANCE hTaskInstance, CBSLTaskInstance* pTaskInstance)
{
    CTaskInstance* pSrc = wxDynamicCast(hTaskInstance, CTaskInstance);
    if (!pSrc)
        return BSLERR_TASKINSTANCE_NOT_FOUND;

    CBSLTaskInstance* pDest = wxDynamicCast(pTaskInstance, CBSLTaskInstance);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr* ppData)
{
    CTaskInstance* pSrc = wxDynamicCast(hTaskInstance, CTaskInstance);
    if (!pSrc)
        return BSLERR_TASKINSTANCE_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetTransfer(BSLTRANSFER hTransfer, CBSLTransfer* pTransfer)
{
    CTransfer* pSrc = wxDynamicCast(hTransfer, CTransfer);
    if (!pSrc)
        return BSLERR_TRANSFER_NOT_FOUND;

    CBSLTransfer* pDest = wxDynamicCast(pTransfer, CBSLTransfer);
    if (!pDest)
        return BSLERR_INVALID_PARAMETER;

    CObjectLocker olLock(pSrc);
    *pDest = *pSrc;

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::GetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr* ppData)
{
    CTransfer* pSrc = wxDynamicCast(hTransfer, CTransfer);
    if (!pSrc)
        return BSLERR_TRANSFER_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    *ppData = pSrc->GetData();

    return BSLERR_SUCCESS;
}

bool CClientState::IsShutdownInitiated()
{
    return m_bShutdownInitiated;
}

BSLERRCODE CClientState::LookupAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword)
{
    CRPCLookupAccount rpcLookupAccount;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcLookupAccount.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, strProjectURL, strIdentifier, strPassword);
}

BSLERRCODE CClientState::LookupAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator)
{
    CRPCLookupAccountPoll rpcLookupAccountPoll;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcLookupAccountPoll.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, uiReturnCode, oMessages, strAuthenticator);
}

bool CClientState::IsLocalHostName(const wxString& strHost)
{
    bool rc = false;
    wxString strNormalizedHostName = strHost.Lower();

    if (wxT("localhost") == strNormalizedHostName)
    {
        rc = true;
    }
    else if (wxT("localhost.local") == strNormalizedHostName)
    {
        rc = true;
    }
    else if (wxT("localhost.localdomain") == strNormalizedHostName)
    {
        rc = true;
    }
    else if (wxT("127.0.0.1") == strNormalizedHostName)
    {
        rc = true;
    }
    else if (m_strLocalHostName == strNormalizedHostName)
    {
        rc = true;
    }
    else if (m_strLocalFullHostName == strNormalizedHostName)
    {
        rc = true;
    }

    return rc;
}

BSLERRCODE CClientState::NetworkAvailable(BSLHOST hHost)
{
    CRPCNetworkAvailable rpcNetworkAvailable;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcNetworkAvailable.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
}

BSLERRCODE CClientState::ProjectAttach(BSLHOST hHost, wxString& strProjectURL, wxString& strProjectName, wxString& strAuthenticator)
{
    CRPCProjectAttach rpcProjectAttach;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcProjectAttach.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, strProjectURL, strProjectName, strAuthenticator);
}

BSLERRCODE CClientState::ProjectAttachPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages)
{
    CRPCProjectAttachPoll rpcProjectAttachPoll;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcProjectAttachPoll.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, uiReturnCode, oMessages);
}

BSLERRCODE CClientState::ProjectDetach(BSLPROJECT hProject)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CHost* pHost;
    CProject* pProject;
    CBSLProject* pbslProject = new CBSLProject();
    CRPCProjectDetach rpcProjectDetach;

    pProject = wxDynamicCast(hProject, CProject);
    if (!pProject)
        rc = BSLERR_PROJECT_NOT_FOUND;

    pHost = wxDynamicCast(pProject->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(hProject, pbslProject);
        if (!rc)
        {
            rc = rpcProjectDetach.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
        }
    }

    delete pbslProject;

    return rc;
}

BSLERRCODE CClientState::ProjectReset(BSLPROJECT hProject)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CHost* pHost;
    CProject* pProject;
    CBSLProject* pbslProject = new CBSLProject();
    CRPCProjectReset rpcProjectReset;

    pProject = wxDynamicCast(hProject, CProject);
    if (!pProject)
        rc = BSLERR_PROJECT_NOT_FOUND;

    pHost = wxDynamicCast(pProject->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(hProject, pbslProject);
        if (!rc)
        {
            rc = rpcProjectReset.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
        }
    }

    delete pbslProject;

    return rc;
}

BSLERRCODE CClientState::ProjectUpdate(BSLPROJECT hProject)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CHost* pHost;
    CProject* pProject;
    CBSLProject* pbslProject = new CBSLProject();
    CRPCProjectUpdate rpcProjectUpdate;

    pProject = wxDynamicCast(hProject, CProject);
    if (!pProject)
        rc = BSLERR_PROJECT_NOT_FOUND;

    pHost = wxDynamicCast(pProject->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(hProject, pbslProject);
        if (!rc)
        {
            rc = rpcProjectUpdate.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
        }
    }

    delete pbslProject;

    return rc;
}

BSLERRCODE CClientState::ProjectSetProperty(BSLPROJECT hProject, CBSLClient::PROJECTPROPERTY property, wxUint32 uiValue)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CHost* pHost;
    CProject* pProject;
    CBSLProject* pbslProject = new CBSLProject();

    pProject = wxDynamicCast(hProject, CProject);
    if (!pProject)
        rc = BSLERR_PROJECT_NOT_FOUND;

    pHost = wxDynamicCast(pProject->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(pProject->GetProjectHandle(), pbslProject);
        if (!rc)
        {
            switch(property)
            {
                case CBSLClient::ProjectPropertySuspend:
                    if (uiValue)
                    {
                        CRPCProjectSuspend rpcProjectSuspend;
                        rc = rpcProjectSuspend.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
                    }
                    else
                    {
                        CRPCProjectResume rpcProjectResume;
                        rc = rpcProjectResume.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
                    }
                    break;
                case CBSLClient::ProjectPropertyTaskAccumulation:
                    if (uiValue)
                    {
                        CRPCProjectAllowMoreWork rpcProjectAllowMoreWork;
                        rc = rpcProjectAllowMoreWork.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
                    }
                    else
                    {
                        CRPCProjectNoMoreWork rpcProjectNoMoreWork;
                        rc = rpcProjectNoMoreWork.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
                    }
                    break;
                case CBSLClient::ProjectPropertyDetachWhenDone:
                    if (uiValue)
                    {
                        CRPCProjectDetachWhenDone rpcProjectDetachWhenDone;
                        rc = rpcProjectDetachWhenDone.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
                    }
                    else
                    {
                        CRPCProjectDontDetachWhenDone rpcProjectDontDetachWhenDone;
                        rc = rpcProjectDontDetachWhenDone.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject);
                    }
                    break;
                case CBSLClient::ProjectPropertyUnknown:
                default:
                    rc = BSLERR_FAILURE;
                    wxASSERT(false);
                    break;
            }
        }
    }

    delete pbslProject;

    return rc;
}

BSLERRCODE CClientState::RunBenchmarks(BSLHOST hHost)
{
    CRPCRunBenchmarks rpcRunBenchmarks;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcRunBenchmarks.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
}

BSLERRCODE CClientState::SetAppEventData(BSLAPP hApp, wxUIntPtr pData)
{
    CApp* pSrc = wxDynamicCast(hApp, CApp);
    if (!pSrc)
        return BSLERR_APP_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr pData)
{
    CAppVersion* pSrc = wxDynamicCast(hAppVersion, CAppVersion);
    if (!pSrc)
        return BSLERR_APPVERSION_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetAutoSyncProperty(BSLHOST hHost, CBSLClient::AUTOSYNCPROPERTY property, wxUint32 uiValue)
{
    CSyncProfile* pSyncProfile = NULL;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    // Find/Create the sync property record.
    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindSyncProfile(property, &pSyncProfile))
    {
        pSyncProfile = new CSyncProfile(property);
        pHost->AddSyncProfile(pSyncProfile);
    }
    wxASSERT(pSyncProfile);

    pSyncProfile->SetValue(uiValue);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetHostEventData(BSLHOST hHost, wxUIntPtr pData)
{
    CHost* pSrc = wxDynamicCast(hHost, CHost);
    if (!pSrc)
        return BSLERR_HOST_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetHostStatusEventData(BSLHOST hHost, wxUIntPtr pData)
{
    CHost* pSrc = wxDynamicCast(hHost, CHost);
    if (!pSrc)
        return BSLERR_HOSTSTATUS_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->GetHostStatus().SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr pData)
{
    CMessage* pSrc = wxDynamicCast(hMessage, CMessage);
    if (!pSrc)
        return BSLERR_MESSAGE_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetModeCPU(BSLHOST hHost, CBSLClient::SETMODE mode, wxUint32 uiDuration)
{
    CRPCSetModeCPU rpcSetModeCPU;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcSetModeCPU.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, mode, uiDuration);
}

BSLERRCODE CClientState::SetModeGPU(BSLHOST hHost, CBSLClient::SETMODE mode, wxUint32 uiDuration)
{
    CRPCSetModeGPU rpcSetModeGPU;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcSetModeGPU.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, mode, uiDuration);
}

BSLERRCODE CClientState::SetModeNetwork(BSLHOST hHost, CBSLClient::SETMODE mode, wxUint32 uiDuration)
{
    CRPCSetModeNetwork rpcSetModeNetwork;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcSetModeNetwork.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, mode, uiDuration);
}

BSLERRCODE CClientState::SetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr pData)
{
    CNotification* pSrc = wxDynamicCast(hNotification, CNotification);
    if (!pSrc)
        return BSLERR_NOTIFICATION_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetProjectEventData(BSLPROJECT hProject, wxUIntPtr pData)
{
    CProject* pSrc = wxDynamicCast(hProject, CProject);
    if (!pSrc)
        return BSLERR_PROJECT_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr pData)
{
    CProjectListItem* pSrc = wxDynamicCast(hProjectListItem, CProjectListItem);
    if (!pSrc)
        return BSLERR_PROJECTLISTITEM_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr pData)
{
    CProjectStatistic* pSrc = wxDynamicCast(hProjectStatistic, CProjectStatistic);
    if (!pSrc)
        return BSLERR_PROJECTSTATISTIC_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetTaskEventData(BSLTASK hTask, wxUIntPtr pData)
{
    CTask* pSrc = wxDynamicCast(hTask, CTask);
    if (!pSrc)
        return BSLERR_TASK_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr pData)
{
    CTaskInstance* pSrc = wxDynamicCast(hTaskInstance, CTaskInstance);
    if (!pSrc)
        return BSLERR_TASKINSTANCE_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr pData)
{
    CTransfer* pSrc = wxDynamicCast(hTransfer, CTransfer);
    if (!pSrc)
        return BSLERR_TRANSFER_NOT_FOUND;

    CObjectLocker olLock(pSrc);
    pSrc->SetData(pData);

    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::SetShutdownInitiated(bool bShutdownInitiated)
{
    m_bShutdownInitiated = bShutdownInitiated;
    return BSLERR_SUCCESS;
}

BSLERRCODE CClientState::Shutdown(BSLHOST hHost)
{
    CRPCShutdown rpcShutdown;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    return rpcShutdown.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
}

BSLERRCODE CClientState::TaskInstanceAbort(BSLTASKINSTANCE hTaskInstance)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    BSLERRCODE rc2 = BSLERR_SUCCESS;
    CHost* pHost;
    CTaskInstance* pTaskInstance;
    CBSLProject* pbslProject = new CBSLProject();
    CBSLTaskInstance* pbslTaskInstance = new CBSLTaskInstance();
    CRPCTaskInstanceAbort rpcTaskInstanceAbort;

    pTaskInstance = wxDynamicCast(hTaskInstance, CTaskInstance);
    if (!pTaskInstance)
        rc = BSLERR_TASKINSTANCE_NOT_FOUND;

    pHost = wxDynamicCast(pTaskInstance->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(pTaskInstance->GetProjectHandle(), pbslProject);
        rc2 = GetTaskInstance(pTaskInstance->GetTaskInstanceHandle(), pbslTaskInstance);
        if (!rc && !rc2)
        {
            rc = rpcTaskInstanceAbort.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject, pbslTaskInstance);
        }
    }

    delete pbslProject;
    delete pbslTaskInstance;

    return rc;
}

BSLERRCODE CClientState::TaskInstanceSetProperty(BSLTASKINSTANCE hTaskInstance, CBSLClient::TASKINSTANCEPROPERTY property, wxUint32 uiValue)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    BSLERRCODE rc2 = BSLERR_SUCCESS;
    CHost* pHost;
    CTaskInstance* pTaskInstance;
    CBSLProject* pbslProject = new CBSLProject();
    CBSLTaskInstance* pbslTaskInstance = new CBSLTaskInstance();

    pTaskInstance = wxDynamicCast(hTaskInstance, CTaskInstance);
    if (!pTaskInstance)
        rc = BSLERR_TASKINSTANCE_NOT_FOUND;

    pHost = wxDynamicCast(pTaskInstance->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(pTaskInstance->GetProjectHandle(), pbslProject);
        rc2 = GetTaskInstance(pTaskInstance->GetTaskInstanceHandle(), pbslTaskInstance);
        if (!rc && !rc2)
        {
            switch(property)
            {
                case CBSLClient::TaskInstancePropertySuspend:
                    if (uiValue)
                    {
                        CRPCTaskInstanceSuspend rpcTaskInstanceSuspend;
                        rc = rpcTaskInstanceSuspend.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject, pbslTaskInstance);
                    }
                    else
                    {
                        CRPCTaskInstanceResume rpcTaskInstanceResume;
                        rc = rpcTaskInstanceResume.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject, pbslTaskInstance);
                    }
                    break;
                case CBSLClient::TaskInstancePropertyUnknown:
                default:
                    rc = BSLERR_FAILURE;
                    wxASSERT(false);
                    break;
            }
        }
    }

    delete pbslProject;
    delete pbslTaskInstance;

    return rc;
}

BSLERRCODE CClientState::TransferAbort(BSLTRANSFER hTransfer)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    BSLERRCODE rc2 = BSLERR_SUCCESS;
    CHost* pHost;
    CTransfer* pTransfer;
    CBSLProject* pbslProject = new CBSLProject();
    CBSLTransfer* pbslTransfer = new CBSLTransfer();
    CRPCTransferAbort rpcTransferAbort;

    pTransfer = wxDynamicCast(hTransfer, CTransfer);
    if (!pTransfer)
        rc = BSLERR_TRANSFER_NOT_FOUND;

    pHost = wxDynamicCast(pTransfer->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(pTransfer->GetProjectHandle(), pbslProject);
        rc2 = GetTransfer(pTransfer->GetTransferHandle(), pbslTransfer);
        if (!rc && !rc2)
        {
            rc = rpcTransferAbort.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject, pbslTransfer);
        }
    }

    delete pbslProject;
    delete pbslTransfer;

    return rc;
}

BSLERRCODE CClientState::TransferRetry(BSLTRANSFER hTransfer)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    BSLERRCODE rc2 = BSLERR_SUCCESS;
    CHost* pHost;
    CTransfer* pTransfer;
    CBSLProject* pbslProject = new CBSLProject();
    CBSLTransfer* pbslTransfer = new CBSLTransfer();
    CRPCTransferRetry rpcTransferRetry;

    pTransfer = wxDynamicCast(hTransfer, CTransfer);
    if (!pTransfer)
        rc = BSLERR_TRANSFER_NOT_FOUND;

    pHost = wxDynamicCast(pTransfer->GetHostHandle(), CHost);
    if (!pHost)
        rc = BSLERR_HOST_NOT_FOUND;

    if (!rc)
    {
        rc = GetProject(pTransfer->GetProjectHandle(), pbslProject);
        rc2 = GetTransfer(pTransfer->GetTransferHandle(), pbslTransfer);
        if (!rc && !rc2)
        {
            rc = rpcTransferRetry.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, pbslProject, pbslTransfer);
        }
    }

    delete pbslProject;
    delete pbslTransfer;

    return rc;
}

BSLERRCODE CClientState::TransferSetProperty(BSLTRANSFER WXUNUSED(hTransfer), CBSLClient::TRANSFERPROPERTY WXUNUSED(property), wxUint32 WXUNUSED(uiValue))
{
    return BSLERR_FAILURE;
}

BSLERRCODE CClientState::UpdateHostState(BSLHOST hHost, bool bBackgroundOperation)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCSyncState rpcSyncState;

    CHost* pHost = wxDynamicCast(hHost, CHost);
    if (!pHost)
        return BSLERR_HOST_NOT_FOUND;

    if (bBackgroundOperation)
    {
        rc = rpcSyncState.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate);
    }
    else
    {
        rc = rpcSyncState.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);
    }

    return rc;
}

wxChar* CClientState::ClearMemory(wxChar* v, size_t n)
{
    volatile wxChar* p = v;
    while (n--)
    {
        *p++ = 0;
    }
    return v;
}
