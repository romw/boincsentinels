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
#include "RPCSyncTransfers.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncTransfers, CRPCProtocol);

CRPCSyncTransfers::CRPCSyncTransfers():
    CRPCProtocol(wxT("get_file_transfers"), sizeof(wxT("get_file_transfers")))
{
}

CRPCSyncTransfers::~CRPCSyncTransfers()
{
}

BSLERRCODE CRPCSyncTransfers::ParseResponse(CHost* pHost, wxString& strResponse)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLTransfer bslTransfer, bslTransferData;
    CTransfer* pTransfer = NULL;
    CProject* pProject = NULL;
    std::vector<BSLHANDLE> oBulkAdd;
    std::vector<BSLHANDLE> oBulkUpdate;

    oDocument.SetDocument(strResponse);
    oBulkAdd.reserve(GetEventManager()->GetOptimialQueueSize());
    oBulkUpdate.reserve(GetEventManager()->GetOptimialQueueSize());

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_TRANSFER == oElement.GetNameHash()) 
        {
            bslTransfer.Clear();
            bslTransfer.ParseEx(oDocument);

            if (BSLERR_SUCCESS == pHost->FindProject(bslTransfer.GetProjectHash(), &pProject))
            {
                // Setup known handles
                bslTransfer.SetHostHandle(pHost);
                bslTransfer.SetProjectHandle(pProject);

                // Update existing record if it already exists
                if (BSLERR_SUCCESS == pHost->FindTransfer(bslTransfer.GetProjectHash(), bslTransfer.GetNameHash(), &pTransfer, &bslTransferData))
                {
                    // Add missing handles
                    bslTransfer.SetTransferHandle(bslTransferData.GetTransferHandle());
                    bslTransfer.SetData(bslTransferData.GetData());

                    // Only update if something has changed
                    if (BSLERR_SUCCESS == pTransfer->Update(bslTransfer))
                    {
                        oBulkUpdate.push_back(pTransfer->GetTransferHandle());
                    }
                }
                else
                {
                    pTransfer = new CTransfer(bslTransfer);
                    pHost->AddTransfer(pTransfer);

                    oBulkAdd.push_back(pTransfer->GetTransferHandle());
                }
            }
            else
            {
                rc = BSLERR_OBJECT_NOT_FOUND;
            }
        }
    }

    GetEventManager()->FireBulkEvent(wxEVT_BSLTRANSFER_BULKADD, pHost, oBulkAdd);
    GetEventManager()->FireBulkEvent(wxEVT_BSLTRANSFER_BULKUPDATE, pHost, oBulkUpdate);

    return rc;
}
