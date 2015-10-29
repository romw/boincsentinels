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
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "EventManager.h"
#include "RPCProtocol.h"

IMPLEMENT_DYNAMIC_CLASS(CHost, CBSLHost);

CHost::CHost() :
CObject(),
CBSLHost()
{
    CObjectLocker olLock(this);

    m_bForceRefresh = false;

    m_strConnectionName = wxEmptyString;
    m_strConnectionPassword = wxEmptyString;
    m_lConnectionPort = -1;
    m_uiLastMessageSequenceNumber = 0;
    m_uiLastNotificationSequenceNumber = 0;

    m_HostStatus.SetHostHandle(this);
    m_HostStatus.SetHostStatusHandle(&m_HostStatus);

    m_pRPCOnDemand = new CRPCConnection( CRPCConnection::ConnectionTypeOnDemand );
    wxASSERT(m_pRPCOnDemand);

    m_pRPCStatusUpdate = new CRPCConnection( CRPCConnection::ConnectionTypeStatusUpdate );
    wxASSERT(m_pRPCStatusUpdate);

    m_pAppsDatabase = new CDatabaseIndexed<CAppIndex, CApp*, CBSLApp*>();
    wxASSERT(m_pAppsDatabase);

    m_pAppVersionsDatabase = new CDatabaseIndexed<CAppVersionIndex, CAppVersion*, CBSLAppVersion*>();
    wxASSERT(m_pAppVersionsDatabase);

    m_pMessagesDatabase = new CDatabaseIndexed<CMessageIndex, CMessage*, CBSLMessage*>();
    wxASSERT(m_pMessagesDatabase);

    m_pNotificationsDatabase = new CDatabaseIndexed<CNotificationIndex, CNotification*, CBSLNotification*>();
    wxASSERT(m_pNotificationsDatabase);

    m_pProjectsDatabase = new CDatabaseIndexed<CProjectIndex, CProject*, CBSLProject*>();
    wxASSERT(m_pProjectsDatabase);

    m_pProjectListDatabase = new CDatabaseIndexed<CProjectListItemIndex, CProjectListItem*, CBSLProjectListItem*>();
    wxASSERT(m_pProjectListDatabase);

    m_pTasksDatabase = new CDatabaseIndexed<CTaskIndex, CTask*, CBSLTask*>();
    wxASSERT(m_pTasksDatabase);

    m_pTaskInstancesDatabase = new CDatabaseIndexed<CTaskInstanceIndex, CTaskInstance*, CBSLTaskInstance*>();
    wxASSERT(m_pTaskInstancesDatabase);

    m_pTransfersDatabase = new CDatabaseIndexed<CTransferIndex, CTransfer*, CBSLTransfer*>();
    wxASSERT(m_pTransfersDatabase);

    m_pRPCProfilesDatabase = new CDatabase<CRPCProfile*>();
    wxASSERT(m_pRPCProfilesDatabase);

    m_pSyncProfilesDatabase = new CDatabase<CSyncProfile*>();
    wxASSERT(m_pSyncProfilesDatabase);
}

CHost::~CHost()
{
    CObjectLocker olLock(this);

    m_bForceRefresh = false;
    m_strConnectionName = wxEmptyString;
    m_strConnectionPassword = wxEmptyString;
    m_lConnectionPort = -1;
    m_uiLastMessageSequenceNumber = 0;
    m_uiLastNotificationSequenceNumber = 0;

    delete m_pSyncProfilesDatabase;
    m_pSyncProfilesDatabase = NULL;

    delete m_pRPCProfilesDatabase;
    m_pRPCProfilesDatabase = NULL;

    delete m_pTransfersDatabase;
    m_pTransfersDatabase = NULL;

    delete m_pTaskInstancesDatabase;
    m_pTaskInstancesDatabase = NULL;

    delete m_pTasksDatabase;
    m_pTasksDatabase = NULL;

    delete m_pProjectsDatabase;
    m_pProjectsDatabase = NULL;

    delete m_pProjectListDatabase;
    m_pProjectListDatabase = NULL;

    delete m_pNotificationsDatabase;
    m_pNotificationsDatabase = NULL;

    delete m_pMessagesDatabase;
    m_pMessagesDatabase = NULL;

    delete m_pAppVersionsDatabase;
    m_pAppVersionsDatabase = NULL;

    delete m_pAppsDatabase;
    m_pAppsDatabase = NULL;

    delete m_pRPCStatusUpdate;
    m_pRPCStatusUpdate = NULL;

    delete m_pRPCOnDemand;
    m_pRPCOnDemand = NULL;
}

