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
#include "Hunter.h"
#include "ConfigManager.h"

CConfigManager::CConfigManager() :
wxConfig()
{
}

bool CConfigManager::DeleteConfigGroup(wxString strComponent, wxString strSubComponent)
{
    bool rc = false;
    wxString strPath = DeterminePath(strComponent, strSubComponent);

    SetPath(strPath);

    rc = DeleteGroup(strPath);

    SetPath(wxT("/"));

    return rc;
}

wxString CConfigManager::DeterminePath(wxString strComponent, wxString strSubComponent)
{
    wxString strPath;

    strPath = wxT("/");
    if (!strComponent.IsEmpty())
    {
        strPath += strComponent + wxT("/");
        if (!strSubComponent.IsEmpty())
        {
            strPath += strSubComponent + wxT("/");
        }
    }
    return strPath;
}

bool CConfigManager::EnumerateGroups(wxString strComponent, wxString strSubComponent, wxSortedArrayString* pstrGroups)
{
    bool rc = false;
    wxString strPath = DeterminePath(strComponent, strSubComponent);
    wxString strGroup = wxEmptyString;
    long lCookie = 0;

    SetPath(strPath);

    rc = GetFirstGroup(strGroup, lCookie);
    while (rc)
    {
        pstrGroups->Add(strGroup);
        rc = GetNextGroup(strGroup, lCookie);
    }

    SetPath(wxT("/"));

    return (pstrGroups->Count() != 0);
}

bool CConfigManager::GetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue)
{
    bool rc = false;
    wxString strPath = DeterminePath(strComponent, strSubComponent);

    SetPath(strPath);

    rc = Read(strValueName, pdwValue, dwDefaultValue);

    SetPath(wxT("/"));

    return rc;
}

bool CConfigManager::GetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName, wxString strDefaultValue, wxString* pstrValue)
{
    bool rc = false;
    wxString strPath = DeterminePath(strComponent, strSubComponent);

    SetPath(strPath);

    rc = Read(strValueName, pstrValue, strDefaultValue);

    SetPath(wxT("/"));

    return rc;
}

bool CConfigManager::SetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName, long dwValue)
{
    bool rc = false;
    wxString strPath = DeterminePath(strComponent, strSubComponent);

    SetPath(strPath);

    rc = Write(strValueName, dwValue);

    SetPath(wxT("/"));

    return rc;
}

bool CConfigManager::SetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName, wxString strValue)
{
    bool rc = false;
    wxString strPath = DeterminePath(strComponent, strSubComponent);

    SetPath(strPath);

    rc = Write(strValueName, strValue);

    SetPath(wxT("/"));

    return rc;
}

