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

IMPLEMENT_DYNAMIC_CLASS(CBSLMessageEventData, wxObject);

CBSLMessageEventData::CBSLMessageEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hMessage = NULL;
    m_hProject = NULL;
}

CBSLMessageEventData::CBSLMessageEventData(const CBSLMessageEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hMessage = data.m_hMessage;
    m_hProject = data.m_hProject;
}

CBSLMessageEventData::~CBSLMessageEventData()
{
}

BSLHOST CBSLMessageEventData::GetHostHandle()
{
    return m_hHost;
}

BSLMESSAGE CBSLMessageEventData::GetMessageHandle()
{
    return m_hMessage;
}

BSLPROJECT CBSLMessageEventData::GetProjectHandle()
{
    return m_hProject;
}

void CBSLMessageEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLMessageEventData::SetMessageHandle(BSLMESSAGE hMessage)
{
    m_hMessage = hMessage;
}

void CBSLMessageEventData::SetProjectHandle(BSLPROJECT hProject)
{
    m_hProject = hProject;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLMessageAuditLogEventData, CBSLMessageEventData);

CBSLMessageAuditLogEventData::CBSLMessageAuditLogEventData() :
    CBSLMessageEventData(), CBSLAuditLogEventData()
{
}

CBSLMessageAuditLogEventData::CBSLMessageAuditLogEventData(const CBSLMessageAuditLogEventData& data) :
    CBSLMessageEventData(data), CBSLAuditLogEventData(data)
{
}

CBSLMessageAuditLogEventData::~CBSLMessageAuditLogEventData()
{
}
