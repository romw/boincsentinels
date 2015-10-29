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
#include "bslxml/bslXMLTestUtil.h"

void CBSLXMLTestUtil::ReplicateDocument(CBSLXMLDocumentEx& oDocument, const wxUint32 uiCopies)
{
    wxString strBuffer;
    wxString strDocument;
    wxUint32 uiCount = uiCopies - 1;

    oDocument.GetDocument(strBuffer);

    strDocument.Alloc(strBuffer.size() * uiCopies);
    for (wxUint32 i = 0; i < uiCount; ++i)
    {
        strDocument += strBuffer;
    }

    oDocument.SetDocument(strDocument);
}
