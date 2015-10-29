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
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateEvents.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "RPCProtocol.h"
#include "RPCSetModeOperation.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCSetModeOperation, CRPCProtocol);

CRPCSetModeOperation::CRPCSetModeOperation():
    CRPCProtocol()
{
}

CRPCSetModeOperation::CRPCSetModeOperation(const wxChar* pszRPCName, wxUint32 uiRPCNameLength):
    CRPCProtocol(pszRPCName, uiRPCNameLength)
{
}

CRPCSetModeOperation::~CRPCSetModeOperation()
{
}

BSLERRCODE CRPCSetModeOperation::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, CBSLClient::SETMODE mode, wxUint32 uiDuration)
{
    // Cache parameters so the GetRequest function can use them
    m_Mode = mode;
    m_uiDuration = uiDuration;

    // Execute the RPC
    return CRPCProtocol::Execute(pHost, type);
}

wxString CRPCSetModeOperation::GetRequest()
{
    wxString strRequest;

    strRequest.Printf(
        wxT("%s\n")
        wxT("  <%s>\n")
        wxT("    %s\n")
        wxT("    <duration>%d.0</duration>\n")
        wxT("  </%s>\n")
        wxT("%s\n"),
        GetRequestHeader(),
        GetRequestName(),
        ConvertSetModeToXML(m_Mode),
        m_uiDuration,
        GetRequestName(),
        GetRequestFooter()
    );

    return strRequest;
}

const wxChar* CRPCSetModeOperation::ConvertSetModeToXML(CBSLClient::SETMODE& mode)
{
    switch(mode)
    {
        case CBSLClient::SetModeAlways:
            return wxT("<always/>");
        case CBSLClient::SetModeNever:
            return wxT("<never/>");
        case CBSLClient::SetModeAuto:
            return wxT("<auto/>");
        case CBSLClient::SetModeRestore:
            return wxT("<restore/>");
        default:
            break;
    }
    return wxT("<unknown/>");
}

