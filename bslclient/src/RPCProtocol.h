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

#ifndef _RPCPROTOCOL_H_
#define _RPCPROTOCOL_H_

#include "RPCConnection.h"

class CRPCProtocol: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CRPCProtocol)

public:
    CRPCProtocol();
    CRPCProtocol(const wxChar* pszRPCName, wxUint32 uiRPCNameLength);
    virtual ~CRPCProtocol();

    /// \brief Send the current RPC request to the BOINC client.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] type the type of RPC connection to use.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_NOT_CONNECTED \copybrief BSLERRCODE::BSLERR_CONNECT_NOT_CONNECTED
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_ACCESS_DENIED \copybrief BSLERRCODE::BSLERR_ACCESS_DENIED
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    virtual BSLERRCODE Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type);

    /// \brief Default RPC execution handler for RPCs.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] pRPCConnection the connection to execute the RPC request against.
    /// \param[in] pRPCProfiler the statistics record to update once the RPC has been completed.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_NOT_CONNECTED \copybrief BSLERRCODE::BSLERR_CONNECT_NOT_CONNECTED
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_ACCESS_DENIED \copybrief BSLERRCODE::BSLERR_ACCESS_DENIED
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    virtual BSLERRCODE OnExecute(CHost* pHost, CRPCConnection* pRPCConnection, CRPCProfile* pRPCProfiler);

    /// \brief Returns the desired RPC connection type.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] type the type of RPC connection to use.
    static CRPCConnection* GetConnection(CHost* pHost, CRPCConnection::CONNECTIONTYPE type);

    /// \brief Returns the error message the BOINC client returned when the RPC was executed.
    wxString GetLastError();

    /// \brief Returns the RPC Request.
    virtual wxString GetRequest();
    /// \brief Returns the RPC Request Header.
    virtual const wxChar* GetRequestHeader();
    /// \brief Returns the RPC Request Footer.
    virtual const wxChar* GetRequestFooter();
    /// \brief Returns the RPC Name.
    virtual const wxChar* GetRequestName();

    /// \brief Parse the RPC Response.
    /// \param[in] pHost the host the RPC was issued against.
    /// \param[in] strResponse the RPC response message.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_ACCESS_DENIED \copybrief BSLERRCODE::BSLERR_ACCESS_DENIED
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    virtual BSLERRCODE ParseResponse(CHost* pHost, wxString& strResponse);

    /// \brief Parse the RPC Response (Account Edition).
    /// \param[in] pHost the host the RPC was issued against.
    /// \param[in] strResponse the RPC response message.
    /// \param[out] ulReturnCode the error code returned from the BOINC client.
    /// \param[out] strReturnMessage the error message returned from the BOINC project.
    /// \param[out] strAuthenticator the authenticator on successful completion.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_ACCESS_DENIED \copybrief BSLERRCODE::BSLERR_ACCESS_DENIED
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    virtual BSLERRCODE ParseResponseAccount(CHost* pHost, wxString& strResponse, BSLERRCODE& ulReturnCode, wxString& strReturnMessage, wxString& strAuthenticator);

    /// \brief Reset the request/response buffers.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    virtual BSLERRCODE ResetBuffers();

protected:
    /// \brief Converts a BOINC Error Code to a BOINC Sentinels Error Code.
    BSLERRCODE CovertBOINCERRCODEToBSLERRCODE(wxInt32 iErrorCode);

private:
    wxString m_strRPCName;
    wxString m_strRequest;
    wxString m_strResponse;
    wxString m_strErrorMessage;
};

#endif

///
/// \}
