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


DEFINE_EVENT_TYPE(wxEVT_WIDGETBASE_INIT);
DEFINE_EVENT_TYPE(wxEVT_WIDGETBASE_RECALCSIZE);
DEFINE_EVENT_TYPE(wxEVT_WIDGETBASE_SHOWCONTENTS);
DEFINE_EVENT_TYPE(wxEVT_WIDGETBASE_HIDECONTENTS);

IMPLEMENT_DYNAMIC_CLASS(CWidgetBase, wxPanel);

BEGIN_EVENT_TABLE(CWidgetBase, wxPanel)
    EVT_WIDGETBASE_INIT(CWidgetBase::OnWidgetBaseInit)
    EVT_BUTTON(ID_WIDGETBASEHEADERCHEVRONEXPAND, CWidgetBase::OnWidgetBaseShowContents)
    EVT_BUTTON(ID_WIDGETBASEHEADERCHEVRONCOLLAPSE, CWidgetBase::OnWidgetBaseShowContents)
    EVT_PAINT(CWidgetBase::OnWidgetBasePaint)
END_EVENT_TABLE();

CWidgetBase::CWidgetBase()
{
    m_bInitialized = false;
    m_bVisible = false;
    m_bContentsEnabled = false;
    m_bShowContents = false;
    m_pWidgetBaseSizer = NULL;
    m_pHeader = NULL;
    m_pHeaderSizer = NULL;
    m_pChevronBar = NULL;
    m_pChevronBarSizer = NULL;
    m_pChevronExpandedCtrl = NULL;
    m_pChevronCollapsedCtrl = NULL;
    m_pNameCtrl = NULL;
    m_pWidgetBaseButtonBar = NULL;
    m_pWidgetBaseContents = NULL;
    m_pParent = NULL;
}

CWidgetBase::CWidgetBase(wxWindow* pParent, wxWindowID iWindowID, wxString strWidgetName)
{
    m_bInitialized = false;
    m_bVisible = true;
    m_bContentsEnabled = false;
    m_bShowContents = false;
    m_pWidgetBaseSizer = NULL;
    m_pHeader = NULL;
    m_pHeaderSizer = NULL;
    m_pChevronBar = NULL;
    m_pChevronBarSizer = NULL;
    m_pChevronExpandedCtrl = NULL;
    m_pChevronCollapsedCtrl = NULL;
    m_pNameCtrl = NULL;
    m_pWidgetBaseButtonBar = NULL;
    m_pWidgetBaseContents = NULL;

    m_pParent = pParent;
    m_strWidgetName = strWidgetName;

    // Initialize base class
    //
    Create(pParent, iWindowID, wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW|wxTAB_TRAVERSAL|wxCLIP_CHILDREN);
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    SetBackgroundColour(pParent->GetBackgroundColour());
    SetForegroundColour(pParent->GetForegroundColour());

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETBASE_INIT);
    AddPendingEvent(evt);
}

CWidgetBase::~CWidgetBase()
{
}

