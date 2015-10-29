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


IMPLEMENT_DYNAMIC_CLASS(CBSLTransfer, CBSLTransferEventData);

CBSLTransfer::CBSLTransfer() :
CBSLTransferEventData()
{
    Clear();
}

CBSLTransfer::~CBSLTransfer()
{
}

bool CBSLTransfer::operator== (const CBSLTransfer& bslTransfer) const
{
    if (m_uiProjectHash != bslTransfer.m_uiProjectHash) return false;
    if (m_uiNameHash != bslTransfer.m_uiNameHash) return false;
    if (m_tsElapsedTime != bslTransfer.m_tsElapsedTime) return false;
    if (m_tsProjectBackoff != bslTransfer.m_tsProjectBackoff) return false;
    if (m_dtFirstRequestTime != bslTransfer.m_dtFirstRequestTime) return false;
    if (m_dtNextRequestTime != bslTransfer.m_dtNextRequestTime) return false;
    if (m_uiRetryCount != bslTransfer.m_uiRetryCount) return false;
    if (m_ullBytes != bslTransfer.m_ullBytes) return false;
    if (m_ullBytesTransfered != bslTransfer.m_ullBytesTransfered) return false;
    if (m_ullBytesUploaded != bslTransfer.m_ullBytesUploaded) return false;
    if (m_ullTransferRate != bslTransfer.m_ullTransferRate) return false;
    if (m_bSticky != bslTransfer.m_bSticky) return false;
    if (m_bPersistantTransferActive != bslTransfer.m_bPersistantTransferActive) return false;
    if (m_bTransferActive != bslTransfer.m_bTransferActive) return false;
    if (m_bUpload != bslTransfer.m_bUpload) return false;
    return true;
}

bool CBSLTransfer::operator!= (const CBSLTransfer& bslTransfer) const
{
    return !(*this == bslTransfer);
}

void CBSLTransfer::Clear()
{
    m_strProject.clear();
    m_uiProjectHash = 0;
    m_strName.clear();
    m_uiNameHash = 0;
    m_tsElapsedTime = 0;
    m_tsProjectBackoff = 0;
    m_dtFirstRequestTime = wxDateTime((time_t)0);
    m_dtNextRequestTime = wxDateTime((time_t)0);
    m_uiRetryCount = 0;
    m_ullBytes = 0;
    m_ullBytesTransfered = 0;
    m_ullBytesUploaded = 0;
    m_ullTransferRate = 0;
    m_bSticky = false;
    m_bPersistantTransferActive = false;
    m_bTransferActive = false;
    m_bUpload = false;
}

wxUint64 CBSLTransfer::GetBytes()
{
    return m_ullBytes;
}

wxUint64 CBSLTransfer::GetBytesTransfered()
{
    return m_ullBytesTransfered;
}

wxUint64 CBSLTransfer::GetBytesUploaded()
{
    return m_ullBytesUploaded;
}

wxTimeSpan& CBSLTransfer::GetElapsedTime()
{
    return m_tsElapsedTime;
}

wxDateTime& CBSLTransfer::GetFirstRequestTime()
{
    return m_dtFirstRequestTime;
}

wxString& CBSLTransfer::GetName()
{
    return m_strName;
}

wxUint32 CBSLTransfer::GetNameHash()
{
    return m_uiNameHash;
}

wxString& CBSLTransfer::GetProject()
{
    return m_strProject;
}

wxUint32 CBSLTransfer::GetProjectHash()
{
    return m_uiProjectHash;
}

wxDateTime& CBSLTransfer::GetNextRequestTime()
{
    return m_dtNextRequestTime;
}

wxTimeSpan& CBSLTransfer::GetProjectBackoff()
{
    return m_tsProjectBackoff;
}

wxUint32 CBSLTransfer::GetRetryCount()
{
    return m_uiRetryCount;
}

wxUint64 CBSLTransfer::GetTransferRate()
{
    return m_ullTransferRate;
}

