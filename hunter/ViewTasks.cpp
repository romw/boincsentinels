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
//#include "bsconfig.h"
#include "bslxml/bslXMLUtil.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Hunter.h"
#include "ConfigManager.h"
#include "SkinManager.h"
#include "BOINCTaskCtrl.h"
#include "BOINCListCtrl.h"
#include "ViewBase.h"
#include "ViewTasks.h"
#include "Utils.h"


#define COLUMN_PROJECT              0
#define COLUMN_APPLICATION          1
#define COLUMN_NAME                 2
#define COLUMN_CPUTIME              3
#define COLUMN_PROGRESS             4
#define COLUMN_TOCOMPLETION         5
#define COLUMN_REPORTDEADLINE       6
#define COLUMN_STATUS               7

// groups that contain buttons
#define GRP_TASKS    0
#define GRP_WEBSITES 1

// buttons in the "tasks" area
#define BTN_ACTIVE_ONLY             0
#define BTN_GRAPHICS                1
#define BTN_SUSPEND                 2
#define BTN_ABORT                   3
#define BTN_PROPERTIES              4

// Forward Declares
static bool SortProjectAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortProjectDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortApplicationAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortApplicationDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortNameAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortNameDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortCPUTimeAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortCPUTimeDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortProgressAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortProgressDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortToCompletionAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortToCompletionDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortReportDeadlineAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortReportDeadlineDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortStatusAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);
static bool SortStatusDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2);


//
class CViewTaskItem
{
public:
    wxUint32 uiIndex;
    BSLTASKINSTANCE hTaskInstance;
    wxString strProject;
    wxUint32 uiProjectHash;
    wxString strApplication;
    wxUint32 uiApplicationHash;
    wxString strName;
    wxUint32 uiNameHash;
    wxString strCPUTime;
    wxTimeSpan tsCPUTime;
    wxString strProgress;
    wxDouble dProgress;
    wxString strToCompletion;
    wxTimeSpan tsToCompletion;
    wxString strReportDeadline;
    wxDateTime dtReportDeadline;
    wxString strStatus;
    wxUint32 uiStatusHash;
};


DEFINE_EVENT_TYPE(wxEVT_VIEWTASKS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CViewTasks, CViewBase);

BEGIN_EVENT_TABLE(CViewTasks, CViewBase)
    EVT_VIEWTASKS_INIT(CViewTasks::OnInit)
    EVT_LIST_ITEM_SELECTED(ID_LIST_WORKVIEW, CViewTasks::OnListSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LIST_WORKVIEW, CViewTasks::OnListDeselected)
    EVT_LIST_COL_CLICK(ID_LIST_WORKVIEW, CViewTasks::OnColumnClick)
    EVT_LIST_COL_END_DRAG(ID_LIST_WORKVIEW, CViewTasks::OnColumnEndDrag)
    EVT_BSLTASKINSTANCE_BULKADD(CViewTasks::OnTaskInstanceBulkAdd)
    EVT_BSLTASKINSTANCE_BULKUPDATE(CViewTasks::OnTaskInstanceBulkUpdate)
    EVT_BSLTASKINSTANCE_DELETE(CViewTasks::OnTaskInstanceDelete)
END_EVENT_TABLE();

CViewTasks::CViewTasks()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CViewTasks::CViewTasks - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CViewTasks::CViewTasks - Function End"));
}


CViewTasks::CViewTasks(wxNotebook* pNotebook, BSLHOST hHost) :
     CViewBase(pNotebook, ID_TASK_WORKVIEW, DEFAULT_TASK_FLAGS, ID_LIST_WORKVIEW, DEFAULT_LIST_FLAGS)
{
    //
    // Store host handle for future use
    //
    m_hHost = hHost;

    // Initialize List View
    CreateTasks();
    CreateHeaders();

    // Initialize Column Sorting Mechinism
    m_bSortUpdatedColumns.resize(COLUMN_STATUS + 1);

    // Restore State
    RestoreState();

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_VIEWTASKS_INIT);
    AddPendingEvent(evt);
}


