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


IMPLEMENT_DYNAMIC_CLASS(CBSLProjectLink, wxObject);

CBSLProjectLink::CBSLProjectLink() :
wxObject()
{
    Clear();
}

CBSLProjectLink::~CBSLProjectLink()
{
    Clear();
}

bool CBSLProjectLink::operator== (const CBSLProjectLink& bslProjectLink) const
{
    if (m_uiNameHash != bslProjectLink.m_uiNameHash) return false;
    if (m_uiDescriptionHash != bslProjectLink.m_uiDescriptionHash) return false;
    if (m_uiLinkHash != bslProjectLink.m_uiLinkHash) return false;
    return true;
}

bool CBSLProjectLink::operator!= (const CBSLProjectLink& bslProjectLink) const
{
    return !(*this == bslProjectLink);
}

void CBSLProjectLink::Clear()
{
    m_strName.clear();
    m_uiNameHash = 0;
    m_strDescription.clear();
    m_uiDescriptionHash = 0;
    m_strLink.empty();
    m_uiLinkHash = 0;
}

wxString& CBSLProjectLink::GetName()
{
    return m_strName;
}

wxString& CBSLProjectLink::GetDescription()
{
    return m_strDescription;
}

wxString& CBSLProjectLink::GetLink()
{
    return m_strLink;
}

BSLERRCODE CBSLProjectLink::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_PROJECTLINK == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
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
                m_strLink = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiLinkHash = oElement.GetValueHash();
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLProjectLink::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLProjectLink::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLProjectLink::SetDescription(wxString strDescription)
{
    m_strDescription = strDescription;
    m_uiDescriptionHash = bslXMLStrHash32(m_strDescription.c_str(), m_strDescription.size());
}

void CBSLProjectLink::SetLink(wxString strLink)
{
    m_strLink = strLink;
    m_uiLinkHash = bslXMLStrHash32(m_strLink.c_str(), m_strLink.size());
}

