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
#include "bslTaskTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TaskTestCase);

void TaskTestCase::CreateDelete()
{
    CBSLTask* pTask = new CBSLTask();
    CPPUNIT_ASSERT(pTask != NULL);
    delete pTask;
}

void TaskTestCase::Equality()
{
    CBSLTask* pTask = new CBSLTask();
    CBSLTask* pTask2 = new CBSLTask();
    CPPUNIT_ASSERT(*pTask == *pTask2);
    delete pTask;
    delete pTask2;
}

void TaskTestCase::Inequality()
{
    CBSLTask* pTask = new CBSLTask();
    CBSLTask* pTask2 = new CBSLTask();
    wxString strName = wxT("Test Task");
    pTask->SetName(strName);
    CPPUNIT_ASSERT(*pTask != *pTask2);
    delete pTask;
    delete pTask2;
}

void TaskTestCase::AssignmentOperator()
{
    CBSLTask* pTask = new CBSLTask();
    CBSLTask* pTask2 = new CBSLTask();
    wxString strName = wxT("Test Task");
    pTask->SetName(strName);
    *pTask2 = *pTask;
    CPPUNIT_ASSERT(pTask->GetName() == pTask2->GetName());
    delete pTask;
    delete pTask2;
}

void TaskTestCase::GetSetName()
{
    CBSLTask* pTask = new CBSLTask();
    wxString strName = wxT("Test Task");
    pTask->SetName(strName);
    CPPUNIT_ASSERT(strName == pTask->GetName());
    delete pTask;
}

void TaskTestCase::GetSetRuntimeBoundDisk()
{
    CBSLTask* pTask = new CBSLTask();
    wxUint64 ullBound = 31416;
    pTask->SetRuntimeBoundDisk(ullBound);
    CPPUNIT_ASSERT(ullBound == pTask->GetRuntimeBoundDisk());
    delete pTask;
}

void TaskTestCase::GetSetRuntimeBoundFLOPS()
{
    CBSLTask* pTask = new CBSLTask();
    wxUint64 ullBound = 31416;
    pTask->SetRuntimeBoundFLOPS(ullBound);
    CPPUNIT_ASSERT(ullBound == pTask->GetRuntimeBoundFLOPS());
    delete pTask;
}

void TaskTestCase::GetSetRuntimeBoundMemory()
{
    CBSLTask* pTask = new CBSLTask();
    wxUint64 ullBound = 31416;
    pTask->SetRuntimeBoundMemory(ullBound);
    CPPUNIT_ASSERT(ullBound == pTask->GetRuntimeBoundMemory());
    delete pTask;
}

void TaskTestCase::GetSetRuntimeEstimatedFLOPS()
{
    CBSLTask* pTask = new CBSLTask();
    wxUint64 ullEstimated = 31416;
    pTask->SetRuntimeEstimatedFLOPS(ullEstimated);
    CPPUNIT_ASSERT(ullEstimated == pTask->GetRuntimeEstimatedFLOPS());
    delete pTask;
}

