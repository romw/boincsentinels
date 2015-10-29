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
#include "RPCManager.h"
#include "RPCProtocol.h"

#define BSLXMLTAGHASH_SUCCESS \
    0xd8120976
#define BSLXMLTAGHASH_AUTHENTICATOR \
    0x59c5c0ea
#define BSLXMLTAGHASH_UNAUTHORIZED \
    0xe08a02f
#define BSLXMLTAGHASH_ERROR \
    0x70192415
#define BSLXMLTAGHASH_ERRORCODE \
    0x45f101b0
#define BSLXMLTAGHASH_ERRORMESSAGE \
    0x37eead5b

IMPLEMENT_DYNAMIC_CLASS(CRPCProtocol, wxObject);

CRPCProtocol::CRPCProtocol() :
wxObject()
{
}

CRPCProtocol::CRPCProtocol(const wxChar* pszRPCName, wxUint32 uiRPCNameLength) :
wxObject()
{
    m_strRPCName = wxString(pszRPCName, uiRPCNameLength);
}

CRPCProtocol::~CRPCProtocol()
{
}

BSLERRCODE CRPCProtocol::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type)
{
    CRPCConnection* pConnection = NULL;
    CRPCProfile* pProfile = NULL;

    // Validate connection state
    if (pHost->GetConnectionState() != CHost::ConnectionStateConnected)
    {
        return BSLERR_CONNECT_NOT_CONNECTED;
    }

    // Find/Create the RPC Profile record for this RPC type.
    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindRPCProfile(GetClassInfo()->GetClassName(), &pProfile))
    {
        pProfile = new CRPCProfile(GetClassInfo()->GetClassName());
        pHost->AddRPCProfile(pProfile);
    }
    wxASSERT(pProfile);

    // Find the connection for use
    pConnection = GetConnection(pHost, type);
    wxASSERT(pConnection);

    // Execute RPC
    return OnExecute(pHost, pConnection, pProfile);
}

BSLERRCODE CRPCProtocol::OnExecute(CHost* pHost, CRPCConnection* pRPCConnection, CRPCProfile* pRPCProfiler)
{
    BSLERRCODE rc;
    wxDateTime dtLastRequestTime;
    wxUint64 ullRequestSize;
    wxUint64 ullResponseSize;
#ifdef __WXDEBUG__
    wxStopWatch swStopWatch;
    wxStopWatch swStopWatchTotal;
    wxTimeSpan tsRequestDuration;
    wxTimeSpan tsResponseDuration;
    wxTimeSpan tsParseDuration;
    wxTimeSpan tsTotalDuration;
#endif

    // Record the time stamp for this RPC
    dtLastRequestTime = wxDateTime::UNow();

    // Start the stop watch for the total duration
#ifdef __WXDEBUG__
    swStopWatchTotal.Start(0);
#endif

    // Preallocate request and response buffers
    // Increase last buffer sizes by 25% in case there is something new
    m_strRequest.Alloc(pRPCProfiler->GetRequestSize() * 1.25);
    m_strResponse.Alloc(pRPCProfiler->GetResponseSize() * 1.25);

    // Construct the RPC Request Message
    m_strRequest = GetRequest();

    pRPCConnection->Lock();

    // Write the request to the client socket
#ifdef __WXDEBUG__
    swStopWatch.Start(0);
#endif
    rc = pRPCConnection->WriteRPCMessage(m_strRequest);
#ifdef __WXDEBUG__
    tsRequestDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
    if (rc)
    {
        pRPCConnection->Unlock();
        goto CLEANUP;
    }

    // Read the response from the client socket
#ifdef __WXDEBUG__
    swStopWatch.Start(0);
#endif
    rc = pRPCConnection->ReadRPCMessage(m_strResponse);
#ifdef __WXDEBUG__
    tsResponseDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
    if (rc)
    {
        pRPCConnection->Unlock();
        goto CLEANUP;
    }

    // Release the connection lock before attempting to parse the response
    pRPCConnection->Unlock();

    // Parse the response from the client
#ifdef __WXDEBUG__
    swStopWatch.Start(0);
#endif
    rc = ParseResponse(pHost, m_strResponse);
#ifdef __WXDEBUG__
    tsParseDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
    if (BSLERR_OBJECT_NOT_FOUND == rc)
    {
        // One of the Sync RPCs couldn't find a dependent object, we need to refresh
        // the global state.
        pHost->ForceRefresh(true);
    }

CLEANUP:
    if (
        rc == BSLERR_CONNECT_IO_ERROR ||
        rc == BSLERR_CONNECT_NOT_CONNECTED
    )
    {
        if (
            pHost->GetConnectionState() == CHost::ConnectionStateUnknown ||
            pHost->GetConnectionState() == CHost::ConnectionStateConnected
        )
        {
            pHost->SetConnectionState(CHost::ConnectionStateDisconnected);
        }
    }

#ifdef __WXDEBUG__
    // Stop the stop watch for the total duration
    tsTotalDuration = wxTimeSpan(0, 0, 0, swStopWatchTotal.Time());
#endif

    // Update RPC Statistics
    ullRequestSize = m_strRequest.size();
    ullResponseSize = m_strResponse.size();

#ifdef __WXDEBUG__
    pRPCProfiler->Update(
        dtLastRequestTime,
        tsRequestDuration,
        ullRequestSize,
        tsResponseDuration,
        ullResponseSize,
        tsParseDuration,
        tsTotalDuration
    );
#else
    pRPCProfiler->Update(
        dtLastRequestTime,
        ullRequestSize,
        ullResponseSize
    );
#endif

    if (rc) return rc;
    return BSLERR_SUCCESS;
}

