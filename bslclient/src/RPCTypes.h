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

///
/// \defgroup RPCProtocol RPC Protocol
/// \{

#ifndef _RPCTYPES_H_
#define _RPCTYPES_H_

#include "RPCProtocol.h"
#include "RPCProjectOperation.h"
#include "RPCSetModeOperation.h"
#include "RPCTaskInstanceOperation.h"
#include "RPCTransferOperation.h"
#include "RPCAuthorize.h"
#include "RPCConnection.h"
#include "RPCCreateAccount.h"
#include "RPCCreateAccountPoll.h"
#include "RPCExchangeVersions.h"
#include "RPCLookupAccount.h"
#include "RPCLookupAccountPoll.h"
#include "RPCManager.h"
#include "RPCNetworkAvailable.h"
#include "RPCProjectAllowMoreWork.h"
#include "RPCProjectAttach.h"
#include "RPCProjectAttachPoll.h"
#include "RPCProjectDetach.h"
#include "RPCProjectDetachWhenDone.h"
#include "RPCProjectDontDetachWhenDone.h"
#include "RPCProjectNoMoreWork.h"
#include "RPCProjectReset.h"
#include "RPCProjectResume.h"
#include "RPCProjectSuspend.h"
#include "RPCProjectUpdate.h"
#include "RPCRunBenchmarks.h"
#include "RPCSetModeCPU.h"
#include "RPCSetModeGPU.h"
#include "RPCSetModeNetwork.h"
#include "RPCShutdown.h"
#include "RPCSyncHost.h"
#include "RPCSyncHostStatus.h"
#include "RPCSyncMessages.h"
#include "RPCSyncNotifications.h"
#include "RPCSyncProjectList.h"
#include "RPCSyncProjectStatistics.h"
#include "RPCSyncProjects.h"
#include "RPCSyncState.h"
#include "RPCSyncTaskInstances.h"
#include "RPCSyncTransfers.h"
#include "RPCTaskInstanceAbort.h"
#include "RPCTaskInstanceResume.h"
#include "RPCTaskInstanceSuspend.h"
#include "RPCTransferAbort.h"
#include "RPCTransferRetry.h"

#endif

///
/// \}
