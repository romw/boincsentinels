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
#include "bslversion.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "Vulture.h"


void DisplayLogo(){
    printf("BOINC Sentinels Vulture %s \n", PACKAGE_VERSION);
    printf("The BOINC Sentinels Command Line Interface\n\n");
}

void DisplayUsage(){
    fprintf(stderr, "\n\
usage: vulture [--host host] [--password password] [--port port] command\n\n\
Commands:\n\
"
);
    exit(1);
}



int main(int argc, char* argv[])
{
    wxInitialize();

    BSLERRCODE rc = BSLERR_FAILURE;
    CBSLClient* pClient = new CBSLClient();
    BSLHOST hHost = NULL;
    CBSLHost* pHost = new CBSLHost();
    wxString strDataDirectory;
    wxString strConnectionName;
    wxString strConnectionPassword;
    long lConnectionPort;

    // Initialize BSLClient
    //
    pClient->OnInit();

    // Get Default Values
    //
    pClient->GetLocalHostName(strConnectionName);
    pClient->GetLocalHostPassword(strConnectionPassword);
    pClient->GetLocalHostPort(lConnectionPort);

    // Parse Command Line Options
    //

    // Display Logo
    //
    DisplayLogo();

    // Initiate a connection to the host
    rc = pClient->Connect(strConnectionName, strConnectionPassword, lConnectionPort, true, &hHost);
    if (BSLERR_SUCCESS == rc)
    {
        pClient->GetHost(hHost, pHost);
        printf(
            "Connected too %s (BOINC Version %d.%d.%d)\n",
            (const char*)pHost->GetName().mb_str(),
            pHost->GetClientVersionMajor(),
            pHost->GetClientVersionMinor(),
            pHost->GetClientVersionRelease()
        );
    }
    else
    {
        printf("Connect Failed (%d)!\n", rc);
    }

    // Disconnect from host
    rc = pClient->Disconnect(hHost);

    // Cleanup
    //
    pClient->OnExit();
    wxUninitialize();

    return rc;
}

