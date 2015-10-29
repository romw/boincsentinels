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
#include "RPCTypes.h"
#include "ClientState.h"
#include "GarbageCollector.h"

IMPLEMENT_DYNAMIC_CLASS(CGarbageCollector, wxObject);

CGarbageCollector::CGarbageCollector() :
wxObject()
{
    m_pHost = NULL;
    m_dtNow = wxDateTime((time_t)0);
}

CGarbageCollector::~CGarbageCollector()
{
}

void CGarbageCollector::Execute(CHost* pHost)
{
    m_pHost = pHost;
    m_dtNow = wxDateTime::Now();

    PruneMessages();
    PruneNotifications();
    RecycleProjectListItems();
    RecycleTransfers();
    RecycleTaskInstances();
    RecycleTasks();
    RecycleAppVersions();
    RecycleApps();
    RecycleProjects();
}

void CGarbageCollector::PruneMessages()
{
    BSLERRCODE rc;
    std::vector<CMessage*> oMessages;
    CSyncProfile* pSyncProfile = NULL;
    wxUint32 uiCount = 0;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyMessagesCount, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    uiCount = pSyncProfile->GetValue();
    if (!uiCount) return;

    rc = m_pHost->EnumerateMessages(oMessages);
    if (BSLERR_SUCCESS != rc) return;

    while (oMessages.size() > uiCount)
    {
        m_pHost->DeleteMessage(*oMessages.begin());
    }
}

void CGarbageCollector::PruneNotifications()
{
    BSLERRCODE rc;
    std::vector<CNotification*> oNotifications;
    CSyncProfile* pSyncProfile = NULL;
    wxUint32 uiCount = 0;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyNotificationsCount, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    uiCount = pSyncProfile->GetValue();
    if (!uiCount) return;

    rc = m_pHost->EnumerateNotifications(oNotifications);
    if (BSLERR_SUCCESS != rc) return;

    while (oNotifications.size() > uiCount)
    {
        m_pHost->DeleteNotification(*oNotifications.begin());
    }
}

void CGarbageCollector::RecycleProjectListItems()
{
    BSLERRCODE rc;
    std::vector<CProjectListItem*> oProjectListItems;
    std::vector<CProjectListItem*>::iterator iter;
    CProjectListItem* pProjectListItem = NULL;
    CRPCProfile* pRPCProfile = NULL;
    CSyncProfile* pSyncProfile = NULL;
    wxDateTime dtExpirationDate = wxDateTime((time_t)0);
    wxDateTime dtRPCCompletedDate = wxDateTime((time_t)0);
    wxUint32 uiInterval = 0;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyProjectListUpdateInterval, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    rc = m_pHost->FindRPCProfile(CLASSINFO(CRPCSyncProjectList)->GetClassName(), &pRPCProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pRPCProfile) return;

    uiInterval = pSyncProfile->GetValue();
    if (!uiInterval) return;

    dtRPCCompletedDate = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();

    rc = m_pHost->EnumerateProjectList(oProjectListItems);
    if (BSLERR_SUCCESS != rc) return;

    for (iter = oProjectListItems.begin(); iter != oProjectListItems.end(); ++iter)
    {
        pProjectListItem = *iter;

        // An item is deemed expired if it wasn't refreshed the last time the synchronize
        // RPC was called.
        //
        dtExpirationDate =
            pProjectListItem->GetLastModifiedTime() +
            wxTimeSpan(0, 0, uiInterval, 0) +
            wxTimeSpan(0, 0, 0, 1250);

        if ((m_dtNow > dtExpirationDate) && (dtRPCCompletedDate > dtExpirationDate))
        {
            wxLogTrace(wxT("Function Status"),
                wxT("CGarbageCollector::RecycleProjectListItems - Recycle '%p', dtNow: '%s', dtExpirationDate: '%s', dtRPCCompletedDate: '%s'"),
                pProjectListItem,
                m_dtNow.Format(wxT("%H:%M:%S.%l")).c_str(),
                dtExpirationDate.Format(wxT("%H:%M:%S.%l")).c_str(),
                dtRPCCompletedDate.Format(wxT("%H:%M:%S.%l")).c_str()
            );

            m_pHost->DeleteProjectListItem(pProjectListItem);
        }
    }
}

