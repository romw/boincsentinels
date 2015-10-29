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
#include "bslxml/bslXMLTypes.h"
#include "bslxml/bslXMLTestUtil.h"
#include "bslcommon/bslCommonTypes.h"
#include "BOINCXMLStream.h"
#include "BOINCNativeParsers.h"
#include "BOINCNativeTaskInstance.h"
#include "BOINCParsers.h"
#include "BOINCSentinelsParserEx.h"

#define REPLICATIONFACTOR 5000
//#define BOINCSENTINELPARSERONLY 1

int main(int , char**)
{
    CBOINCXMLStream oBOINCXML;
    CBSLXMLDocumentEx oDocument;
    std::vector<CBSLTaskInstance*> oNewTaskInstances;
#ifndef BOINCSENTINELPARSERONLY
    std::vector<TASKINSTANCE*> oOldTaskInstances;
    wxChar* pCurrentPosition;
#endif
    wxDateTime dtStart;
    wxTimeSpan tsDuration;


    wxInitialize();

#if 0
#ifndef BOINCSENTINELPARSERONLY
    wxPrintf(wxT("Memory scan speed...\n"));
    if (oDocument.SetDocumentFromFile(wxT("get_results.xml")))
    {
        wxPrintf(wxT("    Super sizing task instance list...\n"));
        CBSLXMLTestUtil::ReplicateDocument(oDocument, REPLICATIONFACTOR);

        dtStart = wxDateTime::UNow();

        pCurrentPosition = oDocument.GetPosition();
        while (*pCurrentPosition)
        {
            ++pCurrentPosition;
        }

        tsDuration = wxDateTime::UNow() - dtStart;
        wxPrintf(wxT("    Elapsed Time: %llu milliseconds\n"), tsDuration.GetMilliseconds());
        wxPrintf(wxT("    Array Size: %d \n"), (int)(pCurrentPosition - oDocument.GetPosition()));
    }
#endif

#ifndef BOINCSENTINELPARSERONLY
    wxPrintf(wxT("XML Stream Line Scan speed...\n"));
    if (oDocument.SetDocumentFromFile(wxT("get_results.xml")))
    {
        wxPrintf(wxT("    Super sizing task instance list...\n"));
        CBSLXMLTestUtil::ReplicateDocument(oDocument, REPLICATIONFACTOR);

        dtStart = wxDateTime::UNow();

        pCurrentPosition = 0;;
        while (oDocument.GetNextElement())
        {
            ++pCurrentPosition;
        }

        tsDuration = wxDateTime::UNow() - dtStart;
        wxPrintf(wxT("    Elapsed Time: %llu milliseconds\n"), tsDuration.GetMilliseconds());
        wxPrintf(wxT("    Line Count: %d \n"), (int)pCurrentPosition);
    }
#endif
#endif

    wxPrintf(wxT("BOINC Sentinels XML parser v2 (FNV1 Static Hash Map) speed...\n"));
    if (BSLXMLERR_SUCCESS == oDocument.SetDocumentFromFile(wxT("get_results.xml")))
    {
        wxPrintf(wxT("    Super sizing task instance list...\n"));
        CBSLXMLTestUtil::ReplicateDocument(oDocument, REPLICATIONFACTOR);

        dtStart = wxDateTime::UNow();

        BOINCSentinelsParserExTaskInstances(oDocument, oNewTaskInstances);

        tsDuration = wxDateTime::UNow() - dtStart;
        wxPrintf(wxT("    Elapsed Time: %llu milliseconds\n"), tsDuration.GetMilliseconds());
        wxPrintf(wxT("    Result Count: %d \n"), (int)oNewTaskInstances.size());

        for (size_t i = 0; i < oNewTaskInstances.size(); ++i)
        {
            delete oNewTaskInstances[i];
        }
        oNewTaskInstances.clear();
    }


#ifndef BOINCSENTINELPARSERONLY
    wxPrintf(wxT("BOINC XML parser v1 speed...\n"));
    if (oBOINCXML.StreamFromFile(wxT("get_results.xml")))
    {
        wxPrintf(wxT("    Super sizing task instance list...\n"));
        CBSLXMLTestUtil::ReplicateDocument(oDocument, REPLICATIONFACTOR);

        dtStart = wxDateTime::UNow();

        BOINCV1ParserTaskInstances(oBOINCXML, oOldTaskInstances);

        tsDuration = wxDateTime::UNow() - dtStart;
        wxPrintf(wxT("    Elapsed Time: %llu milliseconds\n"), tsDuration.GetMilliseconds());
        wxPrintf(wxT("    Result Count: %d \n"), (int)oOldTaskInstances.size());
        for (size_t i = 0; i < oOldTaskInstances.size(); ++i)
        {
            delete oOldTaskInstances[i];
        }
        oOldTaskInstances.clear();
    }
#endif


#ifndef BOINCSENTINELPARSERONLY
    wxPrintf(wxT("BOINC XML parser v2 (XML_PARSER) speed...\n"));
    if (oBOINCXML.StreamFromFile(wxT("get_results.xml")))
    {
        wxPrintf(wxT("    Super sizing task instance list...\n"));
        CBSLXMLTestUtil::ReplicateDocument(oDocument, REPLICATIONFACTOR);

        dtStart = wxDateTime::UNow();

        BOINCV2ParserTaskInstances(oBOINCXML, oOldTaskInstances);

        tsDuration = wxDateTime::UNow() - dtStart;
        wxPrintf(wxT("    Elapsed Time: %llu milliseconds\n"), tsDuration.GetMilliseconds());
        wxPrintf(wxT("    Result Count: %d \n"), (int)oOldTaskInstances.size());
        for (size_t i = 0; i < oOldTaskInstances.size(); ++i)
        {
            delete oOldTaskInstances[i];
        }
        oOldTaskInstances.clear();
    }
#endif


    wxUninitialize();


    return EXIT_SUCCESS;
}

