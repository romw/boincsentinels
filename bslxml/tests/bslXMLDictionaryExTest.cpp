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
#include "bslXMLDictionaryExTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(XMLDictionaryExTestCase);

void XMLDictionaryExTestCase::CreateDelete()
{
    CBSLXMLDictionaryEx* pXMLDictionaryEx = new CBSLXMLDictionaryEx();
    CPPUNIT_ASSERT(pXMLDictionaryEx != NULL);
    delete pXMLDictionaryEx;
}

void XMLDictionaryExTestCase::Parse()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");

    strDictionary.Printf(
        wxT("<host_info>\n")
        wxT("    <domain_name>%s</domain_name>\n")
        wxT("    <ip_addr>%s</ip_addr>\n")
        wxT("    <timezone>%d</timezone>\n")
        wxT("    <host_cpid>%s</host_cpid>\n")
        wxT("</host_info>\n"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strName == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("domain_name"))->GetValue(), oDictionary.FindElement(wxT("domain_name"))->GetValueLength()));
    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("ip_addr"))->GetValue(), oDictionary.FindElement(wxT("ip_addr"))->GetValueLength()));
    CPPUNIT_ASSERT(iTimezone == CBSLXMLConverterEx::ConvertToI32(oDictionary.FindElement(wxT("timezone"))->GetValue()));
    CPPUNIT_ASSERT(strCrossProjectId == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("host_cpid"))->GetValue(), oDictionary.FindElement(wxT("host_cpid"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDictionaryExTestCase::ParseNested()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");

    strDictionary.Printf(
        wxT("<nested1>\n")
        wxT("    <host_info>\n")
        wxT("        <domain_name>%s</domain_name>\n")
        wxT("        <ip_addr>%s</ip_addr>\n")
        wxT("        <timezone>%d</timezone>\n")
        wxT("        <host_cpid>%s</host_cpid>\n")
        wxT("    </host_info>\n")
        wxT("</nested1>\n"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strName == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("domain_name"))->GetValue(), oDictionary.FindElement(wxT("domain_name"))->GetValueLength()));
    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("ip_addr"))->GetValue(), oDictionary.FindElement(wxT("ip_addr"))->GetValueLength()));
    CPPUNIT_ASSERT(iTimezone == CBSLXMLConverterEx::ConvertToI32(oDictionary.FindElement(wxT("timezone"))->GetValue()));
    CPPUNIT_ASSERT(strCrossProjectId == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("host_cpid"))->GetValue(), oDictionary.FindElement(wxT("host_cpid"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDictionaryExTestCase::ParseDoubleNested()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");

    strDictionary.Printf(
        wxT("<nested1>\n")
        wxT("    <nested2>\n")
        wxT("        <host_info>\n")
        wxT("            <domain_name>%s</domain_name>\n")
        wxT("            <ip_addr>%s</ip_addr>\n")
        wxT("            <timezone>%d</timezone>\n")
        wxT("            <host_cpid>%s</host_cpid>\n")
        wxT("        </host_info>\n")
        wxT("    </nested2>\n")
        wxT("</nested1>\n"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strName == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("domain_name"))->GetValue(), oDictionary.FindElement(wxT("domain_name"))->GetValueLength()));
    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("ip_addr"))->GetValue(), oDictionary.FindElement(wxT("ip_addr"))->GetValueLength()));
    CPPUNIT_ASSERT(iTimezone == CBSLXMLConverterEx::ConvertToI32(oDictionary.FindElement(wxT("timezone"))->GetValue()));
    CPPUNIT_ASSERT(strCrossProjectId == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("host_cpid"))->GetValue(), oDictionary.FindElement(wxT("host_cpid"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDictionaryExTestCase::ParseAttribute1()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");

    strDictionary.Printf(
        wxT("<host_info domain_name='%s'>\n")
        wxT("    <ip_addr>%s</ip_addr>\n")
        wxT("    <timezone>%d</timezone>\n")
        wxT("    <host_cpid>%s</host_cpid>\n")
        wxT("</host_info>\n"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strName == CBSLXMLConverterEx::ConvertToString(
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValue(),
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValueLength()
        ));
    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("ip_addr"))->GetValue(), oDictionary.FindElement(wxT("ip_addr"))->GetValueLength()));
    CPPUNIT_ASSERT(iTimezone == CBSLXMLConverterEx::ConvertToI32(oDictionary.FindElement(wxT("timezone"))->GetValue()));
    CPPUNIT_ASSERT(strCrossProjectId == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("host_cpid"))->GetValue(), oDictionary.FindElement(wxT("host_cpid"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDictionaryExTestCase::ParseAttribute2()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");

    strDictionary.Printf(
        wxT("<host_info domain_name='%s' ip_addr='%s'>\n")
        wxT("    <timezone>%d</timezone>\n")
        wxT("    <host_cpid>%s</host_cpid>\n")
        wxT("</host_info>\n"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strName == CBSLXMLConverterEx::ConvertToString(
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValue(),
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValueLength()
        ));
    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("ip_addr"))->GetValue(),
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("ip_addr"))->GetValueLength()
        ));
    CPPUNIT_ASSERT(iTimezone == CBSLXMLConverterEx::ConvertToI32(oDictionary.FindElement(wxT("timezone"))->GetValue()));
    CPPUNIT_ASSERT(strCrossProjectId == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("host_cpid"))->GetValue(), oDictionary.FindElement(wxT("host_cpid"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDictionaryExTestCase::ParseXMLComment()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");

    strDictionary.Printf(
        wxT("<host_info domain_name='%s' ip_addr='%s'>\n")
        wxT("    <!-- This is a comment -->\n")
        wxT("    <timezone>%d</timezone>\n")
        wxT("    <!-- This is a comment -->\n")
        wxT("    <host_cpid>%s</host_cpid>\n")
        wxT("</host_info>\n"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strName == CBSLXMLConverterEx::ConvertToString(
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValue(),
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValueLength()
        ));
    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("ip_addr"))->GetValue(),
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("ip_addr"))->GetValueLength()
        ));
    CPPUNIT_ASSERT(iTimezone == CBSLXMLConverterEx::ConvertToI32(oDictionary.FindElement(wxT("timezone"))->GetValue()));
    CPPUNIT_ASSERT(strCrossProjectId == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("host_cpid"))->GetValue(), oDictionary.FindElement(wxT("host_cpid"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDictionaryExTestCase::ParseWithoutLF()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");

    strDictionary.Printf(
        wxT("<host_info domain_name='%s' ip_addr='%s'>")
        wxT("    <!-- This is a comment -->")
        wxT("    <timezone>%d</timezone>")
        wxT("    <!-- This is a comment -->")
        wxT("    <host_cpid>%s</host_cpid>")
        wxT("</host_info>"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strName == CBSLXMLConverterEx::ConvertToString(
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValue(),
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("domain_name"))->GetValueLength()
        ));
    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("ip_addr"))->GetValue(),
        (oDictionary.FindElement(wxT("host_info")))->FindAttribute(wxT("ip_addr"))->GetValueLength()
        ));
    CPPUNIT_ASSERT(iTimezone == CBSLXMLConverterEx::ConvertToI32(oDictionary.FindElement(wxT("timezone"))->GetValue()));
    CPPUNIT_ASSERT(strCrossProjectId == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("host_cpid"))->GetValue(), oDictionary.FindElement(wxT("host_cpid"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLDictionaryExTestCase::ParseEmptyNode()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;

    wxString strDictionary;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");

    strDictionary.Printf(
        wxT("<host_info>\n")
        wxT("    <domain_name></domain_name>\n")
        wxT("    <ip_addr>%s</ip_addr>\n")
        wxT("</host_info>\n"),
        strIPAddr.c_str()
    );

    oDocument.SetDocument(strDictionary);
    rc = oDictionary.Parse(oDocument, 0);

    CPPUNIT_ASSERT(strIPAddr == CBSLXMLConverterEx::ConvertToString(oDictionary.FindElement(wxT("ip_addr"))->GetValue(), oDictionary.FindElement(wxT("ip_addr"))->GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}
