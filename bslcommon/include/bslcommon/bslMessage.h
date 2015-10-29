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

#ifndef _BSLCOMMONMESSAGE_H_
#define _BSLCOMMONMESSAGE_H_

#define BSLXMLTAGHASH_MESSAGE \
    0x2c7df5b8

class CBSLMessage: public CBSLMessageEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLMessage)

public:

    /// \brief Priority of the message
    /// \note  Values are directly compatible with default BOINC message values.
    enum PRIORITY
    {
        PriorityUnknown = 0,
        PriorityInfo = 1,
        PriorityUserAlert = 2,
        PriorityInternalError = 3
    };

    CBSLMessage();
    virtual ~CBSLMessage();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLMessage&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLMessage&) const;

    /// \brief Initialize CBSLMessage state.
    void Clear();

    /// \brief Returns the sequence number of the message.
    wxInt32 GetSequenceNumber();
    /// \brief Returns the priority of the message.
    PRIORITY GetPriority();
    /// \brief Returns the time stamp of the message.
    wxDateTime& GetTimestamp();
    /// \brief Returns the name/URL of the project that generated the message.
    wxString& GetProject();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief Returns the contents of the message.
    wxString& GetMessageText();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the sequence number of the message.
    void SetSequenceNumber(wxInt32 iSequenceNumber);
    /// \brief Sets the priority of the message.
    void SetPriority(PRIORITY iPriority);
    /// \brief Sets the time stamp of the message.
    void SetTimestamp(wxDateTime dtTimestamp);
    /// \brief Sets the name/URL of the project that generated the message.
    void SetProject(wxString strProject);
    /// \brief Sets the contents of the message.
    void SetMessageText(wxString strMessageText);

private:
    wxInt32 m_iSequenceNumber;
    PRIORITY m_iPriority;
    wxDateTime m_dtTimestamp;
    wxString m_strProject;
    wxUint32 m_uiProjectHash;
    wxString m_strMessageText;
    wxUint32 m_uiMessageTextHash;
};

#endif

///
/// \}
