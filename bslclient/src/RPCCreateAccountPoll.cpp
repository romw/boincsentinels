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
#include "RPCCreateAccountPoll.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCCreateAccountPoll, CRPCProtocol);

CRPCCreateAccountPoll::CRPCCreateAccountPoll():
    CRPCProtocol(wxT("create_account_poll"), sizeof(wxT("create_account_poll")))
{
}

CRPCCreateAccountPoll::~CRPCCreateAccountPoll()
{
}

BSLERRCODE CRPCCreateAccountPoll::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, BSLERRCODE& uiReturnCode, std::vector<wxString>& oMessages, wxString& strAuthenticator)
{
    BSLERRCODE rc = BSLERR_FAILURE;

    // Execute RPC
    rc = CRPCProtocol::Execute(pHost, type);

    // Return the values
    uiReturnCode = m_uiReturnCode;
    strAuthenticator = m_strAuthenticator;
    oMessages.push_back(m_strReturnMessage);

    return rc;
}

BSLERRCODE CRPCCreateAccountPoll::ParseResponse(CHost* pHost, wxString& strResponse)
{
    return CRPCProtocol::ParseResponseAccount(pHost, strResponse, m_uiReturnCode, m_strReturnMessage, m_strAuthenticator);
}

