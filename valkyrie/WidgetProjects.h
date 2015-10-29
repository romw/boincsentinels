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

#ifndef _WIDGETPROJECTS_H_
#define _WIDGETPROJECTS_H_

// Forward Declares
class CWidgetProject;

class CWidgetProjects: public CWidgetBase
{
    DECLARE_DYNAMIC_CLASS(CWidgetProjects)
    DECLARE_EVENT_TABLE()

public:

    CWidgetProjects();
    CWidgetProjects(wxWindow* pParent, BSLHOST hHost);
    ~CWidgetProjects();

    void OnInit(wxCommandEvent& event);
    void OnShowContents(wxCommandEvent& event);
    void OnHideContents(wxCommandEvent& event);
    void OnResumeProjects(wxCommandEvent& event);
    void OnSuspendProjects(wxCommandEvent& event);
    void OnProjectAdd(CBSLProjectEvent& event);
    void OnProjectDelete(CBSLProjectEvent& event);

protected:
    bool OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);
    bool OnCreateContent(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);

private:
    BSLHOST m_hHost;

    wxWindow* m_pButtonBar;
    wxBoxSizer* m_pButtonBarSizer;
    CWidgetBitmapButton* m_pAddProjectCtrl;
    CWidgetBitmapButton* m_pResumeProjectsCtrl;
    CWidgetBitmapButton* m_pSuspendProjectsCtrl;

    wxWindow* m_pContent;
    wxFlexGridSizer* m_pContentSizer;

    std::vector<CWidgetProject*> m_Projects;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_WIDGETPROJECTS_INIT, 10200 )
END_DECLARE_EVENT_TYPES()

#define EVT_WIDGETPROJECTS_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETPROJECTS_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

