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
#include "bslxml/bslXMLTypes.h"
#include "LookupTables.h"
#include "FNV1Hash.h"

CBSLXMLElementEx::CBSLXMLElementEx()
{
    m_iAttributesSize = 0;
    Clear();
}

CBSLXMLElementEx::CBSLXMLElementEx(const CBSLXMLElementEx& bslXMLElementEx)
{
    for (size_t i = 0; i < bslXMLElementEx.m_Attributes.size(); ++i)
    {
        m_Attributes.push_back(new CBSLXMLAttributeEx(*bslXMLElementEx.m_Attributes[i]));
    }
    m_iNextAttribute = bslXMLElementEx.m_iNextAttribute;
    m_iAttributesSize = bslXMLElementEx.m_iAttributesSize;
    m_pszName = bslXMLElementEx.m_pszName;
    m_uiNameHash = bslXMLElementEx.m_uiNameHash;
    m_uiNameLength = bslXMLElementEx.m_uiNameLength;
    m_pszValue = bslXMLElementEx.m_pszValue;
    m_uiValueHash = bslXMLElementEx.m_uiValueHash;
    m_uiValueLength = bslXMLElementEx.m_uiValueLength;
    m_iType = bslXMLElementEx.m_iType;
}

CBSLXMLElementEx::~CBSLXMLElementEx()
{
    for (size_t i = 0; i < m_iAttributesSize; ++i)
    {
        delete m_Attributes[i];
    }
    m_Attributes.clear();
}

void CBSLXMLElementEx::Clear()
{
    for (size_t i = 0; i < m_iAttributesSize; ++i)
    {
        m_Attributes[i]->Clear();
    }
    m_iNextAttribute = 0;
    m_pszName = NULL;
    m_uiNameHash = FNV1_32_INIT;
    m_uiNameLength = 0;
    m_pszValue = NULL;
    m_uiValueHash = FNV1_32_INIT;
    m_uiValueLength = 0;
    m_iType = ElementTypeUnknown;
}

wxChar* CBSLXMLElementEx::GetName()
{
    return m_pszName;
}

wxUint32 CBSLXMLElementEx::GetNameHash()
{
    return m_uiNameHash;
}

wxUint32 CBSLXMLElementEx::GetNameLength()
{
    return m_uiNameLength;
}

wxChar* CBSLXMLElementEx::GetValue()
{
    return m_pszValue;
}

wxUint32 CBSLXMLElementEx::GetValueHash()
{
    return m_uiValueHash;
}

wxUint32 CBSLXMLElementEx::GetValueLength()
{
    return m_uiValueLength;
}

CBSLXMLElementEx::ELEMENTTYPE CBSLXMLElementEx::GetType()
{
    return m_iType;
}

CBSLXMLAttributeEx* CBSLXMLElementEx::FindAttribute(const wxChar* pszName)
{
    wxUint32 uiHash = FNV1_32_INIT;
    wxChar* pPosition = (wxChar*)pszName;

    // Compute hash to compare against the elements hash
    while (*pPosition)
    {
        FNV132COMPUTE(uiHash, *pPosition);
        ++pPosition;
    }

    return FindAttribute(uiHash);
}

CBSLXMLAttributeEx* CBSLXMLElementEx::FindAttribute(wxUint32 uiNameHash)
{
    // Find desired element by hash
    for (size_t i = 0; i < m_iNextAttribute; ++i)
    {
        if (uiNameHash == m_Attributes[i]->GetNameHash())
        {
            return m_Attributes[i];
        }
    }

    return NULL;
}

void CBSLXMLElementEx::SetName(const wxChar* pszName)
{
    m_uiNameHash = FNV1_32_INIT;
    wxChar* pPosition = m_pszName = wxConstCast(pszName, wxChar);

    // Skip to the end of the element name
    while (*pPosition)
    {
        FNV132COMPUTE(m_uiNameHash, *pPosition);
        ++pPosition;
    }

    m_uiNameLength = (wxUint32)(pPosition - pszName);
}

void CBSLXMLElementEx::SetValue(const wxChar* pszValue)
{
    m_uiValueHash = FNV1_32_INIT;
    wxChar* pPosition = m_pszValue = wxConstCast(pszValue, wxChar);

    // Skip to the end of the element value
    while (*pPosition)
    {
        FNV132COMPUTE(m_uiValueHash, *pPosition);
        ++pPosition;
    }

    m_uiValueLength = (wxUint32)(pPosition - pszValue);
}

