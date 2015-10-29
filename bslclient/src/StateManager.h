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
/// \defgroup StateManager State Manager
/// \{

#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "StateManagerJob.h"

// Forward Declares
class CObject;
class CStateManagerThread;
class CStateWorkerThread;


class CStateManager: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CStateManager)

    friend class CStateManagerThread;
    friend class CStateWorkerThread;

public:
    CStateManager();
    ~CStateManager();

    void Recycle(CObject* pObject);

protected:
    CStateManagerJob PopWorkerJob();
    bool PushWorkerJob(CStateManagerJob::PRIORITY iPriority, CStateManagerJob oJob);
    void WaitWorkerJob();

    void PurgeRecycleBin(wxDateTime& dtNow);

private:
    CStateManagerThread* m_pStateManagerThread;

    std::vector<CStateWorkerThread*> m_WorkerThreadPool;
    wxCriticalSection* m_pWorkerThreadPoolLocker;

    std::multimap<CStateManagerJob::PRIORITY, CStateManagerJob> m_JobQueue;
    wxSemaphore* m_pJobQueueTrigger;
    wxCriticalSection* m_pJobQueueLocker;

    std::vector<CObject*> m_RecycleBinDatabase;
    wxCriticalSection* m_pRecycleBinLocker;
};

#endif

///
/// \}

