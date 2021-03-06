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
#include "bslProjectStatisticTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectStatisticTestCase);

void ProjectStatisticTestCase::CreateDelete()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    CPPUNIT_ASSERT(pProjectStatistic != NULL);
    delete pProjectStatistic;
}

void ProjectStatisticTestCase::Equality()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    CBSLProjectStatistic* pProjectStatistic2 = new CBSLProjectStatistic();
    CPPUNIT_ASSERT(*pProjectStatistic == *pProjectStatistic2);
    delete pProjectStatistic;
    delete pProjectStatistic2;
}

void ProjectStatisticTestCase::Inequality()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    CBSLProjectStatistic* pProjectStatistic2 = new CBSLProjectStatistic();
    wxDouble dCredit = 3.1416;
    pProjectStatistic->SetCreditHostAverage(dCredit);
    CPPUNIT_ASSERT(*pProjectStatistic != *pProjectStatistic2);
    delete pProjectStatistic;
    delete pProjectStatistic2;
}

void ProjectStatisticTestCase::AssignmentOperator()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    CBSLProjectStatistic* pProjectStatistic2 = new CBSLProjectStatistic();
    wxDouble dCredit = 3.1416;
    pProjectStatistic->SetCreditHostAverage(dCredit);
    *pProjectStatistic2 = *pProjectStatistic;
    CPPUNIT_ASSERT(pProjectStatistic->GetCreditHostAverage() == pProjectStatistic2->GetCreditHostAverage());
    delete pProjectStatistic;
    delete pProjectStatistic2;
}

void ProjectStatisticTestCase::GetSetCreditHostAverage()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    wxDouble dCredit = 3.1416;
    pProjectStatistic->SetCreditHostAverage(dCredit);
    CPPUNIT_ASSERT(dCredit == pProjectStatistic->GetCreditHostAverage());
    delete pProjectStatistic;
}

void ProjectStatisticTestCase::GetSetCreditHostTotal()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    wxDouble dCredit = 3.1416;
    pProjectStatistic->SetCreditHostTotal(dCredit);
    CPPUNIT_ASSERT(dCredit == pProjectStatistic->GetCreditHostTotal());
    delete pProjectStatistic;
}

void ProjectStatisticTestCase::GetSetCreditUserAverage()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    wxDouble dCredit = 3.1416;
    pProjectStatistic->SetCreditUserAverage(dCredit);
    CPPUNIT_ASSERT(dCredit == pProjectStatistic->GetCreditUserAverage());
    delete pProjectStatistic;
}

void ProjectStatisticTestCase::GetSetCreditUserTotal()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    wxDouble dCredit = 3.1416;
    pProjectStatistic->SetCreditUserTotal(dCredit);
    CPPUNIT_ASSERT(dCredit == pProjectStatistic->GetCreditUserTotal());
    delete pProjectStatistic;
}

void ProjectStatisticTestCase::GetSetTimestamp()
{
    CBSLProjectStatistic* pProjectStatistic = new CBSLProjectStatistic();
    wxDateTime dtNow = wxDateTime::Now();
    pProjectStatistic->SetTimestamp(dtNow);
    CPPUNIT_ASSERT(dtNow == pProjectStatistic->GetTimestamp());
    delete pProjectStatistic;
}
