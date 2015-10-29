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


#define BSLXMLTAGHASH_PLATFORMS \
    0x69310333


IMPLEMENT_DYNAMIC_CLASS(CBSLProjectListItem, CBSLProjectListItemEventData);

CBSLProjectListItem::CBSLProjectListItem() :
CBSLProjectListItemEventData()
{
    Clear();
}

CBSLProjectListItem::~CBSLProjectListItem()
{
}

bool CBSLProjectListItem::operator== (const CBSLProjectListItem& bslProjectListItem) const
{
    if (m_uiMasterURLHash != bslProjectListItem.m_uiMasterURLHash) return false;
    if (m_uiNameHash != bslProjectListItem.m_uiNameHash) return false;
    if (m_uiDescriptionHash != bslProjectListItem.m_uiDescriptionHash) return false;
    if (m_uiGeneralAreaHash != bslProjectListItem.m_uiGeneralAreaHash) return false;
    if (m_uiSpecificAreaHash != bslProjectListItem.m_uiSpecificAreaHash) return false;
    if (m_uiOrganizationHash != bslProjectListItem.m_uiOrganizationHash) return false;
    if (m_uiLogoHash != bslProjectListItem.m_uiLogoHash) return false;
    if (m_oSupportedPlatforms != bslProjectListItem.m_oSupportedPlatforms) return false;
    return true;
}

bool CBSLProjectListItem::operator!= (const CBSLProjectListItem& bslProjectListItem) const
{
    return !(*this == bslProjectListItem);
}

void CBSLProjectListItem::Clear()
{
    m_strMasterURL.clear();
    m_uiMasterURLHash = 0;
    m_strName.clear();
    m_uiNameHash = 0;
    m_strDescription.clear();
    m_uiDescriptionHash = 0;
    m_strGeneralArea.clear();
    m_uiGeneralAreaHash = 0;
    m_strSpecificArea.clear();
    m_uiSpecificAreaHash = 0;
    m_strOrganization.clear();
    m_uiOrganizationHash = 0;
    m_strLogo.empty();
    m_uiLogoHash = 0;
    m_oSupportedPlatforms.clear();
}

wxString& CBSLProjectListItem::GetMasterURL()
{
    return m_strMasterURL;
}

wxUint32 CBSLProjectListItem::GetMasterURLHash()
{
    return m_uiMasterURLHash;
}

wxString& CBSLProjectListItem::GetName()
{
    return m_strName;
}

wxString& CBSLProjectListItem::GetDescription()
{
    return m_strDescription;
}

wxString& CBSLProjectListItem::GetGeneralArea()
{
    return m_strGeneralArea;
}

wxString& CBSLProjectListItem::GetSpecificArea()
{
    return m_strSpecificArea;
}

wxString& CBSLProjectListItem::GetOrganization()
{
    return m_strOrganization;
}

wxString& CBSLProjectListItem::GetLogo()
{
    return m_strLogo;
}

std::vector<wxString>& CBSLProjectListItem::GetSupportedPlatforms()
{
    return m_oSupportedPlatforms;
}

BSLERRCODE CBSLProjectListItem::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECT == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        if (BSLXMLTAGHASH_PLATFORMS == oElement.GetNameHash())
        {
            while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement)) {
                if (BSLXMLTAGHASH_PLATFORMS == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
                switch(oElement.GetNameHash())
                {
                    case 0x2f8b3bf4:    // name
                        m_oSupportedPlatforms.push_back(CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength()));
                        break;
                    default:
#ifdef __WXDEBUG__
                        wxLogTrace(
                            wxT("BSLCommon Parser"),
                            wxT("CBSLProjectListItem::ParseEx: (Supported Platforms) Hash: '0x%x', Name: '%s'"),
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
        }
        else
        {
            switch(oElement.GetNameHash())
            {
                case 0x2f8b3bf4:    // name
                    m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiNameHash = oElement.GetValueHash();
                    break;
                case 0x6b7119c1:    // description
                    m_strDescription = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiDescriptionHash = oElement.GetValueHash();
                    break;
                case 0x3b6a85a8:    // url
                    m_strMasterURL = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiMasterURLHash = oElement.GetValueHash();
                    break;
                case 0xd4d6a8f9:    // general_area
                    m_strGeneralArea = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiGeneralAreaHash = oElement.GetValueHash();
                    break;
                case 0xdcb7f5e7:    // specific_area
                    m_strSpecificArea = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiSpecificAreaHash = oElement.GetValueHash();
                    break;
                case 0xbda06a7c:    // home
                    m_strOrganization = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiOrganizationHash = oElement.GetValueHash();
                    break;
                case 0x9e0b246c:    // image
                    m_strLogo = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiLogoHash = oElement.GetValueHash();
                    break;
                default:
#ifdef __WXDEBUG__
                    wxLogTrace(
                        wxT("BSLCommon Parser"),
                        wxT("CBSLProjectListItem::ParseEx: Hash: '0x%x', Name: '%s'"),
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
    }

    return BSLERR_SUCCESS;
}

void CBSLProjectListItem::SetMasterURL(wxString strMasterURL)
{
    m_strMasterURL = strMasterURL;
    m_uiMasterURLHash = bslXMLStrHash32(m_strMasterURL.c_str(), m_strMasterURL.size());
}

void CBSLProjectListItem::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLProjectListItem::SetDescription(wxString strDescription)
{
    m_strDescription = strDescription;
    m_uiDescriptionHash = bslXMLStrHash32(m_strDescription.c_str(), m_strDescription.size());
}

void CBSLProjectListItem::SetGeneralArea(wxString strGeneralArea)
{
    m_strGeneralArea = strGeneralArea;
    m_uiGeneralAreaHash = bslXMLStrHash32(m_strGeneralArea.c_str(), m_strGeneralArea.size());
}

void CBSLProjectListItem::SetSpecificArea(wxString strSpecificArea)
{
    m_strSpecificArea = strSpecificArea;
    m_uiSpecificAreaHash = bslXMLStrHash32(m_strSpecificArea.c_str(), m_strSpecificArea.size());
}

void CBSLProjectListItem::SetOrganization(wxString strOrganization)
{
    m_strOrganization = strOrganization;
    m_uiOrganizationHash = bslXMLStrHash32(m_strOrganization.c_str(), m_strOrganization.size());
}

void CBSLProjectListItem::SetLogo(wxString strLogo)
{
    m_strLogo = strLogo;
    m_uiLogoHash = bslXMLStrHash32(m_strLogo.c_str(), m_strLogo.size());
}

void CBSLProjectListItem::SetSupportedPlatforms(std::vector<wxString>& oSupportedPlatforms)
{
    m_oSupportedPlatforms = oSupportedPlatforms;
}
