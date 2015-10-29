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

#ifndef BSLXMLATTRIBUTEEX_H_
#define BSLXMLATTRIBUTEEX_H_

///
/// \brief An XML Attribute.
///
/// Contains an XML Attribute.
///
class CBSLXMLAttributeEx
{
    friend class CBSLXMLTestUtil;
    friend class CBSLXMLElementEx;

public:
    CBSLXMLAttributeEx();
    CBSLXMLAttributeEx(const CBSLXMLAttributeEx&);
    virtual ~CBSLXMLAttributeEx();

    /// \brief Initialize CBSLXMLAttributeEx state.
    void Clear();

    /// \brief Name of XML Attribute.
    wxChar* GetName();
    /// \brief the FNV1 hash of the XML Attribute's name.
    wxUint32 GetNameHash();
    /// \brief the XML Attribute's name length.
    wxUint32 GetNameLength();
    /// \brief Value of XML Attribute.
    wxChar* GetValue();
    /// \brief the FNV1 hash of the XML Attribute's value.
    wxUint32 GetValueHash();
    /// \brief the XML Attribute's value length.
    wxUint32 GetValueLength();

    /// \brief Name of XML Attribute.
    /// \param[in] pszName the name of the XML Attribute.
    void SetName(const wxChar* pszName);

    /// \brief Value of XML Attribute.
    /// \param[in] pszValue the value of the XML Attribute.
    void SetValue(const wxChar* pszValue);

    /// \brief Parse an XML Attribute
    /// \param[in] oDocument the XML Document to parse the attribute from.
    /// \retval BSLXMLERR_SUCCESS \copybrief BSLXMLERRCODE::BSLXMLERR_SUCCESS
    /// \retval BSLXMLERR_MALFORMED_XML \copybrief BSLXMLERRCODE::BSLXMLERR_MALFORMED_XML
    BSLXMLERRCODE Parse(CBSLXMLDocumentEx& oDocument);

protected:
    wxChar* m_pszName;
    wxUint32 m_uiNameHash;
    wxUint32 m_uiNameLength;
    wxChar* m_pszValue;
    wxUint32 m_uiValueHash;
    wxUint32 m_uiValueLength;
};

#endif

///
/// \}
