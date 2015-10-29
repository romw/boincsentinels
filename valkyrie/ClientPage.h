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

#ifndef _CLIENTPAGE_H_
#define _CLIENTPAGE_H_

// Forward Declares
class CWidgetActiveTasks;
class CWidgetActiveTransfers;
class CWidgetEventLog;
class CWidgetNews;
class CWidgetProjects;
class CWidgetStatus;
class CWidgetUsage;

class CClientPage: public wxScrolledWindow
{
    DECLARE_DYNAMIC_CLASS(CClientPage)
    DECLARE_EVENT_TABLE()

public:

    CClientPage();
    CClientPage(wxWindow* pParent, BSLHOST hHost);
    ~CClientPage();

    void OnRecalcSize(wxCommandEvent& event);
    void OnDraw(wxDC& dc);

private:
    BSLHOST m_hHost;

    CWidgetActiveTasks* m_pActiveTasks;
    CWidgetActiveTransfers* m_pActiveTransfers;
    CWidgetEventLog* m_pEventLog;
    CWidgetNews* m_pNews;
    CWidgetProjects* m_pProjects;
    CWidgetStatus* m_pStatus;
    CWidgetUsage* m_pUsage;

    bool CreateControls();
};

#endif

