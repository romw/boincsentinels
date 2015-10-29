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
#include "Events.h"
#include "Valkyrie.h"
#include "DlgConnection.h"
#include "StatusPage.h"

// Known HREFs
#define HREFCODE_NEWCONNECTION          1

DEFINE_EVENT_TYPE( wxEVT_STATUSPAGE_INIT);

IMPLEMENT_DYNAMIC_CLASS(CStatusPage, wxPanel);

BEGIN_EVENT_TABLE(CStatusPage, wxPanel)
    EVT_STATUSPAGE_INIT(CStatusPage::OnInit)
    EVT_WEBVIEW_ERROR(ID_STATUSHTMLCTRL, CStatusPage::OnPageError)
    EVT_WEBVIEW_NAVIGATING(ID_STATUSHTMLCTRL, CStatusPage::OnPageLinkClicked)
END_EVENT_TABLE();

CStatusPage::CStatusPage()
{
}

CStatusPage::CStatusPage(wxWindow* pParent)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::CStatusPage - Function Begin"));

    m_pCurrentStatus = NULL;

    // Initialize base class
    //
    Create(pParent, ID_STATUSPAGE);

    // Create UI elements
    //
    CreateControls();

    // Move everything into place
    //
    Layout();

    // Give time for all the controls to figure out their layout and render
    // properly.
    wxCommandEvent evt(wxEVT_STATUSPAGE_INIT);
    AddPendingEvent(evt);

    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::CStatusPage - Function End"));
}

CStatusPage::~CStatusPage()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::~CStatusPage - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::~CStatusPage - Function End"));
}

bool CStatusPage::CreateControls()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::CreateControls - Function Begin"));

    // Create NotebookPage Sizer
    wxFlexGridSizer* pNotebookPageSizer = new wxFlexGridSizer(1, 1, 0, 0);
    pNotebookPageSizer->AddGrowableRow(0);
    pNotebookPageSizer->AddGrowableCol(0);
    SetSizer(pNotebookPageSizer);

    // Treat the status page as an HTML document.
    m_pCurrentStatus = wxWebView::New();
    m_pCurrentStatus->Create( this, ID_STATUSHTMLCTRL, wxWebViewDefaultURLStr, wxDefaultPosition, wxDefaultSize );

    pNotebookPageSizer->Add(m_pCurrentStatus, 1, wxALL | wxGROW);

    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::CreateControls - Function End"));
    return true;
}

void CStatusPage::OnInit(wxCommandEvent& WXUNUSED(event))
{
    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::OnInit - Function Begin"));

    wxString strHTML;
    wxString strHREFText;
    wxString strHREFId;
    wxString strTemp;

    // Start Page Creation
    strHTML += wxT("<html>");
    strHTML += wxT("  <head>");
    strHTML += wxT("  </head>");
    strHTML += wxT("  <body>");

    // Add 'Make a new Connection' link
    strHREFId.Printf(wxT("%d"), HREFCODE_NEWCONNECTION);
    strHREFText.Printf(wxT("%s"), _("Make a new connection"));

    strTemp.Printf(wxT("<a href='%s'>%s</a>"), strHREFId.wx_str(), strHREFText.wx_str());
    strHTML += strTemp;

    // Finish Page Creation
    strHTML += wxT("  </body>");
    strHTML += wxT("</html>");

    m_pCurrentStatus->SetPage(strHTML, wxT("http://"));

    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::OnInit - Function End"));
}

void CStatusPage::OnPageError(wxWebViewEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::OnPageError - Function Begin"));

#define WX_ERROR_CASE(type) \
    case type: \
        category = #type; \
        break;

    wxString category;
    switch (event.GetInt())
    {
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_CONNECTION);
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_CERTIFICATE);
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_AUTH);
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_SECURITY);
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_NOT_FOUND);
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_REQUEST);
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_USER_CANCELLED);
        WX_ERROR_CASE(wxWEBVIEW_NAV_ERR_OTHER);
    }

    wxLogMessage(wxT("Function Status"), "Error; url='" + event.GetURL() + "', error='" + category + " (" + event.GetString() + ")'");


    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::OnPageError - Function End"));
}

void CStatusPage::OnPageLinkClicked(wxWebViewEvent& event)
{
    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::OnPageLinkClicked - Function Begin"));

    int iCommandId = 0;
    wxString url = event.GetURL();

    url.Replace(wxT("about:"), wxT(""));

    url.ToLong((long*) &iCommandId);

    switch (iCommandId)
    {
        case HREFCODE_NEWCONNECTION:
            CDlgConnection dlgNewConnection(this);
            dlgNewConnection.ShowModal();
            break;
    }

    event.Veto();

    wxLogTrace(wxT("Function Start/End"), wxT("CStatusPage::OnPageLinkClicked - Function End"));
}

