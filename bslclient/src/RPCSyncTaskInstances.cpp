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
#include "Instance.h"
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateEvents.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "EventManager.h"
#include "RPCProtocol.h"
#include "RPCSyncTaskInstances.h"

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncTaskInstances, CRPCProtocol);

CRPCSyncTaskInstances::CRPCSyncTaskInstances():
    CRPCProtocol(wxT("get_results"), sizeof(wxT("get_results")))
{
}

CRPCSyncTaskInstances::~CRPCSyncTaskInstances()
{
}

wxString CRPCSyncTaskInstances::GetRequest()
{
    wxString strRequest;

    strRequest.Printf(
        wxT("%s\n")
        wxT("  <%s>\n")
        wxT("    <active_only>0</active_only>\n")
        wxT("  </%s>\n")
        wxT("%s\n"),
        GetRequestHeader(),
        GetRequestName(),
        GetRequestName(),
        GetRequestFooter()
    );

    return strRequest;
}

BSLERRCODE CRPCSyncTaskInstances::ParseResponse(CHost* pHost, wxString& strResponse)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;
    CBSLTaskInstance bslTaskInstance, bslTaskInstanceData;
    CProject* pProject = NULL;
    CApp* pApp = NULL;
    CAppVersion* pAppVersion = NULL;
    CTask* pTask = NULL;
    CTaskInstance* pTaskInstance = NULL;
    std::vector<BSLHANDLE> oBulkAdd;
    std::vector<BSLHANDLE> oBulkUpdate;

    oDocument.SetDocument(strResponse);
    oBulkAdd.reserve(GetEventManager()->GetOptimialQueueSize());
    oBulkUpdate.reserve(GetEventManager()->GetOptimialQueueSize());

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_TASKINSTANCE == oElement.GetNameHash()) 
        {
            bslTaskInstance.Clear();
            bslTaskInstance.ParseEx(oDocument);

            if (BSLERR_SUCCESS == pHost->FindProject(bslTaskInstance.GetProjectHash(), &pProject))
            {
                // Setup known handles
                bslTaskInstance.SetHostHandle(pHost);
                bslTaskInstance.SetProjectHandle(pProject);

                // Update existing record if it already exists
                if (BSLERR_SUCCESS == pHost->FindTaskInstance(bslTaskInstance.GetProjectHash(), bslTaskInstance.GetNameHash(), &pTaskInstance, &bslTaskInstanceData))
                {
                    // Add missing handles
                    bslTaskInstance.SetAppHandle(bslTaskInstanceData.GetAppHandle());
                    bslTaskInstance.SetAppVersionHandle(bslTaskInstanceData.GetAppVersionHandle());
                    bslTaskInstance.SetTaskHandle(bslTaskInstanceData.GetTaskHandle());
                    bslTaskInstance.SetTaskInstanceHandle(bslTaskInstanceData.GetTaskInstanceHandle());
                    bslTaskInstance.SetData(bslTaskInstanceData.GetData());

                    // Only update if something has changed
                    if (BSLERR_SUCCESS == pTaskInstance->Update(bslTaskInstance))
                    {
                        oBulkUpdate.push_back(pTaskInstance->GetTaskInstanceHandle());
                    }
                }
                else
                {
                    // Add missing handles
                    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindTask(
                        bslTaskInstance.GetProjectHash(),
                        bslTaskInstance.GetTaskNameHash(),
                        &pTask
                    ))
                    {
                        continue;
                    }

                    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindApp(
                        bslTaskInstance.GetProjectHash(),
                        bslTaskInstance.GetAppNameHash(),
                        &pApp
                    ))
                    {
                        continue;
                    }

                    if (BSLERR_OBJECT_NOT_FOUND == pHost->FindAppVersion(
                        bslTaskInstance.GetProjectHash(),
                        bslTaskInstance.GetAppNameHash(),
                        bslTaskInstance.GetAppVersion(),
                        bslTaskInstance.GetAppPlanClassHash(),
                        &pAppVersion
                    ))
                    {
                        continue;
                    }

                    bslTaskInstance.SetAppHandle(pApp);
                    bslTaskInstance.SetAppVersionHandle(pAppVersion);
                    bslTaskInstance.SetTaskHandle(pTask);

                    // Add the new task instance
                    pTaskInstance = new CTaskInstance(bslTaskInstance);
                    pHost->AddTaskInstance(pTaskInstance);

                    oBulkAdd.push_back(pTaskInstance->GetTaskInstanceHandle());
                }
            }
            else
            {
                rc = BSLERR_OBJECT_NOT_FOUND;
            }

        }
    }

    GetEventManager()->FireBulkEvent(wxEVT_BSLTASKINSTANCE_BULKADD, pHost, oBulkAdd);
    GetEventManager()->FireBulkEvent(wxEVT_BSLTASKINSTANCE_BULKUPDATE, pHost, oBulkUpdate);

    return rc;
}
