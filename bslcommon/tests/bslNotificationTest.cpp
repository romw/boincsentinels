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
#include "bslNotificationTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NotificationTestCase);

void NotificationTestCase::CreateDelete()
{
    CBSLNotification* pNotification = new CBSLNotification();
    CPPUNIT_ASSERT(pNotification != NULL);
    delete pNotification;
}

void NotificationTestCase::Equality()
{
    CBSLNotification* pNotification = new CBSLNotification();
    CBSLNotification* pNotification2 = new CBSLNotification();
    CPPUNIT_ASSERT(*pNotification == *pNotification2);
    delete pNotification;
    delete pNotification2;
}

void NotificationTestCase::Inequality()
{
    CBSLNotification* pNotification = new CBSLNotification();
    CBSLNotification* pNotification2 = new CBSLNotification();
    pNotification->SetSequenceNumber(31416);
    CPPUNIT_ASSERT(*pNotification != *pNotification2);
    delete pNotification;
    delete pNotification2;
}

void NotificationTestCase::AssignmentOperator()
{
    CBSLNotification* pNotification = new CBSLNotification();
    CBSLNotification* pNotification2 = new CBSLNotification();
    pNotification->SetSequenceNumber(31416);
    *pNotification = *pNotification2;
    CPPUNIT_ASSERT(pNotification->GetSequenceNumber() == pNotification2->GetSequenceNumber());
    delete pNotification;
    delete pNotification2;
}

void NotificationTestCase::GetSetSequenceNumber()
{
    CBSLNotification* pNotification = new CBSLNotification();
    wxInt32 iSeqNo = 31416;
    pNotification->SetSequenceNumber(iSeqNo);
    CPPUNIT_ASSERT(iSeqNo == pNotification->GetSequenceNumber());
    delete pNotification;
}

void NotificationTestCase::GetSetCreateTime()
{
    CBSLNotification* pNotification = new CBSLNotification();
    wxDateTime dtNow = wxDateTime::Now();
    pNotification->SetCreateTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pNotification->GetCreateTime());
    delete pNotification;
}

void NotificationTestCase::GetSetArrivalTime()
{
    CBSLNotification* pNotification = new CBSLNotification();
    wxDateTime dtNow = wxDateTime::Now();
    pNotification->SetArrivalTime(dtNow);
    CPPUNIT_ASSERT(dtNow == pNotification->GetArrivalTime());
    delete pNotification;
}

void NotificationTestCase::GetSetPrivate()
{
    CBSLNotification* pNotification = new CBSLNotification();
    bool bPrivate = true;
    pNotification->SetPrivate(bPrivate);
    CPPUNIT_ASSERT(bPrivate == pNotification->IsPrivate());
    delete pNotification;
}

void NotificationTestCase::GetSetCategory()
{
    CBSLNotification* pNotification = new CBSLNotification();
    wxString strCategory = wxT("News");
    pNotification->SetCategory(strCategory);
    CPPUNIT_ASSERT(strCategory == pNotification->GetCategory());
    delete pNotification;
}

void NotificationTestCase::GetSetLink()
{
    CBSLNotification* pNotification = new CBSLNotification();
    wxString strLink = wxT("http://goofy.example.com/");
    pNotification->SetLink(strLink);
    CPPUNIT_ASSERT(strLink == pNotification->GetLink());
    delete pNotification;
}

void NotificationTestCase::GetSetTitle()
{
    CBSLNotification* pNotification = new CBSLNotification();
    wxString strTitle = wxT("Blah Blah Blah");
    pNotification->SetTitle(strTitle);
    CPPUNIT_ASSERT(strTitle == pNotification->GetTitle());
    delete pNotification;
}

void NotificationTestCase::GetSetNotificationText()
{
    CBSLNotification* pNotification = new CBSLNotification();
    wxString strNotificationText = wxT("Blah Blah Blah");
    pNotification->SetNotificationText(strNotificationText);
    CPPUNIT_ASSERT(strNotificationText == pNotification->GetNotificationText());
    delete pNotification;
}