CRPCConnection* CRPCProtocol::GetConnection(CHost* pHost, CRPCConnection::CONNECTIONTYPE type)
{
    CRPCConnection* pConnection = NULL;
    switch(type) {
        case CRPCConnection::ConnectionTypeOnDemand:
            pConnection = pHost->m_pRPCOnDemand;
            break;
        case CRPCConnection::ConnectionTypeStatusUpdate:
            pConnection = pHost->m_pRPCStatusUpdate;
            break;
    }
    return pConnection;
}

wxString CRPCProtocol::GetLastError()
{
    return m_strErrorMessage;
}

wxString CRPCProtocol::GetRequest()
{
    wxString strRPCRequest;

    strRPCRequest.Printf(
        wxT("%s\n")
        wxT("  <%s/>\n")
        wxT("%s\n"),
        GetRequestHeader(),
        GetRequestName(),
        GetRequestFooter()
    );

    return strRPCRequest;
}

const wxChar* CRPCProtocol::GetRequestHeader()
{
    return wxT("<boinc_gui_rpc_request>");
}

const wxChar* CRPCProtocol::GetRequestFooter()
{
    return wxT("</boinc_gui_rpc_request>");
}

const wxChar* CRPCProtocol::GetRequestName()
{
    return m_strRPCName.c_str();
}

BSLERRCODE CRPCProtocol::ParseResponse(CHost* WXUNUSED(pHost), wxString& strResponse)
{
    BSLERRCODE rc = BSLERR_OBJECT_NOT_FOUND;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    oDocument.SetDocument(strResponse);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_SUCCESS == oElement.GetNameHash()) 
        {
            rc = BSLERR_SUCCESS;
        }
        if (BSLXMLTAGHASH_UNAUTHORIZED == oElement.GetNameHash())
        {
            rc = BSLERR_ACCESS_DENIED;
        }
        if (BSLXMLTAGHASH_ERROR == oElement.GetNameHash())
        {
            m_strErrorMessage = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
        }
    }

    return rc;
}

BSLERRCODE CRPCProtocol::ParseResponseAccount(CHost* WXUNUSED(pHost), wxString& strResponse, BSLERRCODE& ulReturnCode, wxString& strReturnMessage, wxString& strAuthenticator)
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
            ulReturnCode = CovertBOINCERRCODEToBSLERRCODE(CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue()));
            rc = BSLERR_SUCCESS;
        }
        if (BSLXMLTAGHASH_ERRORMESSAGE == oElement.GetNameHash()) 
        {
            strReturnMessage = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
            rc = BSLERR_SUCCESS;
        }
        if (BSLXMLTAGHASH_AUTHENTICATOR == oElement.GetNameHash()) 
        {
            strAuthenticator = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
            rc = BSLERR_SUCCESS;
        }
    }

    return rc;
}

BSLERRCODE CRPCProtocol::ResetBuffers()
{
    m_strRequest.Empty();
    m_strResponse.Empty();
    return BSLERR_SUCCESS;
}

BSLERRCODE CRPCProtocol::CovertBOINCERRCODEToBSLERRCODE(wxInt32 iErrorCode)
{
    switch(iErrorCode)
    {
        case 0:
            // BOINC_SUCCESS
            return BSLERR_SUCCESS;
            break;
        case -136:
            // ERR_DB_NOT_FOUND
            return BSLERR_OBJECT_NOT_FOUND;
            break;
        case -137:
            // ERR_DB_NOT_UNIQUE
            return BSLERR_OBJECT_ALREADY_CREATED;
            break;
        case -204:
            // ERR_IN_PROGRESS
            return BSLERR_OPERATION_IN_PROGRESS;
            break;
        case -205:
            // ERR_BAD_EMAIL_ADDR
            return BSLERR_MALFORMED_IDENTITY;
            break;
        case -206:
            // ERR_BAD_PASSWD
            return BSLERR_BAD_IDENTITY_OR_PASSWORD;
            break;
        case -208:
            // ERR_ACCT_CREATION_DISABLED
            return BSLERR_ACCOUNT_CREATION_DISABLED;
            break;
        case -209:
            // ERR_ATTACH_FAIL_INIT
            return BSLERR_INVITE_CODE_REQUIRED;
            break;
    }
    return BSLERR_FAILURE;
}
