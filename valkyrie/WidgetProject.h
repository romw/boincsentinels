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

#ifndef _WIDGETPROJECT_H_
#define _WIDGETPROJECT_H_

class CWidgetProject: public CWidgetBase
{
    DECLARE_DYNAMIC_CLASS(CWidgetProject)
    DECLARE_EVENT_TABLE()

public:

    CWidgetProject();
    CWidgetProject(wxWindow* pParent, BSLHOST hHost, BSLPROJECT hProject);
    ~CWidgetProject();

    BSLHOST GetHostHandle();
    BSLPROJECT GetProjectHandle();

    void OnInit(wxCommandEvent& event);
    void OnShowContents(wxCommandEvent& event);
    void OnHideContents(wxCommandEvent& event);
    void OnProjectUpdate(CBSLProjectEvent& event);

protected:
    bool OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);
    bool OnCreateContent(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);

    void UpdateControls(CBSLProject& bslProject);
    void UpdateControlsButtonBar(CBSLProject& bslProject);

private:
    BSLHOST m_hHost;
    BSLPROJECT m_hProject;

    wxWindow* m_pButtonBar;
    wxBoxSizer* m_pButtonBarSizer;
    CWidgetBitmapButton* m_pUpdateCtrl;
    CWidgetBitmapButton* m_pResumeCtrl;
    CWidgetBitmapButton* m_pSuspendCtrl;
    CWidgetBitmapButton* m_pPropertiesCtrl;

    wxWindow* m_pContent;
    wxBoxSizer* m_pContentSizer;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_WIDGETPROJECT_INIT, 10200 )
END_DECLARE_EVENT_TYPES()

#define EVT_WIDGETPROJECT_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETPROJECT_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