void NotificationTestCase::ParseEx()
{
    CBSLNotification* pNotification = new CBSLNotification();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strNotification;

    wxString strSeqNo = wxT("1");
    wxString strTitle = wxT("Einstein@Home Discovers a Tenth Pulsar in Parkes Radio Data");
    wxString strNotificationText = wxT("I am delighted to announce that Einstein@Home has discovered a tenth new radio pulsar in data from the Parkes Multi Beam Pulsar Survey (PMPS)!");
    wxString strCreateTime = wxT("1315360924");
    wxDateTime dtCreateTime;
    dtCreateTime.Set((time_t)1315360924);
    wxString strArrivalTime = wxT("1317409367");
    wxDateTime dtArrivalTime;
    dtArrivalTime.Set((time_t)1317409367);
    wxString strIsPrivate = wxT("0");
    wxString strProjectName = wxT("Einstein@Home");
    wxString strCategory = wxT("");
    wxString strLink = wxT("http://einstein.phys.uwm.edu/forum_thread.php?id=9058");
    wxString strGUID = wxT("http://einstein.phys.uwm.edu/forum_thread.php?id=9058");
    wxString strFeedURL = wxT("http://einstein.phys.uwm.edu/forum_thread.php?id=9058");

    strNotification.Printf(
        wxT("<notice>\n")
        wxT("    <seqno>%s</seqno>\n")
        wxT("    <title>%s</title>\n")
        wxT("    <description>%s</description>\n")
        wxT("    <create_time>%s</create_time>\n")
        wxT("    <arrival_time>%s</arrival_time>\n")
        wxT("    <is_private>%s</is_private>\n")
        wxT("    <project_name>%s</project_name>\n")
        wxT("    <category>%s</category>\n")
        wxT("    <link>%s</link>\n")
        wxT("    <guid>%s</guid>\n")
        wxT("    <feed_url>%s</feed_url>\n")
        wxT("</notice>\n"),
        strSeqNo.c_str(),
        strTitle.c_str(),
        strNotificationText.c_str(),
        strCreateTime.c_str(),
        strArrivalTime.c_str(),
        strIsPrivate.c_str(),
        strProjectName.c_str(),
        strCategory.c_str(),
        strLink.c_str(),
        strGUID.c_str(),
        strFeedURL.c_str()
    );

    oDocument.SetDocument(strNotification);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_NOTIFICATION == oElement.GetNameHash())
        {
            pNotification->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be 1", 1, pNotification->GetSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetTitle().mb_str(), strTitle, pNotification->GetTitle());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetNotificationText().mb_str(), strNotificationText, pNotification->GetNotificationText());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetCreateTime().Format().mb_str(), dtCreateTime.Format(), pNotification->GetCreateTime().Format());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetArrivalTime().Format().mb_str(), dtArrivalTime.Format(), pNotification->GetArrivalTime().Format());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should not be private", false, pNotification->IsPrivate());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetProject().mb_str(), strProjectName, pNotification->GetProject());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetCategory().mb_str(), strCategory, pNotification->GetCategory());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetLink().mb_str(), strLink, pNotification->GetLink());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetGUID().mb_str(), strGUID, pNotification->GetGUID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetFeedURL().mb_str(), strFeedURL, pNotification->GetFeedURL());

    delete pNotification;
}

void NotificationTestCase::ParseCDATA()
{
    CBSLNotification* pNotification = new CBSLNotification();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strNotification;

    wxString strSeqNo = wxT("1");
    wxString strTitle = wxT("Einstein@Home Discovers a Tenth Pulsar in Parkes Radio Data");
    wxString strNotificationText = wxT("can be found on <a href=\"http://einstein.phys.uwm.edu/radiopulsar/html/PMPS_discoveries/\" rel=\"nofollow\">this web page</a>, and will be published in due course.");
    wxString strCreateTime = wxT("1315360924");
    wxDateTime dtCreateTime;
    dtCreateTime.Set((time_t)1315360924);
    wxString strArrivalTime = wxT("1317409367");
    wxDateTime dtArrivalTime;
    dtArrivalTime.Set((time_t)1317409367);
    wxString strIsPrivate = wxT("0");
    wxString strProjectName = wxT("Einstein@Home");
    wxString strCategory = wxT("");
    wxString strLink = wxT("http://einstein.phys.uwm.edu/forum_thread.php?id=9058");
    wxString strGUID = wxT("http://einstein.phys.uwm.edu/forum_thread.php?id=9058");
    wxString strFeedURL = wxT("http://einstein.phys.uwm.edu/forum_thread.php?id=9058");

    strNotification.Printf(
        wxT("<notice>\n")
        wxT("    <seqno>%s</seqno>\n")
        wxT("    <title>%s</title>\n")
        wxT("    <description><![CDATA[%s]]></description>\n")
        wxT("    <create_time>%s</create_time>\n")
        wxT("    <arrival_time>%s</arrival_time>\n")
        wxT("    <is_private>%s</is_private>\n")
        wxT("    <project_name>%s</project_name>\n")
        wxT("    <category>%s</category>\n")
        wxT("    <link>%s</link>\n")
        wxT("    <guid>%s</guid>\n")
        wxT("    <feed_url>%s</feed_url>\n")
        wxT("</notice>\n"),
        strSeqNo.c_str(),
        strTitle.c_str(),
        strNotificationText.c_str(),
        strCreateTime.c_str(),
        strArrivalTime.c_str(),
        strIsPrivate.c_str(),
        strProjectName.c_str(),
        strCategory.c_str(),
        strLink.c_str(),
        strGUID.c_str(),
        strFeedURL.c_str()
    );

    oDocument.SetDocument(strNotification);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_NOTIFICATION == oElement.GetNameHash())
        {
            pNotification->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should be 1", 1, pNotification->GetSequenceNumber());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetTitle().mb_str(), strTitle, pNotification->GetTitle());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetNotificationText().mb_str(), strNotificationText, pNotification->GetNotificationText());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetCreateTime().Format().mb_str(), dtCreateTime.Format(), pNotification->GetCreateTime().Format());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetArrivalTime().Format().mb_str(), dtArrivalTime.Format(), pNotification->GetArrivalTime().Format());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Should not be private", false, pNotification->IsPrivate());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetProject().mb_str(), strProjectName, pNotification->GetProject());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetCategory().mb_str(), strCategory, pNotification->GetCategory());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetLink().mb_str(), strLink, pNotification->GetLink());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetGUID().mb_str(), strGUID, pNotification->GetGUID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pNotification->GetFeedURL().mb_str(), strFeedURL, pNotification->GetFeedURL());

    delete pNotification;
}
