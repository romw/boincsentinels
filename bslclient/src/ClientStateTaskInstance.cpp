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

IMPLEMENT_DYNAMIC_CLASS(CTaskInstance, CBSLTaskInstance);

CTaskInstance::CTaskInstance() :
CObject(),
CBSLTaskInstance()
{
    CObjectLocker olLock(this);
}

CTaskInstance::CTaskInstance(const CBSLTaskInstance& bslTaskInstance) :
CObject(),
CBSLTaskInstance()
{
    CObjectLocker olLock(this);

    *this = bslTaskInstance;
    SetTaskInstanceHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLTASKINSTANCE_ADD, GetHostHandle(), GetTaskInstanceHandle());
}

CTaskInstance::~CTaskInstance()
{
    CObjectLocker olLock(this);
}

CTaskInstance& CTaskInstance::operator= (const CBSLTaskInstance& bslTaskInstance)
{
    CObjectLocker olLock(this);

    CBSLTaskInstance::operator=(bslTaskInstance);
    SetTaskInstanceHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLTASKINSTANCE_UPDATE, GetHostHandle(), GetTaskInstanceHandle());

    return *this;
}

bool CTaskInstance::operator== (const CBSLTaskInstance& bslTaskInstance)
{
    CObjectLocker olLock(this);
    return CBSLTaskInstance::operator==(bslTaskInstance);
}

bool CTaskInstance::operator!= (const CBSLTaskInstance& bslTaskInstance)
{
    CObjectLocker olLock(this);
    return CBSLTaskInstance::operator!=(bslTaskInstance);
}

void CTaskInstance::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLTASKINSTANCE_DELETE, GetHostHandle(), GetTaskInstanceHandle());
    CObject::Dispose(this);
}

BSLERRCODE CTaskInstance::Update(CBSLTaskInstance& bslTaskInstance)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLTaskInstance::operator!=(bslTaskInstance))
    {
        CBSLTaskInstance::operator=(bslTaskInstance);
        GetEventManager()->FireEvent(wxEVT_BSLTASKINSTANCE_UPDATE, GetHostHandle(), GetTaskInstanceHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CTaskInstanceIndex::CTaskInstanceIndex()
{
    m_pTaskInstance = NULL;
    m_uiProjectHash = 0;
    m_uiNameHash = 0;
}

CTaskInstanceIndex::CTaskInstanceIndex(CTaskInstance* pTaskInstance)
{
    m_pTaskInstance = pTaskInstance;
    m_uiProjectHash = pTaskInstance->GetProjectHash();
    m_uiNameHash = pTaskInstance->GetNameHash();
}

CTaskInstanceIndex::CTaskInstanceIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash)
{
    m_pTaskInstance = NULL;
    m_uiProjectHash = uiProjectHash;
    m_uiNameHash = uiNameHash;
}

CTaskInstanceIndex::~CTaskInstanceIndex()
{
}

bool CTaskInstanceIndex::operator== (const CTaskInstanceIndex& entry)
{
    if (m_uiProjectHash != entry.m_uiProjectHash) return false;
    if (m_uiNameHash != entry.m_uiNameHash) return false;
    return true;
}

bool CTaskInstanceIndex::operator!= (const CTaskInstanceIndex& entry)
{
    return !(*this == entry);
}

CTaskInstance* CTaskInstanceIndex::GetRecord()
{
    return m_pTaskInstance;
}

wxUint32 CTaskInstanceIndex::GetProjectHash()
{
    return m_uiProjectHash;
}

wxUint32 CTaskInstanceIndex::GetNameHash()
{
    return m_uiNameHash;
}