BSLXMLERRCODE CBSLXMLElementEx::Parse(CBSLXMLDocumentEx& oDocument)
{
    BSLXMLERRCODE rc = BSLXMLERR_MALFORMED_XML;
    CBSLXMLAttributeEx* pAttribute = NULL;
    wxChar* pPosition = oDocument.GetPosition();
    bool bPresetValue = false;

    m_iType = ElementTypeUnknown;
    m_pszName = NULL;
    m_uiNameHash = FNV1_32_INIT;
    m_uiNameLength = 0;
    m_pszValue = NULL;
    m_uiValueHash = FNV1_32_INIT;
    m_uiValueLength = 0;


    // Skip any whitespace
    while (lookup_whitespace[*pPosition])
        ++pPosition;


    if (0 == memcmp(pPosition, xml_node_begin, sizeof(xml_node_begin)))
    {
        //
        // XML Comment node?
        //
        // <!--
        // ^
        //
        if (0 == memcmp(pPosition, xml_comment_begin, sizeof(xml_comment_begin)))
        {
            m_iType = ElementTypeComment;

            // Skip to the end of the comment
            //
            // -->
            // ^
            //
            while (0 != memcmp(pPosition, xml_comment_end, sizeof(xml_comment_end)))
                ++pPosition;

            pPosition += sizeof(xml_comment_end) / sizeof(wxChar);

            m_uiValueLength = 0;
            m_pszValue = (wxChar*)preset_empty_string;
            m_uiValueHash = preset_empty_string_hash;
            bPresetValue = true;

            // We have successfully parsed this element
            rc = BSLXMLERR_SUCCESS;
        }

        //
        // XML Container node (closing tag)?
        //
        // </
        // ^
        //
        else if (0 == memcmp(pPosition, xml_container_end, sizeof(xml_container_end)))
        {
            m_iType = ElementTypeContainerEnd;

            pPosition += sizeof(xml_container_end) / sizeof(wxChar);

            // Record the start of the element name
            m_pszName = pPosition;

            // Skip to the end of the element name
            while (lookup_node_name[*pPosition])
            {
                FNV132COMPUTE(m_uiNameHash, *pPosition);
                ++pPosition;
            }

            // Record the size of the element name
            m_uiNameLength = (wxUint32)(pPosition - m_pszName);

            // This is an empty element
            m_uiValueLength = 0;
            m_pszValue = (wxChar*)preset_empty_string;
            m_uiValueHash = preset_empty_string_hash;
            bPresetValue = true;
        }
        
        //
        // XML Node?
        //
        // <
        // ^
        //
        else
        {
            // Skip '<'
            ++pPosition;

            m_iType = ElementTypeNormal;

            // Record the start of the element name
            m_pszName = pPosition;

            // Skip to the end of the element name
            while (lookup_node_name[*pPosition])
            {
                FNV132COMPUTE(m_uiNameHash, *pPosition);
                ++pPosition;
            }

            // Record the size of the element name
            m_uiNameLength = (wxUint32)(pPosition - m_pszName);

            // Skip any whitespace
            while (lookup_whitespace[*pPosition])
                ++pPosition;

            // Parse attributes, if any
            oDocument.SetPosition(pPosition);
            while (lookup_attributes[*pPosition])
            {
                if (m_iNextAttribute >= m_iAttributesSize)
                {
                    pAttribute = new CBSLXMLAttributeEx();
                    m_Attributes.push_back(pAttribute);

                    ++m_iAttributesSize;
                }
                else
                {
                    pAttribute = m_Attributes[m_iNextAttribute];
                }

                pAttribute->Parse(oDocument);
                ++m_iNextAttribute;

                pPosition = oDocument.GetPosition();
            }

            //
            // XML Bool Node?
            //
            // <example />
            //          ^^
            //
            if (0 == memcmp(pPosition, xml_bool_node, sizeof(xml_bool_node)))
            {
                m_iType = ElementTypeBool;

                // This is an boolean value
                m_uiValueLength = 1;
                m_pszValue = (wxChar*)preset_true_string;
                m_uiValueHash = preset_true_string_hash;
                bPresetValue = true;
            }
            else if (0 == memcmp(pPosition, xml_node_end, sizeof(xml_node_end)))
            {
                // Advance to the next character
                ++pPosition;

                // Skip any whitespace
                while (lookup_whitespace[*pPosition])
                    ++pPosition;

                //
                // XML CDATA node?
                //
                // <example><![CDATA[  ]]></example>
                //          ^^^^^^^^
                //
                if (0 == memcmp(pPosition, xml_cdata_begin, sizeof(xml_cdata_begin)))
                {
                    m_iType = ElementTypeCDATA;

                    pPosition += (sizeof(xml_cdata_begin) / sizeof(wxChar)) + 1;

                    // Record the start of the element value
                    m_pszValue = pPosition;

                    // Skip to the end of the element value
                    while (0 != memcmp(pPosition, xml_cdata_end, sizeof(xml_cdata_end)))
                    {
                        FNV132COMPUTE(m_uiValueHash, *pPosition);
                        ++pPosition;
                    }

                    // Record the size of the element value
                    m_uiValueLength = (wxUint32)(pPosition - m_pszValue);

                    // Skip past the end of the CDATA marker
                    pPosition += sizeof(xml_cdata_end) / sizeof(wxChar);

                    // Skip any whitespace
                    while (pPosition[0] != wxT('<'))
                        ++pPosition;

                    // Skip past the beginning of the closing tag
                    ++pPosition;
                }

                //
                // XML Node closing tag?
                //
                // </
                // ^
                //
                else if (0 == memcmp(pPosition, xml_node_closing_tag, sizeof(xml_node_closing_tag)))
                {
                    // Advance past the decorations and to the first character
                    // of the closing tag.
                    pPosition += sizeof(xml_node_closing_tag) / sizeof(wxChar);

                    // Skip to the end of the element name
                    while (lookup_node_name[*pPosition])
                    {
                        ++pPosition;
                    }

                    // This is an empty element
                    m_uiValueLength = 0;
                    m_pszValue = (wxChar*)preset_empty_string;
                    m_uiValueHash = preset_empty_string_hash;
                    bPresetValue = true;
                }

                //
                // XML Container node (begining tag)?
                //
                // >
                // ^
                //
                else if (0 == memcmp(pPosition, xml_container_begin, sizeof(xml_container_begin)))
                {
                    m_iType = ElementTypeContainer;

                    // This is an empty element
                    m_uiValueLength = 0;
                    m_pszValue = (wxChar*)preset_empty_string;
                    m_uiValueHash = preset_empty_string_hash;
                    bPresetValue = true;
                }
                else
                {
                    // This is a regular element
                    m_pszValue = pPosition;

                    // Skip to the end of the element value
                    while (lookup_text[*pPosition])
                    {
                        FNV132COMPUTE(m_uiValueHash, *pPosition);
                        ++pPosition;
                    }

                    // Record the size of the element value
                    m_uiValueLength = (wxUint32)(pPosition - m_pszValue);
                }
            }
        }
    }

    // Terminate element name
    if (m_uiNameLength)
    {
        m_pszName[m_uiNameLength] = wxT('\0');
        if (pPosition == &m_pszName[m_uiNameLength])
        {
            ++pPosition;
        }

        // We have successfully parsed this element
        rc = BSLXMLERR_SUCCESS;
    }

    // Terminate element value
    if (m_uiValueLength && !bPresetValue)
    {
        m_pszValue[m_uiValueLength] = wxT('\0');
        if (pPosition == &m_pszValue[m_uiValueLength])
        {
            ++pPosition;
        }
    }

    //
    // Determine if what we have just parsed is in fact a normal element type
    //
    if (ElementTypeNormal == m_iType)
    {
        // If the value is null, the element must be a container.
        if (0 == m_uiValueLength && !bPresetValue)
        {
            m_iType = ElementTypeContainer;
            m_pszValue = (wxChar*)preset_empty_string;
            m_uiValueHash = preset_empty_string_hash;
        }

        // If the value of an element is either '1' or '0' its element type is considered a bool.
        if ((1 == m_uiValueLength) && ((m_pszValue[0] == '0') || (m_pszValue[0] == '1')))
        {
            m_iType = ElementTypeBool;
        }
    }

    // Update the position in the XML Stream
    if (BSLXMLERR_SUCCESS == rc)
    {
        oDocument.SetPosition(pPosition);
    }

    return rc;
}
