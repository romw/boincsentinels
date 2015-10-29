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
#include "bslXMLElementExTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(XMLElementExTestCase);

void XMLElementExTestCase::CreateDelete()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    CPPUNIT_ASSERT(pElement != NULL);
    delete pElement;
}

void XMLElementExTestCase::GetSetName()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    wxString strName = wxT("TestName");
    pElement->SetName(strName.wx_str());
    CPPUNIT_ASSERT(strName == pElement->GetName());
    delete pElement;
}

void XMLElementExTestCase::GetSetValue()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    wxString strValue = wxT("TestValue");
    pElement->SetValue(strValue.wx_str());
    CPPUNIT_ASSERT(strValue == pElement->GetValue());
    delete pElement;
}

void XMLElementExTestCase::GetSetBoolValueTrue()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("1"));
    CPPUNIT_ASSERT(true == CBSLXMLConverterEx::ConvertToBool(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetBoolValueFalse()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("0"));
    CPPUNIT_ASSERT(false == CBSLXMLConverterEx::ConvertToBool(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetStringValue()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    wxString strValue = wxT("TestValue");
    pElement->SetValue(strValue.wx_str());
    CPPUNIT_ASSERT(strValue == CBSLXMLConverterEx::ConvertToString(pElement->GetValue(), pElement->GetValueLength()));
    delete pElement;
}

void XMLElementExTestCase::GetSetDoubleValue()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("3.14159"));
    CPPUNIT_ASSERT((wxDouble)3.14159 == CBSLXMLConverterEx::ConvertToDouble(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetDoubleValueOne()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("1.0"));
    CPPUNIT_ASSERT((wxDouble)1.0 == CBSLXMLConverterEx::ConvertToDouble(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetDoubleValueZero()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("0.0"));
    CPPUNIT_ASSERT((wxDouble)0.0 == CBSLXMLConverterEx::ConvertToDouble(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetDoubleValueNegative()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("-1.0"));
    CPPUNIT_ASSERT((wxDouble)-1.0 == CBSLXMLConverterEx::ConvertToDouble(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI32Value()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxInt32)314159 == CBSLXMLConverterEx::ConvertToI32(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI32ValueOne()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxInt32)1 == CBSLXMLConverterEx::ConvertToI32(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI32ValueZero()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxInt32)0 == CBSLXMLConverterEx::ConvertToI32(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI32ValueNegative()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("-1"));
    CPPUNIT_ASSERT((wxInt32)-1 == CBSLXMLConverterEx::ConvertToI32(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI64Value()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxInt64)314159 == CBSLXMLConverterEx::ConvertToI64(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI64ValueOne()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxInt64)1 == CBSLXMLConverterEx::ConvertToI64(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI64ValueZero()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxInt64)0 == CBSLXMLConverterEx::ConvertToI64(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetI64ValueNegative()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("-1"));
    CPPUNIT_ASSERT((wxInt64)-1 == CBSLXMLConverterEx::ConvertToI64(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetUI32Value()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxUint32)314159 == CBSLXMLConverterEx::ConvertToUI32(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetUI32ValueOne()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxUint32)1 == CBSLXMLConverterEx::ConvertToUI32(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetUI32ValueZero()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxUint32)0 == CBSLXMLConverterEx::ConvertToUI32(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetUI64Value()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxUint64)314159 == CBSLXMLConverterEx::ConvertToUI64(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetUI64ValueOne()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxUint64)1 == CBSLXMLConverterEx::ConvertToUI64(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetUI64ValueZero()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    pElement->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxUint64)0 == CBSLXMLConverterEx::ConvertToUI64(pElement->GetValue()));
    delete pElement;
}

void XMLElementExTestCase::GetSetNameHash()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    wxString strName = wxT("TestName");
    pElement->SetName(strName.wx_str());
    CPPUNIT_ASSERT(strName == pElement->GetName());
    CPPUNIT_ASSERT(0xde52bb50 == pElement->GetNameHash());
    delete pElement;
}

void XMLElementExTestCase::GetSetValueHash()
{
    CBSLXMLElementEx* pElement = new CBSLXMLElementEx();
    wxString strValue = wxT("TestValue");
    pElement->SetValue(strValue.wx_str());
    CPPUNIT_ASSERT(strValue == pElement->GetValue());
    CPPUNIT_ASSERT(0x102798 == pElement->GetValueHash());
    delete pElement;
}

void XMLElementExTestCase::Parse()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");

    strElement.Printf(
        wxT("<%s>%s</%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseBoolTrue1()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("1");

    strElement.Printf(
        wxT("<%s/>"),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(true == CBSLXMLConverterEx::ConvertToBool(oElement.GetValue()));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseBoolTrue2()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("1");

    strElement.Printf(
        wxT("<%s>%s</%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(true == CBSLXMLConverterEx::ConvertToBool(oElement.GetValue()));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseBoolFalse()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("0");

    strElement.Printf(
        wxT("<%s>%s</%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(false == CBSLXMLConverterEx::ConvertToBool(oElement.GetValue()));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseEmpty()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("");

    strElement.Printf(
        wxT("<%s>%s</%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(strElementValue == oElement.GetValue());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseCDATA()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("<tag1>tag1value</tag1>");

    strElement.Printf(
        wxT("<%s><![CDATA[%s]]></%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseXMLComment()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;

    strElement = wxT("<!-- This is a comment -->");

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(NULL == oElement.GetName());
    CPPUNIT_ASSERT(wxEmptyString == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseAttribute1()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");
    wxString strElementAttribName = wxT("TestAttribName");
    wxString strElementAttribValue = wxT("TestAttribValue");

    strElement.Printf(
        wxT("<%s %s=\"%s\">%s</%s>"),
        strElementName.wx_str(),
        strElementAttribName.wx_str(),
        strElementAttribValue.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(strElementAttribValue == CBSLXMLConverterEx::ConvertToString(oElement.FindAttribute(strElementAttribName)->GetValue(), oElement.FindAttribute(strElementAttribName)->GetValueLength()));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseAttribute2()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");
    wxString strElementAttrib1Name = wxT("TestAttrib1Name");
    wxString strElementAttrib1Value = wxT("TestAttrib1Value");
    wxString strElementAttrib2Name = wxT("TestAttrib2Name");
    wxString strElementAttrib2Value = wxT("TestAttrib2Value");

    strElement.Printf(
        wxT("<%s %s=\"%s\" %s=\"%s\">%s</%s>"),
        strElementName.wx_str(),
        strElementAttrib1Name.wx_str(),
        strElementAttrib1Value.wx_str(),
        strElementAttrib2Name.wx_str(),
        strElementAttrib2Value.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(strElementAttrib1Value == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttrib1Name)->GetValue(),
        oElement.FindAttribute(strElementAttrib1Name)->GetValueLength()
        ));
    CPPUNIT_ASSERT(strElementAttrib2Value == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttrib2Name)->GetValue(),
        oElement.FindAttribute(strElementAttrib2Name)->GetValueLength()
        ));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseAttributeSingleQuote()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");
    wxString strElementAttribName = wxT("TestAttribName");
    wxString strElementAttribValue = wxT("TestAttribValue");

    strElement.Printf(
        wxT("<%s %s='%s'>%s</%s>"),
        strElementName.wx_str(),
        strElementAttribName.wx_str(),
        strElementAttribValue.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(strElementAttribValue == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttribName)->GetValue(),
        oElement.FindAttribute(strElementAttribName)->GetValueLength()
        ));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseAttributeDoubleQuote()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");
    wxString strElementAttribName = wxT("TestAttribName");
    wxString strElementAttribValue = wxT("TestAttribValue");

    strElement.Printf(
        wxT("<%s %s=\"%s\">%s</%s>"),
        strElementName.wx_str(),
        strElementAttribName.wx_str(),
        strElementAttribValue.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(strElementAttribValue == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttribName)->GetValue(),
        oElement.FindAttribute(strElementAttribName)->GetValueLength()
        ));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseAttributeMixedQuotes()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");
    wxString strElementAttribName = wxT("TestAttribName");
    wxString strElementAttribValue = wxT("'T'e's't'A't't'r'i'b'V'a''l'u'e'");

    strElement.Printf(
        wxT("<%s %s=\"%s\">%s</%s>"),
        strElementName.wx_str(),
        strElementAttribName.wx_str(),
        strElementAttribValue.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(strElementAttribValue == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttribName)->GetValue(),
        oElement.FindAttribute(strElementAttribName)->GetValueLength()
        ));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseAttributeBothQuotes()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");
    wxString strElementAttrib1Name = wxT("TestAttrib1Name");
    wxString strElementAttrib1Value = wxT("'TestAttrib1Value'");
    wxString strElementAttrib2Name = wxT("TestAttrib2Name");
    wxString strElementAttrib2Value = wxT("\"TestAttrib2Value\"");

    strElement.Printf(
        wxT("<%s %s=\"%s\" %s='%s'>%s</%s>"),
        strElementName.wx_str(),
        strElementAttrib1Name.wx_str(),
        strElementAttrib1Value.wx_str(),
        strElementAttrib2Name.wx_str(),
        strElementAttrib2Value.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(strElementAttrib1Value == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttrib1Name)->GetValue(),
        oElement.FindAttribute(strElementAttrib1Name)->GetValueLength()
        ));
    CPPUNIT_ASSERT(strElementAttrib2Value == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttrib2Name)->GetValue(),
        oElement.FindAttribute(strElementAttrib2Name)->GetValueLength()
        ));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::ParseWhitespace()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("TestValue");
    wxString strElementAttrib1Name = wxT("TestAttrib1Name");
    wxString strElementAttrib1Value = wxT("TestAttrib1Value");
    wxString strElementAttrib2Name = wxT("TestAttrib2Name");
    wxString strElementAttrib2Value = wxT("TestAttrib2Value");

    strElement.Printf(
        wxT("     <%s      %s     =     \"%s\"     %s     =     \"%s\"     >     %s</%s>"),
        strElementName.wx_str(),
        strElementAttrib1Name.wx_str(),
        strElementAttrib1Value.wx_str(),
        strElementAttrib2Name.wx_str(),
        strElementAttrib2Value.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(strElementName == oElement.GetName());
    CPPUNIT_ASSERT(strElementValue == CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
    CPPUNIT_ASSERT(strElementAttrib1Value == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttrib1Name)->GetValue(),
        oElement.FindAttribute(strElementAttrib1Name)->GetValueLength()
        ));
    CPPUNIT_ASSERT(strElementAttrib2Value == CBSLXMLConverterEx::ConvertToString(
        oElement.FindAttribute(strElementAttrib2Name)->GetValue(),
        oElement.FindAttribute(strElementAttrib2Name)->GetValueLength()
        ));
    CPPUNIT_ASSERT(0xde52bb50 == oElement.GetNameHash());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeNormal()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("Test");

    strElement.Printf(
        wxT("<%s>%s</%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeNormal == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeBoolTrue1()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("1");

    strElement.Printf(
        wxT("<%s/>"),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeBool == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeBoolTrue2()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("1");

    strElement.Printf(
        wxT("<%s>%s</%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeBool == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeBoolFalse()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("0");

    strElement.Printf(
        wxT("<%s>%s</%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeBool == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeCDATA()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;
    wxString strElementName = wxT("TestName");
    wxString strElementValue = wxT("<tag1>tag1value</tag1>");

    strElement.Printf(
        wxT("<%s><![CDATA[%s]]></%s>"),
        strElementName.wx_str(),
        strElementValue.wx_str(),
        strElementName.wx_str()
    );

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeCDATA == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeXMLComment()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;

    strElement = wxT("<!-- This is a comment -->");

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeComment == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeContainer()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;

    strElement = wxT("<Test1>");

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeContainer == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}

void XMLElementExTestCase::DetectTypeContainerEnd()
{
    BSLXMLERRCODE rc;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strElement;

    strElement = wxT("</Test1>");

    oDocument.SetDocument(strElement);
    rc = oElement.Parse(oDocument);

    CPPUNIT_ASSERT(CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType());
    CPPUNIT_ASSERT(BSLXMLERR_SUCCESS == rc);
}
