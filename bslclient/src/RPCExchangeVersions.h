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

#ifndef _RPCEXCHANGEVERSIONS_H_
#define _RPCEXCHANGEVERSIONS_H_

///
/// \brief Handles version exchange with the BOINC client software.
/// \details \{
/// The following block illustrates the request:\n
/// \code
/// <boinc_gui_rpc_request>
///   <exchange_versions>
///     <major>6</major>
///     <minor>13</minor>
///     <release>3</release>
///   </exchange_versions>
/// </boinc_gui_rpc_request>
/// \endcode
/// The following block illustrates the response:\n
/// \code
/// <boinc_gui_rpc_reply>
///   <server_version>
///     <major>6</major>
///     <minor>13</minor>
///     <release>3</release>
///   </server_version>
/// </boinc_gui_rpc_reply>
/// \endcode
/// \}
///
class CRPCExchangeVersions: public CRPCProtocol
{
    DECLARE_DYNAMIC_CLASS(CRPCExchangeVersions)

public:
    CRPCExchangeVersions();
    ~CRPCExchangeVersions();

    /// \copydoc CRPCProtocol::Execute()
    BSLERRCODE Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type);

    /// \copydoc CRPCProtocol::GetRequest()
    wxString GetRequest();

    /// \copydoc CRPCProtocol::ParseResponse()
    BSLERRCODE ParseResponse(CHost* pHost, wxString& strResponse);

private:
    bool IsCompatible(wxUint32 uiMajor, wxUint32 uiMinor, wxUint32 uiRelease);
};

#endif

///
/// \}
