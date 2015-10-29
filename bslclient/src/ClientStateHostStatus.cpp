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
#include "ClientState.h"
#include "EventManager.h"
#include "RPCProtocol.h"

IMPLEMENT_DYNAMIC_CLASS(CHostStatus, CBSLHostStatus);

CHostStatus::CHostStatus() :
CObject(),
CBSLHostStatus()
{
    CObjectLocker olLock(this);
}

CHostStatus::~CHostStatus()
{
    CObjectLocker olLock(this);
}

CHostStatus& CHostStatus::operator= (const CBSLHostStatus& bslHostStatus)
{
    CObjectLocker olLock(this);

    CBSLHostStatus::operator=(bslHostStatus);
    SetHostStatusHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLHOSTSTATUS_UPDATE, GetHostHandle(), GetHostStatusHandle());

    return *this;
}

bool CHostStatus::operator== (const CBSLHostStatus& bslHostStatus)
{
    CObjectLocker olLock(this);
    return CBSLHostStatus::operator==(bslHostStatus);
}

bool CHostStatus::operator!= (const CBSLHostStatus& bslHostStatus)
{
    CObjectLocker olLock(this);
    return CBSLHostStatus::operator!=(bslHostStatus);
}

BSLERRCODE CHostStatus::Update(CBSLHostStatus& bslHostStatus)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLHostStatus::operator!=(bslHostStatus))
    {
        CBSLHostStatus::operator=(bslHostStatus);
        GetEventManager()->FireEvent(wxEVT_BSLHOSTSTATUS_UPDATE, GetHostHandle(), GetHostStatusHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}
