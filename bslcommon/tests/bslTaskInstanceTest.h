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

#ifndef CPP_UNIT_TASKINSTANCETESTCASE_H
#define CPP_UNIT_TASKINSTANCETESTCASE_H

class TaskInstanceTestCase: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TaskInstanceTestCase);
    CPPUNIT_TEST(CreateDelete);
    CPPUNIT_TEST(Equality);
    CPPUNIT_TEST(Inequality);
    CPPUNIT_TEST(AssignmentOperator);
    CPPUNIT_TEST(GetSetActiveTaskState);
    CPPUNIT_TEST(GetSetCheckpointCPUTime);
    CPPUNIT_TEST(GetSetCurrentCPUTime);
    CPPUNIT_TEST(GetSetElapsedTime);
    CPPUNIT_TEST(GetSetEstimatedElapsedTimeRemaining);
    CPPUNIT_TEST(GetSetExitStatus);
    CPPUNIT_TEST(GetSetFinalCPUTime);
    CPPUNIT_TEST(GetSetFinalElapsedTime);
    CPPUNIT_TEST(GetSetFractionDone);
    CPPUNIT_TEST(GetSetGraphicsApplication);
    CPPUNIT_TEST(GetSetName);
    CPPUNIT_TEST(GetSetPageFaultRate);
    CPPUNIT_TEST(GetSetProcessID);
    CPPUNIT_TEST(GetSetReceivedTime);
    CPPUNIT_TEST(GetSetReportDeadline);
    CPPUNIT_TEST(GetSetResourcesUtilized);
    CPPUNIT_TEST(GetSetSchedulerState);
    CPPUNIT_TEST(GetSetSlotDirectory);
    CPPUNIT_TEST(GetSetSlotID);
    CPPUNIT_TEST(GetSetSwapSize);
    CPPUNIT_TEST(GetSetTaskState);
    CPPUNIT_TEST(GetSetWorkingSetSize);
    CPPUNIT_TEST(GetSetWorkingSetSizeSmoothed);
    CPPUNIT_TEST(IsSetTaskActive);
    CPPUNIT_TEST(IsSetCoprocMissing);
    CPPUNIT_TEST(IsSetEDFScheduled);
    CPPUNIT_TEST(IsSetInterfaceSuspensionEnabled);
    CPPUNIT_TEST(IsSetReadyToReport);
    CPPUNIT_TEST(IsSetServerAcknowledged);
    CPPUNIT_TEST(IsSetSupportsGraphics);
    CPPUNIT_TEST(IsSetWaitingOnScheduler);
    CPPUNIT_TEST(IsSetWaitingOnMemory);
    CPPUNIT_TEST(IsSetWaitingOnSharedMemory);
    CPPUNIT_TEST_SUITE_END();

protected:
    void CreateDelete();
    void Equality();
    void Inequality();
    void AssignmentOperator();
    void GetSetActiveTaskState();
    void GetSetCheckpointCPUTime();
    void GetSetCurrentCPUTime();
    void GetSetElapsedTime();
    void GetSetEstimatedElapsedTimeRemaining();
    void GetSetExitStatus();
    void GetSetFinalCPUTime();
    void GetSetFinalElapsedTime();
    void GetSetFractionDone();
    void GetSetGraphicsApplication();
    void GetSetName();
    void GetSetPageFaultRate();
    void GetSetProcessID();
    void GetSetReceivedTime();
    void GetSetReportDeadline();
    void GetSetResourcesUtilized();
    void GetSetSchedulerState();
    void GetSetSlotDirectory();
    void GetSetSlotID();
    void GetSetSwapSize();
    void GetSetTaskState();
    void GetSetWorkingSetSize();
    void GetSetWorkingSetSizeSmoothed();
    void IsSetTaskActive();
    void IsSetCoprocMissing();
    void IsSetEDFScheduled();
    void IsSetInterfaceSuspensionEnabled();
    void IsSetReadyToReport();
    void IsSetServerAcknowledged();
    void IsSetSupportsGraphics();
    void IsSetWaitingOnScheduler();
    void IsSetWaitingOnMemory();
    void IsSetWaitingOnSharedMemory();
};

#endif
