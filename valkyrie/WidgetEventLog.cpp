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
#include "WidgetEventLog.h"
#include "DlgEventLog.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETEVENTLOG_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetEventLog, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetEventLog, CWidgetBase)
    EVT_WIDGETEVENTLOG_INIT(CWidgetEventLog::OnInit)
    EVT_BUTTON(ID_WIDGETEVENTLOGPROPERTIES, CWidgetEventLog::OnEventLogProperties)
END_EVENT_TABLE();

CWidgetEventLog::CWidgetEventLog()
{
}

CWidgetEventLog::CWidgetEventLog(wxWindow* pParent, BSLHOST hHost) :
CWidgetBase(pParent, ID_WIDGETEVENTLOG, _("Event Log"))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::CWidgetEventLog - Function Begin"));

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;
    m_pPropertiesCtrl = NULL;

    m_hHost = hHost;

    // Create Controls
    CreateControls(false, false, true);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETEVENTLOG_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::CWidgetEventLog - Function End"));
}

CWidgetEventLog::~CWidgetEventLog()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::~CWidgetEventLog - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::~CWidgetEventLog - Function End"));
}

bool CWidgetEventLog::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::OnCreateButtonBar - Function Begin"));

    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pPropertiesCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETEVENTLOGPROPERTIES, pSkin->GetPropertiesIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pPropertiesCtrl->SetToolTip(_("View Event Log"));
    m_pButtonBarSizer->Add(m_pPropertiesCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::OnCreateButtonBar - Function End"));
    return true;
}

void CWidgetEventLog::OnInit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::OnInit - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for messages
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyMessagesUpdateInterval, 1);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetEventLog::OnInit - Function End"));
}

void CWidgetEventLog::OnEventLogProperties(wxCommandEvent& WXUNUSED(event))
{
    CDlgEventLog dlgEventLog(m_hHost);
    dlgEventLog.ShowModal();
}
