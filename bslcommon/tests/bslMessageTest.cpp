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
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslMessageTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MessageTestCase);

void MessageTestCase::CreateDelete()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CPPUNIT_ASSERT(pMessage != NULL);
    delete pMessage;
}

void MessageTestCase::Equality()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLMessage* pMessage2 = new CBSLMessage();
    CPPUNIT_ASSERT(*pMessage == *pMessage2);
    delete pMessage;
    delete pMessage2;
}

void MessageTestCase::Inequality()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLMessage* pMessage2 = new CBSLMessage();
    pMessage->SetSequenceNumber(31416);
    CPPUNIT_ASSERT(*pMessage != *pMessage2);
    delete pMessage;
    delete pMessage2;
}

void MessageTestCase::AssignmentOperator()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLMessage* pMessage2 = new CBSLMessage();
    pMessage->SetSequenceNumber(31416);
    *pMessage = *pMessage2;
    CPPUNIT_ASSERT(pMessage->GetSequenceNumber() == pMessage2->GetSequenceNumber());
    delete pMessage;
    delete pMessage2;
}

void MessageTestCase::GetSetSequenceNumber()
{
    CBSLMessage* pMessage = new CBSLMessage();
    wxInt32 iSeqNo = 31416;
    pMessage->SetSequenceNumber(iSeqNo);
    CPPUNIT_ASSERT(iSeqNo == pMessage->GetSequenceNumber());
    delete pMessage;
}

void MessageTestCase::GetSetPriority()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLMessage::PRIORITY iPriority = CBSLMessage::PriorityInternalError;
    pMessage->SetPriority(iPriority);
    CPPUNIT_ASSERT(iPriority == pMessage->GetPriority());
    delete pMessage;
}

void MessageTestCase::GetSetTimestamp()
{
    CBSLMessage* pMessage = new CBSLMessage();
    wxDateTime dtNow = wxDateTime::Now();
    pMessage->SetTimestamp(dtNow);
    CPPUNIT_ASSERT(dtNow == pMessage->GetTimestamp());
    delete pMessage;
}

void MessageTestCase::GetSetMessageText()
{
    CBSLMessage* pMessage = new CBSLMessage();
    wxString strMessage = wxT("Blah Blah Blah");
    pMessage->SetMessageText(strMessage);
    CPPUNIT_ASSERT(strMessage == pMessage->GetMessageText());
    delete pMessage;
}

void MessageTestCase::ParseEx()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strMessage;

    wxString strSeqNo = wxT("1");
    wxString strProject = wxT("blah");
    wxString strMessageText = wxT("blah2");
    wxString strPriority = wxT("0");
    wxString strTimestamp = wxT("1315360924");
    wxDateTime dtTimestamp;
    dtTimestamp.Set((time_t)1315360924);

    strMessage.Printf(
        wxT("<msg>\n")
        wxT("    <seqno>%s</seqno>\n")
        wxT("    <project>%s</project>\n")
        wxT("    <body>%s</body>\n")
        wxT("    <pri>%s</pri>\n")
        wxT("    <time>%s</time>\n")
        wxT("</msg>\n"),
        strSeqNo.c_str(),
        strProject.c_str(),
        strMessageText.c_str(),
        strPriority.c_str(),
        strTimestamp.c_str()
    );

    oDocument.SetDocument(strMessage);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_MESSAGE == oElement.GetNameHash())
        {
            pMessage->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be 1", 1, pMessage->GetSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be CBSLMessage::PriorityUnknown", CBSLMessage::PriorityUnknown, pMessage->GetPriority());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetProject().mb_str(), strProject, pMessage->GetProject());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetMessageText().mb_str(), strMessageText, pMessage->GetMessageText());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetTimestamp().Format().mb_str(), dtTimestamp.Format(), pMessage->GetTimestamp().Format());

    delete pMessage;
}

