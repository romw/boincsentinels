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
#include "Valkyrie.h"
#include "SkinManager.h"

// XPM Images
#ifndef __WXMSW__
#include "res/boincsentinels16.xpm"
#include "res/boincsentinels32.xpm"
#include "res/boincsentinels48.xpm"
#include "res/boincsentinels128.xpm"
#include "res/boincsentinels256.xpm"
#include "res/computer.xpm"
#include "res/computer_add.xpm"
#include "res/computer_delete.xpm"
#include "res/computer_error.xpm"
#include "res/computer_go.xpm"
#include "res/computer_key.xpm"
#include "res/computer_link.xpm"
#include "res/server_add.xpm"
#include "res/search.xpm"
#include "res/alert.xpm"
#include "res/notification.xpm"
#include "res/refresh.xpm"
#include "res/play.xpm"
#include "res/pause.xpm"
#include "res/stop.xpm"
#include "res/showgraphics.xpm"
#include "res/showwebgraphics.xpm"
#include "res/showvmconsole.xpm"
#include "res/copy.xpm"
#endif
#include "res/chevroncollapsed.xpm"
#include "res/chevronexpanded.xpm"


CSkinManager::CSkinManager() :
wxObject()
{
    m_SmallIconSize = wxSize(wxSystemSettings::GetMetric(wxSYS_SMALLICON_X), wxSystemSettings::GetMetric(wxSYS_SMALLICON_Y));
    m_MediumIconSize = wxSize(wxSystemSettings::GetMetric(wxSYS_ICON_X), wxSystemSettings::GetMetric(wxSYS_ICON_Y));
    m_LargeIconSize = wxSize(wxSystemSettings::GetMetric(wxSYS_ICON_X)*2, wxSystemSettings::GetMetric(wxSYS_ICON_Y)*2);

#if defined(__WXMSW__) || defined(__WXMAC__)
    LoadBundle(wxT("boincsentinels"), m_BOINCSentinels);

    LoadBundle(wxT("computer"), m_Host);
    LoadBundle(wxT("computer_add"), m_HostAdd);
    LoadBundle(wxT("computer_connecting"), m_HostConnecting);
    LoadBundle(wxT("computer_connected"), m_HostConnected);
    LoadBundle(wxT("computer_connection_failure"), m_HostConnectionFailure);
    LoadBundle(wxT("computer_authentication_failure"), m_HostAuthenticationFailure);
    LoadBundle(wxT("computer_disconnected"), m_HostDisconnected);
    LoadBundle(wxT("project_add"), m_ProjectAdd);
    LoadBundle(wxT("project_remove"), m_ProjectRemove);
    LoadBundle(wxT("pause"), m_Suspend);
    LoadBundle(wxT("play"), m_Resume);
    LoadBundle(wxT("stop"), m_Abort);
    LoadBundle(wxT("search"), m_Properties);
    LoadBundle(wxT("refresh"), m_Update);
    LoadBundle(wxT("copy"), m_Copy);
    LoadBundle(wxT("alert"), m_Alert);
    LoadBundle(wxT("notification"), m_Notification);
    LoadBundle(wxT("showgraphics"), m_ShowGraphics);
    LoadBundle(wxT("showvmconsole"), m_ShowVMConsole);
    LoadBundle(wxT("showwebgraphics"), m_ShowWebGraphics);
    LoadBundle(wxT("chevronexpanded"), m_ChevronExpanded);
    LoadBundle(wxT("chevroncollapsed"), m_ChevronCollapsed);
#else
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels16_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels32_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels48_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels128_xpm));
    m_BOINCSentinels.AddIcon(wxIcon(boincsentinels256_xpm));

    m_Host.AddIcon(wxIcon(computer_xpm));
    m_HostAdd.AddIcon(wxIcon(computer_add_xpm));
    m_HostConnecting.AddIcon(wxIcon(computer_go_xpm));
    m_HostConnected.AddIcon(wxIcon(computer_link_xpm));
    m_HostConnectionFailure.AddIcon(wxIcon(computer_error_xpm));
    m_HostAuthenticationFailure.AddIcon(wxIcon(computer_key_xpm));
    m_HostDisconnected.AddIcon(wxIcon(computer_delete_xpm));
    m_ProjectAdd.AddIcon(wxIcon(server_add_xpm));
    m_ProjectRemove.AddIcon(wxIcon(server_add_xpm));
    m_Suspend.AddIcon(wxIcon(pause_xpm));
    m_Resume.AddIcon(wxIcon(play_xpm));
    m_Abort.AddIcon(wxIcon(stop_xpm));
    m_Properties.AddIcon(wxIcon(search_xpm));
    m_Update.AddIcon(wxIcon(refresh_xpm));
    m_Copy.AddIcon(wxIcon(copy_xpm));
    m_Alert.AddIcon(wxIcon(bell_xpm));
    m_Notification.AddIcon(wxIcon(newspaper_xpm));
    m_ShowGraphics.AddIcon(wxIcon(application_view_gallery_xpm));
    m_ShowVMConsole.AddIcon(wxIcon(application_xp_terminal_xpm));
    m_ShowWebGraphics.AddIcon(wxIcon(world_go_xpm));
    m_ChevronExpanded.AddIcon(wxIcon(chevronexpanded_xpm));
    m_ChevronCollapsed.AddIcon(wxIcon(chevroncollapsed_xpm));
