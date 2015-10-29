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

IMPLEMENT_DYNAMIC_CLASS(CBSLProjectStatisticEventData, wxObject);

CBSLProjectStatisticEventData::CBSLProjectStatisticEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hProject = NULL;
    m_hProjectStatistic = NULL;
}

CBSLProjectStatisticEventData::CBSLProjectStatisticEventData(const CBSLProjectStatisticEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hProject = data.m_hProject;
    m_hProjectStatistic = data.m_hProjectStatistic;
}

CBSLProjectStatisticEventData::~CBSLProjectStatisticEventData()
{
}

BSLHOST CBSLProjectStatisticEventData::GetHostHandle()
{
    return m_hHost;
}

BSLPROJECT CBSLProjectStatisticEventData::GetProjectHandle()
{
    return m_hProject;
}

BSLPROJECTSTATISTIC CBSLProjectStatisticEventData::GetProjectStatisticHandle()
{
    return m_hProjectStatistic;
}

void CBSLProjectStatisticEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLProjectStatisticEventData::SetProjectHandle(BSLPROJECT hProject)
{
    m_hProject = hProject;
}

void CBSLProjectStatisticEventData::SetProjectStatisticHandle(BSLPROJECTSTATISTIC hProjectStatistic)
{
    m_hProjectStatistic = hProjectStatistic;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLProjectStatisticAuditLogEventData, CBSLProjectStatisticEventData);

CBSLProjectStatisticAuditLogEventData::CBSLProjectStatisticAuditLogEventData() :
    CBSLProjectStatisticEventData(), CBSLAuditLogEventData()
{
}

CBSLProjectStatisticAuditLogEventData::CBSLProjectStatisticAuditLogEventData(const CBSLProjectStatisticAuditLogEventData& data) :
    CBSLProjectStatisticEventData(data), CBSLAuditLogEventData(data)
{
}

CBSLProjectStatisticAuditLogEventData::~CBSLProjectStatisticAuditLogEventData()
{
}
