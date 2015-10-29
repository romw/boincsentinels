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

#include "stdwx.h"
#include "Instance.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateEvents.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "EventManagerTypes.h"
#include "EventManager.h"

IMPLEMENT_DYNAMIC_CLASS(CEventManager, wxObject);

CEventManager::CEventManager() :
wxObject()
{
    m_pEventHandlerDatabaseLock = new wxCriticalSection();
    wxASSERT(m_pEventHandlerDatabaseLock);

    m_pStateManagerQueueLock = new wxCriticalSection();
    wxASSERT(m_pStateManagerQueueLock);

    m_uiOptimialQueueSize = 128;
}

CEventManager::~CEventManager()
{
    // Cleanup the database before deleting the lock.
    m_pEventHandlerDatabaseLock->Enter();

    std::vector<CEventHandlerEntry*>::iterator iter;
    for (iter = m_EventHandlerDatabase.begin(); iter != m_EventHandlerDatabase.end(); iter++)
    {
        CEventHandlerEntry* pEntry = (CEventHandlerEntry*) *iter;
        delete pEntry;
    }
    m_EventHandlerDatabase.clear();

    m_pEventHandlerDatabaseLock->Leave();

    // Cleanup the Queue before deleting the lock.
    m_pStateManagerQueueLock->Enter();
    m_StateManagerQueue.clear();
    m_pStateManagerQueueLock->Leave();

    // Cleanup the locks.
    delete m_pEventHandlerDatabaseLock;
    m_pEventHandlerDatabaseLock = NULL;

    delete m_pStateManagerQueueLock;
    m_pStateManagerQueueLock = NULL;
}

bool CEventManager::FireEvent(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    bool rc = false;

    if (!GetState()->IsShutdownInitiated())
    {
        wxCriticalSectionLocker locker(*m_pEventHandlerDatabaseLock);

        std::vector<CEventHandlerEntry*>::iterator iter;
        for (iter = m_EventHandlerDatabase.begin(); iter != m_EventHandlerDatabase.end(); iter++)
        {
            CEventHandlerEntry* pEntry = (CEventHandlerEntry*) *iter;
            if (ShouldFireEventEntry(pEntry, etEventType, hHost, hHandle))
            {
                if      ((wxEVT_BSLAPP_EVENTSBEGIN <= etEventType) && (wxEVT_BSLAPP_EVENTSEND >= etEventType))
                {
                    // Application Event
                    AddPendingEvent<CBSLAppEvent, CApp>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLAPPVERSION_EVENTSBEGIN <= etEventType) && (wxEVT_BSLAPPVERSION_EVENTSEND >= etEventType))
                {
                    // Application Version Event
                    AddPendingEvent<CBSLAppVersionEvent, CAppVersion>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLHOST_EVENTSBEGIN <= etEventType) && (wxEVT_BSLHOST_EVENTSEND >= etEventType))
                {
                    // Host Event
                    CBSLHostEvent evtHost(etEventType, (CHost*) hHost); 
                    pEntry->GetEventHandler()->AddPendingEvent(evtHost); 
                }
                else if ((wxEVT_BSLHOSTSTATUS_EVENTSBEGIN <= etEventType) && (wxEVT_BSLHOSTSTATUS_EVENTSEND >= etEventType))
                {
                    // Host Status Event
                    AddPendingEvent<CBSLHostStatusEvent, CHostStatus>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLMESSAGE_EVENTSBEGIN <= etEventType) && (wxEVT_BSLMESSAGE_EVENTSEND >= etEventType))
                {
                    // Message Event
                    AddPendingEvent<CBSLMessageEvent, CMessage>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLNOTIFICATION_EVENTSBEGIN <= etEventType) && (wxEVT_BSLNOTIFICATION_EVENTSEND >= etEventType))
                {
                    // Notification Event
                    AddPendingEvent<CBSLNotificationEvent, CNotification>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLPROJECT_EVENTSBEGIN <= etEventType) && (wxEVT_BSLPROJECT_EVENTSEND >= etEventType))
                {
                    // Project Event
                    AddPendingEvent<CBSLProjectEvent, CProject>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLPROJECTLISTITEM_EVENTSBEGIN <= etEventType) && (wxEVT_BSLPROJECTLISTITEM_EVENTSEND >= etEventType))
                {
                    // Project List Item Event
                    AddPendingEvent<CBSLProjectListItemEvent, CProjectListItem>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLPROJECTSTATISTIC_EVENTSBEGIN <= etEventType) && (wxEVT_BSLPROJECTSTATISTIC_EVENTSEND >= etEventType))
                {
                    // Project Statistic Event
                    AddPendingEvent<CBSLProjectStatisticEvent, CProjectStatistic>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLTASK_EVENTSBEGIN <= etEventType) && (wxEVT_BSLTASK_EVENTSEND >= etEventType))
                {
                    // Task Event
                    AddPendingEvent<CBSLTaskEvent, CTask>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLTASKINSTANCE_EVENTSBEGIN <= etEventType) && (wxEVT_BSLTASKINSTANCE_EVENTSEND >= etEventType))
                {
                    // Task Instance Event
                    AddPendingEvent<CBSLTaskInstanceEvent, CTaskInstance>(pEntry, etEventType, hHandle);
                }
                else if ((wxEVT_BSLTRANSFER_EVENTSBEGIN <= etEventType) && (wxEVT_BSLTRANSFER_EVENTSEND >= etEventType))
                {
                    // Transfer Event
                    AddPendingEvent<CBSLTransferEvent, CTransfer>(pEntry, etEventType, hHandle);
                }
                rc = true;
            }
        }

        NotifyStateManager(etEventType, hHost, hHandle);
    }

    return rc;
}

