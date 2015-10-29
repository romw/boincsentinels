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
/// \defgroup StateManager State Manager
/// \{

#ifndef _STATEMANAGERJOB_H_
#define _STATEMANAGERJOB_H_

class CStateManagerJob: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CStateManagerJob)

public:

    enum PRIORITY
    {
        /// \brief
        PriorityHigh,
        /// \brief
        PriorityAboveNormal,
        /// \brief
        PriorityNormal,
        /// \brief
        PriorityBelowNormal,
        /// \brief
        PriorityLow,
        /// \brief
        PriorityIdle
    };

    enum COMMAND
    {
        /// \brief
        CommandStart,
        /// \brief
        CommandConnect,
        /// \brief
        CommandDisconnect,
        /// \brief
        CommandCollectGarbage,
        /// \brief
        CommandRPC,
        /// \brief
        CommandStop
    };

    enum RPC
    {
        /// \brief
        RPCUnknown,
        /// \brief
        RPCHostUpdate,
        /// \brief
        RPCHostStatusUpdate,
        /// \brief
        RPCMessagesUpdate,
        /// \brief
        RPCNotificationsUpdate,
        /// \brief
        RPCProjectListUpdate,
        /// \brief
        RPCProjectsUpdate,
        /// \brief
        RPCProjectStatisticsUpdate,
        /// \brief
        RPCStateUpdate,
        /// \brief
        RPCTaskInstancesUpdate,
        /// \brief
        RPCTransfersUpdate
    };

    CStateManagerJob();
    CStateManagerJob(COMMAND iCommand, RPC iRPC = RPCUnknown, BSLHOST hHost = NULL, wxUint32 uiSequenceNumber = 0);
    CStateManagerJob(const CStateManagerJob& job);
    ~CStateManagerJob();

    COMMAND GetCommandType();
    RPC GetRPCType();
    BSLHOST GetHostHandle();
    wxUint32 GetSequenceNumber();

private:
    COMMAND m_iCommand;
    RPC m_iRPC;
    BSLHOST m_hHost;
    wxUint32 m_uiSequenceNumber;
};

#endif

///
/// \}

