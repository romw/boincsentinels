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
#include "EventManagerTypes.h"
#include "EventManager.h"
#include "RPCTypes.h"
#include "StateManagerJob.h"
#include "StateManagerThread.h"
#include "StateManager.h"

CStateManagerThread::CStateManagerThread(CStateManager* pStateManager) :
wxThread(wxTHREAD_JOINABLE)
{
    m_pStateManager = pStateManager;
    m_pEventManager = GetEventManager();
    m_pState = GetState();

    Create(64*1024);
}

wxThread::ExitCode CStateManagerThread::Entry()
{
    wxStopWatch swPoll;

    while (!TestDestroy())
    {
        ProcessEventQueue();

        if (swPoll.Time() >= 1000)
        {
            swPoll.Start(0);

            // Refresh the 'now' variable for the various poll routines.
            m_dtNow = wxDateTime::UNow();

            ProcessUpdateRPCs();
            ProcessCollectGarbage();
            ProcessRecycleBin();
        }

        wxThread::Sleep(100);
    }

    return 0;
}

void CStateManagerThread::OnExit()
{
}

void CStateManagerThread::ProcessCollectGarbage()
{
    std::vector<BSLHOST> oHosts;

    if (BSLERR_SUCCESS == m_pState->EnumerateHosts(oHosts))
    {
        for (std::vector<BSLHOST>::iterator i = oHosts.begin(); i != oHosts.end(); i++)
        {
            CStateManagerJob oCollectGarbageJob(CStateManagerJob::CommandCollectGarbage, CStateManagerJob::RPCUnknown, *i);
            m_pStateManager->PushWorkerJob(CStateManagerJob::PriorityNormal, oCollectGarbageJob);
        }
    }
}

void CStateManagerThread::ProcessEventQueue()
{
    std::vector<CStateManagerEntry> oQueue;
    CStateManagerEntry oEntry;

    if (m_pEventManager->GetStateManagerQueue(oQueue))
    {
        for (std::vector<CStateManagerEntry>::iterator i = oQueue.begin(); i != oQueue.end(); i++)
        {
            oEntry = (CStateManagerEntry)*i;

            // Check for a host add pending event, if found begin the connection
            // process.
            if (wxEVT_BSLHOST_CONNECTPENDING == oEntry.GetEventType())
            {
                CStateManagerJob oConnectJob(CStateManagerJob::CommandConnect, CStateManagerJob::RPCUnknown, oEntry.GetHost());
                m_pStateManager->PushWorkerJob(CStateManagerJob::PriorityAboveNormal, oConnectJob);
            }

            // Check for a host delete pending event, if found begin the disconnection
            // process.
            if (wxEVT_BSLHOST_DISCONNECTPENDING == oEntry.GetEventType())
            {
                CStateManagerJob oDisconnectJob(CStateManagerJob::CommandDisconnect, CStateManagerJob::RPCUnknown, oEntry.GetHost());
                m_pStateManager->PushWorkerJob(CStateManagerJob::PriorityNormal, oDisconnectJob);
            }
        }
    }
}

void CStateManagerThread::ProcessRecycleBin()
{
    m_pStateManager->PurgeRecycleBin(m_dtNow);
}

