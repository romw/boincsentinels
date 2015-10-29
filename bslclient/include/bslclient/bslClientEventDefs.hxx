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

#ifndef _BSLCLIENTEVENTDEFS_H_
#define _BSLCLIENTEVENTDEFS_H_

BEGIN_DECLARE_EVENT_TYPES()

    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_EVENTSBEGIN, 10500 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_ADD, 10501 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_BULKADD, 10502 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_DELETE, 10503 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_BULKDELETE, 10504 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_UPDATE, 10505 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_BULKUPDATE, 10506 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_AUDITLOG, 10507 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPP_EVENTSEND, 10599 )

    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_EVENTSBEGIN, 10600 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_ADD, 10601 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_BULKADD, 10602 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_DELETE, 10603 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_BULKDELETE, 10604 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_UPDATE, 10605 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_BULKUPDATE, 10606 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_AUDITLOG, 10607 )
    DECLARE_EVENT_TYPE( wxEVT_BSLAPPVERSION_EVENTSEND, 10699 )

    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_EVENTSBEGIN, 10700 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_ADD, 10701 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_DELETE, 10702 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_UPDATE, 10703 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_CONNECTING, 10705 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_CONNECTED, 10706 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_DISCONNECTING, 10707 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_DISCONNECTED, 10708 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_RECONNECTING, 10709 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_CONNECTFAILURE, 10710 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_AUTHENTICATIONFAILURE, 10711 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_VERSIONINCOMPATIBLEFAILURE, 10712 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOST_EVENTSEND, 10799 )

    DECLARE_EVENT_TYPE( wxEVT_BSLHOSTSTATUS_EVENTSBEGIN, 10800 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOSTSTATUS_UPDATE, 10801 )
    DECLARE_EVENT_TYPE( wxEVT_BSLHOSTSTATUS_EVENTSEND, 10899 )

    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_EVENTSBEGIN, 10900 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_ADD, 10901 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_BULKADD, 10902 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_DELETE, 10903 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_BULKDELETE, 10904 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_UPDATE, 10905 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_BULKUPDATE, 10906 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_AUDITLOG, 10907 )
    DECLARE_EVENT_TYPE( wxEVT_BSLMESSAGE_EVENTSEND, 10999 )

    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_EVENTSBEGIN, 11000 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_ADD, 11001 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_BULKADD, 11002 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_DELETE, 11003 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_BULKDELETE, 11004 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_UPDATE, 11005 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_BULKUPDATE, 11006 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_AUDITLOG, 11007 )
    DECLARE_EVENT_TYPE( wxEVT_BSLNOTIFICATION_EVENTSEND, 11099 )

    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_EVENTSBEGIN, 11100 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_ADD, 11101 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_BULKADD, 11102 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_DELETE, 11103 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_BULKDELETE, 11104 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_UPDATE, 11105 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_BULKUPDATE, 11106 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_AUDITLOG, 11107 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECT_EVENTSEND, 11199 )

    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_EVENTSBEGIN, 11200 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_ADD, 11201 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_BULKADD, 11202 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_DELETE, 11203 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_BULKDELETE, 11204 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_UPDATE, 11205 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_BULKUPDATE, 11206 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_AUDITLOG, 11207 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTLISTITEM_EVENTSEND, 11299 )

    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_EVENTSBEGIN, 11300 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_ADD, 11301 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_BULKADD, 11302 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_DELETE, 11303 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_BULKDELETE, 11304 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_UPDATE, 113005 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_BULKUPDATE, 11306 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_AUDITLOG, 11307 )
    DECLARE_EVENT_TYPE( wxEVT_BSLPROJECTSTATISTIC_EVENTSEND, 11399 )

    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_EVENTSBEGIN, 11400 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_ADD, 11401 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_BULKADD, 11402 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_DELETE, 11403 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_BULKDELETE, 11404 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_UPDATE, 11405 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_BULKUPDATE, 11406 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_AUDITLOG, 11407 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASK_EVENTSEND, 11499 )

    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_EVENTSBEGIN, 11500 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_ADD, 11501 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_BULKADD, 11502 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_DELETE, 11503 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_BULKDELETE, 11504 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_UPDATE, 11505 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_BULKUPDATE, 11506 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_AUDITLOG, 11507 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTASKINSTANCE_EVENTSEND, 11599 )

    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_EVENTSBEGIN, 11600 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_ADD, 11601 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_BULKADD, 11602 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_DELETE, 11603 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_BULKDELETE, 11604 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_UPDATE, 11605 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_BULKUPDATE, 11606 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_AUDITLOG, 11607 )
    DECLARE_EVENT_TYPE( wxEVT_BSLTRANSFER_EVENTSEND, 11699 )

