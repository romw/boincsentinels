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
#include "bslclient/bslClient.h"
#include "EnumerateNotificationsTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(EnumerateNotificationsTestCase);

void EnumerateNotificationsTestCase::NullHandle()
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CBSLClient* pClient = new CBSLClient();
    BSLHOST hHost = NULL;
    std::vector<BSLNOTIFICATION> oNotifications;

    pClient->OnInit();
    rc = pClient->EnumerateNotifications(hHost, 0, oNotifications);
    pClient->OnExit();

    delete pClient;

    CPPUNIT_ASSERT(pClient != NULL);
    CPPUNIT_ASSERT(BSLERR_HOST_NOT_FOUND == rc);
}

void EnumerateNotificationsTestCase::InvalidHandle()
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CBSLClient* pClient = new CBSLClient();
    BSLHOST hHost = (BSLHOST) 0x31416;
    std::vector<BSLNOTIFICATION> oNotifications;

    pClient->OnInit();
    rc = pClient->EnumerateNotifications(hHost, 0, oNotifications);
    pClient->OnExit();

    delete pClient;

    CPPUNIT_ASSERT(pClient != NULL);
    CPPUNIT_ASSERT(BSLERR_HOST_NOT_FOUND == rc);
}

void EnumerateNotificationsTestCase::EmptyDataSet()
{
    BSLERRCODE rcConnect = BSLERR_FAILURE;
    BSLERRCODE rcDisconnect = BSLERR_FAILURE;
    BSLERRCODE rcEnumerate = BSLERR_FAILURE;
    CBSLClient* pClient = new CBSLClient();
    std::vector<BSLNOTIFICATION> oNotifications;
    BSLHOST hHost = NULL;
    long lPort;

    pClient->OnInit();
    pClient->GetLocalHostPort(lPort);
    rcConnect = pClient->Connect(wxT("blah.example.com"), wxT("blah.example.password"), lPort, false, &hHost);
    rcEnumerate = pClient->EnumerateNotifications(hHost, 0, oNotifications, false);
    rcDisconnect = pClient->Disconnect(hHost);
    pClient->OnExit();

    delete pClient;

    CPPUNIT_ASSERT(pClient != NULL);
    CPPUNIT_ASSERT(hHost != NULL);
    CPPUNIT_ASSERT(BSLERR_SUCCESS == rcConnect);
    CPPUNIT_ASSERT(BSLERR_SUCCESS == rcEnumerate);
    CPPUNIT_ASSERT(BSLERR_SUCCESS == rcDisconnect);
    CPPUNIT_ASSERT(0 == oNotifications.size());
}
