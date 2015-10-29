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
#include "StateManager.h"
#include "RPCManager.h"

CEventManager* g_pbslEventManager;
CStateManager* g_pbslStateManager;
CRPCManager* g_pbslRPCManager;
CClientState* g_pbslState;
wxCriticalSection g_csInitialization;
wxUint32 g_uiInitializationReferenceCount = 0;

IMPLEMENT_DYNAMIC_CLASS(CBSLClient, wxObject);

CBSLClient::CBSLClient()
{
    wxCriticalSectionLocker cslInitializationLock(g_csInitialization);

    // Increment the reference counter
    g_uiInitializationReferenceCount++;

    if (1 == g_uiInitializationReferenceCount)
    {
        // Initialize state information
        g_pbslState = new CClientState();
        wxASSERT(g_pbslState);

        // Initialize non-thread based services
        g_pbslEventManager = new CEventManager();
        wxASSERT(g_pbslEventManager);

        g_pbslRPCManager = new CRPCManager();
        wxASSERT(g_pbslRPCManager);

        // Initialize thread based services
        g_pbslStateManager = new CStateManager();
        wxASSERT(g_pbslStateManager);
    }
}

CBSLClient::~CBSLClient()
{
    wxCriticalSectionLocker cslInitializationLock(g_csInitialization);

    // Decrement the reference counter
    g_uiInitializationReferenceCount--;

    if (0 == g_uiInitializationReferenceCount)
    {
        // Begin the shutdown sequence
        g_pbslState->SetShutdownInitiated(true);

        // Shutdown any services that manage one or more threads
        delete g_pbslStateManager;
        g_pbslStateManager = NULL;

        // Shutdown any remaining services
        delete g_pbslRPCManager;
        g_pbslRPCManager = NULL;

        delete g_pbslEventManager;
        g_pbslEventManager = NULL;

        // Cleanup state information
        delete g_pbslState;
        g_pbslState = NULL;

    }
}

bool CBSLClient::OnInit()
{
    return GetState()->OnInit();
}

bool CBSLClient::OnExit()
{
    return GetState()->OnExit();
}

BSLERRCODE CBSLClient::Connect(wxString strName, wxString strPassword, long lPort, bool bWait, BSLHOST* phHost)
{
    return GetState()->Connect(strName, strPassword, lPort, bWait, phHost);
}

BSLERRCODE CBSLClient::CreateAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword, wxString& strName, wxString& strTeamName, wxString& strInviteCode)
{
    return GetState()->CreateAccount(hHost, strProjectURL, strIdentifier, strPassword, strName, strTeamName, strInviteCode);
}

BSLERRCODE CBSLClient::CreateAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator)
{
    return GetState()->CreateAccountPoll(hHost, uiReturnCode, oMessages, strAuthenticator);
}

BSLERRCODE CBSLClient::Disconnect(BSLHOST hHost)
{
    return GetState()->Disconnect(hHost);
}

BSLERRCODE CBSLClient::EnumerateApps(BSLHOST hHost, std::vector<BSLAPP>& oApps)
{
    return GetState()->EnumerateApps(hHost, oApps);
}

BSLERRCODE CBSLClient::EnumerateAppVersions(BSLHOST hHost, std::vector<BSLAPPVERSION>& oAppVersions)
{
    return GetState()->EnumerateAppVersions(hHost, oAppVersions);
}

BSLERRCODE CBSLClient::EnumerateHosts(std::vector<BSLHOST>& oHosts)
{
    return GetState()->EnumerateHosts(oHosts);
}

BSLERRCODE CBSLClient::EnumerateMessages(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLMESSAGE>& oMessages, bool bUpdateCache)
{
    return GetState()->EnumerateMessages(hHost, iSequenceNumber, oMessages, bUpdateCache, false);
}

BSLERRCODE CBSLClient::EnumerateNotifications(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLNOTIFICATION>& oNotifications, bool bUpdateCache)
{
    return GetState()->EnumerateNotifications(hHost, iSequenceNumber, oNotifications, bUpdateCache, false);
}

BSLERRCODE CBSLClient::EnumerateProjectList(BSLHOST hHost, std::vector<BSLPROJECTLISTITEM>& oProjectListItems, bool bUpdateCache)
{
    return GetState()->EnumerateProjectList(hHost, oProjectListItems, bUpdateCache, false);
}