END_DECLARE_EVENT_TYPES();


class CBSLAppEvent;
class CBSLAppBulkEvent;
class CBSLAppAuditLogEvent;

typedef void (wxEvtHandler::*CBSLAppEventFunction)(CBSLAppEvent&);
typedef void (wxEvtHandler::*CBSLAppBulkEventFunction)(CBSLAppBulkEvent&);
typedef void (wxEvtHandler::*CBSLAppAuditLogEventFunction)(CBSLAppAuditLogEvent&);

#define CBSLAppEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLAppEventFunction, &func)
#define CBSLAppBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLAppBulkEventFunction, &func)
#define CBSLAppAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLAppAuditLogEventFunction, &func)

#define wx__DECLARE_BSLAPPEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLAPP_ ## evt, CBSLAppEventHandler(fn))
#define wx__DECLARE_BSLAPPBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLAPP_ ## evt, CBSLAppBulkEventHandler(fn))
#define wx__DECLARE_BSLAPPAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLAPP_ ## evt, CBSLAppAuditLogEventHandler(fn))

#define EVT_BSLAPP_ADD(fn)                      wx__DECLARE_BSLAPPEVT(ADD, fn)
#define EVT_BSLAPP_BULKADD(fn)                  wx__DECLARE_BSLAPPBULKEVT(BULKADD, fn)
#define EVT_BSLAPP_DELETE(fn)                   wx__DECLARE_BSLAPPEVT(DELETE, fn)
#define EVT_BSLAPP_BULKDELETE(fn)               wx__DECLARE_BSLAPPBULKEVT(BULKDELETE, fn)
#define EVT_BSLAPP_UPDATE(fn)                   wx__DECLARE_BSLAPPEVT(UPDATE, fn)
#define EVT_BSLAPP_BULKUPDATE(fn)               wx__DECLARE_BSLAPPBULKEVT(BULKUPDATE, fn)
#define EVT_BSLAPP_AUDITLOG(fn)                 wx__DECLARE_BSLAPPAUDITLOGEVT(AUDITLOG, fn)

class CBSLAppVersionEvent;
class CBSLAppVersionBulkEvent;
class CBSLAppVersionAuditLogEvent;

typedef void (wxEvtHandler::*CBSLAppVersionEventFunction)(CBSLAppVersionEvent&);
typedef void (wxEvtHandler::*CBSLAppVersionBulkEventFunction)(CBSLAppVersionBulkEvent&);
typedef void (wxEvtHandler::*CBSLAppVersionAuditLogEventFunction)(CBSLAppVersionAuditLogEvent&);

#define CBSLAppVersionEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLAppVersionEventFunction, &func)
#define CBSLAppVersionBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLAppVersionBulkEventFunction, &func)
#define CBSLAppVersionAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLAppVersionAuditLogEventFunction, &func)

#define wx__DECLARE_BSLAPPVERSIONEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLAPPVERSION_ ## evt, CBSLAppVersionEventHandler(fn))
#define wx__DECLARE_BSLAPPVERSIONBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLAPPVERSION_ ## evt, CBSLAppVersionBulkEventHandler(fn))
#define wx__DECLARE_BSLAPPVERSIONAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLAPPVERSION_ ## evt, CBSLAppVersionAuditLogEventHandler(fn))

#define EVT_BSLAPPVERSION_ADD(fn)               wx__DECLARE_BSLAPPVERSIONEVT(ADD, fn)
#define EVT_BSLAPPVERSION_BULKADD(fn)           wx__DECLARE_BSLAPPVERSIONBULKEVT(BULKADD, fn)
#define EVT_BSLAPPVERSION_DELETE(fn)            wx__DECLARE_BSLAPPVERSIONEVT(DELETE, fn)
#define EVT_BSLAPPVERSION_BULKDELETE(fn)        wx__DECLARE_BSLAPPVERSIONBULKEVT(BULKDELETE, fn)
#define EVT_BSLAPPVERSION_UPDATE(fn)            wx__DECLARE_BSLAPPVERSIONEVT(UPDATE, fn)
#define EVT_BSLAPPVERSION_BULKUPDATE(fn)        wx__DECLARE_BSLAPPVERSIONBULKEVT(BULKUPDATE, fn)
#define EVT_BSLAPPVERSION_AUDITLOG(fn)          wx__DECLARE_BSLAPPVERSIONAUDITLOGEVT(AUDITLOG, fn)

