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

#ifndef _CONFIGMANAGER_H_
#define _CONFIGMANAGER_H_

class CConfigManager: public wxConfig
{
    DECLARE_NO_COPY_CLASS(CConfigManager)

public:
    CConfigManager();

    bool DeleteConfigGroup(wxString strComponent, wxString strSubComponent);

    wxString DeterminePath(wxString strComponent, wxString strSubComponent);

    bool EnumerateGroups(wxString strComponent, wxString strSubComponent, wxSortedArrayString* pstrGroups);

    bool GetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName,
        long dwDefaultValue, long* pdwValue);

    bool GetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName,
        wxString strDefaultValue, wxString* pstrValue);

    bool SetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName, long dwValue);

    bool SetConfigValue(wxString strComponent, wxString strSubComponent, wxString strValueName, wxString strValue);
};

#endif