void CGarbageCollector::RecycleTransfers()
{
    BSLERRCODE rc;
    std::vector<CTransfer*> oTransfers;
    std::vector<CTransfer*>::iterator iter;
    CTransfer* pTransfer = NULL;
    CRPCProfile* pRPCProfile = NULL;
    CSyncProfile* pSyncProfile = NULL;
    wxDateTime dtExpirationDate = wxDateTime((time_t)0);
    wxDateTime dtRPCCompletedDate = wxDateTime((time_t)0);
    wxUint32 uiInterval = 0;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyTransfersUpdateInterval, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    rc = m_pHost->FindRPCProfile(CLASSINFO(CRPCSyncTransfers)->GetClassName(), &pRPCProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pRPCProfile) return;

    uiInterval = pSyncProfile->GetValue();
    if (!uiInterval) return;

    dtRPCCompletedDate = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();

    rc = m_pHost->EnumerateTransfers(oTransfers);
    if (BSLERR_SUCCESS != rc) return;

    for (iter = oTransfers.begin(); iter != oTransfers.end(); ++iter)
    {
        pTransfer = *iter;

        // An item is deemed expired if it wasn't refreshed the last time the synchronize
        // RPC was called.
        //
        dtExpirationDate =
            pTransfer->GetLastModifiedTime() +
            wxTimeSpan(0, 0, uiInterval, 0) +
            wxTimeSpan(0, 0, 0, 250);

        if ((m_dtNow > dtExpirationDate) && (dtRPCCompletedDate > dtExpirationDate))
        {
            wxLogTrace(wxT("Function Status"),
                wxT("CGarbageCollector::RecycleTransfers - Recycle '%p', dtNow: '%s', dtExpirationDate: '%s', dtRPCCompletedDate: '%s'"),
                pTransfer,
                m_dtNow.Format(wxT("%H:%M:%S.%l")).c_str(),
                dtRPCCompletedDate.Format(wxT("%H:%M:%S.%l")).c_str(),
                dtExpirationDate.Format(wxT("%H:%M:%S.%l")).c_str()
            );

            m_pHost->DeleteTransfer(pTransfer);
        }
    }
}

void CGarbageCollector::RecycleTaskInstances()
{
    BSLERRCODE rc;
    std::vector<CTaskInstance*> oTaskInstances;
    std::vector<CTaskInstance*>::iterator iter;
    CTaskInstance* pTaskInstance = NULL;
    CRPCProfile* pRPCProfile = NULL;
    CSyncProfile* pSyncProfile = NULL;
    wxDateTime dtExpirationDate = wxDateTime((time_t)0);
    wxDateTime dtRPCCompletedDate = wxDateTime((time_t)0);
    wxUint32 uiInterval = 0;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyTaskInstancesUpdateInterval, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    rc = m_pHost->FindRPCProfile(CLASSINFO(CRPCSyncTaskInstances)->GetClassName(), &pRPCProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pRPCProfile) return;

    uiInterval = pSyncProfile->GetValue();
    if (!uiInterval) return;

    dtRPCCompletedDate = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();

    rc = m_pHost->EnumerateTaskInstances(oTaskInstances);
    if (BSLERR_SUCCESS != rc) return;

    for (iter = oTaskInstances.begin(); iter != oTaskInstances.end(); ++iter)
    {
        pTaskInstance = *iter;

        // An item is deemed expired if it wasn't refreshed the last time the synchronize
        // RPC was called.
        //
        dtExpirationDate =
            pTaskInstance->GetLastModifiedTime() +
            wxTimeSpan(0, 0, uiInterval, 0) +
            wxTimeSpan(0, 0, 0, 250);

        if ((m_dtNow > dtExpirationDate) && (dtRPCCompletedDate > dtExpirationDate))
        {
            wxLogTrace(wxT("Function Status"),
                wxT("CGarbageCollector::RecycleTaskInstances - Recycle '%p', dtNow: '%s', dtExpirationDate: '%s', dtRPCCompletedDate: '%s'"),
                pTaskInstance,
                m_dtNow.Format(wxT("%H:%M:%S.%l")).c_str(),
                dtRPCCompletedDate.Format(wxT("%H:%M:%S.%l")).c_str(),
                dtExpirationDate.Format(wxT("%H:%M:%S.%l")).c_str()
            );

            m_pHost->DeleteTaskInstance(pTaskInstance);
        }
    }
}

