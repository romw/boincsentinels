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

IMPLEMENT_DYNAMIC_CLASS(CBSLHostStatusEventData, wxObject);

CBSLHostStatusEventData::CBSLHostStatusEventData() :
    wxObject(), CBSLEventData()
{
    m_hHost = NULL;
    m_hHostStatus = NULL;
}

CBSLHostStatusEventData::CBSLHostStatusEventData(const CBSLHostStatusEventData& data) :
    wxObject(data), CBSLEventData(data)
{
    m_hHost = data.m_hHost;
    m_hHostStatus = data.m_hHostStatus;
}

CBSLHostStatusEventData::~CBSLHostStatusEventData()
{
}

BSLHOST CBSLHostStatusEventData::GetHostHandle()
{
    return m_hHost;
}

BSLHOSTSTATUS CBSLHostStatusEventData::GetHostStatusHandle()
{
    return m_hHostStatus;
}

void CBSLHostStatusEventData::SetHostHandle(BSLHOST hHost)
{
    m_hHost = hHost;
}

void CBSLHostStatusEventData::SetHostStatusHandle(BSLHOSTSTATUS hHostStatus)
{
    m_hHostStatus = hHostStatus;
}
