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
#include "bslAppVersionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AppVersionTestCase);

void AppVersionTestCase::CreateDelete()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    CPPUNIT_ASSERT(pAppVersion != NULL);
    delete pAppVersion;
}

void AppVersionTestCase::Equality()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    CBSLAppVersion* pAppVersion2 = new CBSLAppVersion();
    CPPUNIT_ASSERT(*pAppVersion == *pAppVersion2);
    delete pAppVersion;
    delete pAppVersion2;
}

void AppVersionTestCase::Inequality()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    CBSLAppVersion* pAppVersion2 = new CBSLAppVersion();
    pAppVersion->SetName(wxT("blah"));
    CPPUNIT_ASSERT(*pAppVersion != *pAppVersion2);
    delete pAppVersion;
    delete pAppVersion2;
}

void AppVersionTestCase::AssignmentOperator()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    CBSLAppVersion* pAppVersion2 = new CBSLAppVersion();
    pAppVersion->SetName(wxT("blah"));
    *pAppVersion2 = *pAppVersion;
    CPPUNIT_ASSERT(pAppVersion->GetName() == pAppVersion2->GetName());
    delete pAppVersion;
    delete pAppVersion2;
}

void AppVersionTestCase::GetSetName()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    wxString strName = wxT("TestApp");
    pAppVersion->SetName(strName);
    CPPUNIT_ASSERT(strName == pAppVersion->GetName());
    delete pAppVersion;
}

void AppVersionTestCase::GetSetPlanClass()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    wxString strPlanClass = wxT("PlanClass");
    pAppVersion->SetPlanClass(strPlanClass);
    CPPUNIT_ASSERT(strPlanClass == pAppVersion->GetPlanClass());
    delete pAppVersion;
}

void AppVersionTestCase::GetSetVersion()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    wxUint32 uiVersion = 256;
    pAppVersion->SetVersion(uiVersion);
    CPPUNIT_ASSERT(uiVersion == pAppVersion->GetVersion());
    delete pAppVersion;
}

void AppVersionTestCase::GetVersionMajor()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    wxUint32 uiVersion = 256;
    pAppVersion->SetVersion(uiVersion);
    CPPUNIT_ASSERT(2 == pAppVersion->GetVersionMajor());
    delete pAppVersion;
}

void AppVersionTestCase::GetVersionMinor()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    wxUint32 uiVersion = 256;
    pAppVersion->SetVersion(uiVersion);
    CPPUNIT_ASSERT(56 == pAppVersion->GetVersionMinor());
    delete pAppVersion;
}

void AppVersionTestCase::ParseEx()
{
    CBSLAppVersion* pAppVersion = new CBSLAppVersion();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strApp;

    wxString strName = wxT("Uppercase");
    wxString strPlanClass = wxT("Supperfly");
    wxString strVersion = wxT("2456");

    strApp.Printf(
        wxT("<app_version>\n")
        wxT("    <app_name>%s</app_name>\n")
        wxT("    <plan_class>%s</plan_class>\n")
        wxT("    <version_num>%s</version_num>\n")
        wxT("</app_version>\n"),
        strName.c_str(),
        strPlanClass.c_str(),
        strVersion.c_str()
    );

    oDocument.SetDocument(strApp);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_APPVERSION == oElement.GetNameHash())
        {
            pAppVersion->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pAppVersion->GetName().mb_str(), strName, pAppVersion->GetName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pAppVersion->GetPlanClass().mb_str(), strPlanClass, pAppVersion->GetPlanClass());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Major Version", (wxUint32)24, pAppVersion->GetVersionMajor());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Minor Version", (wxUint32)56, pAppVersion->GetVersionMinor());

    delete pAppVersion;
}
