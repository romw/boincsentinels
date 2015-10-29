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
#include "Hunter.h"
#include "Utils.h"

#ifdef __WXMAC__
#include <Carbon/Carbon.h>
#endif

CUtils::CUtils()
{
}

CUtils::~CUtils()
{
}

wxString CUtils::ConstructByteCount(wxUint64 ullSize, wxUint64 ullTotal)
{
    wxString strBuffer;
    wxDouble xTERA = (1024.0*1024.0*1024.0*1024.0);
    wxDouble xGIGA = (1024.0*1024.0*1024.0);
    wxDouble xMEGA = (1024.0*1024.0);
    wxDouble xKILO = (1024.0);

    if (0 != ullTotal)
    {
        if (ullSize >= xTERA)
        {
            strBuffer.Printf(_("%0.2f/%0.2f TB"), ullSize/xTERA, ullTotal/xTERA);
        }
        else if (ullSize >= xGIGA)
        {
            strBuffer.Printf(_("%0.2f/%0.2f GB"), ullSize/xGIGA, ullTotal/xTERA);
        }
        else if (ullSize >= xMEGA)
        {
            strBuffer.Printf(_("%0.2f/%0.2f MB"), ullSize/xMEGA, ullTotal/xTERA);
        }
        else if (ullSize >= xKILO)
        {
            strBuffer.Printf(_("%0.2f/%0.2f KB"), ullSize/xKILO, ullTotal/xTERA);
        }
        else
        {
            strBuffer.Printf(_("%0.0f/%0.0f bytes"), ullSize, ullTotal);
        }
    }
    else
    {
        if (ullSize >= xTERA)
        {
            strBuffer.Printf(_("%0.2f TB"), ullSize/xTERA);
        }
        else if (ullSize >= xGIGA)
        {
            strBuffer.Printf(_("%0.2f GB"), ullSize/xGIGA);
        }
        else if (ullSize >= xMEGA)
        {
            strBuffer.Printf(_("%0.2f MB"), ullSize/xMEGA);
        }
        else if (ullSize >= xKILO)
        {
            strBuffer.Printf(_("%0.2f KB"), ullSize/xKILO);
        }
        else
        {
            strBuffer.Printf(_("%0.0f bytes"), ullSize);
        }
    }

    return strBuffer;
}

wxString CUtils::ConstructByteRate(wxUint64 ullSize)
{
    wxString strBuffer;
    wxDouble xTERA = (1024.0*1024.0*1024.0*1024.0);
    wxDouble xGIGA = (1024.0*1024.0*1024.0);
    wxDouble xMEGA = (1024.0*1024.0);
    wxDouble xKILO = (1024.0);

    if (ullSize >= xTERA)
    {
        strBuffer.Printf(_("%0.2f TBps"), ullSize/xTERA);
    }
    else if (ullSize >= xGIGA)
    {
        strBuffer.Printf(_("%0.2f GBps"), ullSize/xGIGA);
    }
    else if (ullSize >= xMEGA)
    {
        strBuffer.Printf(_("%0.2f MBps"), ullSize/xMEGA);
    }
    else if (ullSize >= xKILO)
    {
        strBuffer.Printf(_("%0.2f KBps"), ullSize/xKILO);
    }
    else
    {
        strBuffer.Printf(_("%0.0f bps"), ullSize);
    }

    return strBuffer;
}

