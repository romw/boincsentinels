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
#include "Instance.h"
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateEvents.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "EventManager.h"
#include "RPCProtocol.h"
#include "RPCSyncProjectStatistics.h"

#define BSLXMLTAGHASH_PROJECTGROUPING \
    0x97f08fa2
#define BSLXMLTAGHASH_MASTERURL \
    0xda55ae25

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncProjectStatistics, CRPCProtocol);

CRPCSyncProjectStatistics::CRPCSyncProjectStatistics():
    CRPCProtocol(wxT("get_statistics"), sizeof(wxT("get_statistics")))
{
}

CRPCSyncProjectStatistics::~CRPCSyncProjectStatistics()
{
}

BSLERRCODE CRPCSyncProjectStatistics::ParseResponse(CHost* pHost, wxString& strResponse)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLProjectStatistic bslProjectStatistic, bslProjectStatisticData;
    CProject* pProject = NULL;
    CProjectStatistic* pProjectStatistic = NULL;
    std::vector<BSLHANDLE> oBulkAdd;
    std::vector<BSLHANDLE> oBulkUpdate;

    oDocument.SetDocument(strResponse);
    oBulkAdd.reserve(GetEventManager()->GetOptimialQueueSize());
    oBulkUpdate.reserve(GetEventManager()->GetOptimialQueueSize());

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECTGROUPING == oElement.GetNameHash()) 
        {
            while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
            {
                if (BSLXMLTAGHASH_PROJECTGROUPING == oElement.GetNameHash()) break;
                if (BSLXMLTAGHASH_MASTERURL == oElement.GetNameHash())
                {                    
                    pHost->FindProject(oElement.GetValueHash(), &pProject);
                }
                else if ((BSLXMLTAGHASH_PROJECTSTATISTIC == oElement.GetNameHash()) && pProject)
                {
                    bslProjectStatistic.Clear();

                    // Parse data
                    bslProjectStatistic.ParseEx(oDocument);

                    // Setup known handles
                    bslProjectStatistic.SetHostHandle(pHost);
                    bslProjectStatistic.SetProjectHandle(pProject);

                    // Update existing record if it already exists
                    if (BSLERR_SUCCESS == pProject->FindProjectStatistic(bslProjectStatistic.GetTimestamp(), &pProjectStatistic, &bslProjectStatisticData))
                    {
                        // Add missing handles
                        bslProjectStatistic.SetProjectStatisticHandle(bslProjectStatisticData.GetProjectStatisticHandle());
                        bslProjectStatistic.SetData(bslProjectStatisticData.GetData());

                        // Only update if something has changed
                        if (BSLERR_SUCCESS == pProjectStatistic->Update(bslProjectStatistic))
                        {
                            oBulkUpdate.push_back(pProjectStatistic->GetProjectStatisticHandle());
                        }
                    }
                    else
                    {
                        pProjectStatistic = new CProjectStatistic(bslProjectStatistic);
                        pProject->AddProjectStatistic(pProjectStatistic);

                        oBulkAdd.push_back(pProjectStatistic->GetProjectStatisticHandle());
                    }
                }
                else if (!pProject)
                {
                    rc = BSLERR_OBJECT_NOT_FOUND;
                }
            }
        }
    }

    GetEventManager()->FireBulkEvent(wxEVT_BSLPROJECTSTATISTIC_BULKADD, pHost, oBulkAdd);
    GetEventManager()->FireBulkEvent(wxEVT_BSLPROJECTSTATISTIC_BULKUPDATE, pHost, oBulkUpdate);

    return rc;
}