void CGarbageCollector::RecycleTasks()
{
    BSLERRCODE rc;
    std::vector<CTask*> oTasks;
    std::vector<CTaskInstance*> oTaskInstances;
    std::vector<CTask*>::iterator iterTasks;
    std::vector<CTaskInstance*>::iterator iterTaskInstances;
    CTask* pTask = NULL;
    CTaskInstance* pTaskInstance = NULL;
    CRPCProfile* pRPCProfile = NULL;
    CSyncProfile* pSyncProfile = NULL;
    wxDateTime dtExpirationDate = wxDateTime((time_t)0);
    wxDateTime dtRPCCompletedDate = wxDateTime((time_t)0);
    wxUint32 uiInterval = 0;
    bool bTaskInstanceFound = false;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyStateUpdateInterval, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    rc = m_pHost->FindRPCProfile(CLASSINFO(CRPCSyncState)->GetClassName(), &pRPCProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pRPCProfile) return;

    uiInterval = pSyncProfile->GetValue();
    if (!uiInterval) return;

    dtRPCCompletedDate = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();

    rc = m_pHost->EnumerateTasks(oTasks);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateTaskInstances(oTaskInstances);
    if (BSLERR_SUCCESS != rc) return;

    for (iterTasks = oTasks.begin(); iterTasks != oTasks.end(); ++iterTasks)
    {
        pTask = *iterTasks;

        // An item is deemed expired if it wasn't refreshed the last time the synchronize
        // RPC was called.
        //
        dtExpirationDate =
            pTask->GetLastModifiedTime() +
            wxTimeSpan(0, 0, uiInterval, 0) +
            wxTimeSpan(0, 0, 0, 250);

        if ((m_dtNow > dtExpirationDate) && (dtRPCCompletedDate > dtExpirationDate))
        {
            // Sanity Check: Make sure their are no task instances that refer to this task
            bTaskInstanceFound = false;

            for (iterTaskInstances = oTaskInstances.begin(); iterTaskInstances != oTaskInstances.end(); ++iterTaskInstances)
            {
                pTaskInstance = *iterTaskInstances;
                if (pTaskInstance->GetTaskHandle() == pTask->GetTaskHandle())
                {
                    bTaskInstanceFound = true;
                }
            }

            if (!bTaskInstanceFound)
            {
                wxLogTrace(wxT("Function Status"),
                    wxT("CGarbageCollector::RecycleTasks - Recycle '%p', dtNow: '%s', dtExpirationDate: '%s', dtRPCCompletedDate: '%s'"),
                    pTask,
                    m_dtNow.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtRPCCompletedDate.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtExpirationDate.Format(wxT("%H:%M:%S.%l")).c_str()
                );

                m_pHost->DeleteTask(pTask);
            }
        }
    }
}

