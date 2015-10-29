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
#include "BOINCXMLStream.h"
#include "LookupTables.h"


CBOINCXMLStream::CBOINCXMLStream()
{
    Clear();
}

CBOINCXMLStream::~CBOINCXMLStream()
{
}

void CBOINCXMLStream::Clear()
{
    m_strStreamContents.Clear();
    m_bFirstLine = true;
    m_bCurrentLineNullTerminated = false;
    m_pCurrentPosition = NULL;
    m_pNextPosition = NULL;
}

bool CBOINCXMLStream::CurrentLineMatchesTag(const wxChar* pszTag)
{
    wxChar *p1, *p2;

    p1 = (wxChar*)pszTag;
    p2 = m_pCurrentPosition;

    // Skip any whitespace, space \n \r \t \0
    while (lookup_whitespace[*p2])
        ++p2;

    // Compare
    while ((*p1 == *p2) && *p1 != '\0')
    {
        ++p1;
        ++p2;
    }

    return (*p1 == '\0') || ((*p1 - *p2) == 0);
}

wxChar* CBOINCXMLStream::GetCurrentLine()
{
    if (m_pCurrentPosition)
    {
        m_pNextPosition = _tcschr(m_pCurrentPosition, wxT('\n'));
        if (!m_pNextPosition) return NULL;

        wxChar* pEOL = m_pNextPosition - 1;
        *pEOL = wxT('\0');

        m_bCurrentLineNullTerminated = true;
    }

    return m_pCurrentPosition;
}

size_t CBOINCXMLStream::GetCurrentLineSize()
{
    return m_pNextPosition - m_pCurrentPosition + 1;
}

wxChar* CBOINCXMLStream::GetCurrentPosition()
{
    return m_pCurrentPosition;
}

bool CBOINCXMLStream::ReadNextLine()
{
    // First invocation, we want to be able to read the very first line
    // after the stream has been initialized.
    if (m_bFirstLine)
    {
        m_bFirstLine = false;
        return true;
    }

    if (m_bCurrentLineNullTerminated)
    {
        m_bCurrentLineNullTerminated = false;
        wxChar* pEOL = m_pNextPosition - 1;
        *pEOL = ' ';
    }

    // Have we reached the end of file?
    if (m_pCurrentPosition[0] == 0) return false;

    // Skip anything until we have found the EOL
    while (lookup_eol[*m_pCurrentPosition])
        ++m_pCurrentPosition;

    // Have we reached the end of file?
    if (m_pCurrentPosition[0] == 0) return true;

    // Must have found a newline, skip past it.
    ++m_pCurrentPosition;

    // Skip any whitespace
    while (lookup_whitespace[*m_pCurrentPosition])
        ++m_pCurrentPosition;

    return true;
}

void CBOINCXMLStream::Reset()
{
    wxChar* pStreamBuffer = (wxChar*) m_strStreamContents.wx_str();
    m_bFirstLine = true;
    m_bCurrentLineNullTerminated = false;
    m_pCurrentPosition = pStreamBuffer;
    m_pNextPosition = pStreamBuffer;
}

bool CBOINCXMLStream::SetCurrentPosition(const wxChar* pPosition)
{
    // Skip anything until we have found the EOL
    m_pCurrentPosition = (wxChar*)_tcschr(pPosition, '\n');
    return true;
}

void CBOINCXMLStream::SetStream(const wxChar* pszStreamContents)
{
    m_strStreamContents = pszStreamContents;
    Reset();
}

bool CBOINCXMLStream::StreamFromFile(wxString strFilename)
{
    if (wxFile::Exists(strFilename))
    {
        wxFFile file(strFilename, wxT("r"));
        if (file.IsOpened())
        {
            if (file.ReadAll(&m_strStreamContents, wxConvUTF8))
            {
                Reset();
                return true;
            }
        }
    }
    return false;
}

void CBOINCXMLStream::Replicate(wxUint32 uiCopies)
{
    wxString strBuffer = m_strStreamContents;
    wxUint32 uiCount = uiCopies - 1;
    m_strStreamContents.Alloc(strBuffer.size() * uiCopies);
    for (wxUint32 i = 0; i < uiCount; ++i)
    {
        m_strStreamContents += strBuffer;
    }
    Reset();
}
