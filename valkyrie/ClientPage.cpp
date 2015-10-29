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
#include "WidgetBase.h"
#include "WidgetActiveTasks.h"
#include "WidgetActiveTransfers.h"
#include "WidgetEventLog.h"
#include "WidgetNews.h"
#include "WidgetProjects.h"
#include "WidgetStatus.h"
#include "WidgetUsage.h"
#include "ClientPage.h"

DEFINE_EVENT_TYPE(wxEVT_CLIENTPAGE_INIT);

IMPLEMENT_DYNAMIC_CLASS(CClientPage, wxScrolledWindow);

BEGIN_EVENT_TABLE(CClientPage, wxScrolledWindow)
    EVT_WIDGETBASE_RECALCSIZE(CClientPage::OnRecalcSize)
END_EVENT_TABLE();

CClientPage::CClientPage()
{
}

CClientPage::CClientPage(wxWindow* pParent, BSLHOST hHost)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CClientPage::CClientPage - Function Begin"));

    m_hHost = hHost;

    // Initialize base class
    //
    Create(pParent, ID_CLIENTPAGE);
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetBackgroundColour(wxColour(176,196,222));

    // Move everything into place automatically
    //
    SetAutoLayout(true);

    // Create UI elements
    //
    CreateControls();

    wxLogTrace(wxT("Function Start/End"), wxT("CClientPage::CClientPage - Function End"));
}

CClientPage::~CClientPage()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CClientPage::~CClientPage - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CClientPage::~CClientPage - Function End"));
}

bool CClientPage::CreateControls()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CClientPage::CreateControls - Function Begin"));

    // Create NotebookPage Sizer
    wxFlexGridSizer* pPageSizer = new wxFlexGridSizer(0, 1, 0, 0);
    pPageSizer->AddGrowableCol(0);
    pPageSizer->SetVGap(3);
    SetSizer(pPageSizer);

    pPageSizer->AddSpacer(2);

    m_pStatus = new CWidgetStatus(this, m_hHost);
    pPageSizer->Add(m_pStatus, 0, wxRIGHT|wxLEFT|wxGROW, 3);

    m_pNews = new CWidgetNews(this, m_hHost);
    pPageSizer->Add(m_pNews, 0, wxRIGHT|wxLEFT|wxGROW, 3);

    m_pActiveTasks = new CWidgetActiveTasks(this, m_hHost);
    pPageSizer->Add(m_pActiveTasks, 0, wxRIGHT|wxLEFT|wxGROW, 3);

    m_pActiveTransfers = new CWidgetActiveTransfers(this, m_hHost);
    pPageSizer->Add(m_pActiveTransfers, 0, wxRIGHT|wxLEFT|wxGROW, 3);

    m_pProjects = new CWidgetProjects(this, m_hHost);
    pPageSizer->Add(m_pProjects, 0, wxRIGHT|wxLEFT|wxGROW, 3);

    m_pUsage = new CWidgetUsage(this, m_hHost);
    pPageSizer->Add(m_pUsage, 0, wxRIGHT|wxLEFT|wxGROW, 3);

    m_pEventLog = new CWidgetEventLog(this, m_hHost);
    pPageSizer->Add(m_pEventLog, 0, wxRIGHT|wxLEFT|wxGROW, 3);

    pPageSizer->AddSpacer(2);

    wxLogTrace(wxT("Function Start/End"), wxT("CClientPage::CreateControls - Function End"));
    return true;
}

void CClientPage::OnRecalcSize(wxCommandEvent& WXUNUSED(event))
{
    GetSizer()->RecalcSizes();
    GetSizer()->Layout();
    Refresh(true);

    SetScrollRate( 0, 25 );
    SetVirtualSize( GetSizer()->ComputeFittingWindowSize(this) );
}

void CClientPage::OnDraw(wxDC& dc)
{
    // Page dimensions
    wxSize sz = GetVirtualSize();

    // Fill the page with the desired color
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(wxPen(GetBackgroundColour()));
    dc.DrawRectangle(0, 0, sz.GetWidth(), sz.GetHeight() + 100);
}
