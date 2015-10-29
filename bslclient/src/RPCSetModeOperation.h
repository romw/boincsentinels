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

#ifndef _RPCSETMODEOPERATION_H_
#define _RPCSETMODEOPERATION_H_

class CRPCSetModeOperation: public CRPCProtocol
{
    DECLARE_DYNAMIC_CLASS(CRPCSetModeOperation)

public:
    CRPCSetModeOperation();
    CRPCSetModeOperation(const wxChar* pszRPCName, wxUint32 uiRPCNameLength);
    virtual ~CRPCSetModeOperation();

    /// \brief Send the current RPC request to the BOINC client.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] type the type of RPC connection to use.
    /// \param[in] mode which mode to change.
    /// \param[in] uiDuration how long that mode should stay in effect, 0 means permanent.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_NOT_CONNECTED \copybrief BSLERRCODE::BSLERR_CONNECT_NOT_CONNECTED
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_ACCESS_DENIED \copybrief BSLERRCODE::BSLERR_ACCESS_DENIED
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    virtual BSLERRCODE Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, CBSLClient::SETMODE mode, wxUint32 uiDuration);

    /// \copydoc CRPCProtocol::GetRequest()
    virtual wxString GetRequest();

private:
    /// \brief Converts a BOINC Sentinels set mode to an XML shred used by BOINC.
    const wxChar* ConvertSetModeToXML(CBSLClient::SETMODE& mode);

    CBSLClient::SETMODE m_Mode;
    wxUint32 m_uiDuration;
};

#endif

///
/// \}
