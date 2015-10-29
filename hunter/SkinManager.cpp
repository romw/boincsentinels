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

#include "stdwx.h"
#include "Hunter.h"
#include "SkinManager.h"

// XPM Images
#ifndef __WXMSW__
#include "res/boincsentinels16.xpm"
#include "res/boincsentinels32.xpm"
#include "res/boincsentinels48.xpm"
#include "res/boincsentinels128.xpm"
#include "res/boincsentinels256.xpm"
#endif
#include "res/sortascending.xpm"
#include "res/sortdescending.xpm"
#include "res/mess.xpm"
#include "res/proj.xpm"
#include "res/usage.xpm"
#include "res/stats.xpm"
#include "res/result.xpm"
#include "res/xfer.xpm"


CSkinManager::CSkinManager() :
wxObject()
{
#ifdef __WXMSW__
    m_BOINCSentinels.AddIcon(wxICON(boincsentinels));
#else
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels16_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels32_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels48_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels128_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels256_xpm));
#endif
    m_SortAscending = wxImage(sortascending_xpm);
    m_SortDescending = wxImage(sortdescending_xpm);
    m_Notifications = wxImage(mess_xpm);
    m_Projects = wxImage(proj_xpm);
    m_Resources = wxImage(usage_xpm);
    m_Statistics = wxImage(stats_xpm);
    m_Tasks = wxImage(result_xpm);
    m_Transfers = wxImage(xfer_xpm);
}

CSkinManager::~CSkinManager()
{
}

wxIconBundle& CSkinManager::GetBOINCSentinelsIcons()
{
    return m_BOINCSentinels;
}

wxImage& CSkinManager::GetSortAscendingIcon()
{
    return m_SortAscending;
}

wxImage& CSkinManager::GetSortDescendingIcon()
{
    return m_SortDescending;
}

wxImage& CSkinManager::GetNotificationsIcon()
{
    return m_Notifications;
}

wxImage& CSkinManager::GetProjectsIcon()
{
    return m_Projects;
}

wxImage& CSkinManager::GetResourcesIcon()
{
    return m_Resources;
}

wxImage& CSkinManager::GetStatisticsIcon()
{
    return m_Statistics;
}

wxImage& CSkinManager::GetTasksIcon()
{
    return m_Tasks;
}

wxImage& CSkinManager::GetTransfersIcon()
{
    return m_Transfers;
}

