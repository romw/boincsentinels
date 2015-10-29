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
#include "bslcommon/bslCommonTypes.h"

IMPLEMENT_DYNAMIC_CLASS(CBSLNotificationEventData, wxObject);

CBSLNotificationEventData::CBSLNotificationEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hNotification = NULL;
    m_hProject = NULL;
}

CBSLNotificationEventData::CBSLNotificationEventData(const CBSLNotificationEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hNotification = data.m_hNotification;
    m_hProject = data.m_hProject;
}

CBSLNotificationEventData::~CBSLNotificationEventData()
{
}

BSLHOST CBSLNotificationEventData::GetHostHandle()
{
    return m_hHost;
}

BSLNOTIFICATION CBSLNotificationEventData::GetNotificationHandle()
{
    return m_hNotification;
}

BSLPROJECT CBSLNotificationEventData::GetProjectHandle()
{
    return m_hProject;
}

void CBSLNotificationEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLNotificationEventData::SetNotificationHandle(BSLNOTIFICATION hNotification)
{
    m_hNotification = hNotification;
}

void CBSLNotificationEventData::SetProjectHandle(BSLPROJECT hProject)
{
    m_hProject = hProject;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLNotificationAuditLogEventData, CBSLNotificationEventData);

CBSLNotificationAuditLogEventData::CBSLNotificationAuditLogEventData() :
    CBSLNotificationEventData(), CBSLAuditLogEventData()
{
}

CBSLNotificationAuditLogEventData::CBSLNotificationAuditLogEventData(const CBSLNotificationAuditLogEventData& data) :
    CBSLNotificationEventData(data), CBSLAuditLogEventData(data)
{
}

CBSLNotificationAuditLogEventData::~CBSLNotificationAuditLogEventData()
{
}
