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

#ifndef CPP_UNIT_PROJECTTESTCASE_H
#define CPP_UNIT_PROJECTTESTCASE_H

class ProjectTestCase: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ProjectTestCase);
    CPPUNIT_TEST(CreateDelete);
    CPPUNIT_TEST(Equality);
    CPPUNIT_TEST(Inequality);
    CPPUNIT_TEST(AssignmentOperator);
    CPPUNIT_TEST(GetSetATIBackoffInterval);
    CPPUNIT_TEST(GetSetATIBackoffTime);
    CPPUNIT_TEST(GetSetCPUBackoffInterval);
    CPPUNIT_TEST(GetSetCPUBackoffTime);
    CPPUNIT_TEST(GetSetCreditHostTotal);
    CPPUNIT_TEST(GetSetCreditHostAverage);
    CPPUNIT_TEST(GetSetCreditUserTotal);
    CPPUNIT_TEST(GetSetCreditUserAverage);
    CPPUNIT_TEST(GetSetCrossProjectID);
    CPPUNIT_TEST(GetSetCrossProjectIdTimestamp);
    CPPUNIT_TEST(GetSetDCF);
    CPPUNIT_TEST(GetSetHostID);
    CPPUNIT_TEST(GetSetMasterFetchFailureCount);
    CPPUNIT_TEST(GetSetMasterURL);
    CPPUNIT_TEST(GetSetNvidiaBackoffInterval);
    CPPUNIT_TEST(GetSetNvidiaBackoffTime);
    CPPUNIT_TEST(GetSetProjectName);
    CPPUNIT_TEST(GetSetResourceShare);
    CPPUNIT_TEST(GetSetSchedulerRPCFailureCount);
    CPPUNIT_TEST(GetSetSchedulerRPCPending);
    CPPUNIT_TEST(GetSetSchedulerRPCLastSuccess);
    CPPUNIT_TEST(GetSetSchedulerRPCMinimumTime);
    CPPUNIT_TEST(GetSetSchedulerRPCNextTime);
    CPPUNIT_TEST(GetSetTeamName);
    CPPUNIT_TEST(GetSetUserName);
    CPPUNIT_TEST(IsSetAccountManagementEnabled);
    CPPUNIT_TEST(IsSetAnonymousPlatformEnabled);
    CPPUNIT_TEST(IsSetATIUsageDisabled);
    CPPUNIT_TEST(IsSetCPUUsageDisabled);
    CPPUNIT_TEST(IsSetInterfaceSuspensionEnabled);
    CPPUNIT_TEST(IsSetMasterFetchInProgress);
    CPPUNIT_TEST(IsSetNonCPUIntensive);
    CPPUNIT_TEST(IsSetNvidiaUsageDisabled);
    CPPUNIT_TEST(IsSetSchedulerRPCInProgress);
    CPPUNIT_TEST(IsSetTaskAccumulationDisabled);
    CPPUNIT_TEST(IsSetTricklePending);
    CPPUNIT_TEST_SUITE_END();

protected:
    void CreateDelete();
    void Equality();
    void Inequality();
    void AssignmentOperator();
    void GetSetATIBackoffInterval();
    void GetSetATIBackoffTime();
    void GetSetCPUBackoffInterval();
    void GetSetCPUBackoffTime();
    void GetSetCreditHostTotal();
    void GetSetCreditHostAverage();
    void GetSetCreditUserTotal();
    void GetSetCreditUserAverage();
    void GetSetCrossProjectID();
    void GetSetCrossProjectIdTimestamp();
    void GetSetDCF();
    void GetSetHostID();
    void GetSetMasterFetchFailureCount();
    void GetSetMasterURL();
    void GetSetNvidiaBackoffInterval();
    void GetSetNvidiaBackoffTime();
    void GetSetProjectName();
    void GetSetResourceShare();
    void GetSetSchedulerRPCFailureCount();
    void GetSetSchedulerRPCPending();
    void GetSetSchedulerRPCLastSuccess();
    void GetSetSchedulerRPCMinimumTime();
    void GetSetSchedulerRPCNextTime();
    void GetSetTeamName();
    void GetSetUserName();
    void IsSetAccountManagementEnabled();
    void IsSetAnonymousPlatformEnabled();
    void IsSetATIUsageDisabled();
    void IsSetCPUUsageDisabled();
    void IsSetInterfaceSuspensionEnabled();
    void IsSetMasterFetchInProgress();
    void IsSetNonCPUIntensive();
    void IsSetNvidiaUsageDisabled();
    void IsSetSchedulerRPCInProgress();
    void IsSetTaskAccumulationDisabled();
    void IsSetTricklePending();
};

#endif
