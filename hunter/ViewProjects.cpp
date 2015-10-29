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
#include "Utils.h"
#include "ViewBase.h"
#include "ViewProjects.h"


#define COLUMN_PROJECT              0
#define COLUMN_USERNAME             1
#define COLUMN_TEAMNAME             2
#define COLUMN_TOTALCREDIT          3
#define COLUMN_AVGCREDIT            4
#define COLUMN_RESOURCESHARE        5
#define COLUMN_STATUS               6

// groups that contain buttons
#define GRP_TASKS    0
#define GRP_WEBSITES 1

// buttons in the "tasks" area
#define BTN_UPDATE       0
#define BTN_SUSPEND      1
#define BTN_NOWORK       2
#define BTN_RESET        3
#define BTN_DETACH       4
#define BTN_PROPERTIES   5

// Forward Declares
static bool SortProjectAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortProjectDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortUserNameAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortUserNameDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortTeamNameAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortTeamNameDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortTotalCreditAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortTotalCreditDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortAverageCreditAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortAverageCreditDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortResourceShareAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortResourceShareDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortStatusAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);
static bool SortStatusDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2);


//
class CViewProjectItem
{
public:
    wxUint32 uiIndex;
    BSLPROJECT hProject;
    wxString strProject;
    wxUint32 uiProjectHash;
    wxString strUserName;
    wxUint32 uiUserNameHash;
    wxString strTeamName;
    wxUint32 uiTeamNameHash;
    wxString strTotalCredit;
    wxDouble dTotalCredit;
    wxString strAverageCredit;
    wxDouble dAverageCredit;
    wxString strResourceShare;
    wxUint32 uiResourceShare;
    wxString strStatus;
    wxUint32 uiStatusHash;
};


DEFINE_EVENT_TYPE(wxEVT_VIEWPROJECTS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CViewProjects, CViewBase);

BEGIN_EVENT_TABLE(CViewProjects, CViewBase)
    EVT_VIEWPROJECTS_INIT(CViewProjects::OnInit)
    //EVT_BUTTON(ID_TASK_PROJECT_UPDATE, CViewProjects::OnUpdateClick)
    //EVT_BUTTON(ID_TASK_PROJECT_SUSPEND, CViewProjects::OnSuspendClick)
    //EVT_BUTTON(ID_TASK_PROJECT_NONEWWORK, CViewProjects::OnNoNewWorkClick)
    //EVT_BUTTON(ID_TASK_PROJECT_RESET, CViewProjects::OnResetClick)
    //EVT_BUTTON(ID_TASK_PROJECT_DETACH, CViewProjects::OnDetachClick)
    //EVT_BUTTON(ID_TASK_PROJECT_SHOW_PROPERTIES, CViewProjects::OnPropertiesClick)
    //EVT_CUSTOM_RANGE(wxEVT_COMMAND_BUTTON_CLICKED, ID_TASK_PROJECT_WEB_PROJDEF_MIN, ID_TASK_PROJECT_WEB_PROJDEF_MAX, CViewProjects::OnWebsiteClick)
    EVT_LIST_ITEM_SELECTED(ID_LIST_PROJECTSVIEW, CViewProjects::OnListSelected)
    EVT_LIST_ITEM_DESELECTED(ID_LIST_PROJECTSVIEW, CViewProjects::OnListDeselected)
    EVT_LIST_COL_CLICK(ID_LIST_PROJECTSVIEW, CViewProjects::OnColumnClick)
    EVT_LIST_COL_END_DRAG(ID_LIST_PROJECTSVIEW, CViewProjects::OnColumnEndDrag)
    EVT_BSLPROJECT_BULKADD(CViewProjects::OnProjectBulkAdd)
    EVT_BSLPROJECT_BULKUPDATE(CViewProjects::OnProjectBulkUpdate)
    EVT_BSLPROJECT_DELETE(CViewProjects::OnProjectDelete)
END_EVENT_TABLE();

CViewProjects::CViewProjects()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CViewProjects::CViewProjects - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CViewProjects::CViewProjects - Function End"));
}

CViewProjects::CViewProjects(wxNotebook* pNotebook, BSLHOST hHost) :
CViewBase(pNotebook, ID_TASK_PROJECTSVIEW, DEFAULT_TASK_FLAGS, ID_LIST_PROJECTSVIEW, DEFAULT_LIST_FLAGS)
{
    wxASSERT(m_pTaskPane);
    wxASSERT(m_pListPane);

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
    wxCommandEvent evt(wxEVT_VIEWPROJECTS_INIT);
    AddPendingEvent(evt);
}

