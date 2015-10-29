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
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Valkyrie.h"
#include "Utils.h"
#include "SkinManager.h"
#include "DlgActiveTask.h"
#include "WidgetControls.h"
#include "WidgetBase.h"
#include "WidgetActiveTask.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETACTIVETASK_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetActiveTask, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetActiveTask, CWidgetBase)
    EVT_WIDGETACTIVETASK_INIT(CWidgetActiveTask::OnInit)
    EVT_WIDGETBASE_SHOWCONTENTS(CWidgetActiveTask::OnShowContents)
    EVT_WIDGETBASE_HIDECONTENTS(CWidgetActiveTask::OnHideContents)
    EVT_BUTTON(ID_WIDGETACTIVETASKSHOWGRAPHICS, CWidgetActiveTask::OnShowGraphics)
    EVT_BUTTON(ID_WIDGETACTIVETASKSHOWWEBGRAPHICS, CWidgetActiveTask::OnShowWebGraphics)
    EVT_BUTTON(ID_WIDGETACTIVETASKSHOWVMCONSOLE, CWidgetActiveTask::OnShowVMConsole)
    EVT_BUTTON(ID_WIDGETACTIVETASKSUSPEND, CWidgetActiveTask::OnSuspend)
    EVT_BUTTON(ID_WIDGETACTIVETASKRESUME, CWidgetActiveTask::OnResume)
    EVT_BUTTON(ID_WIDGETACTIVETASKABORT, CWidgetActiveTask::OnAbort)
    EVT_BUTTON(ID_WIDGETACTIVETASKPROPERTIES, CWidgetActiveTask::OnProperties)
    EVT_BSLTASKINSTANCE_UPDATE(CWidgetActiveTask::OnTaskInstanceUpdate)
END_EVENT_TABLE();

CWidgetActiveTask::CWidgetActiveTask() :
CWidgetBase()
{
}

CWidgetActiveTask::CWidgetActiveTask(wxWindow* pParent, BSLHOST hHost, BSLTASKINSTANCE hTaskInstance) :
CWidgetBase(pParent, ID_WIDGETACTIVETASK)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTaskInstance bslTaskInstance;

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;

    m_hHost = hHost;
    m_hTaskInstance = hTaskInstance;

    // Create Controls
    CreateControls(true, false, true);

    // Update control state.
    pState->GetTaskInstance(m_hTaskInstance, &bslTaskInstance);
    SetWidgetName(bslTaskInstance.GetName());
    UpdateControls(bslTaskInstance);
    UpdateControlsButtonBar(bslTaskInstance);
    ToggleVisibility(bslTaskInstance);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETACTIVETASK_INIT);
    AddPendingEvent(evt);
}

CWidgetActiveTask::~CWidgetActiveTask()
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->UnregisterEventHandler(this, wxEVT_BSLTASKINSTANCE_UPDATE, m_hHost, m_hTaskInstance);
}

BSLHOST CWidgetActiveTask::GetHostHandle()
{
    return m_hHost;
}

BSLTASKINSTANCE CWidgetActiveTask::GetTaskInstanceHandle()
{
    return m_hTaskInstance;
}

