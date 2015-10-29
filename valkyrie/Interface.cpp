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
#include "bslversion.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Valkyrie.h"
#include "DlgConnection.h"
#include "ConfigManager.h"
#include "SkinManager.h"
#include "Interface.h"
#include "StatusPage.h"
#include "ClientPage.h"


DEFINE_EVENT_TYPE(wxEVT_INTERFACE_INIT);

IMPLEMENT_DYNAMIC_CLASS(CInterface, wxFrame);

BEGIN_EVENT_TABLE(CInterface, wxFrame)
    EVT_MENU(wxID_EXIT, CInterface::OnExit)
    EVT_MENU(wxID_ABOUT, CInterface::OnAbout)
    EVT_HELP(wxID_ANY, CInterface::OnHelp)
    EVT_CLOSE(CInterface::OnClose)
    EVT_INTERFACE_INIT(CInterface::OnInit)
    EVT_BSLHOST_ADD(CInterface::OnHostAdd)
    EVT_BSLHOST_DELETE(CInterface::OnHostDelete)
    EVT_BSLHOST_CONNECTING(CInterface::OnHostConnecting)
    EVT_BSLHOST_CONNECTED(CInterface::OnHostConnected)
    EVT_BSLHOST_DISCONNECTING(CInterface::OnHostConnecting)
    EVT_BSLHOST_DISCONNECTED(CInterface::OnHostDisconnected)
    EVT_BSLHOST_RECONNECTING(CInterface::OnHostConnecting)
    EVT_BSLHOST_CONNECTFAILURE(CInterface::OnHostConnectionFailure)
    EVT_BSLHOST_AUTHENTICATIONFAILURE(CInterface::OnHostAuthenticationFailure)
    EVT_BSLHOST_VERSIONINCOMPATIBLEFAILURE(CInterface::OnHostVersionIncompatibleFailure)
END_EVENT_TABLE();

CInterface::CInterface()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CInterface - Function Begin"));

    m_pMenuBar = NULL;
    m_pNotebook = NULL;
    m_iHostIconPosition = 0;
    m_iHostAddIconPosition = 0;
    m_iHostConnectingIconPosition = 0;
    m_iHostConnectedIconPosition = 0;
    m_iHostConnectionFailureIconPosition = 0;
    m_iHostAuthenticationFailureIconPosition = 0;
    m_iHostDisconnectedIconPosition = 0;

    long lMaxWidth = wxSystemSettings::GetMetric( wxSYS_SCREEN_X );
    long lMaxHeight = wxSystemSettings::GetMetric( wxSYS_SCREEN_Y );
    long lHeight = 550;
    long lWidth = 300;
    long lTop = 30;
    long lLeft = lMaxWidth - lWidth - 30;

    // Restore window to its previous location
    //
    GetConfigValue( wxEmptyString, wxT("Top"), lTop, (long*)&lTop );
    GetConfigValue( wxEmptyString, wxT("Left"), lLeft, (long*)&lLeft );
    GetConfigValue( wxEmptyString, wxT("Height"), lHeight, (long*)&lHeight );
    GetConfigValue( wxEmptyString, wxT("Width"), lWidth, (long*)&lWidth );

    // Correct any problems due to possible resolution change
    //
    if ( lLeft < 0 ) lLeft = 30;
    if ( lTop < 0 ) lTop = 30;
    if ( lTop + lHeight > lMaxHeight ) lTop = lMaxHeight - lHeight - 30;
    if ( lLeft + lWidth > lMaxWidth ) lLeft = lMaxWidth - lWidth - 30;

    // Initialize base class
    //
    Create(
        NULL,
        ID_INTERFACEFRAME,
        _("BOINC-Sentinels-Valkyrie"),
        wxPoint((int)lLeft, (int)lTop),
        wxSize((int)lWidth, (int)lHeight),
        wxDEFAULT_FRAME_STYLE
    );
    
    // Initialize Application
    //
    SetIcons(wxGetApp().GetSkinManager()->GetBOINCSentinelsIcons());

    // Create UI elements
    //
    CreateMenu();
    CreateNotebook();

    // Move everything into place
    //
    Layout();

    // Give time for all the controls to figure out their layout and render
    // properly.  The next step will be to create the pages for the
    // notebook.
    //
    wxCommandEvent evt(wxEVT_INTERFACE_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CInterface - Function End"));
}

