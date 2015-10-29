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
#include "Valkyrie.h"
#include "Utils.h"
#include "Interface.h"
#include "DlgControls.h"
#include "DlgActiveTransfer.h"

IMPLEMENT_DYNAMIC_CLASS(CDlgActiveTransfer, wxDialog);

BEGIN_EVENT_TABLE(CDlgActiveTransfer, wxDialog)
    EVT_BSLTRANSFER_UPDATE(CDlgActiveTransfer::OnTransferUpdate)
END_EVENT_TABLE();


CDlgActiveTransfer::CDlgActiveTransfer()
{
}

CDlgActiveTransfer::CDlgActiveTransfer(BSLHOST hHost, BSLTRANSFER hTransfer)
{
    m_hHost = hHost;
    m_hTransfer = hTransfer;
    Create(NULL);
}

CDlgActiveTransfer::CDlgActiveTransfer(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    Create(parent, id, caption, pos, size, style);
}

CDlgActiveTransfer::~CDlgActiveTransfer()
{
    CBSLClient* pState = wxGetApp().GetState();

    // Unregister for notification events
    pState->UnregisterEventHandler(this, wxEVT_BSLTRANSFER_UPDATE, m_hHost, m_hTransfer);
}

bool CDlgActiveTransfer::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTransfer bslTransfer;

    wxString strCaption = caption;
    if (strCaption.IsEmpty())
    {
        strCaption = _("BOINC-Sentinels - Active Transfer");
    }

    SetExtraStyle(GetExtraStyle() | wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create(parent, id, strCaption, pos, size, style);

    pState->GetTransfer(m_hTransfer, &bslTransfer);
    CreateControls();
    UpdateControls(bslTransfer);

    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);

    Centre();

    // Register for task instance events
    pState->RegisterEventHandler(this, wxEVT_BSLTRANSFER_UPDATE, m_hHost, m_hTransfer);
    return TRUE;
}

void CDlgActiveTransfer::CreateControls()
{
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(3, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(1);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( this, wxID_STATIC, _("Project:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pProjectCtrl = new CDlgStaticText( this, ID_PROJECT, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pProjectCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( this, wxID_STATIC, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pNameCtrl = new CDlgStaticText( this, ID_NAME, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pNameCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( this, wxID_STATIC, _("Progress:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pProgressCtrl = new CDlgProgress( this, ID_PROGRESS, 0.0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pProgressCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( this, wxID_STATIC, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pSizeCtrl = new CDlgByteCount( this, ID_SIZE, 0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pSizeCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( this, wxID_STATIC, _("Elapsed Time:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pElapsedTimeCtrl = new CDlgTimeSpan( this, ID_ELAPSEDTIME, wxTimeSpan::Seconds(0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pElapsedTimeCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( this, wxID_STATIC, _("Speed:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pSpeedCtrl = new CDlgByteRate( this, ID_SPEED, 0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pSpeedCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( this, wxID_STATIC, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pStatusCtrl = new CDlgStaticText( this, ID_STATUS, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pProjectCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer4 = new wxStdDialogButtonSizer;
    itemBoxSizer2->Add(itemStdDialogButtonSizer4, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton11 = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
    itemStdDialogButtonSizer4->AddButton(itemButton11);
    itemStdDialogButtonSizer4->Realize();
}

void CDlgActiveTransfer::UpdateControls(CBSLTransfer& bslTransfer)
{
    m_pProjectCtrl->SetLabel(bslTransfer.GetProject());
    m_pNameCtrl->SetLabel(bslTransfer.GetName());
    m_pProgressCtrl->SetValue(
        std::floor((double)bslTransfer.GetBytesTransfered() / (double)bslTransfer.GetBytes() * 10000)/10000
    );
    m_pSizeCtrl->SetValue(bslTransfer.GetBytesTransfered());
    m_pSizeCtrl->SetTotal(bslTransfer.GetBytes());
    m_pElapsedTimeCtrl->SetValue(bslTransfer.GetElapsedTime());
    m_pSpeedCtrl->SetValue(bslTransfer.GetTransferRate());
    m_pStatusCtrl->SetLabel(CUtils::ConstructTransferStatus(bslTransfer));
}

void CDlgActiveTransfer::OnTransferUpdate(CBSLTransferEvent& event)
{
    CBSLTransfer bslTransfer;
    if (BSLERR_SUCCESS == event.GetTransfer(&bslTransfer))
    {
        UpdateControls(bslTransfer);
    }
}
