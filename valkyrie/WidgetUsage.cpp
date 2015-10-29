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
#include "WidgetUsage.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETUSAGE_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetUsage, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetUsage, CWidgetBase)
    EVT_WIDGETUSAGE_INIT(CWidgetUsage::OnInit)
    EVT_BUTTON(ID_WIDGETUSAGEPROPERTIES, CWidgetUsage::OnUsageProperties)
END_EVENT_TABLE();

CWidgetUsage::CWidgetUsage()
{
}

CWidgetUsage::CWidgetUsage(wxWindow* pParent, BSLHOST hHost) :
CWidgetBase(pParent, ID_WIDGETUSAGE, _("Usage"))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::CWidgetUsage - Function Begin"));

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;

    m_hHost = hHost;

    // Create Controls
    CreateControls(false, false, true);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETUSAGE_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::CWidgetUsage - Function End"));
}

CWidgetUsage::~CWidgetUsage()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::~CWidgetUsage - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::~CWidgetUsage - Function End"));
}

bool CWidgetUsage::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::OnCreateButtonBar - Function Begin"));

    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pPropertiesCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETUSAGEPROPERTIES, pSkin->GetPropertiesIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pButtonBarSizer->Add(m_pPropertiesCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::OnCreateButtonBar - Function End"));
    return true;
}

void CWidgetUsage::OnInit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::OnInit - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::OnInit - Function End"));
}

void CWidgetUsage::OnUsageProperties(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::OnUsageProperties - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetUsage::OnUsageProperties - Function End"));
}
