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
/// \defgroup LibraryState Library State
/// \{

#ifndef _CLIENTSTATE_H_
#define _CLIENTSTATE_H_

// Forward Declares
//
class CHost;
template<class T>
    class CDatabase;

class CClientState: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CClientState)

public:

    CClientState();
    ~CClientState();

    /// \copydoc CBSLClient::OnInit()
    bool OnInit();

    /// \copydoc CBSLClient::OnExit()
    bool OnExit();

    /// \copydoc CBSLClient::Connect()
    BSLERRCODE Connect(wxString& strName, wxString& strPassword, long lPort, bool bWait, BSLHOST* phHost);

    /// \copydoc CBSLClient::CreateAccount()
    BSLERRCODE CreateAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword, wxString& strName, wxString& strTeamName, wxString& strInviteCode);

    /// \copydoc CBSLClient::CreateAccountPoll()
    BSLERRCODE CreateAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator);

    /// \copydoc CBSLClient::Disconnect()
    BSLERRCODE Disconnect(BSLHOST hHost);

    /// \brief Add a host to the host database.
    /// \param[in] pHost a pointer to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    BSLERRCODE AddHost(CHost* pHost);

    /// \brief Delete a host from the host database.
    /// \param[in] pHost a pointer to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    BSLERRCODE DeleteHost(CHost* pHost);

    /// \copydoc CBSLClient::EnumerateApps()
    BSLERRCODE EnumerateApps(BSLHOST hHost, std::vector<BSLAPP>& oApps);

    /// \copydoc CBSLClient::EnumerateAppVersions()
    BSLERRCODE EnumerateAppVersions(BSLHOST hHost, std::vector<BSLAPPVERSION>& oAppVersions);

    /// \copydoc CBSLClient::EnumerateHosts()
    BSLERRCODE EnumerateHosts(std::vector<BSLHOST>& oHosts);

    /// \brief Retrieve all the messages for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[in] iSequenceNumber last sequence number processed.
    /// \param[out] oMessages a vector containing all the message handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the message handles.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateMessages(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLMESSAGE>& oMessages, bool bUpdateCache, bool bBackgroundOperation);

    /// \brief Retrieve all the notifications for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[in] iSequenceNumber last sequence number processed.
    /// \param[out] oNotifications a vector containing all the notification handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the notification handles.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateNotifications(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLNOTIFICATION>& oNotifications, bool bUpdateCache, bool bBackgroundOperation);

    /// \brief Retrieve all the projects for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oProjectListItems a vector containing all the project list handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the project handles.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateProjectList(BSLHOST hHost, std::vector<BSLPROJECTLISTITEM>& oProjectListItems, bool bUpdateCache, bool bBackgroundOperation);

    /// \brief Retrieve all the statistics for a given project on a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[in] hProject a handle to the project.
    /// \param[out] oProjectStatistics a vector containing all the project statistic handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the project handles.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateProjectStatistics(BSLHOST hHost, BSLPROJECT hProject, std::vector<BSLPROJECTSTATISTIC>& oProjectStatistics, bool bUpdateCache, bool bBackgroundOperation);

    /// \brief Retrieve all the projects for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oProjects a vector containing all the project handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the project handles.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateProjects(BSLHOST hHost, std::vector<BSLPROJECT>& oProjects, bool bUpdateCache, bool bBackgroundOperation);

    /// \copydoc CBSLClient::EnumerateTasks()
    BSLERRCODE EnumerateTasks(BSLHOST hHost, std::vector<BSLTASK>& oTasks);

    /// \brief Retrieve all the task instances for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oTaskInstances a vector containing all the task instance handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the task instance handles.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateTaskInstances(BSLHOST hHost, std::vector<BSLTASKINSTANCE>& oTaskInstances, bool bUpdateCache, bool bBackgroundOperation);

    /// \brief Retrieve all the transfers for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oTransfers a vector containing all the transfer handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the transfer handles.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateTransfers(BSLHOST hHost, std::vector<BSLTRANSFER>& oTransfers, bool bUpdateCache, bool bBackgroundOperation);

    /// \copydoc CBSLClient::FireEvent()
    BSLERRCODE FireEvent(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \copydoc CBSLClient::GetApp()
    BSLERRCODE GetApp(BSLAPP hApp, CBSLApp* pApp);

    /// \copydoc CBSLClient::GetAppEventData()
    BSLERRCODE GetAppEventData(BSLAPP hApp, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetAppVersion()
    BSLERRCODE GetAppVersion(BSLAPPVERSION hAppVersion, CBSLAppVersion* pAppVersion);

    /// \copydoc CBSLClient::GetAppVersionEventData()
    BSLERRCODE GetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetBOINCDataDirectory()
    BSLERRCODE GetBOINCDataDirectory(wxString& strData);

    /// \copydoc CBSLClient::GetBOINCInstallDirectory()
    BSLERRCODE GetBOINCInstallDirectory(wxString& strInstall);

    /// \brief Copy the host data referenced by the host handle to the application controlled host pointer.
    /// \param[in] hHost a handle to the host.
    /// \param[out] pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \param[in] bUpdateCache update the local cache before returning the host handle.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(BSLHOST hHost, CBSLHost* pHost, bool bUpdateCache, bool bBackgroundOperation);

    /// \copydoc CBSLClient::GetHostEventData()
    BSLERRCODE GetHostEventData(BSLHOST hHost, wxUIntPtr* ppData);

    /// \brief Copy the host status data referenced by the host status handle to the application controlled host status pointer.
    /// \param[in] hHost a handle to the host to get the status of.
    /// \param[out] pHostStatus an application supplied pointer to a CBSLHostStatus object to populate with host status data.
    /// \param[in] bUpdateCache update the local cache before returning the host status handle.
    /// \param[in] bBackgroundOperation if bUpdateCache is true, then whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOSTSTATUS_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOSTSTATUS_NOT_FOUND
    BSLERRCODE GetHostStatus(BSLHOST hHost, CBSLHostStatus* pHostStatus, bool bUpdateCache, bool bBackgroundOperation);

    /// \copydoc CBSLClient::GetHostStatusEventData()
    BSLERRCODE GetHostStatusEventData(BSLHOST hHost, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetLocalHostName()
    BSLERRCODE GetLocalHostName(wxString& strName);

    /// \copydoc CBSLClient::GetLocalHostPassword()
    BSLERRCODE GetLocalHostPassword(wxString& strPassword);

    /// \copydoc CBSLClient::GetLocalHostPort()
    BSLERRCODE GetLocalHostPort(long& lPort);

    /// \copydoc CBSLClient::GetMessage()
    BSLERRCODE GetMessage(BSLMESSAGE hMessage, CBSLMessage* pMessage);

    /// \copydoc CBSLClient::GetMessageEventData()
    BSLERRCODE GetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetNotification()
    BSLERRCODE GetNotification(BSLNOTIFICATION hNotification, CBSLNotification* pNotification);

    /// \copydoc CBSLClient::GetNotificationEventData()
    BSLERRCODE GetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetProject()
    BSLERRCODE GetProject(BSLPROJECT hProject, CBSLProject* pProject);

    /// \copydoc CBSLClient::GetProjectEventData()
    BSLERRCODE GetProjectEventData(BSLPROJECT hProject, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetProjectListItem()
    BSLERRCODE GetProjectListItem(BSLPROJECTLISTITEM hProjectListItem, CBSLProjectListItem* pProjectListItem);

    /// \copydoc CBSLClient::GetProjectListItemEventData()
    BSLERRCODE GetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetProjectStatistic()
    BSLERRCODE GetProjectStatistic(BSLPROJECTSTATISTIC hProjectStatistic, CBSLProjectStatistic* pProjectStatistic);

    /// \copydoc CBSLClient::GetProjectStatisticEventData()
    BSLERRCODE GetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetTask()
    BSLERRCODE GetTask(BSLTASK hTask, CBSLTask* pTask);

    /// \copydoc CBSLClient::GetTaskEventData()
    BSLERRCODE GetTaskEventData(BSLTASK hTask, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetTaskInstance()
    BSLERRCODE GetTaskInstance(BSLTASKINSTANCE hTaskInstance, CBSLTaskInstance* pTaskInstance);

    /// \copydoc CBSLClient::GetTaskInstanceEventData()
    BSLERRCODE GetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr* ppData);

    /// \copydoc CBSLClient::GetTransfer()
    BSLERRCODE GetTransfer(BSLTRANSFER hTransfer, CBSLTransfer* pTransfer);

    /// \copydoc CBSLClient::GetTransferEventData()
    BSLERRCODE GetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr* ppData);

    /// \brief
    bool IsShutdownInitiated();

    /// \copydoc CBSLClient::LookupAccount()
    BSLERRCODE LookupAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword);

    /// \copydoc CBSLClient::LookupAccountPoll()
    BSLERRCODE LookupAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator);

    /// \copydoc CBSLClient::IsLocalHostName()
    bool IsLocalHostName(const wxString& strHost);

    /// \copydoc CBSLClient::NetworkAvailable()
    BSLERRCODE NetworkAvailable(BSLHOST hHost);

    /// \copydoc CBSLClient::ProjectAttach()
    BSLERRCODE ProjectAttach(BSLHOST hHost, wxString& strProjectURL, wxString& strProjectName, wxString& strAuthenticator);

    /// \copydoc CBSLClient::ProjectAttachPoll()
    BSLERRCODE ProjectAttachPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages);

    /// \copydoc CBSLClient::ProjectDetach()
    BSLERRCODE ProjectDetach(BSLPROJECT hProject);

    /// \copydoc CBSLClient::ProjectReset()
    BSLERRCODE ProjectReset(BSLPROJECT hProject);

    /// \copydoc CBSLClient::ProjectUpdate()
    BSLERRCODE ProjectUpdate(BSLPROJECT hProject);

    /// \copydoc CBSLClient::ProjectSetProperty()
    BSLERRCODE ProjectSetProperty(BSLPROJECT hProject, CBSLClient::PROJECTPROPERTY property, wxUint32 uiValue);

    /// \copydoc CBSLClient::RunBenchmarks()
    BSLERRCODE RunBenchmarks(BSLHOST hHost);

    /// \copydoc CBSLClient::SetAppEventData()
    BSLERRCODE SetAppEventData(BSLAPP hApp, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetAppVersionEventData()
    BSLERRCODE SetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetAutoSyncProperty()
    BSLERRCODE SetAutoSyncProperty(BSLHOST hHost, CBSLClient::AUTOSYNCPROPERTY property, wxUint32 uiValue);

    /// \copydoc CBSLClient::SetHostEventData()
    BSLERRCODE SetHostEventData(BSLHOST hHost, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetHostStatusEventData()
    BSLERRCODE SetHostStatusEventData(BSLHOST hHost, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetMessageEventData()
    BSLERRCODE SetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetModeCPU()
    BSLERRCODE SetModeCPU(BSLHOST hHost, CBSLClient::SETMODE mode, wxUint32 uiDuration);

    /// \copydoc CBSLClient::SetModeGPU()
    BSLERRCODE SetModeGPU(BSLHOST hHost, CBSLClient::SETMODE mode, wxUint32 uiDuration);

    /// \copydoc CBSLClient::SetModeNetwork()
    BSLERRCODE SetModeNetwork(BSLHOST hHost, CBSLClient::SETMODE mode, wxUint32 uiDuration);

    /// \copydoc CBSLClient::SetNotificationEventData()
    BSLERRCODE SetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetProjectEventData()
    BSLERRCODE SetProjectEventData(BSLPROJECT hProject, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetProjectListItemEventData()
    BSLERRCODE SetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetProjectStatisticEventData()
    BSLERRCODE SetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetTaskEventData()
    BSLERRCODE SetTaskEventData(BSLTASK hTask, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetTaskInstanceEventData()
    BSLERRCODE SetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr pData);

    /// \copydoc CBSLClient::SetTransferEventData()
    BSLERRCODE SetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr pData);

    /// \brief
    BSLERRCODE SetShutdownInitiated(bool bShutdownInitiated);

    /// \copydoc CBSLClient::Shutdown()
    BSLERRCODE Shutdown(BSLHOST hHost);

    /// \copydoc CBSLClient::TaskInstanceAbort()
    BSLERRCODE TaskInstanceAbort(BSLTASKINSTANCE hTaskInstance);

    /// \copydoc CBSLClient::TaskInstanceSetProperty()
    BSLERRCODE TaskInstanceSetProperty(BSLTASKINSTANCE hTaskInstance, CBSLClient::TASKINSTANCEPROPERTY property, wxUint32 uiValue);

    /// \copydoc CBSLClient::TransferAbort()
    BSLERRCODE TransferAbort(BSLTRANSFER hTransfer);

    /// \copydoc CBSLClient::TransferRetry()
    BSLERRCODE TransferRetry(BSLTRANSFER hTransfer);

    /// \copydoc CBSLClient::TransferSetProperty()
    BSLERRCODE TransferSetProperty(BSLTRANSFER hTransfer, CBSLClient::TRANSFERPROPERTY property, wxUint32 uiValue);

    /// \brief Update host specific state (applications, application versions, tasks, task instances, etc.)
    /// \param[in] hHost a handle to the host.
    /// \param[in] bBackgroundOperation whether the desired operation should be performed in a background thread.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE UpdateHostState(BSLHOST hHost, bool bBackgroundOperation);

    /// \brief Clear a character buffer.
    /// \param[in] v the pointer to the beginning of the buffer to clear.
    /// \param[in] n the number of characters to clear.
    wxChar* ClearMemory(wxChar* v, size_t n);

private:

    CDatabase<CHost*>* m_pHostsDatabase;

    wxString m_strLocalHostName;
    wxString m_strLocalFullHostName;

    bool m_bShutdownInitiated;
};

#endif

///
/// \}
