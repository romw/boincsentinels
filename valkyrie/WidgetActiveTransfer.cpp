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
#include "Utils.h"
#include "SkinManager.h"
#include "DlgActiveTransfer.h"
#include "WidgetControls.h"
#include "WidgetBase.h"
#include "WidgetActiveTransfer.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETACTIVETRANSFER_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetActiveTransfer, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetActiveTransfer, CWidgetBase)
    EVT_WIDGETACTIVETRANSFER_INIT(CWidgetActiveTransfer::OnInit)
    EVT_WIDGETBASE_SHOWCONTENTS(CWidgetActiveTransfer::OnShowContents)
    EVT_WIDGETBASE_HIDECONTENTS(CWidgetActiveTransfer::OnHideContents)
    EVT_BUTTON(ID_WIDGETACTIVETRANSFERRETRY, CWidgetActiveTransfer::OnRetry)
    EVT_BUTTON(ID_WIDGETACTIVETRANSFERABORT, CWidgetActiveTransfer::OnAbort)
    EVT_BUTTON(ID_WIDGETACTIVETRANSFERPROPERTIES, CWidgetActiveTransfer::OnProperties)
    EVT_BSLTRANSFER_UPDATE(CWidgetActiveTransfer::OnTransferUpdate)
END_EVENT_TABLE();

CWidgetActiveTransfer::CWidgetActiveTransfer()
{
}

CWidgetActiveTransfer::CWidgetActiveTransfer(wxWindow* pParent, BSLHOST hHost, BSLTRANSFER hTransfer) :
CWidgetBase(pParent, ID_WIDGETACTIVETRANSFER)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTransfer bslTransfer;

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;

    m_hHost = hHost;
    m_hTransfer = hTransfer;

    // Create Controls
    CreateControls(true, true, false);

    // Update control state.
    pState->GetTransfer(m_hTransfer, &bslTransfer);
    SetWidgetName(bslTransfer.GetName());
    UpdateControls(bslTransfer);
    UpdateControlsButtonBar(bslTransfer);
    ToggleVisibility(bslTransfer);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETACTIVETRANSFER_INIT);
    AddPendingEvent(evt);
}

CWidgetActiveTransfer::~CWidgetActiveTransfer()
{
    CBSLClient* pState = wxGetApp().GetState();

    // Unregister from project update events
    pState->UnregisterEventHandler(this, wxEVT_BSLTRANSFER_UPDATE, m_hHost, m_hTransfer);
}

BSLHOST CWidgetActiveTransfer::GetHostHandle()
{
    return m_hHost;
}

BSLTASKINSTANCE CWidgetActiveTransfer::GetTransferHandle()
{
    return m_hTransfer;
}