CHost& CHost::operator= (const CBSLHost& bslHost)
{
    CObjectLocker olLock(this);

    CBSLHost::operator=(bslHost);
    SetHostHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLHOST_UPDATE, GetHostHandle(), NULL);

    return *this;
}

bool CHost::operator== (const CBSLHost& bslHost)
{
    CObjectLocker olLock(this);
    return CBSLHost::operator==(bslHost);
}

bool CHost::operator!= (const CBSLHost& bslHost)
{
    CObjectLocker olLock(this);
    return CBSLHost::operator!=(bslHost);
}

BSLERRCODE CHost::AddApp(CApp* pApp)
{
    return m_pAppsDatabase->Add(pApp);
}

BSLERRCODE CHost::AddAppVersion(CAppVersion* pAppVersion)
{
    return m_pAppVersionsDatabase->Add(pAppVersion);
}

BSLERRCODE CHost::AddMessage(CMessage* pMessage)
{
    return m_pMessagesDatabase->Add(pMessage);
}

BSLERRCODE CHost::AddNotification(CNotification* pNotification)
{
    return m_pNotificationsDatabase->Add(pNotification);
}

BSLERRCODE CHost::AddProject(CProject* pProject)
{
    return m_pProjectsDatabase->Add(pProject);
}

BSLERRCODE CHost::AddProjectListItem(CProjectListItem* pProjectListItem)
{
    return m_pProjectListDatabase->Add(pProjectListItem);
}

BSLERRCODE CHost::AddRPCProfile(CRPCProfile* pRPCProfile)
{
    return m_pRPCProfilesDatabase->Add(pRPCProfile);
}

BSLERRCODE CHost::AddSyncProfile(CSyncProfile* pSyncProfile)
{
    return m_pSyncProfilesDatabase->Add(pSyncProfile);
}

BSLERRCODE CHost::AddTask(CTask* pTask)
{
    return m_pTasksDatabase->Add(pTask);
}

BSLERRCODE CHost::AddTaskInstance(CTaskInstance* pTaskInstance)
{
    return m_pTaskInstancesDatabase->Add(pTaskInstance);
}

BSLERRCODE CHost::AddTransfer(CTransfer* pTransfer)
{
    return m_pTransfersDatabase->Add(pTransfer);
}

BSLERRCODE CHost::DeleteApp(CApp* pApp)
{
    return m_pAppsDatabase->Delete(pApp);
}

BSLERRCODE CHost::DeleteAppVersion(CAppVersion* pAppVersion)
{
    return m_pAppVersionsDatabase->Delete(pAppVersion);
}

BSLERRCODE CHost::DeleteMessage(CMessage* pMessage)
{
    return m_pMessagesDatabase->Delete(pMessage);
}

BSLERRCODE CHost::DeleteNotification(CNotification* pNotification)
{
    return m_pNotificationsDatabase->Delete(pNotification);
}

BSLERRCODE CHost::DeleteProject(CProject* pProject)
{
    return m_pProjectsDatabase->Delete(pProject);
}

BSLERRCODE CHost::DeleteProjectListItem(CProjectListItem* pProjectListItem)
{
    return m_pProjectListDatabase->Delete(pProjectListItem);
}

BSLERRCODE CHost::DeleteRPCProfile(CRPCProfile* pRPCProfile)
{
    return m_pRPCProfilesDatabase->Delete(pRPCProfile);
}

BSLERRCODE CHost::DeleteSyncProfile(CSyncProfile* pSyncProfile)
{
    return m_pSyncProfilesDatabase->Delete(pSyncProfile);
}

BSLERRCODE CHost::DeleteTask(CTask* pTask)
{
    return m_pTasksDatabase->Delete(pTask);
}

