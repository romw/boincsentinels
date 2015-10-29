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

#ifndef _RPCAUTHORIZE_H_
#define _RPCAUTHORIZE_H_

///
/// \brief Handles authentication with the BOINC client software.
/// \details \{
/// Unlike the other BOINC GUI RPCs, authentication is treated like other
/// challenge/response authentication mechanisms.  First send an RPC to
/// get the challenge and then send another RPC to respond to the challenge.\n
/// \n
/// The following block illustrates the challenge request:\n
/// \code
/// <boinc_gui_rpc_request>
///   <auth1/>
/// </boinc_gui_rpc_request>
/// \endcode
/// The following block illustrates the challenge response:\n
/// \code
/// <boinc_gui_rpc_reply>
///   <nonce>1315869996.834662</nonce>
/// </boinc_gui_rpc_reply>
/// \endcode
/// Next, the password needs to be concatenated with the nonce and then run through
/// the MD5 hashing algorithm.\n
/// \code
/// char* hash = md5sum("1315869996.834662test");
/// \endcode
/// The following block illustrates the response request:\n
/// \code
/// <boinc_gui_rpc_request>
///   <auth2>
///     <nonce_hash>3ec02238b1928f405f171c2cf7d6349d</nonce_hash>
///   </auth2>
/// </boinc_gui_rpc_request>
/// \endcode
/// The following block illustrates the response response:\n
/// \code
/// <boinc_gui_rpc_reply>
///   <authorized/>
/// </boinc_gui_rpc_reply>
/// \endcode
/// \}
///
class CRPCAuthorize: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CRPCAuthorize)

public:
    CRPCAuthorize();
    ~CRPCAuthorize();

    /// \brief Send the Authorization RPC request to the BOINC client.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] type the type of RPC connection to use.
    /// \param[in] strPassword the password to use to authorize a connection.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_CONNECT_AUTHENTICATION_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_AUTHENTICATION_ERROR
    BSLERRCODE Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, wxString strPassword);

    /// \brief Default RPC execution handler for RPCs.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] pRPCConnection the connection to execute the RPC request against.
    /// \param[in] pRPCProfiler the statistics record to update once the RPC has been completed.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_CONNECT_AUTHENTICATION_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_AUTHENTICATION_ERROR
    BSLERRCODE OnAuth1Execute(CHost* pHost, CRPCConnection* pRPCConnection, CRPCProfile* pRPCProfiler);

    /// \brief Default RPC execution handler for RPCs.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] pRPCConnection the connection to execute the RPC request against.
    /// \param[in] pRPCProfiler the statistics record to update once the RPC has been completed.
    /// \param[in] strPassword the password to use to authorize a connection.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_CONNECT_AUTHENTICATION_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_AUTHENTICATION_ERROR
    BSLERRCODE OnAuth2Execute(CHost* pHost, CRPCConnection* pRPCConnection, CRPCProfile* pRPCProfiler, wxString& strPassword);

    /// \brief Parse the RPC Response and apply it to the host state.
    /// \param[in] pHost the host the RPC was issued against.
    /// \param[in] strResponse the RPC response.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_AUTHENTICATION_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_AUTHENTICATION_ERROR
    BSLERRCODE OnParseAuth1Response(CHost* pHost, wxString& strResponse);

    /// \brief Parse the RPC Response and apply it to the host state.
    /// \param[in] pHost the host the RPC was issued against.
    /// \param[in] strResponse the RPC response.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_AUTHENTICATION_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_AUTHENTICATION_ERROR
    BSLERRCODE OnParseAuth2Response(CHost* pHost, wxString& strResponse);

private:
    wxString m_strRequest;
    wxString m_strResponse;
    wxString m_strNonce;
};

#endif

///
/// \}
