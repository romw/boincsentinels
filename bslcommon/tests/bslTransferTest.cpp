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
#include "bslTransferTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TransferTestCase);

void TransferTestCase::CreateDelete()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    CPPUNIT_ASSERT(pTransfer != NULL);
    delete pTransfer;
}

void TransferTestCase::Equality()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    CBSLTransfer* pTransfer2 = new CBSLTransfer();
    CPPUNIT_ASSERT(*pTransfer == *pTransfer2);
    delete pTransfer;
    delete pTransfer2;
}

void TransferTestCase::Inequality()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    CBSLTransfer* pTransfer2 = new CBSLTransfer();
    wxString strName = wxT("blah_blah_blah");
    pTransfer->SetName(strName);
    CPPUNIT_ASSERT(*pTransfer != *pTransfer2);
    delete pTransfer;
    delete pTransfer2;
}

void TransferTestCase::AssignmentOperator()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    CBSLTransfer* pTransfer2 = new CBSLTransfer();
    wxString strName = wxT("blah_blah_blah");
    pTransfer->SetName(strName);
    *pTransfer2 = *pTransfer;
    CPPUNIT_ASSERT(pTransfer->GetName() == pTransfer2->GetName());
    delete pTransfer;
    delete pTransfer2;
}

void TransferTestCase::GetSetBytes()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxUint64 ullBytes = 31416;
    pTransfer->SetBytes(ullBytes);
    CPPUNIT_ASSERT(ullBytes == pTransfer->GetBytes());
    delete pTransfer;
}

void TransferTestCase::GetSetBytesTransfered()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxUint64 ullBytesTransfered = 31416;
    pTransfer->SetBytesTransfered(ullBytesTransfered);
    CPPUNIT_ASSERT(ullBytesTransfered == pTransfer->GetBytesTransfered());
    delete pTransfer;
}

void TransferTestCase::GetSetBytesUploaded()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxUint64 ullBytesUploaded = 31416;
    pTransfer->SetBytesUploaded(ullBytesUploaded);
    CPPUNIT_ASSERT(ullBytesUploaded == pTransfer->GetBytesUploaded());
    delete pTransfer;
}

void TransferTestCase::GetSetElapsedTime()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxTimeSpan tsElapsedTime = 31416;
    pTransfer->SetElapsedTime(tsElapsedTime);
    CPPUNIT_ASSERT(tsElapsedTime == pTransfer->GetElapsedTime());
    delete pTransfer;
}

void TransferTestCase::GetSetFirstRequestTime()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxDateTime dtNow = wxDateTime::Now();
    pTransfer->SetFirstRequestTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pTransfer->GetFirstRequestTime());
    delete pTransfer;
}

void TransferTestCase::GetSetName()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxString strName = wxT("blah_blah_blah");
    pTransfer->SetName(strName);
    CPPUNIT_ASSERT(strName == pTransfer->GetName());
    delete pTransfer;
}

void TransferTestCase::GetSetNextRequestTime()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxDateTime dtNow = wxDateTime::Now();
    pTransfer->SetNextRequestTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pTransfer->GetNextRequestTime());
    delete pTransfer;
}

void TransferTestCase::GetSetProjectBackoff()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxTimeSpan tsProjectBackoff = 31416;
    pTransfer->SetProjectBackoff(tsProjectBackoff);
    CPPUNIT_ASSERT(tsProjectBackoff == pTransfer->GetProjectBackoff());
    delete pTransfer;
}

void TransferTestCase::GetSetRetryCount()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxUint32 uiRetryCount = 31416;
    pTransfer->SetRetryCount(uiRetryCount);
    CPPUNIT_ASSERT(uiRetryCount == pTransfer->GetRetryCount());
    delete pTransfer;
}

void TransferTestCase::GetSetTransferRate()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    wxUint64 ullTransferRate = 31416;
    pTransfer->SetTransferRate(ullTransferRate);
    CPPUNIT_ASSERT(ullTransferRate == pTransfer->GetTransferRate());
    delete pTransfer;
}

void TransferTestCase::IsSetPersistantTransferActive()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    bool bPersistantTransferActive = true;
    pTransfer->SetPersistantTransferActive(bPersistantTransferActive);
    CPPUNIT_ASSERT(bPersistantTransferActive == pTransfer->IsPersistantTransferActive());
    delete pTransfer;
}

void TransferTestCase::IsSetSticky()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    bool bSticky = true;
    pTransfer->SetSticky(bSticky);
    CPPUNIT_ASSERT(bSticky == pTransfer->IsSticky());
    delete pTransfer;
}

void TransferTestCase::IsSetTransferActive()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    bool bTransferActive = true;
    pTransfer->SetTransferActive(bTransferActive);
    CPPUNIT_ASSERT(bTransferActive == pTransfer->IsTransferActive());
    delete pTransfer;
}

void TransferTestCase::IsSetUpload()
{
    CBSLTransfer* pTransfer = new CBSLTransfer();
    bool bUpload = true;
    pTransfer->SetUpload(bUpload);
    CPPUNIT_ASSERT(bUpload == pTransfer->IsUpload());
    delete pTransfer;
}