BSLERRCODE CHost::DeleteTaskInstance(CTaskInstance* pTaskInstance)
{
    return m_pTaskInstancesDatabase->Delete(pTaskInstance);
}

BSLERRCODE CHost::DeleteTransfer(CTransfer* pTransfer)
{
    return m_pTransfersDatabase->Delete(pTransfer);
}

void CHost::Dispose()
{
    CObjectLocker olLock(this);
    CObject::Dispose(this);
}

BSLERRCODE CHost::EnumerateApps(std::vector<CApp*>& oApps)
{
    return m_pAppsDatabase->Enumerate(oApps);
}

BSLERRCODE CHost::EnumerateAppVersions(std::vector<CAppVersion*>& oAppVersions)
{
    return m_pAppVersionsDatabase->Enumerate(oAppVersions);
}

BSLERRCODE CHost::EnumerateMessages(std::vector<CMessage*>& oMessages)
{
    return m_pMessagesDatabase->Enumerate(oMessages);
}

BSLERRCODE CHost::EnumerateNotifications(std::vector<CNotification*>& oNotifications)
{
    return m_pNotificationsDatabase->Enumerate(oNotifications);
}

BSLERRCODE CHost::EnumerateProjects(std::vector<CProject*>& oProjects)
{
    return m_pProjectsDatabase->Enumerate(oProjects);
}

BSLERRCODE CHost::EnumerateProjectList(std::vector<CProjectListItem*>& oProjectList)
{
    return m_pProjectListDatabase->Enumerate(oProjectList);
}

BSLERRCODE CHost::EnumerateRPCProfiles(std::vector<CRPCProfile*>& oRPCProfiles)
{
    return m_pRPCProfilesDatabase->Enumerate(oRPCProfiles);
}

BSLERRCODE CHost::EnumerateSyncProfiles(std::vector<CSyncProfile*>& oSyncProfiles)
{
    return m_pSyncProfilesDatabase->Enumerate(oSyncProfiles);
}

BSLERRCODE CHost::EnumerateTasks(std::vector<CTask*>& oTasks)
{
    return m_pTasksDatabase->Enumerate(oTasks);
}

BSLERRCODE CHost::EnumerateTaskInstances(std::vector<CTaskInstance*>& oTaskInstances)
{
    return m_pTaskInstancesDatabase->Enumerate(oTaskInstances);
}

BSLERRCODE CHost::EnumerateTransfers(std::vector<CTransfer*>& oTransfers)
{
    return m_pTransfersDatabase->Enumerate(oTransfers);
}

BSLERRCODE CHost::FindApp(
    wxUint32 uiProjectHash,
    wxUint32 uiNameHash,
    CApp** ppApp,
    CBSLApp* pBSLApp
)
{
    return m_pAppsDatabase->Find(CAppIndex(uiProjectHash, uiNameHash), ppApp, pBSLApp);
}

BSLERRCODE CHost::FindAppVersion(
    wxUint32 uiProjectHash,
    wxUint32 uiNameHash,
    wxUint32 uiVersion,
    wxUint32 uiPlanClassHash,
    CAppVersion** ppAppVersion,
    CBSLAppVersion* pBSLAppVersion
)
{
    return m_pAppVersionsDatabase->Find(CAppVersionIndex(uiProjectHash, uiNameHash, uiVersion, uiPlanClassHash), ppAppVersion, pBSLAppVersion);
}

BSLERRCODE CHost::FindMessage(
    wxInt32 iSeqNo,
    CMessage** ppMessage,
    CBSLMessage* pBSLMessage
)
{
    return m_pMessagesDatabase->Find(CMessageIndex(iSeqNo), ppMessage, pBSLMessage);
}

BSLERRCODE CHost::FindNotification(
    wxInt32 iSeqNo,
    CNotification** ppNotification,
    CBSLNotification* pBSLNotification
)
{
    return m_pNotificationsDatabase->Find(CNotificationIndex(iSeqNo), ppNotification, pBSLNotification);
}

