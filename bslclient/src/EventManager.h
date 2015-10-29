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

#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

// Forward Declares
//
class CEventHandlerEntry;
class CEventAuditLogEntry;
class CStateManagerEntry;

class CEventManager: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CEventManager)

    friend class CStateManager;
    friend class CStateManagerThread;
    friend class CStateWorkerThread;

public:

    CEventManager();
    ~CEventManager();

    /// \brief Add an event to the event queue for each registered event handler.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host, if NULL then the event will be sent to all event handlers registered for the event type.
    /// \param[in] hHandle handle to an object, if NULL then the event will sent to all event handlers registered for the event type.
    /// \return true on success, false on failure.
    bool FireEvent(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Add a bulk event to the event queue for each registered event handler.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host, if NULL then the event will be sent to all event handlers registered for the event type.
    /// \param[in] oEventQueue A collection of handles to process.
    /// \param[in] bIgnoreEventQueueSize Whether to ignore the size of the event queue when calculating the optimal size.
    /// \return true on success, false on failure.
    bool FireBulkEvent(wxEventType etEventType, BSLHOST hHost, std::vector<BSLHANDLE>& oEventQueue, bool bIgnoreEventQueueSize = false);

    /// \brief Add a bulk event to the event queue for each registered event handler.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host, if NULL then the event will be sent to all event handlers registered for the event type.
    /// \param[in] oEventQueue A collection of handles to process.
    /// \param[in] bIgnoreEventQueueSize Whether to ignore the size of the event queue when calculating the optimal size.
    /// \return true on success, false on failure.
    bool FireAuditLogEvent(wxEventType etEventType, BSLHOST hHost, std::vector<CEventAuditLogEntry>& oEventQueue);

    /// \brief Check to see if an event handler is registered for a given event type.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host.
    /// \return true if the event handler is registered, otherwise false.
    bool IsEventHandlerRegistered(wxEventType etEventType, BSLHOST hHost);

    /// \brief Registers a window to receive the desired events.
    /// \param[in] pEventHandler an event handler to receive the desired event.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host, if NULL then the window will receive events for all hosts.
    /// \param[in] hHandle handle to an object, if NULL then the window will receive events for all objects of the general type.
    /// \return true on success, false on failure.
    BSLERRCODE RegisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Unregisters a window and stops sending the desired events.
    /// \param[in] pEventHandler an event handler to stop receiving the desired event.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host, if NULL then the window will stop receiving events for all hosts.
    /// \param[in] hHandle handle to an object, if NULL then the window will stop receiving events for all objects of the general type.
    /// \return true on success, false on failure.
    BSLERRCODE UnregisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Get the optimial queue size of an event queue.
    wxUint32 GetOptimialQueueSize();

protected:

    /// \brief Provide a mechanism for the state manager to use to monitor the events traveling through the system.
    /// \param[in] oQueue a vector to stuff the new event queues items to be processed into.
    /// \return true on success, false on failure.
    bool GetStateManagerQueue(std::vector<CStateManagerEntry>& oQueue);

private:
    std::vector<CEventHandlerEntry*> m_EventHandlerDatabase;
    wxCriticalSection* m_pEventHandlerDatabaseLock;

    std::vector<CStateManagerEntry> m_StateManagerQueue;
    wxCriticalSection* m_pStateManagerQueueLock;

    /// \brief Checks to see if the event entry matches the event parameters.
    /// \param[in] pEntry the event entry to compare.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host.
    /// \param[in] hHandle handle to an object.
    /// \return true if the event can be fired, otherwise false.
    bool ShouldFireEventEntry(CEventHandlerEntry* pEntry, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Checks to see if the event entry matches the event parameters.
    /// \param[in] pEntry the event entry to compare.
    /// \param[in] pEventHandler an event handler.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host.
    /// \param[in] hHandle handle to an object.
    /// \return true if the event can be erased, otherwise false.
    bool ShouldEraseEventEntry(CEventHandlerEntry* pEntry, wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    /// \brief Notify the state manager that the specified event was thrown.
    /// \param[in] etEventType the desired event.
    /// \param[in] hHost handle to the host.
    /// \param[in] hHandle handle to an object.
    /// \return true if successful, otherwise false.
    bool NotifyStateManager(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle);

    template<class T1, class T2>
    void AddPendingEvent(CEventHandlerEntry* pEntry, wxEventType etEventType, BSLHANDLE hHandle);

    template<class T1, class T2, class T3>
    void AddPendingBulkEvent(CEventHandlerEntry* pEntry, wxEventType etEventType, std::vector<BSLHANDLE>& oEventQueue);

    template<class T1, class T2, class T3>
    void AddPendingAuditLogEvent(CEventHandlerEntry* pEntry, wxEventType etEventType, std::vector<CEventAuditLogEntry>& oEventQueue);

    wxUint32 m_uiOptimialQueueSize;
};

#endif

///
/// \}
