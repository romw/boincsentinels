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
#include "bslcommon/bslCommonTypes.h"
#include "bslProjectLinkTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectLinkTestCase);

void ProjectLinkTestCase::CreateDelete()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    CPPUNIT_ASSERT(pProjectLink != NULL);
    delete pProjectLink;
}

void ProjectLinkTestCase::Equality()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    CBSLProjectLink* pProjectLink2 = new CBSLProjectLink();
    CPPUNIT_ASSERT(*pProjectLink == *pProjectLink2);
    delete pProjectLink;
    delete pProjectLink2;
}

void ProjectLinkTestCase::Inequality()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    CBSLProjectLink* pProjectLink2 = new CBSLProjectLink();
    pProjectLink->SetName(wxT("blah"));
    CPPUNIT_ASSERT(*pProjectLink != *pProjectLink2);
    delete pProjectLink;
    delete pProjectLink2;
}

void ProjectLinkTestCase::AssignmentOperator()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    CBSLProjectLink* pProjectLink2 = new CBSLProjectLink();
    pProjectLink->SetName(wxT("blah"));
    *pProjectLink2 = *pProjectLink;
    CPPUNIT_ASSERT(pProjectLink->GetName() == pProjectLink2->GetName());
    delete pProjectLink;
    delete pProjectLink2;
}

void ProjectLinkTestCase::GetSetName()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    wxString strName = wxT("Blah");
    pProjectLink->SetName(strName);
    CPPUNIT_ASSERT(strName == pProjectLink->GetName());
    delete pProjectLink;
}

void ProjectLinkTestCase::GetSetDescription()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    wxString strDescription = wxT("Blah");
    pProjectLink->SetDescription(strDescription);
    CPPUNIT_ASSERT(strDescription == pProjectLink->GetDescription());
    delete pProjectLink;
}

void ProjectLinkTestCase::GetSetLink()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    wxString strLink = wxT("http://goofy.example.com/");
    pProjectLink->SetLink(strLink);
    CPPUNIT_ASSERT(strLink == pProjectLink->GetLink());
    delete pProjectLink;
}

void ProjectLinkTestCase::ParseEx()
{
    CBSLProjectLink* pProjectLink = new CBSLProjectLink();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strProjectLink;

    wxString strName = wxT("Einstein status");
    wxString strDescription = wxT("Current status of the Einstein@Home server");
    wxString strURL = wxT("http://einstein.phys.uwm.edu/server_status.php");

    strProjectLink.Printf(
        wxT("<gui_url>\n")
        wxT("    <name>%s</name>\n")
        wxT("    <description>%s</description>\n")
        wxT("    <url>%s</url>\n")
        wxT("</gui_url>\n"),
        strName.c_str(),
        strDescription.c_str(),
        strURL.c_str()
    );

    oDocument.SetDocument(strProjectLink);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECTLINK == oElement.GetNameHash())
        {
            pProjectLink->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectLink->GetName().mb_str(), strName, pProjectLink->GetName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectLink->GetDescription().mb_str(), strDescription, pProjectLink->GetDescription());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectLink->GetLink().mb_str(), strURL, pProjectLink->GetLink());

    delete pProjectLink;
}