CViewTasks::~CViewTasks()
{
    CBSLClient* pState = wxGetApp().GetState();

    // Unregister project events
    pState->UnregisterEventHandler(this, wxEVT_BSLTASKINSTANCE_BULKADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLTASKINSTANCE_BULKUPDATE, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLTASKINSTANCE_DELETE, m_hHost, NULL);

    // Save State
    SaveState();

    // Cleanup List
    if (m_oTaskItems.size())
    {
        for (std::vector<CViewTaskItem*>::iterator iter = m_oTaskItems.begin(); iter != m_oTaskItems.end(); ++iter)
        {
            delete *iter;
        }
        m_oTaskItems.clear();
    }
}


wxString& CViewTasks::GetViewName()
{
    static wxString strViewName(wxT("Tasks"));
    return strViewName;
}


wxString& CViewTasks::GetViewDisplayName()
{
    static wxString strViewName(_("Tasks"));
    return strViewName;
}


wxImage& CViewTasks::GetViewIcon()
{
    return wxGetApp().GetSkinManager()->GetTasksIcon();
}


const int CViewTasks::GetViewCurrentViewPage()
{
    return 0;
}


void CViewTasks::SaveState()
{
    wxListItem liColumnInfo;

    SaveListState();

    m_pListPane->GetColumn(COLUMN_PROJECT, liColumnInfo);
    SaveListColumnState(wxT("Project"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_APPLICATION, liColumnInfo);
    SaveListColumnState(wxT("Application"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_NAME, liColumnInfo);
    SaveListColumnState(wxT("Name"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_CPUTIME, liColumnInfo);
    SaveListColumnState(wxT("Elapsed"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_PROGRESS, liColumnInfo);
    SaveListColumnState(wxT("Progress"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_TOCOMPLETION, liColumnInfo);
    SaveListColumnState(wxT("Remaining (estimated)"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_REPORTDEADLINE, liColumnInfo);
    SaveListColumnState(wxT("Report deadline"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_STATUS, liColumnInfo);
    SaveListColumnState(wxT("Status"), liColumnInfo);
}


void CViewTasks::RestoreState()
{
    wxListItem liColumnInfo;

    liColumnInfo.SetColumn(COLUMN_PROJECT);
    m_pListPane->GetColumn(COLUMN_PROJECT, liColumnInfo);
    RestoreListColumnState(wxT("Project"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_APPLICATION);
    m_pListPane->GetColumn(COLUMN_APPLICATION, liColumnInfo);
    RestoreListColumnState(wxT("Application"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_NAME);
    m_pListPane->GetColumn(COLUMN_NAME, liColumnInfo);
    RestoreListColumnState(wxT("Name"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_CPUTIME);
    m_pListPane->GetColumn(COLUMN_CPUTIME, liColumnInfo);
    RestoreListColumnState(wxT("Elapsed"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_PROGRESS);
    m_pListPane->GetColumn(COLUMN_PROGRESS, liColumnInfo);
    RestoreListColumnState(wxT("Progress"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_TOCOMPLETION);
    m_pListPane->GetColumn(COLUMN_TOCOMPLETION, liColumnInfo);
    RestoreListColumnState(wxT("Remaining (estimated)"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_REPORTDEADLINE);
    m_pListPane->GetColumn(COLUMN_REPORTDEADLINE, liColumnInfo);
    RestoreListColumnState(wxT("Report deadline"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_STATUS);
    m_pListPane->GetColumn(COLUMN_STATUS, liColumnInfo);
    RestoreListColumnState(wxT("Status"), liColumnInfo);

    RestoreListState();
}


void CViewTasks::CreateTasks()
{
    CTaskItemGroup* pGroup = NULL;
    CTaskItem*      pItem = NULL;

    //
    // Setup View
    //
    pGroup = new CTaskItemGroup( _("Commands") );
    m_TaskGroups.push_back( pGroup );

    pItem = new CTaskItem(
        _("Show graphics"),
        _("Show application graphics in a window."),
        ID_TASK_WORK_SHOWGRAPHICS
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Suspend"),
        _("Suspend work for this result."),
        ID_TASK_WORK_SUSPEND
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Abort"),
        _("Abandon work on the result. You will get no credit for it."),
        ID_TASK_WORK_ABORT
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Properties"),
        _("Show task details."),
        ID_TASK_SHOW_PROPERTIES
    );
    pGroup->m_Tasks.push_back( pItem );

    // Create Task Pane Items
    m_pTaskPane->UpdateControls();
}


void CViewTasks::CreateHeaders()
{
    // Create List Pane Items
    m_pListPane->InsertColumn(COLUMN_PROJECT, _("Project"), wxLIST_FORMAT_LEFT, 125);
    m_pListPane->InsertColumn(COLUMN_APPLICATION, _("Application"), wxLIST_FORMAT_LEFT, 95);
    m_pListPane->InsertColumn(COLUMN_NAME, _("Name"), wxLIST_FORMAT_LEFT, 285);
    m_pListPane->InsertColumn(COLUMN_CPUTIME, _("Elapsed"), wxLIST_FORMAT_RIGHT, 80);
    m_pListPane->InsertColumn(COLUMN_PROGRESS, _("Progress"), wxLIST_FORMAT_CENTRE, 60);
    m_pListPane->InsertColumn(COLUMN_TOCOMPLETION, _("Remaining (estimated)"), wxLIST_FORMAT_RIGHT, 100);
    m_pListPane->InsertColumn(COLUMN_REPORTDEADLINE, _("Report deadline"), wxLIST_FORMAT_LEFT, 150);
    m_pListPane->InsertColumn(COLUMN_STATUS, _("Status"), wxLIST_FORMAT_LEFT, 135);
}


void CViewTasks::Sort()
{
    std::vector<CViewTaskItem*> oOriginalSortOrder = m_oTaskItems;

    switch((m_iSortColumn * 10) + m_iSortOrder)
    {
        case ((COLUMN_PROJECT * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortProjectAsc);
            break;
        case ((COLUMN_PROJECT * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortProjectDesc);
            break;
        case ((COLUMN_APPLICATION * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortApplicationAsc);
            break;
        case ((COLUMN_APPLICATION * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortApplicationDesc);
            break;
        case ((COLUMN_NAME * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortNameAsc);
            break;
        case ((COLUMN_NAME * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortNameDesc);
            break;
        case ((COLUMN_CPUTIME * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortCPUTimeAsc);
            break;
        case ((COLUMN_CPUTIME * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortCPUTimeDesc);
            break;
        case ((COLUMN_PROGRESS * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortProgressAsc);
            break;
        case ((COLUMN_PROGRESS * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortProgressDesc);
            break;
        case ((COLUMN_TOCOMPLETION * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortToCompletionAsc);
            break;
        case ((COLUMN_TOCOMPLETION * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortToCompletionDesc);
            break;
        case ((COLUMN_REPORTDEADLINE * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortReportDeadlineAsc);
            break;
        case ((COLUMN_REPORTDEADLINE * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortReportDeadlineDesc);
            break;
        case ((COLUMN_STATUS * 10) + SORT_ASCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortStatusAsc);
            break;
        case ((COLUMN_STATUS * 10) + SORT_DESCENDING):
            std::stable_sort(m_oTaskItems.begin(), m_oTaskItems.end(), SortStatusDesc);
            break;
    }

    size_t count = m_oTaskItems.size();
    for (size_t i = 0; i < count; ++i) {
        if (oOriginalSortOrder[i] != m_oTaskItems[i])
        {
            m_oTaskItems[i]->uiIndex = i;
            m_pListPane->RefreshItem(i);
        }
    }
}


void CViewTasks::UpdateTaskInstance(CViewTaskItem& vtItem, CBSLTaskInstance& bslTaskInstance)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLProject bslProject;
    wxString strTemp = wxEmptyString;
    wxTimeSpan tsTemp;
    wxDouble dTemp;
    wxRect rect;
    wxUint32 count = m_pListPane->GetItemCount();

    pState->GetProject(bslTaskInstance.GetProjectHandle(), &bslProject);

    //
    if (vtItem.strProject.IsEmpty())
    {
        vtItem.strProject = bslProject.GetProjectName();
        vtItem.uiProjectHash = bslProject.GetProjectNameHash();

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_PROJECT, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_PROJECT == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_PROJECT] = true;
    }

    //
    if (vtItem.strApplication.IsEmpty())
    {
        vtItem.strApplication = CUtils::ConstructTaskInstanceAppVersion(bslTaskInstance);
        vtItem.uiApplicationHash = bslXMLStrHash32(vtItem.strApplication);

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_APPLICATION, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_APPLICATION == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_APPLICATION] = true;
    }

    //
    if (vtItem.strName.IsEmpty())
    {
        vtItem.strName = bslTaskInstance.GetName();
        vtItem.uiNameHash = bslTaskInstance.GetNameHash();

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_NAME, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_NAME == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_NAME] = true;
    }

    //
    tsTemp = CUtils::DetermineTaskInstanceCPUTime(bslTaskInstance);
    if (vtItem.tsCPUTime != tsTemp)
    {
        vtItem.tsCPUTime = tsTemp;
        vtItem.strCPUTime = vtItem.tsCPUTime.Format();

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_CPUTIME, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_CPUTIME == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_CPUTIME] = true;
    }

    //
    dTemp = CUtils::DetermineTaskInstancePercentage(bslTaskInstance);
    if (vtItem.dProgress != dTemp)
    {
        vtItem.dProgress = dTemp;
        vtItem.strProgress = CUtils::ConstructTaskInstancePercentage(vtItem.dProgress);

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_PROGRESS, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_PROGRESS == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_PROGRESS] = true;
    }

    //
    if (vtItem.tsToCompletion != bslTaskInstance.GetEstimatedElapsedTimeRemaining())
    {
        vtItem.tsToCompletion = bslTaskInstance.GetEstimatedElapsedTimeRemaining();
        vtItem.strToCompletion = bslTaskInstance.GetEstimatedElapsedTimeRemaining().Format();

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_TOCOMPLETION, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_TOCOMPLETION == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_TOCOMPLETION] = true;
    }

    //
    if (vtItem.strReportDeadline.IsEmpty())
    {
        vtItem.dtReportDeadline = bslTaskInstance.GetReportDeadline();
        vtItem.strReportDeadline = bslTaskInstance.GetReportDeadline().Format();

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_REPORTDEADLINE, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_REPORTDEADLINE == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_REPORTDEADLINE] = true;
    }

    //
    strTemp = CUtils::ConstructTaskInstanceStatus(bslTaskInstance);
    if (strTemp != vtItem.strStatus)
    {
        vtItem.strStatus = strTemp;
        vtItem.uiStatusHash = bslXMLStrHash32(strTemp);

        if (count)
        {
            m_pListPane->GetSubItemRect(vtItem.uiIndex, COLUMN_STATUS, rect, wxLIST_RECT_BOUNDS);
            m_pListPane->RefreshRect(rect);
        }

        if (COLUMN_STATUS == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_STATUS] = true;
    }

}


void CViewTasks::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewTaskItem* pItem = NULL;
    CBSLTaskInstance bslTaskInstance;
    std::vector<BSLTASKINSTANCE> oTaskInstances;

    // Add any projects we know about
    pState->EnumerateTaskInstances(m_hHost, oTaskInstances, false);
    for (std::vector<BSLTASKINSTANCE>::iterator iter = oTaskInstances.begin(); iter != oTaskInstances.end(); iter++)
    {
        pState->GetTaskInstance(*iter, &bslTaskInstance);

        pItem = new CViewTaskItem();
        m_oTaskItems.push_back(pItem);
        pItem->hTaskInstance = bslTaskInstance.GetTaskInstanceHandle();
        pItem->uiIndex = (wxUint32)m_oTaskItems.size() - 1;

        pState->SetTaskInstanceEventData(bslTaskInstance.GetTaskInstanceHandle(), (wxUIntPtr)pItem);

        // Update the content of the list item
        UpdateTaskInstance(*pItem, bslTaskInstance);
    }

    m_pListPane->SetItemCount(m_oTaskItems.size());

    // Register for task instance events
    pState->RegisterEventHandler(this, wxEVT_BSLTASKINSTANCE_BULKADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLTASKINSTANCE_BULKUPDATE, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLTASKINSTANCE_DELETE, m_hHost, NULL);

    // Update Everything
    UpdateSelection();
}


void CViewTasks::OnColumnClick(wxListEvent& event)
{
    CViewBase::OnColumnClick(event);
    Sort();
}


void CViewTasks::OnColumnEndDrag(wxListEvent& event)
{
    SaveState();
}


void CViewTasks::OnTaskInstanceBulkAdd(CBSLTaskInstanceBulkEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewTaskItem* pItem = NULL;
    CBSLTaskInstance bslTaskInstance;
    std::vector<CBSLTaskInstanceEvent> oEventQueue;
    std::vector<CBSLTaskInstanceEvent>::iterator oEventIter;

    oEventQueue = event.GetEvents();
    for (oEventIter = oEventQueue.begin(); oEventIter != oEventQueue.end(); oEventIter++)
    {
        bslTaskInstance.Clear();
        if (BSLERR_SUCCESS == (*oEventIter).GetTaskInstance(&bslTaskInstance))
        {
            pItem = new CViewTaskItem();
            m_oTaskItems.push_back(pItem);
            pItem->hTaskInstance = bslTaskInstance.GetTaskInstanceHandle();
            pItem->uiIndex = (wxUint32)m_oTaskItems.size() - 1;

            pState->SetTaskInstanceEventData(bslTaskInstance.GetTaskInstanceHandle(), (wxUIntPtr)pItem);

            // Update the content of the list item
            UpdateTaskInstance(*pItem, bslTaskInstance);
        }
    }

    if (m_iSortColumn != -1 && m_bSortUpdatedColumns[m_iSortColumn])
    {
        m_bSortUpdatedColumns[m_iSortColumn] = false;
        Sort();
    }

    if (m_pListPane->GetItemCount() != m_oTaskItems.size())
    {
        m_pListPane->SetItemCount(m_oTaskItems.size());
    }

}


void CViewTasks::OnTaskInstanceBulkUpdate(CBSLTaskInstanceBulkEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewTaskItem* pEntry;
    CBSLTaskInstance bslTaskInstance;
    std::vector<CBSLTaskInstanceEvent> oEventQueue;
    std::vector<CBSLTaskInstanceEvent>::iterator oEventIter;

    oEventQueue = event.GetEvents();
    for (oEventIter = oEventQueue.begin(); oEventIter != oEventQueue.end(); oEventIter++)
    {
        bslTaskInstance.Clear();
        if (BSLERR_SUCCESS == (*oEventIter).GetTaskInstance(&bslTaskInstance))
        {
            pState->GetTaskInstanceEventData(bslTaskInstance.GetTaskInstanceHandle(), (wxUIntPtr*)&pEntry);
            if (pEntry)
            {
                UpdateTaskInstance(*pEntry, bslTaskInstance);
            }
        }
    }

    if (m_iSortColumn != -1 && m_bSortUpdatedColumns[m_iSortColumn])
    {
        m_bSortUpdatedColumns[m_iSortColumn] = false;
        Sort();
    }

    if (m_pListPane->GetItemCount() != m_oTaskItems.size())
    {
        m_pListPane->SetItemCount(m_oTaskItems.size());
    }

}


void CViewTasks::OnTaskInstanceDelete(CBSLTaskInstanceEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewTaskItem* pEntry;
    CBSLTaskInstance bslTaskInstance;

    if (BSLERR_SUCCESS == event.GetTaskInstance(&bslTaskInstance))
    {
        pState->GetTaskInstanceEventData(bslTaskInstance.GetTaskInstanceHandle(), (wxUIntPtr*)&pEntry);
        if (pEntry)
        {
            m_oTaskItems.erase(m_oTaskItems.begin() + pEntry->uiIndex);
            delete pEntry;
        }
    }
}


void CViewTasks::OnSelectionChanged(bool bRegister)
{
    CBSLClient* pState = wxGetApp().GetState();
    if (bRegister)
    {
        wxLogTrace(wxT("Function Status"), wxT("CViewTasks::OnSelectionChanged - Registering Task Instance Refresh Cycle"));
        pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyTaskInstancesUpdateInterval, 1);
    }
    else
    {
        wxLogTrace(wxT("Function Status"), wxT("CViewTasks::OnSelectionChanged - Unregistering Task Instance Refresh Cycle"));
        pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyTaskInstancesUpdateInterval, 0);
    }
}


wxString CViewTasks::OnListGetItemText(long item, long column) const {
    switch(column) {
        case COLUMN_PROJECT:
            return m_oTaskItems[item]->strProject;
            break;
        case COLUMN_APPLICATION:
            return m_oTaskItems[item]->strApplication;
            break;
        case COLUMN_NAME:
            return m_oTaskItems[item]->strName;
            break;
        case COLUMN_CPUTIME:
            return m_oTaskItems[item]->strCPUTime;
            break;
        case COLUMN_PROGRESS:
            return m_oTaskItems[item]->strProgress;
            break;
        case COLUMN_TOCOMPLETION:
            return m_oTaskItems[item]->strToCompletion;
            break;
        case COLUMN_REPORTDEADLINE:
            return m_oTaskItems[item]->strReportDeadline;
            break;
        case COLUMN_STATUS:
            return m_oTaskItems[item]->strStatus;
            break;
        default:
            break;
    }
    return wxEmptyString;
}


bool SortProjectAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiProjectHash != pItem2->uiProjectHash)
    {
        rc = (pItem1->strProject < pItem2->strProject);
    }
    return rc;
}

bool SortProjectDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiProjectHash != pItem2->uiProjectHash)
    {
        rc = (pItem1->strProject > pItem2->strProject);
    }
    return rc;
}

bool SortApplicationAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiApplicationHash != pItem2->uiApplicationHash)
    {
        rc = (pItem1->strApplication < pItem2->strApplication);
    }
    return rc;
}

bool SortApplicationDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiApplicationHash != pItem2->uiApplicationHash)
    {
        rc = (pItem1->strApplication > pItem2->strApplication);
    }
    return rc;
}

bool SortNameAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiNameHash != pItem2->uiNameHash)
    {
        rc = (pItem1->strName < pItem2->strName);
    }
    return rc;
}

bool SortNameDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiNameHash != pItem2->uiNameHash)
    {
        rc = (pItem1->strName > pItem2->strName);
    }
    return rc;
}

bool SortCPUTimeAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->tsCPUTime < pItem2->tsCPUTime);
}

bool SortCPUTimeDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->tsCPUTime > pItem2->tsCPUTime);
}

bool SortProgressAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->dProgress < pItem2->dProgress);
}

bool SortProgressDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->dProgress > pItem2->dProgress);
}

bool SortToCompletionAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->tsToCompletion < pItem2->tsToCompletion);
}

bool SortToCompletionDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->tsToCompletion > pItem2->tsToCompletion);
}

bool SortReportDeadlineAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->dtReportDeadline < pItem2->dtReportDeadline);
}

bool SortReportDeadlineDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    return (pItem1->dtReportDeadline > pItem2->dtReportDeadline);
}

bool SortStatusAsc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiStatusHash != pItem2->uiStatusHash)
    {
        rc = (pItem1->strStatus < pItem2->strStatus);
    }
    return rc;
}

bool SortStatusDesc(CViewTaskItem* pItem1, CViewTaskItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiStatusHash != pItem2->uiStatusHash)
    {
        rc = (pItem1->strStatus > pItem2->strStatus);
    }
    return rc;
}

