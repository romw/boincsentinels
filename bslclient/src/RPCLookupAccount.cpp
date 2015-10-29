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
#include "RPCLookupAccount.h"
#include "wxMD5.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCLookupAccount, CRPCProtocol);

CRPCLookupAccount::CRPCLookupAccount():
    CRPCProtocol(wxT("lookup_account"), sizeof(wxT("lookup_account")))
{
}

CRPCLookupAccount::~CRPCLookupAccount()
{
}

BSLERRCODE CRPCLookupAccount::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, wxString& strProjectURL, wxString& strIdentifier, wxString& strPassword)
{
    // Cache parameters so the GetRequest function can use them
    m_strProjectURL = strProjectURL;
    m_strIdentifier = strIdentifier;
    m_strPassword = strPassword;

    // Execute the RPC
    return CRPCProtocol::Execute(pHost, type);
}

wxString CRPCLookupAccount::GetRequest()
{
    wxString strRequest;
    wxString strPasswordPreHash;
    wxString strPasswordHash;

    strPasswordPreHash = m_strPassword + m_strIdentifier;

    strPasswordHash = wxMD5::GetMD5(strPasswordPreHash);

    strRequest.Printf(
        wxT("%s\n")
        wxT("  <%s>\n")
        wxT("    <url>%s</url>\n")
        wxT("    <email_addr>%s</email_addr>\n")
        wxT("    <passwd_hash>%s</passwd_hash>\n")
        wxT("  </%s>\n")
        wxT("%s\n"),
        GetRequestHeader(),
        GetRequestName(),
        m_strProjectURL.c_str(),
        m_strIdentifier.Lower().c_str(),
        strPasswordPreHash.c_str(),
        GetRequestName(),
        GetRequestFooter()
    );

    // Overwrite the password in memory before leaving the function.
    GetState()->ClearMemory((wxChar*)m_strPassword.wx_str(), m_strPassword.size());
    m_strPassword.Empty();

    // Overwrite the password pre-hash in memory before leaving the function.
    GetState()->ClearMemory((wxChar*)strPasswordPreHash.wx_str(), strPasswordPreHash.size());
    strPasswordPreHash.Empty();

    // Overwrite the password hash in memory before leaving the function.
    GetState()->ClearMemory((wxChar*)strPasswordHash.wx_str(), strPasswordHash.size());
    strPasswordHash.Empty();

    return strRequest;
}
