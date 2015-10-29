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

IMPLEMENT_DYNAMIC_CLASS(CBSLTaskInstanceEventData, wxObject);

CBSLTaskInstanceEventData::CBSLTaskInstanceEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hProject = NULL;
    m_hApp = NULL;
    m_hAppVersion = NULL;
    m_hTask = NULL;
    m_hTaskInstance = NULL;
}

CBSLTaskInstanceEventData::CBSLTaskInstanceEventData(const CBSLTaskInstanceEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hProject = data.m_hProject;
    m_hApp = data.m_hApp;
    m_hAppVersion = data.m_hAppVersion;
    m_hTask = data.m_hTask;
    m_hTaskInstance = data.m_hTaskInstance;
}

CBSLTaskInstanceEventData::~CBSLTaskInstanceEventData()
{
}

BSLHOST CBSLTaskInstanceEventData::GetHostHandle()
{
    return m_hHost;
}

BSLPROJECT CBSLTaskInstanceEventData::GetProjectHandle()
{
    return m_hProject;
}

BSLAPP CBSLTaskInstanceEventData::GetAppHandle()
{
    return m_hApp;
}

BSLAPPVERSION CBSLTaskInstanceEventData::GetAppVersionHandle()
{
    return m_hAppVersion;
}

BSLTASK CBSLTaskInstanceEventData::GetTaskHandle()
{
    return m_hTask;
}

BSLTASKINSTANCE CBSLTaskInstanceEventData::GetTaskInstanceHandle()
{
    return m_hTaskInstance;
}

void CBSLTaskInstanceEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLTaskInstanceEventData::SetProjectHandle(BSLPROJECT hProject)
{
    m_hProject = hProject;
}

void CBSLTaskInstanceEventData::SetAppHandle(BSLAPP hApp)
{
    m_hApp = hApp;
}

void CBSLTaskInstanceEventData::SetAppVersionHandle(BSLAPPVERSION hAppVersion)
{
    m_hAppVersion = hAppVersion;
}

void CBSLTaskInstanceEventData::SetTaskHandle(BSLTASK hTask)
{
    m_hTask = hTask;
}

void CBSLTaskInstanceEventData::SetTaskInstanceHandle(BSLTASKINSTANCE hTaskInstance)
{
    m_hTaskInstance = hTaskInstance;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLTaskInstanceAuditLogEventData, CBSLTaskInstanceEventData);

CBSLTaskInstanceAuditLogEventData::CBSLTaskInstanceAuditLogEventData() :
    CBSLTaskInstanceEventData(), CBSLAuditLogEventData()
{
}

CBSLTaskInstanceAuditLogEventData::CBSLTaskInstanceAuditLogEventData(const CBSLTaskInstanceAuditLogEventData& data) :
    CBSLTaskInstanceEventData(data), CBSLAuditLogEventData(data)
{
}

CBSLTaskInstanceAuditLogEventData::~CBSLTaskInstanceAuditLogEventData()
{
}
