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

#ifndef CPP_UNIT_APPTESTCASE_H
#define CPP_UNIT_APPTESTCASE_H

class XMLAttributeExTestCase: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(XMLAttributeExTestCase);
    CPPUNIT_TEST(CreateDelete);
    CPPUNIT_TEST(GetSetName);
    CPPUNIT_TEST(GetSetValue);
    CPPUNIT_TEST(GetSetBoolValueTrue);
    CPPUNIT_TEST(GetSetBoolValueFalse);
    CPPUNIT_TEST(GetSetStringValue);
    CPPUNIT_TEST(GetSetDoubleValue);
    CPPUNIT_TEST(GetSetDoubleValueOne);
    CPPUNIT_TEST(GetSetDoubleValueZero);
    CPPUNIT_TEST(GetSetDoubleValueNegative);
    CPPUNIT_TEST(GetSetI32Value);
    CPPUNIT_TEST(GetSetI32ValueOne);
    CPPUNIT_TEST(GetSetI32ValueZero);
    CPPUNIT_TEST(GetSetI32ValueNegative);
    CPPUNIT_TEST(GetSetI64Value);
    CPPUNIT_TEST(GetSetI64ValueOne);
    CPPUNIT_TEST(GetSetI64ValueZero);
    CPPUNIT_TEST(GetSetI64ValueNegative);
    CPPUNIT_TEST(GetSetUI32Value);
    CPPUNIT_TEST(GetSetUI32ValueOne);
    CPPUNIT_TEST(GetSetUI32ValueZero);
    CPPUNIT_TEST(GetSetUI64Value);
    CPPUNIT_TEST(GetSetUI64ValueOne);
    CPPUNIT_TEST(GetSetUI64ValueZero);
    CPPUNIT_TEST(GetSetNameHash);
    CPPUNIT_TEST(GetSetValueHash);
    CPPUNIT_TEST_SUITE_END();

protected:
    void CreateDelete();
    void GetSetName();
    void GetSetValue();
    void GetSetBoolValueTrue();
    void GetSetBoolValueFalse();
    void GetSetStringValue();
    void GetSetDoubleValue();
    void GetSetDoubleValueOne();
    void GetSetDoubleValueZero();
    void GetSetDoubleValueNegative();
    void GetSetI32Value();
    void GetSetI32ValueOne();
    void GetSetI32ValueZero();
    void GetSetI32ValueNegative();
    void GetSetI64Value();
    void GetSetI64ValueOne();
    void GetSetI64ValueZero();
    void GetSetI64ValueNegative();
    void GetSetUI32Value();
    void GetSetUI32ValueOne();
    void GetSetUI32ValueZero();
    void GetSetUI64Value();
    void GetSetUI64ValueOne();
    void GetSetUI64ValueZero();
    void GetSetNameHash();
    void GetSetValueHash();
};

#endif
