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
#include "bslAppTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AppTestCase);

void AppTestCase::CreateDelete()
{
    CBSLApp* pApp = new CBSLApp();
    CPPUNIT_ASSERT(pApp != NULL);
    delete pApp;
}

void AppTestCase::Equality()
{
    CBSLApp* pApp = new CBSLApp();
    CBSLApp* pApp2 = new CBSLApp();
    CPPUNIT_ASSERT(*pApp == *pApp2);
    delete pApp;
    delete pApp2;
}

void AppTestCase::Inequality()
{
    CBSLApp* pApp = new CBSLApp();
    CBSLApp* pApp2 = new CBSLApp();
    pApp->SetName(wxT("TestApp"));
    CPPUNIT_ASSERT(*pApp != *pApp2);
    delete pApp;
    delete pApp2;
}

void AppTestCase::AssignmentOperator()
{
    CBSLApp* pApp = new CBSLApp();
    CBSLApp* pApp2 = new CBSLApp();
    pApp->SetName(wxT("TestApp"));
    *pApp2 = *pApp;
    CPPUNIT_ASSERT(pApp->GetName() == pApp2->GetName());
    delete pApp;
    delete pApp2;
}

void AppTestCase::GetSetProject()
{
    CBSLApp* pApp = new CBSLApp();
    wxString strProject = wxT("TestApp");
    pApp->SetProject(strProject);
    CPPUNIT_ASSERT(strProject == pApp->GetProject());
    delete pApp;
}

void AppTestCase::GetSetName()
{
    CBSLApp* pApp = new CBSLApp();
    wxString strName = wxT("TestApp");
    pApp->SetName(strName);
    CPPUNIT_ASSERT(strName == pApp->GetName());
    delete pApp;
}

void AppTestCase::GetSetFriendlyName()
{
    CBSLApp* pApp = new CBSLApp();
    wxString strName = wxT("Test Application");
    pApp->SetUserFriendlyName(strName);
    CPPUNIT_ASSERT(strName == pApp->GetUserFriendlyName());
    delete pApp;
}

void AppTestCase::GetSetNonCPUIntensive()
{
    CBSLApp* pApp = new CBSLApp();
    pApp->SetNonCPUIntensive(true);
    CPPUNIT_ASSERT(true == pApp->IsNonCPUIntensive());
    delete pApp;
}

void AppTestCase::ParseEx()
{
    CBSLApp* pApp = new CBSLApp();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strApp;

    wxString strName = wxT("Uppercase");
    wxString strUserFriendlyName = wxT("Uppercase Application");

    strApp.Printf(
        wxT("<app>\n")
        wxT("    <name>%s</name>\n")
        wxT("    <user_friendly_name>%s</user_friendly_name>\n")
        wxT("</app>\n"),
        strName.c_str(),
        strUserFriendlyName.c_str()
    );

    oDocument.SetDocument(strApp);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_APP == oElement.GetNameHash())
        {
            pApp->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pApp->GetName().mb_str(), strName, pApp->GetName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pApp->GetUserFriendlyName().mb_str(), strUserFriendlyName, pApp->GetUserFriendlyName());

    delete pApp;
}
