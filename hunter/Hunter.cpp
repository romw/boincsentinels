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
#include "bslclient/bslClient.h"
#include "ConfigManager.h"
#include "SkinManager.h"
#include "LogManager.h"
#include "Interface.h"
#include "Hunter.h"

IMPLEMENT_APP(CBOINCGUIApp);
IMPLEMENT_DYNAMIC_CLASS(CBOINCGUIApp, wxApp);

bool CBOINCGUIApp::OnInit()
{
    // Setup variables with default values
    //
    m_pConfig = NULL;
    m_pSkin = NULL;
    m_pLog = NULL;
    m_pState = NULL;
    m_pInterface = NULL;

    // Command line parsing is done in wxApp::OnInit()
    //
    if (!wxApp::OnInit())
    {
        return false;
    }

    // Enable known image types
    //
    wxInitAllImageHandlers();

    // Reduce overhead of Idle Events
    //
    wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);

    // Note: JAWS for Windows will only speak the context-sensitive
    //   help if you use this help provider:
    //
    wxHelpProvider::Set(new wxHelpControllerHelpProvider());

    // Setup application and company information
    //
    SetAppName(wxT("BOINC-Sentinels-Hunter"));
    SetVendorName(wxT("ROMWNET"));

    // Initialize the configuration storage module
    //
    m_pConfig = new CConfigManager();
    wxASSERT(m_pConfig);
    wxConfigBase::Set(m_pConfig);

    // Enable Logging and Trace Masks
    //
    m_pLog = new CLogManager();
    wxASSERT(m_pLog);
    wxLog::SetActiveTarget(m_pLog);

    m_pLog->AddTraceMask(wxT("Function Start/End"));
    m_pLog->AddTraceMask(wxT("Function Status"));
    m_pLog->AddTraceMask(wxT("Function Performance"));

    // Enable Skinning
    //
    m_pSkin = new CSkinManager();
    wxASSERT(m_pSkin);

    // Initialize the state of the system
    //
    m_pState = new CBSLClient();
    wxASSERT(m_pState);
    m_pState->OnInit();

    // Initialize the Interface
    //
    m_pInterface = new CInterface();
    wxASSERT(m_pInterface);
    m_pInterface->Show();

    SetTopWindow(m_pInterface);
    
    // Switch the current directory to the BOINC Data directory
    //
#if !defined(__WXDEBUG__) || defined(__WXMAC__)
    if (!GetBOINCDataDirectory().IsEmpty())
    {
        wxSetWorkingDirectory(GetBOINCDataDirectory());
    }
#endif

    return true;
}

int CBOINCGUIApp::OnExit()
{
    if (m_pState)
    {
        m_pState->OnExit();
        delete m_pState;
        m_pState = NULL;
    }

    if (m_pSkin)
    {
        delete m_pSkin;
        m_pSkin = NULL;
    }

    return wxApp::OnExit();
}

///
/// Pass the command line parameters and descriptions to wxWidgets for displaying.
///
void CBOINCGUIApp::OnInitCmdLine(wxCmdLineParser &parser)
{
    wxApp::OnInitCmdLine(parser);
    static const wxCmdLineEntryDesc cmdLineDesc[] =
    {
    { wxCMD_LINE_NONE } //DON'T forget this line!!
    };
    parser.SetDesc(cmdLineDesc);
}

///
/// Parse command line parameters.
///
bool CBOINCGUIApp::OnCmdLineParsed(wxCmdLineParser &parser)
{
    // Give default processing (-?, --help and --verbose) the chance to do something.
    wxApp::OnCmdLineParsed(parser);
    return true;
}

wxString CBOINCGUIApp::GetBOINCDataDirectory()
{
    wxASSERT(m_pState);
    
    wxString strDataDirectory = wxEmptyString;
    m_pState->GetBOINCDataDirectory(strDataDirectory);
    return strDataDirectory;
}

wxString CBOINCGUIApp::GetBOINCRootDirectory()
{
    wxASSERT(m_pState);
    
    wxString strInstallDirectory = wxEmptyString;
    m_pState->GetBOINCDataDirectory(strInstallDirectory);
    return strInstallDirectory;
}
