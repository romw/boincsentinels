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
#include "Lancer.h"
#include "SkinManager.h"

// XPM Images


CSkinManager::CSkinManager() :
wxObject()
{
    m_BOINCSentinels.AddIcon(wxICON(boincsentinels));
}

CSkinManager::~CSkinManager()
{
}

wxIconBundle& CSkinManager::GetBOINCSentinelsIcons()
{
    return m_BOINCSentinels;
}

