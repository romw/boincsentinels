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


#define BSLXMLTAGHASH_FILEREFERENCE \
    0x8b44af1


IMPLEMENT_DYNAMIC_CLASS(CBSLTask, CBSLTaskEventData);

CBSLTask::CBSLTask() :
CBSLTaskEventData()
{
    Clear();
}

CBSLTask::~CBSLTask()
{
}

bool CBSLTask::operator== (const CBSLTask& bslTask) const
{
    if (m_uiProjectHash != bslTask.m_uiProjectHash) return false;
    if (m_uiNameHash != bslTask.m_uiNameHash) return false;
    if (m_uiAppNameHash != bslTask.m_uiAppNameHash) return false;
    if (m_ullRuntimeBoundDisk != bslTask.m_ullRuntimeBoundDisk) return false;
    if (m_ullRuntimeBoundFLOPS != bslTask.m_ullRuntimeBoundFLOPS) return false;
    if (m_ullRuntimeBoundMemory != bslTask.m_ullRuntimeBoundMemory) return false;
    if (m_ullRuntimeEstimatedFLOPS != bslTask.m_ullRuntimeEstimatedFLOPS) return false;
    return true;
}

bool CBSLTask::operator!= (const CBSLTask& bslTask) const
{
    return !(*this == bslTask);
}

void CBSLTask::Clear()
{
    m_strProject.clear();
    m_uiProjectHash = 0;
    m_strName.clear();
    m_uiNameHash = 0;
    m_strAppName.clear();
    m_uiAppNameHash = 0;
    m_ullRuntimeBoundDisk = 0;
    m_ullRuntimeBoundFLOPS = 0;
    m_ullRuntimeBoundMemory = 0;
    m_ullRuntimeEstimatedFLOPS = 0;
}

wxString& CBSLTask::GetProject()
{
    return m_strProject;
}

wxUint32 CBSLTask::GetProjectHash()
{
    return m_uiProjectHash;
}

wxString& CBSLTask::GetAppName()
{
    return m_strAppName;
}

wxUint32 CBSLTask::GetAppNameHash()
{
    return m_uiAppNameHash;
}

wxString& CBSLTask::GetName()
{
    return m_strName;
}

wxUint32 CBSLTask::GetNameHash()
{
    return m_uiNameHash;
}

wxUint64 CBSLTask::GetRuntimeBoundDisk()
{
    return m_ullRuntimeBoundDisk;
}

wxUint64 CBSLTask::GetRuntimeBoundFLOPS()
{
    return m_ullRuntimeBoundFLOPS;
}

wxUint64 CBSLTask::GetRuntimeBoundMemory()
{
    return m_ullRuntimeBoundMemory;
}

wxUint64 CBSLTask::GetRuntimeEstimatedFLOPS()
{
    return m_ullRuntimeEstimatedFLOPS;
}

BSLERRCODE CBSLTask::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_TASK == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0x2f8b3bf4:    // name
                m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiNameHash = oElement.GetValueHash();
                break;
            case 0xf39468a4:    // app_name
                m_strAppName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiAppNameHash = oElement.GetValueHash();
                break;
            case 0x6fe35e31:    // rsc_fpops_est
                m_ullRuntimeEstimatedFLOPS = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0xc0df629d:    // rsc_fpops_bound
                m_ullRuntimeBoundFLOPS = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x77fede9e:    // rsc_memory_bound
                m_ullRuntimeBoundMemory = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0xaa5fd6cc:    // rsc_disk_bound
                m_ullRuntimeBoundDisk = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLTask::ParseEx: Hash: '0x%x', Name: '%s'"),
                    oElement.GetNameHash(),
                    oElement.GetName()
                );
#endif
                if (CBSLXMLElementEx::ElementTypeContainer == oElement.GetType())
                {
                    oDocument.SkipContainer(oElement);
                }
                break;
        }
    }

    return BSLERR_SUCCESS;
}

void CBSLTask::SetProject(wxString strProject)
{
    m_strProject = strProject;
    m_uiProjectHash = bslXMLStrHash32(m_strProject.c_str(), m_strProject.size());
}

void CBSLTask::SetProject(wxString strProject, wxUint32 uiHash)
{
    m_strProject = strProject;
    m_uiProjectHash = uiHash;
}

void CBSLTask::SetAppName(wxString strAppName)
{
    m_strAppName = strAppName;
    m_uiAppNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLTask::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLTask::SetRuntimeBoundDisk(wxUint64 ullRuntimeBoundDisk)
{
    m_ullRuntimeBoundDisk = ullRuntimeBoundDisk;
}

void CBSLTask::SetRuntimeBoundFLOPS(wxUint64 ullRuntimeBoundFLOPS)
{
    m_ullRuntimeBoundFLOPS = ullRuntimeBoundFLOPS;
}

void CBSLTask::SetRuntimeBoundMemory(wxUint64 ullRuntimeBoundMemory)
{
    m_ullRuntimeBoundMemory = ullRuntimeBoundMemory;
}

void CBSLTask::SetRuntimeEstimatedFLOPS(wxUint64 ullRuntimeEstimatedFLOPS)
{
    m_ullRuntimeEstimatedFLOPS = ullRuntimeEstimatedFLOPS;
}

