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
#include "RPCSyncProjectList.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncProjectList, CRPCProtocol);

CRPCSyncProjectList::CRPCSyncProjectList():
    CRPCProtocol(wxT("get_all_projects_list"), sizeof(wxT("get_all_projects_list")))
{
}

CRPCSyncProjectList::~CRPCSyncProjectList()
{
}

BSLERRCODE CRPCSyncProjectList::ParseResponse(CHost* pHost, wxString& strResponse)
{
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLProjectListItem bslProjectListItem, bslProjectListItemData;
    CProjectListItem* pProjectListItem = NULL;
    std::vector<BSLHANDLE> oBulkAdd;
    std::vector<BSLHANDLE> oBulkUpdate;

    oDocument.SetDocument(strResponse);
    oBulkAdd.reserve(GetEventManager()->GetOptimialQueueSize());
    oBulkUpdate.reserve(GetEventManager()->GetOptimialQueueSize());

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECTLISTITEM == oElement.GetNameHash()) 
        {
            bslProjectListItem.Clear();
            bslProjectListItem.ParseEx(oDocument);

            // Setup known handles
            bslProjectListItem.SetHostHandle(pHost);

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindProjectListItem(bslProjectListItem.GetMasterURLHash(), &pProjectListItem, &bslProjectListItemData))
            {
                // Add missing handles
                bslProjectListItem.SetProjectListItemHandle(pProjectListItem);
                bslProjectListItem.SetData(bslProjectListItemData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pProjectListItem->Update(bslProjectListItem))
                {
                    oBulkUpdate.push_back(pProjectListItem->GetProjectListItemHandle());
                }
            }
            else
            {
                pProjectListItem = new CProjectListItem(bslProjectListItem);
                pHost->AddProjectListItem(pProjectListItem);

                oBulkAdd.push_back(pProjectListItem->GetProjectListItemHandle());
            }
        }
    }

    GetEventManager()->FireBulkEvent(wxEVT_BSLPROJECTLISTITEM_BULKADD, pHost, oBulkAdd);
    GetEventManager()->FireBulkEvent(wxEVT_BSLPROJECTLISTITEM_BULKUPDATE, pHost, oBulkUpdate);

    return BSLERR_SUCCESS;
}