CInterface::~CInterface()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::~CInterface - Function Begin"));

    // Unregister with the Event Manager in BOINC Client Library
    // to stop receiving host events.
    wxGetApp().GetState()->UnregisterEventHandler(this, wxEVT_BSLHOST_ADD, NULL, NULL);
    wxGetApp().GetState()->UnregisterEventHandler(this, wxEVT_BSLHOST_DELETE, NULL, NULL);

    // Store window position for future use
    //
    SetConfigValue(wxEmptyString, wxT("Top"), GetPosition().y);
    SetConfigValue(wxEmptyString, wxT("Left"), GetPosition().x);
    SetConfigValue(wxEmptyString, wxT("Height"), GetSize().GetHeight());
    SetConfigValue(wxEmptyString, wxT("Width"), GetSize().GetWidth());

    if (m_pNotebook)
    {
        DeleteNotebook();
    }

    if (m_pMenuBar)
    {
        DeleteMenu();
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::~CInterface - Function End"));
}

bool CInterface::CreateMenu()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CreateMenu - Function Begin"));

    // File menu
    wxMenu *menuFile = new wxMenu;

    menuFile->Append(wxID_EXIT, _("E&xit"), _("Exit BOINC-Sentinels-Valkyrie"));

    // Help menu
    wxMenu *menuHelp = new wxMenu;

    menuHelp->Append(wxID_ABOUT, _("&About BOINC-Sentinels-Valkyrie..."), _("Licensing and copyright information."));

    // construct menu
    m_pMenuBar = new wxMenuBar;
    m_pMenuBar->Append(menuFile, _("&File"));
    m_pMenuBar->Append(menuHelp, _("&Help"));

    SetMenuBar(m_pMenuBar);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CreateMenu - Function End"));
    return true;
}

bool CInterface::CreateNotebook()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CreateNotebook - Function Begin"));

    // Create Frame Sizer
    wxBoxSizer* pFrameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(pFrameSizer);

    // Create Frame Panel
    wxPanel* pPanel = new wxPanel();
    pPanel->Create(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_BORDER);
    pPanel->SetAutoLayout(TRUE);
    pFrameSizer->Add(pPanel, 1, wxEXPAND, 5);

    // Create Frame Panel Sizer
    wxBoxSizer* pPanelSizer = new wxBoxSizer(wxVERTICAL);
    pPanel->SetSizer(pPanelSizer);

    // Create Notebook
    m_pNotebook = new wxNotebook();
    m_pNotebook->Create(pPanel, ID_INTERFACENOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_LEFT | wxCLIP_CHILDREN);
    m_pNotebook->SetImageList(new wxImageList(wxSystemSettings::GetMetric(wxSYS_SMALLICON_X), wxSystemSettings::GetMetric(wxSYS_SMALLICON_Y), true, 0));
    pPanelSizer->Add(m_pNotebook, 1, wxEXPAND);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CreateNotebook - Function End"));
    return true;
}

bool CInterface::DeleteMenu()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeleteMenu - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeleteMenu - Function End"));
    return true;
}

bool CInterface::DeleteNotebook()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeleteNotebook - Function Begin"));

    // Delete all existing pages
    m_pNotebook->DeleteAllPages();

    // Delete all existing images
    wxImageList* pImageList = m_pNotebook->GetImageList();
    if (pImageList)
    {
        pImageList->RemoveAll();
        delete pImageList;
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeleteNotebook - Function End"));
    return true;
}

bool CInterface::GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue)
{
    return wxGetApp().GetConfigManager()->GetConfigValue(wxString(wxT("Interface")), strSubComponent, strValueName, dwDefaultValue, pdwValue);
}

bool CInterface::SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue)
{
    return wxGetApp().GetConfigManager()->SetConfigValue(wxString(wxT("Interface")), strSubComponent, strValueName, dwValue);
}

