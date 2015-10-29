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


DEFINE_EVENT_TYPE(wxEVT_VIEWBASE_INIT);


IMPLEMENT_DYNAMIC_CLASS(CViewBase, wxSplitterWindow);

BEGIN_EVENT_TABLE(CViewBase, wxSplitterWindow)
    EVT_VIEWBASE_INIT(CViewBase::OnViewBaseInit)
END_EVENT_TABLE();


CViewBase::CViewBase()
{
}


CViewBase::CViewBase(wxNotebook* pNotebook) :
wxSplitterWindow(pNotebook, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)
{
    wxASSERT(pNotebook);

    //
    // Setup View
    //
    m_pTaskPane = NULL;
    m_pListPane = NULL;

    SetName(GetViewName());

    SetAutoLayout(TRUE);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_VIEWBASE_INIT);
    AddPendingEvent(evt);
}


CViewBase::CViewBase( wxNotebook* pNotebook, wxWindowID iTaskWindowID, int iTaskWindowFlags, wxWindowID iListWindowID, int iListWindowFlags ) :
wxSplitterWindow(pNotebook, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)
{
    wxASSERT(pNotebook);

    //
    // Setup View
    //
    m_pTaskPane = NULL;
    m_pListPane = NULL;
    m_bForceUpdateSelection = true;
    m_iSortColumn = -1;
    m_iSortOrder = SORT_ASCENDING;

    SetName(GetViewName());

    SetAutoLayout(TRUE);

    m_pTaskPane = new CBOINCTaskCtrl(this, iTaskWindowID, iTaskWindowFlags);
    wxASSERT(m_pTaskPane);

    m_pListPane = new CBOINCListCtrl(this, iListWindowID, iListWindowFlags);
    wxASSERT(m_pListPane);

    wxImageList* pImageList = new wxImageList(16, 16, true);
    pImageList->Add( wxGetApp().GetSkinManager()->GetSortAscendingIcon() );
    pImageList->Add( wxGetApp().GetSkinManager()->GetSortDescendingIcon() );
    m_pListPane->SetImageList(pImageList, wxIMAGE_LIST_SMALL);

    SplitVertically(m_pTaskPane, m_pListPane, 210);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_VIEWBASE_INIT);
    AddPendingEvent(evt);
}


CViewBase::~CViewBase()
{
    if (m_pListPane)
    {
        // Delete all existing images
        wxImageList* pImageList = m_pListPane->GetImageList(wxIMAGE_LIST_SMALL);
        if (pImageList)
        {
            pImageList->RemoveAll();
        }
    }

    EmptyTasks();
}


// The name of the view.
//   If it has not been defined by the view "Undefined" is returned.
//
wxString& CViewBase::GetViewName()
{
    static wxString strViewName(wxT("Undefined"));
    return strViewName;
}


// The user friendly name of the view.
//   If it has not been defined by the view "Undefined" is returned.
//
wxString& CViewBase::GetViewDisplayName()
{
    static wxString strViewName(wxT("Undefined"));
    return strViewName;
}


// The user friendly icon of the view.
//   If it has not been defined by the view the BOINC icon is returned.
//
wxImage& CViewBase::GetViewIcon()
{
    return wxNullImage;
}


// The rate at which the view is refreshed.
//   If it has not been defined by the view 1 second is returned.
//
const int CViewBase::GetViewRefreshRate()
{
    return 1;
}


void CViewBase::SaveListState()
{
    CConfigManager* pConfig = wxGetApp().GetConfigManager();

    // Save Sorting Information
    pConfig->SetConfigValue(GetViewName(), wxEmptyString, wxT("SortColumn"), m_iSortColumn);
    pConfig->SetConfigValue(GetViewName(), wxEmptyString, wxT("ReverseSort"), m_iSortOrder);

    // Save Column Order
#ifdef wxHAS_LISTCTRL_COLUMN_ORDER
    wxString strColumnOrder;
    wxString strBuffer;
    wxArrayInt aOrder(m_pListPane->GetColumnCount());

    aOrder = m_pListPane->GetColumnsOrder();

    for (int i = 0; i < aOrder.Count(); ++i) 
    {
        strBuffer.Printf(wxT("%d "), aOrder[i]);
        strColumnOrder += strBuffer;
    }

    pConfig->SetConfigValue(GetViewName(), wxEmptyString, wxT("ColumnOrder"), strColumnOrder);
#endif
}


void CViewBase::SaveListColumnState(wxString strName, wxListItem& liColumnInfo)
{
    CConfigManager* pConfig = wxGetApp().GetConfigManager();

    pConfig->SetConfigValue(GetViewName(), strName, wxT("Width"), liColumnInfo.GetWidth());
}


