// BOINC Sentinels.
// https://projects.romwnet.org/boincsentinels
// Copyright (C) 2009-2013 Rom Walton
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
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateEvents.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "RPCManager.h"
#include "RPCConnection.h"


class CSocket
{
public:

    CSocket()
    {
        m_fd = wxSOCKET_UNINIT;
        m_bConnected = false;
        m_Error = wxSOCKET_NOERROR;
        m_uiLastCount = 0;
        memset(&m_addr, 0, sizeof(sockaddr_in));
    }

    ~CSocket()
    {
        if (m_fd != wxSOCKET_UNINIT)
        {
            Close();
        }
        m_bConnected = false;
        m_Error = wxSOCKET_NOERROR;
        m_uiLastCount = 0;
        memset(&m_addr, 0, sizeof(sockaddr_in));
    }

    void Close()
    {
#ifdef __WXMSW__
        closesocket(m_fd);
#else
        close(m_fd);
#endif
        m_fd = wxSOCKET_UNINIT;
        m_bConnected = false;
    }

    bool Connect(wxIPV4address& address)
    {
        int retval;

        // Close any existing socket
        if (m_fd != wxSOCKET_UNINIT)
        {
            Close();
        }

        // Create a new socket
        m_fd = (int)socket(AF_INET, SOCK_STREAM, 0);
        if (m_fd < 0)
        {
            m_Error = wxSOCKET_INVSOCK;
            return false;
        }
#ifndef __WXMSW__
        fcntl(m_fd, F_SETFD, FD_CLOEXEC);
#endif

        // Set up receive timeout; avoid hang if client doesn't respond
#ifdef __WXMSW__
        DWORD tv = 10000;
#else
        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;
#endif
        setsockopt(m_fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv));
        setsockopt(m_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));

        // Resolve host name port number
        retval = TranslateAddress(address, m_addr);
        if (retval)
        {
            m_Error = (wxSocketError)retval;
            return false;
        }

        // Connect
        retval = connect(m_fd, (const sockaddr*)(&m_addr), sizeof(m_addr));
        if (retval) {
#ifdef __WXMSW__
            switch(WSAGetLastError())
            {
                case WSAETIMEDOUT:
                    m_Error = wxSOCKET_TIMEDOUT;
                    break;
                default:
                    m_Error = wxSOCKET_IOERR;
                    break;
            }
#else
            switch(retval)
            {
                case ETIMEDOUT:
                    m_Error = wxSOCKET_TIMEDOUT;
                    break;
                default:
                    m_Error = wxSOCKET_IOERR;
                    break;
            }
#endif
            Close();
            return false;
        }

        m_bConnected = true;
        return true;
    }

    bool Error() const
    {
        return m_Error > 0;
    }

    bool IsConnected() const
    {
        return m_bConnected;
    }

    wxUint32 LastCount() const
    {
        return m_uiLastCount;
    }

    wxSocketError LastError() const
    {
        return m_Error;
    }

    void Read(void* buffer, wxUint32 nbytes)
    {
        ssize_t n = 0;
        n = recv(m_fd, (char*)buffer, nbytes, 0);
        if (n < 0)
        {
#ifdef __WXMSW__
            switch(WSAGetLastError())
            {
                case WSAETIMEDOUT:
                    m_Error = wxSOCKET_TIMEDOUT;
                    break;
                default:
                    m_Error = wxSOCKET_IOERR;
                    break;
            }
#else
            switch(errno)
            {
                case ETIMEDOUT:
                    m_Error = wxSOCKET_TIMEDOUT;
                    break;
                default:
                    m_Error = wxSOCKET_IOERR;
                    break;
            }
#endif
            m_uiLastCount = 0;
            return;
        }
        m_Error = wxSOCKET_NOERROR;
        m_uiLastCount = (wxUint32)n;
    }

    void Write(const void* buffer, wxUint32 nbytes)
    {
        ssize_t n = 0;
        n = send(m_fd, (char*)buffer, nbytes, 0);
        if (n < 0)
        {
#ifdef __WXMSW__
            switch(WSAGetLastError())
            {
                case WSAETIMEDOUT:
                    m_Error = wxSOCKET_TIMEDOUT;
                    break;
                default:
                    m_Error = wxSOCKET_IOERR;
                    break;
            }
#else
            switch(errno)
            {
                case ETIMEDOUT:
                    m_Error = wxSOCKET_TIMEDOUT;
                    break;
                default:
                    m_Error = wxSOCKET_IOERR;
                    break;
            }
#endif
            m_uiLastCount = 0;
            return;
        }
        m_Error = wxSOCKET_NOERROR;
        m_uiLastCount = (wxUint32)n;
    }

    wxSocketError TranslateAddress(wxIPV4address& address, sockaddr_in& ip_addr)
    {
        ip_addr.sin_family = AF_INET;

        if (address.Service() == 0)
        {
            return wxSOCKET_INVPORT;
        }
        ip_addr.sin_port = htons(address.Service());

        if (address.IsLocalHost())
        {
            ip_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        }
        else
        {
            hostent* hep;
            hep = gethostbyname(address.Hostname().mb_str());
            if (!hep)
            {
                return wxSOCKET_NOHOST;
            }
            ip_addr.sin_addr.s_addr = *(int*)hep->h_addr_list[0];
        }
        return wxSOCKET_NOERROR;
    }

    int              m_fd;
    bool             m_bConnected;
    wxSocketError    m_Error;
    wxUint32         m_uiLastCount;
    sockaddr_in      m_addr;
};