CViewProjects::~CViewProjects()
{
    CBSLClient* pState = wxGetApp().GetState();

    // Unregister project events
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_BULKADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_BULKUPDATE, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_DELETE, m_hHost, NULL);

    // Save State
    SaveState();

    // Cleanup List
    if (m_oProjectItems.size())
    {
        for (std::vector<CViewProjectItem*>::iterator iter = m_oProjectItems.begin(); iter != m_oProjectItems.end(); ++iter)
        {
            delete *iter;
        }
        m_oProjectItems.clear();
    }
}

wxString& CViewProjects::GetViewName()
{
    static wxString strViewName(wxT("Projects"));
    return strViewName;
}


wxString& CViewProjects::GetViewDisplayName()
{
    static wxString strViewName(_("Projects"));
    return strViewName;
}


wxImage& CViewProjects::GetViewIcon()
{
    return wxGetApp().GetSkinManager()->GetProjectsIcon();
}


const int CViewProjects::GetViewCurrentViewPage()
{
    return 0;
}


void CViewProjects::SaveState()
{
    wxListItem liColumnInfo;

    SaveListState();

    m_pListPane->GetColumn(COLUMN_PROJECT, liColumnInfo);
    SaveListColumnState(wxT("Project"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_USERNAME, liColumnInfo);
    SaveListColumnState(wxT("Account"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_TEAMNAME, liColumnInfo);
    SaveListColumnState(wxT("Team"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_TOTALCREDIT, liColumnInfo);
    SaveListColumnState(wxT("Work done"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_AVGCREDIT, liColumnInfo);
    SaveListColumnState(wxT("Avg. work done"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_RESOURCESHARE, liColumnInfo);
    SaveListColumnState(wxT("Resource share"), liColumnInfo);

    m_pListPane->GetColumn(COLUMN_STATUS, liColumnInfo);
    SaveListColumnState(wxT("Status"), liColumnInfo);
}


void CViewProjects::RestoreState()
{
    wxListItem liColumnInfo;
 
    liColumnInfo.SetColumn(COLUMN_PROJECT);
    m_pListPane->GetColumn(COLUMN_PROJECT, liColumnInfo);
    RestoreListColumnState(wxT("Project"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_USERNAME);
    m_pListPane->GetColumn(COLUMN_USERNAME, liColumnInfo);
    RestoreListColumnState(wxT("Account"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_TEAMNAME);
    m_pListPane->GetColumn(COLUMN_TEAMNAME, liColumnInfo);
    RestoreListColumnState(wxT("Team"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_TOTALCREDIT);
    m_pListPane->GetColumn(COLUMN_TOTALCREDIT, liColumnInfo);
    RestoreListColumnState(wxT("Work done"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_AVGCREDIT);
    m_pListPane->GetColumn(COLUMN_AVGCREDIT, liColumnInfo);
    RestoreListColumnState(wxT("Avg. work done"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_RESOURCESHARE);
    m_pListPane->GetColumn(COLUMN_RESOURCESHARE, liColumnInfo);
    RestoreListColumnState(wxT("Resource share"), liColumnInfo);

    liColumnInfo.SetColumn(COLUMN_STATUS);
    m_pListPane->GetColumn(COLUMN_STATUS, liColumnInfo);
    RestoreListColumnState(wxT("Status"), liColumnInfo);

    RestoreListState();
}


void CViewProjects::CreateTasks()
{
    CTaskItemGroup* pGroup = NULL;
    CTaskItem*      pItem = NULL;

    //
    // Setup View
    //
    pGroup = new CTaskItemGroup( _("Commands") );
    m_TaskGroups.push_back( pGroup );

    pItem = new CTaskItem(
        _("Update"),
        _("Report all completed tasks, get latest credit, get latest preferences, and possibly get more tasks."),
        ID_TASK_PROJECT_UPDATE
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Suspend"),
        _("Suspend tasks for this project."),
        ID_TASK_PROJECT_SUSPEND
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("No new tasks"),
        _("Don't get new tasks for this project."),
        ID_TASK_PROJECT_NONEWWORK
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Reset project"),
        _("Delete all files and tasks associated with this project, and get new tasks.  You can update the project first to report any completed tasks."),
        ID_TASK_PROJECT_RESET
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Remove"),
        _("Remove this project.  Tasks in progress will be lost (use 'Update' first to report any completed tasks)."),
        ID_TASK_PROJECT_DETACH
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Properties"),
        _("Show project details."),
        ID_TASK_PROJECT_SHOW_PROPERTIES
    );
    pGroup->m_Tasks.push_back( pItem );

    // Create Task Pane Items
    m_pTaskPane->UpdateControls();
}


void CViewProjects::CreateHeaders()
{
    // Create List Pane Items
    m_pListPane->InsertColumn(COLUMN_PROJECT, _("Project"), wxLIST_FORMAT_LEFT, 150);
    m_pListPane->InsertColumn(COLUMN_USERNAME, _("Account"), wxLIST_FORMAT_LEFT, 80);
    m_pListPane->InsertColumn(COLUMN_TEAMNAME, _("Team"), wxLIST_FORMAT_LEFT, 80);
    m_pListPane->InsertColumn(COLUMN_TOTALCREDIT, _("Work done"), wxLIST_FORMAT_RIGHT, 80);
    m_pListPane->InsertColumn(COLUMN_AVGCREDIT, _("Avg. work done"), wxLIST_FORMAT_RIGHT, 80);
    m_pListPane->InsertColumn(COLUMN_RESOURCESHARE, _("Resource share"), wxLIST_FORMAT_CENTRE, 85);
    m_pListPane->InsertColumn(COLUMN_STATUS, _("Status"), wxLIST_FORMAT_LEFT, 150);
}


void CViewProjects::Sort()
{
    std::vector<CViewProjectItem*> oOriginalSortOrder = m_oProjectItems;

    switch((m_iSortColumn * 10) + m_iSortOrder)
    {
        case ((COLUMN_PROJECT * 10) + SORT_ASCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortProjectAsc);
            break;
        case ((COLUMN_PROJECT * 10) + SORT_DESCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortProjectDesc);
            break;
        case ((COLUMN_USERNAME * 10) + SORT_ASCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortUserNameAsc);
            break;
        case ((COLUMN_USERNAME * 10) + SORT_DESCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortUserNameDesc);
            break;
        case ((COLUMN_TEAMNAME * 10) + SORT_ASCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortTeamNameAsc);
            break;
        case ((COLUMN_TEAMNAME * 10) + SORT_DESCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortTeamNameDesc);
            break;
        case ((COLUMN_TOTALCREDIT * 10) + SORT_ASCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortTotalCreditAsc);
            break;
        case ((COLUMN_TOTALCREDIT * 10) + SORT_DESCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortTotalCreditDesc);
            break;
        case ((COLUMN_AVGCREDIT * 10) + SORT_ASCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortAverageCreditAsc);
            break;
        case ((COLUMN_AVGCREDIT * 10) + SORT_DESCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortAverageCreditDesc);
            break;
        case ((COLUMN_STATUS * 10) + SORT_ASCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortStatusAsc);
            break;
        case ((COLUMN_STATUS * 10) + SORT_DESCENDING):
            std::stable_sort(m_oProjectItems.begin(), m_oProjectItems.end(), SortStatusDesc);
            break;
    }

    size_t count = m_oProjectItems.size();
    for (size_t i = 0; i < count; ++i) {
        if (oOriginalSortOrder[i] != m_oProjectItems[i])
        {
            m_oProjectItems[i]->uiIndex = i;
            m_pListPane->RefreshItem(i);
        }
    }
}


void CViewProjects::UpdateProject(CViewProjectItem& vpItem, CBSLProject& bslProject)
{
    wxString strTemp = wxEmptyString;

    //
    if (vpItem.strProject.IsEmpty())
    {
        vpItem.strProject = bslProject.GetProjectName();
        vpItem.uiProjectHash = bslProject.GetProjectNameHash();
        if (COLUMN_PROJECT == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_PROJECT] = true;
    }

    //
    if (vpItem.uiUserNameHash != bslProject.GetUserNameHash())
    {
        vpItem.strUserName = bslProject.GetUserName();
        vpItem.uiUserNameHash = bslProject.GetUserNameHash();
        if (COLUMN_USERNAME == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_USERNAME] = true;
    }

    //
    if (vpItem.uiTeamNameHash != bslProject.GetTeamNameHash())
    {
        vpItem.strTeamName = bslProject.GetTeamName();
        vpItem.uiTeamNameHash = bslProject.GetTeamNameHash();
        if (COLUMN_TEAMNAME == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_TEAMNAME] = true;
    }

    //
    if (vpItem.dTotalCredit != bslProject.GetCreditUserTotal())
    {
        vpItem.strTotalCredit = CUtils::ConstructProjectTotalCredit(bslProject);
        vpItem.dTotalCredit = bslProject.GetCreditUserTotal();
        if (COLUMN_TOTALCREDIT == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_TOTALCREDIT] = true;
    }

    //
    if (vpItem.dAverageCredit != bslProject.GetCreditUserAverage())
    {
        vpItem.strAverageCredit = CUtils::ConstructProjectAverageCredit(bslProject);
        vpItem.dAverageCredit = bslProject.GetCreditUserAverage();
        if (COLUMN_AVGCREDIT == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_AVGCREDIT] = true;
    }

    //
    if (vpItem.uiResourceShare != bslProject.GetResourceShare())
    {
        vpItem.strResourceShare = CUtils::ConstructProjectResourceShare(bslProject);
        vpItem.uiResourceShare = bslProject.GetResourceShare();
        if (COLUMN_RESOURCESHARE == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_RESOURCESHARE] = true;
    }

    //
    strTemp = CUtils::ConstructProjectStatus(bslProject);
    if (strTemp != vpItem.strStatus)
    {
        vpItem.strStatus = strTemp;
        vpItem.uiStatusHash = bslXMLStrHash32(strTemp);
        if (COLUMN_STATUS == m_iSortColumn) m_bSortUpdatedColumns[COLUMN_STATUS] = true;
    }

    //
    m_pListPane->RefreshItem(vpItem.uiIndex);
}


void CViewProjects::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewProjectItem* pItem = NULL;
    CBSLProject bslProject;
    std::vector<BSLPROJECT> oProjects;

    // Add any projects we know about
    pState->EnumerateProjects(m_hHost, oProjects, false);
    for (std::vector<BSLPROJECT>::iterator iter = oProjects.begin(); iter != oProjects.end(); iter++)
    {
        pState->GetProject(*iter, &bslProject);

        pItem = new CViewProjectItem();
        m_oProjectItems.push_back(pItem);
        pItem->hProject = bslProject.GetProjectHandle();
        pItem->uiIndex = (wxUint32)m_oProjectItems.size() - 1;

        pState->SetProjectEventData(bslProject.GetProjectHandle(), (wxUIntPtr)pItem);

        // Update the content of the list item
        UpdateProject(*pItem, bslProject);
    }

    m_pListPane->SetItemCount(m_oProjectItems.size());

    // Register for project events
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_BULKADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_BULKUPDATE, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_DELETE, m_hHost, NULL);

    // Update Everything
    UpdateSelection();
}


void CViewProjects::OnColumnClick(wxListEvent& event)
{
    CViewBase::OnColumnClick(event);
    Sort();
}


void CViewProjects::OnColumnEndDrag(wxListEvent& event)
{
    SaveState();
}


void CViewProjects::OnProjectBulkAdd(CBSLProjectBulkEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewProjectItem* pItem = NULL;
    CBSLProject bslProject;
    std::vector<CBSLProjectEvent> oEventQueue;
    std::vector<CBSLProjectEvent>::iterator oEventIter;

    oEventQueue = event.GetEvents();
    for (oEventIter = oEventQueue.begin(); oEventIter != oEventQueue.end(); oEventIter++)
    {
        if (BSLERR_SUCCESS == (*oEventIter).GetProject(&bslProject))
        {
            pItem = new CViewProjectItem();
            m_oProjectItems.push_back(pItem);
            pItem->hProject = bslProject.GetProjectHandle();
            pItem->uiIndex = (wxUint32)m_oProjectItems.size() - 1;

            pState->SetProjectEventData(bslProject.GetProjectHandle(), (wxUIntPtr)pItem);

            // Update the content of the list item
            UpdateProject(*pItem, bslProject);
        }
    }
}


void CViewProjects::OnProjectBulkUpdate(CBSLProjectBulkEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewProjectItem* pEntry;
    CBSLProject bslProject;
    std::vector<CBSLProjectEvent> oEventQueue;
    std::vector<CBSLProjectEvent>::iterator oEventIter;

    oEventQueue = event.GetEvents();
    for (oEventIter = oEventQueue.begin(); oEventIter != oEventQueue.end(); oEventIter++)
    {
        if (BSLERR_SUCCESS == (*oEventIter).GetProject(&bslProject))
        {
            pState->GetProjectEventData(bslProject.GetProjectHandle(), (wxUIntPtr*)&pEntry);
            if (pEntry)
            {
                UpdateProject(*pEntry, bslProject);
            }
        }
    }

    if (m_iSortColumn != -1 && m_bSortUpdatedColumns[m_iSortColumn])
    {
        m_bSortUpdatedColumns[m_iSortColumn] = false;
        Sort();
    }

    if (m_pListPane->GetItemCount() != m_oProjectItems.size())
    {
        m_pListPane->SetItemCount(m_oProjectItems.size());
    }

    // Update Everything
    UpdateSelection();
}


void CViewProjects::OnProjectDelete(CBSLProjectEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CViewProjectItem* pEntry;
    CBSLProject bslProject;

    if (BSLERR_SUCCESS == event.GetProject(&bslProject))
    {
        pState->GetProjectEventData(bslProject.GetProjectHandle(), (wxUIntPtr*)&pEntry);
        if (pEntry)
        {
            m_oProjectItems.erase(m_oProjectItems.begin() + pEntry->uiIndex);
            delete pEntry;
        }
    }
}


void CViewProjects::OnSelectionChanged(bool bRegister)
{
    CBSLClient* pState = wxGetApp().GetState();
    if (bRegister)
    {
        wxLogTrace(wxT("Function Status"), wxT("CViewProjects::OnSelectionChanged - Registering Project Refresh Cycle"));
        pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyProjectsUpdateInterval, 1);
    }
    else
    {
        wxLogTrace(wxT("Function Status"), wxT("CViewProjects::OnSelectionChanged - Unregistering Project Refresh Cycle"));
        pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyProjectsUpdateInterval, 0);
    }
}


wxString CViewProjects::OnListGetItemText(long item, long column) const {
    switch(column) {
        case COLUMN_PROJECT:
            return m_oProjectItems[item]->strProject;
            break;
        case COLUMN_USERNAME:
            return m_oProjectItems[item]->strUserName;
            break;
        case COLUMN_TEAMNAME:
            return m_oProjectItems[item]->strTeamName;
            break;
        case COLUMN_TOTALCREDIT:
            return m_oProjectItems[item]->strTotalCredit;
            break;
        case COLUMN_AVGCREDIT:
            return m_oProjectItems[item]->strAverageCredit;
            break;
        case COLUMN_RESOURCESHARE:
            return m_oProjectItems[item]->strResourceShare;
            break;
        case COLUMN_STATUS:
            return m_oProjectItems[item]->strStatus;
            break;
        default:
            break;
    }
    return wxEmptyString;
}


bool SortProjectAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiProjectHash != pItem2->uiProjectHash)
    {
        rc = (pItem1->strProject < pItem2->strProject);
    }
    return rc;
}

bool SortProjectDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiProjectHash != pItem2->uiProjectHash)
    {
        rc = (pItem1->strProject > pItem2->strProject);
    }
    return rc;
}

bool SortUserNameAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiUserNameHash != pItem2->uiUserNameHash)
    {
        rc = (pItem1->strUserName < pItem2->strUserName);
    }
    return rc;
}

