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

#ifndef _BSLCOMMONTRANSFER_H_
#define _BSLCOMMONTRANSFER_H_

#define BSLXMLTAGHASH_TRANSFER \
    0x4f98effb

class CBSLTransfer: public CBSLTransferEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLTransfer)

public:
    CBSLTransfer();
    virtual ~CBSLTransfer();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLTransfer&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLTransfer&) const;

    /// \brief Initialize CBSLTransfer state.
    void Clear();

    /// \brief
    wxUint64 GetBytes();
    /// \brief
    wxUint64 GetBytesTransfered();
    /// \brief
    wxUint64 GetBytesUploaded();
    /// \brief
    wxTimeSpan& GetElapsedTime();
    /// \brief
    wxDateTime& GetFirstRequestTime();
    /// \brief
    wxString& GetName();
    /// \brief
    wxUint32 GetNameHash();
    /// \brief Returns the URL of the project that generated the transfer.
    wxString& GetProject();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief
    wxDateTime& GetNextRequestTime();
    /// \brief
    wxTimeSpan& GetProjectBackoff();
    /// \brief
    wxUint32 GetRetryCount();
    /// \brief
    wxUint64 GetTransferRate();
    /// \brief
    bool IsPersistantTransferActive();
    /// \brief
    bool IsSticky();
    /// \brief
    bool IsTransferActive();
    /// \brief
    bool IsUpload();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief
    void SetBytes(wxUint64 ullBytes);
    /// \brief
    void SetBytesTransfered(wxUint64 ullBytesTransfered);
    /// \brief
    void SetBytesUploaded(wxUint64 ullBytesUploaded);
    /// \brief
    void SetElapsedTime(wxTimeSpan tsElapsedTime);
    /// \brief
    void SetFirstRequestTime(wxDateTime dtFirstRequestTime);
    /// \brief
    void SetName(wxString strName);
    /// \brief Sets the URL of the project that generated the transfer.
    void SetProject(wxString strProject);
    /// \brief
    void SetNextRequestTime(wxDateTime dtNextRequestTime);
    /// \brief
    void SetPersistantTransferActive(bool bPersistantTransferActive);
    /// \brief
    void SetProjectBackoff(wxTimeSpan tsProjectBackoff);
    /// \brief
    void SetRetryCount(wxUint32 uiRetryCount);
    /// \brief
    void SetSticky(bool bSticky);
    /// \brief
    void SetTransferActive(bool bTransferActive);
    /// \brief
    void SetTransferRate(wxUint64 ullTransferRate);
    /// \brief
    void SetUpload(bool bUpload);

private:
    wxString m_strProject;
    wxUint32 m_uiProjectHash;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxTimeSpan m_tsElapsedTime;
    wxTimeSpan m_tsProjectBackoff;
    wxDateTime m_dtFirstRequestTime;
    wxDateTime m_dtNextRequestTime;
    wxUint32 m_uiRetryCount;
    wxUint64 m_ullBytes;
    wxUint64 m_ullBytesTransfered;
    wxUint64 m_ullBytesUploaded;
    wxUint64 m_ullTransferRate;
    bool m_bSticky;
    bool m_bPersistantTransferActive;
    bool m_bTransferActive;
    bool m_bUpload;
};

#endif

///
/// \}