BSLERRCODE CBSLClient::EnumerateProjectStatistics(BSLHOST hHost, BSLPROJECT hProject, std::vector<BSLPROJECTSTATISTIC>& oProjectStatistics, bool bUpdateCache)
{
    return GetState()->EnumerateProjectStatistics(hHost, hProject, oProjectStatistics, bUpdateCache, false);
}

BSLERRCODE CBSLClient::EnumerateProjects(BSLHOST hHost, std::vector<BSLPROJECT>& oProjects, bool bUpdateCache)
{
    return GetState()->EnumerateProjects(hHost, oProjects, bUpdateCache, false);
}

BSLERRCODE CBSLClient::EnumerateTasks(BSLHOST hHost, std::vector<BSLTASK>& oTasks)
{
    return GetState()->EnumerateTasks(hHost, oTasks);
}

BSLERRCODE CBSLClient::EnumerateTaskInstances(BSLHOST hHost, std::vector<BSLTASKINSTANCE>& oTaskInstances, bool bUpdateCache)
{
    return GetState()->EnumerateTaskInstances(hHost, oTaskInstances, bUpdateCache, false);
}

BSLERRCODE CBSLClient::EnumerateTransfers(BSLHOST hHost, std::vector<BSLTRANSFER>& oTransfers, bool bUpdateCache)
{
    return GetState()->EnumerateTransfers(hHost, oTransfers, bUpdateCache, false);
}

BSLERRCODE CBSLClient::FireEvent(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    return GetState()->FireEvent(etEventType, hHost, hHandle);
}

BSLERRCODE CBSLClient::GetApp(BSLAPP hApp, CBSLApp* pApp)
{
    return GetState()->GetApp(hApp, pApp);
}

BSLERRCODE CBSLClient::GetAppEventData(BSLAPP hApp, wxUIntPtr* ppData)
{
    return GetState()->GetAppEventData(hApp, ppData);
}

BSLERRCODE CBSLClient::GetAppVersion(BSLAPPVERSION hAppVersion, CBSLAppVersion* pAppVersion)
{
    return GetState()->GetAppVersion(hAppVersion, pAppVersion);
}

BSLERRCODE CBSLClient::GetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr* ppData)
{
    return GetState()->GetAppVersionEventData(hAppVersion, ppData);
}

BSLERRCODE CBSLClient::GetBOINCDataDirectory(wxString& strData)
{
    return GetState()->GetBOINCDataDirectory(strData);
}

BSLERRCODE CBSLClient::GetBOINCInstallDirectory(wxString& strInstall)
{
    return GetState()->GetBOINCInstallDirectory(strInstall);
}

BSLERRCODE CBSLClient::GetHost(BSLHOST hHost, CBSLHost* pHost, bool bUpdateCache)
{
    return GetState()->GetHost(hHost, pHost, bUpdateCache, false);
}

BSLERRCODE CBSLClient::GetHostEventData(BSLHOST hHost, wxUIntPtr* ppData)
{
    return GetState()->GetHostEventData(hHost, ppData);
}

BSLERRCODE CBSLClient::GetHostStatus(BSLHOST hHost, CBSLHostStatus* pHostStatus, bool bUpdateCache)
{
    return GetState()->GetHostStatus(hHost, pHostStatus, bUpdateCache, false);
}

BSLERRCODE CBSLClient::GetHostStatusEventData(BSLHOST hHost, wxUIntPtr* ppData)
{
    return GetState()->GetHostStatusEventData(hHost, ppData);
}

BSLERRCODE CBSLClient::GetLocalHostName(wxString& strName)
{
    return GetState()->GetLocalHostName(strName);
}

BSLERRCODE CBSLClient::GetLocalHostPassword(wxString& strPassword)
{
    return GetState()->GetLocalHostPassword(strPassword);
}

BSLERRCODE CBSLClient::GetLocalHostPort(long& lPort)
{
    return GetState()->GetLocalHostPort(lPort);
}

BSLERRCODE CBSLClient::GetMessage(BSLMESSAGE hMessage, CBSLMessage* pMessage)
{
    return GetState()->GetMessage(hMessage, pMessage);
}

BSLERRCODE CBSLClient::GetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr* ppData)
{
    return GetState()->GetMessageEventData(hMessage, ppData);
}

BSLERRCODE CBSLClient::GetNotification(BSLNOTIFICATION hNotification, CBSLNotification* pNotification)
{
    return GetState()->GetNotification(hNotification, pNotification);
}

