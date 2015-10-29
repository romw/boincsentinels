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
/// \defgroup BSLXML BOINC Sentinels XML Library Interface
/// \{

#ifndef _BSLXMLDOCUMENT_H_
#define _BSLXMLDOCUMENT_H_

///
/// \brief An XML Document.
///
/// Contains an XML Document to be parsed.
///
/// \note  This parser uses destructive parsing techniques, any XML passed
///        in may no longer be usable when parsing has been completed.
///
class CBSLXMLDocumentEx
{
    friend class CBSLXMLTestUtil;
    friend class CBSLXMLAttributeEx;
    friend class CBSLXMLElementEx;

public:
    CBSLXMLDocumentEx();
    virtual ~CBSLXMLDocumentEx();

    /// \brief Initialize CBSLXMLDocumentEx state.
    void Clear();

    /// \brief Copies the XML Document into the supplied buffer.
    /// \param[in] strDocument a string to store the current XML Document.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_FAILURE \copybrief BSLXMLERRCODE::BSLXMLERR_FAILURE
    /// \retval BSLXMLERR_INVALID_PARAMETER \copybrief BSLXMLERRCODE::BSLXMLERR_INVALID_PARAMETER
    BSLXMLERRCODE GetDocument(wxString& strDocument);

    /// \brief Parse the next XML Element in the XML Document.
    /// \param[out] oElement the contents of the next XML Element.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_FAILURE \copybrief BSLXMLERRCODE::BSLXMLERR_FAILURE
    BSLXMLERRCODE GetNextElement(CBSLXMLElementEx& oElement);

    /// \brief Copies the XML Document into a buffer to be parsed.
    /// \param[in] pszDocument a pointer to the XML Document to copy.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_FAILURE \copybrief BSLXMLERRCODE::BSLXMLERR_FAILURE
    /// \retval BSLXMLERR_INVALID_PARAMETER \copybrief BSLXMLERRCODE::BSLXMLERR_INVALID_PARAMETER
    BSLXMLERRCODE SetDocument(const wxChar* pszDocument);

    /// \brief Copies the XML Document into a buffer to be parsed.
    /// \param[in] strDocument a pointer to the XML Document to copy.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_FAILURE \copybrief BSLXMLERRCODE::BSLXMLERR_FAILURE
    /// \retval BSLXMLERR_INVALID_PARAMETER \copybrief BSLXMLERRCODE::BSLXMLERR_INVALID_PARAMETER
    BSLXMLERRCODE SetDocument(const wxString& strDocument);

    /// \brief Copies the contents of a file into a buffer to be parsed.
    /// \param[in] strFilename the file whose contents are to be copied.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_FAILURE \copybrief BSLXMLERRCODE::BSLXMLERR_FAILURE
    /// \retval BSLXMLERR_INVALID_PARAMETER \copybrief BSLXMLERRCODE::BSLXMLERR_INVALID_PARAMETER
    /// \retval BSLXMLERR_FILE_NOT_FOUND \copybrief BSLXMLERRCODE::BSLXMLERR_FILE_NOT_FOUND
    BSLXMLERRCODE SetDocumentFromFile(const wxString strFilename);

    /// \brief Advances the document position past the specified container.
    /// \param[in] oElement the container to skip.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_FAILURE \copybrief BSLXMLERRCODE::BSLXMLERR_FAILURE
    /// \retval BSLXMLERR_INVALID_PARAMETER \copybrief BSLXMLERRCODE::BSLXMLERR_INVALID_PARAMETER
	BSLXMLERRCODE SkipContainer(CBSLXMLElementEx& oElement);

protected:
    wxChar* GetPosition();
    BSLXMLERRCODE SetPosition(const wxChar* pPosition);

private:
    wxString m_strDocument;
    bool m_bFirstElement;
    wxChar* m_pCurrentPosition;
    wxChar* m_pLastPosition;
};

#endif

///
/// \}
