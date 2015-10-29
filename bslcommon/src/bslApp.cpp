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


IMPLEMENT_DYNAMIC_CLASS(CBSLApp, CBSLAppEventData);

CBSLApp::CBSLApp() :
CBSLAppEventData()
{
    Clear();
}

CBSLApp::~CBSLApp()
{
}

bool CBSLApp::operator== (const CBSLApp& bslApp) const
{
    if (m_uiProjectHash != bslApp.m_uiProjectHash) return false;
    if (m_uiNameHash != bslApp.m_uiNameHash) return false;
    if (m_uiUserFriendlyNameHash != bslApp.m_uiUserFriendlyNameHash) return false;
    if (m_bNonCPUIntensive != bslApp.m_bNonCPUIntensive) return false;
    return true;
}

bool CBSLApp::operator!= (const CBSLApp& bslApp) const
{
    return !(*this == bslApp);
}

void CBSLApp::Clear()
{
    m_strProject.clear();
    m_uiProjectHash = 0;
    m_strName.clear();
    m_uiNameHash = 0;
    m_strUserFriendlyName.clear();
    m_uiUserFriendlyNameHash = 0;
    m_bNonCPUIntensive = false;
}

wxString& CBSLApp::GetProject()
{
    return m_strProject;
}

wxUint32 CBSLApp::GetProjectHash()
{
    return m_uiProjectHash;
}

wxString& CBSLApp::GetName()
{
    return m_strName;
}

wxUint32 CBSLApp::GetNameHash()
{
    return m_uiNameHash;
}

wxString& CBSLApp::GetUserFriendlyName()
{
    return m_strUserFriendlyName;
}

bool CBSLApp::IsNonCPUIntensive()
{
    return m_bNonCPUIntensive;
}

BSLERRCODE CBSLApp::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_APP == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0x2f8b3bf4:    // name
                m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiNameHash = oElement.GetValueHash();
                break;
            case 0xf29f57b4:    // user_friendly_name
                m_strUserFriendlyName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiUserFriendlyNameHash = oElement.GetValueHash();
                break;
            case 0x540e2ee9:    // non_cpu_intensive
                m_bNonCPUIntensive = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLApp::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLApp::SetProject(wxString strProject)
{
    m_strProject = strProject;
    m_uiProjectHash = bslXMLStrHash32(m_strProject.c_str(), m_strProject.size());
}

void CBSLApp::SetProject(wxString strProject, wxUint32 uiHash)
{
    m_strProject = strProject;
    m_uiProjectHash = uiHash;
}

void CBSLApp::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLApp::SetName(wxString strName, wxUint32 uiHash)
{
    m_strName = strName;
    m_uiNameHash = uiHash;
}

void CBSLApp::SetUserFriendlyName(wxString strUserFriendlyName)
{
    m_strUserFriendlyName = strUserFriendlyName;
    m_uiUserFriendlyNameHash = bslXMLStrHash32(m_strUserFriendlyName.c_str(), m_strUserFriendlyName.size());
}

void CBSLApp::SetUserFriendlyName(wxString strUserFriendlyName, wxUint32 uiHash)
{
    m_strUserFriendlyName = strUserFriendlyName;
    m_uiUserFriendlyNameHash = uiHash;
}

void CBSLApp::SetNonCPUIntensive(bool bNonCPUIntensive)
{
    m_bNonCPUIntensive = bNonCPUIntensive;
}