bool CEventManager::FireBulkEvent(wxEventType etEventType, BSLHOST hHost, std::vector<BSLHANDLE>& oEventQueue, bool bIgnoreEventQueueSize)
{
    bool rc = false;

    if (oEventQueue.size() == 0) return rc;

    if ((oEventQueue.size() > m_uiOptimialQueueSize) && !bIgnoreEventQueueSize) {
        m_uiOptimialQueueSize = oEventQueue.size() * 1.25;
    }

    if (!GetState()->IsShutdownInitiated())
    {
        wxCriticalSectionLocker locker(*m_pEventHandlerDatabaseLock);

        std::vector<CEventHandlerEntry*>::iterator iter;
        for (iter = m_EventHandlerDatabase.begin(); iter != m_EventHandlerDatabase.end(); iter++)
        {
            CEventHandlerEntry* pEntry = (CEventHandlerEntry*) *iter;
            if (ShouldFireEventEntry(pEntry, etEventType, hHost, NULL))
            {
                if      ((wxEVT_BSLAPP_EVENTSBEGIN <= etEventType) && (wxEVT_BSLAPP_EVENTSEND >= etEventType))
                {
                    // Application Bulk Event
                    AddPendingBulkEvent<CBSLAppEvent, CBSLAppBulkEvent, CApp>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLAPPVERSION_EVENTSBEGIN <= etEventType) && (wxEVT_BSLAPPVERSION_EVENTSEND >= etEventType))
                {
                    // Application Version Bulk Event
                    AddPendingBulkEvent<CBSLAppVersionEvent, CBSLAppVersionBulkEvent, CAppVersion>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLMESSAGE_EVENTSBEGIN <= etEventType) && (wxEVT_BSLMESSAGE_EVENTSEND >= etEventType))
                {
                    // Message Bulk Event
                    AddPendingBulkEvent<CBSLMessageEvent, CBSLMessageBulkEvent, CMessage>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLNOTIFICATION_EVENTSBEGIN <= etEventType) && (wxEVT_BSLNOTIFICATION_EVENTSEND >= etEventType))
                {
                    // Notification Bulk Event
                    AddPendingBulkEvent<CBSLNotificationEvent, CBSLNotificationBulkEvent, CNotification>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLPROJECT_EVENTSBEGIN <= etEventType) && (wxEVT_BSLPROJECT_EVENTSEND >= etEventType))
                {
                    // Project Bulk Event
                    AddPendingBulkEvent<CBSLProjectEvent, CBSLProjectBulkEvent, CProject>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLPROJECTLISTITEM_EVENTSBEGIN <= etEventType) && (wxEVT_BSLPROJECTLISTITEM_EVENTSEND >= etEventType))
                {
                    // Project List Item Bulk Event
                    AddPendingBulkEvent<CBSLProjectListItemEvent, CBSLProjectListItemBulkEvent, CProjectListItem>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLPROJECTSTATISTIC_EVENTSBEGIN <= etEventType) && (wxEVT_BSLPROJECTSTATISTIC_EVENTSEND >= etEventType))
                {
                    // Project Statistic Item Bulk Event
                    AddPendingBulkEvent<CBSLProjectStatisticEvent, CBSLProjectStatisticBulkEvent, CProjectStatistic>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLTASK_EVENTSBEGIN <= etEventType) && (wxEVT_BSLTASK_EVENTSEND >= etEventType))
                {
                    // Task Bulk Event
                    AddPendingBulkEvent<CBSLTaskEvent, CBSLTaskBulkEvent, CTask>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLTASKINSTANCE_EVENTSBEGIN <= etEventType) && (wxEVT_BSLTASKINSTANCE_EVENTSEND >= etEventType))
                {
                    // Task Instance Bulk Event
                    AddPendingBulkEvent<CBSLTaskInstanceEvent, CBSLTaskInstanceBulkEvent, CTaskInstance>(pEntry, etEventType, oEventQueue);
                }
                else if ((wxEVT_BSLTRANSFER_EVENTSBEGIN <= etEventType) && (wxEVT_BSLTRANSFER_EVENTSEND >= etEventType))
                {
                    // Transfer Bulk Event
                    AddPendingBulkEvent<CBSLTransferEvent, CBSLTransferBulkEvent, CTransfer>(pEntry, etEventType, oEventQueue);
                }
                rc = true;
            }
        }

        NotifyStateManager(etEventType, hHost, NULL);
    }

    return rc;
}



