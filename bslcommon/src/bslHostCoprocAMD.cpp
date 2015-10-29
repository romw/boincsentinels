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


IMPLEMENT_DYNAMIC_CLASS(CBSLHostCoprocAMD, wxObject);

CBSLHostCoprocAMD::CBSLHostCoprocAMD() :
wxObject()
{
    Clear();
}

CBSLHostCoprocAMD::~CBSLHostCoprocAMD()
{
}

bool CBSLHostCoprocAMD::operator== (const CBSLHostCoprocAMD& bslHostCoprocAMD) const
{
    if (m_uiCount != bslHostCoprocAMD.m_uiCount) return false;
    if (m_bCALAvailable != bslHostCoprocAMD.m_bCALAvailable) return false;
    if (m_bOpenCLAvailable != bslHostCoprocAMD.m_bOpenCLAvailable) return false;
    if (m_bDoublePrecisionAvailable != bslHostCoprocAMD.m_bDoublePrecisionAvailable) return false;
    if (m_ullPeakFlops != bslHostCoprocAMD.m_ullPeakFlops) return false;
    if (m_uiTarget != bslHostCoprocAMD.m_uiTarget) return false;
    if (m_ullAvailableRAM != bslHostCoprocAMD.m_ullAvailableRAM) return false;
    if (m_ullLocalRAM != bslHostCoprocAMD.m_ullLocalRAM) return false;
    if (m_ullUncachedRemoteRAM != bslHostCoprocAMD.m_ullUncachedRemoteRAM) return false;
    if (m_ullCachedRemoteRAM != bslHostCoprocAMD.m_ullCachedRemoteRAM) return false;
    if (m_uiEngineClock != bslHostCoprocAMD.m_uiEngineClock) return false;
    if (m_uiMemoryClock != bslHostCoprocAMD.m_uiMemoryClock) return false;
    if (m_uiWavefrontSize != bslHostCoprocAMD.m_uiWavefrontSize) return false;
    if (m_uiNumberOfSIMD != bslHostCoprocAMD.m_uiNumberOfSIMD) return false;
    if (m_uiPitchAlignment != bslHostCoprocAMD.m_uiPitchAlignment) return false;
    if (m_uiSurfaceAlignment != bslHostCoprocAMD.m_uiSurfaceAlignment) return false;
    if (m_uiMaxResource1DWidth != bslHostCoprocAMD.m_uiMaxResource1DWidth) return false;
    if (m_uiMaxResource2DWidth != bslHostCoprocAMD.m_uiMaxResource2DWidth) return false;
    if (m_uiMaxResource2DHeight != bslHostCoprocAMD.m_uiMaxResource2DHeight) return false;
    if (m_uiNameHash != bslHostCoprocAMD.m_uiNameHash) return false;
    if (m_uiCALVersionHash != bslHostCoprocAMD.m_uiCALVersionHash) return false;
    if (m_OpenCLProperties != bslHostCoprocAMD.m_OpenCLProperties) return false;
    return true;
}

bool CBSLHostCoprocAMD::operator!= (const CBSLHostCoprocAMD& bslHostCoprocAMD) const
{
    return !(*this == bslHostCoprocAMD);
}

void CBSLHostCoprocAMD::Clear()
{
    m_uiCount = 0;
    m_strName.clear();
    m_uiNameHash = 0;
    m_strCALVersion.clear();
    m_uiCALVersionHash = 0;
    m_bCALAvailable = false;
    m_bOpenCLAvailable = false;
    m_bDoublePrecisionAvailable = false;
    m_ullPeakFlops = 0;
    m_uiTarget = 0;
    m_ullAvailableRAM = 0;
    m_ullLocalRAM = 0;
    m_ullUncachedRemoteRAM = 0;
    m_ullCachedRemoteRAM = 0;
    m_uiEngineClock = 0;
    m_uiMemoryClock = 0;
    m_uiWavefrontSize = 0;
    m_uiNumberOfSIMD = 0;
    m_uiPitchAlignment = 0;
    m_uiSurfaceAlignment = 0;
    m_uiMaxResource1DWidth = 0;
    m_uiMaxResource2DWidth = 0;
    m_uiMaxResource2DHeight = 0;
    m_OpenCLProperties.Clear();
}

wxUint32 CBSLHostCoprocAMD::GetCount()
{
    return m_uiCount;
}

