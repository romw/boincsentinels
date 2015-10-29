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
#include "bslcommon/bslCommonTypes.h"
#include "bslAppVersionEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AppVersionEventDataTestCase);

void AppVersionEventDataTestCase::CreateDelete()
{
    CBSLAppVersionEventData* pAppVersionEventData = new CBSLAppVersionEventData();
    CPPUNIT_ASSERT(pAppVersionEventData != NULL);
    delete pAppVersionEventData;
}

void AppVersionEventDataTestCase::CopyConstructor()
{
    CBSLAppVersionEventData* pAppVersionEventData = new CBSLAppVersionEventData();
    CPPUNIT_ASSERT(pAppVersionEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pAppVersionEventData->SetHostHandle(hHost);

    CBSLAppVersionEventData* pAppVersionEventData2 = new CBSLAppVersionEventData(*pAppVersionEventData);
    CPPUNIT_ASSERT(pAppVersionEventData2 != NULL);

    CPPUNIT_ASSERT(pAppVersionEventData->GetHostHandle() == pAppVersionEventData2->GetHostHandle());

    delete pAppVersionEventData;
    delete pAppVersionEventData2;
}

void AppVersionEventDataTestCase::GetSetHostHandle()
{
    CBSLAppVersionEventData* pAppVersionEventData = new CBSLAppVersionEventData();
    CPPUNIT_ASSERT(pAppVersionEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pAppVersionEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pAppVersionEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetAppVersionHandle());

    delete pAppVersionEventData;
}

void AppVersionEventDataTestCase::GetSetProjectHandle()
{
    CBSLAppVersionEventData* pAppVersionEventData = new CBSLAppVersionEventData();
    CPPUNIT_ASSERT(pAppVersionEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pAppVersionEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProject == pAppVersionEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetAppVersionHandle());

    delete pAppVersionEventData;
}

void AppVersionEventDataTestCase::GetSetAppHandle()
{
    CBSLAppVersionEventData* pAppVersionEventData = new CBSLAppVersionEventData();
    CPPUNIT_ASSERT(pAppVersionEventData != NULL);

    BSLAPP hApp = (BSLAPP) 0x314156;
    pAppVersionEventData->SetAppHandle(hApp);
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetProjectHandle());
    CPPUNIT_ASSERT(hApp == pAppVersionEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetAppVersionHandle());

    delete pAppVersionEventData;
}

void AppVersionEventDataTestCase::GetSetAppVersionHandle()
{
    CBSLAppVersionEventData* pAppVersionEventData = new CBSLAppVersionEventData();
    CPPUNIT_ASSERT(pAppVersionEventData != NULL);

    BSLAPPVERSION hAppVersion = (BSLAPPVERSION) 0x314156;
    pAppVersionEventData->SetAppVersionHandle(hAppVersion);
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pAppVersionEventData->GetAppHandle());
    CPPUNIT_ASSERT(hAppVersion == pAppVersionEventData->GetAppVersionHandle());

    delete pAppVersionEventData;
}
