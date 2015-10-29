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
#include "RPCManager.h"
#include "RPCProtocol.h"
#include "RPCAuthorize.h"
#include "RPCExchangeVersions.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCManager, wxObject);

CRPCManager::CRPCManager()
{
}

CRPCManager::~CRPCManager()
{
}

BSLERRCODE CRPCManager::OnConnect(CHost* pHost)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    wxSocketError iSocketError;
    CRPCConnection* pOnDemandConnection = pHost->m_pRPCOnDemand;
    CRPCConnection* pStatusUpdateConnection = pHost->m_pRPCStatusUpdate;
    CRPCAuthorize rpcAuthorizeOnDemand;
    CRPCAuthorize rpcAuthorizeStatusUpdate;
    CRPCExchangeVersions rpcExchangeVersionsOnDemand;
    wxString strConnectionName;
    wxString strConnectionPassword;
    long lConnectionPort;
    wxIPV4address addr;

    // Begin the connection process
    pHost->SetConnectionState(CHost::ConnectionStateConnecting);

    // Lookup the connection settings
    pHost->GetConnectionProperties(strConnectionName, strConnectionPassword, lConnectionPort);

    // Determine if we are connecting to the local host, if so, use the loop back
    // adapter address.
    if (GetState()->IsLocalHostName(strConnectionName))
    {
        strConnectionName = wxT("127.0.0.1");
    }

    // Populate the IP address abstraction class
    addr.Hostname(strConnectionName);
    addr.Service(lConnectionPort);

    // Setup the OnDemand connection
    pOnDemandConnection->Lock();
    if (!pOnDemandConnection->Connect(addr))
    {
        iSocketError = pOnDemandConnection->LastError();
        if (wxSOCKET_NOHOST == iSocketError)
        {
            rc = BSLERR_CONNECT_HOST_NOT_FOUND;
        }
        else if (wxSOCKET_INVPORT == iSocketError)
        {
            rc = BSLERR_CONNECT_PORT_NOT_FOUND;
        }
        else if (wxSOCKET_TIMEDOUT == iSocketError)
        {
            rc = BSLERR_CONNECT_TIME_OUT;
        }
        else if (wxSOCKET_IOERR == iSocketError)
        {
            rc = BSLERR_CONNECT_IO_ERROR;
        }
        else
        {
            rc = BSLERR_CONNECT_ERROR;
        }
        pOnDemandConnection->Unlock();
        goto CONNECTION_ERROR;
    }
    pOnDemandConnection->Unlock();

    // Setup the StatusUpdate connection
    pStatusUpdateConnection->Lock();
    if (!pStatusUpdateConnection->Connect(addr))
    {
        iSocketError = pStatusUpdateConnection->LastError();
        if (wxSOCKET_NOHOST == iSocketError)
        {
            rc = BSLERR_CONNECT_HOST_NOT_FOUND;
        }
        else if (wxSOCKET_INVPORT == iSocketError)
        {
            rc = BSLERR_CONNECT_PORT_NOT_FOUND;
        }
        else if (wxSOCKET_TIMEDOUT == iSocketError)
        {
            rc = BSLERR_CONNECT_TIME_OUT;
        }
        else if (wxSOCKET_IOERR == iSocketError)
        {
            rc = BSLERR_CONNECT_IO_ERROR;
        }
        else
        {
            rc = BSLERR_CONNECT_ERROR;
        }
        pStatusUpdateConnection->Unlock();
        goto CONNECTION_ERROR;
    }
    pStatusUpdateConnection->Unlock();

    // Authenticate the OnDemand connection
    rc = rpcAuthorizeOnDemand.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand, strConnectionPassword);
    if (BSLERR_SUCCESS != rc) goto CONNECTION_ERROR;

    // Authenticate the StatusUpdate connection
    rc = rpcAuthorizeStatusUpdate.Execute(pHost, CRPCConnection::ConnectionTypeStatusUpdate, strConnectionPassword);
    if (BSLERR_SUCCESS != rc) goto CONNECTION_ERROR;

    // Exchange version information
    rc = rpcExchangeVersionsOnDemand.Execute(pHost, CRPCConnection::ConnectionTypeOnDemand);

CONNECTION_ERROR:
    GetState()->ClearMemory((wxChar*)strConnectionPassword.wx_str(), strConnectionPassword.size());
    strConnectionPassword.Empty();

    if (BSLERR_SUCCESS == rc)
    {
        pHost->SetConnectionState(CHost::ConnectionStateConnected);
    }
    else
    {
        if (pOnDemandConnection->IsConnected())
        {
            pOnDemandConnection->Close();
        }
        if (pStatusUpdateConnection->IsConnected())
        {
            pStatusUpdateConnection->Close();
        }

        if (BSLERR_CONNECT_AUTHENTICATION_ERROR == rc)
        {
            pHost->SetConnectionState(CHost::ConnectionStateAuthenticationFailure);
        }
        else if (BSLERR_CONNECT_VERSIONINCOMPATIBILITY_ERROR == rc)
        {
            pHost->SetConnectionState(CHost::ConnectionStateVersionIncompatibleFailure);
        }
        else
        {
            pHost->SetConnectionState(CHost::ConnectionStateConnectFailure);
        }
    }

    return rc;
}

BSLERRCODE CRPCManager::OnDisconnect(CHost* pHost)
{
    pHost->SetConnectionState(CHost::ConnectionStateDisconnecting);

    pHost->SetConnectionState(CHost::ConnectionStateDisconnected);
    return BSLERR_SUCCESS;
}

