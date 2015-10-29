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

#ifndef _WIDGETNEWS_H_
#define _WIDGETNEWS_H_

class CWidgetNews: public CWidgetBase
{
    DECLARE_DYNAMIC_CLASS(CWidgetNews)
    DECLARE_EVENT_TABLE()

public:

    CWidgetNews();
    CWidgetNews(wxWindow* pParent, BSLHOST hHost);
    ~CWidgetNews();

    void OnInit(wxCommandEvent& event);
    void OnNotificationUpdate(CBSLNotificationEvent& event);
    void OnProperties(wxCommandEvent& event);

    void UpdateInterface();

protected:
    bool OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize);

private:
    BSLHOST m_hHost;

    wxUint32 m_uiAlertCount;
    wxUint32 m_uiAnnouncementCount;

    wxWindow* m_pButtonBar;
    wxBoxSizer* m_pButtonBarSizer;
    CWidgetStaticText* m_pAlertCountCtrl;
    CWidgetStaticBitmap* m_pAlertIconCtrl;
    CWidgetStaticText* m_pAnnouncementCountCtrl;
    CWidgetStaticBitmap* m_pAnnouncementIconCtrl;
    CWidgetBitmapButton* m_pPropertiesCtrl;
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_WIDGETNEWS_INIT, 10200 )
END_DECLARE_EVENT_TYPES()

#define EVT_WIDGETNEWS_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_WIDGETNEWS_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