bool CWidgetBase::CreateControls(bool bEnableContents, bool bShowContents, bool bEnableButtonBar)
{
    CSkinManager* pSkin = wxGetApp().GetSkinManager();
    wxSize oIconSize = pSkin->GetSmallIconSize();

    m_pWidgetBaseSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_pWidgetBaseSizer->AddGrowableCol(0);
    SetSizer(m_pWidgetBaseSizer);

    m_pHeader = new wxPanel( this, ID_WIDGETBASEHEADERPANEL, wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
    m_pHeader->SetBackgroundStyle(wxBG_STYLE_COLOUR);
    m_pHeader->SetBackgroundColour(*wxWHITE);
    m_pWidgetBaseSizer->Add(m_pHeader, 0, wxGROW|wxALL, 5);

    m_pHeaderSizer = new wxFlexGridSizer(0, 3, 0, 0);
    m_pHeaderSizer->AddGrowableCol(1);
    m_pHeader->SetSizer(m_pHeaderSizer);

    m_pChevronBar = new wxPanel( m_pHeader, ID_WIDGETBASECHEVRONPANEL, wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
    m_pChevronBar->SetBackgroundStyle(wxBG_STYLE_COLOUR);
    m_pChevronBar->SetBackgroundColour(*wxWHITE);
    m_pHeaderSizer->Add(m_pChevronBar, 0, wxALIGN_LEFT|wxALIGN_CENTER, 0);

    m_pChevronBarSizer = new wxFlexGridSizer(1, 0, 0, 0);
    m_pChevronBar->SetSizer(m_pChevronBarSizer);

    if (bEnableContents)
    {
        m_bContentsEnabled = true;

        m_pChevronExpandedCtrl = new CWidgetBitmapButton( m_pChevronBar, ID_WIDGETBASEHEADERCHEVRONEXPAND, pSkin->GetChevronExpandedIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
        m_pChevronBarSizer->Add(m_pChevronExpandedCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER, 0);

        m_pChevronCollapsedCtrl = new CWidgetBitmapButton( m_pChevronBar, ID_WIDGETBASEHEADERCHEVRONCOLLAPSE, pSkin->GetChevronCollapsedIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
        m_pChevronBarSizer->Add(m_pChevronCollapsedCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER, 0);
    }
    else
    {
        m_pChevronBarSizer->AddSpacer(pSkin->GetSmallIconSize().GetWidth());
        m_pChevronBarSizer->AddSpacer(0);
    }

    m_pNameCtrl = new CWidgetTitle( m_pHeader, ID_WIDGETBASEHEADERTEXT, m_strWidgetName, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_pHeaderSizer->Add(m_pNameCtrl, 0, wxGROW|wxLEFT|wxRIGHT|wxALIGN_CENTER, 5);

    if (bEnableButtonBar)
    {
        m_pWidgetBaseButtonBar = new wxPanel( m_pHeader, ID_WIDGETBASEBUTTONBARPANEL, wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
        m_pWidgetBaseButtonBar->SetBackgroundStyle(wxBG_STYLE_COLOUR);
        m_pWidgetBaseButtonBar->SetBackgroundColour(*wxWHITE);
        m_pHeaderSizer->Add(m_pWidgetBaseButtonBar, 0, wxRIGHT|wxALIGN_CENTER, 3);

        OnCreateButtonBar(m_pWidgetBaseButtonBar, pSkin, oIconSize);

        m_pWidgetBaseButtonBar->Show(true);
    }
    else
    {
        m_pHeaderSizer->AddSpacer(0);
    }

    if (bEnableContents)
    {
        m_pWidgetBaseContents = new wxPanel( this, ID_WIDGETBASECONTENTSPANEL, wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
        m_pWidgetBaseContents->SetBackgroundStyle(wxBG_STYLE_COLOUR);
        m_pWidgetBaseContents->SetBackgroundColour(*wxWHITE);
        m_pWidgetBaseSizer->Add(m_pWidgetBaseContents, 0, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 5);

        OnCreateContent(m_pWidgetBaseContents, pSkin, oIconSize);

        if (bShowContents)
        {
            ShowContents(true);
        }
        else
        {
            ShowContents(false);
        }
    }

    return true;
}

bool CWidgetBase::OnCreateButtonBar(wxWindow* WXUNUSED(pParent), CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    return false;
}

bool CWidgetBase::OnCreateContent(wxWindow* WXUNUSED(pParent), CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    return false;
}

bool CWidgetBase::UpdateHeaderLayout()
{
    m_pHeader->Layout();
    m_pHeader->Refresh();
    return true;
}

void CWidgetBase::OnWidgetBaseInit(wxCommandEvent& WXUNUSED(event))
{
    m_bInitialized = true;
}

void CWidgetBase::OnWidgetBaseShowContents(wxCommandEvent& WXUNUSED(event))
{
    if (IsContentsShown())
    {
        ShowContents(false);
    }
    else
    {
        ShowContents(true);
    }
}

void CWidgetBase::OnWidgetBasePaint(wxPaintEvent& WXUNUSED(event))
{
    // Create a buffered device context to reduce flicker
    wxAutoBufferedPaintDC dc(this);

    // Widget dimensions
    wxSize sz = GetClientSize();

    // Fill the background with the desired color
    dc.SetBrush(wxBrush(GetBackgroundColour()));
    dc.SetPen(wxPen(GetBackgroundColour()));
    dc.DrawRectangle(0, 0, sz.GetWidth(), sz.GetHeight());

    // Fill the widget with the desired color
    dc.SetBrush(wxBrush(*wxWHITE));
    dc.SetPen(wxPen(*wxBLUE, 1));
    dc.DrawRoundedRectangle(0, 0, sz.GetWidth(), sz.GetHeight(), 7.0);
}

wxString& CWidgetBase::GetWidgetName()
{
    return m_strWidgetName;
}

void CWidgetBase::SetWidgetName(wxString strWidgetName)
{
    m_strWidgetName = strWidgetName;
    m_pNameCtrl->SetLabel(strWidgetName);
}

bool CWidgetBase::Show(bool show)
{
    m_bVisible = show;
    return wxPanel::Show(show);
}

bool CWidgetBase::ShowContents(bool show)
{
    if (m_bContentsEnabled)
    {
        if (show)
        {
            m_bShowContents = true;
            m_pWidgetBaseContents->Show();
            m_pChevronExpandedCtrl->Show();
            m_pChevronCollapsedCtrl->Hide();

            wxCommandEvent evt(wxEVT_WIDGETBASE_SHOWCONTENTS);
            ProcessEvent(evt);
        }
        else
        {
            m_bShowContents = false;
            m_pWidgetBaseContents->Hide();
            m_pChevronExpandedCtrl->Hide();
            m_pChevronCollapsedCtrl->Show();

            wxCommandEvent evt(wxEVT_WIDGETBASE_HIDECONTENTS);
            ProcessEvent(evt);
        }

        m_pChevronBar->Layout();
    }

    wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
    AddPendingEvent(evt);

    return true;
}

bool CWidgetBase::IsShown() const
{
    return m_bVisible;
}

bool CWidgetBase::IsContentsShown() const
{
    return m_bVisible && m_bShowContents;
}
