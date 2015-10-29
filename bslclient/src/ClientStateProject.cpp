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
#include "bslcommon/bslCommonTypes.h"
#include "bslclient/bslClient.h"
#include "ClientStateTypes.h"
#include "ClientState.h"
#include "EventManager.h"

IMPLEMENT_DYNAMIC_CLASS(CProject, CBSLProject);

CProject::CProject() :
CObject(),
CBSLProject()
{
    CObjectLocker olLock(this);

    m_pProjectStatisticsDatabase = new CDatabase<CProjectStatistic*>();
    wxASSERT(m_pProjectStatisticsDatabase);
}

CProject::CProject(const CBSLProject& bslProject) :
CObject(),
CBSLProject()
{
    CObjectLocker olLock(this);

    m_pProjectStatisticsDatabase = new CDatabase<CProjectStatistic*>();
    wxASSERT(m_pProjectStatisticsDatabase);

    *this = bslProject;
    SetProjectHandle(this);
    GetEventManager()->FireEvent(wxEVT_BSLPROJECT_ADD, GetHostHandle(), GetProjectHandle());
}

CProject::~CProject()
{
    CObjectLocker olLock(this);

    // Cleanup databases
    delete m_pProjectStatisticsDatabase;
    m_pProjectStatisticsDatabase = NULL;
}

CProject& CProject::operator= (const CBSLProject& bslProject)
{
    CObjectLocker olLock(this);

    CBSLProject::operator=(bslProject);
    SetProjectHandle(this);
    UpdateLastModified();
    GetEventManager()->FireEvent(wxEVT_BSLPROJECT_UPDATE, GetHostHandle(), GetProjectHandle());

    return *this;
}

bool CProject::operator== (const CBSLProject& bslProject)
{
    CObjectLocker olLock(this);
    return CBSLProject::operator==(bslProject);
}

bool CProject::operator!= (const CBSLProject& bslProject)
{
    CObjectLocker olLock(this);
    return CBSLProject::operator!=(bslProject);
}

BSLERRCODE CProject::AddProjectStatistic(CProjectStatistic* pProjectStatistic)
{
    return m_pProjectStatisticsDatabase->Add(pProjectStatistic);
}

BSLERRCODE CProject::DeleteProjectStatistic(CProjectStatistic* pProjectStatistic)
{
    return m_pProjectStatisticsDatabase->Delete(pProjectStatistic);
}

BSLERRCODE CProject::EnumerateProjectStatistics(std::vector<CProjectStatistic*>& oProjectStatistics)
{
    return m_pProjectStatisticsDatabase->Enumerate(oProjectStatistics);
}

BSLERRCODE CProject::FindProjectStatistic(
    wxDateTime dtTimestamp,
    CProjectStatistic** ppProjectStatistic,
    CBSLProjectStatistic* pBSLProjectStatistic
)
{
    BSLERRCODE rc = BSLERR_MESSAGE_NOT_FOUND;
    std::vector<CProjectStatistic*>::iterator i;
    CProjectStatistic* pProjectStatistic = NULL;

    *ppProjectStatistic = NULL;

    m_pProjectStatisticsDatabase->Lock();

    for (i = m_pProjectStatisticsDatabase->m_Database.begin(); i != m_pProjectStatisticsDatabase->m_Database.end(); ++i)
    {
        pProjectStatistic = *i;

        //
        if (pProjectStatistic->GetTimestamp() != dtTimestamp) continue;

        //
        *ppProjectStatistic = pProjectStatistic;
        rc = BSLERR_SUCCESS;

        break;
    }

    if (pProjectStatistic && pBSLProjectStatistic)
    {
        CObjectLocker olLock(pProjectStatistic);
        *pBSLProjectStatistic = *pProjectStatistic;
    }

    m_pProjectStatisticsDatabase->Unlock();

    return rc;
}

void CProject::Dispose()
{
    CObjectLocker olLock(this);
    GetEventManager()->FireEvent(wxEVT_BSLPROJECT_DELETE, GetHostHandle(), GetProjectHandle());
    CObject::Dispose(this);
}

BSLERRCODE CProject::Update(CBSLProject& bslProject)
{
    CObjectLocker olLock(this);

	BSLERRCODE rc = BSLERR_FAILURE;
    wxDateTime dtNow = wxDateTime::Now();

    if (CBSLProject::operator!=(bslProject))
    {
        CBSLProject::operator=(bslProject);
        GetEventManager()->FireEvent(wxEVT_BSLPROJECT_UPDATE, GetHostHandle(), GetProjectHandle());

        rc = BSLERR_SUCCESS;
    }
    else if (bslProject.GetSchedulerRPCMinimumTime() > dtNow || bslProject.GetSchedulerRPCNextTime() > dtNow)
    {
        GetEventManager()->FireEvent(wxEVT_BSLPROJECT_UPDATE, GetHostHandle(), GetProjectHandle());

        rc = BSLERR_SUCCESS;
    }

    UpdateLastModified();

	return rc;
}


CProjectIndex::CProjectIndex()
{
    m_pProject = NULL;
    m_uiMasterURLHash = 0;
}

CProjectIndex::CProjectIndex(CProject* pProject)
{
    m_pProject = pProject;
    m_uiMasterURLHash = pProject->GetMasterURLHash();
}

CProjectIndex::CProjectIndex(wxUint32 uiMasterURLHash)
{
    m_pProject = NULL;
    m_uiMasterURLHash = uiMasterURLHash;
}

CProjectIndex::~CProjectIndex()
{
}

bool CProjectIndex::operator== (const CProjectIndex& entry)
{
    if (m_uiMasterURLHash != entry.m_uiMasterURLHash) return false;
    return true;
}

bool CProjectIndex::operator!= (const CProjectIndex& entry)
{
    return !(*this == entry);
}

CProject* CProjectIndex::GetRecord()
{
    return m_pProject;
}

wxUint32 CProjectIndex::GetMasterURLHash()
{
    return m_uiMasterURLHash;
}