bool CWidgetActiveTask::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pButtonBarProgressCtrl = new CWidgetProgress( m_pButtonBar, wxID_ANY, 0, wxDefaultPosition, wxSize(80, 16), 0 );
    m_pButtonBarSizer->Add(m_pButtonBarProgressCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pShowGraphicsCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKSHOWGRAPHICS, pSkin->GetShowGraphicsIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pShowGraphicsCtrl->SetToolTip(_("Show Graphics"));
    m_pButtonBarSizer->Add(m_pShowGraphicsCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pShowWebGraphicsCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKSHOWWEBGRAPHICS, pSkin->GetShowWebGraphicsIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pShowWebGraphicsCtrl->SetToolTip(_("Show Web Graphics"));
    m_pButtonBarSizer->Add(m_pShowWebGraphicsCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pShowVMConsoleCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKSHOWVMCONSOLE, pSkin->GetShowVMConsoleIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pShowVMConsoleCtrl->SetToolTip(_("Show VM Console"));
    m_pButtonBarSizer->Add(m_pShowVMConsoleCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pResumeCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKRESUME, pSkin->GetResumeIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pResumeCtrl->SetToolTip(_("Resume"));
    m_pButtonBarSizer->Add(m_pResumeCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pSuspendCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKSUSPEND, pSkin->GetSuspendIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pSuspendCtrl->SetToolTip(_("Suspend"));
    m_pButtonBarSizer->Add(m_pSuspendCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pAbortCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKABORT, pSkin->GetAbortIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pAbortCtrl->SetToolTip(_("Abort"));
    m_pButtonBarSizer->Add(m_pAbortCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pPropertiesCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETASKPROPERTIES, pSkin->GetPropertiesIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pPropertiesCtrl->SetToolTip(_("View Details"));
    m_pButtonBarSizer->Add(m_pPropertiesCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    return true;
}

bool CWidgetActiveTask::OnCreateContent(wxWindow* pParent, CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    m_pContent = pParent;
    m_pContentSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_pContentSizer->AddGrowableCol(0);
    m_pContent->SetSizer(m_pContentSizer);

    wxFlexGridSizer* itemFlexGridSizer12 = new wxFlexGridSizer(0, 1, 0, 0);
    itemFlexGridSizer12->AddGrowableCol(0);
    m_pContentSizer->Add(itemFlexGridSizer12, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    m_pAppNameCtrl = new wxStaticText( m_pContent, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer12->Add(m_pAppNameCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pContentSizer->AddSpacer(1);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(1);
    m_pContentSizer->Add(itemFlexGridSizer3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxStaticText* pProgressStaticCtrl = new wxStaticText( m_pContent, wxID_STATIC, _("Progress:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(pProgressStaticCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pProgressCtrl = new CWidgetProgress( m_pContent, wxID_ANY, 0, wxDefaultPosition, wxSize(-1, 16), 0 );
    itemFlexGridSizer3->Add(m_pProgressCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    wxFlexGridSizer* itemFlexGridSizer6 = new wxFlexGridSizer(0, 4, 0, 0);
    itemFlexGridSizer6->AddGrowableCol(1);
    itemFlexGridSizer6->AddGrowableCol(3);
    m_pContentSizer->Add(itemFlexGridSizer6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxStaticText* pRemainingStaticCtrl = new wxStaticText( m_pContent, wxID_STATIC, _("Remaining:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(pRemainingStaticCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pRemainingCtrl = new CWidgetRemaining( m_pContent, wxID_STATIC, wxTimeSpan(0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(m_pRemainingCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    wxStaticText* itemStaticText9 = new wxStaticText( m_pContent, wxID_STATIC, _("Deadline:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(itemStaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pDeadlineCtrl = new CWidgetDeadline( m_pContent, wxID_STATIC, wxDateTime((time_t)0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(m_pDeadlineCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    wxFlexGridSizer* itemFlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer11->AddGrowableCol(1);
    m_pContentSizer->Add(itemFlexGridSizer11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2);

    wxStaticText* pStatusStaticCtrl = new wxStaticText( m_pContent, wxID_STATIC, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(pStatusStaticCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pStatusCtrl = new wxStaticText( m_pContent, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(m_pStatusCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 2);

    m_pContentSizer->AddSpacer(1);

    // Calculate the layout of the control
    m_pContentSizer->CalcMin();

    // Progress, Remaining, and Status should all have the same width.
    int iMaxWidth = pProgressStaticCtrl->GetEffectiveMinSize().GetWidth();
    iMaxWidth = std::max(iMaxWidth, pRemainingStaticCtrl->GetEffectiveMinSize().GetWidth());
    iMaxWidth = std::max(iMaxWidth, pStatusStaticCtrl->GetEffectiveMinSize().GetWidth());

    wxSize sz(iMaxWidth, -1);
    pProgressStaticCtrl->SetMinSize(sz);
    pRemainingStaticCtrl->SetMinSize(sz);
    pStatusStaticCtrl->SetMinSize(sz);

    return true;
}

void CWidgetActiveTask::UpdateControls(CBSLTaskInstance& bslTaskInstance)
{
    m_pAppNameCtrl->SetLabel(CUtils::ConstructTaskInstanceAppVersion(bslTaskInstance));
    m_pProgressCtrl->SetValue(bslTaskInstance.GetFractionDone());
    m_pRemainingCtrl->SetValue(bslTaskInstance.GetEstimatedElapsedTimeRemaining());
    m_pDeadlineCtrl->SetValue(bslTaskInstance.GetReportDeadline());
    m_pStatusCtrl->SetLabel(CUtils::ConstructTaskInstanceStatus(bslTaskInstance));
}

void CWidgetActiveTask::UpdateControlsButtonBar(CBSLTaskInstance& bslTaskInstance)
{
    m_pAppNameCtrl->SetLabel(CUtils::ConstructTaskInstanceAppVersion(bslTaskInstance));
    m_pButtonBarProgressCtrl->SetValue(bslTaskInstance.GetFractionDone());

    if (bslTaskInstance.GetGraphicsApplication().IsEmpty() ||
        (bslTaskInstance.GetSchedulerState() != CBSLTaskInstance::SchedulerStateScheduled))
    {
        if (m_pShowGraphicsCtrl->IsShown())
        {
            m_pShowGraphicsCtrl->Hide();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (!m_pShowGraphicsCtrl->IsShown() &&
            (bslTaskInstance.GetSchedulerState() == CBSLTaskInstance::SchedulerStateScheduled))
        {
            m_pShowGraphicsCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    if (bslTaskInstance.GetWebGraphicsApplication().IsEmpty() ||
        (bslTaskInstance.GetSchedulerState() != CBSLTaskInstance::SchedulerStateScheduled))
    {
        if (m_pShowWebGraphicsCtrl->IsShown())
        {
            m_pShowWebGraphicsCtrl->Hide();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (!m_pShowWebGraphicsCtrl->IsShown() &&
            (bslTaskInstance.GetSchedulerState() == CBSLTaskInstance::SchedulerStateScheduled))
        {
            m_pShowWebGraphicsCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    if (bslTaskInstance.GetRemoteDesktopAddress().IsEmpty() ||
        (bslTaskInstance.GetSchedulerState() != CBSLTaskInstance::SchedulerStateScheduled))
    {
        if (m_pShowVMConsoleCtrl->IsShown())
        {
            m_pShowVMConsoleCtrl->Hide();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (!m_pShowVMConsoleCtrl->IsShown() &&
            (bslTaskInstance.GetSchedulerState() == CBSLTaskInstance::SchedulerStateScheduled))
        {
            m_pShowVMConsoleCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    if (bslTaskInstance.IsInterfaceSuspensionEnabled())
    {
        if (m_pSuspendCtrl->IsShown())
        {
            m_pSuspendCtrl->Hide();
            m_pResumeCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (m_pResumeCtrl->IsShown())
        {
            m_pResumeCtrl->Hide();
            m_pSuspendCtrl->Show();
            UpdateHeaderLayout();
        }
    }
}

void CWidgetActiveTask::ToggleVisibility(CBSLTaskInstance& bslTaskInstance)
{
    if (!IsShown())
    {
        if (bslTaskInstance.IsTaskActive())
        {
            Show();

            wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
            AddPendingEvent(evt);
        }
    }
    else
    {
        if (!bslTaskInstance.IsTaskActive())
        {
            Hide();

            wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
            AddPendingEvent(evt);
        }
    }
}

void CWidgetActiveTask::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->RegisterEventHandler(this, wxEVT_BSLTASKINSTANCE_UPDATE, m_hHost, m_hTaskInstance);
}

void CWidgetActiveTask::OnShowContents(wxCommandEvent& WXUNUSED(event))
{
    m_pButtonBarProgressCtrl->Show(false);
    UpdateHeaderLayout();
}

void CWidgetActiveTask::OnHideContents(wxCommandEvent& WXUNUSED(event))
{
    m_pButtonBarProgressCtrl->Show();
    UpdateHeaderLayout();
}

void CWidgetActiveTask::OnShowGraphics(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTaskInstance bslTaskInstance;

    pState->GetTaskInstance(m_hTaskInstance, &bslTaskInstance);
    CUtils::LaunchGraphics(bslTaskInstance);
}

void CWidgetActiveTask::OnShowWebGraphics(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTaskInstance bslTaskInstance;

    pState->GetTaskInstance(m_hTaskInstance, &bslTaskInstance);
    CUtils::LaunchWebGraphics(bslTaskInstance);
}

void CWidgetActiveTask::OnShowVMConsole(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTaskInstance bslTaskInstance;

    pState->GetTaskInstance(m_hTaskInstance, &bslTaskInstance);
    CUtils::LaunchRemoteDesktop(bslTaskInstance);
}

void CWidgetActiveTask::OnResume(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->TaskInstanceSetProperty(m_hTaskInstance, CBSLClient::TaskInstancePropertySuspend, 0);
}

void CWidgetActiveTask::OnSuspend(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->TaskInstanceSetProperty(m_hTaskInstance, CBSLClient::TaskInstancePropertySuspend, 1);
}

void CWidgetActiveTask::OnAbort(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTaskInstance bslTaskInstance;
    wxString strBuffer = wxEmptyString;

    pState->GetTaskInstance(m_hTaskInstance, &bslTaskInstance);

    strBuffer.Printf(
        _("Are you sure you wish to abort task '%s'?\n(Progress: %.2f%%)"),
        bslTaskInstance.GetName().c_str(),
        bslTaskInstance.GetFractionDone() * 100
    );

    wxInt32 rc = ::wxMessageBox(
        strBuffer.c_str(),
        _("BOINC-Sentinels"),
        wxYES_NO | wxICON_QUESTION
    );
    if (wxYES == rc)
    {
        pState->TaskInstanceAbort(m_hTaskInstance);
    }
}

void CWidgetActiveTask::OnProperties(wxCommandEvent& WXUNUSED(event))
{
    CDlgActiveTask dlgActiveTask(m_hHost, m_hTaskInstance);
    dlgActiveTask.ShowModal();
}

void CWidgetActiveTask::OnTaskInstanceUpdate(CBSLTaskInstanceEvent& event)
{
    CBSLTaskInstance bslTaskInstance;
    event.GetTaskInstance(&bslTaskInstance);

    ToggleVisibility(bslTaskInstance);
    if (bslTaskInstance.IsTaskActive())
    {
        UpdateControlsButtonBar(bslTaskInstance);
        if (IsContentsShown())
        {
            UpdateControls(bslTaskInstance);
        }
    }
}