void CInterface::OnExit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnExit - Function Begin"));

    Close(true);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnExit - Function End"));
}

void CInterface::OnClose(wxCloseEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnClose - Function Begin"));

    Destroy();

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnClose - Function End"));
}

void CInterface::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnAbout - Function Begin"));

    wxAboutDialogInfo info;

    info.SetIcon(wxGetApp().GetSkinManager()->GetBOINCSentinelsIcons().GetIcon(128));
    info.SetName(wxT(PACKAGE_NAME));
    info.SetVersion(wxT(PACKAGE_VERSION));
    info.SetDescription(_("A prototype interface for BOINC to test usability ideas."));
    info.SetCopyright(wxT("Copyright (c) 2009-2014 BOINC Sentinels Development Team"));
    info.SetWebSite(wxT(PACKAGE_URL), wxT("BOINC Sentinels"));
    info.AddDeveloper(wxT("Rom Walton"));
    info.AddDeveloper(wxT("Jorden van der Elst"));
    info.AddArtist(wxT("DryIcons (http://dryicons.com)"));
    info.AddArtist(wxT("LedIcons (http://led24.de)"));

    wxAboutBox(info);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnAbout - Function End"));
}

void CInterface::OnHelp(wxHelpEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHelp - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHelp - Function End"));
}

void CInterface::OnInit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnInit - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();
    CSkinManager* pSkin = wxGetApp().GetSkinManager();
    wxSize oSize = pSkin->GetSmallIconSize();
    wxSortedArrayString astrHosts;
    wxString strHost;
    wxString strPassword;
    wxString strPort;
    wxInt32 rc = 0;
    wxUint32 i = 0;
    long lPort = 0;
    long bConnectOnStartup = 0;

    // Register with the Event Manager in BOINC Client Library
    // to start receiving host events.
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_ADD, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_DELETE, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_CONNECTING, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_CONNECTED, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_DISCONNECTING, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_DISCONNECTED, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_RECONNECTING, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_CONNECTFAILURE, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_AUTHENTICATIONFAILURE, NULL, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLHOST_VERSIONINCOMPATIBLEFAILURE, NULL, NULL);

    // Populate the ImageList with desired icons
    //
    wxImageList* pImageList = m_pNotebook->GetImageList();
    m_iHostIconPosition = pImageList->Add(pSkin->GetHostIcon(oSize));
    m_iHostAddIconPosition = pImageList->Add(pSkin->GetHostAddIcon(oSize));
    m_iHostConnectingIconPosition = pImageList->Add(pSkin->GetHostConnectingIcon(oSize));
    m_iHostConnectedIconPosition = pImageList->Add(pSkin->GetHostConnectedIcon(oSize));
    m_iHostConnectionFailureIconPosition = pImageList->Add(pSkin->GetHostConnectionFailureIcon(oSize));
    m_iHostAuthenticationFailureIconPosition = pImageList->Add(pSkin->GetHostAuthenticationFailureIcon(oSize));
    m_iHostDisconnectedIconPosition = pImageList->Add(pSkin->GetHostDisconnectedIcon(oSize));

    // First page is the status page
    //
    m_pNotebook->AddPage(new CStatusPage(m_pNotebook), wxEmptyString, true, m_iHostAddIconPosition);

    // Add any connections that need to be created on startup
    //
    EnumeratePersistantConnections(&astrHosts);
    if (astrHosts.Count() != 0)
    {
        // One or more connections have been stored, find those we
        // are supposed to start automatically.
        for (i = 0; i < astrHosts.Count(); i++)
        {
            strHost = astrHosts[i];
            rc = GetPersistantConnectionProperties(strHost, &strPassword, &strPort, &bConnectOnStartup);
            if (rc && bConnectOnStartup)
            {
                strPort.ToLong(&lPort);
                AddConnection(strHost, strPassword, lPort);
            }
        }
    }
    else
    {
        // No previous connections have been detected. Check to see if BOINC
        // has been installed locally, if so, ask the user if they want to
        // connect to it automatically.
        if (!wxGetApp().GetBOINCDataDirectory().IsEmpty())
        {
            pState->GetLocalHostName(strHost);
            pState->GetLocalHostPassword(strPassword);
            pState->GetLocalHostPort(lPort);
            strPort.Printf(wxT("%d"), (int)lPort);

            rc = ::wxMessageBox(
                _("BOINC-Sentinels has detected BOINC is installed on this host.\nWould you like to connect to it automatically on startup?"),
                _("BOINC-Sentinels"),
                wxYES_NO | wxICON_QUESTION
            );
            if (wxYES == rc)
            {
                bConnectOnStartup = true;
            }
            else
            {
                bConnectOnStartup = false;
            }

            AddPersistantConnection(strHost, strPassword, strPort, bConnectOnStartup);

            if (wxYES == rc)
            {
                strPort.ToLong(&lPort);
                AddConnection(strHost, strPassword, lPort);
            }
        }
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnInit - Function End"));
}