class CBSLHostEvent;

typedef void (wxEvtHandler::*CBSLHostEventFunction)(CBSLHostEvent&);

#define CBSLHostEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLHostEventFunction, &func)

#define wx__DECLARE_BSLHOSTEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLHOST_ ## evt, CBSLHostEventHandler(fn))

#define EVT_BSLHOST_ADD(fn)                     wx__DECLARE_BSLHOSTEVT(ADD, fn)
#define EVT_BSLHOST_DELETE(fn)                  wx__DECLARE_BSLHOSTEVT(DELETE, fn)
#define EVT_BSLHOST_UPDATE(fn)                  wx__DECLARE_BSLHOSTEVT(UPDATE, fn)
#define EVT_BSLHOST_CONNECTING(fn)              wx__DECLARE_BSLHOSTEVT(CONNECTING, fn)
#define EVT_BSLHOST_CONNECTED(fn)               wx__DECLARE_BSLHOSTEVT(CONNECTED, fn)
#define EVT_BSLHOST_DISCONNECTING(fn)           wx__DECLARE_BSLHOSTEVT(DISCONNECTING, fn)
#define EVT_BSLHOST_DISCONNECTED(fn)            wx__DECLARE_BSLHOSTEVT(DISCONNECTED, fn)
#define EVT_BSLHOST_RECONNECTING(fn)            wx__DECLARE_BSLHOSTEVT(RECONNECTING, fn)
#define EVT_BSLHOST_CONNECTFAILURE(fn)          wx__DECLARE_BSLHOSTEVT(CONNECTFAILURE, fn)
#define EVT_BSLHOST_AUTHENTICATIONFAILURE(fn)   wx__DECLARE_BSLHOSTEVT(AUTHENTICATIONFAILURE, fn)
#define EVT_BSLHOST_VERSIONINCOMPATIBLEFAILURE(fn) wx__DECLARE_BSLHOSTEVT(VERSIONINCOMPATIBLEFAILURE, fn)

class CBSLHostStatusEvent;

typedef void (wxEvtHandler::*CBSLHostStatusEventFunction)(CBSLHostStatusEvent&);

#define CBSLHostStatusEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLHostStatusEventFunction, &func)

#define wx__DECLARE_BSLHOSTSTATUSEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLHOSTSTATUS_ ## evt, CBSLHostStatusEventHandler(fn))

#define EVT_BSLHOSTSTATUS_UPDATE(fn)            wx__DECLARE_BSLHOSTSTATUSEVT(UPDATE, fn)

class CBSLMessageEvent;
class CBSLMessageBulkEvent;
class CBSLMessageAuditLogEvent;

typedef void (wxEvtHandler::*CBSLMessageEventFunction)(CBSLMessageEvent&);
typedef void (wxEvtHandler::*CBSLMessageBulkEventFunction)(CBSLMessageBulkEvent&);
typedef void (wxEvtHandler::*CBSLMessageAuditLogEventFunction)(CBSLMessageAuditLogEvent&);

#define CBSLMessageEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLMessageEventFunction, &func)
#define CBSLMessageBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLMessageBulkEventFunction, &func)
#define CBSLMessageAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLMessageAuditLogEventFunction, &func)

#define wx__DECLARE_BSLMESSAGEEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLMESSAGE_ ## evt, CBSLMessageEventHandler(fn))
#define wx__DECLARE_BSLMESSAGEBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLMESSAGE_ ## evt, CBSLMessageBulkEventHandler(fn))
#define wx__DECLARE_BSLMESSAGEAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLMESSAGE_ ## evt, CBSLMessageAuditLogEventHandler(fn))

