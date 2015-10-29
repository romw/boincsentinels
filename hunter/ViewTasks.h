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

#ifndef _VIEWTASKS_H_
#define _VIEWTASKS_H_

class CViewTaskItem;

class CViewTasks: public CViewBase
{
    DECLARE_DYNAMIC_CLASS(CViewTasks)
    DECLARE_EVENT_TABLE()

public:

    CViewTasks();
    CViewTasks(wxNotebook* pNotebook, BSLHOST hHost);
    ~CViewTasks();

    void OnInit(wxCommandEvent& event);
    void OnColumnClick(wxListEvent& event);
    void OnColumnEndDrag(wxListEvent& event);
    void OnTaskInstanceBulkAdd(CBSLTaskInstanceBulkEvent& event);
    void OnTaskInstanceBulkUpdate(CBSLTaskInstanceBulkEvent& event);
    void OnTaskInstanceDelete(CBSLTaskInstanceEvent& event);

    void OnSelectionChanged( bool bRegister );
    wxString OnListGetItemText( long item, long column ) const;

    virtual wxString&       GetViewName();
    virtual wxString&       GetViewDisplayName();
    virtual wxImage&        GetViewIcon();
    virtual const int       GetViewCurrentViewPage();

    void SaveState();
    void RestoreState();

private:
    void CreateTasks();
    void CreateHeaders();

    void Sort();

    void UpdateTaskInstance(CViewTaskItem& vtItem, CBSLTaskInstance& bslTaskInstance);

    std::vector<CViewTaskItem*> m_oTaskItems;
    BSLHOST m_hHost;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_VIEWTASKS_INIT, 10100 )
END_DECLARE_EVENT_TYPES()

#define EVT_VIEWTASKS_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_VIEWTASKS_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

