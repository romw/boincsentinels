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


CBSLXMLDocumentEx::CBSLXMLDocumentEx()
{
    Clear();
}

CBSLXMLDocumentEx::~CBSLXMLDocumentEx()
{
}

void CBSLXMLDocumentEx::Clear()
{
    m_bFirstElement = true;
    m_pCurrentPosition = wxConstCast(m_strDocument.wx_str(), wxChar);
    m_pLastPosition = NULL;
}

wxChar* CBSLXMLDocumentEx::GetPosition()
{
    return m_pCurrentPosition;
}

BSLXMLERRCODE CBSLXMLDocumentEx::GetDocument(wxString& strDocument)
{
    strDocument = m_strDocument;
    return BSLXMLERR_SUCCESS;
}

BSLXMLERRCODE CBSLXMLDocumentEx::GetNextElement(CBSLXMLElementEx& oElement)
{
    // Have we reached the end?
    if (m_pCurrentPosition == NULL || *m_pCurrentPosition == wxT('\0'))
    {
        return BSLXMLERR_FAILURE;
    }

    // Manually advance one character and search for the start of the next element
    if ((!m_bFirstElement) && (m_pLastPosition == m_pCurrentPosition))
    {
        ++m_pCurrentPosition;
    }

    // Find the next XML element
    m_pCurrentPosition = bslXMLStrChr(m_pCurrentPosition, wxT('<'));

    // Have we reached the end?
    if (m_pCurrentPosition == NULL || *m_pCurrentPosition == wxT('\0'))
    {
        return BSLXMLERR_FAILURE;
    }

    // Update
    m_pLastPosition = m_pCurrentPosition;

    if (m_bFirstElement)
    {
        m_bFirstElement = false;
    }

    oElement.Clear();
    oElement.Parse(*this);

    return BSLXMLERR_SUCCESS;
}

BSLXMLERRCODE CBSLXMLDocumentEx::SkipContainer(CBSLXMLElementEx& oElement)
{
    BSLXMLERRCODE rc = BSLXMLERR_FAILURE;
    CBSLXMLElementEx oWorkingElement;
    wxUint32 uiNestedContainerLevel = 0;

    if (CBSLXMLElementEx::ElementTypeContainer != oElement.GetType()) 
    {
        return BSLXMLERR_INVALID_PARAMETER;
    }

    do
    {
        rc = GetNextElement(oWorkingElement);
        if (BSLXMLERR_SUCCESS == rc)
        {
            if (CBSLXMLElementEx::ElementTypeContainer == oWorkingElement.GetType())
            {
                ++uiNestedContainerLevel;
            }
            else if (CBSLXMLElementEx::ElementTypeContainerEnd == oWorkingElement.GetType())
            {
                if (0 < uiNestedContainerLevel)
                {
                    --uiNestedContainerLevel;
                }
                else
                {
                    if (oWorkingElement.GetNameHash() == oElement.GetNameHash())
                    {
                        break;
                    }
                }
            }
        }
    }
    while (BSLXMLERR_SUCCESS == rc);

    return rc;
}

BSLXMLERRCODE CBSLXMLDocumentEx::SetPosition(const wxChar* pPosition)
{
    m_pLastPosition = m_pCurrentPosition;
    m_pCurrentPosition = wxConstCast(pPosition, wxChar);

    return BSLXMLERR_SUCCESS;
}

BSLXMLERRCODE CBSLXMLDocumentEx::SetDocument(const wxChar* pszDocument)
{
    if (NULL == pszDocument)
    {
        return BSLXMLERR_INVALID_PARAMETER;
    }

    Clear();
    m_strDocument = pszDocument;
    m_pCurrentPosition = wxConstCast(m_strDocument.wx_str(), wxChar);

    return BSLXMLERR_SUCCESS;
}

BSLXMLERRCODE CBSLXMLDocumentEx::SetDocument(const wxString& strDocument)
{
    if (strDocument.IsEmpty())
    {
        return BSLXMLERR_INVALID_PARAMETER;
    }

    Clear();
    m_strDocument = strDocument;
    m_pCurrentPosition = wxConstCast(m_strDocument.wx_str(), wxChar);

    return BSLXMLERR_SUCCESS;
}

BSLXMLERRCODE CBSLXMLDocumentEx::SetDocumentFromFile(const wxString strFilename)
{
    if (strFilename.IsEmpty())
    {
        return BSLXMLERR_INVALID_PARAMETER;
    }
    if (!wxFile::Exists(strFilename))
    {
        return BSLXMLERR_FILE_NOT_FOUND;
    }

    wxFFile file(strFilename, wxT("r"));
    if (file.IsOpened())
    {
        if (file.ReadAll(&m_strDocument, wxConvUTF8))
        {
            Clear();
            return BSLXMLERR_SUCCESS;
        }
    }

    return BSLXMLERR_FAILURE;
}
