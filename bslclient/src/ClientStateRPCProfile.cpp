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

IMPLEMENT_DYNAMIC_CLASS(CRPCProfile, wxObject);

CRPCProfile::CRPCProfile() :
CObject(),
wxObject()
{
    CObjectLocker olLock(this);

    m_ullExecutionCount = 0;
    m_ullTotalBytesSent = 0;
    m_ullTotalBytesReceived = 0;
    m_ullRequestSize = 0;
    m_ullResponseSize = 0;
}

CRPCProfile::CRPCProfile(wxString strRPCName) :
CObject(),
wxObject()
{
    CObjectLocker olLock(this);

    m_strRPCName = strRPCName;
    m_dtLastRequestTime = wxDateTime((time_t)0);

    m_ullExecutionCount = 0;
    m_ullTotalBytesSent = 0;
    m_ullTotalBytesReceived = 0;

    // Populate the RPC request and response size values with some reasonable defaults
    m_ullRequestSize = 512;
    m_ullResponseSize = 1024;
}

CRPCProfile::~CRPCProfile()
{
    CObjectLocker olLock(this);
}

void CRPCProfile::Dispose()
{
    CObjectLocker olLock(this);
    CObject::Dispose(this);
}

wxString CRPCProfile::GetRPCName()
{
    CObjectLocker olLock(this);
    return m_strRPCName;
}

wxUint64 CRPCProfile::GetExecutionCount()
{
    CObjectLocker olLock(this);
    return m_ullExecutionCount;
}

wxDateTime CRPCProfile::GetLastRequestTime()
{
    CObjectLocker olLock(this);
    return m_dtLastRequestTime;
}

wxTimeSpan CRPCProfile::GetRequestDuration()
{
    CObjectLocker olLock(this);
    return m_tsRequestDuration;
}

wxUint64 CRPCProfile::GetRequestSize()
{
    CObjectLocker olLock(this);
    return m_ullRequestSize;
}

wxTimeSpan CRPCProfile::GetResponseDuration()
{
    CObjectLocker olLock(this);
    return m_tsResponseDuration;
}

wxUint64 CRPCProfile::GetResponseSize()
{
    CObjectLocker olLock(this);
    return m_ullResponseSize;
}

wxTimeSpan CRPCProfile::GetParseDuration()
{
    CObjectLocker olLock(this);
    return m_tsParseDuration;
}

wxTimeSpan CRPCProfile::GetTotalDuration()
{
    CObjectLocker olLock(this);
    return m_tsTotalDuration;
}

wxUint64 CRPCProfile::GetTotalBytesSent()
{
    CObjectLocker olLock(this);
    return m_ullTotalBytesSent;
}

wxUint64 CRPCProfile::GetTotalBytesReceived()
{
    CObjectLocker olLock(this);
    return m_ullTotalBytesReceived;
}

void CRPCProfile::Update(
    wxDateTime& dtLastRequestTime,
    wxUint64& ullRequestSize,
    wxUint64& ullResponseSize
)
{
    CObjectLocker olLock(this);
    m_ullExecutionCount++;
    m_dtLastRequestTime = dtLastRequestTime;
    m_ullRequestSize = ullRequestSize;
    m_ullResponseSize = ullResponseSize;
    m_ullTotalBytesSent += ullRequestSize;
    m_ullTotalBytesReceived += ullResponseSize;
}

#ifdef __WXDEBUG__
void CRPCProfile::Update(
    wxDateTime& dtLastRequestTime,
    wxTimeSpan& tsRequestDuration,
    wxUint64& ullRequestSize,
    wxTimeSpan& tsResponseDuration,
    wxUint64& ullResponseSize,
    wxTimeSpan& tsParseDuration,
    wxTimeSpan& tsTotalDuration
)
{
    CObjectLocker olLock(this);
    m_ullExecutionCount++;
    m_dtLastRequestTime = dtLastRequestTime;
    m_tsRequestDuration = tsRequestDuration;
    m_ullRequestSize = ullRequestSize;
    m_tsResponseDuration = tsResponseDuration;
    m_ullResponseSize = ullResponseSize;
    m_tsParseDuration = tsParseDuration;
    m_tsTotalDuration = tsTotalDuration;
    m_ullTotalBytesSent += ullRequestSize;
    m_ullTotalBytesReceived += ullResponseSize;
}
#endif
