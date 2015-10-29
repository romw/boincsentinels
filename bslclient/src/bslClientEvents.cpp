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
#include "ClientState.h"

DEFINE_EVENT_TYPE(wxEVT_BSLAPP_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLAPP_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLAPP_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLAPP_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPP_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPP_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPP_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPP_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLAPPVERSION_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLHOST_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_CONNECTING)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_CONNECTED)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_DISCONNECTING)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_DISCONNECTED)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_RECONNECTING)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_CONNECTFAILURE)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_AUTHENTICATIONFAILURE)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_VERSIONINCOMPATIBLEFAILURE)
DEFINE_EVENT_TYPE(wxEVT_BSLHOST_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLHOSTSTATUS_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLHOSTSTATUS_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLHOSTSTATUS_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLMESSAGE_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLNOTIFICATION_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECT_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTLISTITEM_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLPROJECTSTATISTIC_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLTASK_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLTASK_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLTASK_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLTASK_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASK_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASK_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASK_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASK_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLTASKINSTANCE_EVENTSEND)

DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_EVENTSBEGIN)
DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_ADD)
DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_BULKADD)
DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_DELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_BULKDELETE)
DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_UPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_BULKUPDATE)
DEFINE_EVENT_TYPE(wxEVT_BSLTRANSFER_EVENTSEND)

//
// CBSLAppEvent
//

BSLERRCODE CBSLAppEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLAppEvent::GetProject(CBSLProject* pProject)
{
    return GetState()->GetProject(GetProjectHandle(), pProject);
}

BSLERRCODE CBSLAppEvent::GetApp(CBSLApp* pApp)
{
    return GetState()->GetApp(GetAppHandle(), pApp);
}

BSLERRCODE CBSLAppEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetAppEventData(GetAppHandle(), ppData);
}

//
// CBSLAppVersionEvent
//

BSLERRCODE CBSLAppVersionEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLAppVersionEvent::GetProject(CBSLProject* pProject)
{
    return GetState()->GetProject(GetProjectHandle(), pProject);
}

BSLERRCODE CBSLAppVersionEvent::GetApp(CBSLApp* pApp)
{
    return GetState()->GetApp(GetAppHandle(), pApp);
}

BSLERRCODE CBSLAppVersionEvent::GetAppVersion(CBSLAppVersion* pAppVersion)
{
    return GetState()->GetAppVersion(GetAppVersionHandle(), pAppVersion);
}

BSLERRCODE CBSLAppVersionEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetAppVersionEventData(GetAppVersionHandle(), ppData);
}

//
// CBSLHostEvent
//

BSLERRCODE CBSLHostEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLHostEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetHostEventData(GetHostHandle(), ppData);
}

//
// CBSLHostStatusEvent
//

BSLERRCODE CBSLHostStatusEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLHostStatusEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetHostStatusEventData(GetHostHandle(), ppData);
}

//
// CBSLMessageEvent
//

BSLERRCODE CBSLMessageEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLMessageEvent::GetMessage(CBSLMessage* pMessage)
{
    return GetState()->GetMessage(GetMessageHandle(), pMessage);
}

BSLERRCODE CBSLMessageEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetMessageEventData(GetMessageHandle(), ppData);
}

//
// CBSLNotificationEvent
//

BSLERRCODE CBSLNotificationEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLNotificationEvent::GetNotification(CBSLNotification* pNotification)
{
    return GetState()->GetNotification(GetNotificationHandle(), pNotification);
}

BSLERRCODE CBSLNotificationEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetNotificationEventData(GetNotificationHandle(), ppData);
}

//
// CBSLProjectEvent
//

BSLERRCODE CBSLProjectEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLProjectEvent::GetProject(CBSLProject* pProject)
{
    return GetState()->GetProject(GetProjectHandle(), pProject);
}

BSLERRCODE CBSLProjectEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetProjectEventData(GetProjectHandle(), ppData);
}

//
// CBSLProjectListItemEvent
//

BSLERRCODE CBSLProjectListItemEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLProjectListItemEvent::GetProjectListItem(CBSLProjectListItem* pProjectListItem)
{
    return GetState()->GetProjectListItem(GetProjectListItemHandle(), pProjectListItem);
}

BSLERRCODE CBSLProjectListItemEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetProjectListItemEventData(GetProjectListItemHandle(), ppData);
}

//
// CBSLProjectStatisticEvent
//

BSLERRCODE CBSLProjectStatisticEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLProjectStatisticEvent::GetProject(CBSLProject* pProject)
{
    return GetState()->GetProject(GetProjectHandle(), pProject);
}

BSLERRCODE CBSLProjectStatisticEvent::GetProjectStatistic(CBSLProjectStatistic* pProjectStatistic)
{
    return GetState()->GetProjectStatistic(GetProjectStatisticHandle(), pProjectStatistic);
}

BSLERRCODE CBSLProjectStatisticEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetProjectStatisticEventData(GetProjectStatisticHandle(), ppData);
}

//
// CBSLTaskEvent
//

BSLERRCODE CBSLTaskEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLTaskEvent::GetProject(CBSLProject* pProject)
{
    return GetState()->GetProject(GetProjectHandle(), pProject);
}

BSLERRCODE CBSLTaskEvent::GetApp(CBSLApp* pApp)
{
    return GetState()->GetApp(GetAppHandle(), pApp);
}

BSLERRCODE CBSLTaskEvent::GetTask(CBSLTask* pTask)
{
    return GetState()->GetTask(GetTaskHandle(), pTask);
}

BSLERRCODE CBSLTaskEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetTaskEventData(GetTaskHandle(), ppData);
}

//
// CBSLTaskInstanceEvent
//

BSLERRCODE CBSLTaskInstanceEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLTaskInstanceEvent::GetProject(CBSLProject* pProject)
{
    return GetState()->GetProject(GetProjectHandle(), pProject);
}

BSLERRCODE CBSLTaskInstanceEvent::GetApp(CBSLApp* pApp)
{
    return GetState()->GetApp(GetAppHandle(), pApp);
}

BSLERRCODE CBSLTaskInstanceEvent::GetAppVersion(CBSLAppVersion* pAppVersion)
{
    return GetState()->GetAppVersion(GetAppVersionHandle(), pAppVersion);
}

BSLERRCODE CBSLTaskInstanceEvent::GetTask(CBSLTask* pTask)
{
    return GetState()->GetTask(GetTaskHandle(), pTask);
}

BSLERRCODE CBSLTaskInstanceEvent::GetTaskInstance(CBSLTaskInstance* pTaskInstance)
{
    return GetState()->GetTaskInstance(GetTaskInstanceHandle(), pTaskInstance);
}

BSLERRCODE CBSLTaskInstanceEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetTaskInstanceEventData(GetTaskInstanceHandle(), ppData);
}

//
// CBSLTransferEvent
//

BSLERRCODE CBSLTransferEvent::GetHost(CBSLHost* pHost)
{
    return GetState()->GetHost(GetHostHandle(), pHost, false, false);
}

BSLERRCODE CBSLTransferEvent::GetProject(CBSLProject* pProject)
{
    return GetState()->GetProject(GetProjectHandle(), pProject);
}

BSLERRCODE CBSLTransferEvent::GetTransfer(CBSLTransfer* pTransfer)
{
    return GetState()->GetTransfer(GetTransferHandle(), pTransfer);
}

BSLERRCODE CBSLTransferEvent::GetEventData(wxUIntPtr* ppData)
{
    return GetState()->GetTransferEventData(GetTransferHandle(), ppData);
}
