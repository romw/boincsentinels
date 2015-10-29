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
#include "bslAppEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AppEventDataTestCase);

void AppEventDataTestCase::CreateDelete()
{
    CBSLAppEventData* pAppEventData = new CBSLAppEventData();
    CPPUNIT_ASSERT(pAppEventData != NULL);
    delete pAppEventData;
}

void AppEventDataTestCase::CopyConstructor()
{
    CBSLAppEventData* pAppEventData = new CBSLAppEventData();
    CPPUNIT_ASSERT(pAppEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pAppEventData->SetHostHandle(hHost);

    CBSLAppEventData* pAppEventData2 = new CBSLAppEventData(*pAppEventData);
    CPPUNIT_ASSERT(pAppEventData2 != NULL);

    CPPUNIT_ASSERT(pAppEventData->GetHostHandle() == pAppEventData2->GetHostHandle());

    delete pAppEventData;
    delete pAppEventData2;
}

void AppEventDataTestCase::GetSetHostHandle()
{
    CBSLAppEventData* pAppEventData = new CBSLAppEventData();
    CPPUNIT_ASSERT(pAppEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pAppEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pAppEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pAppEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pAppEventData->GetAppHandle());

    delete pAppEventData;
}

void AppEventDataTestCase::GetSetProjectHandle()
{
    CBSLAppEventData* pAppEventData = new CBSLAppEventData();
    CPPUNIT_ASSERT(pAppEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pAppEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(NULL == pAppEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProject == pAppEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pAppEventData->GetAppHandle());

    delete pAppEventData;
}

void AppEventDataTestCase::GetSetAppHandle()
{
    CBSLAppEventData* pAppEventData = new CBSLAppEventData();
    CPPUNIT_ASSERT(pAppEventData != NULL);

    BSLAPP hApp = (BSLAPP) 0x314156;
    pAppEventData->SetAppHandle(hApp);
    CPPUNIT_ASSERT(NULL == pAppEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pAppEventData->GetProjectHandle());
    CPPUNIT_ASSERT(hApp == pAppEventData->GetAppHandle());

    delete pAppEventData;
}
