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
#include "RPCProjectAttach.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCProjectAttach, CRPCProtocol);

CRPCProjectAttach::CRPCProjectAttach():
    CRPCProtocol(wxT("project_attach"), sizeof(wxT("project_attach")))
{
}

CRPCProjectAttach::~CRPCProjectAttach()
{
}

BSLERRCODE CRPCProjectAttach::Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, wxString& strProjectURL, wxString& strProjectName, wxString& strAuthenticator)
{
    // Cache parameters so the GetRequest function can use them
    m_strProjectURL = strProjectURL;
    m_strProjectName = strProjectName;
    m_strAuthenticator = strAuthenticator;

    // Execute the RPC
    return CRPCProtocol::Execute(pHost, type);
}

wxString CRPCProjectAttach::GetRequest()
{
    wxString strRequest;

    strRequest.Printf(
        wxT("%s\n")
        wxT("  <%s>\n")
        wxT("    <project_url>%s</project_url>\n")
        wxT("    <project_name>%s</project_name>\n")
        wxT("    <authenticator>%s</authenticator>\n")
        wxT("  </%s>\n")
        wxT("%s\n"),
        GetRequestHeader(),
        GetRequestName(),
        m_strProjectURL.c_str(),
        m_strProjectName.c_str(),
        m_strAuthenticator.c_str(),
        GetRequestName(),
        GetRequestFooter()
    );

    return strRequest;
}
