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

#ifndef _STATEWORKERTHREAD_H_
#define _STATEWORKERTHREAD_H_

class CStateManager;
class CStateManagerJob;

class CStateWorkerThread: public wxThread
{
public:
    CStateWorkerThread(CStateManager* pStateManager);

    virtual wxThread::ExitCode Entry();
    virtual void OnExit();

private:
    CStateManager* m_pStateManager;

    void OnCollectGarbage(CStateManagerJob& oJob);
    void OnHostConnect(CStateManagerJob& oJob);
    void OnHostDisconnect(CStateManagerJob& oJob);
    void OnRPCHostUpdate(CStateManagerJob& oJob);
    void OnRPCHostStatusUpdate(CStateManagerJob& oJob);
    void OnRPCMessagesUpdate(CStateManagerJob& oJob);
    void OnRPCNotificationsUpdate(CStateManagerJob& oJob);
    void OnRPCProjectListUpdate(CStateManagerJob& oJob);
    void OnRPCProjectStatisticsUpdate(CStateManagerJob& oJob);
    void OnRPCProjectsUpdate(CStateManagerJob& oJob);
    void OnRPCStateUpdate(CStateManagerJob& oJob);
    void OnRPCTaskInstancesUpdate(CStateManagerJob& oJob);
    void OnRPCTransfersUpdate(CStateManagerJob& oJob);
};

#endif

///
/// \}

