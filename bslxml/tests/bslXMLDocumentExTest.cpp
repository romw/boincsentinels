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
#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>
#include "bslxml/bslXMLTypes.h"
#include "bslXMLDocumentExTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(XMLDocumentExTestCase);

void XMLDocumentExTestCase::CreateDelete()
{
    CBSLXMLDocumentEx* pXMLDocumentEx = new CBSLXMLDocumentEx();
    CPPUNIT_ASSERT(pXMLDocumentEx != NULL);
    delete pXMLDocumentEx;
}

void XMLDocumentExTestCase::SkipContainer()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strDocument;

    strDocument = 
        wxT("<msg>\n")
        wxT("    <foo>\n")
        wxT("    </foo>\n")
        wxT("    <time>testing</time>\n")
        wxT("</msg>\n");

    oDocument.SetDocument(strDocument);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (CBSLXMLElementEx::ElementTypeContainer == oElement.GetType())
        {
            rc = oDocument.SkipContainer(oElement);
        }
    }

    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDocumentExTestCase::SkipContainerNested()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strDocument;

    strDocument = 
        wxT("<msg>\n")
        wxT("    <foo>\n")
        wxT("        <fighters>\n")
        wxT("        </fighters>\n")
        wxT("    </foo>\n")
        wxT("    <time>testing</time>\n")
        wxT("</msg>\n");

    oDocument.SetDocument(strDocument);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (CBSLXMLElementEx::ElementTypeContainer == oElement.GetType())
        {
            rc = oDocument.SkipContainer(oElement);
        }
    }

    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDocumentExTestCase::SkipContainerNestedNested()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strDocument;

    strDocument = 
        wxT("<msg>\n")
        wxT("    <foo>\n")
        wxT("        <fighters>\n")
        wxT("            <foo>\n")
        wxT("            </foo>\n")
        wxT("        </fighters>\n")
        wxT("    </foo>\n")
        wxT("    <time>testing</time>\n")
        wxT("</msg>\n");

    oDocument.SetDocument(strDocument);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (CBSLXMLElementEx::ElementTypeContainer == oElement.GetType())
        {
            rc = oDocument.SkipContainer(oElement);
        }
    }

    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}
