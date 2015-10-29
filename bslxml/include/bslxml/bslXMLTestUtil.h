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

#ifndef BSLXMLTESTUTIL_H_
#define BSLXMLTESTUTIL_H_

///
/// \brief Provide a set of tools for manipulating XML data for unit tests.
///
class CBSLXMLTestUtil
{
public:

    /// \brief Replicate the current XML Document the specified number of times.
    /// \param[in] oDocument the XML Document to parse the element from.
    /// \param[in] uiCopies number of times to replicate the current XML Document.
    static void ReplicateDocument(CBSLXMLDocumentEx& oDocument, const wxUint32 uiCopies);
};

#endif

///
/// \}
