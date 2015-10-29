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

#ifndef _NOTIFICATIONMANAGER_H_
#define _NOTIFICATIONMANAGER_H_

class CNotificationManager: public wxObject
{
    DECLARE_NO_COPY_CLASS(CNotificationManager)

public:
    CNotificationManager();
    virtual ~CNotificationManager();

    bool IsRead(CBSLNotification& bslNotification);
    bool IsDeleted(CBSLNotification& bslNotification);
    bool MarkRead(CBSLNotification& bslNotification, bool bValue);
    bool MarkDeleted(CBSLNotification& bslNotification, bool bValue);

private:
    wxString DeterminePath(CBSLNotification& bslNotification);

    bool GetConfigValue(wxString strSubComponent, wxString strValueName, long dwDefaultValue, long* pdwValue);
    bool SetConfigValue(wxString strSubComponent, wxString strValueName, long dwValue);
};

#endif
