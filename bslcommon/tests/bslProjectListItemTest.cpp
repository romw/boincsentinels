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
#include "bslProjectListItemTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectListItemTestCase);

void ProjectListItemTestCase::CreateDelete()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    CPPUNIT_ASSERT(pProjectListItem != NULL);
    delete pProjectListItem;
}

void ProjectListItemTestCase::Equality()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    CBSLProjectListItem* pProjectListItem2 = new CBSLProjectListItem();
    CPPUNIT_ASSERT(*pProjectListItem == *pProjectListItem2);
    delete pProjectListItem;
    delete pProjectListItem2;
}

void ProjectListItemTestCase::Inequality()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    CBSLProjectListItem* pProjectListItem2 = new CBSLProjectListItem();
    pProjectListItem->SetName(wxT("blah"));
    CPPUNIT_ASSERT(*pProjectListItem != *pProjectListItem2);
    delete pProjectListItem;
    delete pProjectListItem2;
}

void ProjectListItemTestCase::AssignmentOperator()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    CBSLProjectListItem* pProjectListItem2 = new CBSLProjectListItem();
    pProjectListItem->SetName(wxT("blah"));
    *pProjectListItem2 = *pProjectListItem;
    CPPUNIT_ASSERT(pProjectListItem->GetName() == pProjectListItem2->GetName());
    delete pProjectListItem;
    delete pProjectListItem2;
}

void ProjectListItemTestCase::GetSetMasterURL()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    wxString strMasterURL = wxT("http://goofy.example.com/");
    pProjectListItem->SetMasterURL(strMasterURL);
    CPPUNIT_ASSERT(strMasterURL == pProjectListItem->GetMasterURL());
    delete pProjectListItem;
}

void ProjectListItemTestCase::GetSetName()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    wxString strName = wxT("Blah");
    pProjectListItem->SetName(strName);
    CPPUNIT_ASSERT(strName == pProjectListItem->GetName());
    delete pProjectListItem;
}

void ProjectListItemTestCase::GetSetDescription()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    wxString strDescription = wxT("Blah");
    pProjectListItem->SetDescription(strDescription);
    CPPUNIT_ASSERT(strDescription == pProjectListItem->GetDescription());
    delete pProjectListItem;
}

void ProjectListItemTestCase::GetSetGeneralArea()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    wxString strGeneralArea = wxT("Blah");
    pProjectListItem->SetGeneralArea(strGeneralArea);
    CPPUNIT_ASSERT(strGeneralArea == pProjectListItem->GetGeneralArea());
    delete pProjectListItem;
}

void ProjectListItemTestCase::GetSetSpecificArea()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    wxString strSpecificArea = wxT("Blah");
    pProjectListItem->SetSpecificArea(strSpecificArea);
    CPPUNIT_ASSERT(strSpecificArea == pProjectListItem->GetSpecificArea());
    delete pProjectListItem;
}

void ProjectListItemTestCase::GetSetOrganization()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    wxString strOrganization = wxT("Blah");
    pProjectListItem->SetOrganization(strOrganization);
    CPPUNIT_ASSERT(strOrganization == pProjectListItem->GetOrganization());
    delete pProjectListItem;
}

void ProjectListItemTestCase::GetSetLogo()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    wxString strLogo = wxT("http://goofy.example.com/logo.jpg");
    pProjectListItem->SetLogo(strLogo);
    CPPUNIT_ASSERT(strLogo == pProjectListItem->GetLogo());
    delete pProjectListItem;
}

void ProjectListItemTestCase::GetSetSupportedPlatforms()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    std::vector<wxString> oPlatforms;
    wxString strPlaform = wxT("blah");
    oPlatforms.push_back(strPlaform);
    pProjectListItem->SetSupportedPlatforms(oPlatforms);
    CPPUNIT_ASSERT(oPlatforms == pProjectListItem->GetSupportedPlatforms());
    delete pProjectListItem;
}

