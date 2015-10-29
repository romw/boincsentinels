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

#ifndef _VIEWTRANSFERS_H_
#define _VIEWTRANSFERS_H_

class CViewTransfers: public CViewBase
{
    DECLARE_DYNAMIC_CLASS(CViewTransfers)
    DECLARE_EVENT_TABLE()

public:

    CViewTransfers();
    CViewTransfers(wxNotebook* pNotebook, BSLHOST hHost);
    ~CViewTransfers();

    virtual wxString&       GetViewName();
    virtual wxString&       GetViewDisplayName();
    virtual wxImage&        GetViewIcon();
    virtual const int       GetViewCurrentViewPage();
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_VIEWTRANSFERS_INIT, 10100 )
END_DECLARE_EVENT_TYPES()

#define EVT_VIEWTRANSFERS_INIT(fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_VIEWTRANSFERS_INIT, -1, -1, (wxObjectEventFunction) (wxEventFunction) &fn, NULL),

#endif

