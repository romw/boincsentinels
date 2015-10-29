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
#include "EventManager.h"

IMPLEMENT_DYNAMIC_CLASS(CProjectLink, CBSLProjectLink);

CProjectLink::CProjectLink() :
CObject(),
CBSLProjectLink()
{
    CObjectLocker olLock(this);
}

CProjectLink::CProjectLink(const CBSLProjectLink& bslProjectLink) :
CObject(),
CBSLProjectLink()
{
    CObjectLocker olLock(this);
    *this = bslProjectLink;
}

CProjectLink::~CProjectLink()
{
    CObjectLocker olLock(this);
}

CProjectLink& CProjectLink::operator= (const CBSLProjectLink& bslProjectLink)
{
    CObjectLocker olLock(this);

    CBSLProjectLink::operator=(bslProjectLink);
    UpdateLastModified();

    return *this;
}

bool CProjectLink::operator== (const CBSLProjectLink& bslProjectLink)
{
    CObjectLocker olLock(this);
    return CBSLProjectLink::operator==(bslProjectLink);
}

bool CProjectLink::operator!= (const CBSLProjectLink& bslProjectLink)
{
    CObjectLocker olLock(this);
    return CBSLProjectLink::operator!=(bslProjectLink);
}

BSLERRCODE CProjectLink::Update(CBSLProjectLink& bslProjectLink)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLProjectLink::operator!=(bslProjectLink))
    {
        CBSLProjectLink::operator=(bslProjectLink);

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}