void ProjectListItemTestCase::ParseEx()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strProjectListItem;

    wxString strMasterURL = wxT("http://escatter11.fullerton.edu/nfs/");
    wxString strName = wxT("NFS@home");
    wxString strGeneralArea = wxT("Mathematics, computing, and games");
    wxString strSpecificArea = wxT("Factorization of large integers");
    wxString strDescription = wxT("NFS@Home is a research project that uses Internet-connected computers to do the lattice sieving step in the Number Field Sieve factorization of large integers. As a young school student, you gained your first experience at breaking an integer into prime factors, such as 15 = 3 * 5 or 35 = 5 * 7. NFS@Home is a continuation of that experience, only with integers that are hundreds of digits long.");
    wxString strOrganization = wxT("California State University Fullerton");
    wxString strLogo = wxT("http://boinc.berkeley.edu/images/NFS_Logo.jpg");
    wxString strPlatform1 = wxT("i686-apple-darwin");
    wxString strPlatform2 = wxT("i686-pc-linux-gnu");
    wxString strPlatform3 = wxT("windows_intelx86");
    wxString strPlatform4 = wxT("x86_64-pc-linux-gnu");

    strProjectListItem.Printf(
        wxT("<project>\n")
        wxT("    <name>%s</name>\n")
        wxT("    <url>%s</url>\n")
        wxT("    <general_area>%s</general_area>\n")
        wxT("    <specific_area>%s</specific_area>\n")
        wxT("    <description>%s</description>\n")
        wxT("    <home>%s</home>\n")
        wxT("    <platforms>\n")
        wxT("        <name>%s</name>\n")
        wxT("        <name>%s</name>\n")
        wxT("        <name>%s</name>\n")
        wxT("        <name>%s</name>\n")
        wxT("    </platforms>\n")
        wxT("    <image>%s</image>\n")
        wxT("</project>\n"),
        strName.c_str(),
        strMasterURL.c_str(),
        strGeneralArea.c_str(),
        strSpecificArea.c_str(),
        strDescription.c_str(),
        strOrganization.c_str(),
        strPlatform1.c_str(),
        strPlatform2.c_str(),
        strPlatform3.c_str(),
        strPlatform4.c_str(),
        strLogo.c_str()
    );

    oDocument.SetDocument(strProjectListItem);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECTLISTITEM == oElement.GetNameHash())
        {
            pProjectListItem->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetName().mb_str(), strName, pProjectListItem->GetName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetMasterURL().mb_str(), strMasterURL, pProjectListItem->GetMasterURL());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetGeneralArea().mb_str(), strGeneralArea, pProjectListItem->GetGeneralArea());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSpecificArea().mb_str(), strSpecificArea, pProjectListItem->GetSpecificArea());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetDescription().mb_str(), strDescription, pProjectListItem->GetDescription());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetOrganization().mb_str(), strOrganization, pProjectListItem->GetOrganization());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[0].mb_str(), strPlatform1, pProjectListItem->GetSupportedPlatforms()[0]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[1].mb_str(), strPlatform2, pProjectListItem->GetSupportedPlatforms()[1]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[2].mb_str(), strPlatform3, pProjectListItem->GetSupportedPlatforms()[2]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[3].mb_str(), strPlatform4, pProjectListItem->GetSupportedPlatforms()[3]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetLogo().mb_str(), strLogo, pProjectListItem->GetLogo());

    delete pProjectListItem;
}

void ProjectListItemTestCase::ParseCDATA()
{
    CBSLProjectListItem* pProjectListItem = new CBSLProjectListItem();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strProjectListItem;

    wxString strMasterURL = wxT("http://www.primegrid.com/");
    wxString strName = wxT("PrimeGrid");
    wxString strGeneralArea = wxT("Mathematics, computing, and games");
    wxString strSpecificArea = wxT("Cryptography");
    wxString strDescription = wxT("Primegrid is generating a public sequential prime number database, and is searching for large twin primes of the form k*2<sup>n</sup>+1 and k*2<sup>n</sup>-1");
    wxString strOrganization = wxT("Private");
    wxString strLogo = wxT("http://boinc.berkeley.edu/images/primegrid_logo.png");
    wxString strPlatform1 = wxT("i686-apple-darwin");
    wxString strPlatform2 = wxT("i686-pc-linux-gnu");
    wxString strPlatform3 = wxT("windows_intelx86");
    wxString strPlatform4 = wxT("x86_64-pc-linux-gnu");

    strProjectListItem.Printf(
        wxT("<project>\n")
        wxT("    <name>%s</name>\n")
        wxT("    <url>%s</url>\n")
        wxT("    <general_area>%s</general_area>\n")
        wxT("    <specific_area>%s</specific_area>\n")
        wxT("    <description><![CDATA[%s]]></description>\n")
        wxT("    <home>%s</home>\n")
        wxT("    <platforms>\n")
        wxT("        <name>%s</name>\n")
        wxT("        <name>%s</name>\n")
        wxT("        <name>%s</name>\n")
        wxT("        <name>%s</name>\n")
        wxT("    </platforms>\n")
        wxT("    <image>%s</image>\n")
        wxT("</project>\n"),
        strName.c_str(),
        strMasterURL.c_str(),
        strGeneralArea.c_str(),
        strSpecificArea.c_str(),
        strDescription.c_str(),
        strOrganization.c_str(),
        strPlatform1.c_str(),
        strPlatform2.c_str(),
        strPlatform3.c_str(),
        strPlatform4.c_str(),
        strLogo.c_str()
    );

    oDocument.SetDocument(strProjectListItem);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECTLISTITEM == oElement.GetNameHash())
        {
            pProjectListItem->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetName().mb_str(), strName, pProjectListItem->GetName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetMasterURL().mb_str(), strMasterURL, pProjectListItem->GetMasterURL());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetGeneralArea().mb_str(), strGeneralArea, pProjectListItem->GetGeneralArea());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSpecificArea().mb_str(), strSpecificArea, pProjectListItem->GetSpecificArea());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetDescription().mb_str(), strDescription, pProjectListItem->GetDescription());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetOrganization().mb_str(), strOrganization, pProjectListItem->GetOrganization());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[0].mb_str(), strPlatform1, pProjectListItem->GetSupportedPlatforms()[0]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[1].mb_str(), strPlatform2, pProjectListItem->GetSupportedPlatforms()[1]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[2].mb_str(), strPlatform3, pProjectListItem->GetSupportedPlatforms()[2]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetSupportedPlatforms()[3].mb_str(), strPlatform4, pProjectListItem->GetSupportedPlatforms()[3]);
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pProjectListItem->GetLogo().mb_str(), strLogo, pProjectListItem->GetLogo());

    delete pProjectListItem;
}
