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
#include "bslTaskInstanceEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TaskInstanceEventDataTestCase);

void TaskInstanceEventDataTestCase::CreateDelete()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);
    delete pTaskInstanceEventData;
}

void TaskInstanceEventDataTestCase::CopyConstructor()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pTaskInstanceEventData->SetHostHandle(hHost);

    CBSLTaskInstanceEventData* pTaskInstanceEventData2 = new CBSLTaskInstanceEventData(*pTaskInstanceEventData);
    CPPUNIT_ASSERT(pTaskInstanceEventData2 != NULL);

    CPPUNIT_ASSERT(pTaskInstanceEventData->GetHostHandle() == pTaskInstanceEventData2->GetHostHandle());

    delete pTaskInstanceEventData;
    delete pTaskInstanceEventData2;
}

void TaskInstanceEventDataTestCase::GetSetHostHandle()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pTaskInstanceEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pTaskInstanceEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppVersionHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskInstanceHandle());

    delete pTaskInstanceEventData;
}

void TaskInstanceEventDataTestCase::GetSetProjectHandle()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pTaskInstanceEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProject == pTaskInstanceEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppVersionHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskInstanceHandle());

    delete pTaskInstanceEventData;
}

void TaskInstanceEventDataTestCase::GetSetAppHandle()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);

    BSLAPP hApp = (BSLAPP) 0x314156;
    pTaskInstanceEventData->SetAppHandle(hApp);
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetProjectHandle());
    CPPUNIT_ASSERT(hApp == pTaskInstanceEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppVersionHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskInstanceHandle());

    delete pTaskInstanceEventData;
}

void TaskInstanceEventDataTestCase::GetSetAppVersionHandle()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);

    BSLAPPVERSION hAppVersion = (BSLAPPVERSION) 0x314156;
    pTaskInstanceEventData->SetAppVersionHandle(hAppVersion);
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppHandle());
    CPPUNIT_ASSERT(hAppVersion == pTaskInstanceEventData->GetAppVersionHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskInstanceHandle());

    delete pTaskInstanceEventData;
}

void TaskInstanceEventDataTestCase::GetSetTaskHandle()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);

    BSLTASK hTask = (BSLTASK) 0x314156;
    pTaskInstanceEventData->SetTaskHandle(hTask);
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppVersionHandle());
    CPPUNIT_ASSERT(hTask == pTaskInstanceEventData->GetTaskHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskInstanceHandle());

    delete pTaskInstanceEventData;
}

void TaskInstanceEventDataTestCase::GetSetTaskInstanceHandle()
{
    CBSLTaskInstanceEventData* pTaskInstanceEventData = new CBSLTaskInstanceEventData();
    CPPUNIT_ASSERT(pTaskInstanceEventData != NULL);

    BSLTASKINSTANCE hTaskInstance = (BSLTASKINSTANCE) 0x314156;
    pTaskInstanceEventData->SetTaskInstanceHandle(hTaskInstance);
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetAppVersionHandle());
    CPPUNIT_ASSERT(NULL == pTaskInstanceEventData->GetTaskHandle());
    CPPUNIT_ASSERT(hTaskInstance == pTaskInstanceEventData->GetTaskInstanceHandle());

    delete pTaskInstanceEventData;
}
