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

///
/// \defgroup BSLCommon BOINC Sentinels Common Library Interface
/// \{

#ifndef _BSLCOMMONHOSTCOPROCNVIDIA_H_
#define _BSLCOMMONHOSTCOPROCNVIDIA_H_

#include "bslHostCoprocOpenCL.h"

#define BSLXMLTAGHASH_HOSTCOPROCNVIDIA \
    0x37b4cae7

class CBSLHostCoprocNvidia: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CBSLHostCoprocNvidia)

public:
    CBSLHostCoprocNvidia();
    virtual ~CBSLHostCoprocNvidia();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLHostCoprocNvidia&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLHostCoprocNvidia&) const;

    /// \brief Initialize CBSLHostCoprocNvidia state.
    void Clear();

    /// \brief
    wxUint32 GetCount();
    /// \brief
    wxString& GetName();
    /// \brief
    wxString& GetCUDAVersion();
    /// \brief
    wxString& GetDriverVersion();
    /// \brief
    wxUint64 GetPeakFlops();
    /// \brief
    wxUint64 GetAvailableMemory();
    /// \brief
    wxUint64 GetTotalGlobalMemory();
    /// \brief
    wxUint64 GetTotalConstMemory();
    /// \brief
    wxUint32 GetSharedMemoryPerBlock();
    /// \brief
    wxUint32 GetRegsPerBlock();
    /// \brief
    wxUint32 GetWarpSize();
    /// \brief
    wxUint32 GetMemPitch();
    /// \brief
    wxUint32 GetMaxThreadsPerBlock();
    /// \brief
    wxUint32 GetMaxThreadsDim(wxUint32 iIndex);
    /// \brief
    wxUint32 GetMaxGridSize(wxUint32 iIndex);
    /// \brief
    wxUint32 GetClockRate();
    /// \brief
    wxUint32 GetComputeCapabilityMajorVersion();
    /// \brief
    wxUint32 GetComputeCapabilityMinorVersion();
    /// \brief
    wxUint32 GetTextureAlignment();
    /// \brief
    wxUint32 GetDeviceOverlap();
    /// \brief
    wxUint32 GetMultiProcessorCount();
    /// \brief
    CBSLHostCoprocOpenCL& GetOpenCLProperties();
    /// \brief
    bool IsCUDAAvailable();
    /// \brief
    bool IsOpenCLAvailable();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief
    void SetCount(wxUint32 uiCount);
    /// \brief
    void SetName(wxString strName);
    /// \brief
    void SetCUDAVersion(wxString strCUDAVersion);
    /// \brief
    void SetDriverVersion(wxString strDriverVersion);
    /// \brief
    void SetPeakFlops(wxUint64 ullPeakFlops);
    /// \brief
    void SetAvailableMemory(wxUint64 ullAvailableMemory);
    /// \brief
    void SetTotalGlobalMemory(wxUint64 ullTotalGlobalMemory);
    /// \brief
    void SetTotalConstMemory(wxUint64 ullTotalConstMemory);
    /// \brief
    void SetSharedMemoryPerBlock(wxUint32 uiSharedMemoryPerBlock);
    /// \brief
    void SetRegsPerBlock(wxUint32 uiRegsPerBlock);
    /// \brief
    void SetWarpSize(wxUint32 uiWarpSize);
    /// \brief
    void SetMemPitch(wxUint32 uiMemPitch);
    /// \brief
    void SetMaxThreadsPerBlock(wxUint32 uiMaxThreadsPerBlock);
    /// \brief
    void SetMaxThreadsDim(wxUint32 iIndex, wxUint32 uiMaxThreadsDim);
    /// \brief
    void SetMaxGridSize(wxUint32 iIndex, wxUint32 uiMaxGridSize);
    /// \brief
    void SetClockRate(wxUint32 uiClockRate);
    /// \brief
    void SetComputeCapabilityMajorVersion(wxUint32 uiComputeCapabilityMajorVersion);
    /// \brief
    void SetComputeCapabilityMinorVersion(wxUint32 uiComputeCapabilityMinorVersion);
    /// \brief
    void SetTextureAlignment(wxUint32 uiTextureAlignment);
    /// \brief
    void SetDeviceOverlap(wxUint32 uiDeviceOverlap);
    /// \brief
    void SetMultiProcessorCount(wxUint32 uiMultiProcessorCount);
    /// \brief
    void SetOpenCLProperties(CBSLHostCoprocOpenCL& oOpenCLProperties);
    /// \brief
    void SetCUDAAvailable(bool bCUDAAvailable);
    /// \brief
    void SetOpenCLAvailable(bool bOpenCLAvailable);

private:
    wxUint32 m_uiCount;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strCUDAVersion;
    wxUint32 m_uiCUDAVersionHash;
    wxString m_strDriverVersion;
    wxUint32 m_uiDriverVersionHash;
    bool m_bCUDAAvailable;
    bool m_bOpenCLAvailable;
    wxUint64 m_ullPeakFlops;
    wxUint64 m_ullAvailableMemory;
    wxUint64 m_ullTotalGlobalMemory;
    wxUint64 m_ullTotalConstMemory;
    wxUint32 m_uiSharedMemoryPerBlock;
    wxUint32 m_uiRegsPerBlock;
    wxUint32 m_uiWarpSize;
    wxUint32 m_uiMemPitch;
    wxUint32 m_uiMaxThreadsPerBlock;
    wxUint32 m_uiMaxThreadsDim[3];
    wxUint32 m_uiMaxGridSize[3];
    wxUint32 m_uiClockRate;
    wxUint32 m_uiComputeCapabilityMajorVersion;
    wxUint32 m_uiComputeCapabilityMinorVersion;
    wxUint32 m_uiTextureAlignment;
    wxUint32 m_uiDeviceOverlap;
    wxUint32 m_uiMultiProcessorCount;
    CBSLHostCoprocOpenCL m_OpenCLProperties;
};

#endif

///
/// \}