wxString CUtils::ConstructFLOPCount(wxUint64 ullSize)
{
    wxString strBuffer;
    wxDouble xEXA = 1e18;
    wxDouble xPETA = 1e15;
    wxDouble xTERA = 1e12;
    wxDouble xGIGA = 1e9;
    wxDouble xMEGA = 1e6;
    wxDouble xKILO = 1e3;

    if (ullSize >= xEXA)
    {
        strBuffer.Printf(_("%0.2f EFLOPS"), ullSize/xEXA);
    }
    else if (ullSize >= xPETA)
    {
        strBuffer.Printf(_("%0.2f PFLOPS"), ullSize/xPETA);
    }
    else if (ullSize >= xTERA)
    {
        strBuffer.Printf(_("%0.2f TFLOPS"), ullSize/xTERA);
    }
    else if (ullSize >= xGIGA)
    {
        strBuffer.Printf(_("%0.2f GFLOPS"), ullSize/xGIGA);
    }
    else if (ullSize >= xMEGA)
    {
        strBuffer.Printf(_("%0.2f MFLOPS"), ullSize/xMEGA);
    }
    else if (ullSize >= xKILO)
    {
        strBuffer.Printf(_("%0.2f KFLOPS"), ullSize/xKILO);
    }
    else
    {
        strBuffer.Printf(_("%0.0f FLOPS"), ullSize);
    }

    return strBuffer;
}

wxString CUtils::ConstructRPCReason(CBSLProject::RPCREASON srReason)
{
    switch (srReason)
    {
        case CBSLProject::RPCReasonUserRequest:
            return _("Requested by volunteer");
        case CBSLProject::RPCReasonTaskInstanceDue:
            return _("To report completed tasks");
        case CBSLProject::RPCReasonNeedWork:
            return _("To fetch work");
        case CBSLProject::RPCReasonTrickleUp:
            return _("To send trickle-up message");
        case CBSLProject::RPCReasonAccountManagerRequest:
            return _("Requested by account manager");
        case CBSLProject::RPCReasonInitialization:
            return _("Project initialization");
        case CBSLProject::RPCReasonProjectRequest:
            return _("Requested by project");
    }
    return _("unknown reason");
}

wxString CUtils::ConstructSuspendReason(CBSLHostStatus::SUSPENDREASON srReason)
{
    switch (srReason)
    {
        case CBSLHostStatus::SuspendReasonBatteries:
            return _("on batteries");
        case CBSLHostStatus::SuspendReasonUserActive:
            return _("computer is in use");
        case CBSLHostStatus::SuspendReasonUserRequest:
            return _("user request");
        case CBSLHostStatus::SuspendReasonTimeOfDay:
            return _("time of day");
        case CBSLHostStatus::SuspendReasonBenchmarks:
            return _("CPU benchmarks in progress");
        case CBSLHostStatus::SuspendReasonDiskSpace:
            return _("need disk space - check preferences");
        case CBSLHostStatus::SuspendReasonUserInactive:
            return _("computer is not in use");
        case CBSLHostStatus::SuspendReasonInitialDelay:
            return _("starting up");
        case CBSLHostStatus::SuspendReasonExclusiveApplicationRunning:
            return _("an exclusive application is running");
        case CBSLHostStatus::SuspendReasonCPUUsage:
            return _("CPU is busy");
        case CBSLHostStatus::SuspendReasonNetworkQuotaExceeded:
            return _("network bandwidth limit exceeded");
        case CBSLHostStatus::SuspendReasonOS:
            return _("requested by operating system");
    }
    return _("unknown reason");
}

wxString CUtils::ConstructProjectTotalCredit(CBSLProject& bslProject)
{
    wxString strBuffer = wxEmptyString;

    strBuffer.Printf(wxT("%0.2f"), bslProject.GetCreditUserTotal());

    return strBuffer;
}

wxString CUtils::ConstructProjectAverageCredit(CBSLProject& bslProject)
{
    wxString strBuffer = wxEmptyString;

    strBuffer.Printf(wxT("%0.2f"), bslProject.GetCreditUserAverage());

    return strBuffer;
}

wxString CUtils::ConstructProjectResourceShare(CBSLProject& bslProject)
{
    wxString strBuffer = wxEmptyString;

    strBuffer.Printf(wxT("%d"), bslProject.GetResourceShare());

    return strBuffer;
}

