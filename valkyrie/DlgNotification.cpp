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
#include "Interface.h"
#include "DlgNotification.h"


wxString LocalizeNotification(wxString& strMessage) {
    wxString strBuffer = wxEmptyString;
    wxString strStart = wxString(wxT("_(\""));
    wxString strEnd = wxString(wxT("\")"));

    // Replace CRLFs with HTML breaks.
    strMessage.Replace(wxT("\r\n"), wxT("<BR>"));
    // Replace LFs with HTML breaks.
    strMessage.Replace(wxT("\n"), wxT("<BR>"));

    // Localize translatable text
    while (strMessage.Find(strStart.c_str()) != wxNOT_FOUND) {
        strBuffer =
            strMessage.SubString(
                strMessage.Find(strStart.c_str()) + strStart.Length(),
                strMessage.Find(strEnd.c_str()) - (strEnd.Length() - 1)
            );

        strMessage.Replace(
            wxString(strStart + strBuffer + strEnd).c_str(),
            wxGetTranslation(strBuffer.c_str())
        );
    }
    return strMessage;
}


IMPLEMENT_DYNAMIC_CLASS(CDlgNotification, wxDialog);

BEGIN_EVENT_TABLE(CDlgNotification, wxDialog)
    EVT_BSLNOTIFICATION_UPDATE(CDlgNotification::OnNotificationUpdate)
END_EVENT_TABLE();


CDlgNotification::CDlgNotification()
{
}

CDlgNotification::CDlgNotification(BSLHOST hHost, BSLNOTIFICATION hNotification)
{
    m_hHost = hHost;
    m_hNotification = hNotification;
    Create(NULL);
}

CDlgNotification::CDlgNotification(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    Create(parent, id, caption, pos, size, style);
}

CDlgNotification::~CDlgNotification()
{
    CBSLClient* pState = wxGetApp().GetState();

    // Unregister for notification events
    pState->UnregisterEventHandler(this, wxEVT_BSLNOTIFICATION_UPDATE, m_hHost, m_hNotification);
}

bool CDlgNotification::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLNotification bslNotification;

    wxString strCaption = caption;
    if (strCaption.IsEmpty())
    {
        strCaption = _("BOINC-Sentinels - Notification");
    }

    SetExtraStyle(GetExtraStyle() | wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create(parent, id, strCaption, pos, size, style);

    pState->GetNotification(m_hNotification, &bslNotification);
    CreateControls();
    UpdateControls(bslNotification);

    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);

    Centre();

    // Register for notification events
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_UPDATE, m_hHost, m_hNotification);
    return TRUE;
}

void CDlgNotification::CreateControls()
{
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(1);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( this, wxID_STATIC, _("Project:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pProjectCtrl = new wxStaticText( this, ID_PROJECT, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pProjectCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( this, wxID_STATIC, _("Link:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pLinkCtrl = new wxHyperlinkCtrl( this, ID_LINK, wxT(""), wxT(""), wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxHL_CONTEXTMENU|wxHL_ALIGN_LEFT );
    itemFlexGridSizer3->Add(m_pLinkCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( this, wxID_STATIC, _("Subject:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pSubjectCtrl = new wxStaticText( this, ID_SUBJECT, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pSubjectCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pBodyCtrl = wxWebView::New( this, ID_BODY, wxWebViewDefaultURLStr, wxDefaultPosition, wxSize(550, 225) );
    itemBoxSizer2->Add(m_pBodyCtrl, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer4 = new wxStdDialogButtonSizer;
    itemBoxSizer2->Add(itemStdDialogButtonSizer4, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton11 = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
    itemStdDialogButtonSizer4->AddButton(itemButton11);
    itemStdDialogButtonSizer4->Realize();
}

void CDlgNotification::UpdateControls(CBSLNotification& bslNotification)
{
    m_pProjectCtrl->SetLabel(bslNotification.GetProject());
    m_pLinkCtrl->SetLabel(bslNotification.GetLink());
    m_pLinkCtrl->SetURL(bslNotification.GetLink());
    m_pBodyCtrl->SetPage(LocalizeNotification(bslNotification.GetNotificationText()), wxT("http://"));
}

void CDlgNotification::OnNotificationUpdate(CBSLNotificationEvent& event)
{
    CBSLNotification bslNotification;
    if (BSLERR_SUCCESS == event.GetNotification(&bslNotification))
    {
        UpdateControls(bslNotification);
    }
}
