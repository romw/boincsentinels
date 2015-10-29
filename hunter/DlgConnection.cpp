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
#include <wx/valgen.h>
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Hunter.h"
#include "Interface.h"
#include "DlgConnection.h"

/*!
 * CDlgConnection type definition
 */

IMPLEMENT_DYNAMIC_CLASS(CDlgConnection, wxDialog);

/*!
 * CDlgConnection event table definition
 */

BEGIN_EVENT_TABLE(CDlgConnection, wxDialog)
////@begin CDlgConnection event table entries
EVT_TEXT(ID_NAME, CDlgConnection::OnComputerNameUpdated)
EVT_BUTTON(wxID_OK, CDlgConnection::OnOK)
////@end CDlgConnection event table entries
END_EVENT_TABLE();

/*!
 * CDlgConnection constructors
 */

CDlgConnection::CDlgConnection( )
{
}

CDlgConnection::CDlgConnection(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos,
    const wxSize& size, long style)
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * CDlgConnection creator
 */

bool CDlgConnection::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos,
    const wxSize& size, long style)
{
    ////@begin CDlgConnection member initialization
    m_NameCtrl = NULL;
    m_PasswordCtrl = NULL;
    m_PortCtrl = NULL;
    m_ConnectOnStartupCtrl = NULL;
    ////@end CDlgConnection member initialization

    wxString strCaption = caption;
    if (strCaption.IsEmpty())
    {
        strCaption = _("BOINC-Sentinels - New Connection");
    }

    ////@begin CDlgConnection creation
    SetExtraStyle(GetExtraStyle() | wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create(parent, id, strCaption, pos, size, style);

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);

    // Convert the latest and greatest
    //
    TransferDataToWindow();

    Centre();
    ////@end CDlgConnection creation
    return TRUE;
}

/*!
 * Control creation for CDlgConnection
 */

