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
#include "TaskInstancePerf.h"

int main(int , char**)
{
    unsigned long ulElapsedTime = 0;

    wxInitialize();

    wxPrintf(wxT("Task Instance Performance Measurement...\n"));
    ParserTaskInstances(ulElapsedTime);
    wxPrintf(wxT("Task Instance 100000 Records: '%d' milliseconds\n"), ulElapsedTime);

    wxUninitialize();

    return 0;
}

