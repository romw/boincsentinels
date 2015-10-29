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

#ifndef CPP_UNIT_HOSTTESTCASE_H
#define CPP_UNIT_HOSTTESTCASE_H

class HostTestCase: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(HostTestCase);
    CPPUNIT_TEST(CreateDelete);
    CPPUNIT_TEST(Equality);
    CPPUNIT_TEST(Inequality);
    CPPUNIT_TEST(AssignmentOperator);
    CPPUNIT_TEST(GetSetConnectionState);
    CPPUNIT_TEST(GetSetName);
    CPPUNIT_TEST(GetSetCrossProjectID);
    CPPUNIT_TEST(GetSetIPAddress);
    CPPUNIT_TEST(GetSetTimezone);
    CPPUNIT_TEST(GetSetLastProcessorBenchmark);
    CPPUNIT_TEST(GetSetOSName);
    CPPUNIT_TEST(GetSetOSVersion);
    CPPUNIT_TEST(GetSetProcessorCount);
    CPPUNIT_TEST(GetSetProcessorVendor);
    CPPUNIT_TEST(GetSetProcessorModel);
    CPPUNIT_TEST(GetSetProcessorFeatures);
    CPPUNIT_TEST(GetSetProcessorCache);
    CPPUNIT_TEST(GetSetProcessorFLOPS);
    CPPUNIT_TEST(GetSetProcessorIOPS);
    CPPUNIT_TEST(GetSetProcessorMemoryBandwidth);
    CPPUNIT_TEST(GetSetMemoryTotal);
    CPPUNIT_TEST(GetSetMemorySwap);
    CPPUNIT_TEST(GetSetDiskTotal);
    CPPUNIT_TEST(GetSetDiskFree);
    CPPUNIT_TEST(ParseEx);
    CPPUNIT_TEST_SUITE_END();

protected:
    void CreateDelete();
    void Equality();
    void Inequality();
    void AssignmentOperator();
    void GetSetConnectionState();
    void GetSetName();
    void GetSetCrossProjectID();
    void GetSetIPAddress();
    void GetSetTimezone();
    void GetSetLastProcessorBenchmark();
    void GetSetOSName();
    void GetSetOSVersion();
    void GetSetProcessorCount();
    void GetSetProcessorVendor();
    void GetSetProcessorModel();
    void GetSetProcessorFeatures();
    void GetSetProcessorCache();
    void GetSetProcessorFLOPS();
    void GetSetProcessorIOPS();
    void GetSetProcessorMemoryBandwidth();
    void GetSetMemoryTotal();
    void GetSetMemorySwap();
    void GetSetDiskTotal();
    void GetSetDiskFree();
    void ParseEx();
};

#endif
