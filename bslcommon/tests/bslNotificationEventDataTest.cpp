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
#include "bslNotificationEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NotificationEventDataTestCase);

void NotificationEventDataTestCase::CreateDelete()
{
    CBSLNotificationEventData* pNotificationEventData = new CBSLNotificationEventData();
    CPPUNIT_ASSERT(pNotificationEventData != NULL);
    delete pNotificationEventData;
}

void NotificationEventDataTestCase::CopyConstructor()
{
    CBSLNotificationEventData* pNotificationEventData = new CBSLNotificationEventData();
    CPPUNIT_ASSERT(pNotificationEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pNotificationEventData->SetHostHandle(hHost);

    CBSLNotificationEventData* pNotificationEventData2 = new CBSLNotificationEventData(*pNotificationEventData);
    CPPUNIT_ASSERT(pNotificationEventData2 != NULL);

    CPPUNIT_ASSERT(pNotificationEventData->GetHostHandle() == pNotificationEventData2->GetHostHandle());

    delete pNotificationEventData;
    delete pNotificationEventData2;
}

void NotificationEventDataTestCase::GetSetHostHandle()
{
    CBSLNotificationEventData* pNotificationEventData = new CBSLNotificationEventData();
    CPPUNIT_ASSERT(pNotificationEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pNotificationEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pNotificationEventData->GetHostHandle());

    delete pNotificationEventData;
}

void NotificationEventDataTestCase::GetSetNotificationHandle()
{
    CBSLNotificationEventData* pNotificationEventData = new CBSLNotificationEventData();
    CPPUNIT_ASSERT(pNotificationEventData != NULL);

    BSLNOTIFICATION hNotification = (BSLNOTIFICATION) 0x314156;
    pNotificationEventData->SetNotificationHandle(hNotification);
    CPPUNIT_ASSERT(hNotification == pNotificationEventData->GetNotificationHandle());

    delete pNotificationEventData;
}

void NotificationEventDataTestCase::GetSetProjectHandle()
{
    CBSLNotificationEventData* pNotificationEventData = new CBSLNotificationEventData();
    CPPUNIT_ASSERT(pNotificationEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pNotificationEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(hProject == pNotificationEventData->GetProjectHandle());

    delete pNotificationEventData;
}
