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
#include "Hunter.h"
#include "ConfigManager.h"
#include "SkinManager.h"
#include "ViewBase.h"
#include "ViewNotifications.h"
#include "ViewProjects.h"
#include "ViewResources.h"
#include "ViewStatistics.h"
#include "ViewTasks.h"
#include "ViewTransfers.h"
#include "Interface.h"


DEFINE_EVENT_TYPE(wxEVT_INTERFACE_INIT);

IMPLEMENT_DYNAMIC_CLASS(CInterface, wxFrame);

BEGIN_EVENT_TABLE(CInterface, wxFrame)
    EVT_MENU(wxID_EXIT, CInterface::OnExit)
    EVT_MENU(wxID_ABOUT, CInterface::OnAbout)
    EVT_HELP(wxID_ANY, CInterface::OnHelp)
    EVT_CLOSE(CInterface::OnClose)
    EVT_INTERFACE_INIT(CInterface::OnInit)
    EVT_NOTEBOOK_PAGE_CHANGED(ID_INTERFACENOTEBOOK, CInterface::OnNotebookSelectionChanged)
    EVT_BSLHOST_ADD(CInterface::OnHostAdd)
    EVT_BSLHOST_DELETE(CInterface::OnHostDelete)
    EVT_BSLHOST_CONNECTING(CInterface::OnHostConnecting)
    EVT_BSLHOST_CONNECTED(CInterface::OnHostConnected)
    EVT_BSLHOST_DISCONNECTING(CInterface::OnHostDisconnecting)
    EVT_BSLHOST_DISCONNECTED(CInterface::OnHostDisconnected)
    EVT_BSLHOST_RECONNECTING(CInterface::OnHostReconnecting)
    EVT_BSLHOST_CONNECTFAILURE(CInterface::OnHostConnectFailure)
    EVT_BSLHOST_AUTHENTICATIONFAILURE(CInterface::OnHostAuthenticationFailure)
    EVT_BSLHOST_VERSIONINCOMPATIBLEFAILURE(CInterface::OnHostVersionIncompatibleFailure)
END_EVENT_TABLE();

CInterface::CInterface()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CInterface - Function Begin"));

    m_pMenuBar = NULL;
    m_pNotebook = NULL;
    m_hHost = NULL;

    long lMaxWidth = wxSystemSettings::GetMetric( wxSYS_SCREEN_X );
    long lMaxHeight = wxSystemSettings::GetMetric( wxSYS_SCREEN_Y );
    long lHeight = 600;
    long lWidth = 800;
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
        _("BOINC-Sentinels-Hunter"),
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

    menuFile->Append(wxID_EXIT, _("E&xit"), _("Exit BOINC-Sentinels-Hunter"));

    // Help menu
    wxMenu *menuHelp = new wxMenu;

    menuHelp->Append(wxID_ABOUT, _("&About BOINC-Sentinels-Hunter..."), _("Licensing and copyright information."));

    // construct menu
    m_pMenuBar = new wxMenuBar;
    m_pMenuBar->Append(menuFile, _("&File"));
    m_pMenuBar->Append(menuHelp, _("&Help"));

    wxMenuBar* m_pOldMenuBar = GetMenuBar();
    SetMenuBar(m_pMenuBar);
    if (m_pOldMenuBar)
    {
        delete m_pOldMenuBar;
    }

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
    pPanel->Create(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_BORDER);
    pPanel->SetAutoLayout(TRUE);
    pFrameSizer->Add(pPanel, 1, wxEXPAND, 5);

    // Create Frame Panel Sizer
    wxBoxSizer* pPanelSizer = new wxBoxSizer(wxVERTICAL);
    pPanel->SetSizer(pPanelSizer);

    // Create Notebook
    m_pNotebook = new wxNotebook();
    m_pNotebook->Create(pPanel, ID_INTERFACENOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_FIXEDWIDTH | wxCLIP_CHILDREN);
    m_pNotebook->SetImageList(new wxImageList(16, 16, true, 0));
    pPanelSizer->Add(m_pNotebook, 1, wxEXPAND);

    // Display default views
    RepopulateNotebook();

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CreateNotebook - Function End"));
    return true;
}

