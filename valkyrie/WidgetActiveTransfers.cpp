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
#include "WidgetActiveTransfer.h"
#include "WidgetActiveTransfers.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETACTIVETRANSFERS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetActiveTransfers, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetActiveTransfers, CWidgetBase)
    EVT_WIDGETACTIVETRANSFERS_INIT(CWidgetActiveTransfers::OnInit)
    EVT_WIDGETBASE_SHOWCONTENTS(CWidgetActiveTransfers::OnShowContents)
    EVT_WIDGETBASE_HIDECONTENTS(CWidgetActiveTransfers::OnHideContents)
    EVT_BUTTON(ID_WIDGETACTIVETRANSFERSRESUMETRANSFERS, CWidgetActiveTransfers::OnResumeTransfers)
    EVT_BUTTON(ID_WIDGETACTIVETRANSFERSUSPENDTRANSFERS, CWidgetActiveTransfers::OnSuspendTransfers)
    EVT_BSLHOSTSTATUS_UPDATE(CWidgetActiveTransfers::OnHostStatusUpdate)
    EVT_BSLTRANSFER_ADD(CWidgetActiveTransfers::OnTransferAdd)
    EVT_BSLTRANSFER_DELETE(CWidgetActiveTransfers::OnTransferDelete)
END_EVENT_TABLE();


bool SortWidgetActiveTransfer(CWidgetActiveTransfer* p1, CWidgetActiveTransfer* p2)
{
    return p1->GetWidgetName().CmpNoCase(p2->GetWidgetName()) < 0;
}


CWidgetActiveTransfers::CWidgetActiveTransfers()
{
}

CWidgetActiveTransfers::CWidgetActiveTransfers(wxWindow* pParent, BSLHOST hHost) :
CWidgetBase(pParent, ID_WIDGETACTIVETRANSFERS, _("Active Transfers"))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTransfers::CWidgetActiveTransfers - Function Begin"));

    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;

    m_hHost = hHost;

    // Create Controls
    CreateControls(true, false, true);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETACTIVETRANSFERS_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTransfers::CWidgetActiveTransfers - Function End"));
}

CWidgetActiveTransfers::~CWidgetActiveTransfers()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTransfers::~CWidgetActiveTransfers - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();

    // Unregister host status events
    pState->UnregisterEventHandler(this, wxEVT_BSLHOSTSTATUS_UPDATE, m_hHost, NULL);

    // Register for transfer events
    pState->UnregisterEventHandler(this, wxEVT_BSLTRANSFER_ADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLTRANSFER_DELETE, m_hHost, NULL);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetActiveTransfers::~CWidgetActiveTransfers - Function End"));
}

bool CWidgetActiveTransfers::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pResumeTransfersCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETRANSFERSRESUMETRANSFERS, pSkin->GetResumeIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pResumeTransfersCtrl->SetToolTip(_("Resume Transfers"));
    m_pButtonBarSizer->Add(m_pResumeTransfersCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 2);

    m_pSuspendTransfersCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETACTIVETRANSFERSUSPENDTRANSFERS, pSkin->GetSuspendIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pSuspendTransfersCtrl->SetToolTip(_("Suspend Transfers"));
    m_pButtonBarSizer->Add(m_pSuspendTransfersCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    return true;
}

bool CWidgetActiveTransfers::OnCreateContent(wxWindow* pParent, CSkinManager* WXUNUSED(pSkin), wxSize WXUNUSED(oIconSize))
{
    m_pContent = pParent;
    m_pContentSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_pContentSizer->AddGrowableCol(0);
    m_pContent->SetSizer(m_pContentSizer);

    return true;
}

