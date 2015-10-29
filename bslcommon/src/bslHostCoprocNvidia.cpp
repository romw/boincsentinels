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


IMPLEMENT_DYNAMIC_CLASS(CBSLHostCoprocNvidia, wxObject);

CBSLHostCoprocNvidia::CBSLHostCoprocNvidia() :
wxObject()
{
    Clear();
}

CBSLHostCoprocNvidia::~CBSLHostCoprocNvidia()
{
}

bool CBSLHostCoprocNvidia::operator== (const CBSLHostCoprocNvidia& bslHostCoprocNvidia) const
{
    if (m_uiCount != bslHostCoprocNvidia.m_uiCount) return false;
    if (m_ullPeakFlops != bslHostCoprocNvidia.m_ullPeakFlops) return false;
    if (m_ullAvailableMemory != bslHostCoprocNvidia.m_ullAvailableMemory) return false;
    if (m_ullTotalGlobalMemory != bslHostCoprocNvidia.m_ullTotalGlobalMemory) return false;
    if (m_ullTotalConstMemory != bslHostCoprocNvidia.m_ullTotalConstMemory) return false;
    if (m_uiSharedMemoryPerBlock != bslHostCoprocNvidia.m_uiSharedMemoryPerBlock) return false;
    if (m_uiRegsPerBlock != bslHostCoprocNvidia.m_uiRegsPerBlock) return false;
    if (m_uiWarpSize != bslHostCoprocNvidia.m_uiWarpSize) return false;
    if (m_uiMemPitch != bslHostCoprocNvidia.m_uiMemPitch) return false;
    if (m_uiMaxThreadsPerBlock != bslHostCoprocNvidia.m_uiMaxThreadsPerBlock) return false;
    if (m_uiMaxThreadsDim[0] != bslHostCoprocNvidia.m_uiMaxThreadsDim[0]) return false;
    if (m_uiMaxThreadsDim[1] != bslHostCoprocNvidia.m_uiMaxThreadsDim[1]) return false;
    if (m_uiMaxThreadsDim[2] != bslHostCoprocNvidia.m_uiMaxThreadsDim[2]) return false;
    if (m_uiMaxGridSize[0] != bslHostCoprocNvidia.m_uiMaxGridSize[0]) return false;
    if (m_uiMaxGridSize[1] != bslHostCoprocNvidia.m_uiMaxGridSize[1]) return false;
    if (m_uiMaxGridSize[2] != bslHostCoprocNvidia.m_uiMaxGridSize[2]) return false;
    if (m_uiClockRate != bslHostCoprocNvidia.m_uiClockRate) return false;
    if (m_uiComputeCapabilityMajorVersion != bslHostCoprocNvidia.m_uiComputeCapabilityMajorVersion) return false;
    if (m_uiComputeCapabilityMinorVersion != bslHostCoprocNvidia.m_uiComputeCapabilityMinorVersion) return false;
    if (m_uiTextureAlignment != bslHostCoprocNvidia.m_uiTextureAlignment) return false;
    if (m_uiDeviceOverlap != bslHostCoprocNvidia.m_uiDeviceOverlap) return false;
    if (m_uiMultiProcessorCount != bslHostCoprocNvidia.m_uiMultiProcessorCount) return false;
    if (m_OpenCLProperties != bslHostCoprocNvidia.m_OpenCLProperties) return false;
    if (m_bCUDAAvailable != bslHostCoprocNvidia.m_bCUDAAvailable) return false;
    if (m_uiNameHash != bslHostCoprocNvidia.m_uiNameHash) return false;
    if (m_uiCUDAVersionHash != bslHostCoprocNvidia.m_uiCUDAVersionHash) return false;
    if (m_uiDriverVersionHash != bslHostCoprocNvidia.m_uiDriverVersionHash) return false;
    if (m_bOpenCLAvailable != bslHostCoprocNvidia.m_bOpenCLAvailable) return false;
    return true;
}

bool CBSLHostCoprocNvidia::operator!= (const CBSLHostCoprocNvidia& bslHostCoprocNvidia) const
{
    return !(*this == bslHostCoprocNvidia);
}

