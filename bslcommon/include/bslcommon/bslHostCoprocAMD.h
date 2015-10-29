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

#ifndef _BSLCOMMONHOSTCOPROCAMD_H_
#define _BSLCOMMONHOSTCOPROCAMD_H_

#include "bslHostCoprocOpenCL.h"

#define BSLXMLTAGHASH_HOSTCOPROCAMD \
    0xf4eec882

class CBSLHostCoprocAMD: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CBSLHostCoprocAMD)

public:
    CBSLHostCoprocAMD();
    virtual ~CBSLHostCoprocAMD();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLHostCoprocAMD&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLHostCoprocAMD&) const;

    /// \brief Initialize CBSLHostCoprocAMD state.
    void Clear();

    /// \brief
    wxUint32 GetCount();
    /// \brief
    wxString& GetName();
    /// \brief
    wxString& GetCALVersion();
    /// \brief
    wxUint64 GetPeakFlops();
    /// \brief
    wxUint32 GetTarget();
    /// \brief
    wxUint64 GetAvailableRAM();
    /// \brief
    wxUint64 GetLocalRAM();
    /// \brief
    wxUint64 GetUncachedRemoteRAM();
    /// \brief
    wxUint64 GetCachedRemoteRAM();
    /// \brief
    wxUint32 GetEngineClock();
    /// \brief
    wxUint32 GetMemoryClock();
    /// \brief
    wxUint32 GetWavefrontSize();
    /// \brief
    wxUint32 GetNumberOfSIMD();
    /// \brief
    wxUint32 GetPitchAlignment();
    /// \brief
    wxUint32 GetSurfaceAlignment();
    /// \brief
    wxUint32 GetMaxResource1DWidth();
    /// \brief
    wxUint32 GetMaxResource2DWidth();
    /// \brief
    wxUint32 GetMaxResource2DHeight();
    /// \brief
    CBSLHostCoprocOpenCL& GetOpenCLProperties();
    /// \brief
    bool IsCALAvailable();
    /// \brief
    bool IsOpenCLAvailable();
    /// \brief
    bool IsDoublePrecisionAvailable();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief
    void SetCount(wxUint32 uiCount);
    /// \brief
    void SetName(wxString strName);
    /// \brief
    void SetCALVersion(wxString strCALVersion);
    /// \brief
    void SetPeakFlops(wxUint64 ullPeakFlops);
    /// \brief
    void SetTarget(wxUint32 uiTarget);
    /// \brief
    void SetAvailableRAM(wxUint64 ullAvailableRAM);
    /// \brief
    void SetLocalRAM(wxUint64 ullLocalRAM);
    /// \brief
    void SetUncachedRemoteRAM(wxUint64 ullUncachedRemoteRAM);
    /// \brief
    void SetCachedRemoteRAM(wxUint64 ullCachedRemoteRAM);
    /// \brief
    void SetEngineClock(wxUint32 uiEngineClock);
    /// \brief
    void SetMemoryClock(wxUint32 uiMemoryClock);
    /// \brief
    void SetWavefrontSize(wxUint32 uiWavefrontSize);
    /// \brief
    void SetNumberOfSIMD(wxUint32 uiNumberOfSIMD);
    /// \brief
    void SetPitchAlignment(wxUint32 uiPitchAlignment);
    /// \brief
    void SetSurfaceAlignment(wxUint32 uiSurfaceAlignment);
    /// \brief
    void SetMaxResource1DWidth(wxUint32 uiMaxResource1DWidth);
    /// \brief
    void SetMaxResource2DWidth(wxUint32 uiMaxResource2DWidth);
    /// \brief
    void SetMaxResource2DHeight(wxUint32 uiMaxResource2DHeight);
    /// \brief
    void SetOpenCLProperties(CBSLHostCoprocOpenCL& oOpenCLProperties);
    /// \brief
    void SetCALAvailable(bool bCALAvailable);
    /// \brief
    void SetOpenCLAvailable(bool bOpenCLAvailable);
    /// \brief
    void SetDoublePrecisionAvailable(bool bDoublePrecisionAvailable);

private:
    wxUint32 m_uiCount;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strCALVersion;
    wxUint32 m_uiCALVersionHash;
    bool m_bCALAvailable;
    bool m_bOpenCLAvailable;
    bool m_bDoublePrecisionAvailable;
    wxUint64 m_ullPeakFlops;
    wxUint32 m_uiTarget;
    wxUint64 m_ullAvailableRAM;
    wxUint64 m_ullLocalRAM;
    wxUint64 m_ullUncachedRemoteRAM;
    wxUint64 m_ullCachedRemoteRAM;
    wxUint32 m_uiEngineClock;
    wxUint32 m_uiMemoryClock;
    wxUint32 m_uiWavefrontSize;
    wxUint32 m_uiNumberOfSIMD;
    wxUint32 m_uiPitchAlignment;
    wxUint32 m_uiSurfaceAlignment;
    wxUint32 m_uiMaxResource1DWidth;
    wxUint32 m_uiMaxResource2DWidth;
    wxUint32 m_uiMaxResource2DHeight;
    CBSLHostCoprocOpenCL m_OpenCLProperties;
};

#endif

///
/// \}
