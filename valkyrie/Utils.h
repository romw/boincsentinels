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

#ifndef _UTILS_H_
#define _UTILS_H_

class CUtils
{
    DECLARE_NO_COPY_CLASS(CUtils)

public:
    CUtils();
    virtual ~CUtils();

    static wxString ConstructByteCount(wxUint64 ullSize, wxUint64 ullTotal = 0);
    static wxString ConstructByteRate(wxUint64 ullSize);
    static wxString ConstructFLOPCount(wxUint64 ullSize);
    static wxString ConstructRPCReason(CBSLProject::RPCREASON srReason);
    static wxString ConstructSuspendReason(CBSLHostStatus::SUSPENDREASON srReason);
    static wxString ConstructProjectStatus(CBSLProject& bslProject);
    static wxString ConstructTaskInstanceAppVersion(CBSLTaskInstance& bslTaskInstance);
    static wxString ConstructTaskInstanceCPUTime(CBSLTaskInstance& bslTaskInstance);
    static wxString ConstructTaskInstancePercentage(CBSLTaskInstance& bslTaskInstance);
    static wxString ConstructTaskInstanceStatus(CBSLTaskInstance& bslTaskInstance);
    static wxString ConstructTransferStatus(CBSLTransfer& bslTransfer);
    static void AppendStatusMessage(wxString& strBuffer, wxString strMessage);
    static void LaunchGraphics(CBSLTaskInstance& bslTaskInstance);
    static void LaunchWebGraphics(CBSLTaskInstance& bslTaskInstance);
    static void LaunchRemoteDesktop(CBSLTaskInstance& bslTaskInstance);
};

#endif
