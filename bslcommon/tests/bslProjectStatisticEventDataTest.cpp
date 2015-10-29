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
#include "bslProjectStatisticEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectStatisticEventDataTestCase);

void ProjectStatisticEventDataTestCase::CreateDelete()
{
    CBSLProjectStatisticEventData* pProjectStatisticEventData = new CBSLProjectStatisticEventData();
    CPPUNIT_ASSERT(pProjectStatisticEventData != NULL);
    delete pProjectStatisticEventData;
}

void ProjectStatisticEventDataTestCase::CopyConstructor()
{
    CBSLProjectStatisticEventData* pProjectStatisticEventData = new CBSLProjectStatisticEventData();
    CPPUNIT_ASSERT(pProjectStatisticEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pProjectStatisticEventData->SetHostHandle(hHost);

    CBSLProjectStatisticEventData* pProjectStatisticEventData2 = new CBSLProjectStatisticEventData(
        *pProjectStatisticEventData);
    CPPUNIT_ASSERT(pProjectStatisticEventData2 != NULL);

    CPPUNIT_ASSERT(pProjectStatisticEventData->GetHostHandle() == pProjectStatisticEventData2->GetHostHandle());

    delete pProjectStatisticEventData;
    delete pProjectStatisticEventData2;
}

void ProjectStatisticEventDataTestCase::GetSetHostHandle()
{
    CBSLProjectStatisticEventData* pProjectStatisticEventData = new CBSLProjectStatisticEventData();
    CPPUNIT_ASSERT(pProjectStatisticEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pProjectStatisticEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pProjectStatisticEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pProjectStatisticEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pProjectStatisticEventData->GetProjectStatisticHandle());

    delete pProjectStatisticEventData;
}

void ProjectStatisticEventDataTestCase::GetSetProjectHandle()
{
    CBSLProjectStatisticEventData* pProjectStatisticEventData = new CBSLProjectStatisticEventData();
    CPPUNIT_ASSERT(pProjectStatisticEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pProjectStatisticEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(NULL == pProjectStatisticEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProject == pProjectStatisticEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pProjectStatisticEventData->GetProjectStatisticHandle());

    delete pProjectStatisticEventData;
}

void ProjectStatisticEventDataTestCase::GetSetProjectLinkHandle()
{
    CBSLProjectStatisticEventData* pProjectStatisticEventData = new CBSLProjectStatisticEventData();
    CPPUNIT_ASSERT(pProjectStatisticEventData != NULL);

    BSLPROJECTSTATISTIC hProjectStatistic = (BSLPROJECTSTATISTIC) 0x314156;
    pProjectStatisticEventData->SetProjectStatisticHandle(hProjectStatistic);
    CPPUNIT_ASSERT(NULL == pProjectStatisticEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pProjectStatisticEventData->GetProjectHandle());
    CPPUNIT_ASSERT(hProjectStatistic == pProjectStatisticEventData->GetProjectStatisticHandle());

    delete pProjectStatisticEventData;
}
