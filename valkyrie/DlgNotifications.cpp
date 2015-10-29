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
#include "Interface.h"
#include "ConfigManager.h"
#include "NotificationManager.h"
#include "DlgNotification.h"
#include "DlgNotifications.h"


#define COLUMN_TIME    0
#define COLUMN_PROJECT 1
#define COLUMN_SUBJECT 2


// TODO: Upgrade to 2.9 before any production release of a 64-bit client package.
//
#if wxCHECK_VERSION(2, 9, 0)
int wxCALLBACK SortNotificationsListCtrl(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
#else
int wxCALLBACK SortNotificationsListCtrl(long item1, long item2, long WXUNUSED(sortData))
#endif
{
    CBSLNotification bslItem1;
    CBSLNotification bslItem2;

    wxGetApp().GetState()->GetNotification((BSLNOTIFICATION)item1, &bslItem1);
    wxGetApp().GetState()->GetNotification((BSLNOTIFICATION)item2, &bslItem2);

    if (bslItem1.GetCreateTime() > bslItem2.GetCreateTime())
        return -1;
    if (bslItem1.GetCreateTime() < bslItem2.GetCreateTime())
        return 1;
    return 0;
}


IMPLEMENT_DYNAMIC_CLASS(CNotificationsInboxPanel, wxPanel);

BEGIN_EVENT_TABLE(CNotificationsInboxPanel, wxPanel)
    EVT_BSLNOTIFICATION_ADD(CNotificationsInboxPanel::OnNotificationAdd)
    EVT_BSLNOTIFICATION_DELETE(CNotificationsInboxPanel::OnNotificationDelete)
    EVT_BSLNOTIFICATION_UPDATE(CNotificationsInboxPanel::OnNotificationUpdate)
    EVT_LIST_ITEM_SELECTED(ID_INBOXNOTIFICATIONS, CNotificationsInboxPanel::OnSelectionChange)
    EVT_LIST_ITEM_DESELECTED(ID_INBOXNOTIFICATIONS, CNotificationsInboxPanel::OnSelectionChange)
    EVT_LIST_ITEM_ACTIVATED(ID_INBOXNOTIFICATIONS, CNotificationsInboxPanel::OnActivated)
    EVT_BUTTON(ID_OPEN, CNotificationsInboxPanel::OnOpen)
    EVT_BUTTON(ID_MARKASREAD, CNotificationsInboxPanel::OnMarkAsRead)
    EVT_BUTTON(ID_MARKASUNREAD, CNotificationsInboxPanel::OnMarkAsUnread)
    EVT_BUTTON(ID_DELETE, CNotificationsInboxPanel::OnDelete)
END_EVENT_TABLE();

CNotificationsInboxPanel::CNotificationsInboxPanel()
{
}

CNotificationsInboxPanel::CNotificationsInboxPanel(wxWindow* parent, BSLHOST hHost)
{
    m_hHost = hHost;
    Create(parent);
}

CNotificationsInboxPanel::~CNotificationsInboxPanel()
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->UnregisterEventHandler(this, wxEVT_BSLNOTIFICATION_ADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLNOTIFICATION_UPDATE, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLNOTIFICATION_DELETE, m_hHost, NULL);
}

bool CNotificationsInboxPanel::Create(wxWindow* parent)
{
    m_pNotificationsCtrl = NULL;
    m_pOpenCtrl = NULL;
    m_pMarkAsReadCtrl = NULL;
    m_pMarkAsUnreadCtrl = NULL;
    m_pDeleteCtrl = NULL;

    CBSLClient* pState = wxGetApp().GetState();

    if (!wxPanel::Create(parent))
    {
        return FALSE;
    }

    CreateControls();
    CreateHeaders();

    PopulateNotifications();
    UpdateControls();

    // Register for notification events
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_UPDATE, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_DELETE, m_hHost, NULL);

    return TRUE;
}