wxString& CBSLHostCoprocAMD::GetName()
{
    return m_strName;
}

wxString& CBSLHostCoprocAMD::GetCALVersion()
{
    return m_strCALVersion;
}

wxUint64 CBSLHostCoprocAMD::GetPeakFlops()
{
    return m_ullPeakFlops;
}

wxUint32 CBSLHostCoprocAMD::GetTarget()
{
    return m_uiTarget;
}

wxUint64 CBSLHostCoprocAMD::GetAvailableRAM()
{
    return m_ullAvailableRAM;
}

wxUint64 CBSLHostCoprocAMD::GetLocalRAM()
{
    return m_ullLocalRAM;
}

wxUint64 CBSLHostCoprocAMD::GetUncachedRemoteRAM()
{
    return m_ullUncachedRemoteRAM;
}

wxUint64 CBSLHostCoprocAMD::GetCachedRemoteRAM()
{
    return m_ullCachedRemoteRAM;
}

wxUint32 CBSLHostCoprocAMD::GetEngineClock()
{
    return m_uiEngineClock;
}

wxUint32 CBSLHostCoprocAMD::GetMemoryClock()
{
    return m_uiMemoryClock;
}

wxUint32 CBSLHostCoprocAMD::GetWavefrontSize()
{
    return m_uiWavefrontSize;
}

wxUint32 CBSLHostCoprocAMD::GetNumberOfSIMD()
{
    return m_uiNumberOfSIMD;
}

wxUint32 CBSLHostCoprocAMD::GetPitchAlignment()
{
    return m_uiPitchAlignment;
}

wxUint32 CBSLHostCoprocAMD::GetSurfaceAlignment()
{
    return m_uiSurfaceAlignment;
}

wxUint32 CBSLHostCoprocAMD::GetMaxResource1DWidth()
{
    return m_uiMaxResource1DWidth;
}

wxUint32 CBSLHostCoprocAMD::GetMaxResource2DWidth()
{
    return m_uiMaxResource2DWidth;
}

wxUint32 CBSLHostCoprocAMD::GetMaxResource2DHeight()
{
    return m_uiMaxResource2DHeight;
}

CBSLHostCoprocOpenCL& CBSLHostCoprocAMD::GetOpenCLProperties()
{
    return m_OpenCLProperties;
}

bool CBSLHostCoprocAMD::IsCALAvailable()
{
    return m_bCALAvailable;
}

bool CBSLHostCoprocAMD::IsOpenCLAvailable()
{
    return m_bOpenCLAvailable;
}

bool CBSLHostCoprocAMD::IsDoublePrecisionAvailable()
{
    return m_bDoublePrecisionAvailable;
}

BSLERRCODE CBSLHostCoprocAMD::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_HOSTCOPROCAMD == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
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
                case 0xda6b2a71:    // CALVersion
                    m_strCALVersion = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiCALVersionHash = oElement.GetValueHash();
                    break;
                case 0x7808e142:    // have_cal
                    m_bCALAvailable = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0x704a15bf:    // have_opencl
                    m_bOpenCLAvailable = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0xb4d1ed02:    // doublePrecision
                    m_bDoublePrecisionAvailable = CBSLXMLConverterEx::ConvertToBool(oElement.GetValue());
                    break;
                case 0xbad9d1eb:    // peak_flops
                    m_ullPeakFlops = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0xe89bdbb6:    // target
                    m_uiTarget = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xfb6c890b:    // available_ram
                    m_ullAvailableRAM = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0xb7146292:    // localRAM
                    m_ullLocalRAM = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0xcb979cd8:    // uncachedRemoteRAM
                    m_ullUncachedRemoteRAM = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x9ffc04cb:    // cachedRemoteRAM
                    m_ullCachedRemoteRAM = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x56f927eb:    // engineClock
                    m_uiEngineClock = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xb30c76fa:    // memoryClock
                    m_uiMemoryClock = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x1a2ea6a0:    // wavefrontSize
                    m_uiWavefrontSize = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x33f3230a:    // numberOfSIMD
                    m_uiNumberOfSIMD = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x29d87f4b:    // pitch_alignment
                    m_uiPitchAlignment = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x87f0d218:    // surface_alignment
                    m_uiSurfaceAlignment = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xb197b6f6:    // maxResource1DWidth
                    m_uiMaxResource1DWidth = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0x0a6e2165:    // maxResource2DWidth
                    m_uiMaxResource2DWidth = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xb4e5ee16:    // maxResource2DHeight
                    m_uiMaxResource2DHeight = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                default:
#ifdef __WXDEBUG__
                    wxLogTrace(
                        wxT("BSLCommon Parser"),
                        wxT("CBSLHostCoprocAMD::: Hash: '0x%x', Name: '%s'"),
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

void CBSLHostCoprocAMD::SetCount(wxUint32 uiCount)
{
    m_uiCount = uiCount;
}

void CBSLHostCoprocAMD::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLHostCoprocAMD::SetCALVersion(wxString strCALVersion)
{
    m_strCALVersion = strCALVersion;
    m_uiCALVersionHash = bslXMLStrHash32(m_strCALVersion.c_str(), m_strCALVersion.size());
}

void CBSLHostCoprocAMD::SetPeakFlops(wxUint64 ullPeakFlops)
{
    m_ullPeakFlops = ullPeakFlops;
}

void CBSLHostCoprocAMD::SetTarget(wxUint32 uiTarget)
{
    m_uiTarget = uiTarget;
}

void CBSLHostCoprocAMD::SetAvailableRAM(wxUint64 ullAvailableRAM)
{
    m_ullAvailableRAM = ullAvailableRAM;
}

void CBSLHostCoprocAMD::SetLocalRAM(wxUint64 ullLocalRAM)
{
    m_ullLocalRAM = ullLocalRAM;
}

void CBSLHostCoprocAMD::SetUncachedRemoteRAM(wxUint64 ullUncachedRemoteRAM)
{
    m_ullUncachedRemoteRAM = ullUncachedRemoteRAM;
}

void CBSLHostCoprocAMD::SetCachedRemoteRAM(wxUint64 ullCachedRemoteRAM)
{
    m_ullCachedRemoteRAM = ullCachedRemoteRAM;
}

void CBSLHostCoprocAMD::SetEngineClock(wxUint32 uiEngineClock)
{
    m_uiEngineClock = uiEngineClock;
}

void CBSLHostCoprocAMD::SetMemoryClock(wxUint32 uiMemoryClock)
{
    m_uiMemoryClock = uiMemoryClock;
}

void CBSLHostCoprocAMD::SetWavefrontSize(wxUint32 uiWavefrontSize)
{
    m_uiWavefrontSize = uiWavefrontSize;
}

void CBSLHostCoprocAMD::SetNumberOfSIMD(wxUint32 uiNumberOfSIMD)
{
    m_uiNumberOfSIMD = uiNumberOfSIMD;
}

void CBSLHostCoprocAMD::SetPitchAlignment(wxUint32 uiPitchAlignment)
{
    m_uiPitchAlignment = uiPitchAlignment;
}

void CBSLHostCoprocAMD::SetSurfaceAlignment(wxUint32 uiSurfaceAlignment)
{
    m_uiSurfaceAlignment = uiSurfaceAlignment;
}

void CBSLHostCoprocAMD::SetMaxResource1DWidth(wxUint32 uiMaxResource1DWidth)
{
    m_uiMaxResource1DWidth = uiMaxResource1DWidth;
}

void CBSLHostCoprocAMD::SetMaxResource2DWidth(wxUint32 uiMaxResource2DWidth)
{
    m_uiMaxResource2DWidth = uiMaxResource2DWidth;
}

void CBSLHostCoprocAMD::SetMaxResource2DHeight(wxUint32 uiMaxResource2DHeight)
{
    m_uiMaxResource2DHeight = uiMaxResource2DHeight;
}

void CBSLHostCoprocAMD::SetOpenCLProperties(CBSLHostCoprocOpenCL& oOpenCLProperties)
{
    m_OpenCLProperties = oOpenCLProperties;
}

void CBSLHostCoprocAMD::SetCALAvailable(bool bCALAvailable)
{
    m_bCALAvailable = bCALAvailable;
}

void CBSLHostCoprocAMD::SetOpenCLAvailable(bool bOpenCLAvailable)
{
    m_bOpenCLAvailable = bOpenCLAvailable;
}

void CBSLHostCoprocAMD::SetDoublePrecisionAvailable(bool bDoublePrecisionAvailable)
{
    m_bDoublePrecisionAvailable = bDoublePrecisionAvailable;
}