bool CEventManager::IsEventHandlerRegistered(wxEventType etEventType, BSLHOST hHost)
{
    bool rc = false;

    if (!GetState()->IsShutdownInitiated())
    {
        wxCriticalSectionLocker locker(*m_pEventHandlerDatabaseLock);

        std::vector<CEventHandlerEntry*>::iterator iter;
        for (iter = m_EventHandlerDatabase.begin(); iter != m_EventHandlerDatabase.end(); iter++)
        {
            CEventHandlerEntry* pEntry = (CEventHandlerEntry*) *iter;

            if (pEntry->GetEventType() != etEventType) continue;
            if (pEntry->GetHost() != hHost) continue;
            if (pEntry->GetEventHandler() == NULL) continue;

            rc = true;
            break;
        }
    }

    return rc;
}

BSLERRCODE CEventManager::RegisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    CEventHandlerEntry* pEntry = new CEventHandlerEntry();

    pEntry->SetEventHandler(pEventHandler);
    pEntry->SetEventType(etEventType);
    pEntry->SetHost(hHost);
    pEntry->SetHandle(hHandle);
    pEntry->SetThreadId(wxThread::GetCurrentId());

    m_pEventHandlerDatabaseLock->Enter();
    m_EventHandlerDatabase.push_back(pEntry);
    m_pEventHandlerDatabaseLock->Leave();

    return BSLERR_SUCCESS;
}

BSLERRCODE CEventManager::UnregisterEventHandler(wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    wxCriticalSectionLocker locker(*m_pEventHandlerDatabaseLock);
    BSLERRCODE rc = BSLERR_FAILURE;

    std::vector<CEventHandlerEntry*>::iterator iter = m_EventHandlerDatabase.begin();
    while (iter != m_EventHandlerDatabase.end())
    {
        CEventHandlerEntry* pEntry = (CEventHandlerEntry*) *iter;

        if (ShouldEraseEventEntry(pEntry, pEventHandler, etEventType, hHost, hHandle))
        {
            delete pEntry;
            iter = m_EventHandlerDatabase.erase(iter);
            rc = BSLERR_SUCCESS;
        }
        else
        {
            iter++;
        }
    }

    return rc;
}

wxUint32 CEventManager::GetOptimialQueueSize()
{
    return m_uiOptimialQueueSize;
}

bool CEventManager::GetStateManagerQueue(std::vector<CStateManagerEntry>& oQueue)
{
    m_pStateManagerQueueLock->Enter();

    oQueue = m_StateManagerQueue;
    m_StateManagerQueue.clear();

    m_pStateManagerQueueLock->Leave();

    return !oQueue.empty();
}

bool CEventManager::ShouldFireEventEntry(CEventHandlerEntry* pEntry, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    if (pEntry->GetEventType() != etEventType)
        return false;
    if ((pEntry->GetHost() != hHost) && (pEntry->GetHost() != NULL))
        return false;
    if ((pEntry->GetHandle() != hHandle) && (pEntry->GetHandle() != NULL))
        return false;
    return true;
}

bool CEventManager::ShouldEraseEventEntry(CEventHandlerEntry* pEntry, wxEvtHandler* pEventHandler, wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    if (pEntry->GetEventHandler() != pEventHandler)
        return false;
    if (pEntry->GetEventType() != etEventType)
        return false;
    if (pEntry->GetThreadId() != wxThread::GetCurrentId())
        return false;
    if ((pEntry->GetHost() != hHost) && (NULL != hHost))
        return false;
    if ((pEntry->GetHandle() != hHandle) && (NULL != hHandle))
        return false;
    return true;
}

bool CEventManager::NotifyStateManager(wxEventType etEventType, BSLHOST hHost, BSLHANDLE hHandle)
{
    CStateManagerEntry oEntry;

    oEntry.SetEventType(etEventType);
    oEntry.SetHost(hHost);
    oEntry.SetHandle(hHandle);

    m_pStateManagerQueueLock->Enter();
    m_StateManagerQueue.push_back(oEntry);
    m_pStateManagerQueueLock->Leave();

    return true;
}

template<class T1, class T2>
void CEventManager::AddPendingEvent(CEventHandlerEntry* pEntry, wxEventType etEventType, BSLHANDLE hHandle)
{
    T1 evtEvent(etEventType, (T2*) hHandle);
    pEntry->GetEventHandler()->AddPendingEvent(evtEvent);
}

template<class T1, class T2, class T3>
void CEventManager::AddPendingBulkEvent(CEventHandlerEntry* pEntry, wxEventType etEventType, std::vector<BSLHANDLE>& oEventQueue)
{
    std::vector<T1> oEvents;
    std::vector<BSLHANDLE>::iterator iterHandles;

    oEvents.reserve(oEventQueue.size());

    for (iterHandles = oEventQueue.begin(); iterHandles != oEventQueue.end(); iterHandles++)
    {
        T1 evtEvent(etEventType, (T3*) *iterHandles);
        oEvents.push_back(evtEvent);
    }

    T2 evtBulkEvent(etEventType, oEvents);
    pEntry->GetEventHandler()->AddPendingEvent(evtBulkEvent);
}
