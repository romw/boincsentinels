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

#ifndef CPP_UNIT_CONNECTDISCONNECTTESTCASE_H
#define CPP_UNIT_CONNECTDISCONNECTTESTCASE_H

class ConnectDisconnectTestCase: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ConnectDisconnectTestCase);
    CPPUNIT_TEST(ConnectLocalSync);
    CPPUNIT_TEST(ConnectUknownDNSSync);
    CPPUNIT_TEST(ConnectUknownPortSync);
    CPPUNIT_TEST(ConnectLocalAsync);
    CPPUNIT_TEST(ConnectUknownDNSAsync);
    CPPUNIT_TEST_SUITE_END();

protected:
    void ConnectLocalSync();
    void ConnectUknownDNSSync();
    void ConnectUknownPortSync();
    void ConnectLocalAsync();
    void ConnectUknownDNSAsync();
};

#endif
