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
#include "StateManagerJob.h"
#include "StateWorkerThread.h"
#include "StateManager.h"
#include "GarbageCollector.h"
#include "RPCTypes.h"
#include "RPCManager.h"

CStateWorkerThread::CStateWorkerThread(CStateManager* pStateManager) :
wxThread(wxTHREAD_JOINABLE)
{
    m_pStateManager = pStateManager;
    Create(64*1024);
}

wxThread::ExitCode CStateWorkerThread::Entry()
{
    CStateManagerJob oJob;
    bool bAutoBreak = false;

    while (!bAutoBreak)
    {
        m_pStateManager->WaitWorkerJob();
        oJob = m_pStateManager->PopWorkerJob();

        switch (oJob.GetCommandType())
        {
            case CStateManagerJob::CommandStart:
                break;
            case CStateManagerJob::CommandStop:
                bAutoBreak = true;
                break;
            case CStateManagerJob::CommandCollectGarbage:
                OnCollectGarbage(oJob);
                break;
            case CStateManagerJob::CommandConnect:
                OnHostConnect(oJob);
                break;
            case CStateManagerJob::CommandDisconnect:
                OnHostDisconnect(oJob);
                break;
            case CStateManagerJob::CommandRPC:
                switch(oJob.GetRPCType())
                {
                    case CStateManagerJob::RPCHostUpdate:
                        OnRPCHostUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCHostStatusUpdate:
                        OnRPCHostStatusUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCMessagesUpdate:
                        OnRPCMessagesUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCNotificationsUpdate:
                        OnRPCNotificationsUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCProjectListUpdate:
                        OnRPCProjectListUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCProjectStatisticsUpdate:
                        OnRPCProjectStatisticsUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCProjectsUpdate:
                        OnRPCProjectsUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCStateUpdate:
                        OnRPCStateUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCTaskInstancesUpdate:
                        OnRPCTaskInstancesUpdate(oJob);
                        break;
                    case CStateManagerJob::RPCTransfersUpdate:
                        OnRPCTransfersUpdate(oJob);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    return 0;
}

void CStateWorkerThread::OnExit()
{
}

void CStateWorkerThread::OnCollectGarbage(CStateManagerJob& oJob)
{
    CGarbageCollector gcCollector;
    CHost* pHost = wxDynamicCast(oJob.GetHostHandle(), CHost);

    gcCollector.Execute(pHost);
}

void CStateWorkerThread::OnHostConnect(CStateManagerJob& oJob)
{
    CHost* pHost = wxDynamicCast(oJob.GetHostHandle(), CHost);
    GetRPCManager()->OnConnect(pHost);
}

void CStateWorkerThread::OnHostDisconnect(CStateManagerJob& oJob)
{
    CHost* pHost = wxDynamicCast(oJob.GetHostHandle(), CHost);
    GetRPCManager()->OnDisconnect(pHost);
}

void CStateWorkerThread::OnRPCHostUpdate(CStateManagerJob& oJob)
{
    CBSLHost bslHost;
    GetState()->GetHost(
        oJob.GetHostHandle(),
        &bslHost,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCHostStatusUpdate(CStateManagerJob& oJob)
{
    CBSLHostStatus bslHostStatus;
    GetState()->GetHostStatus(
        oJob.GetHostHandle(),
        &bslHostStatus,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCMessagesUpdate(CStateManagerJob& oJob)
{
    std::vector<BSLMESSAGE> oMessages;
    GetState()->EnumerateMessages(
        oJob.GetHostHandle(),
        oJob.GetSequenceNumber(),
        oMessages,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCNotificationsUpdate(CStateManagerJob& oJob)
{
    std::vector<BSLNOTIFICATION> oNotifications;
    GetState()->EnumerateNotifications(
        oJob.GetHostHandle(),
        oJob.GetSequenceNumber(),
        oNotifications,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCProjectListUpdate(CStateManagerJob& oJob)
{
    std::vector<BSLPROJECTLISTITEM> oProjectListItems;
    GetState()->EnumerateProjectList(
        oJob.GetHostHandle(),
        oProjectListItems,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCProjectStatisticsUpdate(CStateManagerJob& oJob)
{
    std::vector<BSLPROJECTSTATISTIC> oProjectStatistics;
    GetState()->EnumerateProjectStatistics(
        oJob.GetHostHandle(),
        NULL,
        oProjectStatistics,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCProjectsUpdate(CStateManagerJob& oJob)
{
    std::vector<BSLPROJECT> oProjects;
    GetState()->EnumerateProjects(
        oJob.GetHostHandle(),
        oProjects,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCStateUpdate(CStateManagerJob& oJob)
{
    GetState()->UpdateHostState(
        oJob.GetHostHandle(),
        true
    );
}

void CStateWorkerThread::OnRPCTaskInstancesUpdate(CStateManagerJob& oJob)
{
    std::vector<BSLTASKINSTANCE> oTaskInstances;
    GetState()->EnumerateTaskInstances(
        oJob.GetHostHandle(),
        oTaskInstances,
        true,
        true
    );
}

void CStateWorkerThread::OnRPCTransfersUpdate(CStateManagerJob& oJob)
{
    std::vector<BSLTRANSFER> oTransfers;
    GetState()->EnumerateTransfers(
        oJob.GetHostHandle(),
        oTransfers,
        true,
        true
    );
}
