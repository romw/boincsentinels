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

#ifndef _WIDGETACTIVETASK_H_
#define _WIDGETACTIVETASK_H_

class CWidgetActiveTask: public CWidgetBase
{
    DECLARE_DYNAMIC_CLASS(CWidgetActiveTask)
    DECLARE_EVENT_TABLE()

public:

    CWidgetActiveTask();
    CWidgetActiveTask(wxWindow* pParent, BSLHOST hHost, BSLTASKINSTANCE hTaskInstance);
    ~CWidgetActiveTask();

    BSLHOST GetHostHandle();
    BSLTASKINSTANCE GetTaskInstanceHandle();

    void OnInit(wxCommandEvent& event);
    void OnShowContents(wxCommandEvent& event);
    void OnHideContents(wxCommandEvent& event);
    void OnShowGraphics(wxCommandEvent& event);
    void OnShowWebGraphics(wxCommandEvent& event);
    void OnShowVMConsole(wxCommandEvent& event);
    void OnSuspend(wxCommandEvent& event);
    void OnResume(wxCommandEvent& event);
    void OnAbort(wxCommandEvent& event);
    void OnProperties(wxCommandEvent& event);
    void OnTaskInstanceUpdate(CBSLTaskInstanceEvent& event);

protected:
    bool OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);
    bool OnCreateContent(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);

    void UpdateControls(CBSLTaskInstance& bslTaskInstance);
    void UpdateControlsButtonBar(CBSLTaskInstance& bslTaskInstance);
    void ToggleVisibility(CBSLTaskInstance& bslTaskInstance);

private:
    BSLHOST m_hHost;
    BSLTASKINSTANCE m_hTaskInstance;

    wxWindow* m_pButtonBar;
    wxBoxSizer* m_pButtonBarSizer;
    CWidgetProgress* m_pButtonBarProgressCtrl;
    CWidgetBitmapButton* m_pShowGraphicsCtrl;
    CWidgetBitmapButton* m_pShowWebGraphicsCtrl;
    CWidgetBitmapButton* m_pShowVMConsoleCtrl;
    CWidgetBitmapButton* m_pResumeCtrl;
    CWidgetBitmapButton* m_pSuspendCtrl;
    CWidgetBitmapButton* m_pAbortCtrl;
    CWidgetBitmapButton* m_pPropertiesCtrl;

    wxWindow* m_pContent;
    wxFlexGridSizer* m_pContentSizer;
    wxStaticText* m_pAppNameCtrl;
    CWidgetProgress* m_pProgressCtrl;
    CWidgetRemaining* m_pRemainingCtrl;
    CWidgetDeadline* m_pDeadlineCtrl;
    wxStaticText* m_pStatusCtrl;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_WIDGETACTIVETASK_INIT, 10200 )
END_DECLARE_EVENT_TYPES()

#define EVT_WIDGETACTIVETASK_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETACTIVETASK_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

