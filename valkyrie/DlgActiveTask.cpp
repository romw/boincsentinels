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
#include "Valkyrie.h"
#include "Utils.h"
#include "Interface.h"
#include "DlgControls.h"
#include "DlgActiveTask.h"

IMPLEMENT_DYNAMIC_CLASS(CDlgActiveTask, wxDialog);

BEGIN_EVENT_TABLE(CDlgActiveTask, wxDialog)
    EVT_BSLTASKINSTANCE_UPDATE(CDlgActiveTask::OnTaskInstanceUpdate)
END_EVENT_TABLE();


CDlgActiveTask::CDlgActiveTask()
{
}

CDlgActiveTask::CDlgActiveTask(BSLHOST hHost, BSLTASKINSTANCE hTaskInstance)
{
    m_hHost = hHost;
    m_hTaskInstance = hTaskInstance;
    Create(NULL);
}

CDlgActiveTask::CDlgActiveTask(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    Create(parent, id, caption, pos, size, style);
}

CDlgActiveTask::~CDlgActiveTask()
{
    CBSLClient* pState = wxGetApp().GetState();

    // Unregister for notification events
    pState->UnregisterEventHandler(this, wxEVT_BSLTASKINSTANCE_UPDATE, m_hHost, m_hTaskInstance);
}

bool CDlgActiveTask::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLTaskInstance bslTaskInstance;

    wxString strCaption = caption;
    if (strCaption.IsEmpty())
    {
        strCaption = _("BOINC-Sentinels - Active Task");
    }

    SetExtraStyle(GetExtraStyle() | wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create(parent, id, strCaption, pos, size, style);

    pState->GetTaskInstance(m_hTaskInstance, &bslTaskInstance);
    CreateControls();
    UpdateControls(bslTaskInstance);

    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);

    Centre();

    // Register for task instance events
    pState->RegisterEventHandler(this, wxEVT_BSLTASKINSTANCE_UPDATE, m_hHost, m_hTaskInstance);
    return TRUE;
}

