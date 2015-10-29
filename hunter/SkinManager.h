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

#ifndef _SKINMANAGER_H_
#define _SKINMANAGER_H_

class CSkinManager: public wxObject
{
    DECLARE_NO_COPY_CLASS(CSkinManager)

public:
    CSkinManager();
    virtual ~CSkinManager();

    wxIconBundle& GetBOINCSentinelsIcons();
    wxImage& GetSortAscendingIcon();
    wxImage& GetSortDescendingIcon();
    wxImage& GetNotificationsIcon();
    wxImage& GetProjectsIcon();
    wxImage& GetResourcesIcon();
    wxImage& GetStatisticsIcon();
    wxImage& GetTasksIcon();
    wxImage& GetTransfersIcon();

private:
    wxIconBundle m_BOINCSentinels;
    wxImage m_SortAscending;
    wxImage m_SortDescending;
    wxImage m_Notifications;
    wxImage m_Projects;
    wxImage m_Resources;
    wxImage m_Statistics;
    wxImage m_Tasks;
    wxImage m_Transfers;
};

#endif
