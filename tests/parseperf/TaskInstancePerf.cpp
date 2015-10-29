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
#include "bslcommon/bslCommonTypes.h"

void ParserTaskInstances(unsigned long& ulElapsedTime)
{
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLTaskInstance oTaskInstance;
    std::vector<CBSLTaskInstance> oTaskInstances;
    unsigned long ulStart = 0;
    unsigned long ulEnd = 0;

    if (oDocument.SetDocumentFromFile(wxT("get_results.xml")))
    {
        // Create enough records so that an actual measurement can be
        // made. 100000 should be enough.
        CBSLXMLTestUtil::ReplicateDocument(oDocument, 2300);

#ifdef __WXMSW__
        ulStart = GetTickCount();
#endif
        while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
        {
            if (BSLXMLTAGHASH_TASKINSTANCE == oElement.GetNameHash())
            {
                oTaskInstance.Clear();
                oTaskInstance.ParseEx(oDocument);

                oTaskInstances.push_back(oTaskInstance);
            }
        }
#ifdef __WXMSW__
        ulEnd = GetTickCount();
#endif

        ulElapsedTime = ulEnd - ulStart;
    }
}