BSLERRCODE CBSLClient::GetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr* ppData)
{
    return GetState()->GetNotificationEventData(hNotification, ppData);
}

BSLERRCODE CBSLClient::GetProject(BSLPROJECT hProject, CBSLProject* pProject)
{
    return GetState()->GetProject(hProject, pProject);
}

BSLERRCODE CBSLClient::GetProjectEventData(BSLPROJECT hProject, wxUIntPtr* ppData)
{
    return GetState()->GetProjectEventData(hProject, ppData);
}

BSLERRCODE CBSLClient::GetProjectListItem(BSLPROJECTLISTITEM hProjectListItem, CBSLProjectListItem* pProjectListItem)
{
    return GetState()->GetProjectListItem(hProjectListItem, pProjectListItem);
}

BSLERRCODE CBSLClient::GetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr* ppData)
{
    return GetState()->GetProjectListItemEventData(hProjectListItem, ppData);
}

BSLERRCODE CBSLClient::GetProjectStatistic(BSLPROJECTSTATISTIC hProjectStatistic, CBSLProjectStatistic* pProjectStatistic)
{
    return GetState()->GetProjectStatistic(hProjectStatistic, pProjectStatistic);
}

BSLERRCODE CBSLClient::GetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr* ppData)
{
    return GetState()->GetProjectStatisticEventData(hProjectStatistic, ppData);
}

BSLERRCODE CBSLClient::GetTask(BSLTASK hTask, CBSLTask* pTask)
{
    return GetState()->GetTask(hTask, pTask);
}

BSLERRCODE CBSLClient::GetTaskEventData(BSLTASK hTask, wxUIntPtr* ppData)
{
    return GetState()->GetTaskEventData(hTask, ppData);
}

BSLERRCODE CBSLClient::GetTaskInstance(BSLTASKINSTANCE hTaskInstance, CBSLTaskInstance* pTaskInstance)
{
    return GetState()->GetTaskInstance(hTaskInstance, pTaskInstance);
}

BSLERRCODE CBSLClient::GetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr* ppData)
{
    return GetState()->GetTaskInstanceEventData(hTaskInstance, ppData);
}

BSLERRCODE CBSLClient::GetTransfer(BSLTRANSFER hTransfer, CBSLTransfer* pTransfer)
{
    return GetState()->GetTransfer(hTransfer, pTransfer);
}

BSLERRCODE CBSLClient::GetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr* ppData)
{
    return GetState()->GetTransferEventData(hTransfer, ppData);
}

BSLERRCODE CBSLClient::LookupAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword)
{
    return GetState()->LookupAccount(hHost, strProjectURL, strIdentifier, strPassword);
}

BSLERRCODE CBSLClient::LookupAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator)
{
    return GetState()->LookupAccountPoll(hHost, uiReturnCode, oMessages, strAuthenticator);
}

bool CBSLClient::IsLocalHostName(const wxString& strHost)
{
    return GetState()->IsLocalHostName(strHost);
}

BSLERRCODE CBSLClient::NetworkAvailable(BSLHOST hHost)
{
    return GetState()->NetworkAvailable(hHost);
}

BSLERRCODE CBSLClient::ProjectAttach(BSLHOST hHost, wxString& strProjectURL, wxString& strProjectName, wxString& strAuthenticator)
{
    return GetState()->ProjectAttach(hHost, strProjectURL, strProjectName, strAuthenticator);
}

BSLERRCODE CBSLClient::ProjectAttachPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages)
{
    return GetState()->ProjectAttachPoll(hHost, uiReturnCode, oMessages);
}

BSLERRCODE CBSLClient::ProjectDetach(BSLPROJECT hProject)
{
    return GetState()->ProjectDetach(hProject);
}

BSLERRCODE CBSLClient::ProjectReset(BSLPROJECT hProject)
{
    return GetState()->ProjectReset(hProject);
}

BSLERRCODE CBSLClient::ProjectUpdate(BSLPROJECT hProject)
{
    return GetState()->ProjectUpdate(hProject);
}

BSLERRCODE CBSLClient::ProjectSetProperty(BSLPROJECT hProject, PROJECTPROPERTY property, wxUint32 uiValue)
{
    return GetState()->ProjectSetProperty(hProject, property, uiValue);
}

BSLERRCODE CBSLClient::RegisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    return GetEventManager()->RegisterEventHandler(pEventHandler, etEventType, hHost, hHandle);
}

