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
#include "StateManagerThread.h"
#include "StateWorkerThread.h"
#include "StateManager.h"

#ifdef __WXDEBUG__
#define RECYCLEBIN_DELAY    9999                                            // Keep around in memory so that things can
                                                                            // be debugged without causing a crash
#else
#define RECYCLEBIN_DELAY    10
#endif


IMPLEMENT_DYNAMIC_CLASS(CStateManager, wxObject);

CStateManager::CStateManager() :
wxObject()
{
    unsigned int i = 0;
    unsigned int iThreadCount = wxThread::GetCPUCount() + 1;
    CStateWorkerThread* pWorkerThread = NULL;

    m_pWorkerThreadPoolLocker = new wxCriticalSection();
    wxASSERT(m_pWorkerThreadPoolLocker);

    m_pJobQueueTrigger = new wxSemaphore();
    wxASSERT(m_pJobQueueTrigger);

    m_pJobQueueLocker = new wxCriticalSection();
    wxASSERT(m_pJobQueueLocker);

    m_pRecycleBinLocker = new wxCriticalSection();
    wxASSERT(m_pRecycleBinLocker);

    m_pStateManagerThread = new CStateManagerThread(this);
    wxASSERT(m_pStateManagerThread);
    m_pStateManagerThread->Run();

    m_pWorkerThreadPoolLocker->Enter();

    // Create and start the threads for the thread pool
    for ( i = 0; i < iThreadCount; i++ )
    {
        pWorkerThread = new CStateWorkerThread(this);
        wxASSERT(pWorkerThread);

        m_WorkerThreadPool.push_back(pWorkerThread);
        pWorkerThread->Run();
    }

    // Send start jobs to each of the threads
    for ( i = 0; i < iThreadCount; i++ )
    {
        PushWorkerJob(
            CStateManagerJob::PriorityNormal,
            CStateManagerJob(CStateManagerJob::CommandStart)
        );
    }

    m_pWorkerThreadPoolLocker->Leave();
}

CStateManager::~CStateManager()
{
    unsigned int uiIndex = 0;
    unsigned int uiCount = 0;
    unsigned int uiTimeout = 0;
    CStateWorkerThread* pThread = NULL;

    m_pWorkerThreadPoolLocker->Enter();

    uiCount = (unsigned int)m_WorkerThreadPool.size();

    // Stop threads
    for (uiIndex = 0; uiIndex < uiCount; uiIndex++)
    {
        PushWorkerJob(CStateManagerJob::PriorityHigh, CStateManagerJob(CStateManagerJob::CommandStop));
    }

    // Wait and delete each thread
    for (uiIndex = 0; uiIndex < uiCount; uiIndex++)
    {
        uiTimeout = 0;
        pThread = m_WorkerThreadPool[uiIndex];
        while (pThread->IsAlive())
        {
            wxThread::Sleep(100);
            uiTimeout += 100;
            if (1000 <= uiTimeout)
            {
                pThread->Kill();
                break;
            }
        }
        delete pThread;
    }
    m_WorkerThreadPool.clear();

    m_pWorkerThreadPoolLocker->Leave();

    // Shutdown manager thread
    m_pStateManagerThread->Delete();
    delete m_pStateManagerThread;
    m_pStateManagerThread = NULL;

    // Clean up the job queue
    m_JobQueue.clear();

    // Clean up the recycle bin
    m_pRecycleBinLocker->Enter();

    std::vector<CObject*>::iterator iter;
    for (iter = m_RecycleBinDatabase.begin(); iter != m_RecycleBinDatabase.end(); iter++)
    {
        CObject* pEntry = (CObject*) *iter;
        delete pEntry;
    }
    m_RecycleBinDatabase.clear();

    m_pRecycleBinLocker->Leave();

    // Clean up the rest of the thread sync objects
    delete m_pJobQueueLocker;
    m_pJobQueueLocker = NULL;

    delete m_pJobQueueTrigger;
    m_pJobQueueTrigger = NULL;

    delete m_pWorkerThreadPoolLocker;
    m_pWorkerThreadPoolLocker = NULL;

    delete m_pRecycleBinLocker;
    m_pRecycleBinLocker = NULL;
}

CStateManagerJob CStateManager::PopWorkerJob()
{
    CStateManagerJob oJob;

    m_pJobQueueLocker->Enter();

    oJob = (m_JobQueue.begin())->second;
    m_JobQueue.erase(m_JobQueue.begin());

    m_pJobQueueLocker->Leave();

    return oJob;
}

bool CStateManager::PushWorkerJob(CStateManagerJob::PRIORITY iPriority, CStateManagerJob oJob)
{
    m_pJobQueueLocker->Enter();
    m_JobQueue.insert(std::pair<CStateManagerJob::PRIORITY, CStateManagerJob>(iPriority, oJob));
    m_pJobQueueTrigger->Post();
    m_pJobQueueLocker->Leave();
    return true;
}

void CStateManager::WaitWorkerJob()
{
    m_pJobQueueTrigger->Wait();
}

void CStateManager::PurgeRecycleBin(wxDateTime& dtNow)
{
    wxTimeSpan tsElapsedTime;

    m_pRecycleBinLocker->Enter();

    std::vector<CObject*>::iterator iter = m_RecycleBinDatabase.begin();
    while (iter != m_RecycleBinDatabase.end())
    {
        CObject* pEntry = (CObject*) *iter;

        tsElapsedTime = dtNow - pEntry->GetLastModifiedTime();
        if (RECYCLEBIN_DELAY <= tsElapsedTime.GetSeconds())
        {
            delete pEntry;
            iter = m_RecycleBinDatabase.erase(iter);
        }
        else
        {
            iter++;
        }
    }

    m_pRecycleBinLocker->Leave();
}

void CStateManager::Recycle(CObject* pObject)
{
    m_pRecycleBinLocker->Enter();

    m_RecycleBinDatabase.push_back(pObject);

    m_pRecycleBinLocker->Leave();
}
