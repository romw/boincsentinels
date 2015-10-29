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

IMPLEMENT_DYNAMIC_CLASS(CBSLTaskEventData, wxObject);

CBSLTaskEventData::CBSLTaskEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hProject = NULL;
    m_hApp = NULL;
    m_hTask = NULL;
}

CBSLTaskEventData::CBSLTaskEventData(const CBSLTaskEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hProject = data.m_hProject;
    m_hApp = data.m_hApp;
    m_hTask = data.m_hTask;
}

CBSLTaskEventData::~CBSLTaskEventData()
{
}

BSLHOST CBSLTaskEventData::GetHostHandle()
{
    return m_hHost;
}

BSLPROJECT CBSLTaskEventData::GetProjectHandle()
{
    return m_hProject;
}

BSLAPP CBSLTaskEventData::GetAppHandle()
{
    return m_hApp;
}

BSLTASK CBSLTaskEventData::GetTaskHandle()
{
    return m_hTask;
}

void CBSLTaskEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLTaskEventData::SetProjectHandle(BSLPROJECT hProject)
{
    m_hProject = hProject;
}

void CBSLTaskEventData::SetAppHandle(BSLAPP hApp)
{
    m_hApp = hApp;
}

void CBSLTaskEventData::SetTaskHandle(BSLTASK hTask)
{
    m_hTask = hTask;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLTaskAuditLogEventData, CBSLTaskEventData);

CBSLTaskAuditLogEventData::CBSLTaskAuditLogEventData() :
    CBSLTaskEventData(), CBSLAuditLogEventData()
{
}

CBSLTaskAuditLogEventData::CBSLTaskAuditLogEventData(const CBSLTaskAuditLogEventData& data) :
    CBSLTaskEventData(data), CBSLAuditLogEventData(data)
{
}

CBSLTaskAuditLogEventData::~CBSLTaskAuditLogEventData()
{
}
