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
/// \defgroup EventManager Event Manager
/// \{

#ifndef _EVENTMANAGERTYPES_H_
#define _EVENTMANAGERTYPES_H_

class CEventHandlerEntry
{
public:

    CEventHandlerEntry()
    {
        m_pEventHandler = NULL;
        m_etEventType = 0;
        m_hHost = 0;
        m_hHandle = 0;
        m_lThreadId = 0;
    }
    ~CEventHandlerEntry()
    {
        m_pEventHandler = NULL;
        m_etEventType = 0;
        m_hHost = 0;
        m_hHandle = 0;
        m_lThreadId = 0;
    }

    wxEvtHandler* GetEventHandler() { return m_pEventHandler; }
    wxEventType GetEventType() { return m_etEventType; }
    BSLHOST GetHost() { return m_hHost; }
    BSLHANDLE GetHandle() { return m_hHandle; }
    wxThreadIdType GetThreadId() { return m_lThreadId; }

    void SetEventHandler(wxEvtHandler* pEventHandler) { m_pEventHandler = pEventHandler; }
    void SetEventType(wxEventType etEventType) { m_etEventType = etEventType; }
    void SetHost(BSLHOST hHost) { m_hHost = hHost; }
    void SetHandle(BSLHANDLE hHandle) { m_hHandle = hHandle; }
    void SetThreadId(wxThreadIdType lThreadId) { m_lThreadId = lThreadId; }

private:
    wxEvtHandler* m_pEventHandler;
    wxEventType m_etEventType;
    BSLHOST m_hHost;
    BSLHANDLE m_hHandle;
    wxThreadIdType m_lThreadId;
};

class CEventAuditLogEntry
{
public:
    CEventAuditLogEntry()
    {
        Clear();
    }
    ~CEventAuditLogEntry()
    {
        Clear();
    }

    void Clear()
    {
        m_hHost = 0;
        m_hHandle = 0;
        m_bAdd = false;
        m_bUpdate = false;
        m_bDelete = false;
    }

    BSLHOST GetHost() { return m_hHost; }
    BSLHANDLE GetHandle() { return m_hHandle; }
    bool IsAdd() { return m_bAdd; }
    bool IsUpdate() { return m_bUpdate; }
    bool IsDelete() { return m_bDelete; }

    void SetHost(BSLHOST hHost) { m_hHost = hHost; }
    void SetHandle(BSLHANDLE hHandle) { m_hHandle = hHandle; }
    void SetAdd(bool bAdd) { m_bAdd = bAdd; }
    void SetUpdate(bool bUpdate) { m_bUpdate = bUpdate; }
    void SetDelete(bool bDelete) { m_bDelete = bDelete; }

private:
    BSLHOST m_hHost;
    BSLHANDLE m_hHandle;
    bool m_bAdd;
    bool m_bUpdate;
    bool m_bDelete;
};

class CStateManagerEntry
{
public:

    CStateManagerEntry()
    {
        Clear();
    }
    ~CStateManagerEntry()
    {
        Clear();
    }

    void Clear()
    {
        m_etEventType = 0;
        m_hHost = 0;
        m_hHandle = 0;
    }

    wxEventType GetEventType() { return m_etEventType; }
    BSLHOST GetHost() { return m_hHost; }
    BSLHANDLE GetHandle() { return m_hHandle; }
    
    void SetEventType(wxEventType etEventType) { m_etEventType = etEventType; }
    void SetHost(BSLHOST hHost) { m_hHost = hHost; }
    void SetHandle(BSLHANDLE hHandle) { m_hHandle = hHandle; }

private:
    wxEventType m_etEventType;
    BSLHOST m_hHost;
    BSLHANDLE m_hHandle;
};

#endif

///
/// \}
