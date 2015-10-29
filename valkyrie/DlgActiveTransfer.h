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

#ifndef _DLGACTIVETRANSFER_H_
#define _DLGACTIVETRANSFER_H_

#define ID_DIALOG 10000
#define SYMBOL_CDLGACTIVETRANSFER_STYLE wxDEFAULT_DIALOG_STYLE
#define SYMBOL_CDLGACTIVETRANSFER_TITLE wxT("")
#define SYMBOL_CDLGACTIVETRANSFER_IDNAME ID_DIALOG
#define SYMBOL_CDLGACTIVETRANSFER_SIZE wxSize(400, 300)
#define SYMBOL_CDLGACTIVETRANSFER_POSITION wxDefaultPosition
#define ID_PROJECT 10001
#define ID_NAME 10002
#define ID_PROGRESS 10003
#define ID_SIZE 10004
#define ID_ELAPSEDTIME 10005
#define ID_SPEED 10006
#define ID_STATUS 10007

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

class CDlgStaticText;
class CDlgDateTime;
class CDlgTimeSpan;
class CDlgProgress;
class CDlgByteCount;
class CDlgByteRate;

class CDlgActiveTransfer: public wxDialog
{
    DECLARE_DYNAMIC_CLASS(CDlgActiveTransfer)
    DECLARE_EVENT_TABLE()

public:
    CDlgActiveTransfer();
    CDlgActiveTransfer(BSLHOST hHost, BSLTRANSFER hTransfer);
    CDlgActiveTransfer(wxWindow* parent, wxWindowID id = SYMBOL_CDLGACTIVETRANSFER_IDNAME, const wxString& caption =
        SYMBOL_CDLGACTIVETRANSFER_TITLE, const wxPoint& pos = SYMBOL_CDLGACTIVETRANSFER_POSITION,
        const wxSize& size = SYMBOL_CDLGACTIVETRANSFER_SIZE, long style = SYMBOL_CDLGACTIVETRANSFER_STYLE);
    virtual ~CDlgActiveTransfer();

    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_CDLGACTIVETRANSFER_IDNAME, const wxString& caption =
        SYMBOL_CDLGACTIVETRANSFER_TITLE, const wxPoint& pos = SYMBOL_CDLGACTIVETRANSFER_POSITION,
        const wxSize& size = SYMBOL_CDLGACTIVETRANSFER_SIZE, long style = SYMBOL_CDLGACTIVETRANSFER_STYLE);

    void OnTransferUpdate(CBSLTransferEvent& event);

private:
    void CreateControls();
    void UpdateControls(CBSLTransfer& bslTransfer);

    BSLHOST m_hHost;
    BSLTRANSFER m_hTransfer;

    CDlgStaticText* m_pProjectCtrl;
    CDlgStaticText* m_pNameCtrl;
    CDlgProgress* m_pProgressCtrl;
    CDlgByteCount* m_pSizeCtrl;
    CDlgTimeSpan* m_pElapsedTimeCtrl;
    CDlgByteRate* m_pSpeedCtrl;
    CDlgStaticText* m_pStatusCtrl;
};

#endif
// _DLGACTIVETASK_H_
