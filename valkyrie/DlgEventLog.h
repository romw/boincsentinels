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

#ifndef _DLGEVENTLOG_H_
#define _DLGEVENTLOG_H_

#define ID_DIALOG 10000
#define SYMBOL_CDLGEVENTLOG_STYLE wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER
#define SYMBOL_CDLGEVENTLOG_TITLE wxT("")
#define SYMBOL_CDLGEVENTLOG_IDNAME ID_DIALOG
#define SYMBOL_CDLGEVENTLOG_SIZE wxDefaultSize
#define SYMBOL_CDLGEVENTLOG_POSITION wxDefaultPosition
#define ID_MESSAGESFILTER 10001
#define ID_MESSAGES 10002

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

class CDlgEventLog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS(CDlgEventLog)
    DECLARE_EVENT_TABLE()

public:
    CDlgEventLog();
    CDlgEventLog(BSLHOST hHost);
    CDlgEventLog(wxWindow* parent, wxWindowID id = SYMBOL_CDLGEVENTLOG_IDNAME, const wxString& caption =
        SYMBOL_CDLGEVENTLOG_TITLE, const wxPoint& pos = SYMBOL_CDLGEVENTLOG_POSITION,
        const wxSize& size = SYMBOL_CDLGEVENTLOG_SIZE, long style = SYMBOL_CDLGEVENTLOG_STYLE);

    virtual ~CDlgEventLog();

    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_CDLGEVENTLOG_IDNAME, const wxString& caption =
        SYMBOL_CDLGEVENTLOG_TITLE, const wxPoint& pos = SYMBOL_CDLGEVENTLOG_POSITION,
        const wxSize& size = SYMBOL_CDLGEVENTLOG_SIZE, long style = SYMBOL_CDLGEVENTLOG_STYLE);

    void OnMessagesAdd(CBSLMessageEvent& event);
    void OnMessagesCopy(wxCommandEvent& event);
    void OnMessagesDelete(CBSLMessageEvent& event);
    void OnMessagesFilterAdd(CBSLProjectEvent& event);
    void OnMessagesFilterChange(wxCommandEvent& event);
    void OnMessagesFilterDelete(CBSLProjectEvent& event);
    void OnMessagesSelectionChange(wxListEvent& event);
    void OnMessagesUpdate(CBSLMessageEvent& event);
    void OnOK(wxCommandEvent& event);

private:
    void CreateControls();
    void CreateHeaders();

    void PopulateMessagesFilter();
    void PopulateMessages();

    void UpdateMessage(wxUint32 iIndex, CBSLMessage& oMessage);

    bool GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue);
    bool SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue);

    BSLHOST m_hHost;

    wxBitmapButton* m_pMessagesCopyCtrl;
    wxComboBox* m_pMessagesFilterCtrl;
    wxListView* m_pMessagesListViewCtrl;
};

#endif

