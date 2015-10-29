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

CBSLXMLAttributeEx::CBSLXMLAttributeEx()
{
    Clear();
}

CBSLXMLAttributeEx::CBSLXMLAttributeEx(const CBSLXMLAttributeEx& bslXMLAttributeEx)
{
    m_pszName = bslXMLAttributeEx.m_pszName;
    m_uiNameHash = bslXMLAttributeEx.m_uiNameHash;
    m_uiNameLength = bslXMLAttributeEx.m_uiNameLength;
    m_pszValue = bslXMLAttributeEx.m_pszValue;
    m_uiValueHash = bslXMLAttributeEx.m_uiValueHash;
    m_uiValueLength = bslXMLAttributeEx.m_uiValueLength;
}

CBSLXMLAttributeEx::~CBSLXMLAttributeEx()
{
}

void CBSLXMLAttributeEx::Clear()
{
    m_pszName = NULL;
    m_uiNameHash = FNV1_32_INIT;
    m_uiNameLength = 0;
    m_pszValue = NULL;
    m_uiValueHash = FNV1_32_INIT;
    m_uiValueLength = 0;
}

wxChar* CBSLXMLAttributeEx::GetName()
{
    return m_pszName;
}

wxUint32 CBSLXMLAttributeEx::GetNameHash()
{
    return m_uiNameHash;
}

wxUint32 CBSLXMLAttributeEx::GetNameLength()
{
    return m_uiNameLength;
}

wxChar* CBSLXMLAttributeEx::GetValue()
{
    return m_pszValue;
}

wxUint32 CBSLXMLAttributeEx::GetValueHash()
{
    return m_uiValueHash;
}

wxUint32 CBSLXMLAttributeEx::GetValueLength()
{
    return m_uiValueLength;
}

void CBSLXMLAttributeEx::SetName(const wxChar* pszName)
{
    m_uiNameHash = FNV1_32_INIT;
    wxChar* pPosition = m_pszName = wxConstCast(pszName, wxChar);

    // Skip to the end of the attribute name
    while (*pPosition)
    {
        FNV132COMPUTE(m_uiNameHash, *pPosition);
        pPosition++;
    }

    m_uiNameLength = (wxUint32)(pPosition - pszName);
}

void CBSLXMLAttributeEx::SetValue(const wxChar* pszValue)
{
    m_uiValueHash = FNV1_32_INIT;
    wxChar* pPosition = m_pszValue = wxConstCast(pszValue, wxChar);

    // Skip to the end of the attribute value
    while (*pPosition)
    {
        FNV132COMPUTE(m_uiValueHash, *pPosition);
        pPosition++;
    }

    m_uiValueLength = (wxUint32)(pPosition - pszValue);
}

BSLXMLERRCODE CBSLXMLAttributeEx::Parse(CBSLXMLDocumentEx& oDocument)
{
    BSLXMLERRCODE rc = BSLXMLERR_MALFORMED_XML;
    wxChar* pPosition = oDocument.GetPosition();
    wxChar cQuoteType = 0;

    m_pszName = NULL;
    m_uiNameHash = FNV1_32_INIT;
    m_uiNameLength = 0;
    m_pszValue = NULL;
    m_uiValueHash = FNV1_32_INIT;
    m_uiValueLength = 0;


    // Skip any whitespace
    while (lookup_whitespace[*pPosition])
        ++pPosition;

    // Record the start of the attribute name
    m_pszName = pPosition;

    // Skip to the end of the attribute name
    while (lookup_attribute_name[*pPosition])
    {
        FNV132COMPUTE(m_uiNameHash, *pPosition);
        ++pPosition;
    }

    // Record the size of the attribute name
    m_uiNameLength = (wxUint32)(pPosition - m_pszName);

    // Skip whitespace after attribute name
    while (lookup_whitespace[*pPosition])
        ++pPosition;

    // Skip =
    ++pPosition;

    // Skip whitespace after =
    while (lookup_whitespace[*pPosition])
        ++pPosition;

    // Remember the quote type
    cQuoteType = *pPosition;

    // Skip over the start quote character
    ++pPosition;

    // Record the start of the attribute value
    m_pszValue = pPosition;

    if (cQuoteType == wxT('\''))
    {
        // Skip to the end of the attribute value
        while (lookup_attribute_data_1_pure[*pPosition])
        {
            FNV132COMPUTE(m_uiValueHash, *pPosition);
            ++pPosition;
        }
    }
    else
    {
        // Skip to the end of the attribute value
        while (lookup_attribute_data_2_pure[*pPosition])
        {
            FNV132COMPUTE(m_uiValueHash, *pPosition);
            ++pPosition;
        }
    }

    // Record the size of the attribute value
    m_uiValueLength = (wxUint32)(pPosition - m_pszValue);

    // Skip over the end quote character
    ++pPosition;

    // Skip whitespace after the attribute value
    while (lookup_whitespace[*pPosition])
        ++pPosition;

    // Terminate attribute name
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

    // Terminate attribute value
    if (m_uiValueLength)
    {
        m_pszValue[m_uiValueLength] = wxT('\0');
        if (pPosition == &m_pszValue[m_uiValueLength])
        {
            ++pPosition;
        }
    }

    // Update the position in the XML Stream
    if (BSLXMLERR_SUCCESS == rc)
    {
        oDocument.SetPosition(pPosition);
    }

    return rc;
}
