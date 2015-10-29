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
#include "Events.h"
#include "Valkyrie.h"
#include "SkinManager.h"
#include "WidgetControls.h"
#include "WidgetBase.h"
#include "WidgetStatus.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETSTATUS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetStatus, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetStatus, CWidgetBase)
    EVT_WIDGETSTATUS_INIT(CWidgetStatus::OnInit)
END_EVENT_TABLE();

CWidgetStatus::CWidgetStatus()
{
}

CWidgetStatus::CWidgetStatus(wxWindow* pParent, BSLHOST hHost) :
CWidgetBase(pParent, ID_WIDGETSTATUS, _("Status"))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::CWidgetStatus - Function Begin"));

    m_hHost = hHost;

    CreateControls(true, true, false);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETSTATUS_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::CWidgetStatus - Function End"));
}

CWidgetStatus::~CWidgetStatus()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::~CWidgetStatus - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for the global state
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyStateUpdateInterval, 0);
    // Setup the refresh cycle for the host status
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyHostStatusUpdateInterval, 0);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::~CWidgetStatus - Function End"));
}

bool CWidgetStatus::OnCreateContent(wxWindow* WXUNUSED(pParent), CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::OnCreateContent - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::OnCreateContent - Function End"));
    return true;
}

void CWidgetStatus::OnInit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::OnInit - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for the global state
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyStateUpdateInterval, 3600);
    // Setup the refresh cycle for the host status
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyHostStatusUpdateInterval, 1);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetStatus::OnInit - Function End"));
}

