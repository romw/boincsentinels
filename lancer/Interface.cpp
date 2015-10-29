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
#include "bslversion.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Lancer.h"
#include "ConfigManager.h"
#include "SkinManager.h"
#include "Interface.h"


IMPLEMENT_DYNAMIC_CLASS(CInterface, wxTaskBarIcon);

BEGIN_EVENT_TABLE(CInterface, wxTaskBarIcon)
    EVT_MENU(wxID_EXIT, CInterface::OnExit)
    EVT_MENU(wxID_ABOUT, CInterface::OnAbout)
    EVT_HELP(wxID_ANY, CInterface::OnHelp)
    EVT_IDLE(CInterface::OnIdle)
END_EVENT_TABLE();

CInterface::CInterface() :
wxTaskBarIcon()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CInterface - Function Begin"));

    SetIcon(wxICON(boincsentinels));

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CInterface - Function End"));
}

CInterface::~CInterface()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::~CInterface - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::~CInterface - Function End"));
}

bool CInterface::GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue)
{
    return wxGetApp().GetConfigManager()->GetConfigValue(wxT("Interface"), strSubComponent, strValueName, dwDefaultValue, pdwValue);
}

bool CInterface::SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue)
{
    return wxGetApp().GetConfigManager()->SetConfigValue(wxT("Interface"), strSubComponent, strValueName, dwValue);
}

void CInterface::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnAbout - Function Begin"));

    wxAboutDialogInfo info;

    info.SetIcon(wxGetApp().GetSkinManager()->GetBOINCSentinelsIcons().GetIcon(128));
    info.SetName(wxT(PACKAGE_NAME));
    info.SetVersion(wxT(PACKAGE_VERSION));
    info.SetDescription(_("A prototype interface for BOINC to test usability ideas."));
    info.SetCopyright(wxT("Copyright (c) 2009-2013 BOINC Sentinels Development Team"));
    info.SetWebSite(wxT("https://projects.romwnet.org/boincsentinels"), wxT("BOINC Sentinels"));
    info.AddDeveloper(wxT("Rom Walton"));
    info.AddDeveloper(wxT("Jorden van der Elst"));
    info.AddArtist(wxT("DryIcons (http://dryicons.com)"));
    info.AddArtist(wxT("LedIcons (http://led24.de)"));

    wxAboutBox(info);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnAbout - Function End"));
}

void CInterface::OnExit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnExit - Function Begin"));

    RemoveIcon();

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnExit - Function End"));
}

void CInterface::OnHelp(wxHelpEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHelp - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHelp - Function End"));
    event.Skip();
}

void CInterface::OnIdle(wxIdleEvent& event) {
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnIdle - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnIdle - Function End"));
    event.Skip();
}

// Overridables
wxMenu* CInterface::CreatePopupMenu()
{
    wxMenu* pMenu = new wxMenu;

    pMenu->Append(wxID_ABOUT, _("&About BOINC Sentinels..."));

    /* OSX has built-in quit menu for the dock menu, but not for the status item */
#ifdef __WXOSX__ 
    if ( OSXIsStatusItem() )
#endif
    {
        pMenu->AppendSeparator();
        pMenu->Append(wxID_EXIT, _("E&xit"));
    }
    return pMenu;
}