bool SortUserNameDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiUserNameHash != pItem2->uiUserNameHash)
    {
        rc = (pItem1->strUserName > pItem2->strUserName);
    }
    return rc;
}

bool SortTeamNameAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiTeamNameHash != pItem2->uiTeamNameHash)
    {
        rc = (pItem1->strTeamName < pItem2->strTeamName);
    }
    return rc;
}

bool SortTeamNameDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiTeamNameHash != pItem2->uiTeamNameHash)
    {
        rc = (pItem1->strTeamName > pItem2->strTeamName);
    }
    return rc;
}

bool SortTotalCreditAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    return (pItem1->dTotalCredit < pItem2->dTotalCredit);
}

bool SortTotalCreditDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    return (pItem1->dTotalCredit > pItem2->dTotalCredit);
}

bool SortAverageCreditAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    return (pItem1->dAverageCredit < pItem2->dAverageCredit);
}

bool SortAverageCreditDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    return (pItem1->dAverageCredit > pItem2->dAverageCredit);
}

bool SortResourceShareAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    return (pItem1->uiResourceShare < pItem2->uiResourceShare);
}

bool SortResourceShareDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    return (pItem1->uiResourceShare > pItem2->uiResourceShare);
}

bool SortStatusAsc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiStatusHash != pItem2->uiStatusHash)
    {
        rc = (pItem1->strStatus < pItem2->strStatus);
    }
    return rc;
}

bool SortStatusDesc(CViewProjectItem* pItem1, CViewProjectItem* pItem2)
{
    bool rc = false;
    if (pItem1->uiStatusHash != pItem2->uiStatusHash)
    {
        rc = (pItem1->strStatus > pItem2->strStatus);
    }
    return rc;
}
