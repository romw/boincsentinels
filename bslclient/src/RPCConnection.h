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

#ifndef _RPCCONNECTION_H_
#define _RPCCONNECTION_H_

class CSocket;

class CConnectionLockerData
{
    DECLARE_NO_COPY_CLASS(CConnectionLockerData)

    friend class CConnectionLocker;

public:
    CConnectionLockerData()
    {
        m_pConnectionLocker = new wxMutex();
        wxASSERT(m_pConnectionLocker);
    }

    ~CConnectionLockerData()
    {
        delete m_pConnectionLocker;
        m_pConnectionLocker = NULL;
    }

protected:
    wxMutex* m_pConnectionLocker;
};

class CRPCConnection: public CConnectionLockerData
{
    friend class CRPCManager;

public:

    enum CONNECTIONTYPE
    {
        ConnectionTypeStatusUpdate,
        ConnectionTypeOnDemand
    };

    CRPCConnection(CONNECTIONTYPE type);
    ~CRPCConnection();

    void Close();
    bool Connect(wxIPV4address& address);
    bool IsConnected() const;
    wxSocketError LastError() const;

    BSLERRCODE ReadRPCMessage(wxString& strMessage);
    BSLERRCODE WriteRPCMessage(wxString& strMessage);

    wxMutexError Lock();
    wxMutexError Unlock();

private:
    CONNECTIONTYPE m_Type;
    CSocket*  m_pSocket;
    wxCSConv* m_pConverter;
    char      m_NarrowCharBuffer[32768];
#if defined(__WXMSW__) && defined(_UNICODE)
    wxChar    m_WideCharBuffer[32768];
#endif
};

#endif

///
/// \}
