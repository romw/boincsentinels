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

#ifndef _STATEMANAGERTHREAD_H_
#define _STATEMANAGERTHREAD_H_

class CStateManager;

class CStateManagerThread: public wxThread
{
public:
    CStateManagerThread(CStateManager* pStateManager);

    virtual wxThread::ExitCode Entry();
    virtual void OnExit();

private:
    CStateManager* m_pStateManager;
    CEventManager* m_pEventManager;
    CClientState*  m_pState;

    wxDateTime     m_dtNow;

    void ProcessCollectGarbage();
    void ProcessEventQueue();
    void ProcessRecycleBin();
    void ProcessUpdateRPCs();

    void ForceUpdateRPCStatus(CHost* pHost, CSyncProfile* pSyncProfile, const wxChar* pszRPCName, CStateManagerJob::RPC RPC);
    void UpdateRPCStatus(CHost* pHost, CSyncProfile* pSyncProfile, const wxChar* pszRPCName, CStateManagerJob::RPC RPC);
};

#endif

///
/// \}

