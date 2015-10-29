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


CBSLEventData::CBSLEventData()
{
    m_pData = NULL;
}

CBSLEventData::CBSLEventData(const CBSLEventData& data)
{
    m_pData = data.m_pData;
}

CBSLEventData::~CBSLEventData()
{
}

wxUIntPtr CBSLEventData::GetData()
{
    return m_pData;
}

void CBSLEventData::SetData(wxUIntPtr pData)
{
    m_pData = pData;
}


CBSLAuditLogEventData::CBSLAuditLogEventData()
{
    m_bAdded = false;
    m_bDeleted = false;
    m_bUpdated = false;
}

CBSLAuditLogEventData::CBSLAuditLogEventData(const CBSLAuditLogEventData& data)
{
    m_bAdded = data.m_bAdded;
    m_bDeleted = data.m_bDeleted;
    m_bUpdated = data.m_bUpdated;
}

CBSLAuditLogEventData::~CBSLAuditLogEventData()
{
}

bool CBSLAuditLogEventData::IsAdded()
{
    return m_bAdded;
}

bool CBSLAuditLogEventData::IsDeleted()
{
    return m_bDeleted;
}

bool CBSLAuditLogEventData::IsUpdated()
{
    return m_bUpdated;
}

void CBSLAuditLogEventData::SetAdded(bool bValue)
{
    m_bAdded = bValue;
}

void CBSLAuditLogEventData::SetDeleted(bool bValue)
{
    m_bDeleted = bValue;
}

void CBSLAuditLogEventData::SetUpdated(bool bValue)
{
    m_bUpdated = bValue;
}