void CStateManagerThread::ProcessUpdateRPCs()
{
    std::vector<BSLHOST> oHosts;
    std::vector<CSyncProfile*> oSyncProperties;
    CHost* pHost = NULL;
    CSyncProfile* pSyncProfile = NULL;

    if (BSLERR_SUCCESS == m_pState->EnumerateHosts(oHosts))
    {
        for (std::vector<BSLHOST>::iterator i = oHosts.begin(); i != oHosts.end(); i++)
        {
            pHost = (CHost*)*i;
            if (BSLERR_SUCCESS == pHost->EnumerateSyncProfiles(oSyncProperties))
            {
                for (std::vector<CSyncProfile*>::iterator j = oSyncProperties.begin(); j != oSyncProperties.end(); j++)
                {
                    pSyncProfile = (CSyncProfile*)*j;

                    // A refresh Interval of 0 means don't refresh
                    if (0 == pSyncProfile->GetValue()) continue;

                    switch(pSyncProfile->GetID())
                    {
                        case CBSLClient::AutoSyncPropertyHostUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncHost)->GetClassName(), CStateManagerJob::RPCHostUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyHostStatusUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncHostStatus)->GetClassName(), CStateManagerJob::RPCHostStatusUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyMessagesUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncMessages)->GetClassName(), CStateManagerJob::RPCMessagesUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyNotificationsUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncNotifications)->GetClassName(), CStateManagerJob::RPCNotificationsUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyProjectListUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncProjectList)->GetClassName(), CStateManagerJob::RPCProjectListUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyProjectsUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncProjects)->GetClassName(), CStateManagerJob::RPCProjectsUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyProjectStatisticsUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncProjectStatistics)->GetClassName(), CStateManagerJob::RPCProjectStatisticsUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyTaskInstancesUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncTaskInstances)->GetClassName(), CStateManagerJob::RPCTaskInstancesUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyTransfersUpdateInterval:
                            UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncTransfers)->GetClassName(), CStateManagerJob::RPCTransfersUpdate);
                            break;
                        case CBSLClient::AutoSyncPropertyStateUpdateInterval:
                            if (pHost->IsForceRefreshEnabled())
                            {
                                ForceUpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncState)->GetClassName(), CStateManagerJob::RPCStateUpdate);
                            }
                            else
                            {
                                UpdateRPCStatus(pHost, pSyncProfile, CLASSINFO(CRPCSyncState)->GetClassName(), CStateManagerJob::RPCStateUpdate);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void CStateManagerThread::ForceUpdateRPCStatus(CHost* pHost, CSyncProfile* pSyncProfile, const wxChar* pszRPCName, CStateManagerJob::RPC RPC)
{
    CRPCProfile* pRPCProfile = NULL;

    pHost->FindRPCProfile(pszRPCName, &pRPCProfile);

    CStateManagerJob oRPCJob(CStateManagerJob::CommandRPC, RPC, pHost->GetHostHandle());
    m_pStateManager->PushWorkerJob(CStateManagerJob::PriorityNormal, oRPCJob);

    if (CStateManagerJob::RPCStateUpdate == RPC) pHost->ForceRefresh(false);
    if (pSyncProfile) pSyncProfile->SetLastQueuedTime(m_dtNow);
}

void CStateManagerThread::UpdateRPCStatus(CHost* pHost, CSyncProfile* pSyncProfile, const wxChar* pszRPCName, CStateManagerJob::RPC RPC)
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CRPCProfile* pRPCProfile = NULL;

    // If we find the RPC Profile, perform the additional checks, otherwise just queue up the RPC
    // so we can start to profile it.
    rc = pHost->FindRPCProfile(pszRPCName, &pRPCProfile);
    if (BSLERR_SUCCESS == rc)
    {
        wxDateTime dtLastQueuedTime = pSyncProfile->GetLastQueuedTime();
        wxDateTime dtLastExecutionCompletedTime = pRPCProfile->GetLastRequestTime() + pRPCProfile->GetTotalDuration();
        wxDateTime dtLastExecutionBufferTime = dtLastExecutionCompletedTime + wxTimeSpan(0,0, pSyncProfile->GetValue(), 0);

        // Has the previous execution completed?
        if (!(dtLastQueuedTime <= dtLastExecutionCompletedTime)) return;

        // Only execute another RPC if the current time is greater than the end time of the last RPC plus the refresh interval
        if (!(m_dtNow > dtLastExecutionBufferTime)) return;
    }

    if (CStateManagerJob::RPCMessagesUpdate == RPC)
    {
        CStateManagerJob oRPCJob(CStateManagerJob::CommandRPC, RPC, pHost->GetHostHandle(), pHost->GetLastMessageSequenceNumber());
        m_pStateManager->PushWorkerJob(CStateManagerJob::PriorityNormal, oRPCJob);
    }
    else if (CStateManagerJob::RPCNotificationsUpdate == RPC)
    {
        CStateManagerJob oRPCJob(CStateManagerJob::CommandRPC, RPC, pHost->GetHostHandle(), pHost->GetLastNotificationSequenceNumber());
        m_pStateManager->PushWorkerJob(CStateManagerJob::PriorityNormal, oRPCJob);
    }
    else
    {
        CStateManagerJob oRPCJob(CStateManagerJob::CommandRPC, RPC, pHost->GetHostHandle());
        m_pStateManager->PushWorkerJob(CStateManagerJob::PriorityNormal, oRPCJob);
    }

    pSyncProfile->SetLastQueuedTime(m_dtNow);
}