BSLERRCODE CBSLClient::RunBenchmarks(BSLHOST hHost)
{
    return GetState()->RunBenchmarks(hHost);
}

BSLERRCODE CBSLClient::SetAppEventData(BSLAPP hApp, wxUIntPtr pData)
{
    return GetState()->SetAppEventData(hApp, pData);
}

BSLERRCODE CBSLClient::SetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr pData)
{
    return GetState()->SetAppVersionEventData(hAppVersion, pData);
}

BSLERRCODE CBSLClient::SetAutoSyncProperty(BSLHOST hHost, CBSLClient::AUTOSYNCPROPERTY property, wxUint32 uiValue)
{
    return GetState()->SetAutoSyncProperty(hHost, property, uiValue);
}

BSLERRCODE CBSLClient::SetHostEventData(BSLHOST hHost, wxUIntPtr pData)
{
    return GetState()->SetHostEventData(hHost, pData);
}

BSLERRCODE CBSLClient::SetHostStatusEventData(BSLHOST hHost, wxUIntPtr pData)
{
    return GetState()->SetHostStatusEventData(hHost, pData);
}

BSLERRCODE CBSLClient::SetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr pData)
{
    return GetState()->SetMessageEventData(hMessage, pData);
}

BSLERRCODE CBSLClient::SetModeCPU(BSLHOST hHost, SETMODE mode, wxUint32 uiDuration)
{
    return GetState()->SetModeCPU(hHost, mode, uiDuration);
}

BSLERRCODE CBSLClient::SetModeGPU(BSLHOST hHost, SETMODE mode, wxUint32 uiDuration)
{
    return GetState()->SetModeGPU(hHost, mode, uiDuration);
}

BSLERRCODE CBSLClient::SetModeNetwork(BSLHOST hHost, SETMODE mode, wxUint32 uiDuration)
{
    return GetState()->SetModeNetwork(hHost, mode, uiDuration);
}

BSLERRCODE CBSLClient::SetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr pData)
{
    return GetState()->SetNotificationEventData(hNotification, pData);
}

BSLERRCODE CBSLClient::SetProjectEventData(BSLPROJECT hProject, wxUIntPtr pData)
{
    return GetState()->SetProjectEventData(hProject, pData);
}

BSLERRCODE CBSLClient::SetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr pData)
{
    return GetState()->SetProjectListItemEventData(hProjectListItem, pData);
}

BSLERRCODE CBSLClient::SetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr pData)
{
    return GetState()->SetProjectStatisticEventData(hProjectStatistic, pData);
}

BSLERRCODE CBSLClient::SetTaskEventData(BSLTASK hTask, wxUIntPtr pData)
{
    return GetState()->SetTaskEventData(hTask, pData);
}

BSLERRCODE CBSLClient::SetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr pData)
{
    return GetState()->SetTaskInstanceEventData(hTaskInstance, pData);
}

BSLERRCODE CBSLClient::SetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr pData)
{
    return GetState()->SetTransferEventData(hTransfer, pData);
}

BSLERRCODE CBSLClient::Shutdown(BSLHOST hHost)
{
    return GetState()->Shutdown(hHost);
}

BSLERRCODE CBSLClient::TaskInstanceAbort(BSLTASKINSTANCE hTaskInstance)
{
    return GetState()->TaskInstanceAbort(hTaskInstance);
}

BSLERRCODE CBSLClient::TaskInstanceSetProperty(BSLTASKINSTANCE hTaskInstance, TASKINSTANCEPROPERTY property, wxUint32 uiValue)
{
    return GetState()->TaskInstanceSetProperty(hTaskInstance, property, uiValue);
}

BSLERRCODE CBSLClient::TransferAbort(BSLTRANSFER hTransfer)
{
    return GetState()->TransferAbort(hTransfer);
}

BSLERRCODE CBSLClient::TransferRetry(BSLTRANSFER hTransfer)
{
    return GetState()->TransferRetry(hTransfer);
}

BSLERRCODE CBSLClient::TransferSetProperty(BSLTRANSFER hTransfer, TRANSFERPROPERTY property, wxUint32 uiValue)
{
    return GetState()->TransferSetProperty(hTransfer, property, uiValue);
}

BSLERRCODE CBSLClient::UnregisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    return GetEventManager()->UnregisterEventHandler(pEventHandler, etEventType, hHost, hHandle);
}

BSLERRCODE CBSLClient::UpdateHostState(BSLHOST hHost)
{
    return GetState()->UpdateHostState(hHost, false);
}
