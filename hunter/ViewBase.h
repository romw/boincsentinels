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

#ifndef _VIEWBASE_H_
#define _VIEWBASE_H_


#define DEFAULT_TASK_FLAGS              wxTAB_TRAVERSAL | wxADJUST_MINSIZE | wxFULL_REPAINT_ON_RESIZE
#define DEFAULT_LIST_FLAGS              wxLC_REPORT | wxLC_VIRTUAL | wxLC_HRULES

#define SORT_ASCENDING                  0
#define SORT_DESCENDING                 1


class CBOINCTaskCtrl;
class CBOINCListCtrl;


class CTaskItem : wxObject
{
public:
    CTaskItem();
    CTaskItem( wxString strName, wxString strDescription, wxInt32 iEventID ) :
        m_strName(strName), m_strDescription(strDescription), m_iEventID(iEventID),
        m_pButton(NULL), m_strWebSiteLink(wxT("")) {};
    CTaskItem( wxString strName, wxString strDescription, wxString strWebSiteLink, wxInt32 iEventID ) :
        m_strName(strName), m_strDescription(strDescription), m_iEventID(iEventID),
        m_pButton(NULL), m_strWebSiteLink(strWebSiteLink) {};
    ~CTaskItem() {};

    wxString                m_strName;
    wxString                m_strDescription;
    wxInt32                 m_iEventID;

    wxButton*               m_pButton;
    wxString                m_strWebSiteLink;
};


class CTaskItemGroup : wxObject
{
public:
    CTaskItemGroup();
    CTaskItemGroup( wxString strName ) :
        m_strName(strName), m_pStaticBox(NULL), m_pStaticBoxSizer(NULL)
    {
        m_Tasks.clear();
    };
    ~CTaskItemGroup() {};

    wxButton* button(int i) {return m_Tasks[i]->m_pButton;}

    wxString                m_strName;

    wxStaticBox*            m_pStaticBox;
    wxStaticBoxSizer*       m_pStaticBoxSizer;

    std::vector<CTaskItem*> m_Tasks;
};


class CViewBase: public wxSplitterWindow
{
    DECLARE_DYNAMIC_CLASS(CViewBase)
    DECLARE_EVENT_TABLE()

public:

    CViewBase();
    CViewBase( wxNotebook* pNotebook );
    CViewBase( wxNotebook* pNotebook, wxWindowID iTaskWindowID, int iTaskWindowFlags, wxWindowID iListWindowID, int iListWindowFlags );

    ~CViewBase();

    virtual wxString&       GetViewName();
    virtual wxString&       GetViewDisplayName();
    virtual wxImage&        GetViewIcon();
    virtual const int       GetViewRefreshRate();

    virtual void            SaveListState();
    virtual void            SaveListColumnState(wxString strName, wxListItem& liColumnInfo);
    virtual void            RestoreListState();
    virtual void            RestoreListColumnState(wxString strName, wxListItem& liColumnInfo);
    
    void                    FireOnSelectionChanged( bool bRegister );
    wxString                FireOnListGetItemText( long item, long column ) const;
    int                     FireOnListGetItemImage( long item ) const;

    virtual void            OnViewBaseInit(wxCommandEvent& event);
    virtual void            OnListSelected( wxListEvent& event );
    virtual void            OnListDeselected( wxListEvent& event );
    virtual void            OnSelectionChanged( bool bRegister );
    virtual wxString        OnListGetItemText( long item, long column ) const;
    virtual int             OnListGetItemImage( long item ) const;
    virtual void            OnColumnClick(wxListEvent& event);

    virtual int             EmptyCache();
    virtual void            EmptyTasks();

    virtual void            PreUpdateSelection();
    virtual void            UpdateSelection();
    virtual void            PostUpdateSelection();

    std::vector<CTaskItemGroup*> m_TaskGroups;

    CBOINCTaskCtrl*         m_pTaskPane;
    CBOINCListCtrl*         m_pListPane;

    bool                    m_bForceUpdateSelection;

    std::vector<bool>       m_bSortUpdatedColumns;
    int                     m_iSortColumn;
    int                     m_iSortOrder;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_VIEWBASE_INIT, 10100 )
END_DECLARE_EVENT_TYPES()

#define EVT_VIEWBASE_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_VIEWBASE_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