void CViewBase::RestoreListState()
{
    CConfigManager* pConfig = wxGetApp().GetConfigManager();
    long lTempValue = 0;

    // Restore Sorting Information
    if (pConfig->GetConfigValue(GetViewName(), wxEmptyString, wxT("ReverseSort"), -1, &lTempValue))
    {
        m_iSortOrder = lTempValue;
    }
    if (pConfig->GetConfigValue(GetViewName(), wxEmptyString, wxT("SortColumn"), -1, &lTempValue))
    {
        m_iSortColumn = lTempValue;
    }

    // Restore Column Order
#ifdef wxHAS_LISTCTRL_COLUMN_ORDER
    wxString strColumnOrder;
    wxArrayInt aOrder(m_pListPane->GetColumnCount());
    long order = 0;
    int i = 0;

    if (pConfig->GetConfigValue(GetViewName(), wxEmptyString, wxT("ColumnOrder"), wxEmptyString, &strColumnOrder))
    {
        wxStringTokenizer tok(strColumnOrder, " ");
        while (tok.HasMoreTokens())
        {
            tok.GetNextToken().ToLong(&order);
            aOrder[i] = order;
            ++i;
        }

        m_pListPane->SetColumnsOrder(aOrder);
    }
#endif
}


void CViewBase::RestoreListColumnState(wxString strName, wxListItem& liColumnInfo)
{
    CConfigManager* pConfig = wxGetApp().GetConfigManager();
    long lTempValue = 0;

    if (pConfig->GetConfigValue(GetViewName(), strName, wxT("Width"), -1, &lTempValue))
    {
        liColumnInfo.SetWidth(lTempValue);
    }

    m_pListPane->SetColumn(liColumnInfo.GetColumn(), liColumnInfo);
}


void CViewBase::FireOnSelectionChanged(bool bRegister)
{
    OnSelectionChanged(bRegister);
}


wxString CViewBase::FireOnListGetItemText(long item, long column) const {
    return OnListGetItemText(item, column);
}


int CViewBase::FireOnListGetItemImage(long item) const {
    return OnListGetItemImage(item);
}


void CViewBase::OnViewBaseInit(wxCommandEvent& WXUNUSED(event))
{
}


void CViewBase::OnListSelected(wxListEvent& event)
{
    m_bForceUpdateSelection = true;
    UpdateSelection();
    event.Skip();
}


void CViewBase::OnListDeselected(wxListEvent& event)
{
    m_bForceUpdateSelection = true;
    UpdateSelection();
    event.Skip();
}


void CViewBase::OnSelectionChanged(bool bRegister)
{
}


wxString CViewBase::OnListGetItemText(long WXUNUSED(item), long WXUNUSED(column)) const {
    return wxString(wxT("Undefined"));
}


int CViewBase::OnListGetItemImage(long WXUNUSED(item)) const {
    return -1;
}


void CViewBase::OnColumnClick(wxListEvent& event) {
    wxListItem      item;

    item.SetMask(wxLIST_MASK_IMAGE);
    if (event.GetColumn() == m_iSortColumn) {
        m_iSortOrder = !m_iSortOrder;
    } else {
        if (m_iSortColumn >= 0) {
            item.SetImage(-1);
            m_pListPane->SetColumn(m_iSortColumn, item);
        }
        m_iSortColumn = event.GetColumn();
        m_iSortOrder = false;
    }
    
    item.SetImage(m_iSortOrder ? 0 : 1);
    m_pListPane->SetColumn(event.GetColumn(), item);
}


int CViewBase::EmptyCache()
{
    return -1;
}


void CViewBase::EmptyTasks()
{
    unsigned int i;
    unsigned int j;
    for (i=0; i<m_TaskGroups.size(); i++) {
        for (j=0; j<m_TaskGroups[i]->m_Tasks.size(); j++) {
            delete m_TaskGroups[i]->m_Tasks[j];
        }
        m_TaskGroups[i]->m_Tasks.clear();
        delete m_TaskGroups[i];
    }
    m_TaskGroups.clear();
}


void CViewBase::PreUpdateSelection()
{
}


void CViewBase::UpdateSelection()
{
}


void CViewBase::PostUpdateSelection()
{
    m_pTaskPane->UpdateControls();
    Layout();

    // Adjust the width of the task pane so that it can be fully displayed.
    //
    if (IsSplit()) {
        wxSize sz = m_pTaskPane->GetVirtualSize();
        SetSashPosition(sz.GetWidth(), true);
    }
}
