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

IMPLEMENT_DYNAMIC_CLASS(CProjectListItem, CBSLProjectListItem);

CProjectListItem::CProjectListItem() :
CObject(),
CBSLProjectListItem()
{
    CObjectLocker olLock(this);
}

CProjectListItem::CProjectListItem(const CBSLProjectListItem& bslProjectListItem) :
CObject(),
CBSLProjectListItem()
{
    CObjectLocker olLock(this);

    *this = bslProjectListItem;
    SetProjectListItemHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLPROJECTLISTITEM_ADD, GetHostHandle(), GetProjectListItemHandle());
}

CProjectListItem::~CProjectListItem()
{
    CObjectLocker olLock(this);
}

CProjectListItem& CProjectListItem::operator= (const CBSLProjectListItem& bslProjectListItem)
{
    CObjectLocker olLock(this);

    CBSLProjectListItem::operator=(bslProjectListItem);
    SetProjectListItemHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLPROJECTLISTITEM_UPDATE, GetHostHandle(), GetProjectListItemHandle());

    return *this;
}

bool CProjectListItem::operator== (const CBSLProjectListItem& bslProjectListItem)
{
    CObjectLocker olLock(this);
    return CBSLProjectListItem::operator==(bslProjectListItem);
}

bool CProjectListItem::operator!= (const CBSLProjectListItem& bslProjectListItem)
{
    CObjectLocker olLock(this);
    return CBSLProjectListItem::operator!=(bslProjectListItem);
}

void CProjectListItem::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLPROJECTLISTITEM_DELETE, GetHostHandle(), GetProjectListItemHandle());
    CObject::Dispose(this);
}

BSLERRCODE CProjectListItem::Update(CBSLProjectListItem& bslProjectListItem)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLProjectListItem::operator!=(bslProjectListItem))
    {
        CBSLProjectListItem::operator=(bslProjectListItem);
        GetEventManager()->FireEvent(wxEVT_BSLPROJECTLISTITEM_UPDATE, GetHostHandle(), GetProjectListItemHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CProjectListItemIndex::CProjectListItemIndex()
{
    m_pProjectListItem = NULL;
    m_uiMasterURLHash = 0;
}

CProjectListItemIndex::CProjectListItemIndex(CProjectListItem* pProjectListItem)
{
    m_pProjectListItem = pProjectListItem;
    m_uiMasterURLHash = pProjectListItem->GetMasterURLHash();
}

CProjectListItemIndex::CProjectListItemIndex(wxUint32 uiMasterURLHash)
{
    m_pProjectListItem = NULL;
    m_uiMasterURLHash = uiMasterURLHash;
}

CProjectListItemIndex::~CProjectListItemIndex()
{
}

bool CProjectListItemIndex::operator== (const CProjectListItemIndex& entry)
{
    if (m_uiMasterURLHash != entry.m_uiMasterURLHash) return false;
    return true;
}

bool CProjectListItemIndex::operator!= (const CProjectListItemIndex& entry)
{
    return !(*this == entry);
}

CProjectListItem* CProjectListItemIndex::GetRecord()
{
    return m_pProjectListItem;
}

wxUint32 CProjectListItemIndex::GetMasterURLHash()
{
    return m_uiMasterURLHash;
}
