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
#include "ViewTransfers.h"


#define COLUMN_PROJECT              0
#define COLUMN_FILE                 1
#define COLUMN_PROGRESS             2
#define COLUMN_SIZE                 3
#define COLUMN_TIME                 4
#define COLUMN_SPEED                5
#define COLUMN_STATUS               6

// buttons in the "tasks" area
#define BTN_RETRY       0
#define BTN_ABORT       1


DEFINE_EVENT_TYPE(wxEVT_VIEWTRANSFERS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CViewTransfers, CViewBase);

BEGIN_EVENT_TABLE(CViewTransfers, CViewBase)
END_EVENT_TABLE();

CViewTransfers::CViewTransfers()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CViewTasks::CViewTransfers - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CViewTasks::CViewTransfers - Function End"));
}


CViewTransfers::CViewTransfers(wxNotebook* pNotebook, BSLHOST hHost) :
CViewBase(pNotebook, ID_TASK_TRANSFERSVIEW, DEFAULT_TASK_FLAGS, ID_LIST_TRANSFERSVIEW, DEFAULT_LIST_FLAGS)
{
    CTaskItemGroup* pGroup = NULL;
    CTaskItem*      pItem = NULL;

    //
    // Setup View
    //
    pGroup = new CTaskItemGroup( _("Commands") );
    m_TaskGroups.push_back( pGroup );

    pItem = new CTaskItem(
        _("Retry Now"),
        _("Click 'Retry now' to transfer the file now"),
        ID_TASK_TRANSFERS_RETRYNOW
    );
    pGroup->m_Tasks.push_back( pItem );

    pItem = new CTaskItem(
        _("Abort Transfer"),
        _("Click 'Abort transfer' to delete the file from the transfer queue. This will prevent you from being granted credit for this result."),
        ID_TASK_TRANSFERS_ABORT
    );
    pGroup->m_Tasks.push_back( pItem );


    // Create Task Pane Items
    m_pTaskPane->UpdateControls();

    // Create List Pane Items
    m_pListPane->InsertColumn(COLUMN_PROJECT, _("Project"), wxLIST_FORMAT_LEFT, 125);
    m_pListPane->InsertColumn(COLUMN_FILE, _("File"), wxLIST_FORMAT_LEFT, 205);
    m_pListPane->InsertColumn(COLUMN_PROGRESS, _("Progress"), wxLIST_FORMAT_CENTRE, 60);
    m_pListPane->InsertColumn(COLUMN_SIZE, _("Size"), wxLIST_FORMAT_LEFT, 80);
    m_pListPane->InsertColumn(COLUMN_TIME, _("Elapsed Time"), wxLIST_FORMAT_LEFT, 80);
    m_pListPane->InsertColumn(COLUMN_SPEED, _("Speed"), wxLIST_FORMAT_LEFT, 80);
    m_pListPane->InsertColumn(COLUMN_STATUS, _("Status"), wxLIST_FORMAT_LEFT, 150);

    UpdateSelection();
}


CViewTransfers::~CViewTransfers()
{
    EmptyCache();
    EmptyTasks();
}


wxString& CViewTransfers::GetViewName()
{
    static wxString strViewName(wxT("Transfers"));
    return strViewName;
}


wxString& CViewTransfers::GetViewDisplayName()
{
    static wxString strViewName(_("Transfers"));
    return strViewName;
}


wxImage& CViewTransfers::GetViewIcon()
{
    return wxGetApp().GetSkinManager()->GetTransfersIcon();
}


const int CViewTransfers::GetViewCurrentViewPage()
{
    return 0;
}
