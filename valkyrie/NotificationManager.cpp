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
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Valkyrie.h"
#include "ConfigManager.h"
#include "NotificationManager.h"


CNotificationManager::CNotificationManager() :
wxObject()
{
    wxSortedArrayString aDates;
    wxDateTime dtNotificationCreated = wxDateTime((time_t)0);
    wxDateTime dtNotificationOldestTime = wxDateTime::Now().Subtract(wxDateSpan::Days(45));

    wxGetApp().GetConfigManager()->EnumerateGroups(wxString(wxT("NotificationsDB")), wxEmptyString, &aDates);
    for (size_t i = 0; i < aDates.Count(); i++)
    {
        dtNotificationCreated.ParseDate(aDates[i]);
        if (dtNotificationCreated < dtNotificationOldestTime)
        {
            wxGetApp().GetConfigManager()->DeleteConfigGroup(wxString(wxT("NotificationsDB")), aDates[i]);
        }
    }
}

CNotificationManager::~CNotificationManager()
{
}

bool CNotificationManager::IsRead(CBSLNotification& bslNotification)
{
    long dwValue = 0;
    GetConfigValue(DeterminePath(bslNotification), wxT("Read"), 0, &dwValue);
    return (dwValue == 1);
}

bool CNotificationManager::IsDeleted(CBSLNotification& bslNotification)
{
    long dwValue = 0;
    GetConfigValue(DeterminePath(bslNotification), wxT("Deleted"), 0, &dwValue);
    return (dwValue == 1);
}

bool CNotificationManager::MarkRead(CBSLNotification& bslNotification, bool bValue)
{
    if (!(bslNotification.GetCategory() == wxT("scheduler")) && !(bslNotification.GetCategory() == wxT("client")))
    {
        SetConfigValue(DeterminePath(bslNotification), wxT("Read"), bValue);
        wxGetApp().GetState()->FireEvent(wxEVT_BSLNOTIFICATION_UPDATE, bslNotification.GetHostHandle(), bslNotification.GetNotificationHandle());
    }
    return true;
}

bool CNotificationManager::MarkDeleted(CBSLNotification& bslNotification, bool bValue)
{
    if (!(bslNotification.GetCategory() == wxT("scheduler")) && !(bslNotification.GetCategory() == wxT("client")))
    {
        SetConfigValue(DeterminePath(bslNotification), wxT("Deleted"), bValue);
        wxGetApp().GetState()->FireEvent(wxEVT_BSLNOTIFICATION_UPDATE, bslNotification.GetHostHandle(), bslNotification.GetNotificationHandle());
    }
    return true;
}

wxString CNotificationManager::DeterminePath(CBSLNotification& bslNotification)
{
    wxString strSubComponent;
    wxString strDate;
    wxString strLink;

    // Sanitize the date for storage
    strDate = bslNotification.GetCreateTime().FormatISODate();

    // Sanitize the link for storage
    strLink = bslNotification.GetLink();
    strLink.Replace(wxT("/"), wxT("-"), true);

    strSubComponent = strDate + wxT("/") + strLink;

    return strSubComponent;
}

bool CNotificationManager::GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue)
{
    return wxGetApp().GetConfigManager()->GetConfigValue(wxString(wxT("NotificationsDB")), strSubComponent, strValueName, dwDefaultValue, pdwValue);
}

bool CNotificationManager::SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue)
{
    return wxGetApp().GetConfigManager()->SetConfigValue(wxString(wxT("NotificationsDB")), strSubComponent, strValueName, dwValue);
}
