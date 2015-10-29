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

#ifndef _DLGACTIVETASK_H_
#define _DLGACTIVETASK_H_

#define ID_DIALOG 10000
#define SYMBOL_CDLGACTIVETASK_STYLE wxDEFAULT_DIALOG_STYLE
#define SYMBOL_CDLGACTIVETASK_TITLE wxT("")
#define SYMBOL_CDLGACTIVETASK_IDNAME ID_DIALOG
#define SYMBOL_CDLGACTIVETASK_SIZE wxSize(400, 300)
#define SYMBOL_CDLGACTIVETASK_POSITION wxDefaultPosition
#define ID_TASK 10001
#define ID_APP 10002
#define ID_PROJECT 10003
#define ID_STATUS 10004
#define ID_RECEIVED 10005
#define ID_DEADLINE 10006
#define ID_RESOURCES 10007
#define ID_ESTIMATEDCOMPUTATION 10008
#define ID_CPUTIME 10009
#define ID_CPUTIMELASTCHECKPOINT 10010
#define ID_ELAPSEDTIME 10011
#define ID_TIMEREMAINING 10012
#define ID_FRACTIONDONE 10013
#define ID_VIRTUALMEMORY 10014
#define ID_WORKINGSET 10015
#define ID_DIRECTORY 10016
#define ID_PROCESSID 10017

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

class CDlgStaticText;
class CDlgDateTime;
class CDlgTimeSpan;
class CDlgUint32;
class CDlgProgress;
class CDlgByteCount;
class CDlgFLOPCount;

class CDlgActiveTask: public wxDialog
{
    DECLARE_DYNAMIC_CLASS(CDlgActiveTask)
    DECLARE_EVENT_TABLE()

public:
    CDlgActiveTask();
    CDlgActiveTask(BSLHOST hHost, BSLTASKINSTANCE hTaskInstance);
    CDlgActiveTask(wxWindow* parent, wxWindowID id = SYMBOL_CDLGACTIVETASK_IDNAME, const wxString& caption =
        SYMBOL_CDLGACTIVETASK_TITLE, const wxPoint& pos = SYMBOL_CDLGACTIVETASK_POSITION,
        const wxSize& size = SYMBOL_CDLGACTIVETASK_SIZE, long style = SYMBOL_CDLGACTIVETASK_STYLE);
    virtual ~CDlgActiveTask();

    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_CDLGACTIVETASK_IDNAME, const wxString& caption =
        SYMBOL_CDLGACTIVETASK_TITLE, const wxPoint& pos = SYMBOL_CDLGACTIVETASK_POSITION,
        const wxSize& size = SYMBOL_CDLGACTIVETASK_SIZE, long style = SYMBOL_CDLGACTIVETASK_STYLE);

    void OnTaskInstanceUpdate(CBSLTaskInstanceEvent& event);

private:
    void CreateControls();
    void UpdateControls(CBSLTaskInstance& bslTaskInstance);

    BSLHOST m_hHost;
    BSLTASKINSTANCE m_hTaskInstance;

    CDlgStaticText* m_pTaskCtrl;
    CDlgStaticText* m_pAppCtrl;
    CDlgStaticText* m_pProjectCtrl;
    CDlgStaticText* m_pStatusCtrl;
    CDlgDateTime* m_pReceivedCtrl;
    CDlgDateTime* m_pDeadlineCtrl;
    CDlgStaticText* m_pResourcesCtrl;
    CDlgFLOPCount* m_pEstimatedComputationCtrl;
    CDlgTimeSpan* m_pCPUTimeCtrl;
    CDlgTimeSpan* m_pCPUTimeLastCheckpointCtrl;
    CDlgTimeSpan* m_pElapsedTimeCtrl;
    CDlgTimeSpan* m_pTimeRemainingCtrl;
    CDlgProgress* m_pFractionDoneCtrl;
    CDlgByteCount* m_pVirtualMemoryCtrl;
    CDlgByteCount* m_pWorkingSetCtrl;
    CDlgStaticText* m_pDirectoryCtrl;
    CDlgUint32* m_pProcessIDCtrl;
};

#endif
// _DLGACTIVETASK_H_
