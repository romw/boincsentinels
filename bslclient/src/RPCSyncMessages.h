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

#ifndef _RPCSYNCMESSAGES_H_
#define _RPCSYNCMESSAGES_H_

class CRPCSyncMessages: public CRPCProtocol
{
    DECLARE_DYNAMIC_CLASS(CRPCSyncMessages)

public:
    CRPCSyncMessages();
    ~CRPCSyncMessages();

    /// \brief Synchronize the messages with the BOINC client.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] type the type of RPC connection to use.
    /// \param[in] uiSequenceNumber the sequence number of last message received.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_NOT_CONNECTED \copybrief BSLERRCODE::BSLERR_CONNECT_NOT_CONNECTED
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_ACCESS_DENIED \copybrief BSLERRCODE::BSLERR_ACCESS_DENIED
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    BSLERRCODE Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, wxUint32 uiSequenceNumber);

    /// \copydoc CRPCProtocol::GetRequest()
    wxString GetRequest();

    /// \copydoc CRPCProtocol::ParseResponse()
    BSLERRCODE ParseResponse(CHost* pHost, wxString& strResponse);

private:
    wxUint32 m_uiSequenceNumber;
};

#endif

///
/// \}
