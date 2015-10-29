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
#include "bslTaskEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TaskEventDataTestCase);

void TaskEventDataTestCase::CreateDelete()
{
    CBSLTaskEventData* pTaskEventData = new CBSLTaskEventData();
    CPPUNIT_ASSERT(pTaskEventData != NULL);
    delete pTaskEventData;
}

void TaskEventDataTestCase::CopyConstructor()
{
    CBSLTaskEventData* pTaskEventData = new CBSLTaskEventData();
    CPPUNIT_ASSERT(pTaskEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pTaskEventData->SetHostHandle(hHost);

    CBSLTaskEventData* pTaskEventData2 = new CBSLTaskEventData(*pTaskEventData);
    CPPUNIT_ASSERT(pTaskEventData2 != NULL);

    CPPUNIT_ASSERT(pTaskEventData->GetHostHandle() == pTaskEventData2->GetHostHandle());

    delete pTaskEventData;
    delete pTaskEventData2;
}

void TaskEventDataTestCase::GetSetHostHandle()
{
    CBSLTaskEventData* pTaskEventData = new CBSLTaskEventData();
    CPPUNIT_ASSERT(pTaskEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pTaskEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pTaskEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetTaskHandle());

    delete pTaskEventData;
}

void TaskEventDataTestCase::GetSetProjectHandle()
{
    CBSLTaskEventData* pTaskEventData = new CBSLTaskEventData();
    CPPUNIT_ASSERT(pTaskEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pTaskEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProject == pTaskEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetTaskHandle());

    delete pTaskEventData;
}

void TaskEventDataTestCase::GetSetAppHandle()
{
    CBSLTaskEventData* pTaskEventData = new CBSLTaskEventData();
    CPPUNIT_ASSERT(pTaskEventData != NULL);

    BSLAPP hApp = (BSLAPP) 0x314156;
    pTaskEventData->SetAppHandle(hApp);
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetProjectHandle());
    CPPUNIT_ASSERT(hApp == pTaskEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetTaskHandle());

    delete pTaskEventData;
}

void TaskEventDataTestCase::GetSetTaskHandle()
{
    CBSLTaskEventData* pTaskEventData = new CBSLTaskEventData();
    CPPUNIT_ASSERT(pTaskEventData != NULL);

    BSLTASK hTask = (BSLTASK) 0x314156;
    pTaskEventData->SetTaskHandle(hTask);
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskEventData->GetAppHandle());
    CPPUNIT_ASSERT(hTask == pTaskEventData->GetTaskHandle());

    delete pTaskEventData;
}