void CBSLHostCoprocNvidia::Clear()
{
    m_uiCount = 0;
    m_strName.clear();
    m_uiNameHash = 0;
    m_strCUDAVersion.clear();
    m_uiCUDAVersionHash = 0;
    m_strDriverVersion.clear();
    m_uiDriverVersionHash = 0;
    m_ullPeakFlops = 0;
    m_ullAvailableMemory = 0;
    m_ullTotalGlobalMemory = 0;
    m_ullTotalConstMemory = 0;
    m_uiSharedMemoryPerBlock = 0;
    m_uiRegsPerBlock = 0;
    m_uiWarpSize = 0;
    m_uiMemPitch = 0;
    m_uiMaxThreadsPerBlock = 0;
    m_uiMaxThreadsDim[0] = 0;
    m_uiMaxThreadsDim[1] = 0;
    m_uiMaxThreadsDim[2] = 0;
    m_uiMaxGridSize[0] = 0;
    m_uiMaxGridSize[1] = 0;
    m_uiMaxGridSize[2] = 0;
    m_uiClockRate = 0;
    m_uiComputeCapabilityMajorVersion = 0;
    m_uiComputeCapabilityMinorVersion = 0;
    m_uiTextureAlignment = 0;
    m_uiDeviceOverlap = 0;
    m_uiMultiProcessorCount = 0;
    m_OpenCLProperties.Clear();
    m_bCUDAAvailable = false;
    m_bOpenCLAvailable = false;
}

wxUint32 CBSLHostCoprocNvidia::GetCount()
{
    return m_uiCount;
}

wxString& CBSLHostCoprocNvidia::GetName()
{
    return m_strName;
}

wxString& CBSLHostCoprocNvidia::GetCUDAVersion()
{
    return m_strCUDAVersion;
}

wxString& CBSLHostCoprocNvidia::GetDriverVersion()
{
    return m_strDriverVersion;
}

wxUint64 CBSLHostCoprocNvidia::GetPeakFlops()
{
    return m_ullPeakFlops;
}

wxUint64 CBSLHostCoprocNvidia::GetAvailableMemory()
{
    return m_ullAvailableMemory;
}

wxUint64 CBSLHostCoprocNvidia::GetTotalGlobalMemory()
{
    return m_ullTotalGlobalMemory;
}

wxUint64 CBSLHostCoprocNvidia::GetTotalConstMemory()
{
    return m_ullTotalConstMemory;
}

wxUint32 CBSLHostCoprocNvidia::GetSharedMemoryPerBlock()
{
    return m_uiSharedMemoryPerBlock;
}

wxUint32 CBSLHostCoprocNvidia::GetRegsPerBlock()
{
    return m_uiRegsPerBlock;
}

wxUint32 CBSLHostCoprocNvidia::GetWarpSize()
{
    return m_uiWarpSize;
}

wxUint32 CBSLHostCoprocNvidia::GetMemPitch()
{
    return m_uiMemPitch;
}

wxUint32 CBSLHostCoprocNvidia::GetMaxThreadsPerBlock()
{
    return m_uiMaxThreadsPerBlock;
}

wxUint32 CBSLHostCoprocNvidia::GetMaxThreadsDim(wxUint32 iIndex)
{
    return m_uiMaxThreadsDim[iIndex];
}

wxUint32 CBSLHostCoprocNvidia::GetMaxGridSize(wxUint32 iIndex)
{
    return m_uiMaxGridSize[iIndex];
}

wxUint32 CBSLHostCoprocNvidia::GetClockRate()
{
    return m_uiClockRate;
}

wxUint32 CBSLHostCoprocNvidia::GetComputeCapabilityMajorVersion()
{
    return m_uiComputeCapabilityMajorVersion;
}

wxUint32 CBSLHostCoprocNvidia::GetComputeCapabilityMinorVersion()
{
    return m_uiComputeCapabilityMinorVersion;
}

wxUint32 CBSLHostCoprocNvidia::GetTextureAlignment()
{
    return m_uiTextureAlignment;
}

wxUint32 CBSLHostCoprocNvidia::GetDeviceOverlap()
{
    return m_uiDeviceOverlap;
}

wxUint32 CBSLHostCoprocNvidia::GetMultiProcessorCount()
{
    return m_uiMultiProcessorCount;
}

CBSLHostCoprocOpenCL& CBSLHostCoprocNvidia::GetOpenCLProperties()
{
    return m_OpenCLProperties;
}

bool CBSLHostCoprocNvidia::IsCUDAAvailable()
{
    return m_bCUDAAvailable;
}

bool CBSLHostCoprocNvidia::IsOpenCLAvailable()
{
    return m_bOpenCLAvailable;
}

