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

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

class CInterface: public wxFrame
{
    DECLARE_DYNAMIC_CLASS(CInterface)
    DECLARE_EVENT_TABLE()

public:

    CInterface();
    ~CInterface();

    void OnExit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHelp(wxHelpEvent& event);
    void OnInit(wxCommandEvent& event);

    void OnHostAdd(CBSLHostEvent& event);
    void OnHostDelete(CBSLHostEvent& event);
    void OnHostConnecting(CBSLHostEvent& event);
    void OnHostConnected(CBSLHostEvent& event);
    void OnHostDisconnected(CBSLHostEvent& event);
    void OnHostConnectionFailure(CBSLHostEvent& event);
    void OnHostAuthenticationFailure(CBSLHostEvent& event);
    void OnHostVersionIncompatibleFailure(CBSLHostEvent& event);

    bool AddConnection(wxString strName, wxString strPassword, long lPort);
    bool AddPersistantConnection(wxString strName, wxString strPassword, wxString strPort, long bConnectOnStartup);
    bool DeleteConnection(wxString strName);
    bool DeletePersistantConnection(wxString strName);
    bool EnumerateConnections(wxSortedArrayString* pstrNames);
    bool EnumeratePersistantConnections(wxSortedArrayString* pstrNames);
    bool GetConnectionProperties(wxString strName, wxString* pstrPassword, long* plPort);
    bool GetPersistantConnectionProperties(wxString strName, wxString* pstrPassword, wxString* pstrPort, long* pbConnectOnStartup);

private:

    wxMenuBar* m_pMenuBar;
    wxNotebook* m_pNotebook;

    int m_iHostIconPosition;
    int m_iHostAddIconPosition;
    int m_iHostConnectingIconPosition;
    int m_iHostConnectedIconPosition;
    int m_iHostConnectionFailureIconPosition;
    int m_iHostAuthenticationFailureIconPosition;
    int m_iHostDisconnectedIconPosition;

    bool CreateMenu();
    bool CreateNotebook();

    bool DeleteMenu();
    bool DeleteNotebook();

    bool GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue);
    bool SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue);
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_INTERFACE_INIT, 10100 )
END_DECLARE_EVENT_TYPES()

#define EVT_INTERFACE_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_INTERFACE_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

