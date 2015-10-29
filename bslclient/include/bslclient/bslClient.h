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
/// \defgroup BSLClient BOINC Sentinels Client Library Interface
/// \{

#ifndef _BSLCLIENT_H_
#define _BSLCLIENT_H_

#include "bslClientEvents.h"

class CBSLClient: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CBSLClient)

public:

    enum PROJECTPROPERTY
    {
        /// \brief
        ProjectPropertyUnknown,
        /// \brief Suspend/Resume a project.
        ProjectPropertySuspend,
        /// \brief Enable/Disable task accumulation for a project.
        ProjectPropertyTaskAccumulation,
        /// \brief Enable/Disable automatic project detach when work is completed.
        ProjectPropertyDetachWhenDone
    };

    enum TASKINSTANCEPROPERTY
    {
        /// \brief
        TaskInstancePropertyUnknown,
        /// \brief Suspend/Resume a task instance.
        TaskInstancePropertySuspend
    };

    enum TRANSFERPROPERTY
    {
        /// \brief
        TransferPropertyUnknown
    };

    enum AUTOSYNCPROPERTY
    {
        /// \brief
        AutoSyncPropertyUnknown,
        /// \brief
        AutoSyncPropertyHostUpdateInterval,
        /// \brief
        AutoSyncPropertyHostStatusUpdateInterval,
        /// \brief
        AutoSyncPropertyMessagesUpdateInterval,
        /// \brief
        AutoSyncPropertyNotificationsUpdateInterval,
        /// \brief
        AutoSyncPropertyProjectListUpdateInterval,
        /// \brief
        AutoSyncPropertyProjectsUpdateInterval,
        /// \brief
        AutoSyncPropertyProjectStatisticsUpdateInterval,
        /// \brief
        AutoSyncPropertyStateUpdateInterval,
        /// \brief
        AutoSyncPropertyTaskInstancesUpdateInterval,
        /// \brief
        AutoSyncPropertyTransfersUpdateInterval,
        /// \brief
        AutoSyncPropertyMessagesCount,
        /// \brief
        AutoSyncPropertyNotificationsCount
    };

    enum SETMODE
    {
        /// \brief
        SetModeUnknown,
        /// \brief
        SetModeAlways,
        /// \brief
        SetModeNever,
        /// \brief
        SetModeAuto,
        /// \brief
        SetModeRestore
    };


    CBSLClient();
    ~CBSLClient();

    /// \brief Initialize the BOINC Sentinels Client Library framework.
    /// \note Must be called from wxApp::OnInit().
    /// \return true on success, false on failure.
    bool OnInit();

    /// \brief Cleanup the BOINC Sentinels Client Library framework.
    /// \note Must be called from wxApp::OnExit().
    /// \return true on success, false on failure.
    bool OnExit();

    /// \brief Establish connection to a BOINC client.
    /// \param[in] strName the name of the BOINC client to connect to.
    /// \param[in] strPassword the password to use.
    /// \param[in] lPort the port number to use.
    /// \param[in] bWait wait until a connection is made or an error occurs.
    /// \param[out] phHost a pointer to a handle to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_ERROR
    /// \retval BSLERR_CONNECT_AUTHENTICATION_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_AUTHENTICATION_ERROR
    /// \retval BSLERR_CONNECT_VERSIONINCOMPATIBILITY_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_VERSIONINCOMPATIBILITY_ERROR
    BSLERRCODE Connect(wxString strName, wxString strPassword, long lPort, bool bWait, BSLHOST* phHost);

    /// \brief Create an account in the desired project for the volunteer.
    /// \param[in] hHost a handle to the host.
    /// \param[in] strProjectURL The URL for a project.
    /// \param[in] strIdentifier The email address or user name to use on the project.
    /// \param[in] strPassword The password to use for the account.
    /// \param[in] strName The name or alias for the account.
    /// \param[in] strTeamName The team name to use for the account.
    /// \param[in] strInviteCode the invite code required to create an account if the project requires one.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE CreateAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword, wxString& strName, wxString& strTeamName, wxString& strInviteCode);

    /// \brief Check the status of a previous create account request.
    /// \param[in] hHost a handle to the host.
    /// \param[out] uiReturnCode the code returned from the project.
    /// \param[out] oMessages a vector containing all the messages returned from the project.
    /// \param[out] strAuthenticator The authenticator returned from the project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE CreateAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator);

    /// \brief Disconnect from a BOINC client.
    /// \param[in] hHost a handle to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE Disconnect(BSLHOST hHost);

    /// \brief Retrieve all the applications for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oApps a vector containing all the application handles for a given host handle.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateApps(BSLHOST hHost, std::vector<BSLAPP>& oApps);

    /// \brief Retrieve all the application versions for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oAppVersions a vector containing all the application version handles for a given host handle.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateAppVersions(BSLHOST hHost, std::vector<BSLAPPVERSION>& oAppVersions);

    /// \brief Retrieve all the hosts.
    /// \param[out] oHosts a vector containing all the host handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateHosts(std::vector<BSLHOST>& oHosts);

    /// \brief Retrieve all the messages for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[in] iSequenceNumber last sequence number processed.
    /// \param[out] oMessages a vector containing all the message handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the message handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateMessages(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLMESSAGE>& oMessages, bool bUpdateCache = true);

    /// \brief Retrieve all the notifications for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[in] iSequenceNumber last sequence number processed.
    /// \param[out] oNotifications a vector containing all the notification handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the notification handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateNotifications(BSLHOST hHost, wxInt32 iSequenceNumber, std::vector<BSLNOTIFICATION>& oNotifications, bool bUpdateCache = true);

    /// \brief Retrieve all the projects for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oProjectListItems a vector containing all the project list handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the project handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateProjectList(BSLHOST hHost, std::vector<BSLPROJECTLISTITEM>& oProjectListItems, bool bUpdateCache = true);

    /// \brief Retrieve all the statistics for a given project on a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[in] hProject a handle to the project.
    /// \param[out] oProjectStatistics a vector containing all the project statistic handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the project handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateProjectStatistics(BSLHOST hHost, BSLPROJECT hProject, std::vector<BSLPROJECTSTATISTIC>& oProjectStatistics, bool bUpdateCache = true);

    /// \brief Retrieve all the projects for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oProjects a vector containing all the project handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the project handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateProjects(BSLHOST hHost, std::vector<BSLPROJECT>& oProjects, bool bUpdateCache = true);

    /// \brief Retrieve all the tasks for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oTasks a vector containing all the task handles for a given host handle.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateTasks(BSLHOST hHost, std::vector<BSLTASK>& oTasks);

    /// \brief Retrieve all the task instances for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oTaskInstances a vector containing all the task instance handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the task instance handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateTaskInstances(BSLHOST hHost, std::vector<BSLTASKINSTANCE>& oTaskInstances, bool bUpdateCache = true);

    /// \brief Retrieve all the transfers for a given host.
    /// \param[in] hHost a handle to the host.
    /// \param[out] oTransfers a vector containing all the transfer handles for a given host handle.
    /// \param[in] bUpdateCache update the local cache before returning the transfer handles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE EnumerateTransfers(BSLHOST hHost, std::vector<BSLTRANSFER>& oTransfers, bool bUpdateCache = true);

    /// \brief Fires an event so all registered event handlers can process it.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host.
    /// \param[in] hHandle handle to an object.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FireEvent(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Copy the application data referenced by the application handle to the application controlled application pointer.
    /// \param[in] hApp a handle to the application.
    /// \param[out] pApp an application supplied pointer to a CBSLApp object to populate with application data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_APP_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APP_NOT_FOUND
    BSLERRCODE GetApp(BSLAPP hApp, CBSLApp* pApp);

    BSLERRCODE GetAppEventData(BSLAPP hApp, wxUIntPtr* ppData);

    /// \brief Copy the application version data referenced by the application version handle to the application controlled application version pointer.
    /// \param[in] hAppVersion a handle to the application version.
    /// \param[out] pAppVersion an application version supplied pointer to a CBSLAppVersion object to populate with application version data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_APPVERSION_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APPVERSION_NOT_FOUND
    BSLERRCODE GetAppVersion(BSLAPPVERSION hAppVersion, CBSLAppVersion* pAppVersion);

    BSLERRCODE GetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr* ppData);

    /// \brief Returns the directory the BOINC data files live in.
    /// \param[out] strData the directory where the BOINC data files live.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE GetBOINCDataDirectory(wxString& strData);

    /// \brief Returns the directory BOINC was installed too.
    /// \param[out] strInstall the directory BOINC was installed too.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE GetBOINCInstallDirectory(wxString& strInstall);

    /// \brief Copy the host data referenced by the host handle to the application controlled host pointer.
    /// \param[in] hHost a handle to the host.
    /// \param[out] pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \param[in] bUpdateCache update the local cache before returning the host handle.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(BSLHOST hHost, CBSLHost* pHost, bool bUpdateCache = true);

    BSLERRCODE GetHostEventData(BSLHOST hHost, wxUIntPtr* ppData);

    /// \brief Copy the host status data referenced by the host status handle to the application controlled host status pointer.
    /// \param[in] hHost a handle to the host to get the status of.
    /// \param[out] pHostStatus an application supplied pointer to a CBSLHostStatus object to populate with host status data.
    /// \param[in] bUpdateCache update the local cache before returning the host status handle.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOSTSTATUS_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOSTSTATUS_NOT_FOUND
    BSLERRCODE GetHostStatus(BSLHOST hHost, CBSLHostStatus* pHostStatus, bool bUpdateCache = true);

    BSLERRCODE GetHostStatusEventData(BSLHOST hHost, wxUIntPtr* ppData);

    /// \brief Returns the locally detected host name sans the domain name.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE GetLocalHostName(wxString& strName);

    /// \brief Returns the password to control the local BOINC client.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE GetLocalHostPassword(wxString& strPassword);

    /// \brief Returns the default port to control the local BOINC client.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE GetLocalHostPort(long& lPort);

    /// \brief Copy the message data referenced by the message handle to the application controlled message pointer.
    /// \param[in] hMessage a handle to the message.
    /// \param[out] pMessage an application supplied pointer to a CBSLMessage object to populate with message data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_MESSAGE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_MESSAGE_NOT_FOUND
    BSLERRCODE GetMessage(BSLMESSAGE hMessage, CBSLMessage* pMessage);

    BSLERRCODE GetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr* ppData);

    /// \brief Copy the notification data referenced by the notification handle to the application controlled notification pointer.
    /// \param[in] hNotification a handle to the notification.
    /// \param[out] pNotification an application supplied pointer to a CBSLNotification object to populate with notification data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_NOTIFICATION_NOT_FOUND \copybrief BSLERRCODE::BSLERR_NOTIFICATION_NOT_FOUND
    BSLERRCODE GetNotification(BSLNOTIFICATION hNotification, CBSLNotification* pNotification);

    BSLERRCODE GetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr* ppData);

    /// \brief Copy the project data referenced by the project handle to the application controlled project pointer.
    /// \param[in] hProject a handle to the project.
    /// \param[out] pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(BSLPROJECT hProject, CBSLProject* pProject);

    BSLERRCODE GetProjectEventData(BSLPROJECT hProject, wxUIntPtr* ppData);

    /// \brief Copy the project list data referenced by the project list item handle to the application controlled project list item pointer.
    /// \param[in] hProjectListItem a handle to the project list item.
    /// \param[out] pProjectListItem an application supplied pointer to a CBSLProjectList object to populate with project list item data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_PROJECTLISTITEM_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECTLISTITEM_NOT_FOUND
    BSLERRCODE GetProjectListItem(BSLPROJECTLISTITEM hProjectListItem, CBSLProjectListItem* pProjectListItem);

    BSLERRCODE GetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr* ppData);

    /// \brief Copy the project statistic data referenced by the project statistic handle to the application controlled project statistic pointer.
    /// \param[in] hProjectStatistic a handle to the project statistic.
    /// \param[out] pProjectStatistic an application supplied pointer to a CBSLProjectStatistic object to populate with project statistic data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_PROJECTSTATISTIC_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECTSTATISTIC_NOT_FOUND
    BSLERRCODE GetProjectStatistic(BSLPROJECTSTATISTIC hProjectStatistic, CBSLProjectStatistic* pProjectStatistic);

    BSLERRCODE GetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr* ppData);

    /// \brief Copy the task data referenced by the task handle to the application controlled task pointer.
    /// \param[in] hTask a handle to the task.
    /// \param[out] pTask an application supplied pointer to a CBSLTask object to populate with task data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_TASK_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASK_NOT_FOUND
    BSLERRCODE GetTask(BSLTASK hTask, CBSLTask* pTask);

    BSLERRCODE GetTaskEventData(BSLTASK hTask, wxUIntPtr* ppData);

    /// \brief Copy the task instance data referenced by the task instance handle to the application controlled task instance pointer.
    /// \param[in] hTaskInstance a handle to the task instance.
    /// \param[out] pTaskInstance an application supplied pointer to a CBSLTaskInstance object to populate with task instance data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_TASKINSTANCE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASKINSTANCE_NOT_FOUND
    BSLERRCODE GetTaskInstance(BSLTASKINSTANCE hTaskInstance, CBSLTaskInstance* pTaskInstance);

    BSLERRCODE GetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr* ppData);

    /// \brief Copy the transfer data referenced by the transfer handle to the application controlled transfer pointer.
    /// \param[in] hTransfer a handle to the transfer.
    /// \param[out] pTransfer an application supplied pointer to a CBSLTransfer object to populate with transfer data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_TRANSFER_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TRANSFER_NOT_FOUND
    BSLERRCODE GetTransfer(BSLTRANSFER hTransfer, CBSLTransfer* pTransfer);

    BSLERRCODE GetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr* ppData);

    /// \brief Lookup an account in the desired project for the volunteer.
    /// \param[in] hHost a handle to the host.
    /// \param[in] strProjectURL The URL for a project.
    /// \param[in] strIdentifier The email address or user name to use on the project.
    /// \param[in] strPassword The password to use for the account.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE LookupAccount(BSLHOST hHost, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword);

    /// \brief Check the status of a previous lookup account request.
    /// \param[in] hHost a handle to the host.
    /// \param[out] uiReturnCode the code returned from the project.
    /// \param[out] oMessages a vector containing all the messages returned from the project.
    /// \param[out] strAuthenticator The authenticator returned from the project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE LookupAccountPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator);

    /// \brief Determines if the supplied host name is considered the local host.
    /// \param[out] strHost a host name to check.
    /// \return true if the supplied host name is the local host, otherwise false.
    bool IsLocalHostName(const wxString& strHost);

    /// \brief Notify the BOINC client that the network is now available for use.
    /// \param[in] hHost a handle to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE NetworkAvailable(BSLHOST hHost);

    /// \brief Attach to a project.
    /// \param[in] hHost a handle to the host.
    /// \param[in] strProjectURL The URL for a project.
    /// \param[in] strProjectName The name for a project.
    /// \param[in] strAuthenticator The authenticator to use for the attach.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE ProjectAttach(BSLHOST hHost, wxString& strProjectURL, wxString& strProjectName, wxString& strAuthenticator);

    /// \brief Check the status of a previous attach request.
    /// \param[in] hHost a handle to the host.
    /// \param[out] uiReturnCode the code returned from the project.
    /// \param[out] oMessages a vector containing all the messages returned from the project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_INVALID_PARAMETER \copybrief BSLERRCODE::BSLERR_INVALID_PARAMETER
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE ProjectAttachPoll(BSLHOST hHost, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages);

    /// \brief Detach from a project.
    /// \param[in] hProject a handle to the project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE ProjectDetach(BSLPROJECT hProject);

    /// \brief Reset a project.
    /// \param[in] hProject a handle to the project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE ProjectReset(BSLPROJECT hProject);

    /// \brief Update a project.
    /// \param[in] hProject a handle to the project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE ProjectUpdate(BSLPROJECT hProject);

    /// \brief Set property for a project.
    /// \param[in] hProject a handle to the project.
    /// \param[in] property the property to be modified.
    /// \param[in] uiValue the value to assign to the property.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE ProjectSetProperty(BSLPROJECT hProject, PROJECTPROPERTY property, wxUint32 uiValue);

    /// \brief Registers a window to receive the desired events.
    /// \param[in] pEventHandler an event handler to receive the desired event.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host, if NULL then the window will receive events for all hosts.
    /// \param[in] hHandle handle to an object, if NULL then the window will receive events for all objects of the general type.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE RegisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Run the benchmarks for a BOINC client.
    /// \param[in] hHost a handle to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE RunBenchmarks(BSLHOST hHost);

    BSLERRCODE SetAppEventData(BSLAPP hApp, wxUIntPtr pData);

    BSLERRCODE SetAppVersionEventData(BSLAPPVERSION hAppVersion, wxUIntPtr pData);

    /// \brief Setup automatic synchronization for RPCs and item counts.
    /// \param[in] hHost a handle to the host.
    /// \param[in] property the property to be modified.
    /// \param[in] uiValue what value to set the property too.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE SetAutoSyncProperty(BSLHOST hHost, AUTOSYNCPROPERTY property, wxUint32 uiValue);

    BSLERRCODE SetHostEventData(BSLHOST hHost, wxUIntPtr pData);

    BSLERRCODE SetHostStatusEventData(BSLHOST hHost, wxUIntPtr pData);

    BSLERRCODE SetMessageEventData(BSLMESSAGE hMessage, wxUIntPtr pData);

    /// \brief Set the CPU mode for the BOINC client.
    /// \param[in] hHost a handle to the host.
    /// \param[in] mode the new mode to use.
    /// \param[in] uiDuration duration of the new mode. a value of 0 makes it permanent.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE SetModeCPU(BSLHOST hHost, SETMODE mode, wxUint32 uiDuration);

    /// \brief Set the GPU mode for the BOINC client.
    /// \param[in] hHost a handle to the host.
    /// \param[in] mode the new mode to use.
    /// \param[in] uiDuration duration of the new mode. a value of 0 makes it permanent.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE SetModeGPU(BSLHOST hHost, SETMODE mode, wxUint32 uiDuration);

    /// \brief Set the network mode for the BOINC client.
    /// \param[in] hHost a handle to the host.
    /// \param[in] mode the new mode to use.
    /// \param[in] uiDuration duration of the new mode. a value of 0 makes it permanent.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE SetModeNetwork(BSLHOST hHost, SETMODE mode, wxUint32 uiDuration);

    BSLERRCODE SetNotificationEventData(BSLNOTIFICATION hNotification, wxUIntPtr pData);

    BSLERRCODE SetProjectEventData(BSLPROJECT hProject, wxUIntPtr pData);

    BSLERRCODE SetProjectListItemEventData(BSLPROJECTLISTITEM hProjectListItem, wxUIntPtr pData);

    BSLERRCODE SetProjectStatisticEventData(BSLPROJECTSTATISTIC hProjectStatistic, wxUIntPtr pData);

    BSLERRCODE SetTaskEventData(BSLTASK hTask, wxUIntPtr pData);

    BSLERRCODE SetTaskInstanceEventData(BSLTASKINSTANCE hTaskInstance, wxUIntPtr pData);

    BSLERRCODE SetTransferEventData(BSLTRANSFER hTransfer, wxUIntPtr pData);

    /// \brief Gracefully shutdown a BOINC client.
    /// \param[in] hHost a handle to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE Shutdown(BSLHOST hHost);

    /// \brief Abort a task instance.
    /// \param[in] hTaskInstance a handle to the task instance.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_TASKINSTANCE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASKINSTANCE_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE TaskInstanceAbort(BSLTASKINSTANCE hTaskInstance);

    /// \brief Set property for a task instance.
    /// \param[in] hTaskInstance a handle to the task instance.
    /// \param[in] property the property to be modified.
    /// \param[in] uiValue the value to assign to the property.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_TASKINSTANCE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASKINSTANCE_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE TaskInstanceSetProperty(BSLTASKINSTANCE hTaskInstance, TASKINSTANCEPROPERTY property, wxUint32 uiValue);

    /// \brief Detach from a project.
    /// \param[in] hTransfer a handle to the transfer.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_TRANSFER_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TRANSFER_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE TransferAbort(BSLTRANSFER hTransfer);

    /// \brief Detach from a project.
    /// \param[in] hTransfer a handle to the transfer.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_TRANSFER_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TRANSFER_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE TransferRetry(BSLTRANSFER hTransfer);

    /// \brief Set property for a transfer.
    /// \param[in] hTransfer a handle to the transfer.
    /// \param[in] property the property to be modified.
    /// \param[in] uiValue the value to assign to the property.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    /// \retval BSLERR_TASKINSTANCE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASKINSTANCE_NOT_FOUND
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE TransferSetProperty(BSLTRANSFER hTransfer, TRANSFERPROPERTY property, wxUint32 uiValue);

    /// \brief Unregisters a window and stops sending the desired events.
    /// \param[in] pEventHandler an event handler to stop receiving the desired event.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host, if NULL then the window will stop receiving events for all hosts.
    /// \param[in] hHandle handle to an object, if NULL then the window will stop receiving events for all objects of the general type.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE UnregisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Update host specific state (applications, application versions, tasks, task instances, etc.)
    /// \param[in] hHost a handle to the host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE UpdateHostState(BSLHOST hHost);
};

#endif

///
/// \}
