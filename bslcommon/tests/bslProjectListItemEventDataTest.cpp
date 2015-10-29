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
#include "bslProjectListItemEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectListItemEventDataTestCase);

void ProjectListItemEventDataTestCase::CreateDelete()
{
    CBSLProjectListItemEventData* pProjectListItemEventData = new CBSLProjectListItemEventData();
    CPPUNIT_ASSERT(pProjectListItemEventData != NULL);
    delete pProjectListItemEventData;
}

void ProjectListItemEventDataTestCase::CopyConstructor()
{
    CBSLProjectListItemEventData* pProjectListItemEventData = new CBSLProjectListItemEventData();
    CPPUNIT_ASSERT(pProjectListItemEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pProjectListItemEventData->SetHostHandle(hHost);

    CBSLProjectListItemEventData* pProjectListItemEventData2 = new CBSLProjectListItemEventData(*pProjectListItemEventData);
    CPPUNIT_ASSERT(pProjectListItemEventData2 != NULL);

    CPPUNIT_ASSERT(pProjectListItemEventData->GetHostHandle() == pProjectListItemEventData2->GetHostHandle());

    delete pProjectListItemEventData;
    delete pProjectListItemEventData2;
}

void ProjectListItemEventDataTestCase::GetSetHostHandle()
{
    CBSLProjectListItemEventData* pProjectListItemEventData = new CBSLProjectListItemEventData();
    CPPUNIT_ASSERT(pProjectListItemEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pProjectListItemEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pProjectListItemEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pProjectListItemEventData->GetProjectListItemHandle());

    delete pProjectListItemEventData;
}

void ProjectListItemEventDataTestCase::GetSetProjectListItemHandle()
{
    CBSLProjectListItemEventData* pProjectListItemEventData = new CBSLProjectListItemEventData();
    CPPUNIT_ASSERT(pProjectListItemEventData != NULL);

    BSLPROJECTLISTITEM hProjectListItem = (BSLPROJECTLISTITEM) 0x314156;
    pProjectListItemEventData->SetProjectListItemHandle(hProjectListItem);
    CPPUNIT_ASSERT(NULL == pProjectListItemEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProjectListItem == pProjectListItemEventData->GetProjectListItemHandle());

    delete pProjectListItemEventData;
}
