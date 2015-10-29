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

#ifndef _BSLXMLERRORS_H_
#define _BSLXMLERRORS_H_

/// \brief Return codes for various BOINC Sentinels XML Library functions.
enum BSLXMLERRCODE
{
    /// \brief the requested operation completed successfully.
    BSLXMLERR_SUCCESS = 0,
    /// \brief the requested operation failed.
    BSLXMLERR_FAILURE = 1,
    /// \brief one of the provided parameters is invalid.
    BSLXMLERR_INVALID_PARAMETER = 2,
    /// \brief the specified file could not be found.
    BSLXMLERR_FILE_NOT_FOUND = 3,
    /// \brief the specified XML could not be parsed correctly.
    BSLXMLERR_MALFORMED_XML = 4
};

#endif

///
/// \}
