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
#include "RPCTransferOperation.h"
#include "RPCTransferAbort.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCTransferAbort, CRPCTransferOperation);

CRPCTransferAbort::CRPCTransferAbort():
    CRPCTransferOperation(wxT("abort_file_transfer"), sizeof(wxT("abort_file_transfer")))
{
}

CRPCTransferAbort::~CRPCTransferAbort()
{
}