bool CWidgetActiveTransfer::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pUpdateCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETRANSFERRETRY, pSkin->GetUpdateIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pUpdateCtrl->SetToolTip(_("Update"));
    m_pButtonBarSizer->Add(m_pUpdateCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pAbortCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETRANSFERABORT, pSkin->GetAbortIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pAbortCtrl->SetToolTip(_("Abort"));
    m_pButtonBarSizer->Add(m_pAbortCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pPropertiesCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETRANSFERPROPERTIES, pSkin->GetPropertiesIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pPropertiesCtrl->SetToolTip(_("View Details"));
    m_pButtonBarSizer->Add(m_pPropertiesCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    return true;
}

bool CWidgetActiveTransfer::OnCreateContent(wxWindow* pParent, CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    m_pContent = pParent;
    m_pContentSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_pContentSizer->AddGrowableCol(0);
    m_pContent->SetSizer(m_pContentSizer);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(1);
    m_pContentSizer->Add(itemFlexGridSizer3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxStaticText* pProjectStaticCtrl = new wxStaticText( m_pContent, wxID_STATIC, _("Project:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(pProjectStaticCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pProjectCtrl = new wxStaticText( m_pContent, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pProjectCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    wxStaticText* pProgressStaticCtrl = new wxStaticText( m_pContent, wxID_STATIC, _("Progress:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(pProgressStaticCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pProgressCtrl = new CWidgetProgress( m_pContent, wxID_ANY, 0, wxDefaultPosition, wxSize(-1, 16), 0 );
    itemFlexGridSizer3->Add(m_pProgressCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    wxFlexGridSizer* itemFlexGridSizer6 = new wxFlexGridSizer(0, 4, 0, 0);
    itemFlexGridSizer6->AddGrowableCol(1);
    itemFlexGridSizer6->AddGrowableCol(3);
    m_pContentSizer->Add(itemFlexGridSizer6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxStaticText* pElapsedTimeStaticCtrl = new wxStaticText( m_pContent, wxID_STATIC, _("Elapsed Time:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(pElapsedTimeStaticCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pElapsedTimeCtrl = new CWidgetElapsed( m_pContent, wxID_STATIC, wxTimeSpan(0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(m_pElapsedTimeCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    wxStaticText* itemStaticText9 = new wxStaticText( m_pContent, wxID_STATIC, _("Transfer Rate:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(itemStaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pTransferRateCtrl = new CWidgetTransferRate( m_pContent, wxID_STATIC, 0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(m_pTransferRateCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    wxFlexGridSizer* itemFlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer11->AddGrowableCol(1);
    m_pContentSizer->Add(itemFlexGridSizer11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxStaticText* pStatusStaticCtrl = new wxStaticText( m_pContent, wxID_STATIC, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(pStatusStaticCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pStatusCtrl = new wxStaticText( m_pContent, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(m_pStatusCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pContentSizer->AddSpacer(1);

    // Calculate the layout of the control
    m_pContentSizer->CalcMin();

    // Project, Progress, Elapsed Time, and Status should all have the same width.
    int iMaxWidth = pProjectStaticCtrl->GetEffectiveMinSize().GetWidth();
    iMaxWidth = std::max(iMaxWidth, pProgressStaticCtrl->GetEffectiveMinSize().GetWidth());
    iMaxWidth = std::max(iMaxWidth, pElapsedTimeStaticCtrl->GetEffectiveMinSize().GetWidth());
    iMaxWidth = std::max(iMaxWidth, pStatusStaticCtrl->GetEffectiveMinSize().GetWidth());

    wxSize sz(iMaxWidth, -1);
    pProjectStaticCtrl->SetMinSize(sz);
    pProgressStaticCtrl->SetMinSize(sz);
    pElapsedTimeStaticCtrl->SetMinSize(sz);
    pStatusStaticCtrl->SetMinSize(sz);

    return true;
}

void CWidgetActiveTransfer::UpdateControls(CBSLTransfer& bslTransfer)
{
    m_pProgressCtrl->SetValue(
        std::floor((double)bslTransfer.GetBytesTransfered() / (double)bslTransfer.GetBytes() * 10000)/10000
    );
    m_pElapsedTimeCtrl->SetValue(bslTransfer.GetElapsedTime());
    m_pTransferRateCtrl->SetValue(bslTransfer.GetTransferRate());
    m_pStatusCtrl->SetLabel(CUtils::ConstructTransferStatus(bslTransfer));
}

void CWidgetActiveTransfer::UpdateControlsButtonBar(CBSLTransfer& bslTransfer)
{
}

void CWidgetActiveTransfer::ToggleVisibility(CBSLTransfer& bslTransfer)
{
    if (!IsShown())
    {
        if (bslTransfer.IsTransferActive())
        {
            Show();

            wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
            AddPendingEvent(evt);
        }
    }
    else
    {
        if (!bslTransfer.IsTransferActive())
        {
            Hide();

            wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
            AddPendingEvent(evt);
        }
    }
}

void CWidgetActiveTransfer::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Register for project update events
    pState->RegisterEventHandler(this, wxEVT_BSLTRANSFER_UPDATE, m_hHost, m_hTransfer);
}

void CWidgetActiveTransfer::OnShowContents(wxCommandEvent& WXUNUSED(event))
{
}

void CWidgetActiveTransfer::OnHideContents(wxCommandEvent& WXUNUSED(event))
{
}

void CWidgetActiveTransfer::OnRetry(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->TransferRetry(m_hTransfer);
}

void CWidgetActiveTransfer::OnAbort(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTransfer bslTransfer;
    wxString strBuffer = wxEmptyString;

    pState->GetTransfer(m_hTransfer, &bslTransfer);

    strBuffer.Printf(
        _("Are you sure you wish to abort transfer '%s'?\nNOTE: Aborting a transfer will invalidate a task and you\nwill not receive credit for it."),
        bslTransfer.GetName().c_str()
    );

    wxInt32 rc = ::wxMessageBox(
        strBuffer.c_str(),
        _("BOINC-Sentinels"),
        wxYES_NO | wxICON_QUESTION
    );
    if (wxYES == rc)
    {
        pState->TransferAbort(m_hTransfer);
    }
}

void CWidgetActiveTransfer::OnProperties(wxCommandEvent& WXUNUSED(event))
{
    CDlgActiveTransfer dlgActiveTransfer(m_hHost, m_hTransfer);
    dlgActiveTransfer.ShowModal();
}

void CWidgetActiveTransfer::OnTransferUpdate(CBSLTransferEvent& event)
{
    CBSLTransfer bslTransfer;
    event.GetTransfer(&bslTransfer);

    ToggleVisibility(bslTransfer);
    if (bslTransfer.IsTransferActive())
    {
        UpdateControlsButtonBar(bslTransfer);
        if (IsContentsShown())
        {
            UpdateControls(bslTransfer);
        }
    }
}