void CGarbageCollector::RecycleAppVersions()
{
    BSLERRCODE rc;
    std::vector<CAppVersion*> oAppVersions;
    std::vector<CTaskInstance*> oTaskInstances;
    std::vector<CAppVersion*>::iterator iterAppVersions;
    std::vector<CTaskInstance*>::iterator iterTaskInstances;
    CAppVersion* pAppVersion = NULL;
    CTaskInstance* pTaskInstance = NULL;
    CRPCProfile* pRPCProfile = NULL;
    CSyncProfile* pSyncProfile = NULL;
    wxDateTime dtExpirationDate = wxDateTime((time_t)0);
    wxDateTime dtRPCCompletedDate = wxDateTime((time_t)0);
    wxUint32 uiInterval = 0;
    bool bTaskInstanceFound = false;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyStateUpdateInterval, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    rc = m_pHost->FindRPCProfile(CLASSINFO(CRPCSyncState)->GetClassName(), &pRPCProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pRPCProfile) return;

    uiInterval = pSyncProfile->GetValue();
    if (!uiInterval) return;

    dtRPCCompletedDate = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();

    rc = m_pHost->EnumerateAppVersions(oAppVersions);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateTaskInstances(oTaskInstances);
    if (BSLERR_SUCCESS != rc) return;

    for (iterAppVersions = oAppVersions.begin(); iterAppVersions != oAppVersions.end(); ++iterAppVersions)
    {
        pAppVersion = *iterAppVersions;

        // An item is deemed expired if it wasn't refreshed the last time the synchronize
        // RPC was called.
        //
        dtExpirationDate =
            pAppVersion->GetLastModifiedTime() +
            wxTimeSpan(0, 0, uiInterval, 0) +
            wxTimeSpan(0, 0, 0, 250);

        if ((m_dtNow > dtExpirationDate) && (dtRPCCompletedDate > dtExpirationDate))
        {
            // Sanity Check: Make sure their are no task instances that refer to this app version
            bTaskInstanceFound = false;
            for (iterTaskInstances = oTaskInstances.begin(); iterTaskInstances != oTaskInstances.end(); ++iterTaskInstances)
            {
                pTaskInstance = *iterTaskInstances;
                if (pTaskInstance->GetAppVersionHandle() == pAppVersion->GetAppVersionHandle())
                {
                    bTaskInstanceFound = true;
                }
            }

            if (!bTaskInstanceFound)
            {
                wxLogTrace(wxT("Function Status"),
                    wxT("CGarbageCollector::RecycleAppVersions - Recycle '%p', dtNow: '%s', dtExpirationDate: '%s', dtRPCCompletedDate: '%s'"),
                    pAppVersion,
                    m_dtNow.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtRPCCompletedDate.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtExpirationDate.Format(wxT("%H:%M:%S.%l")).c_str()
                );

                m_pHost->DeleteAppVersion(pAppVersion);
            }
        }
    }
}