void MessageTestCase::ParsePriInfo()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strMessage;

    wxString strSeqNo = wxT("1");
    wxString strProject = wxT("blah");
    wxString strMessageText = wxT("blah2");
    wxString strPriority = wxT("1");
    wxString strTimestamp = wxT("1315360924");
    wxDateTime dtTimestamp;
    dtTimestamp.Set((time_t)1315360924);

    strMessage.Printf(
        wxT("<msg>\n")
        wxT("    <seqno>%s</seqno>\n")
        wxT("    <project>%s</project>\n")
        wxT("    <body>%s</body>\n")
        wxT("    <pri>%s</pri>\n")
        wxT("    <time>%s</time>\n")
        wxT("</msg>\n"),
        strSeqNo.c_str(),
        strProject.c_str(),
        strMessageText.c_str(),
        strPriority.c_str(),
        strTimestamp.c_str()
    );

    oDocument.SetDocument(strMessage);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_MESSAGE == oElement.GetNameHash())
        {
            pMessage->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be 1", 1, pMessage->GetSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be CBSLMessage::PriorityInfo", CBSLMessage::PriorityInfo, pMessage->GetPriority());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetProject().mb_str(), strProject, pMessage->GetProject());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetMessageText().mb_str(), strMessageText, pMessage->GetMessageText());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetTimestamp().Format().mb_str(), dtTimestamp.Format(), pMessage->GetTimestamp().Format());

    delete pMessage;
}

void MessageTestCase::ParsePriUserAlert()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strMessage;

    wxString strSeqNo = wxT("1");
    wxString strProject = wxT("blah");
    wxString strMessageText = wxT("blah2");
    wxString strPriority = wxT("2");
    wxString strTimestamp = wxT("1315360924");
    wxDateTime dtTimestamp;
    dtTimestamp.Set((time_t)1315360924);

    strMessage.Printf(
        wxT("<msg>\n")
        wxT("    <seqno>%s</seqno>\n")
        wxT("    <project>%s</project>\n")
        wxT("    <body>%s</body>\n")
        wxT("    <pri>%s</pri>\n")
        wxT("    <time>%s</time>\n")
        wxT("</msg>\n"),
        strSeqNo.c_str(),
        strProject.c_str(),
        strMessageText.c_str(),
        strPriority.c_str(),
        strTimestamp.c_str()
    );

    oDocument.SetDocument(strMessage);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_MESSAGE == oElement.GetNameHash())
        {
            pMessage->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be 1", 1, pMessage->GetSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be CBSLMessage::PriorityUserAlert", CBSLMessage::PriorityUserAlert, pMessage->GetPriority());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetProject().mb_str(), strProject, pMessage->GetProject());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetMessageText().mb_str(), strMessageText, pMessage->GetMessageText());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetTimestamp().Format().mb_str(), dtTimestamp.Format(), pMessage->GetTimestamp().Format());

    delete pMessage;
}

void MessageTestCase::ParsePriInternalError()
{
    CBSLMessage* pMessage = new CBSLMessage();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strMessage;

    wxString strSeqNo = wxT("1");
    wxString strProject = wxT("blah");
    wxString strMessageText = wxT("blah2");
    wxString strPriority = wxT("3");
    wxString strTimestamp = wxT("1315360924");
    wxDateTime dtTimestamp;
    dtTimestamp.Set((time_t)1315360924);

    strMessage.Printf(
        wxT("<msg>\n")
        wxT("    <seqno>%s</seqno>\n")
        wxT("    <project>%s</project>\n")
        wxT("    <body>%s</body>\n")
        wxT("    <pri>%s</pri>\n")
        wxT("    <time>%s</time>\n")
        wxT("</msg>\n"),
        strSeqNo.c_str(),
        strProject.c_str(),
        strMessageText.c_str(),
        strPriority.c_str(),
        strTimestamp.c_str()
    );

    oDocument.SetDocument(strMessage);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_MESSAGE == oElement.GetNameHash())
        {
            pMessage->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be 1", 1, pMessage->GetSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be CBSLMessage::PriorityInternalError", CBSLMessage::PriorityInternalError, pMessage->GetPriority());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetProject().mb_str(), strProject, pMessage->GetProject());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetMessageText().mb_str(), strMessageText, pMessage->GetMessageText());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pMessage->GetTimestamp().Format().mb_str(), dtTimestamp.Format(), pMessage->GetTimestamp().Format());

    delete pMessage;
}