CRPCConnection::CRPCConnection(CONNECTIONTYPE type) :
CConnectionLockerData()
{
    m_Type = type;
    m_pSocket = new CSocket();
    memset(&m_NarrowCharBuffer, 0, sizeof(m_NarrowCharBuffer));
#if defined(__WXMSW__) && defined(_UNICODE)
    memset(&m_WideCharBuffer, 0, sizeof(m_WideCharBuffer));
#endif
}

CRPCConnection::~CRPCConnection()
{
    delete m_pSocket;
    m_pSocket = NULL;
}

void CRPCConnection::Close()
{
    m_pSocket->Close();
}

bool CRPCConnection::Connect(wxIPV4address& address)
{
    return m_pSocket->Connect(address);
}

bool CRPCConnection::IsConnected() const
{
    return m_pSocket->IsConnected();
}

wxSocketError CRPCConnection::LastError() const
{
    return m_pSocket->LastError();
}

BSLERRCODE CRPCConnection::ReadRPCMessage(wxString& strMessage)
{
    if (m_pSocket->IsConnected())
    {
        wxUint32 uiBytesTransferred = 0;
        while (1)
        {
            m_pSocket->Read((void*)m_NarrowCharBuffer, sizeof(m_NarrowCharBuffer)-1);
            if (m_pSocket->Error()) {
                return BSLERR_CONNECT_IO_ERROR;
            }

            uiBytesTransferred = m_pSocket->LastCount();
            if (0 == uiBytesTransferred) continue;

            m_NarrowCharBuffer[uiBytesTransferred] = 0;

#if defined(__WXMSW__) && defined(_UNICODE)
            // It turns out we are very sensitive to string conversions from a performance
            // perspective.  Using platform specific APIs to convert between multi byte
            // character sets to wide character sets reduces our CPU load by half.
            //
            uiBytesTransferred = MultiByteToWideChar(
                CP_UTF8,
                0,
                (char*)m_NarrowCharBuffer,
                uiBytesTransferred,
                m_WideCharBuffer,
                (sizeof(m_WideCharBuffer)/sizeof(wxChar))-1
            );
            m_WideCharBuffer[uiBytesTransferred] = 0;

            strMessage.append(m_WideCharBuffer, uiBytesTransferred);
#else
            strMessage.append(m_NarrowCharBuffer, uiBytesTransferred);
#endif

            // Check for the message termination character.  It is probably safe to
            // assume it will be the last character before the NULL terminator.
            if (m_NarrowCharBuffer[uiBytesTransferred-1] ==  0x03) break;
        }
    }
    else
    {
        return BSLERR_CONNECT_NOT_CONNECTED;
    }

    return BSLERR_SUCCESS;
}

BSLERRCODE CRPCConnection::WriteRPCMessage(wxString& strMessage)
{
    if (m_pSocket->IsConnected())
    {
        // It turns out we are very sensitive to string conversions from a performance
        // perspective.  Using platform specific APIs to convert between wide 
        // character sets to multi byte character sets reduces our CPU load by half.
        //
#if defined(__WXMSW__) && defined(_UNICODE)
        wxUint32 uiBytesConverted = 0;

        uiBytesConverted = WideCharToMultiByte(
            CP_UTF8,
            0,
            strMessage.c_str(),
            (int)strMessage.size(),
            (char*)m_NarrowCharBuffer,
            (sizeof(m_NarrowCharBuffer)/sizeof(wxByte))-1,
            NULL,
            NULL
        );

        m_pSocket->Write(m_NarrowCharBuffer, uiBytesConverted);
        if (m_pSocket->Error()) {
            return BSLERR_CONNECT_IO_ERROR;
        }
#else
        m_pSocket->Write(strMessage.mb_str(), (wxUint32)strMessage.size());
        if (m_pSocket->Error()) {
            return BSLERR_CONNECT_IO_ERROR;
        }
#endif
        m_pSocket->Write("\003", 1);
        if (m_pSocket->Error()) {
            return BSLERR_CONNECT_IO_ERROR;
        }
    }
    else
    {
        return BSLERR_CONNECT_NOT_CONNECTED;
    }

    return BSLERR_SUCCESS;
}

wxMutexError CRPCConnection::Lock()
{
    return m_pConnectionLocker->Lock();
}

wxMutexError CRPCConnection::Unlock()
{
    return m_pConnectionLocker->Unlock();
}
