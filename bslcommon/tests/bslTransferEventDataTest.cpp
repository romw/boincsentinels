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
#include "bslTransferEventDataTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TransferEventDataTestCase);

void TransferEventDataTestCase::CreateDelete()
{
    CBSLTransferEventData* pTransferEventData = new CBSLTransferEventData();
    CPPUNIT_ASSERT(pTransferEventData != NULL);
    delete pTransferEventData;
}

void TransferEventDataTestCase::CopyConstructor()
{
    CBSLTransferEventData* pTransferEventData = new CBSLTransferEventData();
    CPPUNIT_ASSERT(pTransferEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pTransferEventData->SetHostHandle(hHost);

    CBSLTransferEventData* pTransferEventData2 = new CBSLTransferEventData(*pTransferEventData);
    CPPUNIT_ASSERT(pTransferEventData2 != NULL);

    CPPUNIT_ASSERT(pTransferEventData->GetHostHandle() == pTransferEventData2->GetHostHandle());

    delete pTransferEventData;
    delete pTransferEventData2;
}

void TransferEventDataTestCase::GetSetHostHandle()
{
    CBSLTransferEventData* pTransferEventData = new CBSLTransferEventData();
    CPPUNIT_ASSERT(pTransferEventData != NULL);

    BSLHOST hHost = (BSLHOST) 0x314156;
    pTransferEventData->SetHostHandle(hHost);
    CPPUNIT_ASSERT(hHost == pTransferEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTransferEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTransferEventData->GetTransferHandle());

    delete pTransferEventData;
}

void TransferEventDataTestCase::GetSetProjectHandle()
{
    CBSLTransferEventData* pTransferEventData = new CBSLTransferEventData();
    CPPUNIT_ASSERT(pTransferEventData != NULL);

    BSLPROJECT hProject = (BSLPROJECT) 0x314156;
    pTransferEventData->SetProjectHandle(hProject);
    CPPUNIT_ASSERT(NULL == pTransferEventData->GetHostHandle());
    CPPUNIT_ASSERT(hProject == pTransferEventData->GetProjectHandle());
    CPPUNIT_ASSERT(NULL == pTransferEventData->GetTransferHandle());

    delete pTransferEventData;
}

void TransferEventDataTestCase::GetSetTransferHandle()
{
    CBSLTransferEventData* pTransferEventData = new CBSLTransferEventData();
    CPPUNIT_ASSERT(pTransferEventData != NULL);

    BSLTRANSFER hTransfer = (BSLTRANSFER) 0x314156;
    pTransferEventData->SetTransferHandle(hTransfer);
    CPPUNIT_ASSERT(NULL == pTransferEventData->GetHostHandle());
    CPPUNIT_ASSERT(NULL == pTransferEventData->GetProjectHandle());
    CPPUNIT_ASSERT(hTransfer == pTransferEventData->GetTransferHandle());

    delete pTransferEventData;
}
