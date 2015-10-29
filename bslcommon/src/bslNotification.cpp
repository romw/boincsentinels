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


IMPLEMENT_DYNAMIC_CLASS(CBSLNotification, CBSLNotificationEventData);

CBSLNotification::CBSLNotification() :
CBSLNotificationEventData()
{
    Clear();
}

CBSLNotification::~CBSLNotification()
{
}

bool CBSLNotification::operator== (const CBSLNotification& bslNotification) const
{
    if (m_iSequenceNumber != bslNotification.m_iSequenceNumber) return false;
    if (m_dtCreateTime != bslNotification.m_dtCreateTime) return false;
    if (m_dtArrivalTime != bslNotification.m_dtArrivalTime) return false;
    if (m_bPrivate != bslNotification.m_bPrivate) return false;
    if (m_uiCategoryHash != bslNotification.m_uiCategoryHash) return false;
    if (m_uiLinkHash != bslNotification.m_uiLinkHash) return false;
    if (m_uiProjectHash != bslNotification.m_uiProjectHash) return false;
    if (m_uiTitleHash != bslNotification.m_uiTitleHash) return false;
    if (m_uiNotificationTextHash != bslNotification.m_uiNotificationTextHash) return false;
    if (m_uiGUIDHash != bslNotification.m_uiGUIDHash) return false;
    if (m_uiFeedURLHash != bslNotification.m_uiFeedURLHash) return false;
    return true;
}

bool CBSLNotification::operator!= (const CBSLNotification& bslNotification) const
{
    return !(*this == bslNotification);
}

void CBSLNotification::Clear()
{
    m_iSequenceNumber = -1;
    m_dtCreateTime = wxDateTime((time_t)0);
    m_dtArrivalTime = wxDateTime((time_t)0);
    m_bPrivate = false;
    m_strCategory.clear();
    m_uiCategoryHash = 0;
    m_strLink.clear();
    m_uiLinkHash = 0;
    m_strProject.clear();
    m_uiProjectHash = 0;
    m_strTitle.clear();
    m_uiTitleHash = 0;
    m_strNotificationText.clear();
    m_uiNotificationTextHash = 0;
    m_strGUID.clear();
    m_uiGUIDHash = 0;
    m_strFeedURL.clear();
    m_uiFeedURLHash = 0;
}

wxInt32 CBSLNotification::GetSequenceNumber()
{
    return m_iSequenceNumber;
}

wxDateTime& CBSLNotification::GetCreateTime()
{
    return m_dtCreateTime;
}

wxDateTime& CBSLNotification::GetArrivalTime()
{
    return m_dtArrivalTime;
}

bool CBSLNotification::IsPrivate()
{
    return m_bPrivate;
}

wxString& CBSLNotification::GetCategory()
{
    return m_strCategory;
}

wxString& CBSLNotification::GetLink()
{
    return m_strLink;
}

wxString& CBSLNotification::GetProject()
{
    return m_strProject;
}

wxUint32 CBSLNotification::GetProjectHash()
{
    return m_uiProjectHash;
}

wxString& CBSLNotification::GetTitle()
{
    return m_strTitle;
}

wxString& CBSLNotification::GetNotificationText()
{
    return m_strNotificationText;
}

wxString& CBSLNotification::GetGUID()
{
    return m_strGUID;
}

wxString& CBSLNotification::GetFeedURL()
{
    return m_strFeedURL;
}

BSLERRCODE CBSLNotification::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_NOTIFICATION == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0xe55382f7:    // seqno
                m_iSequenceNumber = CBSLXMLConverterEx::ConvertToI32(oElement.GetValue());
                break;
            case 0xdce0e62d:    // title
                m_strTitle = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiTitleHash = oElement.GetValueHash();
                break;
            case 0x6b7119c1:    // description
                m_strNotificationText = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiNotificationTextHash = oElement.GetValueHash();
                break;
            case 0xe57fb99b:    // create_time
                m_dtCreateTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0x447aa120:    // arrival_time
                m_dtArrivalTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0xe4a52895:    // is_private
                m_bPrivate = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0x443f1326:    // project_name
                m_strProject = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiProjectHash = oElement.GetValueHash();
                break;
            case 0xa1865fe1:    // category
                m_strCategory = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiCategoryHash = oElement.GetValueHash();
                break;
            case 0x0820aba1:    // link
                m_strLink = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiLinkHash = oElement.GetValueHash();
                break;
            case 0x2e10aaae:    // guid
                m_strGUID = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiGUIDHash = oElement.GetValueHash();
                break;
            case 0xf40fdbf7:    // feed_url
                m_strFeedURL = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiFeedURLHash = oElement.GetValueHash();
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLNotification::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLNotification::SetSequenceNumber(wxInt32 iSequenceNumber)
{
    m_iSequenceNumber = iSequenceNumber;
}

void CBSLNotification::SetCreateTime(wxDateTime dtCreateTime)
{
    m_dtCreateTime = dtCreateTime;
}

void CBSLNotification::SetArrivalTime(wxDateTime dtArrivalTime)
{
    m_dtArrivalTime = dtArrivalTime;
}

void CBSLNotification::SetPrivate(bool bPrivate)
{
    m_bPrivate = bPrivate;
}

void CBSLNotification::SetCategory(wxString strCategory)
{
    m_strCategory = strCategory;
    m_uiCategoryHash = bslXMLStrHash32(m_strCategory.c_str(), m_strCategory.size());
}

void CBSLNotification::SetLink(wxString strLink)
{
    m_strLink = strLink;
    m_uiLinkHash = bslXMLStrHash32(m_strLink.c_str(), m_strLink.size());
}

void CBSLNotification::SetProject(wxString strProject)
{
    m_strProject = strProject;
    m_uiProjectHash = bslXMLStrHash32(m_strProject.c_str(), m_strProject.size());
}

void CBSLNotification::SetTitle(wxString strTitle)
{
    m_strTitle = strTitle;
    m_uiTitleHash = bslXMLStrHash32(m_strTitle.c_str(), m_strTitle.size());
}

void CBSLNotification::SetNotificationText(wxString strNotificationText)
{
    m_strNotificationText = strNotificationText;
    m_uiNotificationTextHash = bslXMLStrHash32(m_strNotificationText.c_str(), m_strNotificationText.size());
}

void CBSLNotification::SetGUID(wxString strGUID)
{
    m_strGUID = strGUID;
    m_uiGUIDHash = bslXMLStrHash32(m_strGUID.c_str(), m_strGUID.size());
}

void CBSLNotification::SetFeedURL(wxString strFeedURL)
{
    m_strFeedURL = strFeedURL;
    m_uiFeedURLHash = bslXMLStrHash32(m_strFeedURL.c_str(), m_strFeedURL.size());
}
