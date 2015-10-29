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

#ifndef _RPCTRANSFEROPERATION_H_
#define _RPCTRANSFEROPERATION_H_

class CRPCTransferOperation: public CRPCProtocol
{
    DECLARE_DYNAMIC_CLASS(CRPCTransferOperation)

public:
    CRPCTransferOperation();
    CRPCTransferOperation(const wxChar* pszRPCName, wxUint32 uiRPCNameLength);
    virtual ~CRPCTransferOperation();

    /// \brief Send the current RPC request to the BOINC client.
    /// \param[in] pHost the host to issue the RPC against.
    /// \param[in] type the type of RPC connection to use.
    /// \param[in] pProject the project to perform the operation on.
    /// \param[in] pTransfer the transfer to perform the operation on.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_CONNECT_NOT_CONNECTED \copybrief BSLERRCODE::BSLERR_CONNECT_NOT_CONNECTED
    /// \retval BSLERR_CONNECT_IO_ERROR \copybrief BSLERRCODE::BSLERR_CONNECT_IO_ERROR
    /// \retval BSLERR_ACCESS_DENIED \copybrief BSLERRCODE::BSLERR_ACCESS_DENIED
    /// \retval BSLERR_OBJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_OBJECT_NOT_FOUND
    virtual BSLERRCODE Execute(CHost* pHost, CRPCConnection::CONNECTIONTYPE type, CBSLProject* pProject, CBSLTransfer* pTransfer);

    /// \copydoc CRPCProtocol::GetRequest()
    virtual wxString GetRequest();

private:
    wxString m_strProjectURL;
    wxString m_strName;
};

#endif

///
/// \}
