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

#ifndef _CLIENTSTATEHOST_H_
#define _CLIENTSTATEHOST_H_

// Forward Declares
//
class CRPCConnection;

class CHost: public CObject, public CBSLHost
{
    DECLARE_DYNAMIC_CLASS(CHost)

    friend class CRPCManager;
    friend class CRPCProtocol;

public:
    CHost();
    virtual ~CHost();

    /// \brief Assignment Operator
    virtual CHost& operator= (const CBSLHost&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLHost&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLHost&);

    /// \brief Add a application to the host.
    /// \param[in] pApp A pointer to the application to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddApp(CApp* pApp);

    /// \brief Add a application version to the host.
    /// \param[in] pAppVersion A pointer to the application version to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddAppVersion(CAppVersion* pAppVersion);

    /// \brief Add a message to the host.
    /// \param[in] pMessage A pointer to the message to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddMessage(CMessage* pMessage);

    /// \brief Add a notification to the host.
    /// \param[in] pNotification A pointer to the notification to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddNotification(CNotification* pNotification);

    /// \brief Add a project to the host.
    /// \param[in] pProject A pointer to the project to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddProject(CProject* pProject);

    /// \brief Add a project list item to the host.
    /// \param[in] pProjectListItem A pointer to the project list item to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddProjectListItem(CProjectListItem* pProjectListItem);

    /// \brief Add a RPC profile to the host.
    /// \param[in] pRPCProfile A pointer to the RPC profile to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddRPCProfile(CRPCProfile* pRPCProfile);

    /// \brief Add a sync profile to the host.
    /// \param[in] pSyncProfile A pointer to the Sync profile to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddSyncProfile(CSyncProfile* pSyncProfile);

    /// \brief Add a task to the host.
    /// \param[in] pTask A pointer to the task to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddTask(CTask* pTask);

    /// \brief Add a task instance to the host.
    /// \param[in] pTaskInstance A pointer to the task instance to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddTaskInstance(CTaskInstance* pTaskInstance);

    /// \brief Add a transfer to the host.
    /// \param[in] pTransfer A pointer to the transfer to add.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE AddTransfer(CTransfer* pTransfer);

    /// \brief Delete a application from the host.
    /// \param[in] pApp A pointer to the application to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteApp(CApp* pApp);

    /// \brief Delete a application version from the host.
    /// \param[in] pAppVersion A pointer to the application version to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteAppVersion(CAppVersion* pAppVersion);

    /// \brief Delete a message from the host.
    /// \param[in] pMessage A pointer to the message to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteMessage(CMessage* pMessage);

    /// \brief Delete a notification from the host.
    /// \param[in] pNotification A pointer to the notification to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteNotification(CNotification* pNotification);

    /// \brief Delete a project from the host.
    /// \param[in] pProject A pointer from the project to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteProject(CProject* pProject);

    /// \brief Delete a project list item from the host.
    /// \param[in] pProjectListItem A pointer from the project list item to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteProjectListItem(CProjectListItem* pProjectListItem);

    /// \brief Delete a sync profile from the host.
    /// \param[in] pSyncProfile A pointer to the sync profile to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteSyncProfile(CSyncProfile* pSyncProfile);

    /// \brief Delete a RPC profile from the host.
    /// \param[in] pRPCProfile A pointer from the RPC profile to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteRPCProfile(CRPCProfile* pRPCProfile);

    /// \brief Delete a task from the host.
    /// \param[in] pTask A pointer from the task to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteTask(CTask* pTask);

    /// \brief Delete a task instance from the host.
    /// \param[in] pTaskInstance A pointer to the task instance to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteTaskInstance(CTaskInstance* pTaskInstance);

    /// \brief Delete a transfer from the host.
    /// \param[in] pTransfer A pointer to the transfer to delete.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE DeleteTransfer(CTransfer* pTransfer);

    /// \brief
    virtual void Dispose();

    /// \brief Retrieve all the applications.
    /// \param[out] oApps a vector containing all the applications.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateApps(std::vector<CApp*>& oApps);

    /// \brief Retrieve all the application versions.
    /// \param[out] oAppVersions a vector containing all the application versions.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateAppVersions(std::vector<CAppVersion*>& oAppVersions);