void CGarbageCollector::RecycleApps()
{
    BSLERRCODE rc;
    std::vector<CApp*> oApps;
    std::vector<CAppVersion*> oAppVersions;
    std::vector<CTask*> oTasks;
    std::vector<CTaskInstance*> oTaskInstances;
    std::vector<CApp*>::iterator iterApps;
    std::vector<CAppVersion*>::iterator iterAppVersions;
    std::vector<CTask*>::iterator iterTasks;
    std::vector<CTaskInstance*>::iterator iterTaskInstances;
    CApp* pApp = NULL;
    CAppVersion* pAppVersion = NULL;
    CTask* pTask = NULL;
    CTaskInstance* pTaskInstance = NULL;
    CRPCProfile* pRPCProfile = NULL;
    CSyncProfile* pSyncProfile = NULL;
    wxDateTime dtExpirationDate = wxDateTime((time_t)0);
    wxDateTime dtRPCCompletedDate = wxDateTime((time_t)0);
    wxUint32 uiInterval = 0;
    bool bAppVersionFound = false;
    bool bTaskFound = false;
    bool bTaskInstanceFound = false;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyStateUpdateInterval, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    rc = m_pHost->FindRPCProfile(CLASSINFO(CRPCSyncState)->GetClassName(), &pRPCProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pRPCProfile) return;

    uiInterval = pSyncProfile->GetValue();
    if (!uiInterval) return;

    dtRPCCompletedDate = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();

    rc = m_pHost->EnumerateApps(oApps);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateAppVersions(oAppVersions);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateTasks(oTasks);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateTaskInstances(oTaskInstances);
    if (BSLERR_SUCCESS != rc) return;

    for (iterApps = oApps.begin(); iterApps != oApps.end(); ++iterApps)
    {
        pApp = *iterApps;

        // An item is deemed expired if it wasn't refreshed the last time the synchronize
        // RPC was called.
        //
        dtExpirationDate =
            pApp->GetLastModifiedTime() +
            wxTimeSpan(0, 0, uiInterval, 0) +
            wxTimeSpan(0, 0, 0, 250);

        if ((m_dtNow > dtExpirationDate) && (dtRPCCompletedDate > dtExpirationDate))
        {
            // Sanity Check: Make sure that no task instances refer to this app
            bTaskInstanceFound = false;
            for (iterTaskInstances = oTaskInstances.begin(); iterTaskInstances != oTaskInstances.end(); ++iterTaskInstances)
            {
                pTaskInstance = *iterTaskInstances;
                if (pTaskInstance->GetAppHandle() == pApp->GetAppHandle())
                {
                    bTaskInstanceFound = true;
                }
            }

            // Sanity Check: Make sure that no tasks refer to this app
            bTaskFound = false;
            for (iterTasks = oTasks.begin(); iterTasks != oTasks.end(); ++iterTasks)
            {
                pTask = *iterTasks;
                if (pTask->GetAppHandle() == pApp->GetAppHandle())
                {
                    bTaskFound = true;
                }
            }

            // Sanity Check: Make sure that no app versions refer to this app
            bAppVersionFound = false;
            for (iterAppVersions = oAppVersions.begin(); iterAppVersions != oAppVersions.end(); ++iterAppVersions)
            {
                pAppVersion = *iterAppVersions;
                if (pAppVersion->GetAppHandle() == pApp->GetAppHandle())
                {
                    bAppVersionFound = true;
                }
            }

            if (!bTaskInstanceFound && !bTaskFound && !bAppVersionFound)
            {
                wxLogTrace(wxT("Function Status"),
                    wxT("CGarbageCollector::RecycleApps - Recycle '%p', dtNow: '%s', dtExpirationDate: '%s', dtRPCCompletedDate: '%s'"),
                    pApp,
                    m_dtNow.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtRPCCompletedDate.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtExpirationDate.Format(wxT("%H:%M:%S.%l")).c_str()
                );

                m_pHost->DeleteApp(pApp);
            }
        }
    }
}

