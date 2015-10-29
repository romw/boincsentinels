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
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "BOINCXMLStream.h"
#include "BOINCNativeParsers.h"
#include "BOINCNativeTaskInstance.h"
#include "BOINCParsers.h"

void BOINCV1ParserTaskInstances(CBOINCXMLStream& oXML, std::vector<TASKINSTANCE*>& oTaskInstances)
{
    TASKINSTANCE* pTaskInstance;

    while (oXML.ReadNextLine())
    {
        if (oXML.CurrentLineMatchesTag(wxT("<result>")))
        {
            pTaskInstance = new TASKINSTANCE();
            pTaskInstance->Parse(oXML);
            oTaskInstances.push_back(pTaskInstance);
        }
    }
}

void BOINCV2ParserTaskInstances(CBOINCXMLStream& oXML, std::vector<TASKINSTANCE*>& oTaskInstances)
{
    TASKINSTANCE* pTaskInstance;
    MIOFILE mf;
    XML_PARSER xp(&mf);

    mf.init_buf_read(oXML.GetCurrentPosition());
    if (!xp.parse_start(wxT("boinc_gui_rpc_reply"))) {
        return;
    }

    while (!xp.get_tag())
    {
        if (!xp.is_tag) {
            _ftprintf(stderr, wxT("unexpected text: %s\n"), xp.parsed_tag);
            continue;
        }
        if (xp.match_tag(wxT("boinc_gui_rpc_reply"))) continue;
        if (xp.match_tag(wxT("/boinc_gui_rpc_reply"))) {
            continue;
        }
        else if (xp.match_tag(wxT("results"))) continue;
        else if (xp.match_tag(wxT("/results"))) continue;
        else if (xp.match_tag(wxT("result")))
        {
            pTaskInstance = new TASKINSTANCE();
            pTaskInstance->ParseV2(xp);
            oTaskInstances.push_back(pTaskInstance);
        }
        else
        {
            xp.skip_unexpected(true, wxT("main loop"));
        }
    }
}