wxString CUtils::ConstructProjectStatus(CBSLProject& bslProject)
{
    wxString strBuffer = wxEmptyString;
    wxString strBuffer2 = wxEmptyString;

    if (bslProject.IsInterfaceSuspensionEnabled())
    {
        AppendStatusMessage(strBuffer, _("Project suspended by volunteer"));
    }
    if (bslProject.IsTaskAccumulationDisabled())
    {
        AppendStatusMessage(strBuffer, _("Won't get new tasks"));
    }
    if (bslProject.GetSchedulerRPCPending())
    {
        strBuffer2.Printf(
            _("Scheduler request pending, %s"),
            ConstructRPCReason(bslProject.GetSchedulerRPCPending()).c_str()
        );
        AppendStatusMessage(strBuffer, strBuffer2);
    }
    if (bslProject.IsSchedulerRPCInProgress())
    {
        AppendStatusMessage(strBuffer, _("Scheduler request in progress"));
    }
    if (bslProject.IsTricklePending())
    {
        AppendStatusMessage(strBuffer, _("Trickle up message pending"));
    }
    if (bslProject.GetSchedulerRPCMinimumTime() > wxDateTime::Now()) {
        wxTimeSpan tsNextRPC(bslProject.GetSchedulerRPCMinimumTime() - wxDateTime::Now());
        strBuffer2.Printf(
            _("Communication deferred %s"),
            tsNextRPC.Format().c_str()
        );
        AppendStatusMessage(strBuffer, strBuffer2);
    }
    return strBuffer;
}

wxString CUtils::ConstructTaskInstanceAppVersion(CBSLTaskInstance& bslTaskInstance)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLApp bslApp;
    CBSLAppVersion bslAppVersion;
    CBSLProject bslProject;
    wxString strAnonymousBuffer = wxEmptyString;
    wxString strAppBuffer = wxEmptyString;
    wxString strBuffer = wxEmptyString;

    pState->GetApp(bslTaskInstance.GetAppHandle(), &bslApp);
    pState->GetAppVersion(bslTaskInstance.GetAppVersionHandle(), &bslAppVersion);
    pState->GetProject(bslTaskInstance.GetProjectHandle(), &bslProject);

    if (!bslApp.GetUserFriendlyName().IsEmpty()) {
        strAppBuffer = bslApp.GetUserFriendlyName();
    } else {
        strAppBuffer = bslApp.GetName();
    }

    if (bslProject.IsAnonymousPlatformEnabled()) {
        strAnonymousBuffer = _("Local: ");
    }

    if (!bslTaskInstance.GetAppPlanClass().IsEmpty())
    {
        strBuffer.Printf(
            _("%s%s %s (%s)"),
            strAnonymousBuffer.wx_str(),
            strAppBuffer.wx_str(),
            bslTaskInstance.GetAppVersionString().wx_str(),
            bslTaskInstance.GetAppPlanClass().wx_str()
        );
    }
    else
    {
        strBuffer.Printf(
            _("%s%s %s"),
            strAnonymousBuffer.wx_str(),
            strAppBuffer.wx_str(),
            bslTaskInstance.GetAppVersionString().wx_str()
        );
    }

    return strBuffer;
}

