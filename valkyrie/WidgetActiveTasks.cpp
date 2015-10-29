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
#include "WidgetActiveTask.h"
#include "WidgetActiveTasks.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETACTIVETASKS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetActiveTasks, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetActiveTasks, CWidgetBase)
    EVT_WIDGETACTIVETASKS_INIT(CWidgetActiveTasks::OnInit)
    EVT_WIDGETBASE_SHOWCONTENTS(CWidgetActiveTasks::OnShowContents)
    EVT_WIDGETBASE_HIDECONTENTS(CWidgetActiveTasks::OnHideContents)
    EVT_BUTTON(ID_WIDGETACTIVETASKSRESUMETASKS, CWidgetActiveTasks::OnResumeTasks)
    EVT_BUTTON(ID_WIDGETACTIVETASKSUSPENDTASKS, CWidgetActiveTasks::OnSuspendTasks)
    EVT_BSLHOSTSTATUS_UPDATE(CWidgetActiveTasks::OnHostStatusUpdate)
    EVT_BSLTASKINSTANCE_ADD(CWidgetActiveTasks::OnTaskInstanceAdd)
    EVT_BSLTASKINSTANCE_DELETE(CWidgetActiveTasks::OnTaskInstanceDelete)
END_EVENT_TABLE();


bool SortWidgetActiveTask(CWidgetActiveTask* p1, CWidgetActiveTask* p2)
{
    return p1->GetWidgetName().CmpNoCase(p2->GetWidgetName()) < 0;
}


CWidgetActiveTasks::CWidgetActiveTasks()
{
}

CWidgetActiveTasks::CWidgetActiveTasks(wxWindow* pParent, BSLHOST hHost) :
CWidgetBase(pParent, ID_WIDGETACTIVETASKS, _("Active Tasks"))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTasks::CWidgetActiveTasks - Function Begin"));

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;

    m_hHost = hHost;

    // Create Controls
    CreateControls(true, false, true);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETACTIVETASKS_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTasks::CWidgetActiveTasks - Function End"));
}

CWidgetActiveTasks::~CWidgetActiveTasks()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTasks::~CWidgetActiveTasks - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();

    // Unregister host status events
    pState->UnregisterEventHandler(this, wxEVT_BSLHOSTSTATUS_UPDATE, m_hHost, NULL);

    // Unregister task instance events
    pState->UnregisterEventHandler(this, wxEVT_BSLTASKINSTANCE_ADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLTASKINSTANCE_DELETE, m_hHost, NULL);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTasks::~CWidgetActiveTasks - Function End"));
}

bool CWidgetActiveTasks::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pResumeTasksCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKSRESUMETASKS, pSkin->GetResumeIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pResumeTasksCtrl->SetToolTip(_("Resume Tasks"));
    m_pButtonBarSizer->Add(m_pResumeTasksCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pSuspendTasksCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKSUSPENDTASKS, pSkin->GetSuspendIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pSuspendTasksCtrl->SetToolTip(_("Suspend Tasks"));
    m_pButtonBarSizer->Add(m_pSuspendTasksCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    return true;
}

bool CWidgetActiveTasks::OnCreateContent(wxWindow* pParent, CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    m_pContent = pParent;
    m_pContentSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_pContentSizer->AddGrowableCol(0);
    m_pContent->SetSizer(m_pContentSizer);

    return true;
}

void CWidgetActiveTasks::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLHostStatus bslHostStatus;
    std::vector<BSLTASKINSTANCE> oTaskInstances;
    CWidgetActiveTask* pWidgetActiveTask = NULL;

    // Add any task instances we know about
    pState->EnumerateTaskInstances(m_hHost, oTaskInstances, false);
    for (std::vector<BSLTASKINSTANCE>::iterator iter = oTaskInstances.begin(); iter != oTaskInstances.end(); iter++)
    {
        pWidgetActiveTask = new CWidgetActiveTask(m_pContent, m_hHost, *iter);
        m_ActiveTasks.push_back(pWidgetActiveTask);
    }

    // Sort them by name
    if (2 <= m_ActiveTasks.size())
    {
        std::stable_sort(m_ActiveTasks.begin(), m_ActiveTasks.end(), SortWidgetActiveTask);
    }

    // Register the now sorted projects with the sizer
    for (std::vector<CWidgetActiveTask*>::iterator iter = m_ActiveTasks.begin(); iter != m_ActiveTasks.end(); iter++)
    {
        m_pContentSizer->Add(*iter, 0, wxGROW|wxALL, 1);
    }

    // Determine the initial state of the button bar
    pState->GetHostStatus(m_hHost, &bslHostStatus);
    if (bslHostStatus.GetTaskSuspendReason())
    {
        if (m_pSuspendTasksCtrl->IsShown())
        {
            m_pSuspendTasksCtrl->Hide();
            m_pResumeTasksCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (m_pResumeTasksCtrl->IsShown())
        {
            m_pResumeTasksCtrl->Hide();
            m_pSuspendTasksCtrl->Show();
            UpdateHeaderLayout();
        }
    }

    // Update the layout
    Layout();

    // Register for host status events
    pState->RegisterEventHandler(this, wxEVT_BSLHOSTSTATUS_UPDATE, m_hHost, NULL);

    // Register for task instance events
    pState->RegisterEventHandler(this, wxEVT_BSLTASKINSTANCE_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLTASKINSTANCE_DELETE, m_hHost, NULL);
}

void CWidgetActiveTasks::OnShowContents(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for task instances
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyTaskInstancesUpdateInterval, 1);
}