void CNotificationsInboxPanel::CreateControls()
{
    int iMaxWidth = 0;

    wxFlexGridSizer* itemFlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer2->AddGrowableRow(0);
    itemFlexGridSizer2->AddGrowableCol(0);
    SetSizer(itemFlexGridSizer2);

    m_pNotificationsCtrl = new wxListView( this, ID_INBOXNOTIFICATIONS, wxDefaultPosition, wxSize(600, 400), wxLC_REPORT|wxLC_SINGLE_SEL );
    itemFlexGridSizer2->Add(m_pNotificationsCtrl, 0, wxGROW|wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemFlexGridSizer2->Add(itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP|wxALL, 5);

    m_pOpenCtrl = new wxButton( this, ID_OPEN, _("Open"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(m_pOpenCtrl, 0, wxGROW|wxALL, 5);

    m_pMarkAsReadCtrl = new wxButton( this, ID_MARKASREAD, _("Mark as Read"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(m_pMarkAsReadCtrl, 0, wxGROW|wxALL, 5);

    m_pMarkAsUnreadCtrl = new wxButton( this, ID_MARKASUNREAD, _("Mark as Unread"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(m_pMarkAsUnreadCtrl, 0, wxGROW|wxALL, 5);

    m_pDeleteCtrl = new wxButton( this, ID_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(m_pDeleteCtrl, 0, wxGROW|wxALL, 5);

    // Calculate the layout of the control
    itemFlexGridSizer2->CalcMin();

    // All the buttons should have the same width.
    iMaxWidth = m_pOpenCtrl->GetEffectiveMinSize().GetWidth();
    iMaxWidth = std::max(iMaxWidth, m_pMarkAsReadCtrl->GetEffectiveMinSize().GetWidth());
    iMaxWidth = std::max(iMaxWidth, m_pMarkAsUnreadCtrl->GetEffectiveMinSize().GetWidth());
    iMaxWidth = std::max(iMaxWidth, m_pDeleteCtrl->GetEffectiveMinSize().GetWidth());

    wxSize sz(iMaxWidth, -1);
    m_pOpenCtrl->SetMinSize(sz);
    m_pMarkAsReadCtrl->SetMinSize(sz);
    m_pMarkAsUnreadCtrl->SetMinSize(sz);
    m_pDeleteCtrl->SetMinSize(sz);
}

void CNotificationsInboxPanel::CreateHeaders()
{
    // Create List Header Items
    m_pNotificationsCtrl->InsertColumn(COLUMN_TIME, _("Time"), wxLIST_FORMAT_LEFT, 130);
    m_pNotificationsCtrl->InsertColumn(COLUMN_PROJECT, _("Project"), wxLIST_FORMAT_LEFT, 120);
    m_pNotificationsCtrl->InsertColumn(COLUMN_SUBJECT, _("Subject"), wxLIST_FORMAT_LEFT, 345);
}

void CNotificationsInboxPanel::PopulateNotifications()
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    std::vector<BSLNOTIFICATION> oNotifications;
    wxListItem item;
    wxUint32 iIndex;

    m_pNotificationsCtrl->DeleteAllItems();

    pState->EnumerateNotifications(m_hHost, 0, oNotifications, false);
    for (std::vector<BSLNOTIFICATION>::iterator iter = oNotifications.begin(); iter != oNotifications.end(); iter++)
    {
        pState->GetNotification(*iter, &bslNotification);

        if (!pNotificationManager->IsDeleted(bslNotification))
        {
            item.SetId(m_pNotificationsCtrl->GetItemCount());
            item.SetColumn(0);
            item.SetText(wxEmptyString);
            iIndex = m_pNotificationsCtrl->InsertItem(item);
            m_pNotificationsCtrl->SetItemPtrData(iIndex, (wxUIntPtr)bslNotification.GetNotificationHandle());

            UpdateNotification(iIndex, bslNotification);
        }
    }

    if (m_pNotificationsCtrl->GetItemCount())
    {
        m_pNotificationsCtrl->SetColumnWidth(COLUMN_TIME, wxLIST_AUTOSIZE);
        m_pNotificationsCtrl->SetColumnWidth(COLUMN_SUBJECT, wxLIST_AUTOSIZE);

        m_pNotificationsCtrl->SortItems(SortNotificationsListCtrl, NULL);
        m_pNotificationsCtrl->Select(0, true);
    }
}

void CNotificationsInboxPanel::UpdateNotification(wxUint32 iIndex, CBSLNotification& bslNotification)
{
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    wxListItem item;
    wxFont font;

    item.SetId(iIndex);

    // If the notification is a system notification, it should be red.
    if ((bslNotification.GetCategory() == wxT("scheduler")) || (bslNotification.GetCategory() == wxT("client")))
    {
        item.SetTextColour(*wxRED);
    }
    else
    {
        item.SetTextColour(*wxBLACK);
    }

    // If the notification hasn't been read before, it should be bold.
    if (!pNotificationManager->IsRead(bslNotification))
    {
        font = item.GetFont();
        font.SetWeight(wxFONTWEIGHT_BOLD);
        item.SetFont(font);
    }
    else
    {
        font = item.GetFont();
        font.SetWeight(wxFONTWEIGHT_NORMAL);
        item.SetFont(font);
    }

    //
    item.SetColumn(COLUMN_TIME);
    item.SetText(bslNotification.GetCreateTime().Format());
    m_pNotificationsCtrl->SetItem(item);

    //
    item.SetColumn(COLUMN_PROJECT);
    item.SetText(bslNotification.GetProject());
    m_pNotificationsCtrl->SetItem(item);

    //
    item.SetColumn(COLUMN_SUBJECT);
    item.SetText(bslNotification.GetTitle());
    m_pNotificationsCtrl->SetItem(item);
}

void CNotificationsInboxPanel::UpdateControls()
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    wxInt32 iIndex;

    iIndex = m_pNotificationsCtrl->GetFirstSelected();
    if (iIndex >= 0)
    {
        pState->GetNotification((BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(iIndex), &bslNotification);

        if (pNotificationManager->IsRead(bslNotification))
        {
            m_pOpenCtrl->Show(true);
            m_pOpenCtrl->Enable(true);
            m_pMarkAsReadCtrl->Show(false);
            m_pMarkAsReadCtrl->Enable(false);
            m_pMarkAsUnreadCtrl->Show(true);
            m_pMarkAsUnreadCtrl->Enable(true);
            m_pDeleteCtrl->Show(true);
            m_pDeleteCtrl->Enable(true);
        }
        else
        {
            m_pOpenCtrl->Show(true);
            m_pOpenCtrl->Enable(true);
            m_pMarkAsReadCtrl->Show(true);
            m_pMarkAsReadCtrl->Enable(true);
            m_pMarkAsUnreadCtrl->Show(false);
            m_pMarkAsUnreadCtrl->Enable(false);
            m_pDeleteCtrl->Show(true);
            m_pDeleteCtrl->Enable(true);
        }
    }
    else
    {
        m_pOpenCtrl->Show(true);
        m_pOpenCtrl->Enable(false);
        m_pMarkAsReadCtrl->Show(true);
        m_pMarkAsReadCtrl->Enable(false);
        m_pMarkAsUnreadCtrl->Show(false);
        m_pMarkAsUnreadCtrl->Enable(false);
        m_pDeleteCtrl->Show(true);
        m_pDeleteCtrl->Enable(false);
    }

    Layout();
}

void CNotificationsInboxPanel::OnNotificationAdd(CBSLNotificationEvent& event)
{
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    wxListItem item;
    wxUint32 iIndex;

    if (BSLERR_SUCCESS == event.GetNotification(&bslNotification))
    {
        if (!pNotificationManager->IsDeleted(bslNotification))
        {
            item.SetId(m_pNotificationsCtrl->GetItemCount());
            item.SetColumn(0);
            item.SetText(wxEmptyString);
            iIndex = m_pNotificationsCtrl->InsertItem(item);
            m_pNotificationsCtrl->SetItemPtrData(iIndex, (wxUIntPtr)bslNotification.GetNotificationHandle());

            UpdateNotification(iIndex, bslNotification);
        }
    }
}

void CNotificationsInboxPanel::OnNotificationDelete(CBSLNotificationEvent& event)
{
    m_pNotificationsCtrl->DeleteItem(m_pNotificationsCtrl->FindItem(-1, (wxUIntPtr)event.GetNotificationHandle()));
}

void CNotificationsInboxPanel::OnNotificationUpdate(CBSLNotificationEvent& event)
{
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    wxListItem item;
    wxInt32 iIndex;

    if (BSLERR_SUCCESS == event.GetNotification(&bslNotification))
    {
        iIndex = m_pNotificationsCtrl->FindItem(-1, (wxUIntPtr)bslNotification.GetNotificationHandle());
        if (iIndex >= 0)
        {
            if (!pNotificationManager->IsDeleted(bslNotification))
            {
                UpdateNotification(iIndex, bslNotification);
            }
            else
            {
                m_pNotificationsCtrl->DeleteItem(iIndex);
            }
        }
        else
        {
            if (!pNotificationManager->IsDeleted(bslNotification))
            {
                item.SetId(m_pNotificationsCtrl->GetItemCount());
                item.SetColumn(0);
                item.SetText(wxEmptyString);
                iIndex = m_pNotificationsCtrl->InsertItem(item);
                m_pNotificationsCtrl->SetItemPtrData(iIndex, (wxUIntPtr)bslNotification.GetNotificationHandle());

                UpdateNotification(iIndex, bslNotification);

                m_pNotificationsCtrl->SortItems(SortNotificationsListCtrl, NULL);
            }
        }
    }

    UpdateControls();
}

void CNotificationsInboxPanel::OnSelectionChange(wxListEvent& WXUNUSED(event))
{
    UpdateControls();
}

void CNotificationsInboxPanel::OnActivated(wxListEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    BSLNOTIFICATION hNotification;

    hNotification = (BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected());

    pState->GetNotification(hNotification, &bslNotification);

    pNotificationManager->MarkRead(bslNotification, true);

    CDlgNotification dlgNotification(m_hHost, hNotification);
    dlgNotification.ShowModal();
}

void CNotificationsInboxPanel::OnOpen(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    BSLNOTIFICATION hNotification;

    hNotification = (BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected());

    pState->GetNotification(hNotification, &bslNotification);

    pNotificationManager->MarkRead(bslNotification, true);

    CDlgNotification dlgNotification(m_hHost, hNotification);
    dlgNotification.ShowModal();
}

void CNotificationsInboxPanel::OnMarkAsRead(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;

    pState->GetNotification((BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected()), &bslNotification);

    pNotificationManager->MarkRead(bslNotification, true);
}

void CNotificationsInboxPanel::OnMarkAsUnread(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;

    pState->GetNotification((BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected()), &bslNotification);

    pNotificationManager->MarkRead(bslNotification, false);
}

void CNotificationsInboxPanel::OnDelete(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;

    pState->GetNotification((BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected()), &bslNotification);

    pNotificationManager->MarkDeleted(bslNotification, true);
}


IMPLEMENT_DYNAMIC_CLASS(CNotificationsGarbagePanel, wxPanel);

BEGIN_EVENT_TABLE(CNotificationsGarbagePanel, wxPanel)
    EVT_BSLNOTIFICATION_ADD(CNotificationsGarbagePanel::OnNotificationAdd)
    EVT_BSLNOTIFICATION_DELETE(CNotificationsGarbagePanel::OnNotificationDelete)
    EVT_BSLNOTIFICATION_UPDATE(CNotificationsGarbagePanel::OnNotificationUpdate)
    EVT_LIST_ITEM_SELECTED(ID_GARBAGENOTIFICATIONS, CNotificationsGarbagePanel::OnSelectionChange)
    EVT_LIST_ITEM_DESELECTED(ID_GARBAGENOTIFICATIONS, CNotificationsGarbagePanel::OnSelectionChange)
    EVT_LIST_ITEM_ACTIVATED(ID_GARBAGENOTIFICATIONS, CNotificationsGarbagePanel::OnActivated)
    EVT_BUTTON(ID_OPEN, CNotificationsGarbagePanel::OnOpen)
    EVT_BUTTON(ID_UNDELETE, CNotificationsGarbagePanel::OnUndelete)
END_EVENT_TABLE();

CNotificationsGarbagePanel::CNotificationsGarbagePanel()
{
}

CNotificationsGarbagePanel::CNotificationsGarbagePanel(wxWindow* parent, BSLHOST hHost)
{
    m_hHost = hHost;
    Create(parent);
}

CNotificationsGarbagePanel::~CNotificationsGarbagePanel()
{
    CBSLClient* pState = wxGetApp().GetState();
    pState->UnregisterEventHandler(this, wxEVT_BSLNOTIFICATION_ADD, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLNOTIFICATION_UPDATE, m_hHost, NULL);
    pState->UnregisterEventHandler(this, wxEVT_BSLNOTIFICATION_DELETE, m_hHost, NULL);
}

bool CNotificationsGarbagePanel::Create(wxWindow* parent)
{
    m_pNotificationsCtrl = NULL;
    m_pOpenCtrl = NULL;
    m_pUndeleteCtrl = NULL;

    CBSLClient* pState = wxGetApp().GetState();

    if (!wxPanel::Create(parent))
    {
        return FALSE;
    }

    CreateControls();
    CreateHeaders();

    PopulateNotifications();

    // Register for notification events
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_UPDATE, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_DELETE, m_hHost, NULL);

    return TRUE;
}

void CNotificationsGarbagePanel::CreateControls()
{
    int iMaxWidth = 0;

    wxFlexGridSizer* itemFlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    itemFlexGridSizer2->AddGrowableRow(0);
    itemFlexGridSizer2->AddGrowableCol(0);
    SetSizer(itemFlexGridSizer2);

    m_pNotificationsCtrl = new wxListView( this, ID_GARBAGENOTIFICATIONS, wxDefaultPosition, wxSize(600, 400), wxLC_REPORT|wxLC_SINGLE_SEL );
    itemFlexGridSizer2->Add(m_pNotificationsCtrl, 0, wxGROW|wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemFlexGridSizer2->Add(itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP|wxALL, 5);

    m_pOpenCtrl = new wxButton( this, ID_OPEN, _("Open"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(m_pOpenCtrl, 0, wxGROW|wxALL, 5);

    m_pUndeleteCtrl = new wxButton( this, ID_UNDELETE, _("Undelete"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(m_pUndeleteCtrl, 0, wxGROW|wxALL, 5);

    // Calculate the layout of the control
    itemFlexGridSizer2->CalcMin();

    // All the buttons should have the same width.
    iMaxWidth = m_pOpenCtrl->GetEffectiveMinSize().GetWidth();
    iMaxWidth = std::max(iMaxWidth, m_pUndeleteCtrl->GetEffectiveMinSize().GetWidth());

    wxSize sz(iMaxWidth, -1);
    m_pOpenCtrl->SetMinSize(sz);
    m_pUndeleteCtrl->SetMinSize(sz);
}

void CNotificationsGarbagePanel::CreateHeaders()
{
    // Create List Header Items
    m_pNotificationsCtrl->InsertColumn(COLUMN_TIME, _("Time"), wxLIST_FORMAT_LEFT, 130);
    m_pNotificationsCtrl->InsertColumn(COLUMN_PROJECT, _("Project"), wxLIST_FORMAT_LEFT, 120);
    m_pNotificationsCtrl->InsertColumn(COLUMN_SUBJECT, _("Subject"), wxLIST_FORMAT_LEFT, 345);
}

void CNotificationsGarbagePanel::PopulateNotifications()
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    std::vector<BSLNOTIFICATION> oNotifications;
    wxListItem item;
    wxUint32 iIndex;

    m_pNotificationsCtrl->DeleteAllItems();

    pState->EnumerateNotifications(m_hHost, 0, oNotifications, false);
    for (std::vector<BSLNOTIFICATION>::iterator iter = oNotifications.begin(); iter != oNotifications.end(); iter++)
    {
        pState->GetNotification(*iter, &bslNotification);

        if (pNotificationManager->IsDeleted(bslNotification))
        {
            item.SetColumn(0);
            item.SetText(wxEmptyString);
            iIndex = m_pNotificationsCtrl->InsertItem(item);
            m_pNotificationsCtrl->SetItemPtrData(iIndex, (wxUIntPtr)bslNotification.GetNotificationHandle());

            UpdateNotification(iIndex, bslNotification);
        }
    }

    if (m_pNotificationsCtrl->GetItemCount())
    {
        m_pNotificationsCtrl->SetColumnWidth(COLUMN_TIME, wxLIST_AUTOSIZE);
        m_pNotificationsCtrl->SetColumnWidth(COLUMN_SUBJECT, wxLIST_AUTOSIZE);

        m_pNotificationsCtrl->SortItems(SortNotificationsListCtrl, NULL);
        m_pNotificationsCtrl->Select(0, true);
    }
}

void CNotificationsGarbagePanel::UpdateNotification(wxUint32 iIndex, CBSLNotification& bslNotification)
{
    wxListItem item;

    item.SetId(iIndex);

    //
    item.SetColumn(COLUMN_TIME);
    item.SetText(bslNotification.GetCreateTime().Format());
    m_pNotificationsCtrl->SetItem(item);

    //
    item.SetColumn(COLUMN_PROJECT);
    item.SetText(bslNotification.GetProject());
    m_pNotificationsCtrl->SetItem(item);

    //
    item.SetColumn(COLUMN_SUBJECT);
    item.SetText(bslNotification.GetTitle());
    m_pNotificationsCtrl->SetItem(item);
}

void CNotificationsGarbagePanel::UpdateControls()
{
    wxInt32 iIndex;

    iIndex = m_pNotificationsCtrl->GetFirstSelected();
    if (iIndex >= 0)
    {
        m_pOpenCtrl->Enable(true);
        m_pUndeleteCtrl->Enable(true);
    }
    else
    {
        m_pOpenCtrl->Enable(false);
        m_pUndeleteCtrl->Enable(false);
    }

    Layout();
}

void CNotificationsGarbagePanel::OnNotificationAdd(CBSLNotificationEvent& event)
{
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    wxListItem item;
    wxUint32 iIndex;

    if (BSLERR_SUCCESS == event.GetNotification(&bslNotification))
    {
        if (pNotificationManager->IsDeleted(bslNotification))
        {
            item.SetId(m_pNotificationsCtrl->GetItemCount());
            item.SetColumn(0);
            item.SetText(wxEmptyString);
            iIndex = m_pNotificationsCtrl->InsertItem(item);
            m_pNotificationsCtrl->SetItemPtrData(iIndex, (wxUIntPtr)bslNotification.GetNotificationHandle());

            UpdateNotification(iIndex, bslNotification);
        }
    }
}

void CNotificationsGarbagePanel::OnNotificationDelete(CBSLNotificationEvent& event)
{
    m_pNotificationsCtrl->DeleteItem(m_pNotificationsCtrl->FindItem(-1, (wxUIntPtr)event.GetNotificationHandle()));
}

void CNotificationsGarbagePanel::OnNotificationUpdate(CBSLNotificationEvent& event)
{
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    wxListItem item;
    wxInt32 iIndex;

    if (BSLERR_SUCCESS == event.GetNotification(&bslNotification))
    {
        iIndex = m_pNotificationsCtrl->FindItem(-1, (wxUIntPtr)bslNotification.GetNotificationHandle());
        if (iIndex >= 0)
        {
            if (pNotificationManager->IsDeleted(bslNotification))
            {
                UpdateNotification(iIndex, bslNotification);
            }
            else
            {
                m_pNotificationsCtrl->DeleteItem(iIndex);
            }
        }
        else
        {
            if (pNotificationManager->IsDeleted(bslNotification))
            {
                item.SetId(m_pNotificationsCtrl->GetItemCount());
                item.SetColumn(0);
                item.SetText(wxEmptyString);
                iIndex = m_pNotificationsCtrl->InsertItem(item);
                m_pNotificationsCtrl->SetItemPtrData(iIndex, (wxUIntPtr)bslNotification.GetNotificationHandle());

                UpdateNotification(iIndex, bslNotification);

                m_pNotificationsCtrl->SortItems(SortNotificationsListCtrl, NULL);
            }
        }
    }

    UpdateControls();
}

void CNotificationsGarbagePanel::OnSelectionChange(wxListEvent& WXUNUSED(event))
{
    UpdateControls();
}

void CNotificationsGarbagePanel::OnActivated(wxListEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    BSLNOTIFICATION hNotification;

    hNotification = (BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected());

    pState->GetNotification(hNotification, &bslNotification);

    pNotificationManager->MarkRead(bslNotification, true);

    CDlgNotification dlgNotification(m_hHost, hNotification);
    dlgNotification.ShowModal();
}

void CNotificationsGarbagePanel::OnOpen(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    BSLNOTIFICATION hNotification;

    hNotification = (BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected());

    pState->GetNotification(hNotification, &bslNotification);

    pNotificationManager->MarkRead(bslNotification, true);

    CDlgNotification dlgNotification(m_hHost, hNotification);
    dlgNotification.ShowModal();
}

void CNotificationsGarbagePanel::OnUndelete(wxCommandEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;

    pState->GetNotification((BSLNOTIFICATION)m_pNotificationsCtrl->GetItemData(m_pNotificationsCtrl->GetFirstSelected()), &bslNotification);

    pNotificationManager->MarkDeleted(bslNotification, false);
}


IMPLEMENT_DYNAMIC_CLASS(CDlgNotifications, wxPropertySheetDialog);

BEGIN_EVENT_TABLE(CDlgNotifications, wxPropertySheetDialog)
END_EVENT_TABLE();

CDlgNotifications::CDlgNotifications()
{
}

CDlgNotifications::CDlgNotifications(BSLHOST hHost)
{
    m_hHost = hHost;
    Create(NULL);
}

CDlgNotifications::CDlgNotifications(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, caption, pos, size, style, name);
}

CDlgNotifications::~CDlgNotifications()
{
    // Store window position and size for future use
    //
    SetConfigValue(wxEmptyString, wxT("Top"), GetPosition().y);
    SetConfigValue(wxEmptyString, wxT("Left"), GetPosition().x);
    SetConfigValue(wxEmptyString, wxT("Height"), GetSize().GetHeight());
    SetConfigValue(wxEmptyString, wxT("Width"), GetSize().GetWidth());
}

bool CDlgNotifications::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& WXUNUSED(pos), const wxSize& WXUNUSED(size), long style, const wxString& name)
{
    wxString strCaption = caption;
    if (strCaption.IsEmpty())
    {
        strCaption = _("BOINC-Sentinels - Notifications");
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

    SetExtraStyle(GetExtraStyle() | wxWS_EX_BLOCK_EVENTS);
    if (!wxPropertySheetDialog::Create(parent, id, strCaption, wxPoint(iLeft, iTop), wxSize(iWidth, iHeight), style, name))
    {
        return FALSE;
    }

    //
    CreateButtons(wxOK);

    // Inbox Panel
    CNotificationsInboxPanel* pInboxCtrl = new CNotificationsInboxPanel(GetBookCtrl(), m_hHost);
    GetBookCtrl()->AddPage(pInboxCtrl, _("Inbox"));

    // Garbage Panel
    CNotificationsGarbagePanel* pGarbageCtrl = new CNotificationsGarbagePanel(GetBookCtrl(), m_hHost);
    GetBookCtrl()->AddPage(pGarbageCtrl, _("Deleted Items"));

    LayoutDialog();
    return TRUE;
}

bool CDlgNotifications::GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue)
{
    return wxGetApp().GetConfigManager()->GetConfigValue(wxString(wxT("Notifications")), strSubComponent, strValueName, dwDefaultValue, pdwValue);
}

bool CDlgNotifications::SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue)
{
    return wxGetApp().GetConfigManager()->SetConfigValue(wxString(wxT("Notifications")), strSubComponent, strValueName, dwValue);
}