#endif
}

CSkinManager::~CSkinManager()
{
}

wxSize CSkinManager::GetSmallIconSize()
{
    return m_SmallIconSize;
}

wxSize CSkinManager::GetMediumIconSize()
{
    return m_MediumIconSize;
}

wxSize CSkinManager::GetLargeIconSize()
{
    return m_LargeIconSize;
}

wxIconBundle& CSkinManager::GetBOINCSentinelsIcons()
{
    return m_BOINCSentinels;
}

wxIcon CSkinManager::GetBOINCSentinelsIcon(wxSize uiDesiredSize)
{
    return m_BOINCSentinels.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);  
}

wxIcon CSkinManager::GetHostIcon(wxSize uiDesiredSize)
{
    return m_Host.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetHostAddIcon(wxSize uiDesiredSize)
{
    return m_HostAdd.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetHostConnectingIcon(wxSize uiDesiredSize)
{
    return m_HostConnecting.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetHostConnectedIcon(wxSize uiDesiredSize)
{
    return m_HostConnected.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetHostConnectionFailureIcon(wxSize uiDesiredSize)
{
    return m_HostConnectionFailure.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetHostAuthenticationFailureIcon(wxSize uiDesiredSize)
{
    return m_HostAuthenticationFailure.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetHostDisconnectedIcon(wxSize uiDesiredSize)
{
    return m_HostDisconnected.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetProjectAddIcon(wxSize uiDesiredSize)
{
    return m_ProjectAdd.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetProjectRemoveIcon(wxSize uiDesiredSize)
{
    return m_ProjectRemove.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetSuspendIcon(wxSize uiDesiredSize)
{
    return m_Suspend.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetResumeIcon(wxSize uiDesiredSize)
{
    return m_Resume.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetAbortIcon(wxSize uiDesiredSize)
{
    return m_Abort.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetPropertiesIcon(wxSize uiDesiredSize)
{
    return m_Properties.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetUpdateIcon(wxSize uiDesiredSize)
{
    return m_Update.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetCopyIcon(wxSize uiDesiredSize)
{
    return m_Copy.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetAlertIcon(wxSize uiDesiredSize)
{
    return m_Alert.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetNotificationIcon(wxSize uiDesiredSize)
{
    return m_Notification.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetShowGraphicsIcon(wxSize uiDesiredSize)
{
    return m_ShowGraphics.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetShowVMConsoleIcon(wxSize uiDesiredSize)
{
    return m_ShowVMConsole.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetShowWebGraphicsIcon(wxSize uiDesiredSize)
{
    return m_ShowWebGraphics.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}


wxIcon CSkinManager::GetChevronExpandedIcon(wxSize uiDesiredSize)
{
    return m_ChevronExpanded.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

wxIcon CSkinManager::GetChevronCollapsedIcon(wxSize uiDesiredSize)
{
    return m_ChevronCollapsed.GetIcon(uiDesiredSize, wxIconBundle::FALLBACK_NEAREST_LARGER);
}

bool CSkinManager::LoadBundle(wxString icon, wxIconBundle& bundle)
{
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 16, 16));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 20, 20));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 24, 24));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 32, 32));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 40, 40));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 48, 48));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 64, 64));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 80, 80));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 96, 96));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 128, 128));
    bundle.AddIcon(wxIcon(icon, wxICON_DEFAULT_TYPE, 256, 256));
    return true;
}
