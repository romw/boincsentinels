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
#include "bslMessageEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MessageEventDataTestCase);

void MessageEventDataTestCase::CreateDelete()
{
    CBSLMessageEventData* pMessageEventData = new CBSLMessageEventData();
    CPPUNIT_ASSERT(pMessageEventData != NULL);
    delete pMessageEventData;
}

void MessageEventDataTestCase::CopyConstructor()
{
    CBSLMessageEventData* pMessageEventData = new CBSLMessageEventData();
    CPPUNIT_ASSERT(pMessageEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pMessageEventData->SetHostHandle(hHost);

    CBSLMessageEventData* pMessageEventData2 = new CBSLMessageEventData(*pMessageEventData);
    CPPUNIT_ASSERT(pMessageEventData2 != NULL);

    CPPUNIT_ASSERT(pMessageEventData->GetHostHandle() == pMessageEventData2->GetHostHandle());

    delete pMessageEventData;
    delete pMessageEventData2;
}

void MessageEventDataTestCase::GetSetHostHandle()
{
    CBSLMessageEventData* pMessageEventData = new CBSLMessageEventData();
    CPPUNIT_ASSERT(pMessageEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pMessageEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pMessageEventData->GetHostHandle());

    delete pMessageEventData;
}

void MessageEventDataTestCase::GetSetMessageHandle()
{
    CBSLMessageEventData* pMessageEventData = new CBSLMessageEventData();
    CPPUNIT_ASSERT(pMessageEventData != NULL);

    BSLMESSAGE hMessage = (BSLMESSAGE) 0x314156;
    pMessageEventData->SetMessageHandle(hMessage);
    CPPUNIT_ASSERT(hMessage == pMessageEventData->GetMessageHandle());

    delete pMessageEventData;
}

void MessageEventDataTestCase::GetSetProjectHandle()
{
    CBSLMessageEventData* pMessageEventData = new CBSLMessageEventData();
    CPPUNIT_ASSERT(pMessageEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pMessageEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(hProject == pMessageEventData->GetProjectHandle());

    delete pMessageEventData;
}