void CGarbageCollector::RecycleProjects()
{
    BSLERRCODE rc;
    std::vector<CProject*> oProjects;
    std::vector<CApp*> oApps;
    std::vector<CAppVersion*> oAppVersions;
    std::vector<CTask*> oTasks;
    std::vector<CTaskInstance*> oTaskInstances;
    std::vector<CProject*>::iterator iterProjects;
    std::vector<CApp*>::iterator iterApps;
    std::vector<CAppVersion*>::iterator iterAppVersions;
    std::vector<CTask*>::iterator iterTasks;
    std::vector<CTaskInstance*>::iterator iterTaskInstances;
    CProject* pProject = NULL;
    CApp* pApp = NULL;
    CAppVersion* pAppVersion = NULL;
    CTask* pTask = NULL;
    CTaskInstance* pTaskInstance = NULL;
    CRPCProfile* pRPCProfile = NULL;
    CSyncProfile* pSyncProfile = NULL;
    wxDateTime dtExpirationDate = wxDateTime((time_t)0);
    wxDateTime dtRPCCompletedDate = wxDateTime((time_t)0);
    wxUint32 uiInterval = 0;
    bool bAppFound = false;
    bool bAppVersionFound = false;
    bool bTaskFound = false;
    bool bTaskInstanceFound = false;

    rc = m_pHost->FindSyncProfile(CBSLClient::AutoSyncPropertyStateUpdateInterval, &pSyncProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pSyncProfile) return;

    rc = m_pHost->FindRPCProfile(CLASSINFO(CRPCSyncState)->GetClassName(), &pRPCProfile);
    if (BSLERR_SUCCESS != rc) return;
    if (!pRPCProfile) return;

    uiInterval = pSyncProfile->GetValue();
    if (!uiInterval) return;

    dtRPCCompletedDate = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();

    rc = m_pHost->EnumerateProjects(oProjects);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateApps(oApps);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateAppVersions(oAppVersions);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateTasks(oTasks);
    if (BSLERR_SUCCESS != rc) return;

    rc = m_pHost->EnumerateTaskInstances(oTaskInstances);
    if (BSLERR_SUCCESS != rc) return;

    for (iterProjects = oProjects.begin(); iterProjects != oProjects.end(); ++iterProjects)
    {
        pProject = *iterProjects;

        // An item is deemed expired if it wasn't refreshed the last time the synchronize
        // RPC was called.
        //
        dtExpirationDate =
            pProject->GetLastModifiedTime() +
            wxTimeSpan(0, 0, uiInterval, 0) +
            wxTimeSpan(0, 0, 0, 250);

        if ((m_dtNow > dtExpirationDate) && (dtRPCCompletedDate > dtExpirationDate))
        {
            // Sanity Check: Make sure that no task instances refer to this project
            bTaskInstanceFound = false;
            for (iterTaskInstances = oTaskInstances.begin(); iterTaskInstances != oTaskInstances.end(); ++iterTaskInstances)
            {
                pTaskInstance = *iterTaskInstances;
                if (pTaskInstance->GetProjectHandle() == pProject->GetProjectHandle())
                {
                    bTaskInstanceFound = true;
                }
            }

            // Sanity Check: Make sure that no tasks refer to this project
            bTaskFound = false;
            for (iterTasks = oTasks.begin(); iterTasks != oTasks.end(); ++iterTasks)
            {
                pTask = *iterTasks;
                if (pTask->GetProjectHandle() == pProject->GetProjectHandle())
                {
                    bTaskFound = true;
                }
            }

            // Sanity Check: Make sure that no app versions refer to this project
            bAppVersionFound = false;
            for (iterAppVersions = oAppVersions.begin(); iterAppVersions != oAppVersions.end(); ++iterAppVersions)
            {
                pAppVersion = *iterAppVersions;
                if (pAppVersion->GetProjectHandle() == pProject->GetProjectHandle())
                {
                    bAppVersionFound = true;
                }
            }

            // Sanity Check: Make sure that no apps refer to this project
            bAppFound = false;
            for (iterApps = oApps.begin(); iterApps != oApps.end(); ++iterApps)
            {
                pApp = *iterApps;
                if (pApp->GetProjectHandle() == pProject->GetProjectHandle())
                {
                    bAppFound = true;
                }
            }

            if (!bTaskInstanceFound && !bTaskFound && !bAppVersionFound && !bAppFound)
            {
                wxLogTrace(wxT("Function Status"),
                    wxT("CGarbageCollector::RecycleProjects - Recycle '%p', dtNow: '%s', dtExpirationDate: '%s', dtRPCCompletedDate: '%s'"),
                    pApp,
                    m_dtNow.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtRPCCompletedDate.Format(wxT("%H:%M:%S.%l")).c_str(),
                    dtExpirationDate.Format(wxT("%H:%M:%S.%l")).c_str()
                );

                m_pHost->DeleteProject(pProject);
            }
        }
    }
}
