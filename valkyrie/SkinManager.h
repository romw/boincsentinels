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

    wxSize GetSmallIconSize();
    wxSize GetMediumIconSize();
    wxSize GetLargeIconSize();

    wxIconBundle& GetBOINCSentinelsIcons();
    wxIcon GetBOINCSentinelsIcon(wxSize uiDesiredSize);
    wxIcon GetHostIcon(wxSize uiDesiredSize);
    wxIcon GetHostAddIcon(wxSize uiDesiredSize);
    wxIcon GetHostConnectingIcon(wxSize uiDesiredSize);
    wxIcon GetHostConnectedIcon(wxSize uiDesiredSize);
    wxIcon GetHostConnectionFailureIcon(wxSize uiDesiredSize);
    wxIcon GetHostAuthenticationFailureIcon(wxSize uiDesiredSize);
    wxIcon GetHostDisconnectedIcon(wxSize uiDesiredSize);
    wxIcon GetProjectAddIcon(wxSize uiDesiredSize);
    wxIcon GetProjectRemoveIcon(wxSize uiDesiredSize);
    wxIcon GetSuspendIcon(wxSize uiDesiredSize);
    wxIcon GetResumeIcon(wxSize uiDesiredSize);
    wxIcon GetAbortIcon(wxSize uiDesiredSize);
    wxIcon GetPropertiesIcon(wxSize uiDesiredSize);
    wxIcon GetUpdateIcon(wxSize uiDesiredSize);
    wxIcon GetCopyIcon(wxSize uiDesiredSize);
    wxIcon GetAlertIcon(wxSize uiDesiredSize);
    wxIcon GetNotificationIcon(wxSize uiDesiredSize);
    wxIcon GetShowGraphicsIcon(wxSize uiDesiredSize);
    wxIcon GetShowVMConsoleIcon(wxSize uiDesiredSize);
    wxIcon GetShowWebGraphicsIcon(wxSize uiDesiredSize);
    wxIcon GetChevronExpandedIcon(wxSize uiDesiredSize);
    wxIcon GetChevronCollapsedIcon(wxSize uiDesiredSize);

private:
    bool LoadBundle(wxString icon, wxIconBundle& bundle);

    wxSize m_SmallIconSize;
    wxSize m_MediumIconSize;
    wxSize m_LargeIconSize;

    wxIconBundle m_BOINCSentinels;
    wxIconBundle m_Host;
    wxIconBundle m_HostAdd;
    wxIconBundle m_HostConnecting;
    wxIconBundle m_HostConnected;
    wxIconBundle m_HostConnectionFailure;
    wxIconBundle m_HostAuthenticationFailure;
    wxIconBundle m_HostDisconnected;
    wxIconBundle m_ProjectAdd;
    wxIconBundle m_ProjectRemove;
    wxIconBundle m_Suspend;
    wxIconBundle m_Resume;
    wxIconBundle m_Abort;
    wxIconBundle m_Properties;
    wxIconBundle m_Update;
    wxIconBundle m_Copy;
    wxIconBundle m_Alert;
    wxIconBundle m_Notification;
    wxIconBundle m_ShowGraphics;
    wxIconBundle m_ShowVMConsole;
    wxIconBundle m_ShowWebGraphics;
    wxIconBundle m_ChevronExpanded;
    wxIconBundle m_ChevronCollapsed;
};

#endif