void CDlgConnection::CreateControls()
{
    ////@begin CDlgConnection content construction
    CDlgConnection* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer5 = new wxFlexGridSizer(3, 2, 5, 0);
    itemBoxSizer2->Add(itemFlexGridSizer5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    wxStaticText* itemStaticText6 = new wxStaticText;
    itemStaticText6->Create(itemDialog1, wxID_STATIC, _("Host name:"), wxDefaultPosition, wxDefaultSize, 0);
    itemFlexGridSizer5->Add(itemStaticText6, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_NameCtrl = new wxTextCtrl;
    m_NameCtrl->Create(itemDialog1, ID_NAME, _T(""), wxDefaultPosition, wxSize(150, -1), 0);
    itemFlexGridSizer5->Add(m_NameCtrl, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 0);

    wxStaticText* itemStaticText8 = new wxStaticText;
    itemStaticText8->Create(itemDialog1, wxID_STATIC, _("Password:"), wxDefaultPosition, wxDefaultSize, 0);
    itemFlexGridSizer5->Add(itemStaticText8, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_PasswordCtrl = new wxTextCtrl;
    m_PasswordCtrl->Create(itemDialog1, ID_PASSWORD, _T(""), wxDefaultPosition, wxSize(150, -1), wxTE_PASSWORD);
    itemFlexGridSizer5->Add(m_PasswordCtrl, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 0);

    wxStaticText* itemStaticText9 = new wxStaticText;
    itemStaticText9->Create(itemDialog1, wxID_STATIC, _("Port:"), wxDefaultPosition, wxDefaultSize, 0);
    itemFlexGridSizer5->Add(itemStaticText9, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_PortCtrl = new wxTextCtrl;
    m_PortCtrl->Create(itemDialog1, ID_PORT, _T(""), wxDefaultPosition, wxSize(50, -1), 0);
    itemFlexGridSizer5->Add(m_PortCtrl, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_ConnectOnStartupCtrl = new wxCheckBox;
    m_ConnectOnStartupCtrl->Create(itemDialog1, ID_CONNECTONSTARTUP, _("Connect on startup"), wxDefaultPosition,
        wxDefaultSize, 0);
    m_ConnectOnStartupCtrl->SetValue(false);
    itemBoxSizer2->Add(m_ConnectOnStartupCtrl, 0, wxALL, 10);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer4 = new wxStdDialogButtonSizer;
    itemBoxSizer2->Add(itemStdDialogButtonSizer4, 0, wxALIGN_RIGHT | wxALL, 5);

    wxButton* itemButton11 = new wxButton(itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
    itemStdDialogButtonSizer4->AddButton(itemButton11);

    wxButton* itemButton12 = new wxButton(itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition,
        wxDefaultSize, 0);
    itemStdDialogButtonSizer4->AddButton(itemButton12);

    itemStdDialogButtonSizer4->Realize();

    // Set validators
    m_NameCtrl->SetValidator(wxGenericValidator(&m_strName));
    m_PasswordCtrl->SetValidator(wxGenericValidator(&m_strPassword));
    m_PortCtrl->SetValidator(wxGenericValidator(&m_strPort));
    m_ConnectOnStartupCtrl->SetValidator(wxGenericValidator(&m_bConnectOnStartup));
    ////@end CDlgConnection content construction
}

/*!
 * Should we show tooltips?
 */

bool CDlgConnection::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap CDlgConnection::GetBitmapResource(const wxString& WXUNUSED(name))
{
    // Bitmap retrieval
    ////@begin CDlgConnection bitmap retrieval
    return wxNullBitmap;
    ////@end CDlgConnection bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CDlgConnection::GetIconResource(const wxString& WXUNUSED(name))
{
    // Icon retrieval
    ////@begin CDlgConnection icon retrieval
    return wxNullIcon;
    ////@end CDlgConnection icon retrieval
}

/*!
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_NAME
 */

void CDlgConnection::OnComputerNameUpdated(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CDlgConnection::OnComputerNameUpdated - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();
    CInterface* pInterface = wxGetApp().GetInterface();
    wxString strName;
    wxString strPassword;
    wxString strPort;
    long lPort = 0;
    long bConnectOnStartup = 0;
    bool rc = false;

    // If the dialog is just starting up the computer name control
    // will be empty
    strName = m_NameCtrl->GetValue();
    if (!strName.IsEmpty())
    {

        bool bIsLocalHost = pState->IsLocalHostName(strName);

        // Determine if an alias was used for the host name
        //
        if (bIsLocalHost)
        {
            // Replace current value with the correct name
            pState->GetLocalHostName(strName);
            m_NameCtrl->ChangeValue(strName);
        }

        // Determine if we can pre-populate the password
        //
        rc = pInterface->GetPersistantConnectionProperties(strName, &strPassword, &strPort, &bConnectOnStartup);

        if (!rc && bIsLocalHost)
        {
            // Haven't connected to this host before, use default values
            pState->GetLocalHostPassword(strPassword);
            pState->GetLocalHostPort(lPort);
            strPort.Printf(wxT("%d"), lPort);
            m_PasswordCtrl->ChangeValue(strPassword);
            m_PortCtrl->SetValue(strPort);
            m_ConnectOnStartupCtrl->SetValue(false);
        }
        else if (rc)
        {
            // Found an entry for this host
            if (bIsLocalHost)
            {
                // Replace current value with the password as defined by the
                // gui_rpc_auth.cfg file.
                pState->GetLocalHostPassword(strPassword);
            }
            m_PasswordCtrl->ChangeValue(strPassword);
            m_PortCtrl->SetValue(strPort);
            m_ConnectOnStartupCtrl->SetValue(bConnectOnStartup == 1);
        }
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CDlgConnection::OnComputerNameUpdated - Function End"));
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void CDlgConnection::OnOK(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CDlgConnection::OnOK - Function Begin"));

    long lPort = 0;
    bool rc = false;

    TransferDataFromWindow();

    rc = wxGetApp().GetInterface()->AddPersistantConnection(m_strName.Lower(), m_strPassword, m_strPort, m_bConnectOnStartup);
    if (rc)
    {
        m_strPort.ToLong(&lPort);
        wxGetApp().GetInterface()->AddConnection(m_strName.Lower(), m_strPassword, lPort);
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CDlgConnection::OnOK - Function End"));
    EndModal( wxID_OK);
}

