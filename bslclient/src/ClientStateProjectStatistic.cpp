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

IMPLEMENT_DYNAMIC_CLASS(CProjectStatistic, CBSLProjectStatistic);

CProjectStatistic::CProjectStatistic() :
CObject(),
CBSLProjectStatistic()
{
    CObjectLocker olLock(this);
}

CProjectStatistic::CProjectStatistic(const CBSLProjectStatistic& bslProjectStatistic) :
CObject(),
CBSLProjectStatistic()
{
    CObjectLocker olLock(this);

    *this = bslProjectStatistic;
    SetProjectStatisticHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLPROJECTSTATISTIC_ADD, GetHostHandle(), GetProjectStatisticHandle());
}

CProjectStatistic::~CProjectStatistic()
{
    CObjectLocker olLock(this);
}

CProjectStatistic& CProjectStatistic::operator= (const CBSLProjectStatistic& bslProjectStatistic)
{
    CObjectLocker olLock(this);

    CBSLProjectStatistic::operator=(bslProjectStatistic);
    SetProjectStatisticHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLPROJECTSTATISTIC_UPDATE, GetHostHandle(), GetProjectStatisticHandle());

    return *this;
}

bool CProjectStatistic::operator== (const CBSLProjectStatistic& bslProjectStatistic)
{
    CObjectLocker olLock(this);
    return CBSLProjectStatistic::operator==(bslProjectStatistic);
}

bool CProjectStatistic::operator!= (const CBSLProjectStatistic& bslProjectStatistic)
{
    CObjectLocker olLock(this);
    return CBSLProjectStatistic::operator!=(bslProjectStatistic);
}

void CProjectStatistic::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLPROJECTSTATISTIC_DELETE, GetHostHandle(), GetProjectStatisticHandle());
    CObject::Dispose(this);
}

BSLERRCODE CProjectStatistic::Update(CBSLProjectStatistic& bslProjectStatistic)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLProjectStatistic::operator!=(bslProjectStatistic))
    {
        CBSLProjectStatistic::operator=(bslProjectStatistic);
        GetEventManager()->FireEvent(wxEVT_BSLPROJECTSTATISTIC_UPDATE, GetHostHandle(), GetProjectStatisticHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}