wxString CUtils::ConstructTaskInstanceStatus(CBSLTaskInstance& bslTaskInstance)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLHostStatus bslHostStatus;
    CBSLProject bslProject;
    wxString strBuffer = wxEmptyString;

    pState->GetProject(bslTaskInstance.GetProjectHandle(), &bslProject);
    pState->GetHostStatus(bslTaskInstance.GetHostHandle(), &bslHostStatus, false);

    if (bslHostStatus.GetTaskSuspendReason() && bslHostStatus.GetTaskSuspendReason() != CBSLHostStatus::SuspendReasonCPUThrottle)
    {
        strBuffer.Printf(
            _("Suspended (%s)"),
            ConstructSuspendReason(bslHostStatus.GetTaskSuspendReason()).wx_str()
        );
    }
    else if (bslProject.IsInterfaceSuspensionEnabled())
    {
        strBuffer = _("Project suspended by volunteer");
    }
    else if (bslTaskInstance.IsInterfaceSuspensionEnabled())
    {
        strBuffer = _("Task suspended by volunteer");
    }
    else if (bslTaskInstance.IsWaitingOnMemory())
    {
        strBuffer = _("Waiting for memory");
    }
    else if (bslTaskInstance.IsWaitingOnSharedMemory())
    {
        strBuffer = _("Waiting for shared memory");
    }
    else if (bslTaskInstance.GetSchedulerState() == CBSLTaskInstance::SchedulerStatePreempted)
    {
        strBuffer = _("Waiting to run");
    }
    else if (bslTaskInstance.GetSchedulerState() == CBSLTaskInstance::SchedulerStateUninitialized)
    {
        strBuffer = _("Ready to start");
    }
    else if (bslTaskInstance.GetSchedulerState() == CBSLTaskInstance::SchedulerStateScheduled)
    {
        if (bslTaskInstance.IsEDFScheduled())
        {
            if (!bslTaskInstance.GetResourcesUtilized().IsEmpty())
            {
                strBuffer.Printf(
                    _("Running, high priority (%s)"),
                    bslTaskInstance.GetResourcesUtilized().wx_str()
                );
            }
            else
            {
                strBuffer = _("Running, high priority");
            }
        }
        else
        {
            if (!bslTaskInstance.GetResourcesUtilized().IsEmpty())
            {
                strBuffer.Printf(
                    _("Running (%s)"),
                    bslTaskInstance.GetResourcesUtilized().wx_str()
                );
            }
            else
            {
                strBuffer = _("Running");
            }
        }
    }

    return strBuffer;
}

wxString CUtils::ConstructTaskInstanceCPUTime(CBSLTaskInstance& bslTaskInstance)
{
    wxTimeSpan ts;

    if (bslTaskInstance.IsTaskActive()) {
        ts = bslTaskInstance.GetElapsedTime();
        if (ts.IsNull()) ts = bslTaskInstance.GetCurrentCPUTime();
    } else {
        if(bslTaskInstance.GetTaskState() < CBSLTaskInstance::TaskStateComputeError) {
            ts = 0.0;
        } else {
            ts = bslTaskInstance.GetFinalElapsedTime();
            if (ts.IsNull()) ts = bslTaskInstance.GetFinalCPUTime();
        }
    }

    return ts.Format();
}

wxString CUtils::ConstructTaskInstancePercentage(wxDouble& dPercentage)
{
    wxString strBuffer = wxEmptyString;

    strBuffer.Printf(wxT("%.3f%%"), dPercentage);

    return strBuffer;
}

wxString CUtils::ConstructTransferStatus(CBSLTransfer& bslTransfer)
{
    CBSLClient* pState = wxGetApp().GetState();
    CBSLHostStatus bslHostStatus;
    wxString strBuffer = wxEmptyString;

    pState->GetHostStatus(bslTransfer.GetHostHandle(), &bslHostStatus, false);

    if (bslTransfer.GetProjectBackoff() > 1)
    {
        if (bslTransfer.IsUpload())
        {
            strBuffer.Printf(
                _("Upload: pending (project backoff: %s)"),
                bslTransfer.GetProjectBackoff().Format().wx_str()
            );
        }
        else
        {
            strBuffer.Printf(
                _("Download: pending (project backoff: %s)"),
                bslTransfer.GetProjectBackoff().Format().wx_str()
            );
        }
    }
    else if (bslTransfer.GetNextRequestTime() > wxDateTime::Now())
    {
        wxTimeSpan tsNextRequest(bslTransfer.GetNextRequestTime() - wxDateTime::Now());
        if (bslTransfer.IsUpload())
        {
            strBuffer = _("Upload: retry in ") + tsNextRequest.Format();
        }
        else
        {
            strBuffer = _("Download: retry in ") + tsNextRequest.Format();
        }
    }
    else if (bslHostStatus.GetNetworkSuspendReason())
    {
        if (bslTransfer.IsUpload())
        {
            strBuffer.Printf(
                _("Upload: suspended (%s)"),
                ConstructSuspendReason(bslHostStatus.GetTaskSuspendReason()).wx_str()
            );
        }
        else
        {
            strBuffer.Printf(
                _("Download: suspended (%s)"),
                ConstructSuspendReason(bslHostStatus.GetTaskSuspendReason()).wx_str()
            );
        }
    }
    else
    {
        if (bslTransfer.IsUpload())
        {
            strBuffer = _("Upload: active");
        }
        else
        {
            strBuffer = _("Download: active");
        }
    }

    return strBuffer;
}

