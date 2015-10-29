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

#ifndef _BSLXMLELEMENTEX_H_
#define _BSLXMLELEMENTEX_H_


///
/// \brief An XML Element.
///
/// Contains an XML Element.
///
class CBSLXMLElementEx
{
    friend class CBSLXMLTestUtil;

public:

    /// \brief Type of element
    enum ELEMENTTYPE
    {
        ElementTypeUnknown = 0,
        ElementTypeNormal = 1,
        ElementTypeContainer = 2,
        ElementTypeContainerEnd = 3,
        ElementTypeBool = 4,
        ElementTypeComment = 5,
        ElementTypeCDATA = 6
    };

    CBSLXMLElementEx();
    CBSLXMLElementEx(const CBSLXMLElementEx&);
    virtual ~CBSLXMLElementEx();

    /// \brief Initialize CBSLXMLElementEx state.
    void Clear();

    /// \brief Name of XML Element.
    wxChar* GetName();
    /// \brief the FNV1 hash of the XML Element's name.
    wxUint32 GetNameHash();
    /// \brief the XML Element's name length.
    wxUint32 GetNameLength();
    /// \brief Value of XML Element.
    wxChar* GetValue();
    /// \brief the FNV1 hash of the XML Element's value.
    wxUint32 GetValueHash();
    /// \brief the XML Element's value length.
    wxUint32 GetValueLength();
    /// \brief the XML Element's type.
    ELEMENTTYPE GetType();

    /// \brief Find an XML Attribute based on its name.
    /// \param[in] pszName the name of the XML Attribute to find.
    /// \retval The pointer to a CBSLXMLAttributeEx object containing the XML Attribute information, or NULL if not found.
    CBSLXMLAttributeEx* FindAttribute(const wxChar* pszName);

    /// \brief Find an XML Attribute based on its hash.
    /// \param[in] uiNameHash the FNV1 hash of the XML Attribute to find.
    /// \retval The pointer to a CBSLXMLAttributeEx object containing the XML Attribute information, or NULL if not found.
    CBSLXMLAttributeEx* FindAttribute(wxUint32 uiNameHash);

    /// \brief Name of XML Element.
    /// \param[in] pszName the name of the XML Element.
    void SetName(const wxChar* pszName);

    /// \brief Value of XML Element.
    /// \param[in] pszValue the value of the XML Element.
    void SetValue(const wxChar* pszValue);

    /// \brief Parse an XML Element
    /// \param[in] oDocument the XML Document to parse the element from.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_MALFORMED_XML \copybrief BSLXMLERRCODE::BSLXMLERR_MALFORMED_XML
    BSLXMLERRCODE Parse(CBSLXMLDocumentEx& oDocument);

protected:
    wxUint32 m_iNextAttribute;
    size_t m_iAttributesSize;
    std::vector<CBSLXMLAttributeEx*> m_Attributes;

    wxChar* m_pszName;
    wxUint32 m_uiNameHash;
    wxUint32 m_uiNameLength;
    wxChar* m_pszValue;
    wxUint32 m_uiValueHash;
    wxUint32 m_uiValueLength;
    ELEMENTTYPE m_iType;
};

#endif

///
/// \}