#define EVT_BSLMESSAGE_ADD(fn)                  wx__DECLARE_BSLMESSAGEEVT(ADD, fn)
#define EVT_BSLMESSAGE_BULKADD(fn)              wx__DECLARE_BSLMESSAGEBULKEVT(BULKADD, fn)
#define EVT_BSLMESSAGE_DELETE(fn)               wx__DECLARE_BSLMESSAGEEVT(DELETE, fn)
#define EVT_BSLMESSAGE_BULKDELETE(fn)           wx__DECLARE_BSLMESSAGEBULKEVT(BULKDELETE, fn)
#define EVT_BSLMESSAGE_UPDATE(fn)               wx__DECLARE_BSLMESSAGEEVT(UPDATE, fn)
#define EVT_BSLMESSAGE_BULKUPDATE(fn)           wx__DECLARE_BSLMESSAGEBULKEVT(BULKUPDATE, fn)
#define EVT_BSLMESSAGE_AUDITLOG(fn)             wx__DECLARE_BSLMESSAGEAUDITLOGEVT(AUDITLOG, fn)

class CBSLNotificationEvent;
class CBSLNotificationBulkEvent;
class CBSLNotificationAuditLogEvent;

typedef void (wxEvtHandler::*CBSLNotificationEventFunction)(CBSLNotificationEvent&);
typedef void (wxEvtHandler::*CBSLNotificationBulkEventFunction)(CBSLNotificationBulkEvent&);
typedef void (wxEvtHandler::*CBSLNotificationAuditLogEventFunction)(CBSLNotificationAuditLogEvent&);

#define CBSLNotificationEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLNotificationEventFunction, &func)
#define CBSLNotificationBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLNotificationBulkEventFunction, &func)
#define CBSLNotificationAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLNotificationAuditLogEventFunction, &func)

#define wx__DECLARE_BSLNOTIFICATIONEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLNOTIFICATION_ ## evt, CBSLNotificationEventHandler(fn))
#define wx__DECLARE_BSLNOTIFICATIONBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLNOTIFICATION_ ## evt, CBSLNotificationBulkEventHandler(fn))
#define wx__DECLARE_BSLNOTIFICATIONAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLNOTIFICATION_ ## evt, CBSLNotificationAuditLogEventHandler(fn))

#define EVT_BSLNOTIFICATION_ADD(fn)             wx__DECLARE_BSLNOTIFICATIONEVT(ADD, fn)
#define EVT_BSLNOTIFICATION_BULKADD(fn)         wx__DECLARE_BSLNOTIFICATIONBULKEVT(BULKADD, fn)
#define EVT_BSLNOTIFICATION_DELETE(fn)          wx__DECLARE_BSLNOTIFICATIONEVT(DELETE, fn)
#define EVT_BSLNOTIFICATION_BULKDELETE(fn)      wx__DECLARE_BSLNOTIFICATIONBULKEVT(BULKDELETE, fn)
#define EVT_BSLNOTIFICATION_UPDATE(fn)          wx__DECLARE_BSLNOTIFICATIONEVT(UPDATE, fn)
#define EVT_BSLNOTIFICATION_BULKUPDATE(fn)      wx__DECLARE_BSLNOTIFICATIONBULKEVT(BULKUPDATE, fn)
#define EVT_BSLNOTIFICATION_AUDITLOG(fn)        wx__DECLARE_BSLNOTIFICATIONAUDITLOGEVT(AUDITLOG, fn)

class CBSLProjectEvent;
class CBSLProjectBulkEvent;
class CBSLProjectAuditLogEvent;

typedef void (wxEvtHandler::*CBSLProjectEventFunction)(CBSLProjectEvent&);
typedef void (wxEvtHandler::*CBSLProjectBulkEventFunction)(CBSLProjectBulkEvent&);
typedef void (wxEvtHandler::*CBSLProjectAuditLogEventFunction)(CBSLProjectAuditLogEvent&);

#define CBSLProjectEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectEventFunction, &func)
#define CBSLProjectBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectBulkEventFunction, &func)
#define CBSLProjectAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectAuditLogEventFunction, &func)

#define wx__DECLARE_BSLPROJECTEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECT_ ## evt, CBSLProjectEventHandler(fn))
#define wx__DECLARE_BSLPROJECTBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECT_ ## evt, CBSLProjectBulkEventHandler(fn))
#define wx__DECLARE_BSLPROJECTAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECT_ ## evt, CBSLProjectAuditLogEventHandler(fn))

