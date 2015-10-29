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

#ifndef _WIDGETACTIVETRANSFER_H_
#define _WIDGETACTIVETRANSFER_H_

class CWidgetActiveTransfer: public CWidgetBase
{
    DECLARE_DYNAMIC_CLASS(CWidgetActiveTransfer)
    DECLARE_EVENT_TABLE()

public:

    CWidgetActiveTransfer();
    CWidgetActiveTransfer(wxWindow* pParent, BSLHOST hHost, BSLTRANSFER hTransfer);
    ~CWidgetActiveTransfer();

    BSLHOST GetHostHandle();
    BSLTASKINSTANCE GetTransferHandle();

    void OnInit(wxCommandEvent& event);
    void OnShowContents(wxCommandEvent& event);
    void OnHideContents(wxCommandEvent& event);
    void OnRetry(wxCommandEvent& event);
    void OnAbort(wxCommandEvent& event);
    void OnProperties(wxCommandEvent& event);
    void OnTransferUpdate(CBSLTransferEvent& event);

protected:
    bool OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);
    bool OnCreateContent(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);

    void UpdateControls(CBSLTransfer& bslTransfer);
    void UpdateControlsButtonBar(CBSLTransfer& bslTransfer);
    void ToggleVisibility(CBSLTransfer& bslTransfer);

private:
    BSLHOST m_hHost;
    BSLTRANSFER m_hTransfer;

    wxWindow* m_pButtonBar;
    wxBoxSizer* m_pButtonBarSizer;
    CWidgetBitmapButton* m_pUpdateCtrl;
    CWidgetBitmapButton* m_pAbortCtrl;
    CWidgetBitmapButton* m_pPropertiesCtrl;

    wxWindow* m_pContent;
    wxFlexGridSizer* m_pContentSizer;
    wxStaticText* m_pProjectCtrl;
    CWidgetProgress* m_pProgressCtrl;
    CWidgetElapsed* m_pElapsedTimeCtrl;
    CWidgetTransferRate* m_pTransferRateCtrl;
    wxStaticText* m_pStatusCtrl;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_WIDGETACTIVETRANSFER_INIT, 10200 )
END_DECLARE_EVENT_TYPES()

#define EVT_WIDGETACTIVETRANSFER_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETACTIVETRANSFER_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

