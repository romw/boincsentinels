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

#ifndef _BSLCOMMONNOTIFICATION_H_
#define _BSLCOMMONNOTIFICATION_H_

#define BSLXMLTAGHASH_NOTIFICATION \
    0xb1b66d8d

class CBSLNotification: public CBSLNotificationEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLNotification)

public:
    CBSLNotification();
    virtual ~CBSLNotification();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLNotification&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLNotification&) const;

    /// \brief Initialize CBSLNotification state.
    void Clear();

    /// \brief Returns the sequence number of the notification.
    wxInt32 GetSequenceNumber();
    /// \brief Returns the time in which the notification was created.
    wxDateTime& GetCreateTime();
    /// \brief Returns the time in which the notification arrived on the host.
    wxDateTime& GetArrivalTime();
    /// \brief Returns whether or not the notification is marked private.
    bool IsPrivate();
    /// \brief Returns the category of the notification.
    wxString& GetCategory();
    /// \brief Returns the link of the notification.
    wxString& GetLink();
    /// \brief Returns the URL of the project that generated the notification.
    wxString& GetProject();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief Returns the title of the notification.
    wxString& GetTitle();
    /// \brief Returns the contents of the notification.
    wxString& GetNotificationText();
    /// \brief Returns the GUID of the notification.
    wxString& GetGUID();
    /// \brief Returns the Feed URL of the notification.
    wxString& GetFeedURL();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the sequence number of the notification.
    void SetSequenceNumber(wxInt32 iSequenceNumber);
    /// \brief Sets the time in which the notification was created.
    void SetCreateTime(wxDateTime dtCreateTime);
    /// \brief Sets the time in which the notification arrived on the host.
    void SetArrivalTime(wxDateTime dtArrivalTime);
    /// \brief Sets whether or not the notification is marked private.
    void SetPrivate(bool bPrivate);
    /// \brief Sets the category of the notification.
    void SetCategory(wxString strCategory);
    /// \brief Sets the link of the notification.
    void SetLink(wxString strLink);
    /// \brief Sets the URL of the project that generated the notification.
    void SetProject(wxString strProject);
    /// \brief Sets the title of the notification.
    void SetTitle(wxString strTitle);
    /// \brief Sets the contents of the notification.
    void SetNotificationText(wxString strNotificationText);
    /// \brief Sets the GUID of the notification.
    void SetGUID(wxString strGUID);
    /// \brief Sets the Feed URL of the notification.
    void SetFeedURL(wxString strFeedURL);

private:
    wxInt32 m_iSequenceNumber;
    wxDateTime m_dtCreateTime;
    wxDateTime m_dtArrivalTime;
    bool m_bPrivate;
    wxString m_strCategory;
    wxUint32 m_uiCategoryHash;
    wxString m_strLink;
    wxUint32 m_uiLinkHash;
    wxString m_strProject;
    wxUint32 m_uiProjectHash;
    wxString m_strTitle;
    wxUint32 m_uiTitleHash;
    wxString m_strNotificationText;
    wxUint32 m_uiNotificationTextHash;
    wxString m_strGUID;
    wxUint32 m_uiGUIDHash;
    wxString m_strFeedURL;
    wxUint32 m_uiFeedURLHash;
};

#endif

///
/// \}
