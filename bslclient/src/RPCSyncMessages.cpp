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
#include "RPCSyncMessages.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncMessages, CRPCProtocol);

CRPCSyncMessages::CRPCSyncMessages():
    CRPCProtocol(wxT("get_messages"), sizeof(wxT("get_messages")))
{
}

CRPCSyncMessages::~CRPCSyncMessages()
{
}

BSLERRCODE CRPCSyncMessages::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, wxUint32 uiSequenceNumber)
{
    // Cache parameters so the GetRequest function can use them
    m_uiSequenceNumber = uiSequenceNumber;

    // Execute the RPC
    return CRPCProtocol::Execute(pHost, type);
}

wxString CRPCSyncMessages::GetRequest()
{
    wxString strRequest;

    strRequest.Printf(
        wxT("%s\n")
        wxT("  <%s>\n")
        wxT("    <seqno>%d</seqno>\n")
        wxT("  </%s>\n")
        wxT("%s\n"),
        GetRequestHeader(),
        GetRequestName(),
        m_uiSequenceNumber,
        GetRequestName(),
        GetRequestFooter()
    );

    return strRequest;
}

BSLERRCODE CRPCSyncMessages::ParseResponse(CHost* pHost, wxString& strResponse)
{
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLMessage bslMessage, bslMessageData;
    CMessage* pMessage = NULL;
    CProject* pProject = NULL;
    std::vector<BSLHANDLE> oBulkAdd;
    std::vector<BSLHANDLE> oBulkUpdate;

    bool bMessageFound = false;

    oDocument.SetDocument(strResponse);
    oBulkAdd.reserve(GetEventManager()->GetOptimialQueueSize());
    oBulkUpdate.reserve(GetEventManager()->GetOptimialQueueSize());

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_MESSAGE == oElement.GetNameHash()) 
        {
            bMessageFound = true;

            bslMessage.Clear();
            bslMessage.ParseEx(oDocument);

            // Setup known handles
            bslMessage.SetHostHandle(pHost);

            // Find the missing handle
            if (BSLERR_OBJECT_NOT_FOUND != pHost->FindProject(bslMessage.GetProjectHash(), &pProject))
            {
                // Add missing handles
                bslMessage.SetProjectHandle(pProject);
            }

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindMessage(bslMessage.GetSequenceNumber(), &pMessage, &bslMessageData))
            {
                // Add missing handles
                bslMessage.SetMessageHandle(pMessage);
                bslMessage.SetData(bslMessageData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pMessage->Update(bslMessage))
                {
                    oBulkUpdate.push_back(pMessage->GetMessageHandle());
                }
            }
            else
            {
                pMessage = new CMessage(bslMessage);
                pHost->AddMessage(pMessage);

                oBulkAdd.push_back(pMessage->GetMessageHandle());
            }
        }
    }

    if (bMessageFound)
    {
        pHost->SetLastMessageSequenceNumber(bslMessage.GetSequenceNumber());
    }

    GetEventManager()->FireBulkEvent(wxEVT_BSLMESSAGE_BULKADD, pHost, oBulkAdd);
    GetEventManager()->FireBulkEvent(wxEVT_BSLMESSAGE_BULKUPDATE, pHost, oBulkUpdate);

    return BSLERR_SUCCESS;
}
