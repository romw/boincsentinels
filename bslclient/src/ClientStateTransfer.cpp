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

IMPLEMENT_DYNAMIC_CLASS(CTransfer, CBSLTransfer);

CTransfer::CTransfer() :
CObject(),
CBSLTransfer()
{
    CObjectLocker olLock(this);
}

CTransfer::CTransfer(const CBSLTransfer& bslTransfer) :
CObject(),
CBSLTransfer()
{
    CObjectLocker olLock(this);

    *this = bslTransfer;
    SetTransferHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLTRANSFER_ADD, GetHostHandle(), GetTransferHandle());
}

CTransfer::~CTransfer()
{
    CObjectLocker olLock(this);
}

CTransfer& CTransfer::operator= (const CBSLTransfer& bslTransfer)
{
    CObjectLocker olLock(this);

    CBSLTransfer::operator=(bslTransfer);
    SetTransferHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLTRANSFER_UPDATE, GetHostHandle(), GetTransferHandle());

    return *this;
}

bool CTransfer::operator== (const CBSLTransfer& bslTransfer)
{
    CObjectLocker olLock(this);
    return CBSLTransfer::operator==(bslTransfer);
}

bool CTransfer::operator!= (const CBSLTransfer& bslTransfer)
{
    CObjectLocker olLock(this);
    return CBSLTransfer::operator!=(bslTransfer);
}

void CTransfer::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLTRANSFER_DELETE, GetHostHandle(), GetTransferHandle());
    CObject::Dispose(this);
}

BSLERRCODE CTransfer::Update(CBSLTransfer& bslTransfer)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLTransfer::operator!=(bslTransfer))
    {
        CBSLTransfer::operator=(bslTransfer);
        GetEventManager()->FireEvent(wxEVT_BSLTRANSFER_UPDATE, GetHostHandle(), GetTransferHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CTransferIndex::CTransferIndex()
{
    m_pTransfer = NULL;
    m_uiProjectHash = 0;
    m_uiNameHash = 0;
}

CTransferIndex::CTransferIndex(CTransfer* pTransfer)
{
    m_pTransfer = pTransfer;
    m_uiProjectHash = pTransfer->GetProjectHash();
    m_uiNameHash = pTransfer->GetNameHash();
}

CTransferIndex::CTransferIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash)
{
    m_pTransfer = NULL;
    m_uiProjectHash = uiProjectHash;
    m_uiNameHash = uiNameHash;
}

CTransferIndex::~CTransferIndex()
{
}

bool CTransferIndex::operator== (const CTransferIndex& entry)
{
    if (m_uiProjectHash != entry.m_uiProjectHash) return false;
    if (m_uiNameHash != entry.m_uiNameHash) return false;
    return true;
}

bool CTransferIndex::operator!= (const CTransferIndex& entry)
{
    return !(*this == entry);
}

CTransfer* CTransferIndex::GetRecord()
{
    return m_pTransfer;
}

wxUint32 CTransferIndex::GetProjectHash()
{
    return m_uiProjectHash;
}

wxUint32 CTransferIndex::GetNameHash()
{
    return m_uiNameHash;
}
