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

#ifndef _BSLXMLDICTIONARYEX_H_
#define _BSLXMLDICTIONARYEX_H_

///
/// \brief A collection of XML Elements.
///
/// A collection of XML Elements from a common parent node.
///
/// \note  This parser uses destructive parsing techniques, any XML passed
///        in may no longer be usable when parsing has been completed.
///
class CBSLXMLDictionaryEx
{
    friend class CBSLXMLTestUtil;

public:
    CBSLXMLDictionaryEx();
    CBSLXMLDictionaryEx(const CBSLXMLDictionaryEx&);
    virtual ~CBSLXMLDictionaryEx();

    /// \brief Initialize CBSLXMLDictionaryEx state.
    void Clear();

    /// \brief Find an XML Element based on its name.
    /// \param[in] pszName the name of the XML Element to find.
    /// \retval The pointer to a CBSLXMLElementEx object containing the XML Element information, or NULL if not found.
    CBSLXMLElementEx* FindElement(const wxChar* pszName);

    /// \brief Find an XML Element based on its hash.
    /// \param[in] uiNameHash the FNV1 hash of the XML Element to find.
    /// \retval The pointer to a CBSLXMLElementEx object containing the XML Element information, or NULL if not found.
    CBSLXMLElementEx* FindElement(wxUint32 uiNameHash);

    /// \brief Parse an XML Dictionary
    /// \param[in] oDocument the XML Document to parse the dictionary from.
    /// \param[in] uiTagHash the FNV1 hash of the closing tag.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_MALFORMED_XML \copybrief BSLXMLERRCODE::BSLXMLERR_MALFORMED_XML
    BSLXMLERRCODE Parse(CBSLXMLDocumentEx& oDocument, wxUint32 uiTagHash);

protected:
    wxUint32 m_iNextElement;
    size_t m_iElementsSize;
    std::vector<CBSLXMLElementEx*> m_Elements;
};

#endif

///
/// \}