void CDlgActiveTask::CreateControls()
{
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(1);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( this, wxID_STATIC, _("Task:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pTaskCtrl = new CDlgStaticText( this, ID_TASK, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pTaskCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( this, wxID_STATIC, _("Application:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAppCtrl = new CDlgStaticText( this, ID_APP, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pAppCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( this, wxID_STATIC, _("Project:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pProjectCtrl = new CDlgStaticText( this, ID_PROJECT, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pProjectCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( this, wxID_STATIC, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pStatusCtrl = new CDlgStaticText( this, ID_STATUS, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pStatusCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( this, wxID_STATIC, _("Received:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pReceivedCtrl = new CDlgDateTime( this, ID_RECEIVED, wxDateTime::Now(), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pReceivedCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( this, wxID_STATIC, _("Report Deadline:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pDeadlineCtrl = new CDlgDateTime( this, ID_DEADLINE, wxDateTime::Now(), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pDeadlineCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( this, wxID_STATIC, _("Resources:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pResourcesCtrl = new CDlgStaticText( this, ID_RESOURCES, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pResourcesCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( this, wxID_STATIC, _("Estimated Computation:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pEstimatedComputationCtrl = new CDlgFLOPCount( this, ID_ESTIMATEDCOMPUTATION, 0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pEstimatedComputationCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( this, wxID_STATIC, _("CPU Time:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pCPUTimeCtrl = new CDlgTimeSpan( this, ID_CPUTIME, wxTimeSpan::Seconds(0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pCPUTimeCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText13 = new wxStaticText( this, wxID_STATIC, _("CPU Time (Last Checkpoint):"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pCPUTimeLastCheckpointCtrl = new CDlgTimeSpan( this, ID_CPUTIMELASTCHECKPOINT, wxTimeSpan::Seconds(0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pCPUTimeLastCheckpointCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText14 = new wxStaticText( this, wxID_STATIC, _("Elapsed Time:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pElapsedTimeCtrl = new CDlgTimeSpan( this, ID_ELAPSEDTIME, wxTimeSpan::Seconds(0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pElapsedTimeCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( this, wxID_STATIC, _("Estimated Time Remaining:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pTimeRemainingCtrl = new CDlgTimeSpan( this, ID_ELAPSEDTIME, wxTimeSpan::Seconds(0), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pTimeRemainingCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText16 = new wxStaticText( this, wxID_STATIC, _("Fraction Done:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pFractionDoneCtrl = new CDlgProgress( this, ID_FRACTIONDONE, 0.0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pFractionDoneCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText17 = new wxStaticText( this, wxID_STATIC, _("Virtual Memory Size:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pVirtualMemoryCtrl = new CDlgByteCount( this, ID_VIRTUALMEMORY, 0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pVirtualMemoryCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText18 = new wxStaticText( this, wxID_STATIC, _("Working Set Size:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText18, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pWorkingSetCtrl = new CDlgByteCount( this, ID_WORKINGSET, 0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pWorkingSetCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText19 = new wxStaticText( this, wxID_STATIC, _("Working Directory:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText19, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pDirectoryCtrl = new CDlgStaticText( this, ID_DIRECTORY, wxT(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pDirectoryCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( this, wxID_STATIC, _("Process ID:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pProcessIDCtrl = new CDlgUint32( this, ID_PROCESSID, 0, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(m_pProcessIDCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer4 = new wxStdDialogButtonSizer;
    itemBoxSizer2->Add(itemStdDialogButtonSizer4, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton11 = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
    itemStdDialogButtonSizer4->AddButton(itemButton11);
    itemStdDialogButtonSizer4->Realize();
}

void CDlgActiveTask::UpdateControls(CBSLTaskInstance& bslTaskInstance)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLProject bslProject;
    CBSLTask bslTask;

    pState->GetProject(bslTaskInstance.GetProjectHandle(), &bslProject);
    pState->GetTask(bslTaskInstance.GetTaskHandle(), &bslTask);

    m_pTaskCtrl->SetLabel(bslTaskInstance.GetName());
    m_pAppCtrl->SetLabel(CUtils::ConstructTaskInstanceAppVersion(bslTaskInstance));
    m_pProjectCtrl->SetLabel(bslProject.GetProjectName());
    m_pStatusCtrl->SetLabel(CUtils::ConstructTaskInstanceStatus(bslTaskInstance));
    m_pReceivedCtrl->SetValue(bslTaskInstance.GetReceivedTime());
    m_pDeadlineCtrl->SetValue(bslTaskInstance.GetReportDeadline());
    m_pResourcesCtrl->SetLabel(bslTaskInstance.GetResourcesUtilized());
    m_pEstimatedComputationCtrl->SetValue(bslTask.GetRuntimeEstimatedFLOPS());
    m_pCPUTimeCtrl->SetValue(bslTaskInstance.GetCurrentCPUTime());
    m_pCPUTimeLastCheckpointCtrl->SetValue(bslTaskInstance.GetCheckpointCPUTime());
    m_pElapsedTimeCtrl->SetValue(bslTaskInstance.GetElapsedTime());
    m_pTimeRemainingCtrl->SetValue(bslTaskInstance.GetEstimatedElapsedTimeRemaining());
    m_pFractionDoneCtrl->SetValue(bslTaskInstance.GetFractionDone());
    m_pVirtualMemoryCtrl->SetValue(bslTaskInstance.GetSwapSize());
    m_pWorkingSetCtrl->SetValue(bslTaskInstance.GetWorkingSetSizeSmoothed());
    m_pDirectoryCtrl->SetLabel(bslTaskInstance.GetSlotDirectory());
    m_pProcessIDCtrl->SetValue(bslTaskInstance.GetProcessID());
}

void CDlgActiveTask::OnTaskInstanceUpdate(CBSLTaskInstanceEvent& event)
{
    CBSLTaskInstance bslTaskInstance;
    if (BSLERR_SUCCESS == event.GetTaskInstance(&bslTaskInstance))
    {
        UpdateControls(bslTaskInstance);
    }
}
