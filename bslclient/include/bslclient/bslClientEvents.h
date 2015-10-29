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
/// \defgroup BSLClient BOINC Sentinels Client Library Interface
/// \{

#ifndef _BSLCLIENTEVENTS_H_
#define _BSLCLIENTEVENTS_H_

#include "bslClientEventDefs.hxx"

class CBSLAppEvent: public wxEvent, public CBSLAppEventData
{
public:
    CBSLAppEvent(wxEventType evtType, CBSLAppEventData* pApp) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pApp)
        {
            CBSLAppEventData::operator=(*pApp);
        }
    }

    CBSLAppEvent(const CBSLAppEvent& event) :
        wxEvent(event), CBSLAppEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLAppEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project data associated with this event to the application controlled project pointer.
    /// \param pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(CBSLProject* pProject);

    /// \brief Copy the application data associated with this event to the application controlled application pointer.
    /// \param pApp an application supplied pointer to a CBSLApp object to populate with application data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APP_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APP_NOT_FOUND
    BSLERRCODE GetApp(CBSLApp* pApp);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this application.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APP_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APP_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLAppBulkEvent: public wxEvent
{
public:
    CBSLAppBulkEvent(wxEventType evtType, std::vector<CBSLAppEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLAppBulkEvent(const CBSLAppBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLAppBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLAppEvent events.
    /// \retval A std::vector<CBSLAppEvent> of events to process
    std::vector<CBSLAppEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLAppEvent> m_Events;
};

class CBSLAppVersionEvent: public wxEvent, public CBSLAppVersionEventData
{
public:
    CBSLAppVersionEvent(wxEventType evtType, CBSLAppVersionEventData* pAppVersion) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pAppVersion)
        {
            CBSLAppVersionEventData::operator=(*pAppVersion);
        }
    }

    CBSLAppVersionEvent(const CBSLAppVersionEvent& event) :
        wxEvent(event), CBSLAppVersionEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLAppVersionEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project data associated with this event to the application controlled project pointer.
    /// \param pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(CBSLProject* pProject);

    /// \brief Copy the application data associated with this event to the application controlled application pointer.
    /// \param pApp an application supplied pointer to a CBSLApp object to populate with application data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APP_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APP_NOT_FOUND
    BSLERRCODE GetApp(CBSLApp* pApp);

    /// \brief Copy the application version data associated with this event to the application controlled application version pointer.
    /// \param pAppVersion an application supplied pointer to a CBSLAppVersion object to populate with application version data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APPVERSION_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APPVERSION_NOT_FOUND
    BSLERRCODE GetAppVersion(CBSLAppVersion* pAppVersion);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this application version.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APPVERSION_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APPVERSION_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLAppVersionBulkEvent: public wxEvent
{
public:
    CBSLAppVersionBulkEvent(wxEventType evtType, std::vector<CBSLAppVersionEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLAppVersionBulkEvent(const CBSLAppVersionBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLAppVersionBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLAppVersionEvent events.
    /// \retval A std::vector<CBSLAppVersionEvent> of events to process
    std::vector<CBSLAppVersionEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLAppVersionEvent> m_Events;
};

class CBSLHostEvent: public wxEvent, public CBSLHostEventData
{
public:
    CBSLHostEvent(wxEventType evtType, CBSLHostEventData* pHost) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pHost)
        {
            CBSLHostEventData::operator=(*pHost);
        }
    }

    CBSLHostEvent(const CBSLHostEvent& event) :
        wxEvent(event), CBSLHostEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLHostEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this host.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLHostStatusEvent: public wxEvent, public CBSLHostStatusEventData
{
public:
    CBSLHostStatusEvent(wxEventType evtType, CBSLHostStatusEventData* pHostStatus) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pHostStatus)
        {
            CBSLHostStatusEventData::operator=(*pHostStatus);
        }
    }

    CBSLHostStatusEvent(const CBSLHostStatusEvent& event) :
        wxEvent(event), CBSLHostStatusEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLHostStatusEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this host status.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOSTSTATUS_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOSTSTATUS_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLMessageEvent: public wxEvent, public CBSLMessageEventData
{
public:
    CBSLMessageEvent(wxEventType evtType, CBSLMessageEventData* pMessage) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pMessage)
        {
            CBSLMessageEventData::operator=(*pMessage);
        }
    }

    CBSLMessageEvent(const CBSLMessageEvent& event) :
        wxEvent(event), CBSLMessageEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLMessageEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the message data associated with this event to the application controlled message pointer.
    /// \param pMessage an application supplied pointer to a CBSLMessage object to populate with message data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_MESSAGE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_MESSAGE_NOT_FOUND
    BSLERRCODE GetMessage(CBSLMessage* pMessage);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this message.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_MESSAGE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_MESSAGE_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLMessageBulkEvent: public wxEvent
{
public:
    CBSLMessageBulkEvent(wxEventType evtType, std::vector<CBSLMessageEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLMessageBulkEvent(const CBSLMessageBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLMessageBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLMessageEvent events.
    /// \retval A std::vector<CBSLMessageEvent> of events to process
    std::vector<CBSLMessageEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLMessageEvent> m_Events;
};

class CBSLNotificationEvent: public wxEvent, public CBSLNotificationEventData
{
public:
    CBSLNotificationEvent(wxEventType evtType, CBSLNotificationEventData* pNotification) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pNotification)
        {
            CBSLNotificationEventData::operator=(*pNotification);
        }
    }

    CBSLNotificationEvent(const CBSLNotificationEvent& event) :
        wxEvent(event), CBSLNotificationEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLNotificationEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the notification data associated with this event to the application controlled notification pointer.
    /// \param pNotification an application supplied pointer to a CBSLNotification object to populate with notification data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_NOTIFICATION_NOT_FOUND \copybrief BSLERRCODE::BSLERR_NOTIFICATION_NOT_FOUND
    BSLERRCODE GetNotification(CBSLNotification* pNotification);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this notification.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_NOTIFICATION_NOT_FOUND \copybrief BSLERRCODE::BSLERR_NOTIFICATION_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLNotificationBulkEvent: public wxEvent
{
public:
    CBSLNotificationBulkEvent(wxEventType evtType, std::vector<CBSLNotificationEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLNotificationBulkEvent(const CBSLNotificationBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLNotificationBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLNotificationEvent events.
    /// \retval A std::vector<CBSLNotificationEvent> of events to process
    std::vector<CBSLNotificationEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLNotificationEvent> m_Events;
};

class CBSLProjectEvent: public wxEvent, public CBSLProjectEventData
{
public:
    CBSLProjectEvent(wxEventType evtType, CBSLProjectEventData* pProject) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pProject)
        {
            CBSLProjectEventData::operator=(*pProject);
        }
    }

    CBSLProjectEvent(const CBSLProjectEvent& event) :
        wxEvent(event), CBSLProjectEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLProjectEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project data associated with this event to the application controlled project pointer.
    /// \param pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(CBSLProject* pProject);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this project.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLProjectBulkEvent: public wxEvent
{
public:
    CBSLProjectBulkEvent(wxEventType evtType, std::vector<CBSLProjectEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLProjectBulkEvent(const CBSLProjectBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLProjectBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLProjectEvent events.
    /// \retval A std::vector<CBSLProjectEvent> of events to process
    std::vector<CBSLProjectEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLProjectEvent> m_Events;
};

class CBSLProjectListItemEvent: public wxEvent, public CBSLProjectListItemEventData
{
public:
    CBSLProjectListItemEvent(wxEventType evtType, CBSLProjectListItemEventData* pProjectListItem) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pProjectListItem)
        {
            CBSLProjectListItemEventData::operator=(*pProjectListItem);
        }
    }

    CBSLProjectListItemEvent(const CBSLProjectListItemEvent& event) :
        wxEvent(event), CBSLProjectListItemEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLProjectListItemEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project list data associated with this event to the application controlled project list pointer.
    /// \param pProjectListItem an application supplied pointer to a CBSLProjectListItem object to populate with project list item data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECTLISTITEM_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECTLISTITEM_NOT_FOUND
    BSLERRCODE GetProjectListItem(CBSLProjectListItem* pProjectListItem);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this project list item.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECTLISTITEM_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECTLISTITEM_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLProjectListItemBulkEvent: public wxEvent
{
public:
    CBSLProjectListItemBulkEvent(wxEventType evtType, std::vector<CBSLProjectListItemEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLProjectListItemBulkEvent(const CBSLProjectListItemBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLProjectListItemBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLProjectListItemEvent events.
    /// \retval A std::vector<CBSLProjectListItemEvent> of events to process
    std::vector<CBSLProjectListItemEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLProjectListItemEvent> m_Events;
};

class CBSLProjectStatisticEvent: public wxEvent, public CBSLProjectStatisticEventData
{
public:
    CBSLProjectStatisticEvent(wxEventType evtType, CBSLProjectStatisticEventData* pProjectStatistic) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pProjectStatistic)
        {
            CBSLProjectStatisticEventData::operator=(*pProjectStatistic);
        }
    }

    CBSLProjectStatisticEvent(const CBSLProjectStatisticEvent& event) :
        wxEvent(event), CBSLProjectStatisticEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLProjectStatisticEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project data associated with this event to the application controlled project pointer.
    /// \param pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(CBSLProject* pProject);

    /// \brief Copy the project statistic data associated with this event to the application controlled project statistic pointer.
    /// \param pProjectStatistic an application supplied pointer to a CBSLProjectStatistic object to populate with project statistic data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECTSTATISTIC_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECTSTATISTIC_NOT_FOUND
    BSLERRCODE GetProjectStatistic(CBSLProjectStatistic* pProjectStatistic);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this project statistic.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECTSTATISTIC_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECTSTATISTIC_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLProjectStatisticBulkEvent: public wxEvent
{
public:
    CBSLProjectStatisticBulkEvent(wxEventType evtType, std::vector<CBSLProjectStatisticEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLProjectStatisticBulkEvent(const CBSLProjectStatisticBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLProjectStatisticBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLProjectStatisticEvent events.
    /// \retval A std::vector<CBSLProjectStatisticEvent> of events to process
    std::vector<CBSLProjectStatisticEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLProjectStatisticEvent> m_Events;
};

class CBSLTaskEvent: public wxEvent, public CBSLTaskEventData
{
public:
    CBSLTaskEvent(wxEventType evtType, CBSLTaskEventData* pTask) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pTask)
        {
            CBSLTaskEventData::operator=(*pTask);
        }
    }

    CBSLTaskEvent(const CBSLTaskEvent& event) :
        wxEvent(event), CBSLTaskEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLTaskEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project data associated with this event to the application controlled project pointer.
    /// \param pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(CBSLProject* pProject);

    /// \brief Copy the application data associated with this event to the application controlled application pointer.
    /// \param pApp an application supplied pointer to a CBSLApp object to populate with application data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APP_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APP_NOT_FOUND
    BSLERRCODE GetApp(CBSLApp* pApp);

    /// \brief Copy the task data associated with this event to the application controlled task pointer.
    /// \param pTask an application supplied pointer to a CBSLTask object to populate with task data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_TASK_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASK_NOT_FOUND
    BSLERRCODE GetTask(CBSLTask* pTask);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this task.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_TASK_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASK_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLTaskBulkEvent: public wxEvent
{
public:
    CBSLTaskBulkEvent(wxEventType evtType, std::vector<CBSLTaskEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLTaskBulkEvent(const CBSLTaskBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLTaskBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLTaskEvent events.
    /// \retval A std::vector<CBSLTaskEvent> of events to process
    std::vector<CBSLTaskEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLTaskEvent> m_Events;
};

class CBSLTaskInstanceEvent: public wxEvent, public CBSLTaskInstanceEventData
{
public:
    CBSLTaskInstanceEvent(wxEventType evtType, CBSLTaskInstanceEventData* pTaskInstance) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pTaskInstance)
        {
            CBSLTaskInstanceEventData::operator=(*pTaskInstance);
        }
    }

    CBSLTaskInstanceEvent(const CBSLTaskInstanceEvent& event) :
        wxEvent(event), CBSLTaskInstanceEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLTaskInstanceEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project data associated with this event to the application controlled project pointer.
    /// \param pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(CBSLProject* pProject);

    /// \brief Copy the application data associated with this event to the application controlled application pointer.
    /// \param pApp an application supplied pointer to a CBSLApp object to populate with application data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APP_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APP_NOT_FOUND
    BSLERRCODE GetApp(CBSLApp* pApp);

    /// \brief Copy the application version data associated with this event to the application controlled application version pointer.
    /// \param pAppVersion an application supplied pointer to a CBSLAppVersion object to populate with application version data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_APPVERSION_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APPVERSION_NOT_FOUND
    BSLERRCODE GetAppVersion(CBSLAppVersion* pAppVersion);

    /// \brief Copy the task data associated with this event to the application controlled task pointer.
    /// \param pTask an application supplied pointer to a CBSLTask object to populate with task data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_TASK_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASK_NOT_FOUND
    BSLERRCODE GetTask(CBSLTask* pTask);

    /// \brief Copy the task instance data associated with this event to the application controlled task instance pointer.
    /// \param pTaskInstance an application supplied pointer to a CBSLTaskInstance object to populate with task instance data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_TASKINSTANCE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TASKINSTANCE_NOT_FOUND
    BSLERRCODE GetTaskInstance(CBSLTaskInstance* pTaskInstance);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this task instance.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_TASKINSTANCE_NOT_FOUND \copybrief BSLERRCODE::BSLERR_APP_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLTaskInstanceBulkEvent: public wxEvent
{
public:
    CBSLTaskInstanceBulkEvent(wxEventType evtType, std::vector<CBSLTaskInstanceEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLTaskInstanceBulkEvent(const CBSLTaskInstanceBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLTaskInstanceBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLTaskInstanceEvent events.
    /// \retval A std::vector<CBSLTaskInstanceEvent> of events to process
    std::vector<CBSLTaskInstanceEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLTaskInstanceEvent> m_Events;
};

class CBSLTransferEvent: public wxEvent, public CBSLTransferEventData
{
public:
    CBSLTransferEvent(wxEventType evtType, CBSLTransferEventData* pTransfer) :
        wxEvent(wxID_ANY, evtType)
    {
        if (pTransfer)
        {
            CBSLTransferEventData::operator=(*pTransfer);
        }
    }

    CBSLTransferEvent(const CBSLTransferEvent& event) :
        wxEvent(event), CBSLTransferEventData(event)
    {
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLTransferEvent(*this);
    }

    /// \brief Copy the host data associated with this event to the application controlled host pointer.
    /// \param pHost an application supplied pointer to a CBSLHost object to populate with host data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_HOST_NOT_FOUND \copybrief BSLERRCODE::BSLERR_HOST_NOT_FOUND
    BSLERRCODE GetHost(CBSLHost* pHost);

    /// \brief Copy the project data associated with this event to the application controlled project pointer.
    /// \param pProject an application supplied pointer to a CBSLProject object to populate with project data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_PROJECT_NOT_FOUND \copybrief BSLERRCODE::BSLERR_PROJECT_NOT_FOUND
    BSLERRCODE GetProject(CBSLProject* pProject);

    /// \brief Copy the transfer data associated with this event to the application controlled transfer pointer.
    /// \param pTransfer an application supplied pointer to a CBSLTransfer object to populate with transfer data.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_TRANSFER_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TRANSFER_NOT_FOUND
    BSLERRCODE GetTransfer(CBSLTransfer* pTransfer);

    /// \brief Copy the custom data associated with this event to the application controlled custom data pointer.
    /// \param ppData an application supplied pointer to populate with custom data assigned for this transfer.
    /// \retval BSLERR_SUCCESS \copybrief BSLERRCODE::BSLERR_SUCCESS
    /// \retval BSLERR_FAILURE \copybrief BSLERRCODE::BSLERR_FAILURE
    /// \retval BSLERR_TRANSFER_NOT_FOUND \copybrief BSLERRCODE::BSLERR_TRANSFER_NOT_FOUND
    BSLERRCODE GetEventData(wxUIntPtr* ppData);
};

class CBSLTransferBulkEvent: public wxEvent
{
public:
    CBSLTransferBulkEvent(wxEventType evtType, std::vector<CBSLTransferEvent>& events) :
        wxEvent(wxID_ANY, evtType)
    {
        m_Events = events;
    }

    CBSLTransferBulkEvent(const CBSLTransferBulkEvent& event) :
        wxEvent(event)
    {
        m_Events = event.m_Events;
    }

    /// \brief Clone this event.
    virtual wxEvent *Clone() const
    {
        return new CBSLTransferBulkEvent(*this);
    }

    /// \brief Returns a collections of CBSLTransferEvent events.
    /// \retval A std::vector<CBSLTransferEvent> of events to process
    std::vector<CBSLTransferEvent>& GetEvents() { return m_Events; }

private:
    std::vector<CBSLTransferEvent> m_Events;
};

#endif

///
/// \}
