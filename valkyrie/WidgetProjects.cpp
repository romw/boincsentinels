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
#include "WidgetProject.h"
#include "WidgetProjects.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETPROJECTS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetProjects, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetProjects, CWidgetBase)
    EVT_WIDGETPROJECTS_INIT(CWidgetProjects::OnInit)
    EVT_WIDGETBASE_SHOWCONTENTS(CWidgetProjects::OnShowContents)
    EVT_WIDGETBASE_HIDECONTENTS(CWidgetProjects::OnHideContents)
    EVT_BUTTON(ID_WIDGETPROJECTSRESUME, CWidgetProjects::OnResumeProjects)
    EVT_BUTTON(ID_WIDGETPROJECTSSUSPEND, CWidgetProjects::OnSuspendProjects)
    EVT_BSLPROJECT_ADD(CWidgetProjects::OnProjectAdd)
    EVT_BSLPROJECT_DELETE(CWidgetProjects::OnProjectDelete)
END_EVENT_TABLE();


bool SortWidgetProject(CWidgetProject* p1, CWidgetProject* p2)
{
    return p1->GetWidgetName().CmpNoCase(p2->GetWidgetName()) < 0;
}


CWidgetProjects::CWidgetProjects()
{
}

CWidgetProjects::CWidgetProjects(wxWindow* pParent, BSLHOST hHost) :
CWidgetBase(pParent, ID_WIDGETPROJECTS, _("Projects"))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetProjects::CWidgetProjects - Function Begin"));

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;

    m_hHost = hHost;

    // Create Controls
    CreateControls(true, false, true);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETPROJECTS_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetProjects::CWidgetProjects - Function End"));
}

CWidgetProjects::~CWidgetProjects()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetProjects::~CWidgetProjects - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();

    // Unregister project events
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_ADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_DELETE, m_hHost, NULL);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetProjects::~CWidgetProjects - Function End"));
}

bool CWidgetProjects::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pAddProjectCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETPROJECTSADD, pSkin->GetProjectAddIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pAddProjectCtrl->SetToolTip(_("Add Project"));
    m_pButtonBarSizer->Add(m_pAddProjectCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pResumeProjectsCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETPROJECTSRESUME, pSkin->GetResumeIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pResumeProjectsCtrl->SetToolTip(_("Resume Projects"));
    m_pButtonBarSizer->Add(m_pResumeProjectsCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pSuspendProjectsCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETPROJECTSSUSPEND, pSkin->GetSuspendIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pSuspendProjectsCtrl->SetToolTip(_("Suspend Projects"));
    m_pButtonBarSizer->Add(m_pSuspendProjectsCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    return true;
}

bool CWidgetProjects::OnCreateContent(wxWindow* pParent, CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    m_pContent = pParent;
    m_pContentSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_pContentSizer->AddGrowableCol(0);
    m_pContent->SetSizer(m_pContentSizer);

    return true;
}

void CWidgetProjects::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    std::vector<BSLPROJECT> oProjects;
    CWidgetProject* pWidgetProject = NULL;

    // Add any projects we know about
    pState->EnumerateProjects(m_hHost, oProjects, false);
    for (std::vector<BSLPROJECT>::iterator iter = oProjects.begin(); iter != oProjects.end(); iter++)
    {
        pWidgetProject = new CWidgetProject(m_pContent, m_hHost, *iter);
        m_Projects.push_back(pWidgetProject);
    }

    // Sort them by name
    std::stable_sort(m_Projects.begin(), m_Projects.end(), SortWidgetProject);

    // Register the now sorted projects with the sizer
    for (std::vector<CWidgetProject*>::iterator iter = m_Projects.begin(); iter != m_Projects.end(); iter++)
    {
        m_pContentSizer->Add(*iter, 0, wxGROW|wxALL, 1);
    }

    // Update the layout
    Layout();

    // Register for project events
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_DELETE, m_hHost, NULL);
}

void CWidgetProjects::OnShowContents(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for projects
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyProjectsUpdateInterval, 1);
}

void CWidgetProjects::OnHideContents(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for projects
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyProjectsUpdateInterval, 0);
}

void CWidgetProjects::OnResumeProjects(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTasks::OnResumeProjects - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTasks::OnResumeProjects - Function End"));
}

void CWidgetProjects::OnSuspendProjects(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetProjects::OnSuspendProjects - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetProjects::OnSuspendProjects - Function End"));
}

void CWidgetProjects::OnProjectAdd(CBSLProjectEvent& event)
{
    CWidgetProject* pWidgetProject = NULL;

    pWidgetProject = new CWidgetProject(m_pContent, event.GetHostHandle(), event.GetProjectHandle());
    m_Projects.push_back(pWidgetProject);

    // Sort them by name
    std::stable_sort(m_Projects.begin(), m_Projects.end(), SortWidgetProject);

    // Delete the old order and re-register the now sorted projects with the sizer
    m_pContentSizer->Clear();
    for (std::vector<CWidgetProject*>::iterator iter = m_Projects.begin(); iter != m_Projects.end(); iter++)
    {
        m_pContentSizer->Add(*iter, 0, wxGROW|wxALL, 1);
    }

    wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
    AddPendingEvent(evt);
}

void CWidgetProjects::OnProjectDelete(CBSLProjectEvent& event)
{
    wxSizerItemList oSizerList;
    CWidgetProject* pWidgetProject = NULL;

    oSizerList = m_pContentSizer->GetChildren();
    for (wxSizerItemList::iterator iter = oSizerList.begin(); iter != oSizerList.end(); iter++)
    {
        pWidgetProject = wxDynamicCast((*iter)->GetWindow(), CWidgetProject);

        if (event.GetProjectHandle() == pWidgetProject->GetProjectHandle())
        {
            m_pContentSizer->Detach(pWidgetProject);
            delete pWidgetProject;
        }
    }

    wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
    AddPendingEvent(evt);
}