wxTimeSpan CUtils::DetermineTaskInstanceCPUTime(CBSLTaskInstance& bslTaskInstance)
{
    wxTimeSpan ts;

    if (bslTaskInstance.IsTaskActive()) {
        ts = bslTaskInstance.GetElapsedTime();
        if (ts.IsNull()) ts = bslTaskInstance.GetCurrentCPUTime();
    } else {
        if(bslTaskInstance.GetTaskState() < CBSLTaskInstance::TaskStateComputeError) {
            ts = 0.0;
        } else {
            ts = bslTaskInstance.GetFinalElapsedTime();
            if (ts.IsNull()) ts = bslTaskInstance.GetFinalCPUTime();
        }
    }

    return ts;
}

wxDouble CUtils::DetermineTaskInstancePercentage(CBSLTaskInstance& bslTaskInstance)
{
    wxDouble dbl = 0.0;

    if (bslTaskInstance.IsTaskActive()) {
        dbl = floor(bslTaskInstance.GetFractionDone() * 100000)/1000;
    } else {
        if(bslTaskInstance.GetTaskState() < CBSLTaskInstance::TaskStateComputeError) {
            dbl = 0.0;
        } else {
            dbl = 100.0;
        }
    }

    return dbl;
}

void CUtils::AppendStatusMessage(wxString& strBuffer, wxString strMessage)
{
    if (strBuffer.IsEmpty())
    {
        strBuffer = strMessage;
    }
    else
    {
        strBuffer += wxT(", ") + strMessage;
    }

}

void CUtils::LaunchGraphics(CBSLTaskInstance& bslTaskInstance)
{
    if (!bslTaskInstance.GetGraphicsApplication().IsEmpty())
    {
        wxString strCWD = ::wxGetCwd();
        wxString strNWD = bslTaskInstance.GetSlotDirectory();

        ::wxSetWorkingDirectory(strNWD);
        wxExecute(bslTaskInstance.GetGraphicsApplication());
        ::wxSetWorkingDirectory(strCWD);
    }
}

void CUtils::LaunchWebGraphics(CBSLTaskInstance& bslTaskInstance)
{
    if (!bslTaskInstance.GetWebGraphicsApplication().IsEmpty())
    {
        wxLaunchDefaultBrowser(bslTaskInstance.GetWebGraphicsApplication());
    }
}

void CUtils::LaunchRemoteDesktop(CBSLTaskInstance& bslTaskInstance)
{
    if (!bslTaskInstance.GetRemoteDesktopAddress().IsEmpty())
    {
        wxString strConnection(bslTaskInstance.GetRemoteDesktopAddress());
        wxString strCommand;

#if   defined(__WXMSW__)
        strCommand = wxT("mstsc.exe /v:") + strConnection;
        wxExecute(strCommand);
#elif defined(__WXGTK__)
        strCommand = wxT("rdesktop-vrdp ") + strConnection;
        wxExecute(strCommand);
#elif defined(__WXMAC__)
        FSRef theFSRef;
        OSStatus status = noErr;

        status = LSFindApplicationForInfo('RDC#', CFSTR("net.sf.cord"), NULL, &theFSRef, NULL);
        if (status != noErr)
        {
            ::wxMessageBox(
                _("Please download and install the CoRD application from http://cord.sourceforge.net"),
                _("Missing application"),
                wxOK | wxICON_INFORMATION
            );
        }
        else
        {
            strCommand = wxT("osascript -e 'tell application \"CoRD\"' -e 'activate' -e 'open location \"rdp://") + strConnection + wxT("\"' -e 'end tell'");
            strCommand.Replace(wxT("localhost"), wxT("127.0.0.1"));
            system(strCommand.char_str());
        }
#endif
    }
}
