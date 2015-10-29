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

#ifndef _BOINCXMLSTREAM_H_
#define _BOINCXMLSTREAM_H_

///
/// \sa \ref page_boincxmlparser
///
class CBOINCXMLStream
{
public:
    CBOINCXMLStream();
    ~CBOINCXMLStream();

    void Clear();

    bool CurrentLineMatchesTag(const wxChar* pszTag);
    wxChar* GetCurrentLine();
    size_t GetCurrentLineSize();
    wxChar* GetCurrentPosition();
    bool ReadNextLine();
    void Reset();
    bool SetCurrentPosition(const wxChar* pPosition);
    void SetStream(const wxChar* pszStreamContents);
    bool StreamFromFile(wxString strFilename);

    // Diagnostics/Performance testing stuff
    void Replicate(wxUint32 uiCopies);

private:
    wxString m_strStreamContents;
    bool m_bFirstLine;
    bool m_bCurrentLineNullTerminated;
    wxChar* m_pCurrentPosition;
    wxChar* m_pNextPosition;
};

#endif

///
/// \}
