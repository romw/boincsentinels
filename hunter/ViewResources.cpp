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
//#include "bsconfig.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Events.h"
#include "Hunter.h"
#include "ConfigManager.h"
#include "SkinManager.h"
#include "BOINCTaskCtrl.h"
#include "BOINCListCtrl.h"
#include "ViewBase.h"
#include "ViewResources.h"


DEFINE_EVENT_TYPE(wxEVT_VIEWRESOURCES_INIT);

IMPLEMENT_DYNAMIC_CLASS(CViewResources, CViewBase);

BEGIN_EVENT_TABLE(CViewResources, CViewBase)
END_EVENT_TABLE();

CViewResources::CViewResources()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CViewResources::CViewResources - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CViewResources::CViewResources - Function End"));
}


CViewResources::CViewResources(wxNotebook* pNotebook, BSLHOST hHost) :
CViewBase(pNotebook)
{
}


CViewResources::~CViewResources()
{
    wxLogTrace(wxT("Function Start/End"), wxT("CViewResources::~CViewResources - Function Begin"));
    wxLogTrace(wxT("Function Start/End"), wxT("CViewResources::~CViewResources - Function End"));
}


wxString& CViewResources::GetViewName()
{
    static wxString strViewName(wxT("Disk"));
    return strViewName;
}


wxString& CViewResources::GetViewDisplayName()
{
    static wxString strViewName(_("Disk"));
    return strViewName;
}


wxImage& CViewResources::GetViewIcon()
{
    return wxGetApp().GetSkinManager()->GetResourcesIcon();
}


const int CViewResources::GetViewRefreshRate()
{
    return 10;
}


const int CViewResources::GetViewCurrentViewPage()
{
    return 0;
}