bool CInterface::RepopulateNotebook()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::RepopulateNotebook - Function Begin"));

    DeleteNotebook();

    // Create the various notebook pages
    CreateNotebookPage(new CViewNotifications(m_pNotebook, m_hHost));
    CreateNotebookPage(new CViewProjects(m_pNotebook, m_hHost));
    CreateNotebookPage(new CViewTasks(m_pNotebook, m_hHost));
    CreateNotebookPage(new CViewTransfers(m_pNotebook, m_hHost));
    CreateNotebookPage(new CViewStatistics(m_pNotebook, m_hHost));
    CreateNotebookPage(new CViewResources(m_pNotebook, m_hHost));

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::RepopulateNotebook - Function End"));
    return true;
}

bool CInterface::CreateNotebookPage(CViewBase* pPage)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CreateNotebookPage - Function Begin"));

    wxImageList* pImageList;
    int          iImageIndex = 0;

    wxASSERT(pPage);
    wxASSERT(m_pNotebook);
    wxASSERT(wxDynamicCast(pPage, CViewBase));

    pImageList = m_pNotebook->GetImageList();
    if (!pImageList) {
        pImageList = new wxImageList(16, 16, true, 0);
        wxASSERT(pImageList != NULL);
        m_pNotebook->SetImageList(pImageList);
    }

    iImageIndex = pImageList->Add(wxBitmap(pPage->GetViewIcon()));
    m_pNotebook->AddPage(pPage, pPage->GetViewDisplayName(), TRUE, iImageIndex);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::CreateNotebookPage - Function End"));
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
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeleteNotebook - Function End"));
    return true;
}

bool CInterface::GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue)
{
    return wxGetApp().GetConfigManager()->GetConfigValue(wxT("Interface"), strSubComponent, strValueName, dwDefaultValue, pdwValue);
}

bool CInterface::SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue)
{
    return wxGetApp().GetConfigManager()->SetConfigValue(wxT("Interface"), strSubComponent, strValueName, dwValue);
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
    info.SetWebSite(wxT("https://projects.romwnet.org/boincsentinels"), wxT("BOINC Sentinels"));
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
    wxSortedArrayString astrHosts;
    wxString strHost;
    wxString strPassword;
    wxString strPort;
    wxInt32 rc = 0;
    wxUint32 i = 0;    long lPort = 0;
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
                wxLogTrace(wxT("Function Status"), wxT("CInterface::OnInit - Automatically connecting to '%s'"), strHost.c_str());
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

void CInterface::OnNotebookSelectionChanged(wxNotebookEvent& event) {
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnNotebookSelectionChanged - Function Begin"));

    CViewBase* pView = NULL;

    int iOld = event.GetOldSelection();
    if (iOld != -1)
    {
        pView = (CViewBase*)m_pNotebook->GetPage(iOld);
        pView->FireOnSelectionChanged(false);
    }

    int iNew = event.GetSelection();
    if (iNew != -1)
    {
        pView = (CViewBase*)m_pNotebook->GetPage(iNew);
        pView->FireOnSelectionChanged(true);
    }

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnNotebookSelectionChanged - Function End"));
}

void CInterface::OnHostAdd(CBSLHostEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAdd - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAdd - Function End"));
}

void CInterface::OnHostDelete(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDelete - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDelete - Function End"));
}

void CInterface::OnHostConnecting(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnecting - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnecting - Function End"));
}

void CInterface::OnHostConnected(CBSLHostEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLHost oHost;

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnected - Function Begin"));

    event.GetHost(&oHost);
    SetTitle(_("BOINC-Sentinels-Hunter - ") + oHost.GetName());

    // Setup the refresh cycle for the global state
    pState->SetAutoSyncProperty(oHost.GetHostHandle(), CBSLClient::AutoSyncPropertyStateUpdateInterval, 3600);
    // Setup the refresh cycle for the host status
    pState->SetAutoSyncProperty(oHost.GetHostHandle(), CBSLClient::AutoSyncPropertyHostStatusUpdateInterval, 1);
    // Setup the refresh cycle for tasks tab
    pState->SetAutoSyncProperty(oHost.GetHostHandle(), CBSLClient::AutoSyncPropertyTaskInstancesUpdateInterval, 1);

    // Re-create notebook tabs with the new host handle
    m_hHost = oHost.GetHostHandle();
    RepopulateNotebook();

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnected - Function End"));
}

void CInterface::OnHostDisconnecting(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDisconnecting - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDisconnecting - Function End"));
}

void CInterface::OnHostDisconnected(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDisconnected - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostDisconnected - Function End"));
}

void CInterface::OnHostReconnecting(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostReconnecting - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostReconnecting - Function End"));
}

void CInterface::OnHostConnectFailure(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnectFailure - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostConnectFailure - Function End"));
}

void CInterface::OnHostAuthenticationFailure(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAuthenticationFailure - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostAuthenticationFailure - Function End"));
}

void CInterface::OnHostVersionIncompatibleFailure(CBSLHostEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostVersionIncompatibleFailure - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::OnHostVersionIncompatibleFailure - Function End"));
}

bool CInterface::AddConnection(wxString strName, wxString strPassword, long lPort)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::AddConnection - Function Begin"));

    BSLERRCODE rc = wxGetApp().GetState()->Connect(strName, strPassword, lPort, false, NULL);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::AddConnection - Function End"));
    return rc == BSLERR_SUCCESS;
}