bool CBSLTransfer::IsPersistantTransferActive()
{
    return m_bPersistantTransferActive;
}

bool CBSLTransfer::IsSticky()
{
    return m_bSticky;
}

bool CBSLTransfer::IsTransferActive()
{
    return m_bTransferActive;
}

bool CBSLTransfer::IsUpload()
{
    return m_bUpload;
}

BSLERRCODE CBSLTransfer::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_TRANSFER == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0xa0081a8e:    // project_url
                m_strProject = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiProjectHash = oElement.GetValueHash();
                break;
            case 0x2f8b3bf4:    // name
                m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiNameHash = oElement.GetValueHash();
                break;
            case 0x27368251:    // time_so_far
                m_tsElapsedTime = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0x18360641:    // project_backoff
                m_tsProjectBackoff = CBSLXMLConverterEx::ConvertToTimeSpan(oElement.GetValue());
                break;
            case 0x36e7a68d:    // first_request_time
                m_dtFirstRequestTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0x33137820:    // next_request_time
                m_dtNextRequestTime = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                break;
            case 0xa62facc8:    // num_retries
                m_uiRetryCount = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0x75030352:    // nbytes
                m_ullBytes = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x4e0fe868:    // last_bytes_xferred
                m_ullBytesTransfered = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x350c42ef:    // file_offset
                m_ullBytesUploaded = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0xefb55df6:    // xfer_speed
                m_ullTransferRate = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                if (m_ullTransferRate > 0)
                {
                    m_bTransferActive = true;
                }
                break;
            case 0x950109a0:    // sticky
                m_bSticky = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0x210ab15:    // persistent_file_xfer
                m_bPersistantTransferActive = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            case 0x557a0f97:    // is_upload
                m_bUpload = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLTransfer::: Hash: '0x%x', Name: '%s'"),
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

void CBSLTransfer::SetBytes(wxUint64 ullBytes)
{
    m_ullBytes = ullBytes;
}

void CBSLTransfer::SetBytesTransfered(wxUint64 ullBytesTransfered)
{
    m_ullBytesTransfered = ullBytesTransfered;
}

void CBSLTransfer::SetBytesUploaded(wxUint64 ullBytesUploaded)
{
    m_ullBytesUploaded = ullBytesUploaded;
}

void CBSLTransfer::SetElapsedTime(wxTimeSpan tsElapsedTime)
{
    m_tsElapsedTime = tsElapsedTime;
}

void CBSLTransfer::SetFirstRequestTime(wxDateTime dtFirstRequestTime)
{
    m_dtFirstRequestTime = dtFirstRequestTime;
}

void CBSLTransfer::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLTransfer::SetProject(wxString strProject)
{
    m_strProject = strProject;
    m_uiProjectHash = bslXMLStrHash32(m_strProject.c_str(), m_strProject.size());
}

void CBSLTransfer::SetNextRequestTime(wxDateTime dtNextRequestTime)
{
    m_dtNextRequestTime = dtNextRequestTime;
}

void CBSLTransfer::SetPersistantTransferActive(bool bPersistantTransferActive)
{
    m_bPersistantTransferActive = bPersistantTransferActive;
}

void CBSLTransfer::SetProjectBackoff(wxTimeSpan tsProjectBackoff)
{
    m_tsProjectBackoff = tsProjectBackoff;
}

void CBSLTransfer::SetRetryCount(wxUint32 uiRetryCount)
{
    m_uiRetryCount = uiRetryCount;
}

void CBSLTransfer::SetSticky(bool bSticky)
{
    m_bSticky = bSticky;
}

void CBSLTransfer::SetTransferActive(bool bTransferActive)
{
    m_bTransferActive = bTransferActive;
}

void CBSLTransfer::SetTransferRate(wxUint64 ullTransferRate)
{
    m_ullTransferRate = ullTransferRate;
}

void CBSLTransfer::SetUpload(bool bUpload)
{
    m_bUpload = bUpload;
}
