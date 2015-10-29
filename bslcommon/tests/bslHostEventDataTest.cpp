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
#include "bslHostEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(HostEventDataTestCase);

void HostEventDataTestCase::CreateDelete()
{
    CBSLHostEventData* pHostEventData = new CBSLHostEventData();
    CPPUNIT_ASSERT(pHostEventData != NULL);
    delete pHostEventData;
}

void HostEventDataTestCase::CopyConstructor()
{
    CBSLHostEventData* pHostEventData = new CBSLHostEventData();
    CPPUNIT_ASSERT(pHostEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pHostEventData->SetHostHandle(hHost);

    CBSLHostEventData* pHostEventData2 = new CBSLHostEventData(*pHostEventData);
    CPPUNIT_ASSERT(pHostEventData2 != NULL);

    CPPUNIT_ASSERT(pHostEventData->GetHostHandle() == pHostEventData2->GetHostHandle());

    delete pHostEventData;
    delete pHostEventData2;
}

void HostEventDataTestCase::GetSetHostHandle()
{
    CBSLHostEventData* pHostEventData = new CBSLHostEventData();
    CPPUNIT_ASSERT(pHostEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pHostEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pHostEventData->GetHostHandle());

    delete pHostEventData;
}