#define EVT_BSLPROJECT_ADD(fn)                  wx__DECLARE_BSLPROJECTEVT(ADD, fn)
#define EVT_BSLPROJECT_BULKADD(fn)              wx__DECLARE_BSLPROJECTBULKEVT(BULKADD, fn)
#define EVT_BSLPROJECT_DELETE(fn)               wx__DECLARE_BSLPROJECTEVT(DELETE, fn)
#define EVT_BSLPROJECT_BulkDELETE(fn)           wx__DECLARE_BSLPROJECTBULKEVT(BULKDELETE, fn)
#define EVT_BSLPROJECT_UPDATE(fn)               wx__DECLARE_BSLPROJECTEVT(UPDATE, fn)
#define EVT_BSLPROJECT_BULKUPDATE(fn)           wx__DECLARE_BSLPROJECTBULKEVT(BULKUPDATE, fn)
#define EVT_BSLPROJECT_AUDITLOG(fn)             wx__DECLARE_BSLPROJECTAUDITLOGEVT(AUDITLOG, fn)

class CBSLProjectListItemEvent;
class CBSLProjectListItemBulkEvent;
class CBSLProjectListItemAuditLogEvent;

typedef void (wxEvtHandler::*CBSLProjectListItemEventFunction)(CBSLProjectListItemEvent&);
typedef void (wxEvtHandler::*CBSLProjectListItemBulkEventFunction)(CBSLProjectListItemBulkEvent&);
typedef void (wxEvtHandler::*CBSLProjectListItemAuditLogEventFunction)(CBSLProjectListItemAuditLogEvent&);

#define CBSLProjectListItemEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectListItemEventFunction, &func)
#define CBSLProjectListItemBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectListItemBulkEventFunction, &func)
#define CBSLProjectListItemAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectListItemAuditLogEventFunction, &func)

#define wx__DECLARE_BSLPROJECTLISTITEMEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECTLISTITEM_ ## evt, CBSLProjectListItemEventHandler(fn))
#define wx__DECLARE_BSLPROJECTLISTITEMBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECTLISTITEM_ ## evt, CBSLProjectListItemBulkEventHandler(fn))
#define wx__DECLARE_BSLPROJECTLISTITEMAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECTLISTITEM_ ## evt, CBSLProjectListItemAuditLogEventHandler(fn))

#define EVT_BSLPROJECTLISTITEM_ADD(fn)          wx__DECLARE_BSLPROJECTLISTITEMEVT(ADD, fn)
#define EVT_BSLPROJECTLISTITEM_BULKADD(fn)      wx__DECLARE_BSLPROJECTLISTITEMBULKEVT(BULKADD, fn)
#define EVT_BSLPROJECTLISTITEM_DELETE(fn)       wx__DECLARE_BSLPROJECTLISTITEMEVT(DELETE, fn)
#define EVT_BSLPROJECTLISTITEM_BULKDELETE(fn)   wx__DECLARE_BSLPROJECTLISTITEMBULKEVT(BULKDELETE, fn)
#define EVT_BSLPROJECTLISTITEM_UPDATE(fn)       wx__DECLARE_BSLPROJECTLISTITEMEVT(UPDATE, fn)
#define EVT_BSLPROJECTLISTITEM_BULKUPDATE(fn)   wx__DECLARE_BSLPROJECTLISTITEMBULKEVT(BULKUPDATE, fn)
#define EVT_BSLPROJECTLISTITEM_AUDITLOG(fn)     wx__DECLARE_BSLPROJECTLISTITEMAUDITLOGEVT(AUDITLOG, fn)

class CBSLProjectStatisticEvent;
class CBSLProjectStatisticBulkEvent;
class CBSLProjectStatisticAuditLogEvent;

typedef void (wxEvtHandler::*CBSLProjectStatisticEventFunction)(CBSLProjectStatisticEvent&);
typedef void (wxEvtHandler::*CBSLProjectStatisticBulkEventFunction)(CBSLProjectStatisticBulkEvent&);
typedef void (wxEvtHandler::*CBSLProjectStatisticAuditLogEventFunction)(CBSLProjectStatisticAuditLogEvent&);

#define CBSLProjectStatisticEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectStatisticEventFunction, &func)
#define CBSLProjectStatisticBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectStatisticBulkEventFunction, &func)
#define CBSLProjectStatisticAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLProjectStatisticAuditLogEventFunction, &func)

