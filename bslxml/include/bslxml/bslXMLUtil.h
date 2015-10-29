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

#ifndef BSLXMLUTIL_H_
#define BSLXMLUTIL_H_

/// \brief Find a character within a null terminated string.
/// \param[in] s a null terminated string to search.
/// \param[in] c the character to search for.
/// \retval The pointer to the character being searched for, or NULL if not found.
extern wxChar* bslXMLStrChr(const wxChar* s, int c);

/// \brief Compute the FNV1 32-bit hash for a given null terminated string.
/// \param[in] s a null terminated string to compute the hash for.
/// \param[in] l the length of the string.
/// \retval The FNV1 32-bit hash of the string, or 0 if it is zero length.
extern wxUint32 bslXMLStrHash32(const wxChar* s, size_t l);

/// \brief Compute the FNV1 32-bit hash for a given string.
/// \param[in] s a string to compute the hash for.
/// \retval The FNV1 32-bit hash of the string, or 0 if it is zero length.
inline wxUint32 bslXMLStrHash32(wxString s)
{
    return bslXMLStrHash32(s.c_str(), s.size());
}

/// \brief Compute the FNV1 64-bit hash for a given null terminated string.
/// \param[in] s a null terminated string to compute the hash for.
/// \param[in] l the length of the string.
/// \retval The FNV1 64-bit hash of the string, or 0 if it is zero length.
extern wxUint64 bslXMLStrHash64(const wxChar* s, size_t l);

/// \brief Compute the FNV1 64-bit hash for a given string.
/// \param[in] s a string to compute the hash for.
/// \retval The FNV1 64-bit hash of the string, or 0 if it is zero length.
inline wxUint64 bslXMLStrHash64(wxString s)
{
    return bslXMLStrHash64(s.c_str(), s.size());
}

#endif

///
/// \}
