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
#include "StateManagerJob.h"

IMPLEMENT_DYNAMIC_CLASS(CStateManagerJob, wxObject);

CStateManagerJob::CStateManagerJob() :
wxObject()
{
}

CStateManagerJob::CStateManagerJob(CStateManagerJob::COMMAND iCommand, CStateManagerJob::RPC iRPC, BSLHOST hHost, wxUint32 uiSequenceNumber) :
wxObject()
{
    m_iCommand = iCommand;
    m_iRPC = iRPC;
    m_hHost = hHost;
    m_uiSequenceNumber = uiSequenceNumber;
}

CStateManagerJob::CStateManagerJob(const CStateManagerJob& job) :
wxObject()
{
    m_iCommand = job.m_iCommand;
    m_iRPC = job.m_iRPC;
    m_hHost = job.m_hHost;
    m_uiSequenceNumber = job.m_uiSequenceNumber;
}

CStateManagerJob::~CStateManagerJob()
{
}

CStateManagerJob::COMMAND CStateManagerJob::GetCommandType()
{
    return m_iCommand;
}

CStateManagerJob::RPC CStateManagerJob::GetRPCType()
{
    return m_iRPC;
}

BSLHOST CStateManagerJob::GetHostHandle()
{
    return m_hHost;
}

wxUint32 CStateManagerJob::GetSequenceNumber()
{
    return m_uiSequenceNumber;
}
