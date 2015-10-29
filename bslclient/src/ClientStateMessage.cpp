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

IMPLEMENT_DYNAMIC_CLASS(CMessage, CBSLMessage);

CMessage::CMessage() :
CObject(),
CBSLMessage()
{
    CObjectLocker olLock(this);
}

CMessage::CMessage(const CBSLMessage& bslMessage) :
CObject(),
CBSLMessage()
{
    CObjectLocker olLock(this);

    *this = bslMessage;
    SetMessageHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLMESSAGE_ADD, GetHostHandle(), GetMessageHandle());
}

CMessage::~CMessage()
{
    CObjectLocker olLock(this);
}

CMessage& CMessage::operator= (const CBSLMessage& bslMessage)
{
    CObjectLocker olLock(this);

    CBSLMessage::operator=(bslMessage);
    SetMessageHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLMESSAGE_UPDATE, GetHostHandle(), GetMessageHandle());

    return *this;
}

bool CMessage::operator== (const CBSLMessage& bslMessage)
{
    CObjectLocker olLock(this);
    return CBSLMessage::operator==(bslMessage);
}

bool CMessage::operator!= (const CBSLMessage& bslMessage)
{
    CObjectLocker olLock(this);
    return CBSLMessage::operator!=(bslMessage);
}

void CMessage::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLMESSAGE_DELETE, GetHostHandle(), GetMessageHandle());
    CObject::Dispose(this);
}

BSLERRCODE CMessage::Update(CBSLMessage& bslMessage)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLMessage::operator!=(bslMessage))
    {
        CBSLMessage::operator=(bslMessage);
        GetEventManager()->FireEvent(wxEVT_BSLMESSAGE_UPDATE, GetHostHandle(), GetMessageHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CMessageIndex::CMessageIndex()
{
    m_pMessage = NULL;
    m_iSeqNo = 0;
}

CMessageIndex::CMessageIndex(CMessage* pMessage)
{
    m_pMessage = pMessage;
    m_iSeqNo = pMessage->GetSequenceNumber();
}

CMessageIndex::CMessageIndex(wxInt32 iSeqNo)
{
    m_pMessage = NULL;
    m_iSeqNo = iSeqNo;
}

CMessageIndex::~CMessageIndex()
{
}

bool CMessageIndex::operator== (const CMessageIndex& entry)
{
    if (m_iSeqNo != entry.m_iSeqNo) return false;
    return true;
}

bool CMessageIndex::operator!= (const CMessageIndex& entry)
{
    return !(*this == entry);
}

CMessage* CMessageIndex::GetRecord()
{
    return m_pMessage;
}

wxInt32 CMessageIndex::GetSequenceNumber()
{
    return m_iSeqNo;
}

