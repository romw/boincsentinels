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
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Hunter.h"
#include "ConfigManager.h"
#include "SkinManager.h"
#include "BOINCTaskCtrl.h"
#include "BOINCListCtrl.h"
#include "ViewBase.h"
#include "ViewStatistics.h"


DEFINE_EVENT_TYPE(wxEVT_VIEWSTATISTICS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CViewStatistics, CViewBase);

BEGIN_EVENT_TABLE(CViewStatistics, CViewBase)
END_EVENT_TABLE();

CViewStatistics::CViewStatistics()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::CViewStatistics - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CViewStatistics::CViewStatistics - Function End"));
}


CViewStatistics::CViewStatistics(wxNotebook* pNotebook, BSLHOST hHost) :
CViewBase(pNotebook)
{
    CTaskItemGroup* pGroup = NULL;
    CTaskItem*      pItem = NULL;

    //
    // Setup View
    //
    wxFlexGridSizer* itemFlexGridSizer = new wxFlexGridSizer(2, 0, 0);
    wxASSERT(itemFlexGridSizer);

    itemFlexGridSizer->AddGrowableRow(0);
    itemFlexGridSizer->AddGrowableCol(1);

    m_pTaskPane = new CBOINCTaskCtrl(this, ID_TASK_STATISTICSVIEW, DEFAULT_TASK_FLAGS);
    wxASSERT(m_pTaskPane);

    m_pStatisticsPanel = new wxPanel(this, ID_LIST_STATISTICSVIEW, wxDefaultPosition, wxSize(-1, -1), 0);
    wxASSERT(m_pStatisticsPanel);

    itemFlexGridSizer->Add(m_pTaskPane, 1, wxGROW|wxALL, 1);
    itemFlexGridSizer->Add(m_pStatisticsPanel, 1, wxGROW|wxALL, 1);

    SetSizer(itemFlexGridSizer);

    Layout();

    pGroup = new CTaskItemGroup( _("Commands") );
    m_TaskGroups.push_back( pGroup );

    pItem = new CTaskItem(
        _("Show user total"),
        _("Show total credit for user"),
        ID_TASK_STATISTICS_USERTOTAL
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Show user average"),
        _("Show average credit for user"),
        ID_TASK_STATISTICS_USERAVERAGE
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Show host total"),
        _("Show total credit for host"),
        ID_TASK_STATISTICS_HOSTTOTAL
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Show host average"),
        _("Show average credit for host"),
        ID_TASK_STATISTICS_HOSTAVERAGE
    );
    pGroup->m_Tasks.push_back( pItem );

    pGroup = new CTaskItemGroup( _("Project") );
    m_TaskGroups.push_back( pGroup );

    pItem = new CTaskItem(
        _("< &Previous project"),
        _("Show chart for previous project"),
        ID_TASK_STATISTICS_PREVPROJECT
    );
    pGroup->m_Tasks.push_back( pItem );
    pItem = new CTaskItem(
        _("&Next project >"),
        _("Show chart for next project"),
        ID_TASK_STATISTICS_NEXTPROJECT
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Hide project list"),
        _("Use entire area for graphs"),
        ID_TASK_STATISTICS_HIDEPROJLIST
    );
    pGroup->m_Tasks.push_back( pItem );

    pGroup = new CTaskItemGroup( _("Mode view") );
    m_TaskGroups.push_back( pGroup );

    pItem = new CTaskItem(
        _("One project"),
        _("Show one chart with selected project"),
        ID_TASK_STATISTICS_MODEVIEWONEPROJECT
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("All projects (separate)"),
        _("Show all projects, one chart per project"),
        ID_TASK_STATISTICS_MODEVIEWALLSEPARATE
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("All projects (together)"),
        _("Show one chart with all projects"),
        ID_TASK_STATISTICS_MODEVIEWALLTOGETHER
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("All projects (sum)"),
        _("Show one chart with sum of projects"),
        ID_TASK_STATISTICS_MODEVIEWSUM
    );
    pGroup->m_Tasks.push_back( pItem );

    // Create Task Pane Items
    m_pTaskPane->UpdateControls();

    UpdateSelection();
}


CViewStatistics::~CViewStatistics()
{
    EmptyCache();
    EmptyTasks();
}


wxString& CViewStatistics::GetViewName()
{
    static wxString strViewName(wxT("Statistics"));
    return strViewName;
}


wxString& CViewStatistics::GetViewDisplayName()
{
    static wxString strViewName(_("Statistics"));
    return strViewName;
}


wxImage& CViewStatistics::GetViewIcon()
{
    return wxGetApp().GetSkinManager()->GetStatisticsIcon();
}


const int CViewStatistics::GetViewRefreshRate()
{
    return 60;
}


const int CViewStatistics::GetViewCurrentViewPage()
{
    return 0;
}

