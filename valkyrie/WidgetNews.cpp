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
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Valkyrie.h"
#include "NotificationManager.h"
#include "SkinManager.h"
#include "WidgetControls.h"
#include "WidgetBase.h"
#include "WidgetNews.h"
#include "DlgNotifications.h"


DEFINE_EVENT_TYPE(wxEVT_WIDGETNEWS_INIT);

IMPLEMENT_DYNAMIC_CLASS(CWidgetNews, CWidgetBase);

BEGIN_EVENT_TABLE(CWidgetNews, CWidgetBase)
    EVT_WIDGETNEWS_INIT(CWidgetNews::OnInit)
    EVT_BSLNOTIFICATION_ADD(CWidgetNews::OnNotificationUpdate)
    EVT_BSLNOTIFICATION_DELETE(CWidgetNews::OnNotificationUpdate)
    EVT_BSLNOTIFICATION_UPDATE(CWidgetNews::OnNotificationUpdate)
    EVT_BUTTON(ID_WIDGETNEWSPROPERTIES, CWidgetNews::OnProperties)
END_EVENT_TABLE();

CWidgetNews::CWidgetNews()
{
}

CWidgetNews::CWidgetNews(wxWindow* pParent, BSLHOST hHost) :
CWidgetBase(pParent, ID_WIDGETNEWS, _("News"))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::CWidgetNews - Function Begin"));

    m_uiAlertCount = 0;
    m_uiAnnouncementCount = 0;
    m_pButtonBar = NULL;
    m_pButtonBarSizer = NULL;
    m_pAlertCountCtrl = NULL;
    m_pAlertIconCtrl = NULL;
    m_pAnnouncementCountCtrl = NULL;
    m_pAnnouncementIconCtrl = NULL;
    m_pPropertiesCtrl = NULL;

    m_hHost = hHost;

    CBSLClient* pState = wxGetApp().GetState();

    // Create Controls
    CreateControls(false, false, true);

    // Register for any future notification events
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_ADD, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_DELETE, m_hHost, NULL);
    pState->RegisterEventHandler(this, wxEVT_BSLNOTIFICATION_UPDATE, m_hHost, NULL);

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_WIDGETNEWS_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::CWidgetNews - Function End"));
}

CWidgetNews::~CWidgetNews()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::~CWidgetNews - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::~CWidgetNews - Function End"));
}

bool CWidgetNews::OnCreateButtonBar(wxWindow* pParent, CSkinManager* pSkin, wxSize oIconSize)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::OnCreateButtonBar - Function Begin"));

    m_pButtonBar = pParent;
    m_pButtonBarSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pButtonBar->SetSizer(m_pButtonBarSizer);

    m_pAlertCountCtrl = new CWidgetStaticText( m_pButtonBar, ID_WIDGETNEWSALERTCOUNT, wxT("0"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_pButtonBarSizer->Add(m_pAlertCountCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 5);

    m_pAlertIconCtrl = new CWidgetStaticBitmap( m_pButtonBar, ID_WIDGETNEWSALERTICON, pSkin->GetAlertIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pButtonBarSizer->Add(m_pAlertIconCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 5);

    m_pAnnouncementCountCtrl = new CWidgetStaticText( m_pButtonBar, ID_WIDGETNEWSANNOUNCEMENTCOUNT, wxT("0"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
    m_pButtonBarSizer->Add(m_pAnnouncementCountCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 5);

    m_pAnnouncementIconCtrl = new CWidgetStaticBitmap( m_pButtonBar, ID_WIDGETNEWSANNOUNCEMENTICON, pSkin->GetNotificationIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pButtonBarSizer->Add(m_pAnnouncementIconCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 5);

    m_pPropertiesCtrl = new CWidgetBitmapButton( m_pButtonBar, ID_WIDGETNEWSPROPERTIES, pSkin->GetPropertiesIcon(oIconSize), wxDefaultPosition, oIconSize, wxNO_BORDER );
    m_pPropertiesCtrl->SetToolTip(_("View Details"));
    m_pButtonBarSizer->Add(m_pPropertiesCtrl, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER, 0);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::OnCreateButtonBar - Function End"));
    return true;
}

void CWidgetNews::OnInit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::OnInit - Function Begin"));

    CBSLClient* pState = wxGetApp().GetState();

    // Setup the refresh cycle for notifications
    pState->SetAutoSyncProperty(m_hHost, CBSLClient::AutoSyncPropertyNotificationsUpdateInterval, 1);

    wxLogTrace(wxT("Function Start/End"), wxT("CWidgetNews::OnInit - Function End"));
}

void CWidgetNews::OnNotificationUpdate(CBSLNotificationEvent& WXUNUSED(event))
{
    CBSLClient* pState = wxGetApp().GetState();
    CNotificationManager* pNotificationManager = wxGetApp().GetNotificationManager();
    CBSLNotification bslNotification;
    std::vector<BSLNOTIFICATION> oNotifications;

    m_uiAlertCount = 0;
    m_uiAnnouncementCount = 0;

    pState->EnumerateNotifications(m_hHost, 0, oNotifications, false);
    for (std::vector<BSLNOTIFICATION>::iterator iter = oNotifications.begin(); iter != oNotifications.end(); iter++)
    {
        pState->GetNotification(*iter, &bslNotification);

        if (!pNotificationManager->IsRead(bslNotification) && !pNotificationManager->IsDeleted(bslNotification))
        {
            if ((bslNotification.GetCategory() == wxT("scheduler")) || (bslNotification.GetCategory() == wxT("client")))
            {
                m_uiAlertCount++;
            }
            else
            {
                m_uiAnnouncementCount++;
            }
        }
    }

    UpdateInterface();
}

void CWidgetNews::OnProperties(wxCommandEvent& WXUNUSED(event))
{
    CDlgNotifications dlgNotifications(m_hHost);
    dlgNotifications.ShowModal();
}

void CWidgetNews::UpdateInterface()
{
    wxString strBuffer;

    strBuffer.Printf(wxT("%d"), m_uiAlertCount);
    m_pAlertCountCtrl->SetLabel(strBuffer);

    strBuffer.Printf(wxT("%d"), m_uiAnnouncementCount);
    m_pAnnouncementCountCtrl->SetLabel(strBuffer);
}
