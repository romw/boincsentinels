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
#include "RPCAuthorize.h"
#include "wxMD5.h"

#define BSLXMLTAGHASH_NONCE \
    0x21f73c82
#define BSLXMLTAGHASH_AUTHORIZED \
    0x979cb9c6

IMPLEMENT_DYNAMIC_CLASS(CRPCAuthorize, wxObject);

CRPCAuthorize::CRPCAuthorize() :
wxObject()
{
}

CRPCAuthorize::~CRPCAuthorize()
{
}

BSLERRCODE CRPCAuthorize::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, wxString strPassword)
{
    CRPCConnection* pConnection = NULL;
    CRPCProfile* pAuth1Profile = NULL;
    CRPCProfile* pAuth2Profile = NULL;
    wxString strAuth1 = wxT("CRPCAuthorize1");
    wxString strAuth2 = wxT("CRPCAuthorize2");
    BSLERRCODE rc;

    // Find/Create the RPC Profile record for these RPC types.
    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindRPCProfile(strAuth1, &pAuth1Profile))
    {
        pAuth1Profile = new CRPCProfile(strAuth1);
        pHost->AddRPCProfile(pAuth1Profile);
    }
    wxASSERT(pAuth1Profile);
    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindRPCProfile(strAuth2, &pAuth2Profile))
    {
        pAuth2Profile = new CRPCProfile(strAuth2);
        pHost->AddRPCProfile(pAuth2Profile);
    }
    wxASSERT(pAuth2Profile);

    // Lock the connection for use
    pConnection = CRPCProtocol::GetConnection(pHost, type);
    wxASSERT(pConnection);

    // Execute RPCs
    pConnection->Lock();
    rc = OnAuth1Execute(pHost, pConnection, pAuth1Profile);
    if (BSLERR_SUCCESS == rc)
    {
        rc = OnAuth2Execute(pHost, pConnection, pAuth2Profile, strPassword);
    }
    pConnection->Unlock();

    return rc;
}

BSLERRCODE CRPCAuthorize::OnAuth1Execute(CHost *pHost, CRPCConnection *pRPCConnection, CRPCProfile *pRPCProfiler)
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

    // Reset the buffers
    m_strRequest.Empty();
    m_strResponse.Empty();

    // Record the time stamp for this RPC
    dtLastRequestTime = wxDateTime::UNow();

    // Start the stop watch for the total duration
#ifdef __WXDEBUG__
    swStopWatchTotal.Start(0);
#endif

    // Preallocate request and response buffers, enlarge the buffers by 25% in case of growth.
    m_strRequest.Alloc(pRPCProfiler->GetRequestSize() * 1.25);
    m_strResponse.Alloc(pRPCProfiler->GetResponseSize() * 1.25);

    // Construct the RPC Auth1 Request Message
    m_strRequest.Printf(
        wxT("<boinc_gui_rpc_request>\n")
        wxT("  <auth1/>\n")
        wxT("</boinc_gui_rpc_request>\n")
    );

    // Write the request to the client socket
#ifdef __WXDEBUG__
    swStopWatch.Start(0);
#endif
    rc = pRPCConnection->WriteRPCMessage(m_strRequest);
#ifdef __WXDEBUG__
    tsRequestDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
    if (!rc)
    {
        // Read the response from the client socket
#ifdef __WXDEBUG__
        swStopWatch.Start(0);
#endif
        rc = pRPCConnection->ReadRPCMessage(m_strResponse);
#ifdef __WXDEBUG__
        tsResponseDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
        if (!rc)
        {
            // Parse the response from the client
#ifdef __WXDEBUG__
            swStopWatch.Start(0);
#endif
            rc = OnParseAuth1Response(pHost, m_strResponse);
#ifdef __WXDEBUG__
            tsParseDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
        }
    }

    // Stop the stop watch for the total duration
#ifdef __WXDEBUG__
    tsTotalDuration = wxTimeSpan(0, 0, 0, swStopWatchTotal.Time());
#endif

    // Update RPC Profile
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