void CWidgetActiveTasks::OnHideContents(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for task instances
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyTaskInstancesUpdateInterval, 0);
}

void CWidgetActiveTasks::OnResumeTasks(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->SetModeCPU(m_hHost, CBSLClient::SetModeAlways, 0);
}

void CWidgetActiveTasks::OnSuspendTasks(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->SetModeCPU(m_hHost, CBSLClient::SetModeNever, 0);
}

void CWidgetActiveTasks::OnHostStatusUpdate(CBSLHostStatusEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLHostStatus bslHostStatus;

    pState->GetHostStatus(event.GetHostHandle(), &bslHostStatus);

    if (bslHostStatus.GetTaskSuspendReason())
    {
        if (m_pSuspendTasksCtrl->IsShown())
        {
            m_pSuspendTasksCtrl->Hide();
            m_pResumeTasksCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (m_pResumeTasksCtrl->IsShown())
        {
            m_pResumeTasksCtrl->Hide();
            m_pSuspendTasksCtrl->Show();
            UpdateHeaderLayout();
        }
    }
}

void CWidgetActiveTasks::OnTaskInstanceAdd(CBSLTaskInstanceEvent& event)
{
    CWidgetActiveTask* pWidgetActiveTask = NULL;

    pWidgetActiveTask = new CWidgetActiveTask(m_pContent, event.GetHostHandle(), event.GetTaskInstanceHandle());
    m_ActiveTasks.push_back(pWidgetActiveTask);

    // Sort them by name
    if (2 <= m_ActiveTasks.size())
    {
        std::stable_sort(m_ActiveTasks.begin(), m_ActiveTasks.end(), SortWidgetActiveTask);
    }

    // Delete the old order and re-register the now sorted projects with the sizer
    m_pContentSizer->Clear();
    for (std::vector<CWidgetActiveTask*>::iterator iter = m_ActiveTasks.begin(); iter != m_ActiveTasks.end(); iter++)
    {
        m_pContentSizer->Add(*iter, 0, wxGROW|wxALL, 1);
    }

    wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
    AddPendingEvent(evt);
}

void CWidgetActiveTasks::OnTaskInstanceDelete(CBSLTaskInstanceEvent& event)
{
    CWidgetActiveTask* pWidgetActiveTask = NULL;

    std::vector<CWidgetActiveTask*>::iterator iterActiveTaskWindows = m_ActiveTasks.begin();
    while (iterActiveTaskWindows != m_ActiveTasks.end())
    {
        pWidgetActiveTask = wxDynamicCast(*iterActiveTaskWindows, CWidgetActiveTask);
        if (event.GetTaskInstanceHandle() == pWidgetActiveTask->GetTaskInstanceHandle())
        {
            iterActiveTaskWindows = m_ActiveTasks.erase(iterActiveTaskWindows);
            m_pContentSizer->Detach(pWidgetActiveTask);
            delete pWidgetActiveTask;
        }
        else
        {
            iterActiveTaskWindows++;
        }
    }

    wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
    AddPendingEvent(evt);
}