void CInterface::OnHostAdd(CBSLHostEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAdd - Function Begin"));

    CBSLHost oHost;
    if (BSLERR_SUCCESS == event.GetHost(&oHost))
    {
        m_pNotebook->AddPage(new CClientPage(m_pNotebook, oHost.GetHostHandle()), oHost.GetName(), true, m_iHostIconPosition);
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAdd - Function End"));
}

void CInterface::OnHostDelete(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDelete - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDelete - Function End"));
}

void CInterface::OnHostConnecting(CBSLHostEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnecting - Function Begin"));

    CBSLHost oHost;
    if (BSLERR_SUCCESS == event.GetHost(&oHost))
    {
        for (wxUint32 uiPageIndex = 0; uiPageIndex < m_pNotebook->GetPageCount(); uiPageIndex++)
        {
            if (0 == oHost.GetName().CmpNoCase(m_pNotebook->GetPageText(uiPageIndex)))
            {
                m_pNotebook->SetPageImage(uiPageIndex, m_iHostConnectingIconPosition);
            }
        }
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnecting - Function End"));
}

void CInterface::OnHostConnected(CBSLHostEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnected - Function Begin"));

    CBSLHost oHost;
    if (BSLERR_SUCCESS == event.GetHost(&oHost))
    {
        for (wxUint32 uiPageIndex = 0; uiPageIndex < m_pNotebook->GetPageCount(); uiPageIndex++)
        {
            if (0 == oHost.GetName().CmpNoCase(m_pNotebook->GetPageText(uiPageIndex)))
            {
                m_pNotebook->SetPageImage(uiPageIndex, m_iHostConnectedIconPosition);
            }
        }
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnected - Function End"));
}

void CInterface::OnHostDisconnected(CBSLHostEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDisconnected - Function Begin"));

    CBSLHost oHost;
    if (BSLERR_SUCCESS == event.GetHost(&oHost))
    {
        for (wxUint32 uiPageIndex = 0; uiPageIndex < m_pNotebook->GetPageCount(); uiPageIndex++)
        {
            if (0 == oHost.GetName().CmpNoCase(m_pNotebook->GetPageText(uiPageIndex)))
            {
                m_pNotebook->SetPageImage(uiPageIndex, m_iHostDisconnectedIconPosition);
            }
        }
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDisconnected - Function End"));
}

void CInterface::OnHostConnectionFailure(CBSLHostEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnectionFailure - Function Begin"));

    wxInt32 rc = 0;
    CBSLHost oHost;
    if (BSLERR_SUCCESS == event.GetHost(&oHost))
    {
        for (wxUint32 uiPageIndex = 0; uiPageIndex < m_pNotebook->GetPageCount(); uiPageIndex++)
        {
            if (0 == oHost.GetName().CmpNoCase(m_pNotebook->GetPageText(uiPageIndex)))
            {
                m_pNotebook->SetPageImage(uiPageIndex, m_iHostConnectionFailureIconPosition);
            }
        }

        rc = ::wxMessageBox(
            _("BOINC-Sentinels was unable to connect to the desired host.\nWould you like to try and connect again?"),
            _("BOINC-Sentinels"),
            wxYES_NO | wxICON_QUESTION
        );
        if (wxYES == rc)
        {
            CDlgConnection dlgNewConnection(this);
            dlgNewConnection.SetName(oHost.GetName());
            dlgNewConnection.ShowModal();
        }
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnectionFailure - Function End"));
}

void CInterface::OnHostAuthenticationFailure(CBSLHostEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAuthenticationFailure - Function Begin"));

    CBSLHost oHost;
    if (BSLERR_SUCCESS == event.GetHost(&oHost))
    {
        for (wxUint32 uiPageIndex = 0; uiPageIndex < m_pNotebook->GetPageCount(); uiPageIndex++)
        {
            if (0 == oHost.GetName().CmpNoCase(m_pNotebook->GetPageText(uiPageIndex)))
            {
                m_pNotebook->SetPageImage(uiPageIndex, m_iHostAuthenticationFailureIconPosition);
            }
        }

        CDlgConnection dlgNewConnection(this);
        dlgNewConnection.SetName(oHost.GetName());
        dlgNewConnection.ShowModal();
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAuthenticationFailure - Function End"));
}

void CInterface::OnHostVersionIncompatibleFailure(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostVersionIncompatibleFailure - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostVersionIncompatibleFailure - Function End"));
}

bool CInterface::AddConnection(wxString strName, wxString strPassword, long lPort)
{
    BSLERRCODE rc = wxGetApp().GetState()->Connect(strName, strPassword, lPort, false, NULL);
    return rc == BSLERR_SUCCESS;
}

bool CInterface::AddPersistantConnection(wxString strName, wxString strPassword, wxString strPort,
    long bConnectOnStartup)
{
    bool rc = false, rc2 = false, rc3 = false;

    rc = wxGetApp().GetConfigManager()->SetConfigValue(wxString(wxT("Connections")), strName, wxT("Password"), strPassword);
    rc2 = wxGetApp().GetConfigManager()->SetConfigValue(wxString(wxT("Connections")), strName, wxT("Port"), strPort);
    rc3 = wxGetApp().GetConfigManager()->SetConfigValue(wxString(wxT("Connections")), strName, wxT("ConnectOnStartup"), bConnectOnStartup);

    return ((rc && rc2 && rc3) == true);
}

bool CInterface::DeleteConnection(wxString strName)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeleteConnection - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeleteConnection - Function End"));
    return true;
}

bool CInterface::DeletePersistantConnection(wxString strName)
{
    return wxGetApp().GetConfigManager()->DeleteConfigGroup(wxString(wxT("Connections")), strName);
}

bool CInterface::EnumerateConnections(wxSortedArrayString* pstrNames)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::EnumerateConnections - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::EnumerateConnections - Function End"));
    return true;
}

bool CInterface::EnumeratePersistantConnections(wxSortedArrayString* pstrNames)
{
    return wxGetApp().GetConfigManager()->EnumerateGroups(wxString(wxT("Connections")), wxEmptyString, pstrNames);
}

bool CInterface::GetConnectionProperties(wxString strName, wxString* pstrPassword, long* plPort)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::GetConnectionProperties - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::GetConnectionProperties - Function End"));
    return true;
}

bool CInterface::GetPersistantConnectionProperties(wxString strName, wxString* pstrPassword, wxString* pstrPort, long* pbConnectOnStartup)
{
    bool rc = false, rc2 = false, rc3 = false;

    rc = wxGetApp().GetConfigManager()->GetConfigValue(wxString(wxT("Connections")), strName, wxT("Password"), wxEmptyString, pstrPassword);
    rc2 = wxGetApp().GetConfigManager()->GetConfigValue(wxString(wxT("Connections")), strName, wxT("Port"), wxT("31416"), pstrPort);
    rc3 = wxGetApp().GetConfigManager()->GetConfigValue(wxString(wxT("Connections")), strName, wxT("ConnectOnStartup"), false, pbConnectOnStartup);

    return ((rc && rc2 && rc3) == true);
}