BSLERRCODE CRPCAuthorize::OnParseAuth1Response(CHost* WXUNUSED(pHost), wxString& strResponse)
{
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;
    CBSLXMLElementEx* pElement;

    oDocument.SetDocument(strResponse);

    oDictionary.Parse(oDocument, 0);

    pElement = oDictionary.FindElement(BSLXMLTAGHASH_NONCE);

    m_strNonce = CBSLXMLConverterEx::ConvertToString(pElement->GetValue(), pElement->GetValueLength());

    if (m_strNonce.empty()) return BSLERR_CONNECT_AUTHENTICATION_ERROR;
    return BSLERR_SUCCESS;
}

BSLERRCODE CRPCAuthorize::OnAuth2Execute(CHost *pHost, CRPCConnection *pRPCConnection, CRPCProfile *pRPCProfiler, wxString& strPassword)
{
    BSLERRCODE rc;
    wxDateTime dtLastRequestTime;
    wxUint64 ullRequestSize;
    wxUint64 ullResponseSize;
    wxString strNonce;
    wxString strNonceHash;
#ifdef __WXDEBUG__
    wxStopWatch swStopWatch;
    wxStopWatch swStopWatchTotal;
    wxTimeSpan tsRequestDuration;
    wxTimeSpan tsResponseDuration;
    wxTimeSpan tsParseDuration;
    wxTimeSpan tsTotalDuration;
#endif

    // Reset the buffers
    m_strRequest.Empty();
    m_strResponse.Empty();

    // Record the time stamp for this RPC
    dtLastRequestTime = wxDateTime::Now();

    // Start the stop watch for the total duration
#ifdef __WXDEBUG__
    swStopWatchTotal.Start(0);
#endif

    // Preallocate request and response buffers
    m_strRequest.Alloc(pRPCProfiler->GetRequestSize() * 1.25);
    m_strResponse.Alloc(pRPCProfiler->GetResponseSize() * 1.25);

    // Construct the RPC Auth2 Request Message
    strNonce = m_strNonce + strPassword;
    strNonceHash = wxMD5::GetMD5(strNonce);

    m_strRequest.Printf(
        wxT("<boinc_gui_rpc_request>\n")
        wxT("  <auth2>\n")
        wxT("    <nonce_hash>%s</nonce_hash>\n")
        wxT("  </auth2>\n")
        wxT("</boinc_gui_rpc_request>\n"),
        strNonceHash.c_str()
    );

    // Write the request to the client socket
#ifdef __WXDEBUG__
    swStopWatch.Start(0);
#endif
    rc = pRPCConnection->WriteRPCMessage(m_strRequest);
#ifdef __WXDEBUG__
    tsRequestDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
    if (!rc)
    {
        // Read the response from the client socket
#ifdef __WXDEBUG__
        swStopWatch.Start(0);
#endif
        rc = pRPCConnection->ReadRPCMessage(m_strResponse);
#ifdef __WXDEBUG__
        tsResponseDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
        if (!rc)
        {
            // Parse the response from the client
#ifdef __WXDEBUG__
            swStopWatch.Start(0);
#endif
            rc = OnParseAuth2Response(pHost, m_strResponse);
#ifdef __WXDEBUG__
            tsParseDuration = wxTimeSpan(0, 0, 0, swStopWatch.Time());
#endif
        }
    }

    // Stop the stop watch for the total duration
#ifdef __WXDEBUG__
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

BSLERRCODE CRPCAuthorize::OnParseAuth2Response(CHost* WXUNUSED(pHost), wxString& strResponse)
{
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx* pElement;
    CBSLXMLDictionaryEx oDictionary;
    bool bAuthorized = false;

    oDocument.SetDocument(strResponse);

    oDictionary.Parse(oDocument, 0);

    pElement = oDictionary.FindElement(BSLXMLTAGHASH_AUTHORIZED);
    if (pElement)
    {
        bAuthorized = CBSLXMLConverterEx::ConvertToBool(pElement->GetValue());
    }

    if (!bAuthorized) return BSLERR_CONNECT_AUTHENTICATION_ERROR;
    return BSLERR_SUCCESS;
}
