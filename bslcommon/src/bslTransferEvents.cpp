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

IMPLEMENT_DYNAMIC_CLASS(CBSLTransferEventData, wxObject);

CBSLTransferEventData::CBSLTransferEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hProject = NULL;
    m_hTransfer = NULL;
}

CBSLTransferEventData::CBSLTransferEventData(const CBSLTransferEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hProject = data.m_hProject;
    m_hTransfer = data.m_hTransfer;
}

CBSLTransferEventData::~CBSLTransferEventData()
{
}

BSLHOST CBSLTransferEventData::GetHostHandle()
{
    return m_hHost;
}

BSLPROJECT CBSLTransferEventData::GetProjectHandle()
{
    return m_hProject;
}

BSLTRANSFER CBSLTransferEventData::GetTransferHandle()
{
    return m_hTransfer;
}

void CBSLTransferEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLTransferEventData::SetProjectHandle(BSLPROJECT hProject)
{
    m_hProject = hProject;
}

void CBSLTransferEventData::SetTransferHandle(BSLTRANSFER hTransfer)
{
    m_hTransfer = hTransfer;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLTransferAuditLogEventData, CBSLTransferEventData);

CBSLTransferAuditLogEventData::CBSLTransferAuditLogEventData() :
    CBSLTransferEventData(), CBSLAuditLogEventData()
{
}

CBSLTransferAuditLogEventData::CBSLTransferAuditLogEventData(const CBSLTransferAuditLogEventData& data) :
    CBSLTransferEventData(data), CBSLAuditLogEventData(data)
{
}

CBSLTransferAuditLogEventData::~CBSLTransferAuditLogEventData()
{
}
