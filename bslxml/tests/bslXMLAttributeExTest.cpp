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
#include "bslXMLAttributeExTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(XMLAttributeExTestCase);

void XMLAttributeExTestCase::CreateDelete()
{
    CBSLXMLAttributeEx* pXMLAttributeEx = new CBSLXMLAttributeEx();
    CPPUNIT_ASSERT(pXMLAttributeEx != NULL);
    delete pXMLAttributeEx;
}

void XMLAttributeExTestCase::GetSetName()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    wxString strName = wxT("TestName");
    pAttribute->SetName(strName.wx_str());
    CPPUNIT_ASSERT(strName == pAttribute->GetName());
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetValue()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    wxString strValue = wxT("TestValue");
    pAttribute->SetValue(strValue.wx_str());
    CPPUNIT_ASSERT(strValue == pAttribute->GetValue());
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetBoolValueTrue()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("1"));
    CPPUNIT_ASSERT(true == CBSLXMLConverterEx::ConvertToBool(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetBoolValueFalse()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("0"));
    CPPUNIT_ASSERT(false == CBSLXMLConverterEx::ConvertToBool(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetStringValue()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    wxString strValue = wxT("TestValue");
    pAttribute->SetValue(strValue.wx_str());
    CPPUNIT_ASSERT(pAttribute->GetValue() == strValue.wx_str());
    CPPUNIT_ASSERT(pAttribute->GetValueLength() == strValue.size());
    CPPUNIT_ASSERT(strValue == CBSLXMLConverterEx::ConvertToString(pAttribute->GetValue(), pAttribute->GetValueLength()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetDoubleValue()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("3.14159"));
    CPPUNIT_ASSERT((wxDouble)3.14159 == CBSLXMLConverterEx::ConvertToDouble(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetDoubleValueOne()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("1.0"));
    CPPUNIT_ASSERT((wxDouble)1.0 == CBSLXMLConverterEx::ConvertToDouble(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetDoubleValueZero()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("0.0"));
    CPPUNIT_ASSERT((wxDouble)0.0 == CBSLXMLConverterEx::ConvertToDouble(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetDoubleValueNegative()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("-1.0"));
    CPPUNIT_ASSERT((wxDouble)-1.0 == CBSLXMLConverterEx::ConvertToDouble(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI32Value()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxInt32)314159 == CBSLXMLConverterEx::ConvertToI32(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI32ValueOne()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxInt32)1 == CBSLXMLConverterEx::ConvertToI32(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI32ValueZero()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxInt32)0 == CBSLXMLConverterEx::ConvertToI32(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI32ValueNegative()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("-1"));
    CPPUNIT_ASSERT((wxInt32)-1 == CBSLXMLConverterEx::ConvertToI32(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI64Value()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxInt64)314159 == CBSLXMLConverterEx::ConvertToI64(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI64ValueOne()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxInt64)1 == CBSLXMLConverterEx::ConvertToI64(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI64ValueZero()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxInt64)0 == CBSLXMLConverterEx::ConvertToI64(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetI64ValueNegative()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("-1"));
    CPPUNIT_ASSERT((wxInt64)-1 == CBSLXMLConverterEx::ConvertToI64(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetUI32Value()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxUint32)314159 == CBSLXMLConverterEx::ConvertToUI32(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetUI32ValueOne()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxUint32)1 == CBSLXMLConverterEx::ConvertToUI32(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetUI32ValueZero()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxUint32)0 == CBSLXMLConverterEx::ConvertToUI32(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetUI64Value()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("314159"));
    CPPUNIT_ASSERT((wxUint64)314159 == CBSLXMLConverterEx::ConvertToUI64(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetUI64ValueOne()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("1"));
    CPPUNIT_ASSERT((wxUint64)1 == CBSLXMLConverterEx::ConvertToUI64(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetUI64ValueZero()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    pAttribute->SetValue(wxT("0"));
    CPPUNIT_ASSERT((wxUint64)0 == CBSLXMLConverterEx::ConvertToUI64(pAttribute->GetValue()));
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetNameHash()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    wxString strName = wxT("TestName");
    pAttribute->SetName(strName.wx_str());
    CPPUNIT_ASSERT(strName == pAttribute->GetName());
    CPPUNIT_ASSERT(0xde52bb50 == pAttribute->GetNameHash());
    delete pAttribute;
}

void XMLAttributeExTestCase::GetSetValueHash()
{
    CBSLXMLAttributeEx* pAttribute = new CBSLXMLAttributeEx();
    wxString strValue = wxT("TestValue");
    pAttribute->SetValue(strValue.wx_str());
    CPPUNIT_ASSERT(strValue == pAttribute->GetValue());
    CPPUNIT_ASSERT(0x102798 == pAttribute->GetValueHash());
    delete pAttribute;
}
