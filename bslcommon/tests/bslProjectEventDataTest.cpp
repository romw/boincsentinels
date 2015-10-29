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
#include "bslProjectEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectEventDataTestCase);

void ProjectEventDataTestCase::CreateDelete()
{
    CBSLProjectEventData* pProjectEventData = new CBSLProjectEventData();
    CPPUNIT_ASSERT(pProjectEventData != NULL);
    delete pProjectEventData;
}

void ProjectEventDataTestCase::CopyConstructor()
{
    CBSLProjectEventData* pProjectEventData = new CBSLProjectEventData();
    CPPUNIT_ASSERT(pProjectEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pProjectEventData->SetHostHandle(hHost);

    CBSLProjectEventData* pProjectEventData2 = new CBSLProjectEventData(*pProjectEventData);
    CPPUNIT_ASSERT(pProjectEventData2 != NULL);

    CPPUNIT_ASSERT(pProjectEventData->GetHostHandle() == pProjectEventData2->GetHostHandle());

    delete pProjectEventData;
    delete pProjectEventData2;
}

void ProjectEventDataTestCase::GetSetHostHandle()
{
    CBSLProjectEventData* pProjectEventData = new CBSLProjectEventData();
    CPPUNIT_ASSERT(pProjectEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pProjectEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pProjectEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pProjectEventData->GetProjectHandle());

    delete pProjectEventData;
}

void ProjectEventDataTestCase::GetSetProjectHandle()
{
    CBSLProjectEventData* pProjectEventData = new CBSLProjectEventData();
    CPPUNIT_ASSERT(pProjectEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pProjectEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(NULL == pProjectEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProject == pProjectEventData->GetProjectHandle());

    delete pProjectEventData;
}
