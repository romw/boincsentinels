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

IMPLEMENT_DYNAMIC_CLASS(CApp, CBSLApp);

CApp::CApp() :
CObject(),
CBSLApp()
{
    CObjectLocker olLock(this);
}

CApp::CApp(const CBSLApp& bslApp) :
CObject(),
CBSLApp()
{
    CObjectLocker olLock(this);

    *this = bslApp;
    SetAppHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLAPP_ADD, GetHostHandle(), GetAppHandle());
}

CApp::~CApp()
{
    CObjectLocker olLock(this);
}

CApp& CApp::operator= (const CBSLApp& bslApp)
{
    CObjectLocker olLock(this);

    CBSLApp::operator=(bslApp);
    SetAppHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLAPP_UPDATE, GetHostHandle(), GetAppHandle());

    return *this;
}

bool CApp::operator== (const CBSLApp& bslApp)
{
    CObjectLocker olLock(this);
    return CBSLApp::operator==(bslApp);
}

bool CApp::operator!= (const CBSLApp& bslApp)
{
    CObjectLocker olLock(this);
    return CBSLApp::operator!=(bslApp);
}

void CApp::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLAPP_DELETE, GetHostHandle(), GetAppHandle());
    CObject::Dispose(this);
}

BSLERRCODE CApp::Update(CBSLApp& bslApp)
{
    CObjectLocker olLock(this);

    BSLERRCODE rc = BSLERR_FAILURE;

    if (CBSLApp::operator!=(bslApp))
    {
        CBSLApp::operator=(bslApp);
        GetEventManager()->FireEvent(wxEVT_BSLAPP_UPDATE, GetHostHandle(), GetAppHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

    return rc;
}


CAppIndex::CAppIndex()
{
    m_pApp = NULL;
    m_uiProjectHash = 0;
    m_uiNameHash = 0;
}

CAppIndex::CAppIndex(CApp* pApp)
{
    m_pApp = pApp;
    m_uiProjectHash = pApp->GetProjectHash();
    m_uiNameHash = pApp->GetNameHash();
}

CAppIndex::CAppIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash)
{
    m_pApp = NULL;
    m_uiProjectHash = uiProjectHash;
    m_uiNameHash = uiNameHash;
}

CAppIndex::~CAppIndex()
{
}

bool CAppIndex::operator== (const CAppIndex& entry)
{
    if (m_uiProjectHash != entry.m_uiProjectHash) return false;
    if (m_uiNameHash != entry.m_uiNameHash) return false;
    return true;
}

bool CAppIndex::operator!= (const CAppIndex& entry)
{
    return !(*this == entry);
}

CApp* CAppIndex::GetRecord()
{
    return m_pApp;
}

wxUint32 CAppIndex::GetProjectHash()
{
    return m_uiProjectHash;
}

wxUint32 CAppIndex::GetNameHash()
{
    return m_uiNameHash;
}
