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

IMPLEMENT_DYNAMIC_CLASS(CSyncProfile, wxObject);

CSyncProfile::CSyncProfile() :
CObject(),
wxObject()
{
    CObjectLocker olLock(this);
}

CSyncProfile::CSyncProfile(CBSLClient::AUTOSYNCPROPERTY uiID) :
CObject(),
wxObject()
{
    CObjectLocker olLock(this);
    m_uiID = uiID;
    m_uiValue = 0;
    m_dtLastQueuedTime = wxDateTime((time_t)0);
}

CSyncProfile::~CSyncProfile()
{
    CObjectLocker olLock(this);
}

void CSyncProfile::Dispose()
{
    CObjectLocker olLock(this);
    CObject::Dispose(this);
}

wxUint32 CSyncProfile::GetDatabaseKey()
{
    CObjectLocker olLock(this);
    return m_uiID;
}

wxUint32 CSyncProfile::GetValue()
{
    CObjectLocker olLock(this);
    return m_uiValue;
}

CBSLClient::AUTOSYNCPROPERTY CSyncProfile::GetID()
{
    CObjectLocker olLock(this);
    return m_uiID;
}

wxDateTime CSyncProfile::GetLastQueuedTime()
{
    CObjectLocker olLock(this);
    return m_dtLastQueuedTime;
}

void CSyncProfile::SetValue(wxUint32 uiValue)
{
    CObjectLocker olLock(this);
    m_uiValue = uiValue;
}

void CSyncProfile::SetLastQueuedTime(wxDateTime dtLastQueuedTime)
{
    CObjectLocker olLock(this);
    m_dtLastQueuedTime = dtLastQueuedTime;
}
