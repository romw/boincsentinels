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

#ifndef CPP_UNIT_PROJECTLISTITEMTESTCASE_H
#define CPP_UNIT_PROJECTLISTITEMTESTCASE_H

class ProjectListItemTestCase: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ProjectListItemTestCase);
    CPPUNIT_TEST(CreateDelete);
    CPPUNIT_TEST(Equality);
    CPPUNIT_TEST(Inequality);
    CPPUNIT_TEST(AssignmentOperator);
    CPPUNIT_TEST(GetSetMasterURL);
    CPPUNIT_TEST(GetSetName);
    CPPUNIT_TEST(GetSetDescription);
    CPPUNIT_TEST(GetSetGeneralArea);
    CPPUNIT_TEST(GetSetSpecificArea);
    CPPUNIT_TEST(GetSetOrganization);
    CPPUNIT_TEST(GetSetLogo);
    CPPUNIT_TEST(GetSetSupportedPlatforms);
    CPPUNIT_TEST(ParseEx);
    CPPUNIT_TEST(ParseCDATA);
    CPPUNIT_TEST_SUITE_END();

protected:
    void CreateDelete();
    void Equality();
    void Inequality();
    void AssignmentOperator();
    void GetSetMasterURL();
    void GetSetName();
    void GetSetDescription();
    void GetSetGeneralArea();
    void GetSetSpecificArea();
    void GetSetOrganization();
    void GetSetLogo();
    void GetSetSupportedPlatforms();
    void ParseEx();
    void ParseCDATA();
};

#endif
