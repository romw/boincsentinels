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

#ifndef _DLGNEWCONNECTION_H_
#define _DLGNEWCONNECTION_H_

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define SYMBOL_CDlgConnection_STYLE wxDEFAULT_DIALOG_STYLE
#define SYMBOL_CDlgConnection_TITLE wxT("")
#define SYMBOL_CDlgConnection_IDNAME ID_DIALOG
#define SYMBOL_CDlgConnection_SIZE wxSize(400, 300)
#define SYMBOL_CDlgConnection_POSITION wxDefaultPosition
#define ID_NAME 10001
#define ID_PASSWORD 10002
#define ID_PORT 10003
#define ID_CONNECTONSTARTUP 10004
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * CDlgConnection class declaration
 */

class CDlgConnection: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CDlgConnection)
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CDlgConnection( );
    CDlgConnection(wxWindow* parent, wxWindowID id = SYMBOL_CDlgConnection_IDNAME, const wxString& caption =
        SYMBOL_CDlgConnection_TITLE, const wxPoint& pos = SYMBOL_CDlgConnection_POSITION,
        const wxSize& size = SYMBOL_CDlgConnection_SIZE, long style = SYMBOL_CDlgConnection_STYLE);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_CDlgConnection_IDNAME, const wxString& caption =
        SYMBOL_CDlgConnection_TITLE, const wxPoint& pos = SYMBOL_CDlgConnection_POSITION,
        const wxSize& size = SYMBOL_CDlgConnection_SIZE, long style = SYMBOL_CDlgConnection_STYLE);

    /// Creates the controls and sizers
    void CreateControls();

    ////@begin CDlgConnection event handler declarations

    /// wxEVT_COMMAND_TEXT_UPDATED event handler for ID_NAME
    void OnComputerNameUpdated(wxCommandEvent& event);

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOK(wxCommandEvent& event);

    ////@end CDlgConnection event handler declarations

    ////@begin CDlgConnection member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource(const wxString& name);

    /// Retrieves icon resources
    wxIcon GetIconResource(const wxString& name);
    ////@end CDlgConnection member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    ////@begin CDlgConnection member variables
    wxTextCtrl* m_NameCtrl;
    wxTextCtrl* m_PasswordCtrl;
    wxTextCtrl* m_PortCtrl;
    wxCheckBox* m_ConnectOnStartupCtrl;
    wxString m_strName;
    wxString m_strPassword;
    wxString m_strPort;
    bool m_bConnectOnStartup;
    ////@end CDlgConnection member variables
};

#endif
// _DLGSELECTCOMPUTER_H_
