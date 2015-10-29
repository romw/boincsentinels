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
#include "SkinManager.h"
#include "Interface.h"
#include "ConfigManager.h"
#include "DlgEventLog.h"

#define COLUMN_TIME    0
#define COLUMN_PROJECT 1
#define COLUMN_MESSAGE 2

IMPLEMENT_DYNAMIC_CLASS(CDlgEventLog, wxDialog);

BEGIN_EVENT_TABLE(CDlgEventLog, wxDialog)
    EVT_BSLMESSAGE_ADD(CDlgEventLog::OnMessagesAdd)
    EVT_BSLMESSAGE_UPDATE(CDlgEventLog::OnMessagesUpdate)
    EVT_BSLMESSAGE_DELETE(CDlgEventLog::OnMessagesDelete)
    EVT_BUTTON(wxID_COPY, CDlgEventLog::OnMessagesCopy)
    EVT_BSLPROJECT_ADD(CDlgEventLog::OnMessagesFilterAdd)
    EVT_COMBOBOX(ID_MESSAGESFILTER, CDlgEventLog::OnMessagesFilterChange)
    EVT_BSLPROJECT_DELETE(CDlgEventLog::OnMessagesFilterDelete)
    EVT_LIST_ITEM_SELECTED(ID_MESSAGES, CDlgEventLog::OnMessagesSelectionChange)
    EVT_LIST_ITEM_DESELECTED(ID_MESSAGES, CDlgEventLog::OnMessagesSelectionChange)
    EVT_BUTTON(wxID_OK, CDlgEventLog::OnOK)
END_EVENT_TABLE();

CDlgEventLog::CDlgEventLog()
{
}

CDlgEventLog::CDlgEventLog(BSLHOST hHost)
{
    m_hHost = hHost;
    Create(NULL);
}

CDlgEventLog::CDlgEventLog(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    Create(parent, id, caption, pos, size, style);
}

CDlgEventLog::~CDlgEventLog()
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_ADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLPROJECT_DELETE, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLMESSAGE_ADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLMESSAGE_UPDATE, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLMESSAGE_DELETE, m_hHost, NULL);

    // Store window position and size for future use
    //
    SetConfigValue(wxEmptyString, wxT("Top"), GetPosition().y);
    SetConfigValue(wxEmptyString, wxT("Left"), GetPosition().x);
    SetConfigValue(wxEmptyString, wxT("Height"), GetSize().GetHeight());
    SetConfigValue(wxEmptyString, wxT("Width"), GetSize().GetWidth());
}

bool CDlgEventLog::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& WXUNUSED(pos), const wxSize& WXUNUSED(size), long style)
{
    CBSLClient* pState = wxGetApp().GetState();

    m_pMessagesCopyCtrl = NULL;
    m_pMessagesFilterCtrl = NULL;
    m_pMessagesListViewCtrl = NULL;

    wxString strCaption = caption;
    if (strCaption.IsEmpty())
    {
        strCaption = _("BOINC-Sentinels - Event Log");
    }

    wxInt32 iMaxWidth = wxSystemSettings::GetMetric( wxSYS_SCREEN_X );
    wxInt32 iMaxHeight = wxSystemSettings::GetMetric( wxSYS_SCREEN_Y );
    wxInt32 iHeight = 600;
    wxInt32 iWidth = 800;
    wxInt32 iTop = 30;
    wxInt32 iLeft = iMaxWidth - iWidth - 30;

    // Restore window to its previous location
    //
    GetConfigValue( wxEmptyString, wxT("Top"), iTop, (long*)&iTop );
    GetConfigValue( wxEmptyString, wxT("Left"), iLeft, (long*)&iLeft );
    GetConfigValue( wxEmptyString, wxT("Height"), iHeight, (long*)&iHeight );
    GetConfigValue( wxEmptyString, wxT("Width"), iWidth, (long*)&iWidth );

    // Correct any problems due to possible resolution change
    //
    if ( iLeft < 0 ) iLeft = 30;
    if ( iTop < 0 ) iTop = 30;
    if ( iTop + iHeight > iMaxHeight ) iTop = iMaxHeight - iHeight - 30;
    if ( iLeft + iWidth > iMaxWidth ) iLeft = iMaxWidth - iWidth - 30;

    wxDialog::Create(parent, id, strCaption, wxPoint(iLeft, iTop), wxSize(iWidth, iHeight), style);
    SetExtraStyle(GetExtraStyle() | wxWS_EX_BLOCK_EVENTS);

    CreateControls();
    CreateHeaders();
    PopulateMessagesFilter();
    PopulateMessages();

    GetSizer()->SetDimension(0, 0, iWidth, iHeight);
    GetSizer()->Layout();

    // Register for project and message events
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLPROJECT_DELETE, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLMESSAGE_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLMESSAGE_UPDATE, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLMESSAGE_DELETE, m_hHost, NULL);

    return TRUE;
}

