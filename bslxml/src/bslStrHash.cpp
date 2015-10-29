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
#include "FNV1Hash.h"


wxUint32 bslXMLStrHash32(const wxChar* str, size_t l)
{
    wxUint32 uiHash = 0;

    if (l)
    {
        uiHash = FNV1_32_INIT;
        for (size_t i = 0; i < l; ++i)
        {
            FNV132COMPUTE(uiHash, str[i]);
        }
    }

    return uiHash;
}


wxUint64 bslXMLStrHash64(const wxChar* str, size_t l)
{
    wxUint64 uiHash = 0;

    if (l)
    {
        uiHash = FNV1_64_INIT;
        for (size_t i = 0; i < l; ++i)
        {
            FNV164COMPUTE(uiHash, str[i]);
        }
    }

    return uiHash;
}