BSLERRCODE CBSLHostCoprocNvidia::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;
    wxString strBuffer;
    wxStringTokenizer tkz;
    wxUint32 uiMaxThreadsDim;
    wxUint32 uiMaxGridSize;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_HOSTCOPROCNVIDIA == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        if (BSLXMLTAGHASH_HOSTCOPROCOPENCL == oElement.GetNameHash())
        {
            m_OpenCLProperties.ParseEx(oDocument);
        }
        else
        {
            switch(oElement.GetNameHash())
            {
                case 0xaf289042:    // count
                    m_uiCount = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x2f8b3bf4:    // name
                    m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiNameHash = oElement.GetValueHash();
                    break;
                case 0x8b44c590:    // cudaVersion
                    m_strCUDAVersion = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiCUDAVersionHash = oElement.GetValueHash();
                    break;
                case 0x50bd3445:    // drvVersion
                    m_strDriverVersion = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiDriverVersionHash = oElement.GetValueHash();
                    break;
                case 0x3fdc920b:    // have_cuda
                    m_bCUDAAvailable = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0x704a15bf:    // have_opencl
                    m_bOpenCLAvailable = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0xbad9d1eb:    // peak_flops
                    m_ullPeakFlops = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0xfb6c890b:    // available_ram
                    m_ullAvailableMemory = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x03a5aa5f:    // totalGlobalMem
                    m_ullTotalGlobalMemory = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x4c9936ed:    // sharedMemPerBlock
                    m_uiSharedMemoryPerBlock = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x6556e6b8:    // regsPerBlock
                    m_uiRegsPerBlock = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x878d2f30:    // warpSize
                    m_uiWarpSize = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xcb725776:    // memPitch
                    m_uiMemPitch = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xddfc00d4:    // maxThreadsPerBlock
                    m_uiMaxThreadsPerBlock = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xc1ed732e:    // maxThreadsDim
                    strBuffer = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    tkz = wxStringTokenizer(strBuffer, wxT(" "), wxTOKEN_RET_EMPTY);
                    tkz.GetNextToken().ToLong((long*)&uiMaxThreadsDim);
                    SetMaxThreadsDim(0, uiMaxThreadsDim);
                    tkz.GetNextToken().ToLong((long*)&uiMaxThreadsDim);
                    SetMaxThreadsDim(1, uiMaxThreadsDim);
                    tkz.GetNextToken().ToLong((long*)&uiMaxThreadsDim);
                    SetMaxThreadsDim(2, uiMaxThreadsDim);
                    break;
                case 0x48679c7e:    // maxGridSize
                    strBuffer = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    tkz = wxStringTokenizer(strBuffer, wxT(" "), wxTOKEN_RET_EMPTY);
                    tkz.GetNextToken().ToLong((long*)&uiMaxGridSize);
                    SetMaxThreadsDim(0, uiMaxGridSize);
                    tkz.GetNextToken().ToLong((long*)&uiMaxGridSize);
                    SetMaxThreadsDim(1, uiMaxGridSize);
                    tkz.GetNextToken().ToLong((long*)&uiMaxGridSize);
                    SetMaxThreadsDim(2, uiMaxGridSize);
                    break;
                case 0xf9feed9b:    // clockRate
                    m_uiClockRate = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xfff713f5:    // totalConstMem
                    m_ullTotalConstMemory = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x4a3554b4:    // major
                    m_uiComputeCapabilityMajorVersion = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xd09ad130:    // minor
                    m_uiComputeCapabilityMinorVersion = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x4256aa71:    // textureAlignment
                    m_uiTextureAlignment = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x45dec048:    // deviceOverlap
                    m_uiDeviceOverlap = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x6521ec89:    // multiProcessorCount
                    m_uiMultiProcessorCount = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                default:
#ifdef __WXDEBUG__
                    wxLogTrace(
                        wxT("BSLCommon Parser"),
                        wxT("HostCoprocNvidiaDictionaryMap: Hash: '0x%x', Name: '%s'"),
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

void CBSLHostCoprocNvidia::SetCount(wxUint32 uiCount)
{
    m_uiCount = uiCount;
}

void CBSLHostCoprocNvidia::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLHostCoprocNvidia::SetCUDAVersion(wxString strCUDAVersion)
{
    m_strCUDAVersion = strCUDAVersion;
    m_uiCUDAVersionHash = bslXMLStrHash32(m_strCUDAVersion.c_str(), m_strCUDAVersion.size());
}

void CBSLHostCoprocNvidia::SetDriverVersion(wxString strDriverVersion)
{
    m_strDriverVersion = strDriverVersion;
    m_uiDriverVersionHash = bslXMLStrHash32(m_strDriverVersion.c_str(), m_strDriverVersion.size());
}

void CBSLHostCoprocNvidia::SetPeakFlops(wxUint64 ullPeakFlops)
{
    m_ullPeakFlops = ullPeakFlops;
}

void CBSLHostCoprocNvidia::SetAvailableMemory(wxUint64 ullAvailableMemory)
{
    m_ullAvailableMemory = ullAvailableMemory;
}

void CBSLHostCoprocNvidia::SetTotalGlobalMemory(wxUint64 ullTotalGlobalMemory)
{
    m_ullTotalGlobalMemory = ullTotalGlobalMemory;
}

void CBSLHostCoprocNvidia::SetTotalConstMemory(wxUint64 ullTotalConstMemory)
{
    m_ullTotalConstMemory = ullTotalConstMemory;
}

void CBSLHostCoprocNvidia::SetSharedMemoryPerBlock(wxUint32 uiSharedMemoryPerBlock)
{
    m_uiSharedMemoryPerBlock = uiSharedMemoryPerBlock;
}

void CBSLHostCoprocNvidia::SetRegsPerBlock(wxUint32 uiRegsPerBlock)
{
    m_uiRegsPerBlock = uiRegsPerBlock;
}

void CBSLHostCoprocNvidia::SetWarpSize(wxUint32 uiWarpSize)
{
    m_uiWarpSize = uiWarpSize;
}

void CBSLHostCoprocNvidia::SetMemPitch(wxUint32 uiMemPitch)
{
    m_uiMemPitch = uiMemPitch;
}

void CBSLHostCoprocNvidia::SetMaxThreadsPerBlock(wxUint32 uiMaxThreadsPerBlock)
{
    m_uiMaxThreadsPerBlock = uiMaxThreadsPerBlock;
}

void CBSLHostCoprocNvidia::SetMaxThreadsDim(wxUint32 iIndex, wxUint32 uiMaxThreadsDim)
{
    m_uiMaxThreadsDim[iIndex] = uiMaxThreadsDim;
}

void CBSLHostCoprocNvidia::SetMaxGridSize(wxUint32 iIndex, wxUint32 uiMaxGridSize)
{
    m_uiMaxGridSize[iIndex] = uiMaxGridSize;
}

void CBSLHostCoprocNvidia::SetClockRate(wxUint32 uiClockRate)
{
    m_uiClockRate = uiClockRate;
}

void CBSLHostCoprocNvidia::SetComputeCapabilityMajorVersion(wxUint32 uiComputeCapabilityMajorVersion)
{
    m_uiComputeCapabilityMajorVersion = uiComputeCapabilityMajorVersion;
}

void CBSLHostCoprocNvidia::SetComputeCapabilityMinorVersion(wxUint32 uiComputeCapabilityMinorVersion)
{
    m_uiComputeCapabilityMinorVersion = uiComputeCapabilityMinorVersion;
}

void CBSLHostCoprocNvidia::SetTextureAlignment(wxUint32 uiTextureAlignment)
{
    m_uiTextureAlignment = uiTextureAlignment;
}

void CBSLHostCoprocNvidia::SetDeviceOverlap(wxUint32 uiDeviceOverlap)
{
    m_uiDeviceOverlap = uiDeviceOverlap;
}

void CBSLHostCoprocNvidia::SetMultiProcessorCount(wxUint32 uiMultiProcessorCount)
{
    m_uiMultiProcessorCount = uiMultiProcessorCount;
}

void CBSLHostCoprocNvidia::SetOpenCLProperties(CBSLHostCoprocOpenCL& oOpenCLProperties)
{
    m_OpenCLProperties = oOpenCLProperties;
}

void CBSLHostCoprocNvidia::SetCUDAAvailable(bool bCUDAAvailable)
{
    m_bCUDAAvailable = bCUDAAvailable;
}

void CBSLHostCoprocNvidia::SetOpenCLAvailable(bool bOpenCLAvailable)
{
    m_bOpenCLAvailable = bOpenCLAvailable;
}
