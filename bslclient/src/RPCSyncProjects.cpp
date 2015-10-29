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
#include "RPCSyncProjects.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncProjects, CRPCProtocol);

CRPCSyncProjects::CRPCSyncProjects():
    CRPCProtocol(wxT("get_project_status"), sizeof(wxT("get_project_status")))
{
}

CRPCSyncProjects::~CRPCSyncProjects()
{
}

BSLERRCODE CRPCSyncProjects::ParseResponse(CHost* pHost, wxString& strResponse)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLProject bslProject, bslProjectData;
    CProject* pProject = NULL;
    std::vector<BSLHANDLE> oBulkUpdate;

    oDocument.SetDocument(strResponse);
    oBulkUpdate.reserve(GetEventManager()->GetOptimialQueueSize());

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECT == oElement.GetNameHash()) 
        {
            bslProject.Clear();
            bslProject.ParseEx(oDocument);

            // Setup known handles
            bslProject.SetHostHandle(pHost);

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindProject(bslProject.GetMasterURLHash(), &pProject, &bslProjectData))
            {
                // Add missing handles
                bslProject.SetProjectHandle(pProject);
                bslProject.SetData(bslProjectData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pProject->Update(bslProject))
                {
                    oBulkUpdate.push_back(pProject->GetProjectHandle());
                }
            }
            else
            {
                rc = BSLERR_OBJECT_NOT_FOUND;
            }
        }
    }

    GetEventManager()->FireBulkEvent(wxEVT_BSLPROJECT_BULKUPDATE, pHost, oBulkUpdate);

    return rc;
}
