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
#include "RPCProtocol.h"
#include "RPCProjectAttachPoll.h"

#define BSLXMLTAGHASH_UNAUTHORIZED \
    0xe08a02f
#define BSLXMLTAGHASH_ERRORCODE \
    0x45f101b0
#define BSLXMLTAGHASH_ERRORMESSAGE \
    0xdbfffa2a

IMPLEMENT_DYNAMIC_CLASS(CRPCProjectAttachPoll, CRPCProtocol);

CRPCProjectAttachPoll::CRPCProjectAttachPoll():
    CRPCProtocol(wxT("project_attach_poll"), sizeof(wxT("project_attach_poll")))
{
}

CRPCProjectAttachPoll::~CRPCProjectAttachPoll()
{
}

BSLERRCODE CRPCProjectAttachPoll::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, BSLERRCODE& ulReturnCode, std::vector<wxString>& oMessages)
{
    BSLERRCODE rc = BSLERR_FAILURE;

    // Execute RPC
    rc = CRPCProtocol::Execute(pHost, type);

    // Return the values
    ulReturnCode = m_ulReturnCode;
    oMessages = m_oMessages;

    return rc;
}

BSLERRCODE CRPCProjectAttachPoll::ParseResponse(CHost* WXUNUSED(pHost), wxString& strResponse)
{
    BSLERRCODE rc = BSLERR_OBJECT_NOT_FOUND;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    oDocument.SetDocument(strResponse);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_UNAUTHORIZED == oElement.GetNameHash()) 
        {
            rc = BSLERR_ACCESS_DENIED;
        }
        if (BSLXMLTAGHASH_ERRORCODE == oElement.GetNameHash())
        {
            m_ulReturnCode = CovertBOINCERRCODEToBSLERRCODE(CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue()));
            rc = BSLERR_SUCCESS;
        }
        if (BSLXMLTAGHASH_ERRORMESSAGE == oElement.GetNameHash())
        {
            m_oMessages.push_back(CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
        }
    }

    return rc;
}
