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
#include "ClientState.h"
#include "EventManager.h"

IMPLEMENT_DYNAMIC_CLASS(CTask, CBSLTask);

CTask::CTask() :
CObject(),
CBSLTask()
{
    CObjectLocker olLock(this);
}

CTask::CTask(const CBSLTask& bslTask) :
CObject(),
CBSLTask()
{
    CObjectLocker olLock(this);

    *this = bslTask;
    SetTaskHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLTASK_ADD, GetHostHandle(), GetTaskHandle());
}

CTask::~CTask()
{
    CObjectLocker olLock(this);
}

CTask& CTask::operator= (const CBSLTask& bslTask)
{
    CObjectLocker olLock(this);

    CBSLTask::operator=(bslTask);
    SetTaskHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLTASK_UPDATE, GetHostHandle(), GetTaskHandle());

    return *this;
}

bool CTask::operator== (const CBSLTask& bslTask)
{
    CObjectLocker olLock(this);
    return CBSLTask::operator==(bslTask);
}

bool CTask::operator!= (const CBSLTask& bslTask)
{
    CObjectLocker olLock(this);
    return CBSLTask::operator!=(bslTask);
}

void CTask::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLTASK_DELETE, GetHostHandle(), GetTaskHandle());
    CObject::Dispose(this);
}

BSLERRCODE CTask::Update(CBSLTask& bslTask)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLTask::operator!=(bslTask))
    {
        CBSLTask::operator=(bslTask);
        GetEventManager()->FireEvent(wxEVT_BSLTASK_UPDATE, GetHostHandle(), GetTaskHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CTaskIndex::CTaskIndex()
{
    m_pTask = NULL;
    m_uiProjectHash = 0;
    m_uiNameHash = 0;
}

CTaskIndex::CTaskIndex(CTask* pTask)
{
    m_pTask = pTask;
    m_uiProjectHash = pTask->GetProjectHash();
    m_uiNameHash = pTask->GetNameHash();
}

CTaskIndex::CTaskIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash)
{
    m_pTask = NULL;
    m_uiProjectHash = uiProjectHash;
    m_uiNameHash = uiNameHash;
}

CTaskIndex::~CTaskIndex()
{
}

bool CTaskIndex::operator== (const CTaskIndex& entry)
{
    if (m_uiProjectHash != entry.m_uiProjectHash) return false;
    if (m_uiNameHash != entry.m_uiNameHash) return false;
    return true;
}

bool CTaskIndex::operator!= (const CTaskIndex& entry)
{
    return !(*this == entry);
}

CTask* CTaskIndex::GetRecord()
{
    return m_pTask;
}

wxUint32 CTaskIndex::GetProjectHash()
{
    return m_uiProjectHash;
}

wxUint32 CTaskIndex::GetNameHash()
{
    return m_uiNameHash;
}
