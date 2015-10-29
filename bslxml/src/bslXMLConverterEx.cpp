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

bool CBSLXMLConverterEx::ConvertToBool(wxChar* pszValue)
{
    bool bValue = (wxT('1') == *pszValue);
    return bValue;
}

wxString CBSLXMLConverterEx::ConvertToString(wxChar* pszValue, wxUint32 uiValueLength)
{
    if (pszValue && uiValueLength)
    {
        return wxString(pszValue, uiValueLength);
    }
    return wxEmptyString;
}

wxDouble CBSLXMLConverterEx::ConvertToDouble(wxChar* pszValue)
{
    if (pszValue)
    {
        return _tstof(pszValue);
    }
    return 0.0;
}

wxInt32 CBSLXMLConverterEx::ConvertToI32(wxChar* pszValue)
{
    if (pszValue)
    {
        return (wxInt32)_tcstol(pszValue, NULL, 10);
    }
    return 0;
}

wxInt64 CBSLXMLConverterEx::ConvertToI64(wxChar* pszValue)
{
    if (pszValue)
    {
        return _tcstoll(pszValue, NULL, 10);
    }
    return 0;
}

wxUint32 CBSLXMLConverterEx::ConvertToUI32(wxChar* pszValue)
{
    if (pszValue)
    {
        return (wxUint32)_tcstoul(pszValue, NULL, 10);
    }
    return 0;
}

wxUint64 CBSLXMLConverterEx::ConvertToUI64(wxChar* pszValue)
{
    if (pszValue)
    {
        return _tcstoull(pszValue, NULL, 10);
    }
    return 0;
}

wxDateTime CBSLXMLConverterEx::ConvertToDateTime(wxChar* pszValue)
{
    if (pszValue)
    {
        return wxDateTime((time_t)_tcstoull(pszValue, NULL, 10));
    }
    return wxDateTime((time_t)0);
}

wxTimeSpan CBSLXMLConverterEx::ConvertToTimeSpan(wxChar* pszValue)
{
    if (pszValue)
    {
        return wxTimeSpan(0, 0, _tcstoull(pszValue, NULL, 10), 0);
    }
    return wxTimeSpan(0);
}
