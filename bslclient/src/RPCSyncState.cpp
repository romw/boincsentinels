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
#include "RPCSyncState.h"

#define BSLXMLTAGHASH_PRIMARYPLATFORM \
    0xab6b3cba
#define BSLXMLTAGHASH_SUPPORTEDPLATFORM \
    0xf089f7c0

IMPLEMENT_DYNAMIC_CLASS(CRPCSyncState, CRPCProtocol);

CRPCSyncState::CRPCSyncState():
    CRPCProtocol(wxT("get_state"), sizeof(wxT("get_state")))
{
}

CRPCSyncState::~CRPCSyncState()
{
}

BSLERRCODE CRPCSyncState::ParseResponse(CHost* pHost, wxString& strResponse)
{
    BSLERRCODE rc = BSLERR_SUCCESS;
    CBSLXMLDocumentEx oDocument;
    CBSLXMLDictionaryEx oDictionary;
    CBSLXMLElementEx oElement;
    CBSLHost bslHost, bslHostData;
    CBSLProject bslProject, bslProjectData;
    CBSLApp bslApp, bslAppData;
    CBSLAppVersion bslAppVersion, bslAppVersionData;
    CBSLTask bslTask, bslTaskData;
    CBSLTaskInstance bslTaskInstance, bslTaskInstanceData;
    CProject* pProject = NULL;
    CApp* pApp = NULL;
    CAppVersion* pAppVersion = NULL;
    CTask* pTask = NULL;
    CTaskInstance* pTaskInstance = NULL;
    wxString strPrimaryPlatform;
    std::vector<wxString> oSupportedPlatforms;
    std::vector<BSLHANDLE> oBulkProjectAdd, oBulkProjectUpdate;
    std::vector<BSLHANDLE> oBulkAppAdd, oBulkAppUpdate;
    std::vector<BSLHANDLE> oBulkAppVersionAdd, oBulkAppVersionUpdate;
    std::vector<BSLHANDLE> oBulkTaskAdd, oBulkTaskUpdate;
    std::vector<BSLHANDLE> oBulkTaskInstanceAdd, oBulkTaskInstanceUpdate;

    oDocument.SetDocument(strResponse);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_HOST == oElement.GetNameHash()) 
        {
            bslHost.Clear();
            bslHost.ParseEx(oDocument);

            // Setup known handles
            bslHost.SetHostHandle(pHost);
            bslHost.SetData(pHost->GetData());

            // Only update if something has changed
            pHost->Update(bslHost);
        }
        else if (BSLXMLTAGHASH_PROJECT == oElement.GetNameHash())
        {
            bslProject.Clear();
            bslProject.ParseEx(oDocument);

            // Setup known handles
            bslProject.SetHostHandle(pHost);

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindProject(
                bslProject.GetMasterURLHash(),
                &pProject,
                &bslProjectData
            ))
            {
                // Add missing handles
                bslProject.SetProjectHandle(pProject);
                bslProject.SetData(bslProjectData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pProject->Update(bslProject))
                {
                    oBulkProjectUpdate.push_back(pProject->GetProjectHandle());
                }
            }
            else
            {
                pProject = new CProject(bslProject);
                pHost->AddProject(pProject);

                oBulkProjectAdd.push_back(pProject->GetProjectHandle());
            }
            continue;
        }
        else if (BSLXMLTAGHASH_APP == oElement.GetNameHash())
        {
            bslApp.Clear();
            bslApp.ParseEx(oDocument);

            // Setup known handles
            bslApp.SetHostHandle(pHost);
            bslApp.SetProjectHandle(pProject);

            // Setup known values not included in the RPC response
            bslApp.SetProject(bslProject.GetMasterURL(), bslProject.GetMasterURLHash());

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindApp(
                bslApp.GetProjectHash(),
                bslApp.GetNameHash(),
                &pApp,
                &bslAppData
            ))
            {
                // Add missing handles
                bslApp.SetAppHandle(pApp);
                bslApp.SetData(bslAppData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pApp->Update(bslApp))
                {
                    oBulkAppUpdate.push_back(pApp->GetAppHandle());
                }
            }
            else
            {
                pApp = new CApp(bslApp);
                pHost->AddApp(pApp);

                oBulkAppAdd.push_back(pApp->GetAppHandle());
            }
            continue;
        }
        else if (BSLXMLTAGHASH_APPVERSION == oElement.GetNameHash())
        {
            bslAppVersion.Clear();
            bslAppVersion.ParseEx(oDocument);

            // Setup known values not included in the RPC response
            bslAppVersion.SetProject(bslProject.GetMasterURL(), bslProject.GetMasterURLHash());

            // Find handles
            pHost->FindApp(
                bslAppVersion.GetProjectHash(),
                bslAppVersion.GetNameHash(),
                &pApp,
                &bslAppData
            );

            // Setup known handles
            bslAppVersion.SetHostHandle(pHost);
            bslAppVersion.SetProjectHandle(pProject);
            bslAppVersion.SetAppHandle(pApp);

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindAppVersion(
                bslAppVersion.GetProjectHash(),
                bslAppVersion.GetNameHash(),
                bslAppVersion.GetVersion(),
                bslAppVersion.GetPlanClassHash(),
                &pAppVersion,
                &bslAppVersionData
            ))
            {
                // Add missing handles
                bslAppVersion.SetAppVersionHandle(pAppVersion);
                bslAppVersion.SetData(bslAppVersionData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pAppVersion->Update(bslAppVersion))
                {
                    oBulkAppVersionUpdate.push_back(pAppVersion->GetAppVersionHandle());
                }
            }
            else
            {
                pAppVersion = new CAppVersion(bslAppVersion);
                pHost->AddAppVersion(pAppVersion);

                oBulkAppVersionAdd.push_back(pAppVersion->GetAppVersionHandle());
            }
            continue;
        }
        else if (BSLXMLTAGHASH_TASK == oElement.GetNameHash())
        {
            bslTask.Clear();
            bslTask.ParseEx(oDocument);

            // Setup known values not included in the RPC response
            bslTask.SetProject(bslProject.GetMasterURL(), bslProject.GetMasterURLHash());

            // Find handles
            pHost->FindApp(
                bslTask.GetProjectHash(),
                bslTask.GetAppNameHash(),
                &pApp,
                &bslAppData
            );

            // Setup known handles
            bslTask.SetHostHandle(pHost);
            bslTask.SetProjectHandle(pProject);
            bslTask.SetAppHandle(pApp);

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindTask(
                bslTask.GetProjectHash(),
                bslTask.GetNameHash(),
                &pTask,
                &bslTaskData
            ))
            {
                // Add missing handles
                bslTask.SetTaskHandle(pTask);
                bslTask.SetData(bslTaskData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pTask->Update(bslTask))
                {
                    oBulkTaskUpdate.push_back(pTask->GetTaskHandle());
                }
            }
            else
            {
                pTask = new CTask(bslTask);
                pHost->AddTask(pTask);

                oBulkTaskAdd.push_back(pTask->GetTaskHandle());
            }
            continue;
        }
        else if (BSLXMLTAGHASH_TASKINSTANCE == oElement.GetNameHash())
        {
            bslTaskInstance.Clear();
            bslTaskInstance.ParseEx(oDocument);

            // Find handles
            pHost->FindTask(
                bslTaskInstance.GetProjectHash(),
                bslTaskInstance.GetTaskNameHash(),
                &pTask,
                &bslTaskData
            );

            GetState()->GetApp(bslTaskData.GetAppHandle(), &bslAppData);

            pHost->FindAppVersion(
                bslTaskInstance.GetProjectHash(),
                bslAppData.GetNameHash(),
                bslTaskInstance.GetAppVersion(),
                bslTaskInstance.GetAppPlanClassHash(),
                &pAppVersion
            );

            // Setup known handles
            bslTaskInstance.SetHostHandle(pHost);
            bslTaskInstance.SetProjectHandle(pProject);
            bslTaskInstance.SetAppHandle(bslAppData.GetAppHandle());
            bslTaskInstance.SetAppVersionHandle(pAppVersion);
            bslTaskInstance.SetTaskHandle(pTask);

            // Update existing record if it already exists
            if (BSLERR_SUCCESS == pHost->FindTaskInstance(
                bslTaskInstance.GetProjectHash(),
                bslTaskInstance.GetNameHash(),
                &pTaskInstance,
                &bslTaskInstanceData
            ))
            {
                // Add missing handles
                bslTaskInstance.SetTaskInstanceHandle(pTaskInstance);
                bslTaskInstance.SetData(bslTaskInstanceData.GetData());

                // Only update if something has changed
                if (BSLERR_SUCCESS == pTaskInstance->Update(bslTaskInstance))
                {
                    oBulkTaskInstanceUpdate.push_back(pTaskInstance->GetTaskInstanceHandle());
                }
            }
            else
            {
                pTaskInstance = new CTaskInstance(bslTaskInstance);
                pHost->AddTaskInstance(pTaskInstance);

                oBulkTaskInstanceAdd.push_back(pTaskInstance->GetTaskInstanceHandle());
            }
            continue;
        }
        else if (BSLXMLTAGHASH_PRIMARYPLATFORM == oElement.GetNameHash())
        {
            strPrimaryPlatform = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
            continue;
        }
        else if (BSLXMLTAGHASH_SUPPORTEDPLATFORM == oElement.GetNameHash())
        {
            oSupportedPlatforms.push_back(CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
            continue;
        }
    }

    // Move the platform information to the CHost object.
    pHost->SetPlatforms(strPrimaryPlatform, oSupportedPlatforms);

    GetEventManager()->FireBulkEvent(wxEVT_BSLPROJECT_BULKADD, pHost, oBulkProjectAdd, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLPROJECT_BULKUPDATE, pHost, oBulkProjectUpdate, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLAPP_BULKADD, pHost, oBulkAppAdd, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLAPP_BULKUPDATE, pHost, oBulkAppUpdate, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLAPPVERSION_BULKADD, pHost, oBulkAppVersionAdd, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLAPPVERSION_BULKUPDATE, pHost, oBulkAppVersionUpdate, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLTASK_BULKADD, pHost, oBulkTaskAdd, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLTASK_BULKUPDATE, pHost, oBulkTaskUpdate, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLTASKINSTANCE_BULKADD, pHost, oBulkTaskInstanceAdd, true);
    GetEventManager()->FireBulkEvent(wxEVT_BSLTASKINSTANCE_BULKUPDATE, pHost, oBulkTaskInstanceUpdate, true);

    return rc;
}