#define wx__DECLARE_BSLPROJECTSTATISTICEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECTSTATISTIC_ ## evt, CBSLProjectStatisticEventHandler(fn))
#define wx__DECLARE_BSLPROJECTSTATISTICBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECTSTATISTIC_ ## evt, CBSLProjectStatisticBulkEventHandler(fn))
#define wx__DECLARE_BSLPROJECTSTATISTICAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLPROJECTSTATISTIC_ ## evt, CBSLProjectStatisticAuditLogEventHandler(fn))

#define EVT_BSLPROJECTSTATISTIC_ADD(fn)         wx__DECLARE_BSLPROJECTSTATISTICEVT(ADD, fn)
#define EVT_BSLPROJECTSTATISTIC_BULKADD(fn)     wx__DECLARE_BSLPROJECTSTATISTICBULKEVT(BULKADD, fn)
#define EVT_BSLPROJECTSTATISTIC_DELETE(fn)      wx__DECLARE_BSLPROJECTSTATISTICEVT(DELETE, fn)
#define EVT_BSLPROJECTSTATISTIC_BULKDELETE(fn)  wx__DECLARE_BSLPROJECTSTATISTICBULKEVT(BULKDELETE, fn)
#define EVT_BSLPROJECTSTATISTIC_UPDATE(fn)      wx__DECLARE_BSLPROJECTSTATISTICEVT(UPDATE, fn)
#define EVT_BSLPROJECTSTATISTIC_BULKUPDATE(fn)  wx__DECLARE_BSLPROJECTSTATISTICBULKEVT(BULKUPDATE, fn)
#define EVT_BSLPROJECTSTATISTIC_AUDITLOG(fn)    wx__DECLARE_BSLPROJECTSTATISTICAUDITLOGEVT(AUDITLOG, fn)

class CBSLTaskEvent;
class CBSLTaskBulkEvent;
class CBSLTaskAuditLogEvent;

typedef void (wxEvtHandler::*CBSLTaskEventFunction)(CBSLTaskEvent&);
typedef void (wxEvtHandler::*CBSLTaskBulkEventFunction)(CBSLTaskBulkEvent&);
typedef void (wxEvtHandler::*CBSLTaskAuditLogEventFunction)(CBSLTaskAuditLogEvent&);

#define CBSLTaskEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTaskEventFunction, &func)
#define CBSLTaskBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTaskBulkEventFunction, &func)
#define CBSLTaskAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTaskAuditLogEventFunction, &func)

#define wx__DECLARE_BSLTASKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTASK_ ## evt, CBSLTaskEventHandler(fn))
#define wx__DECLARE_BSLTASKBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTASK_ ## evt, CBSLTaskBulkEventHandler(fn))
#define wx__DECLARE_BSLTASKAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTASK_ ## evt, CBSLTaskAuditLogEventHandler(fn))

#define EVT_BSLTASK_ADD(fn)                     wx__DECLARE_BSLTASKEVT(ADD, fn)
#define EVT_BSLTASK_BULKADD(fn)                 wx__DECLARE_BSLTASKBULKEVT(BULKADD, fn)
#define EVT_BSLTASK_DELETE(fn)                  wx__DECLARE_BSLTASKEVT(DELETE, fn)
#define EVT_BSLTASK_BULKDELETE(fn)              wx__DECLARE_BSLTASKBULKEVT(BULKDELETE, fn)
#define EVT_BSLTASK_UPDATE(fn)                  wx__DECLARE_BSLTASKEVT(UPDATE, fn)
#define EVT_BSLTASK_BULKUPDATE(fn)              wx__DECLARE_BSLTASKBULKEVT(BULKUPDATE, fn)
#define EVT_BSLTASK_AUDITLOG(fn)                wx__DECLARE_BSLTASKAUDITLOGEVT(AUDITLOG, fn)

class CBSLTaskInstanceEvent;
class CBSLTaskInstanceBulkEvent;
class CBSLTaskInstanceAuditLogEvent;

typedef void (wxEvtHandler::*CBSLTaskInstanceEventFunction)(CBSLTaskInstanceEvent&);
typedef void (wxEvtHandler::*CBSLTaskInstanceBulkEventFunction)(CBSLTaskInstanceBulkEvent&);
typedef void (wxEvtHandler::*CBSLTaskInstanceAuditLogEventFunction)(CBSLTaskInstanceAuditLogEvent&);

