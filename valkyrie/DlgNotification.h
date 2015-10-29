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

#ifndef _DLGNOTIFICATION_H_
#define _DLGNOTIFICATION_H_

#define ID_DIALOG 10000
#define SYMBOL_CDLGNOTIFICATION_STYLE wxDEFAULT_DIALOG_STYLE
#define SYMBOL_CDLGNOTIFICATION_TITLE wxT("")
#define SYMBOL_CDLGNOTIFICATION_IDNAME ID_DIALOG
#define SYMBOL_CDLGNOTIFICATION_SIZE wxSize(400, 300)
#define SYMBOL_CDLGNOTIFICATION_POSITION wxDefaultPosition
#define ID_PROJECT 10001
#define ID_LINK 10002
#define ID_SUBJECT 10003
#define ID_BODY 10004

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

class CDlgNotification: public wxDialog
{
    DECLARE_DYNAMIC_CLASS(CDlgNotification)
    DECLARE_EVENT_TABLE()

public:
    CDlgNotification();
    CDlgNotification(BSLHOST hHost, BSLNOTIFICATION hNotification);
    CDlgNotification(wxWindow* parent, wxWindowID id = SYMBOL_CDLGNOTIFICATION_IDNAME, const wxString& caption =
        SYMBOL_CDLGNOTIFICATION_TITLE, const wxPoint& pos = SYMBOL_CDLGNOTIFICATION_POSITION,
        const wxSize& size = SYMBOL_CDLGNOTIFICATION_SIZE, long style = SYMBOL_CDLGNOTIFICATION_STYLE);
    virtual ~CDlgNotification();

    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_CDLGNOTIFICATION_IDNAME, const wxString& caption =
        SYMBOL_CDLGNOTIFICATION_TITLE, const wxPoint& pos = SYMBOL_CDLGNOTIFICATION_POSITION,
        const wxSize& size = SYMBOL_CDLGNOTIFICATION_SIZE, long style = SYMBOL_CDLGNOTIFICATION_STYLE);

    void OnNotificationUpdate(CBSLNotificationEvent& event);

private:
    void CreateControls();
    void UpdateControls(CBSLNotification& bslNotification);

    BSLHOST m_hHost;
    BSLNOTIFICATION m_hNotification;
    wxStaticText* m_pProjectCtrl;
    wxHyperlinkCtrl* m_pLinkCtrl;
    wxStaticText* m_pSubjectCtrl;
    wxWebView* m_pBodyCtrl;
};

#endif
// _DLGNOTIFICATION_H_
