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

#ifndef _VIEWPROJECTS_H_
#define _VIEWPROJECTS_H_

class CViewProjectItem;

class CViewProjects: public CViewBase
{
    DECLARE_DYNAMIC_CLASS(CViewProjects)
    DECLARE_EVENT_TABLE()

public:

    CViewProjects();
    CViewProjects(wxNotebook* pNotebook, BSLHOST hHost);
    ~CViewProjects();

    void OnInit(wxCommandEvent& event);
    void OnUpdateClick(wxCommandEvent& event);
    void OnSuspendClick(wxCommandEvent& event);
    void OnNoNewWorkClick(wxCommandEvent& event);
    void OnResetClick(wxCommandEvent& event);
    void OnDetachClick(wxCommandEvent& event);
    void OnPropertiesClick(wxCommandEvent& event);
    void OnWebsiteClick(wxEvent& event);
    void OnColumnClick(wxListEvent& event);
    void OnColumnEndDrag(wxListEvent& event);
    void OnProjectBulkAdd(CBSLProjectBulkEvent& event);
    void OnProjectBulkUpdate(CBSLProjectBulkEvent& event);
    void OnProjectDelete(CBSLProjectEvent& event);

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

    void UpdateProject(CViewProjectItem& vtItem, CBSLProject& bslProject);

    std::vector<CViewProjectItem*> m_oProjectItems;
    BSLHOST m_hHost;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_VIEWPROJECTS_INIT, 10100 )
END_DECLARE_EVENT_TYPES()

#define EVT_VIEWPROJECTS_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_VIEWPROJECTS_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

