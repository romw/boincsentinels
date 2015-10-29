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

#ifndef _BSLXMLCONVERTEREX_H_
#define _BSLXMLCONVERTEREX_H_

///
/// \brief Data type conversion routines.
///
/// Convert NULL terminated strings into different data types.
///
class CBSLXMLConverterEx
{
    friend class CBSLXMLTestUtil;

public:

    /// \brief Convert a null terminated string into a boolean.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval True/False
    static bool ConvertToBool(wxChar* pszValue);

    /// \brief Convert a null terminated string into a wxString.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxString
    static wxString ConvertToString(wxChar* pszValue, wxUint32 uiValueLength);

    /// \brief Convert a null terminated string into a wxDouble.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxDouble
    static wxDouble ConvertToDouble(wxChar* pszValue);

    /// \brief Convert a null terminated string into a wxInt32.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxInt32
    static wxInt32 ConvertToI32(wxChar* pszValue);

    /// \brief Convert a null terminated string into a wxInt64.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxInt64
    static wxInt64 ConvertToI64(wxChar* pszValue);

    /// \brief Convert a null terminated string into a wxUint32.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxUint32
    static wxUint32 ConvertToUI32(wxChar* pszValue);

    /// \brief Convert a null terminated string into a wxUint64.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxUint64
    static wxUint64 ConvertToUI64(wxChar* pszValue);

    /// \brief Convert a null terminated string into a wxDateTime.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxDateTime
    static wxDateTime ConvertToDateTime(wxChar* pszValue);

    /// \brief Convert a null terminated string into a wxTimeSpan.
    /// \param[in] pszValue the null terminated string to convert.
    /// \retval A valid wxTimeSpan
    static wxTimeSpan ConvertToTimeSpan(wxChar* pszValue);
};

#endif

///
/// \}
