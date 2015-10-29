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

IMPLEMENT_DYNAMIC_CLASS(CAppVersion, CBSLAppVersion);

CAppVersion::CAppVersion() :
CObject(),
CBSLAppVersion()
{
    CObjectLocker olLock(this);
}

CAppVersion::CAppVersion(const CBSLAppVersion& bslAppVersion) :
CObject(),
CBSLAppVersion()
{
    CObjectLocker olLock(this);

    *this = bslAppVersion;
    SetAppVersionHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLAPPVERSION_ADD, GetHostHandle(), GetAppVersionHandle());
}

CAppVersion::~CAppVersion()
{
    CObjectLocker olLock(this);
}

CAppVersion& CAppVersion::operator= (const CBSLAppVersion& bslAppVersion)
{
    CObjectLocker olLock(this);

    CBSLAppVersion::operator=(bslAppVersion);
    SetAppVersionHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLAPPVERSION_UPDATE, GetHostHandle(), GetAppVersionHandle());

    return *this;
}

bool CAppVersion::operator== (const CBSLAppVersion& bslAppVersion)
{
    CObjectLocker olLock(this);
    return CBSLAppVersion::operator==(bslAppVersion);
}

bool CAppVersion::operator!= (const CBSLAppVersion& bslAppVersion)
{
    CObjectLocker olLock(this);
    return CBSLAppVersion::operator!=(bslAppVersion);
}

void CAppVersion::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLAPPVERSION_DELETE, GetHostHandle(), GetAppVersionHandle());
    CObject::Dispose(this);
}

BSLERRCODE CAppVersion::Update(CBSLAppVersion& bslAppVersion)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLAppVersion::operator!=(bslAppVersion))
    {
        CBSLAppVersion::operator=(bslAppVersion);
        GetEventManager()->FireEvent(wxEVT_BSLAPPVERSION_UPDATE, GetHostHandle(), GetAppVersionHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CAppVersionIndex::CAppVersionIndex()
{
    m_pAppVersion = NULL;
    m_uiProjectHash = 0;
    m_uiVersion = 0;
    m_uiPlanClassHash = 0;
    m_uiNameHash = 0;
}

CAppVersionIndex::CAppVersionIndex(CAppVersion* pAppVersion)
{
    m_pAppVersion = pAppVersion;
    m_uiProjectHash = pAppVersion->GetProjectHash();
    m_uiVersion = pAppVersion->GetVersion();
    m_uiPlanClassHash = pAppVersion->GetPlanClassHash();
    m_uiNameHash = pAppVersion->GetNameHash();
}

CAppVersionIndex::CAppVersionIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash, wxUint32 uiVersion, wxUint32 uiPlanClassHash)
{
    m_pAppVersion = NULL;
    m_uiProjectHash = uiProjectHash;
    m_uiVersion = uiVersion;
    m_uiPlanClassHash = uiPlanClassHash;
    m_uiNameHash = uiNameHash;
}

CAppVersionIndex::~CAppVersionIndex()
{
}

bool CAppVersionIndex::operator== (const CAppVersionIndex& entry)
{
    if (m_uiProjectHash != entry.m_uiProjectHash) return false;
    if (m_uiVersion != entry.m_uiVersion) return false;
    if (m_uiPlanClassHash != entry.m_uiPlanClassHash) return false;
    if (m_uiNameHash != entry.m_uiNameHash) return false;
    return true;
}

bool CAppVersionIndex::operator!= (const CAppVersionIndex& entry)
{
    return !(*this == entry);
}

CAppVersion* CAppVersionIndex::GetRecord()
{
    return m_pAppVersion;
}

wxUint32 CAppVersionIndex::GetProjectHash()
{
    return m_uiProjectHash;
}

wxUint32 CAppVersionIndex::GetVersion()
{
    return m_uiVersion;
}

wxUint32 CAppVersionIndex::GetPlanClassHash()
{
    return m_uiPlanClassHash;
}

wxUint32 CAppVersionIndex::GetNameHash()
{
    return m_uiNameHash;
}