BSLERRCODE CHost::FindProject(
    wxUint32 uiMasterURLHash,
    CProject** ppProject,
    CBSLProject* pBSLProject
)
{
    return m_pProjectsDatabase->Find(CProjectIndex(uiMasterURLHash), ppProject, pBSLProject);
}

BSLERRCODE CHost::FindProjectListItem(
    wxUint32 uiMasterURLHash,
    CProjectListItem** ppProjectListItem,
    CBSLProjectListItem* pBSLProjectListItem
)
{
    return m_pProjectListDatabase->Find(CProjectListItemIndex(uiMasterURLHash), ppProjectListItem, pBSLProjectListItem);
}

BSLERRCODE CHost::FindRPCProfile(
    const wxChar* pszProfile,
    CRPCProfile** ppRPCProfile
)
{
    BSLERRCODE rc = BSLERR_OBJECT_NOT_FOUND;
    std::vector<CRPCProfile*>::iterator i;
    CRPCProfile* pRPCProfile = NULL;

    *ppRPCProfile = NULL;

    m_pRPCProfilesDatabase->Lock();

    for (i = m_pRPCProfilesDatabase->m_Database.begin(); i != m_pRPCProfilesDatabase->m_Database.end(); ++i)
    {
        pRPCProfile = *i;

        //
        if (_tcscmp(pRPCProfile->GetRPCName().c_str(), pszProfile) != 0) continue;

        //
        *ppRPCProfile = pRPCProfile;
        rc = BSLERR_SUCCESS;

        break;
    }

    m_pRPCProfilesDatabase->Unlock();

    return rc;
}

BSLERRCODE CHost::FindSyncProfile(
    CBSLClient::AUTOSYNCPROPERTY uiSyncProperty,
    CSyncProfile** ppSyncProfile
)
{
    BSLERRCODE rc = BSLERR_OBJECT_NOT_FOUND;
    std::vector<CSyncProfile*>::iterator i;
    CSyncProfile* pSyncProfile = NULL;

    *ppSyncProfile = NULL;

    m_pSyncProfilesDatabase->Lock();

    for (i = m_pSyncProfilesDatabase->m_Database.begin(); i != m_pSyncProfilesDatabase->m_Database.end(); ++i)
    {
        pSyncProfile = *i;

        //
        if (pSyncProfile->GetID() != uiSyncProperty) continue;

        //
        *ppSyncProfile = pSyncProfile;
        rc = BSLERR_SUCCESS;

        break;
    }

    m_pSyncProfilesDatabase->Unlock();

    return rc;
}

BSLERRCODE CHost::FindTask(
    wxUint32 uiProjectHash,
    wxUint32 uiNameHash,
    CTask** ppTask,
    CBSLTask* pBSLTask
)
{
    return m_pTasksDatabase->Find(CTaskIndex(uiProjectHash, uiNameHash), ppTask, pBSLTask);
}

BSLERRCODE CHost::FindTaskInstance(
    wxUint32 uiProjectHash,
    wxUint32 uiNameHash,
    CTaskInstance** ppTaskInstance,
    CBSLTaskInstance* pBSLTaskInstance
)
{
    return m_pTaskInstancesDatabase->Find(CTaskInstanceIndex(uiProjectHash, uiNameHash), ppTaskInstance, pBSLTaskInstance);
}

BSLERRCODE CHost::FindTransfer(
    wxUint32 uiProjectHash,
    wxUint32 uiNameHash,
    CTransfer** ppTransfer,
    CBSLTransfer* pBSLTransfer
)
{
    return m_pTransfersDatabase->Find(CTransferIndex(uiProjectHash, uiNameHash), ppTransfer, pBSLTransfer);
}

void CHost::ForceRefresh(bool bValue)
{
    CObjectLocker olLock(this);
    m_bForceRefresh = bValue;
}

bool CHost::IsForceRefreshEnabled()
{
    CObjectLocker olLock(this);
    return m_bForceRefresh;
}

bool CHost::GetConnectionProperties(wxString& strName, wxString& strPassword, long& lPort)
{
    CObjectLocker olLock(this);

    strName = m_strConnectionName;
    strPassword = m_strConnectionPassword;
    lPort = m_lConnectionPort;

    return true;
}