void CWidgetActiveTransfers::OnInit(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLHostStatus bslHostStatus;
    std::vector<BSLTRANSFER> oTransfers;
    CWidgetActiveTransfer* pWidgetActiveTransfer = NULL;

    // Add any task instances we know about
    pState->EnumerateTransfers(m_hHost, oTransfers, false);
    for (std::vector<BSLTRANSFER>::iterator iter = oTransfers.begin(); iter != oTransfers.end(); iter++)
    {
        pWidgetActiveTransfer = new CWidgetActiveTransfer(m_pContent, m_hHost, *iter);
        m_ActiveTransfers.push_back(pWidgetActiveTransfer);
    }

    // Sort them by name
    std::stable_sort(m_ActiveTransfers.begin(), m_ActiveTransfers.end(), SortWidgetActiveTransfer);

    // Register the now sorted projects with the sizer
    for (std::vector<CWidgetActiveTransfer*>::iterator iter = m_ActiveTransfers.begin(); iter != m_ActiveTransfers.end(); iter++)
    {
        m_pContentSizer->Add(*iter, 0, wxGROW|wxALL, 1);
    }

    // Determine the initial state of the button bar
    pState->GetHostStatus(m_hHost, &bslHostStatus);
    if (bslHostStatus.GetNetworkSuspendReason())
    {
        if (m_pSuspendTransfersCtrl->IsShown())
        {
            m_pSuspendTransfersCtrl->Hide();
            m_pResumeTransfersCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (m_pResumeTransfersCtrl->IsShown())
        {
            m_pResumeTransfersCtrl->Hide();
            m_pSuspendTransfersCtrl->Show();
            UpdateHeaderLayout();
        }
    }

    // Update the layout
    Layout();

    // Register for host status events
    pState->RegisterEventHandler(this, wxEVT_BSLHOSTSTATUS_UPDATE, m_hHost, NULL);

    // Register for transfer events
    pState->RegisterEventHandler(this, wxEVT_BSLTRANSFER_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLTRANSFER_DELETE, m_hHost, NULL);
}

void CWidgetActiveTransfers::OnShowContents(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for transfers
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyTransfersUpdateInterval, 1);
}

void CWidgetActiveTransfers::OnHideContents(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for transfers
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyTransfersUpdateInterval, 0);
}

void CWidgetActiveTransfers::OnResumeTransfers(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->SetModeNetwork(m_hHost, CBSLClient::SetModeAlways, 0);
}

void CWidgetActiveTransfers::OnSuspendTransfers(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->SetModeNetwork(m_hHost, CBSLClient::SetModeNever, 0);
}

void CWidgetActiveTransfers::OnHostStatusUpdate(CBSLHostStatusEvent& event)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLHostStatus bslHostStatus;

    pState->GetHostStatus(event.GetHostHandle(), &bslHostStatus);

    if (bslHostStatus.GetNetworkSuspendReason())
    {
        if (m_pSuspendTransfersCtrl->IsShown())
        {
            m_pSuspendTransfersCtrl->Hide();
            m_pResumeTransfersCtrl->Show();
            UpdateHeaderLayout();
        }
    }
    else
    {
        if (m_pResumeTransfersCtrl->IsShown())
        {
            m_pResumeTransfersCtrl->Hide();
            m_pSuspendTransfersCtrl->Show();
            UpdateHeaderLayout();
        }
    }
}

void CWidgetActiveTransfers::OnTransferAdd(CBSLTransferEvent& event)
{
    CWidgetActiveTransfer* pWidgetActiveTransfer = NULL;

    pWidgetActiveTransfer = new CWidgetActiveTransfer(m_pContent, event.GetHostHandle(), event.GetTransferHandle());
    m_ActiveTransfers.push_back(pWidgetActiveTransfer);

    // Sort them by name
    std::stable_sort(m_ActiveTransfers.begin(), m_ActiveTransfers.end(), SortWidgetActiveTransfer);

    // Delete the old order and re-register the now sorted projects with the sizer
    m_pContentSizer->Clear();
    for (std::vector<CWidgetActiveTransfer*>::iterator iter = m_ActiveTransfers.begin(); iter != m_ActiveTransfers.end(); iter++)
    {
        m_pContentSizer->Add(*iter, 0, wxGROW|wxALL, 1);
    }

    wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
    AddPendingEvent(evt);
}

void CWidgetActiveTransfers::OnTransferDelete(CBSLTransferEvent& event)
{
    CWidgetActiveTransfer* pWidgetActiveTransfer = NULL;

    std::vector<CWidgetActiveTransfer*>::iterator iterActiveTransferWidgets = m_ActiveTransfers.begin();
    while (iterActiveTransferWidgets != m_ActiveTransfers.end())
    {
        pWidgetActiveTransfer = wxDynamicCast(*iterActiveTransferWidgets, CWidgetActiveTransfer);
        if (event.GetTransferHandle() == pWidgetActiveTransfer->GetTransferHandle())
        {
            iterActiveTransferWidgets = m_ActiveTransfers.erase(iterActiveTransferWidgets);
            m_pContentSizer->Detach(pWidgetActiveTransfer);
            delete pWidgetActiveTransfer;
        }
        else
        {
            iterActiveTransferWidgets++;
        }
    }

    wxCommandEvent evt(wxEVT_WIDGETBASE_RECALCSIZE);
    AddPendingEvent(evt);
}
