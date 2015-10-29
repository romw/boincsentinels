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

IMPLEMENT_DYNAMIC_CLASS(CNotification, CBSLNotification);

CNotification::CNotification() :
CObject(),
CBSLNotification()
{
    CObjectLocker olLock(this);
}

CNotification::CNotification(const CBSLNotification& bslNotification) :
CObject(),
CBSLNotification()
{
    CObjectLocker olLock(this);

    *this = bslNotification;
    SetNotificationHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLNOTIFICATION_ADD, GetHostHandle(), GetNotificationHandle());
}

CNotification::~CNotification()
{
    CObjectLocker olLock(this);
}

CNotification& CNotification::operator= (const CBSLNotification& bslNotification)
{
    CObjectLocker olLock(this);

    CBSLNotification::operator=(bslNotification);
    SetNotificationHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLNOTIFICATION_UPDATE, GetHostHandle(), GetNotificationHandle());

    return *this;
}

bool CNotification::operator== (const CBSLNotification& bslNotification)
{
    CObjectLocker olLock(this);
    return CBSLNotification::operator==(bslNotification);
}

bool CNotification::operator!= (const CBSLNotification& bslNotification)
{
    CObjectLocker olLock(this);
    return CBSLNotification::operator!=(bslNotification);
}

void CNotification::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLNOTIFICATION_DELETE, GetHostHandle(), GetNotificationHandle());
    CObject::Dispose(this);
}

BSLERRCODE CNotification::Update(CBSLNotification& bslNotification)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLNotification::operator!=(bslNotification))
    {
        CBSLNotification::operator=(bslNotification);
        GetEventManager()->FireEvent(wxEVT_BSLNOTIFICATION_UPDATE, GetHostHandle(), GetNotificationHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CNotificationIndex::CNotificationIndex()
{
    m_pNotification = NULL;
    m_iSeqNo = 0;
}

CNotificationIndex::CNotificationIndex(CNotification* pNotification)
{
    m_pNotification = pNotification;
    m_iSeqNo = pNotification->GetSequenceNumber();
}

CNotificationIndex::CNotificationIndex(wxInt32 iSeqNo)
{
    m_pNotification = NULL;
    m_iSeqNo = iSeqNo;
}

CNotificationIndex::~CNotificationIndex()
{
}

bool CNotificationIndex::operator== (const CNotificationIndex& entry)
{
    if (m_iSeqNo != entry.m_iSeqNo) return false;
    return true;
}

bool CNotificationIndex::operator!= (const CNotificationIndex& entry)
{
    return !(*this == entry);
}

CNotification* CNotificationIndex::GetRecord()
{
    return m_pNotification;
}

wxInt32 CNotificationIndex::GetSequenceNumber()
{
    return m_iSeqNo;
}

