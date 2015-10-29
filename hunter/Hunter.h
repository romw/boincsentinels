// BOINC Sentinels.
// https://projects.romwnet.org/boincsentinels
// Copyright (C) 2009-2014 Rom Walton
//
// BOINC Monitor is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC Monitor.  If not, see <http://www.gnu.org/licenses/>.
//

///
/// @defgroup BOINValkyrie BOINC-Sentinels-Hunter
/// The BOINC Sentinels Hunter User Interface
/// @{

#ifndef _BOINCGUIAPP_H_
#define _BOINCGUIAPP_H_

class CConfigManager;
class CSkinManager;
class CLogManager;
class CBSLClient;
class CInterface;

class CBOINCGUIApp: public wxApp
{
    DECLARE_DYNAMIC_CLASS(CBOINCGUIApp)

protected:
    void OnInitCmdLine(wxCmdLineParser &parser);
    bool OnCmdLineParsed(wxCmdLineParser &parser);

    CConfigManager* m_pConfig;
    CSkinManager* m_pSkin;
    CLogManager* m_pLog;
    CBSLClient* m_pState;
    CInterface* m_pInterface;

    bool m_bAccessibilityEnabled;

public:

    bool OnInit();
    int OnExit();

    wxString GetBOINCDataDirectory();
    wxString GetBOINCRootDirectory();

    CConfigManager* GetConfigManager()
    {
        return m_pConfig;
    }
    CSkinManager* GetSkinManager()
    {
        return m_pSkin;
    }
    CBSLClient* GetState()
    {
        return m_pState;
    }
    CInterface* GetInterface()
    {
        return m_pInterface;
    }
    bool IsAccessibilityEnabled()
    {
        return m_bAccessibilityEnabled;
    }

};

DECLARE_APP(CBOINCGUIApp)

#endif

///
/// \}
