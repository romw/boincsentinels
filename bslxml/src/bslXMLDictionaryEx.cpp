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
#include "FNV1Hash.h"

CBSLXMLDictionaryEx::CBSLXMLDictionaryEx()
{
    m_iElementsSize = 0;
    Clear();
}

CBSLXMLDictionaryEx::CBSLXMLDictionaryEx(const CBSLXMLDictionaryEx& bslXMLDictionaryEx)
{
    for (size_t i = 0; i < bslXMLDictionaryEx.m_Elements.size(); ++i)
    {
        m_Elements.push_back(new CBSLXMLElementEx(*bslXMLDictionaryEx.m_Elements[i]));
    }
    m_iNextElement = bslXMLDictionaryEx.m_iNextElement;
    m_iElementsSize = bslXMLDictionaryEx.m_iElementsSize;
}

CBSLXMLDictionaryEx::~CBSLXMLDictionaryEx()
{
    for (size_t i = 0; i < m_iElementsSize; ++i)
    {
        delete m_Elements[i];
    }
    m_Elements.clear();
}

void CBSLXMLDictionaryEx::Clear()
{
    m_iNextElement = 0;
    for (size_t i = 0; i < m_iElementsSize; ++i)
    {
        m_Elements[i]->Clear();
    }
}

CBSLXMLElementEx* CBSLXMLDictionaryEx::FindElement(const wxChar* pszName)
{
    wxUint32 ulHash = FNV1_32_INIT;
    wxChar* pPosition = (wxChar*)pszName;

    // Compute hash to compare against the elements hash
    while (*pPosition)
    {
        FNV132COMPUTE(ulHash, *pPosition);
        ++pPosition;
    }

    return FindElement(ulHash);
}

CBSLXMLElementEx* CBSLXMLDictionaryEx::FindElement(wxUint32 uiNameHash)
{
    // Find desired element by hash
    for (size_t i = 0; i < m_iNextElement; ++i)
    {
        if (uiNameHash == m_Elements[i]->GetNameHash())
        {
            return m_Elements[i];
        }
    }

    return NULL;
}

BSLXMLERRCODE CBSLXMLDictionaryEx::Parse(CBSLXMLDocumentEx& oDocument, wxUint32 uiTagHash)
{
    CBSLXMLElementEx oElement;
    CBSLXMLElementEx* pElement = NULL;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (uiTagHash == oElement.GetNameHash())
            break;

        if (m_iNextElement >= m_iElementsSize)
        {
            m_Elements.push_back(new CBSLXMLElementEx(oElement));
            ++m_iElementsSize;
        }
        else
        {
            pElement = m_Elements[m_iNextElement];
            pElement->Clear();
            *pElement = oElement;
        }

        ++m_iNextElement;
    }

    return BSLXMLERR_SUCCESS;
}
