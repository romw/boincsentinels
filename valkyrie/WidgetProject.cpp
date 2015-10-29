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
#include "SkinManager.h"
#include "WidgetControls.h"
#include "WidgetBase.h"
#include "WidgetProject.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETPROJECT_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetProject, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetProject, CWidgetBase)
    EVT_WIDGETPROJECT_INIT(CWidgetProject::OnInit)
    EVT_WIDGETBASE_SHOWCONTENTS(CWidgetProject::OnShowContents)
    EVT_WIDGETBASE_HIDECONTENTS(CWidgetProject::OnHideContents)
    EVT_BSLPROJECT_UPDATE(CWidgetProject::OnProjectUpdate)
END_EVENT_TABLE();

CWidgetProject::CWidgetProject()
{
}

CWidgetProject::CWidgetProject(wxWindow* pParent, BSLHOST hHost, BSLPROJECT hProject) :
CWidgetBase(pParent, ID_WIDGETPROJECT)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLProject bslProject;

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;

    m_hHost = hHost;
    m_hProject = hProject;

    // Create Controls
    CreateControls(true, false, true);

    // Update control state.
    pState->GetProject(m_hProject, &bslProject);
    UpdateControls(bslProject);
    UpdateControlsButtonBar(bslProject);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETPROJECT_INIT);
    AddPendingEvent(evt);
}

CWidgetProject::~CWidgetProject()
{
    CBSLClient* pState = wxGetApp().GetState();

    // Unregister from project update events
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_UPDATE, m_hHost, m_hProject);
}

BSLHOST CWidgetProject::GetHostHandle()
{
    return m_hHost;
}

BSLTASKINSTANCE CWidgetProject::GetProjectHandle()
{
    return m_hProject;
}

bool CWidgetProject::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pUpdateCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETPROJECTUPDATE, pSkin->GetUpdateIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pUpdateCtrl->SetToolTip(_("Update"));
    m_pButtonBarSizer->Add(m_pUpdateCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pResumeCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETPROJECTRESUME, pSkin->GetResumeIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pResumeCtrl->SetToolTip(_("Resume"));
    m_pButtonBarSizer->Add(m_pResumeCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pSuspendCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETPROJECTSUSPEND, pSkin->GetSuspendIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pSuspendCtrl->SetToolTip(_("Suspend"));
    m_pButtonBarSizer->Add(m_pSuspendCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pPropertiesCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETPROJECTPROPERTIES, pSkin->GetPropertiesIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pPropertiesCtrl->SetToolTip(_("View Details"));
    m_pButtonBarSizer->Add(m_pPropertiesCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    return true;
}

bool CWidgetProject::OnCreateContent(wxWindow* pParent, CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    m_pContent = pParent;
    m_pContentSizer = new wxBoxSizer(wxVERTICAL);
    m_pContent->SetSizer(m_pContentSizer);
    return true;
}

void CWidgetProject::UpdateControls(CBSLProject& bslProject)
{
    wxString strBuffer = wxEmptyString;

    if (!bslProject.GetProjectName().IsEmpty())
    {
        strBuffer = bslProject.GetProjectName();
    }
    else
    {
        strBuffer = bslProject.GetMasterURL();
    }

    if (strBuffer != GetWidgetName())
    {
        SetWidgetName(strBuffer);
    }
}

void CWidgetProject::UpdateControlsButtonBar(CBSLProject& bslProject)
{
    if (bslProject.IsInterfaceSuspensionEnabled())
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

void CWidgetProject::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Register for project update events
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_UPDATE, m_hHost, m_hProject);
}

void CWidgetProject::OnShowContents(wxCommandEvent& WXUNUSED(event))
{
}

void CWidgetProject::OnHideContents(wxCommandEvent& WXUNUSED(event))
{
}

void CWidgetProject::OnProjectUpdate(CBSLProjectEvent& event)
{
    CBSLProject bslProject;
    event.GetProject(&bslProject);

    UpdateControlsButtonBar(bslProject);
    if (IsContentsShown())
    {
        UpdateControls(bslProject);
    }
}