#define CBSLTaskInstanceEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTaskInstanceEventFunction, &func)
#define CBSLTaskInstanceBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTaskInstanceBulkEventFunction, &func)
#define CBSLTaskInstanceAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTaskInstanceAuditLogEventFunction, &func)

#define wx__DECLARE_BSLTASKINSTANCEEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTASKINSTANCE_ ## evt, CBSLTaskInstanceEventHandler(fn))
#define wx__DECLARE_BSLTASKINSTANCEBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTASKINSTANCE_ ## evt, CBSLTaskInstanceBulkEventHandler(fn))
#define wx__DECLARE_BSLTASKINSTANCEAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTASKINSTANCE_ ## evt, CBSLTaskInstanceAuditLogEventHandler(fn))

#define EVT_BSLTASKINSTANCE_ADD(fn)             wx__DECLARE_BSLTASKINSTANCEEVT(ADD, fn)
#define EVT_BSLTASKINSTANCE_BULKADD(fn)         wx__DECLARE_BSLTASKINSTANCEBULKEVT(BULKADD, fn)
#define EVT_BSLTASKINSTANCE_DELETE(fn)          wx__DECLARE_BSLTASKINSTANCEEVT(DELETE, fn)
#define EVT_BSLTASKINSTANCE_BULKDELETE(fn)      wx__DECLARE_BSLTASKINSTANCEBULKEVT(BULKDELETE, fn)
#define EVT_BSLTASKINSTANCE_UPDATE(fn)          wx__DECLARE_BSLTASKINSTANCEEVT(UPDATE, fn)
#define EVT_BSLTASKINSTANCE_BULKUPDATE(fn)      wx__DECLARE_BSLTASKINSTANCEBULKEVT(BULKUPDATE, fn)
#define EVT_BSLTASKINSTANCE_AUDITLOG(fn)        wx__DECLARE_BSLTASKINSTANCEAUDITLOGEVT(AUDITLOG, fn)

class CBSLTransferEvent;
class CBSLTransferBulkEvent;
class CBSLTransferAuditLogEvent;

typedef void (wxEvtHandler::*CBSLTransferEventFunction)(CBSLTransferEvent&);
typedef void (wxEvtHandler::*CBSLTransferBulkEventFunction)(CBSLTransferBulkEvent&);
typedef void (wxEvtHandler::*CBSLTransferAuditLogEventFunction)(CBSLTransferAuditLogEvent&);

#define CBSLTransferEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTransferEventFunction, &func)
#define CBSLTransferBulkEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTransferBulkEventFunction, &func)
#define CBSLTransferAuditLogEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CBSLTransferAuditLogEventFunction, &func)

#define wx__DECLARE_BSLTRANSFEREVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTRANSFER_ ## evt, CBSLTransferEventHandler(fn))
#define wx__DECLARE_BSLTRANSFERBULKEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTRANSFER_ ## evt, CBSLTransferBulkEventHandler(fn))
#define wx__DECLARE_BSLTRANSFERAUDITLOGEVT(evt, fn) \
    wx__DECLARE_EVT0(wxEVT_BSLTRANSFER_ ## evt, CBSLTransferAuditLogEventHandler(fn))

#define EVT_BSLTRANSFER_ADD(fn)                 wx__DECLARE_BSLTRANSFEREVT(ADD, fn)
#define EVT_BSLTRANSFER_BULKADD(fn)             wx__DECLARE_BSLTRANSFERBULKEVT(BULKADD, fn)
#define EVT_BSLTRANSFER_DELETE(fn)              wx__DECLARE_BSLTRANSFEREVT(DELETE, fn)
#define EVT_BSLTRANSFER_BULKDELETE(fn)          wx__DECLARE_BSLTRANSFERBULKEVT(BULKDELETE, fn)
#define EVT_BSLTRANSFER_UPDATE(fn)              wx__DECLARE_BSLTRANSFEREVT(UPDATE, fn)
#define EVT_BSLTRANSFER_BULKUPDATE(fn)          wx__DECLARE_BSLTRANSFERBULKEVT(BULKUPDATE, fn)
#define EVT_BSLTRANSFER_AUDITLOG(fn)            wx__DECLARE_BSLTRANSFERAUDITLOGEVT(AUDITLOG, fn)

#endif
