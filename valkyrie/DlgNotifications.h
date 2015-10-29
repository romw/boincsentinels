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

#ifndef _DLGNOTIFICATIONS_H_
#define _DLGNOTIFICATIONS_H_

#define ID_DIALOG 10000
#define SYMBOL_CDLGNOTIFICATIONS_STYLE wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER
#define SYMBOL_CDLGNOTIFICATIONS_TITLE wxT("")
#define SYMBOL_CDLGNOTIFICATIONS_IDNAME ID_DIALOG
#define SYMBOL_CDLGNOTIFICATIONS_SIZE wxDefaultSize
#define SYMBOL_CDLGNOTIFICATIONS_POSITION wxDefaultPosition
#define ID_INBOXNOTIFICATIONS 10001
#define ID_OPEN 10002
#define ID_MARKASREAD 10003
#define ID_MARKASUNREAD 10004
#define ID_DELETE 10005
#define ID_GARBAGENOTIFICATIONS 10006
#define ID_UNDELETE 10007

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

class CNotificationsInboxPanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS(CNotificationsInboxPanel)
    DECLARE_EVENT_TABLE()

public:
    CNotificationsInboxPanel();
    CNotificationsInboxPanel(wxWindow* parent, BSLHOST hHost);
    virtual ~CNotificationsInboxPanel();

    bool Create(wxWindow* parent);

    void OnNotificationAdd(CBSLNotificationEvent& event);
    void OnNotificationDelete(CBSLNotificationEvent& event);
    void OnNotificationUpdate(CBSLNotificationEvent& event);
    void OnSelectionChange(wxListEvent& event);
    void OnActivated(wxListEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnMarkAsRead(wxCommandEvent& event);
    void OnMarkAsUnread(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);

private:
    void CreateControls();
    void CreateHeaders();

    void PopulateNotifications();

    void UpdateNotification(wxUint32 iIndex, CBSLNotification& bslNotification);
    void UpdateControls();

    BSLHOST m_hHost;
    wxListView* m_pNotificationsCtrl;
    wxButton* m_pOpenCtrl;
    wxButton* m_pMarkAsReadCtrl;
    wxButton* m_pMarkAsUnreadCtrl;
    wxButton* m_pDeleteCtrl;
};

class CNotificationsGarbagePanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS(CNotificationsGarbagePanel)
    DECLARE_EVENT_TABLE()

public:
    CNotificationsGarbagePanel();
    CNotificationsGarbagePanel(wxWindow* parent, BSLHOST hHost);
    virtual ~CNotificationsGarbagePanel();

    bool Create(wxWindow* parent);

    void OnNotificationAdd(CBSLNotificationEvent& event);
    void OnNotificationDelete(CBSLNotificationEvent& event);
    void OnNotificationUpdate(CBSLNotificationEvent& event);
    void OnSelectionChange(wxListEvent& event);
    void OnActivated(wxListEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnUndelete(wxCommandEvent& event);

private:
    void CreateControls();
    void CreateHeaders();

    void PopulateNotifications();
    void UpdateControls();

    void UpdateNotification(wxUint32 iIndex, CBSLNotification& bslNotification);

    BSLHOST m_hHost;
    wxListView* m_pNotificationsCtrl;
    wxButton* m_pOpenCtrl;
    wxButton* m_pUndeleteCtrl;
};

class CDlgNotifications: public wxPropertySheetDialog
{
    DECLARE_DYNAMIC_CLASS(CDlgNotifications)
    DECLARE_EVENT_TABLE()

public:
    CDlgNotifications();
    CDlgNotifications(BSLHOST hHost);
    CDlgNotifications(wxWindow* parent, wxWindowID id = SYMBOL_CDLGNOTIFICATIONS_IDNAME, const wxString& caption =
        SYMBOL_CDLGNOTIFICATIONS_TITLE, const wxPoint& pos = SYMBOL_CDLGNOTIFICATIONS_POSITION,
        const wxSize& size = SYMBOL_CDLGNOTIFICATIONS_SIZE, long style = SYMBOL_CDLGNOTIFICATIONS_STYLE,
        const wxString& name = wxDialogNameStr);

    virtual ~CDlgNotifications();

    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_CDLGNOTIFICATIONS_IDNAME, const wxString& caption =
        SYMBOL_CDLGNOTIFICATIONS_TITLE, const wxPoint& pos = SYMBOL_CDLGNOTIFICATIONS_POSITION,
        const wxSize& size = SYMBOL_CDLGNOTIFICATIONS_SIZE, long style = SYMBOL_CDLGNOTIFICATIONS_STYLE,
        const wxString& name = wxDialogNameStr);

    void OnOK(wxCommandEvent& event);

private:
    bool GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue);
    bool SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue);

    BSLHOST m_hHost;
};

#endif

