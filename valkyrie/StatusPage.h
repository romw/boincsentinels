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

#ifndef _STATUSPAGE_H_
#define _STATUSPAGE_H_

class CStatusPage: public wxPanel
{
    DECLARE_DYNAMIC_CLASS(CStatusPage)
    DECLARE_EVENT_TABLE()

public:

    CStatusPage();
    CStatusPage(wxWindow* pParent);
    ~CStatusPage();

    void OnInit(wxCommandEvent& event);
    void OnPageError(wxWebViewEvent& event);
    void OnPageLinkClicked(wxWebViewEvent& event);

private:

    wxWebView* m_pCurrentStatus;

    bool CreateControls();

};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_STATUSPAGE_INIT, 10100 )
END_DECLARE_EVENT_TYPES()

#define EVT_STATUSPAGE_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_STATUSPAGE_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