bool CHost::SetConnectionProperties(wxString& strName, wxString& strPassword, long lPort)
{
    CObjectLocker olLock(this);

    m_strConnectionName = strName;
    m_strConnectionPassword = strPassword;
    m_lConnectionPort = lPort;

    // CBOINCHost
    SetName(strName);

    return true;
}

CHost::CONNECTIONSTATE CHost::GetConnectionState()
{
    CObjectLocker olLock(this);
    return m_iConnectionState;
}

void CHost::SetConnectionState(CHost::CONNECTIONSTATE iConnectionState)
{
    CEventManager* pEventManager = GetEventManager();
    CObjectLocker olLock(this);

    m_iConnectionState = iConnectionState;

    // Notify subscribers
    switch (iConnectionState)
    {
        case CHost::ConnectionStateConnecting:
            pEventManager->FireEvent(wxEVT_BSLHOST_CONNECTING, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateConnected:
            pEventManager->FireEvent(wxEVT_BSLHOST_CONNECTED, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateDisconnecting:
            pEventManager->FireEvent(wxEVT_BSLHOST_DISCONNECTING, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateDisconnected:
            pEventManager->FireEvent(wxEVT_BSLHOST_DISCONNECTED, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateReconnecting:
            pEventManager->FireEvent(wxEVT_BSLHOST_RECONNECTING, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateConnectFailure:
            pEventManager->FireEvent(wxEVT_BSLHOST_CONNECTFAILURE, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateAuthenticationFailure:
            pEventManager->FireEvent(wxEVT_BSLHOST_AUTHENTICATIONFAILURE, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateVersionIncompatibleFailure:
            pEventManager->FireEvent(wxEVT_BSLHOST_VERSIONINCOMPATIBLEFAILURE, GetHostHandle(), NULL);
            break;
        case CHost::ConnectionStateUnknown:
            wxASSERT(false);
            break;
    }
}

CBSLHostStatus& CHost::GetHostStatus()
{
    return m_HostStatus;
}

void CHost::SetHostStatus(CBSLHostStatus& bslHostStatus)
{
    bslHostStatus.SetHostHandle(this);
    bslHostStatus.SetHostStatusHandle(&m_HostStatus);
    bslHostStatus.SetData(m_HostStatus.GetData());

    m_HostStatus.Update(bslHostStatus);
}

wxUint32 CHost::GetLastMessageSequenceNumber()
{
    CObjectLocker olLock(this);

    return m_uiLastMessageSequenceNumber;
}

void CHost::SetLastMessageSequenceNumber(wxUint32 uiSequenceNumber)
{
    CObjectLocker olLock(this);

    m_uiLastMessageSequenceNumber = uiSequenceNumber;
}

wxUint32 CHost::GetLastNotificationSequenceNumber()
{
    CObjectLocker olLock(this);

    return m_uiLastNotificationSequenceNumber;
}

void CHost::SetLastNotificationSequenceNumber(wxUint32 uiSequenceNumber)
{
    CObjectLocker olLock(this);

    m_uiLastNotificationSequenceNumber = uiSequenceNumber;
}

bool CHost::SetClientVersion(wxUint32& uiMajor, wxUint32& uiMinor, wxUint32& uiRelease)
{
    CObjectLocker olLock(this);

    // CBOINCHost
    SetClientVersionMajor(uiMajor);
    SetClientVersionMinor(uiMinor);
    SetClientVersionRelease(uiRelease);

    return true;
}

bool CHost::SetPlatforms(wxString strPrimaryPlatform, std::vector<wxString>& oSupportedPlatforms)
{
    CObjectLocker olLock(this);

    // CBOINCHost
    SetPrimaryPlatform(strPrimaryPlatform);
    SetSupportedPlatforms(oSupportedPlatforms);

    return true;
}

BSLERRCODE CHost::Update(CBSLHost& bslHost)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLHost::operator!=(bslHost))
    {
        CBSLHost::operator=(bslHost);
        GetEventManager()->FireEvent(wxEVT_BSLHOST_UPDATE, GetHostHandle(), NULL);

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}