bool CInterface::AddPersistantConnection(wxString strName, wxString strPassword, wxString strPort,
    long bConnectOnStartup)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::AddPersistantConnection - Function Begin"));

    bool rc = false, rc2 = false, rc3 = false;

    rc = wxGetApp().GetConfigManager()->SetConfigValue(wxT("Connections"), strName, wxT("Password"), strPassword);
    rc2 = wxGetApp().GetConfigManager()->SetConfigValue(wxT("Connections"), strName, wxT("Port"), strPort);
    rc3 = wxGetApp().GetConfigManager()->SetConfigValue(wxT("Connections"), strName, wxT("ConnectOnStartup"), bConnectOnStartup);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::AddPersistantConnection - Function End"));
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
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeletePersistantConnection - Function Begin"));

    bool rc = false;

    rc = wxGetApp().GetConfigManager()->DeleteConfigGroup(wxT("Connections"), strName);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::DeletePersistantConnection - Function End"));
    return rc;
}

bool CInterface::EnumerateConnections(wxSortedArrayString* pstrNames)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::EnumerateConnections - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::EnumerateConnections - Function End"));
    return true;
}

bool CInterface::EnumeratePersistantConnections(wxSortedArrayString* pstrNames)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::EnumeratePersistantConnections - Function Begin"));

    bool rc = wxGetApp().GetConfigManager()->EnumerateGroups(wxT("Connections"), wxEmptyString, pstrNames);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::EnumeratePersistantConnections - Function End"));
    return rc;
}

bool CInterface::GetConnectionProperties(wxString strName, wxString* pstrPassword, long* plPort)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::GetConnectionProperties - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::GetConnectionProperties - Function End"));
    return true;
}

bool CInterface::GetPersistantConnectionProperties(wxString strName, wxString* pstrPassword, wxString* pstrPort, long* pbConnectOnStartup)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::GetPersistantConnectionProperties - Function Begin"));

    bool rc = false, rc2 = false, rc3 = false;

    rc = wxGetApp().GetConfigManager()->GetConfigValue(wxT("Connections"), strName, wxT("Password"), wxEmptyString, pstrPassword);
    rc2 = wxGetApp().GetConfigManager()->GetConfigValue(wxT("Connections"), strName, wxT("Port"), wxT("31416"), pstrPort);
    rc3 = wxGetApp().GetConfigManager()->GetConfigValue(wxT("Connections"), strName, wxT("ConnectOnStartup"), false, pbConnectOnStartup);

    wxLogTrace(wxT("Function Start/End"), wxT("CInterface::GetPersistantConnectionProperties - Function End"));
    return ((rc && rc2 && rc3) == true);
}

