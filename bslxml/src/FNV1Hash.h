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

#ifndef FNV1HASH_H_
#define FNV1HASH_H_

/// See: http://tools.ietf.org/html/draft-eastlake-fnv-04


// Constant values
#define FNV1_32_INIT 0x811C9DC5
#define FNV1_32_PRIME 0x01000193

#define FNV1_64_INIT 0xCBF29CE484222325
#define FNV1_64_PRIME 0x00000100000001B3

#define FNV132COMPUTE(hash, value) \
    hash *= FNV1_32_PRIME; \
    hash ^= value;

#define FNV164COMPUTE(hash, value) \
    hash *= FNV1_64_PRIME; \
    hash ^= value;

#endif

///
/// \}

