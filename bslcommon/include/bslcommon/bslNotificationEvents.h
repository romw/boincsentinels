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

///
/// \defgroup BSLCommon BOINC Sentinels Common Library Interface
/// \{

#ifndef _BSLCOMMONNOTIFICATIONEVENTS_H_
#define _BSLCOMMONNOTIFICATIONEVENTS_H_

class CBSLNotificationEventData: public wxObject, public CBSLEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLNotificationEventData)

public:
    CBSLNotificationEventData();
    CBSLNotificationEventData(const CBSLNotificationEventData& data);
    ~CBSLNotificationEventData();

    /// \brief Returns a handle to the associated host.
    BSLHOST GetHostHandle();
    /// \brief Returns a handle to the associated notification.
    BSLNOTIFICATION GetNotificationHandle();
    /// \brief Returns a handle to the associated project.
    BSLPROJECT GetProjectHandle();

    /// \brief Sets the associated host handle.
    void SetHostHandle(BSLHOST hHost);
    /// \brief Sets the associated notification handle.
    void SetNotificationHandle(BSLNOTIFICATION hNotification);
    /// \brief Sets the associated project handle.
    void SetProjectHandle(BSLPROJECT hProject);

private:
    BSLHOST m_hHost;
    BSLNOTIFICATION m_hNotification;
    BSLPROJECT m_hProject;
};


class CBSLNotificationAuditLogEventData: public CBSLNotificationEventData, public CBSLAuditLogEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLNotificationAuditLogEventData)

public:
    CBSLNotificationAuditLogEventData();
    CBSLNotificationAuditLogEventData(const CBSLNotificationAuditLogEventData& data);
    ~CBSLNotificationAuditLogEventData();
};

#endif

///
/// \}
