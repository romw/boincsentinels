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
#include "RPCSyncNotifications.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncNotifications, CRPCProtocol);

CRPCSyncNotifications::CRPCSyncNotifications():
    CRPCProtocol(wxT("get_notices"), sizeof(wxT("get_notices")))
{
}

CRPCSyncNotifications::~CRPCSyncNotifications()
{
}

BSLERRCODE CRPCSyncNotifications::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, wxUint32 uiSequenceNumber)
{
    // Cache parameters so the GetRequest function can use them
    m_uiSequenceNumber = uiSequenceNumber;

    // Execute the RPC
    return CRPCProtocol::Execute(pHost, type);
}

wxString CRPCSyncNotifications::GetRequest()
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

BSLERRCODE CRPCSyncNotifications::ParseResponse(CHost* pHost, wxString& strResponse)
{
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLNotification bslNotification, bslNotificationData;
    CNotification* pNotification = NULL;
    CProject* pProject = NULL;
    bool bResetFlagFound = false;
    bool bNotificationFound = false;
    wxInt32 iHighestSequenceNumberFound = -1;
    std::vector<CNotification*> oNotifications;
    std::vector<BSLHANDLE> oBulkAdd;
    std::vector<BSLHANDLE> oBulkUpdate;

    oDocument.SetDocument(strResponse);
    oBulkAdd.reserve(GetEventManager()->GetOptimialQueueSize());
    oBulkUpdate.reserve(GetEventManager()->GetOptimialQueueSize());

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_NOTIFICATION == oElement.GetNameHash()) 
        {
            bslNotification.Clear();
            bslNotification.ParseEx(oDocument);

            if (-1 == bslNotification.GetSequenceNumber())
            {
                bResetFlagFound = true;
                break;
            }
            else
            {
                bNotificationFound = true;

                if (iHighestSequenceNumberFound < bslNotification.GetSequenceNumber())
                {
                    iHighestSequenceNumberFound = bslNotification.GetSequenceNumber();
                }

                // Setup known handles
                bslNotification.SetHostHandle(pHost);

                // Find the missing handle
                if (BSLERR_OBJECT_NOT_FOUND != pHost->FindProject(bslNotification.GetProjectHash(), &pProject))
                {
                    // Add missing handles
                    bslNotification.SetProjectHandle(pProject);
                }

                // Update existing record if it already exists
                if (BSLERR_SUCCESS == pHost->FindNotification(bslNotification.GetSequenceNumber(), &pNotification, &bslNotificationData))
                {
                    // Add missing handles
                    bslNotification.SetNotificationHandle(pNotification);
                    bslNotification.SetData(bslNotificationData.GetData());

                    // Only update if something has changed
                    if (BSLERR_SUCCESS == pNotification->Update(bslNotification))
                    {
                        oBulkUpdate.push_back(pNotification->GetNotificationHandle());
                    }
                }
                else
                {
                    pNotification = new CNotification(bslNotification);
                    pHost->AddNotification(pNotification);

                    oBulkAdd.push_back(pNotification->GetNotificationHandle());
                }
            }
        }
    }

    // We were told to reset the notification list, so get rid of any excess notifications
    if (bResetFlagFound)
    {
        pHost->EnumerateNotifications(oNotifications);
        for (std::vector<CNotification*>::iterator iter = oNotifications.begin(); iter != oNotifications.end(); iter++)
        {
            if ((*iter)->GetSequenceNumber() > iHighestSequenceNumberFound)
            {
                pHost->DeleteNotification(*iter);
            }
        }
    }

    // Store the highest sequence number found so far for future use.
    if (bNotificationFound)
    {
        pHost->SetLastNotificationSequenceNumber(iHighestSequenceNumberFound);
    }

    GetEventManager()->FireBulkEvent(wxEVT_BSLNOTIFICATION_BULKADD, pHost, oBulkAdd);
    GetEventManager()->FireBulkEvent(wxEVT_BSLNOTIFICATION_BULKUPDATE, pHost, oBulkUpdate);

    return BSLERR_SUCCESS;
}
