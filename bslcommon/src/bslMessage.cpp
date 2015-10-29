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


CBSLMessage::PRIORITY MapPriority(wxInt32 iPriority)
{
    switch (iPriority)
    {
        case 1:
            return CBSLMessage::PriorityInfo;
            break;
        case 2:
            return CBSLMessage::PriorityUserAlert;
            break;
        case 3:
            return CBSLMessage::PriorityInternalError;
            break;
    }
    return CBSLMessage::PriorityUnknown;
}


IMPLEMENT_DYNAMIC_CLASS(CBSLMessage, CBSLMessageEventData);

CBSLMessage::CBSLMessage() :
CBSLMessageEventData()
{
    Clear();
}

CBSLMessage::~CBSLMessage()
{
}

bool CBSLMessage::operator== (const CBSLMessage& bslMessage) const
{
    if (m_iSequenceNumber != bslMessage.m_iSequenceNumber) return false;
    if (m_iPriority != bslMessage.m_iPriority) return false;
    if (m_dtTimestamp != bslMessage.m_dtTimestamp) return false;
    if (m_uiMessageTextHash != bslMessage.m_uiMessageTextHash) return false;
    if (m_uiProjectHash != bslMessage.m_uiProjectHash) return false;
    return true;
}

bool CBSLMessage::operator!= (const CBSLMessage& bslMessage) const
{
    return !(*this == bslMessage);
}

void CBSLMessage::Clear()
{
    m_iSequenceNumber = -1;
    m_iPriority = CBSLMessage::PriorityUnknown;
    m_dtTimestamp = wxDateTime((time_t)0);
    m_strMessageText.clear();
    m_uiMessageTextHash = 0;
    m_strProject.clear();
    m_uiProjectHash = 0;
}

wxInt32 CBSLMessage::GetSequenceNumber()
{
    return m_iSequenceNumber;
}

CBSLMessage::PRIORITY CBSLMessage::GetPriority()
{
    return m_iPriority;
}

wxDateTime& CBSLMessage::GetTimestamp()
{
    return m_dtTimestamp;
}

wxString& CBSLMessage::GetProject()
{
    return m_strProject;
}

wxUint32 CBSLMessage::GetProjectHash()
{
    return m_uiProjectHash;
}

wxString& CBSLMessage::GetMessageText()
{
    return m_strMessageText;
}

BSLERRCODE CBSLMessage::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_MESSAGE == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0xe55382f7:    // seqno
                m_iSequenceNumber = CBSLXMLConverterEx::ConvertToI32(oElement.GetValue());
                break;
            case 0xe2447c34:    // project
                m_strProject = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiProjectHash = oElement.GetValueHash();
                break;
            case 0x6dfe676d:    // body
                m_strMessageText = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiMessageTextHash = oElement.GetValueHash();
                break;
            case 0x3d7754b4:    // pri
                m_iPriority = MapPriority(CBSLXMLConverterEx::ConvertToI32(oElement.GetValue()));
                break;
            case 0x9e3669da:    // time
                m_dtTimestamp = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLMessage::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLMessage::SetSequenceNumber(wxInt32 iSequenceNumber)
{
    m_iSequenceNumber = iSequenceNumber;
}

void CBSLMessage::SetPriority(CBSLMessage::PRIORITY iPriority)
{
    m_iPriority = iPriority;
}

void CBSLMessage::SetTimestamp(wxDateTime dtTimestamp)
{
    m_dtTimestamp = dtTimestamp;
}

void CBSLMessage::SetProject(wxString strProject)
{
    m_strProject = strProject;
    m_uiProjectHash = bslXMLStrHash32(m_strProject.c_str(), m_strProject.size());
}

void CBSLMessage::SetMessageText(wxString strMessageText)
{
    m_strMessageText = strMessageText;
    m_uiMessageTextHash = bslXMLStrHash32(m_strMessageText.c_str(), m_strMessageText.size());
}
