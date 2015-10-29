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


IMPLEMENT_DYNAMIC_CLASS(CBSLAppVersion, CBSLAppVersionEventData);

CBSLAppVersion::CBSLAppVersion() :
CBSLAppVersionEventData()
{
    Clear();
}

CBSLAppVersion::~CBSLAppVersion()
{
}

bool CBSLAppVersion::operator== (const CBSLAppVersion& bslAppVersion) const
{
    if (m_uiVersion != bslAppVersion.m_uiVersion) return false;
    if (m_uiProjectHash != bslAppVersion.m_uiProjectHash) return false;
    if (m_uiNameHash != bslAppVersion.m_uiNameHash) return false;
    if (m_uiPlanClassHash != bslAppVersion.m_uiPlanClassHash) return false;
    return true;
}

bool CBSLAppVersion::operator!= (const CBSLAppVersion& bslAppVersion) const
{
    return !(*this == bslAppVersion);
}

void CBSLAppVersion::Clear()
{
    m_strProject.clear();
    m_uiProjectHash = 0;
    m_strName.clear();
    m_uiNameHash = 0;
    m_strPlanClass.clear();
    m_uiPlanClassHash = 0;
    m_uiVersion = 0;
}

wxString& CBSLAppVersion::GetProject()
{
    return m_strProject;
}

wxUint32 CBSLAppVersion::GetProjectHash()
{
    return m_uiProjectHash;
}

wxString& CBSLAppVersion::GetName()
{
    return m_strName;
}

wxUint32 CBSLAppVersion::GetNameHash()
{
    return m_uiNameHash;
}

wxString& CBSLAppVersion::GetPlanClass()
{
    return m_strPlanClass;
}

wxUint32 CBSLAppVersion::GetPlanClassHash()
{
    return m_uiPlanClassHash;
}

wxUint32 CBSLAppVersion::GetVersion()
{
    return m_uiVersion;
}

wxUint32 CBSLAppVersion::GetVersionMajor()
{
    return m_uiVersion / 100;
}

wxUint32 CBSLAppVersion::GetVersionMinor()
{
    return m_uiVersion % 100;
}

BSLERRCODE CBSLAppVersion::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_APPVERSION == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0xf39468a4:    // app_name
                m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiNameHash = oElement.GetValueHash();
                break;
            case 0xe4839045:    // plan_class
                m_strPlanClass = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiPlanClassHash = oElement.GetValueHash();
                break;
            case 0x4e93e126:    // version_num
                m_uiVersion = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLAppVersion::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLAppVersion::SetProject(wxString strProject)
{
    m_strProject = strProject;
    m_uiProjectHash = bslXMLStrHash32(m_strProject.c_str(), m_strProject.size());
}

void CBSLAppVersion::SetProject(wxString strProject, wxUint32 uiHash)
{
    m_strProject = strProject;
    m_uiProjectHash = uiHash;
}

void CBSLAppVersion::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLAppVersion::SetName(wxString strName, wxUint32 uiHash)
{
    m_strName = strName;
    m_uiNameHash = uiHash;
}

void CBSLAppVersion::SetPlanClass(wxString strPlanClass)
{
    m_strPlanClass = strPlanClass;
    m_uiPlanClassHash = bslXMLStrHash32(m_strPlanClass.c_str(), m_strPlanClass.size());
}

void CBSLAppVersion::SetPlanClass(wxString strPlanClass, wxUint32 uiHash)
{
    m_strPlanClass = strPlanClass;
    m_uiPlanClassHash = uiHash;
}

void CBSLAppVersion::SetVersion(wxUint32 uiVersion)
{
    m_uiVersion = uiVersion;
}