void CDlgEventLog::CreateControls()
{
    CDlgEventLog* itemDialog1 = this;
    CSkinManager* pSkin = wxGetApp().GetSkinManager();
    wxSize oSize = pSkin->GetSmallIconSize();

    wxFlexGridSizer* itemFlexGridSizer2 = new wxFlexGridSizer(3, 1, 0, 0);
    itemFlexGridSizer2->AddGrowableRow(1);
    itemFlexGridSizer2->AddGrowableCol(0);
    itemDialog1->SetSizer(itemFlexGridSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer3->AddGrowableCol(0);
    itemFlexGridSizer2->Add(itemFlexGridSizer3, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 0);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer3->Add(itemBoxSizer4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Tools:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pMessagesCopyCtrl = new wxBitmapButton( itemDialog1, wxID_COPY, pSkin->GetCopyIcon(oSize), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    m_pMessagesCopyCtrl->SetToolTip(_("Copy selected items"));
    itemBoxSizer4->Add(m_pMessagesCopyCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer3->Add(itemBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("Message Filter:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemStaticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemComboBox8Strings;
    m_pMessagesFilterCtrl = new wxComboBox( itemDialog1, ID_MESSAGESFILTER, wxEmptyString, wxDefaultPosition, wxDefaultSize, itemComboBox8Strings, wxCB_READONLY|wxCB_SORT );
    itemBoxSizer6->Add(m_pMessagesFilterCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pMessagesListViewCtrl = new wxListView( itemDialog1, ID_MESSAGES, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
    itemFlexGridSizer2->Add(m_pMessagesListViewCtrl, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer10 = new wxStdDialogButtonSizer;

    itemFlexGridSizer2->Add(itemStdDialogButtonSizer10, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton11->SetFocus();
    itemButton11->SetDefault();
    itemStdDialogButtonSizer10->AddButton(itemButton11);

    itemStdDialogButtonSizer10->Realize();
}

void CDlgEventLog::CreateHeaders()
{
    // Create List Header Items
    m_pMessagesListViewCtrl->InsertColumn(COLUMN_TIME, _("Time"), wxLIST_FORMAT_LEFT, 130);
    m_pMessagesListViewCtrl->InsertColumn(COLUMN_PROJECT, _("Project"), wxLIST_FORMAT_LEFT, 120);
    m_pMessagesListViewCtrl->InsertColumn(COLUMN_MESSAGE, _("Message"), wxLIST_FORMAT_LEFT, 520);
}

void CDlgEventLog::PopulateMessagesFilter()
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLProject oProject;
    std::vector<BSLPROJECT> oProjects;
    wxUint32 iIndex;

    m_pMessagesFilterCtrl->Clear();
    m_pMessagesFilterCtrl->Append(_("<None>"));

    pState->EnumerateProjects(m_hHost, oProjects, false);
    for (std::vector<BSLPROJECT>::iterator iter = oProjects.begin(); iter != oProjects.end(); iter++)
    {
        pState->GetProject(*iter, &oProject);

        if (!oProject.GetProjectName().IsEmpty())
        {
            iIndex = m_pMessagesFilterCtrl->Append(oProject.GetProjectName());
            m_pMessagesFilterCtrl->SetClientData(iIndex, oProject.GetProjectHandle());
        }
    }

    m_pMessagesFilterCtrl->SetValue(_("<None>"));
}

void CDlgEventLog::PopulateMessages()
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLMessage oMessage;
    CBSLProject oProject;
    std::vector<BSLMESSAGE> oMessages;
    wxListItem item;
    wxUint32 iIndex = 0;

    m_pMessagesListViewCtrl->DeleteAllItems();

    iIndex = m_pMessagesFilterCtrl->GetSelection();
    pState->GetProject(m_pMessagesFilterCtrl->GetClientData(iIndex), &oProject);

    pState->EnumerateMessages(m_hHost, 0, oMessages, false);
    for (std::vector<BSLMESSAGE>::iterator iter = oMessages.begin(); iter != oMessages.end(); iter++)
    {
        pState->GetMessage(*iter, &oMessage);

        if (_("<None>") != m_pMessagesFilterCtrl->GetValue())
        {
            // Does the message meet the filter criteria?
            if      (oMessage.GetProject().IsEmpty()){}
            else if (oMessage.GetProject() == oProject.GetProjectName()){}
            else if (oMessage.GetProject() == oProject.GetMasterURL()){}
            else continue;
        }

        item.Clear();
        item.SetId(iIndex);
        iIndex = m_pMessagesListViewCtrl->InsertItem(item);
        m_pMessagesListViewCtrl->SetItemPtrData(iIndex, (wxUIntPtr)oMessage.GetMessageHandle());

        UpdateMessage(iIndex, oMessage);

        ++iIndex;
    }

    // No messages are selected right now, disable the copy control.
    m_pMessagesCopyCtrl->Disable();

    m_pMessagesListViewCtrl->SetColumnWidth(COLUMN_TIME, wxLIST_AUTOSIZE);
    m_pMessagesListViewCtrl->SetColumnWidth(COLUMN_MESSAGE, wxLIST_AUTOSIZE);

    m_pMessagesListViewCtrl->EnsureVisible(m_pMessagesListViewCtrl->GetItemCount() - 1);
}

void CDlgEventLog::UpdateMessage(wxUint32 iIndex, CBSLMessage& oMessage)
{
    wxListItem item;

    item.SetId(iIndex);

    if (CBSLMessage::PriorityUserAlert == oMessage.GetPriority())
    {
        item.SetTextColour(*wxRED);
    }
    else
    {
        item.SetTextColour(*wxBLACK);
    }

    //
    item.SetColumn(COLUMN_TIME);
    item.SetText(oMessage.GetTimestamp().Format());
    m_pMessagesListViewCtrl->SetItem(item);

    //
    item.SetColumn(COLUMN_PROJECT);
    item.SetText(oMessage.GetProject());
    m_pMessagesListViewCtrl->SetItem(item);

    //
    item.SetColumn(COLUMN_MESSAGE);
    item.SetText(oMessage.GetMessageText());
    m_pMessagesListViewCtrl->SetItem(item);
}

void CDlgEventLog::OnMessagesAdd(CBSLMessageEvent& event)
{
    CBSLMessage oMessage;
    wxListItem item;
    wxUint32 iIndex;

    if (BSLERR_SUCCESS == event.GetMessage(&oMessage))
    {
        item.SetId(m_pMessagesListViewCtrl->GetItemCount());
        item.SetColumn(0);
        item.SetText(wxEmptyString);
        iIndex = m_pMessagesListViewCtrl->InsertItem(item);
        m_pMessagesListViewCtrl->SetItemPtrData(iIndex, (wxUIntPtr)event.GetMessageHandle());

        UpdateMessage(iIndex, oMessage);
    }
}

void CDlgEventLog::OnMessagesCopy(wxCommandEvent& WXUNUSED(event))
{
    bool bRetVal = false;
    CBSLClient* pState = wxGetApp().GetState();
    CBSLMessage oMessage;
    wxListItem item;
    wxInt32 iIndex = -1;
    wxInt32 iRowCount = 0;
    wxString strBuffer;
    wxString strClipboardData;

    // Count the number of items selected
    for (;;) {
        iIndex = m_pMessagesListViewCtrl->GetNextItem(
            iIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED
        );
        if (iIndex == -1) break;

        iRowCount++;
    }

    bRetVal = wxTheClipboard->Open();
    if (bRetVal) {
        wxTheClipboard->Clear();

        strClipboardData = wxEmptyString;
        strClipboardData.Alloc( iRowCount * 256 );

        // Reset the position indicator
        iIndex = -1;

        for (;;) {
            iIndex = m_pMessagesListViewCtrl->GetNextItem(
                iIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED
            );
            if (iIndex == -1) break;

            pState->GetMessage((BSLMESSAGE)m_pMessagesListViewCtrl->GetItemData(iIndex), &oMessage);

            strBuffer.Printf(
#ifdef __WXMSW__
                wxT("%s | %s | %s\r\n"),
#else
                wxT("%s | %s | %s\n"),
#endif
                oMessage.GetTimestamp().Format().c_str(),
                oMessage.GetProject().c_str(),
                oMessage.GetMessageText().c_str()
            );

            strClipboardData += strBuffer;
        }

        wxTheClipboard->SetData(new wxTextDataObject(strClipboardData));
        wxTheClipboard->Close();
    }
}

void CDlgEventLog::OnMessagesDelete(CBSLMessageEvent& event)
{
    wxInt32 iIndex = -1;
    iIndex = m_pMessagesListViewCtrl->FindItem(-1, (wxUIntPtr)event.GetMessageHandle());
    if (-1 != iIndex)
    {
        m_pMessagesListViewCtrl->DeleteItem(iIndex);
    }
}

void CDlgEventLog::OnMessagesUpdate(CBSLMessageEvent& event)
{
    CBSLMessage oMessage;
    wxInt32 iIndex = -1;

    iIndex = m_pMessagesListViewCtrl->FindItem(-1, (wxUIntPtr)event.GetMessageHandle());
    if (-1 != iIndex)
    {
        event.GetMessage(&oMessage);
        UpdateMessage(iIndex, oMessage);
    }
}

void CDlgEventLog::OnMessagesFilterAdd(CBSLProjectEvent& event)
{
    CBSLProject oProject;
    wxUint32 iIndex;

    if (BSLERR_SUCCESS == event.GetProject(&oProject))
    {
        iIndex = m_pMessagesFilterCtrl->Append(oProject.GetProjectName());
        m_pMessagesFilterCtrl->SetClientData(iIndex, oProject.GetProjectHandle());
    }
}

void CDlgEventLog::OnMessagesFilterChange(wxCommandEvent& WXUNUSED(event))
{
    PopulateMessages();
}

void CDlgEventLog::OnMessagesFilterDelete(CBSLProjectEvent& event)
{
    for (wxUint32 iIndex = 0; iIndex < m_pMessagesFilterCtrl->GetCount(); ++iIndex)
    {
        if (event.GetProjectHandle() == m_pMessagesFilterCtrl->GetClientData(iIndex))
        {
            m_pMessagesFilterCtrl->Delete(iIndex);
        }
    }
}

void CDlgEventLog::OnMessagesSelectionChange(wxListEvent& WXUNUSED(event))
{
    wxInt32 iIndex = -1;

    iIndex = m_pMessagesListViewCtrl->GetNextItem(
        iIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED
    );

    if (-1 != iIndex)
    {
        m_pMessagesCopyCtrl->Enable();
    }
    else
    {
        m_pMessagesCopyCtrl->Disable();
    }
}

void CDlgEventLog::OnOK(wxCommandEvent& WXUNUSED(event))
{
    EndModal(wxID_OK);
}

bool CDlgEventLog::GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue)
{
    return wxGetApp().GetConfigManager()->GetConfigValue(wxString(wxT("Event Log")), strSubComponent, strValueName, dwDefaultValue, pdwValue);
}

bool CDlgEventLog::SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue)
{
    return wxGetApp().GetConfigManager()->SetConfigValue(wxString(wxT("Event Log")), strSubComponent, strValueName, dwValue);
}