    /// \brief Retrieve all the messages.
    /// \param[out] oMessages a vector containing all the messages.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateMessages(std::vector<CMessage*>& oMessages);

    /// \brief Retrieve all the notifications.
    /// \param[out] oNotifications a vector containing all the notifications.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateNotifications(std::vector<CNotification*>& oNotifications);

    /// \brief Retrieve all the projects.
    /// \param[out] oProjects a vector containing all the projects.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateProjects(std::vector<CProject*>& oProjects);

    /// \brief Retrieve all the projects list items.
    /// \param[out] oProjectList a vector containing all the project list items.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateProjectList(std::vector<CProjectListItem*>& oProjectList);

    /// \brief Retrieve all the RPC profiles.
    /// \param[out] oRPCProfiles a vector containing all the RPC profiles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateRPCProfiles(std::vector<CRPCProfile*>& oRPCProfiles);

    /// \brief Retrieve all the sync profiles.
    /// \param[out] oSyncProfiles a vector containing all the sync profiles.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateSyncProfiles(std::vector<CSyncProfile*>& oSyncProfiles);

    /// \brief Retrieve all the tasks.
    /// \param[out] oTasks a vector containing all the tasks.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateTasks(std::vector<CTask*>& oTasks);

    /// \brief Retrieve all the task instances.
    /// \param[out] oTaskInstances a vector containing all the task instances.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateTaskInstances(std::vector<CTaskInstance*>& oTaskInstances);

    /// \brief Retrieve all the transfers.
    /// \param[out] oTransfers a vector containing all the transfers.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE EnumerateTransfers(std::vector<CTransfer*>& oTransfers);

    /// \brief Find an application pointer for a given unique application key.
    /// \param[in] uiProjectHash the application key to find.
    /// \param[in] uiNameHash the application key to find.
    /// \param[out] ppApp a pointer to the desired application.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindApp(
        wxUint32 uiProjectHash,
        wxUint32 uiNameHash,
        CApp** ppApp,
        CBSLApp* pBSLApp = NULL
    );

    /// \brief Find an application version pointer for a given unique application version key.
    /// \param[in] strAppVersionKey the application version key to find.
    /// \param[out] ppAppVersion a pointer to store the desired application version.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindAppVersion(
        wxUint32 uiProjectHash,
        wxUint32 uiNameHash,
        wxUint32 uiVersion,
        wxUint32 uiPlanClassHash,
        CAppVersion** ppAppVersion,
        CBSLAppVersion* pBSLAppVersion = NULL
    );

    /// \brief Find a message pointer for a given unique message sequence number.
    /// \param[in] iSeqNo the sequence number to find.
    /// \param[out] ppMessage a pointer to store the desired message.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindMessage(
        wxInt32 iSeqNo,
        CMessage** ppMessage,
        CBSLMessage* pBSLMessage = NULL
    );

    /// \brief Find a notification pointer for a given unique notification sequence number.
    /// \param[in] iSeqNo the sequence number to find.
    /// \param[out] ppNotification a pointer to store the desired notification.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindNotification(
        wxInt32 iSeqNo,
        CNotification** ppNotification,
        CBSLNotification* pBSLNotification = NULL
    );

    /// \brief Find a project pointer for a given unique project key.
    /// \param[in] uiMasterURLHash the project key to find.
    /// \param[out] ppProject a pointer to store the desired project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindProject(
        wxUint32 uiMasterURLHash,
        CProject** ppProject,
        CBSLProject* pBSLProject = NULL
    );

    /// \brief Find a project list item pointer for a given unique project list key.
    /// \param[in] uiMasterURLHash the project key to find.
    /// \param[out] ppProjectListItem a pointer to store the desired project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindProjectListItem(
        wxUint32 uiMasterURLHash,
        CProjectListItem** ppProjectListItem,
        CBSLProjectListItem* pBSLProjectListItem = NULL
    );

    /// \brief Find a RPC profile pointer for a given unique RPC profile.
    /// \param[in] pszProfile the profile key to find.
    /// \param[out] ppRPCProfile a pointer to store the desired RPC profile.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindRPCProfile(
        const wxChar* pszProfile,
        CRPCProfile** ppRPCProfile
    );

    /// \brief Find a sync profile pointer for a given unique sync profile key.
    /// \param[in] uiSyncProperty the sync profile to find.
    /// \param[out] ppSyncProfile a pointer to store the desired sync profile.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindSyncProfile(
        CBSLClient::AUTOSYNCPROPERTY uiSyncProperty,
        CSyncProfile** ppSyncProfile
    );

    /// \brief Find a task pointer for a given unique task key.
    /// \param[in] strTaskKey the task key to find.
    /// \param[out] ppTask a pointer to store the desired task.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindTask(
        wxUint32 uiProjectHash,
        wxUint32 uiNameHash,
        CTask** ppTask,
        CBSLTask* pBSLTask = NULL
    );

    /// \brief Find a task instance pointer for a given unique task instance key.
    /// \param[in] strTaskInstanceKey the application key to find.
    /// \param[out] ppTaskInstance a pointer to store the desired task instance.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindTaskInstance(
        wxUint32 uiProjectHash,
        wxUint32 uiNameHash,
        CTaskInstance** ppTaskInstance,
        CBSLTaskInstance* pBSLTaskInstance = NULL
    );

    /// \brief Find a transfer pointer for a given unique transfer key.
    /// \param[in] uiProjectHash the application key to find.
    /// \param[in] uiNameHash the application key to find.
    /// \param[out] ppTransfer a pointer to store the desired transfer.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    BSLERRCODE FindTransfer(
        wxUint32 uiProjectHash,
        wxUint32 uiNameHash,
        CTransfer** ppTransfer,
        CBSLTransfer* pTransfer = NULL
    );

    void ForceRefresh(bool bValue);
    bool IsForceRefreshEnabled();

    bool GetConnectionProperties(wxString& strName, wxString& strPassword, long& lPort);
    bool SetConnectionProperties(wxString& strName, wxString& strPassword, long lPort);

    CONNECTIONSTATE GetConnectionState();
    void SetConnectionState(CONNECTIONSTATE iConnectionState);

    CBSLHostStatus& GetHostStatus();
    void SetHostStatus(CBSLHostStatus& bslHostStatus);

    wxUint32 GetLastMessageSequenceNumber();
    void SetLastMessageSequenceNumber(wxUint32 uiSequenceNumber);

    wxUint32 GetLastNotificationSequenceNumber();
    void SetLastNotificationSequenceNumber(wxUint32 uiSequenceNumber);

    bool SetClientVersion(wxUint32& uiMajor, wxUint32& uiMinor, wxUint32& uiRelease);
    bool SetPlatforms(wxString strPrimaryPlatform, std::vector<wxString>& oSupportedPlatforms);

    BSLERRCODE Update(CBSLHost&);

