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

IMPLEMENT_DYNAMIC_CLASS(CBSLAppVersionEventData, wxObject);

CBSLAppVersionEventData::CBSLAppVersionEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hProject = NULL;
    m_hApp = NULL;
    m_hAppVersion = NULL;
}

CBSLAppVersionEventData::CBSLAppVersionEventData(const CBSLAppVersionEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hProject = data.m_hProject;
    m_hApp = data.m_hApp;
    m_hAppVersion = data.m_hAppVersion;
}

CBSLAppVersionEventData::~CBSLAppVersionEventData()
{
}

BSLHOST CBSLAppVersionEventData::GetHostHandle()
{
    return m_hHost;
}

BSLPROJECT CBSLAppVersionEventData::GetProjectHandle()
{
    return m_hProject;
}

BSLAPP CBSLAppVersionEventData::GetAppHandle()
{
    return m_hApp;
}

BSLAPPVERSION CBSLAppVersionEventData::GetAppVersionHandle()
{
    return m_hAppVersion;
}

void CBSLAppVersionEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLAppVersionEventData::SetProjectHandle(BSLPROJECT hProject)
{
    m_hProject = hProject;
}

void CBSLAppVersionEventData::SetAppHandle(BSLAPP hApp)
{
    m_hApp = hApp;
}

void CBSLAppVersionEventData::SetAppVersionHandle(BSLAPPVERSION hAppVersion)
{
    m_hAppVersion = hAppVersion;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLAppVersionAuditLogEventData, CBSLAppVersionEventData);

CBSLAppVersionAuditLogEventData::CBSLAppVersionAuditLogEventData() :
    CBSLAppVersionEventData(), CBSLAuditLogEventData()
{
}

CBSLAppVersionAuditLogEventData::CBSLAppVersionAuditLogEventData(const CBSLAppVersionAuditLogEventData& data) :
    CBSLAppVersionEventData(data), CBSLAuditLogEventData(data)
{
}

CBSLAppVersionAuditLogEventData::~CBSLAppVersionAuditLogEventData()
{
}
