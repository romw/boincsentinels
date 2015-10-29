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

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

class CInterface: public wxTaskBarIcon
{
    DECLARE_DYNAMIC_CLASS(CInterface)
    DECLARE_EVENT_TABLE()

public:

    CInterface();
    ~CInterface();

    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnHelp(wxHelpEvent& event);

    void OnIdle(wxIdleEvent& event);
    
private:
    bool GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue);
    bool SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue);

    virtual wxMenu* CreatePopupMenu();
};

#endif

