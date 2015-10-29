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

#ifndef _DLGCONNECTION_H_
#define _DLGCONNECTION_H_

#define ID_DIALOG 10000
#define SYMBOL_CDLGCONNECTION_STYLE wxDEFAULT_DIALOG_STYLE
#define SYMBOL_CDLGCONNECTION_TITLE wxT("")
#define SYMBOL_CDLGCONNECTION_IDNAME ID_DIALOG
#define SYMBOL_CDLGCONNECTION_SIZE wxSize(400, 300)
#define SYMBOL_CDLGCONNECTION_POSITION wxDefaultPosition
#define ID_NAME 10001
#define ID_PASSWORD 10002
#define ID_PORT 10003
#define ID_CONNECTONSTARTUP 10004

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

class CDlgConnection: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CDlgConnection)
    DECLARE_EVENT_TABLE()

public:
    CDlgConnection( );
    CDlgConnection(wxWindow* parent, wxWindowID id = SYMBOL_CDLGCONNECTION_IDNAME, const wxString& caption =
        SYMBOL_CDLGCONNECTION_TITLE, const wxPoint& pos = SYMBOL_CDLGCONNECTION_POSITION,
        const wxSize& size = SYMBOL_CDLGCONNECTION_SIZE, long style = SYMBOL_CDLGCONNECTION_STYLE);

    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_CDLGCONNECTION_IDNAME, const wxString& caption =
        SYMBOL_CDLGCONNECTION_TITLE, const wxPoint& pos = SYMBOL_CDLGCONNECTION_POSITION,
        const wxSize& size = SYMBOL_CDLGCONNECTION_SIZE, long style = SYMBOL_CDLGCONNECTION_STYLE);

    void OnActivate(wxActivateEvent& event);
    void OnComputerNameUpdated(wxCommandEvent& event);
    void OnOK(wxCommandEvent& event);
    void OnUpdate();

    void SetName(wxString& strName);

private:
    void CreateControls();

    wxTextCtrl* m_NameCtrl;
    wxTextCtrl* m_PasswordCtrl;
    wxTextCtrl* m_PortCtrl;
    wxCheckBox* m_ConnectOnStartupCtrl;
    wxString m_strName;
    wxString m_strPassword;
    wxString m_strPort;
    bool m_bConnectOnStartup;
};

#endif
