// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#include "stdwx.h"
#include "ViewBase.h"
#include "BOINCListCtrl.h"
#include "Events.h"


IMPLEMENT_DYNAMIC_CLASS(CBOINCListCtrl, wxListView)


CBOINCListCtrl::CBOINCListCtrl()
{
}


CBOINCListCtrl::CBOINCListCtrl( CViewBase* pView, wxWindowID iListWindowID, wxInt32 iListWindowFlags ) :
    wxListView( pView, iListWindowID, wxDefaultPosition, wxSize(-1, -1), iListWindowFlags )
{
    m_pParentView = pView;
    EnableAlternateRowColours(true);
}


CBOINCListCtrl::~CBOINCListCtrl()
{
}


wxString CBOINCListCtrl::OnGetItemText(long item, long column) const {
    return m_pParentView->FireOnListGetItemText(item, column);
}


int CBOINCListCtrl::OnGetItemImage(long item) const {
    return m_pParentView->FireOnListGetItemImage(item);
}

