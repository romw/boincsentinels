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
#include "bslversion.h"
#include "Instance.h"
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateEvents.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "RPCProtocol.h"
#include "RPCExchangeVersions.h"

#define BSLXMLTAGHASH_MAJOR \
    0x4a3554b4
#define BSLXMLTAGHASH_MINOR \
    0xd09ad130
#define BSLXMLTAGHASH_RELEASE \
    0x8f63473c


IMPLEMENT_DYNAMIC_CLASS(CRPCExchangeVersions, CRPCProtocol);

CRPCExchangeVersions::CRPCExchangeVersions():
    CRPCProtocol(wxT("exchange_versions"), sizeof(wxT("exchange_versions")))
{
}

CRPCExchangeVersions::~CRPCExchangeVersions()
{
}

BSLERRCODE CRPCExchangeVersions::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type)
{
    CRPCConnection* pConnection = NULL;
    CRPCProfile* pProfile = NULL;

    // Find/Create the RPC Statistics record for this RPC type.
    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindRPCProfile(GetClassInfo()->GetClassName(), &pProfile))
    {
        pProfile = new CRPCProfile(GetClassInfo()->GetClassName());
        pHost->AddRPCProfile(pProfile);
    }
    wxASSERT(pProfile);

    // Find the connection for use
    pConnection = GetConnection(pHost, type);
    wxASSERT(pProfile);

    // Execute RPC
    return OnExecute(pHost, pConnection, pProfile);
}

wxString CRPCExchangeVersions::GetRequest()
{
    wxString strRequest;

    strRequest.Printf(
        wxT("%s\n")
        wxT("  <%s>\n")
        wxT("    <major>%d</major>\n")
        wxT("    <minor>%d</minor>\n")
        wxT("    <release>%d</release>\n")
        wxT("  </%s>\n")
        wxT("%s\n"),
        GetRequestHeader(),
        GetRequestName(),
        BOINCCOMPAT_VERSION_MAJOR,
        BOINCCOMPAT_VERSION_MINOR,
        BOINCCOMPAT_VERSION_RELEASE,
        GetRequestName(),
        GetRequestFooter()
    );

    return strRequest;
}

BSLERRCODE CRPCExchangeVersions::ParseResponse(CHost* pHost, wxString& strResponse)
{
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;
    wxUint32 ulMajor;
    wxUint32 ulMinor;
    wxUint32 ulRelease;

    oDocument.SetDocument(strResponse);

    oDictionary.Parse(oDocument, 0);

    ulMajor = CBSLXMLConverterEx::ConvertToUI32(oDictionary.FindElement(BSLXMLTAGHASH_MAJOR)->GetValue());
    ulMinor = CBSLXMLConverterEx::ConvertToUI32(oDictionary.FindElement(BSLXMLTAGHASH_MINOR)->GetValue());
    ulRelease = CBSLXMLConverterEx::ConvertToUI32(oDictionary.FindElement(BSLXMLTAGHASH_RELEASE)->GetValue());

    // Store the host version for later use
    pHost->SetClientVersion(ulMajor, ulMinor, ulRelease);

    if (!IsCompatible(ulMajor, ulMinor, ulRelease)) return BSLERR_CONNECT_VERSIONINCOMPATIBILITY_ERROR;
    return BSLERR_SUCCESS;
}

bool CRPCExchangeVersions::IsCompatible(wxUint32 uiMajor, wxUint32 uiMinor, wxUint32 uiRelease)
{
    if (uiMajor >= BOINCCOMPAT_VERSION_MAJOR) return true;
    if (uiMajor < BOINCCOMPAT_VERSION_MAJOR) return false;
    if (uiMinor >= BOINCCOMPAT_VERSION_MINOR) return true;
    if (uiMinor < BOINCCOMPAT_VERSION_MINOR) return false;
    if (uiRelease >= BOINCCOMPAT_VERSION_RELEASE) return true;
    return false;
}