private:
    bool m_bForceRefresh;

    wxString m_strConnectionName;
    wxString m_strConnectionPassword;
    long m_lConnectionPort;

    wxUint32 m_uiLastMessageSequenceNumber;
    wxUint32 m_uiLastNotificationSequenceNumber;

    CRPCConnection* m_pRPCOnDemand;
    CRPCConnection* m_pRPCStatusUpdate;

    CHostStatus m_HostStatus;

    CDatabaseIndexed<CAppIndex, CApp*, CBSLApp*>* m_pAppsDatabase;
    CDatabaseIndexed<CAppVersionIndex, CAppVersion*, CBSLAppVersion*>* m_pAppVersionsDatabase;
    CDatabaseIndexed<CMessageIndex, CMessage*, CBSLMessage*>* m_pMessagesDatabase;
    CDatabaseIndexed<CNotificationIndex, CNotification*, CBSLNotification*>* m_pNotificationsDatabase;
    CDatabaseIndexed<CProjectIndex, CProject*, CBSLProject*>* m_pProjectsDatabase;
    CDatabaseIndexed<CProjectListItemIndex, CProjectListItem*, CBSLProjectListItem*>* m_pProjectListDatabase;
    CDatabaseIndexed<CTaskIndex, CTask*, CBSLTask*>* m_pTasksDatabase;
    CDatabaseIndexed<CTaskInstanceIndex, CTaskInstance*, CBSLTaskInstance*>* m_pTaskInstancesDatabase;
    CDatabaseIndexed<CTransferIndex, CTransfer*, CBSLTransfer*>* m_pTransfersDatabase;

    CDatabase<CRPCProfile*>* m_pRPCProfilesDatabase;
    CDatabase<CSyncProfile*>* m_pSyncProfilesDatabase;
};

#endif

///
/// \}
