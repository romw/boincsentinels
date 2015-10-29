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


#define BSLXMLTAGHASH_COPROCS \
    0xf99697d6


IMPLEMENT_DYNAMIC_CLASS(CBSLHost, CBSLHostEventData);

CBSLHost::CBSLHost() :
CBSLHostEventData()
{
    Clear();
}

CBSLHost::~CBSLHost()
{
}

CBSLHost& CBSLHost::operator= (const CBSLHost& bslHost)
{
    CBSLHostEventData::operator=(bslHost);

    m_strName = bslHost.m_strName;
    m_uiNameHash = bslHost.m_uiNameHash;
    m_strCrossProjectID = bslHost.m_strCrossProjectID;
    m_uiCrossProjectIDHash = bslHost.m_uiCrossProjectIDHash;
    m_strIPAddress = bslHost.m_strIPAddress;
    m_uiIPAddressHash = bslHost.m_uiIPAddressHash;
    m_iTimezone = bslHost.m_iTimezone;
    m_dtLastProcessorBenchmark = bslHost.m_dtLastProcessorBenchmark;
    m_strOSName = bslHost.m_strOSName;
    m_uiOSNameHash = bslHost.m_uiOSNameHash;
    m_strOSVersion = bslHost.m_strOSVersion;
    m_uiOSVersionHash = bslHost.m_uiOSVersionHash;
    m_uiProcessorCount = bslHost.m_uiProcessorCount;
    m_strProcessorVendor = bslHost.m_strProcessorVendor;
    m_uiProcessorVendorHash = bslHost.m_uiProcessorVendorHash;
    m_strProcessorModel = bslHost.m_strProcessorModel;
    m_uiProcessorModelHash = bslHost.m_uiProcessorModelHash;
    m_strProcessorFeatures = bslHost.m_strProcessorFeatures;
    m_uiProcessorFeaturesHash = bslHost.m_uiProcessorFeaturesHash;
    m_ullProcessorCache = bslHost.m_ullProcessorCache;
    m_ullProcessorFLOPS = bslHost.m_ullProcessorFLOPS;
    m_ullProcessorIOPS = bslHost.m_ullProcessorIOPS;
    m_ullProcessorMemoryBandwidth = bslHost.m_ullProcessorMemoryBandwidth;
    m_ullMemoryTotal = bslHost.m_ullMemoryTotal;
    m_ullMemorySwap = bslHost.m_ullMemorySwap;
    m_ullDiskTotal = bslHost.m_ullDiskTotal;
    m_ullDiskFree = bslHost.m_ullDiskFree;
    m_oAMDCoprocs = bslHost.m_oAMDCoprocs;
    m_oNvidiaCoprocs = bslHost.m_oNvidiaCoprocs;

    // The following items are returned via the <get_state> RPC and not the
    // <host_info> RPC. Why oh why are things just thrown in willy nilly?
    // Only copy it if something is already in the field. Otherwise we might
    // overwrite something useful with an empty string and vector.
    if (!bslHost.m_strPrimaryPlatform.IsEmpty())
    {
        m_strPrimaryPlatform = bslHost.m_strPrimaryPlatform;
        m_uiPrimaryPlatformHash = bslHost.m_uiPrimaryPlatformHash;
    }
    if (!bslHost.m_oSupportedPlatforms.size())
    {
        m_oSupportedPlatforms = bslHost.m_oSupportedPlatforms;
    }

    // Client version information is not included with the <get_state> or
    // <host_info> RPCs.  Only copy it if the values are greater than 0.
    if (bslHost.m_uiClientVersionMajor)
    {
        m_uiClientVersionMajor = bslHost.m_uiClientVersionMajor;
    }
    if (bslHost.m_uiClientVersionMinor)
    {
        m_uiClientVersionMinor = bslHost.m_uiClientVersionMinor;
    }
    if (bslHost.m_uiClientVersionRelease)
    {
        m_uiClientVersionRelease = bslHost.m_uiClientVersionRelease;
    }

    return *this;
}

bool CBSLHost::operator== (const CBSLHost& bslHost) const
{
    if (m_uiNameHash != bslHost.m_uiNameHash) return false;
    if (m_uiCrossProjectIDHash != bslHost.m_uiCrossProjectIDHash) return false;
    if (m_uiIPAddressHash != bslHost.m_uiIPAddressHash) return false;
    if (m_iTimezone != bslHost.m_iTimezone) return false;
    if (m_dtLastProcessorBenchmark != bslHost.m_dtLastProcessorBenchmark) return false;
    if (m_uiOSNameHash != bslHost.m_uiOSNameHash) return false;
    if (m_uiOSVersionHash != bslHost.m_uiOSVersionHash) return false;
    if (m_uiProcessorCount != bslHost.m_uiProcessorCount) return false;
    if (m_uiProcessorVendorHash != bslHost.m_uiProcessorVendorHash) return false;
    if (m_uiProcessorModelHash != bslHost.m_uiProcessorModelHash) return false;
    if (m_uiProcessorFeaturesHash != bslHost.m_uiProcessorFeaturesHash) return false;
    if (m_ullProcessorCache != bslHost.m_ullProcessorCache) return false;
    if (m_ullProcessorFLOPS != bslHost.m_ullProcessorFLOPS) return false;
    if (m_ullProcessorIOPS != bslHost.m_ullProcessorIOPS) return false;
    if (m_ullProcessorMemoryBandwidth != bslHost.m_ullProcessorMemoryBandwidth) return false;
    if (m_ullMemoryTotal != bslHost.m_ullMemoryTotal) return false;
    if (m_ullMemorySwap != bslHost.m_ullMemorySwap) return false;
    if (m_ullDiskTotal != bslHost.m_ullDiskTotal) return false;
    if (m_ullDiskFree != bslHost.m_ullDiskFree) return false;
    if (m_uiPrimaryPlatformHash != bslHost.m_uiPrimaryPlatformHash) return false;
    if (m_oAMDCoprocs != bslHost.m_oAMDCoprocs) return false;
    if (m_oNvidiaCoprocs != bslHost.m_oNvidiaCoprocs) return false;
    if (m_oSupportedPlatforms != bslHost.m_oSupportedPlatforms) return false;
    return true;
}

bool CBSLHost::operator!= (const CBSLHost& bslHost) const
{
    return !(*this == bslHost);
}

void CBSLHost::Clear()
{
    m_iConnectionState = CBSLHost::ConnectionStateUnknown;
    m_strName.clear();
    m_uiNameHash = 0;
    m_strCrossProjectID.clear();
    m_uiCrossProjectIDHash = 0;
    m_strIPAddress.clear();
    m_uiIPAddressHash = 0;
    m_iTimezone = 0;
    m_dtLastProcessorBenchmark = wxDateTime((time_t)0);
    m_strOSName.clear();
    m_uiOSNameHash = 0;
    m_strOSVersion.clear();
    m_uiOSVersionHash = 0;
    m_uiClientVersionMajor = 0;
    m_uiClientVersionMinor = 0;
    m_uiClientVersionRelease = 0;
    m_uiProcessorCount = 0;
    m_strProcessorVendor.clear();
    m_uiProcessorVendorHash = 0;
    m_strProcessorModel.clear();
    m_uiProcessorModelHash = 0;
    m_strProcessorFeatures.clear();
    m_uiProcessorFeaturesHash = 0;
    m_ullProcessorCache = 0;
    m_ullProcessorFLOPS = 0;
    m_ullProcessorIOPS = 0;
    m_ullProcessorMemoryBandwidth = 0;
    m_ullMemoryTotal = 0;
    m_ullMemorySwap = 0;
    m_ullDiskTotal = 0;
    m_ullDiskFree = 0;
    m_strPrimaryPlatform.clear();
    m_uiPrimaryPlatformHash = 0;
    m_oAMDCoprocs.clear();
    m_oNvidiaCoprocs.clear();
    m_oSupportedPlatforms.clear();
}

CBSLHost::CONNECTIONSTATE CBSLHost::GetConnectionState()
{
    return m_iConnectionState;
}

wxString& CBSLHost::GetName()
{
    return m_strName;
}

wxString& CBSLHost::GetCrossProjectID()
{
    return m_strCrossProjectID;
}

wxString& CBSLHost::GetIPAddress()
{
    return m_strIPAddress;
}

wxInt32 CBSLHost::GetTimezone()
{
    return m_iTimezone;
}

wxDateTime CBSLHost::GetLastProcessorBenchmark()
{
    return m_dtLastProcessorBenchmark;
}

wxString& CBSLHost::GetOSName()
{
    return m_strOSName;
}

wxString& CBSLHost::GetOSVersion()
{
    return m_strOSVersion;
}

wxUint32 CBSLHost::GetClientVersionMajor()
{
    return m_uiClientVersionMajor;
}

wxUint32 CBSLHost::GetClientVersionMinor()
{
    return m_uiClientVersionMinor;
}

wxUint32 CBSLHost::GetClientVersionRelease()
{
    return m_uiClientVersionRelease;
}

wxUint32 CBSLHost::GetProcessorCount()
{
    return m_uiProcessorCount;
}

wxString& CBSLHost::GetProcessorVendor()
{
    return m_strProcessorVendor;
}

wxString& CBSLHost::GetProcessorModel()
{
    return m_strProcessorModel;
}

wxString& CBSLHost::GetProcessorFeatures()
{
    return m_strProcessorFeatures;
}

wxUint64 CBSLHost::GetProcessorCache()
{
    return m_ullProcessorCache;
}

wxUint64 CBSLHost::GetProcessorFLOPS()
{
    return m_ullProcessorFLOPS;
}

wxUint64 CBSLHost::GetProcessorIOPS()
{
    return m_ullProcessorIOPS;
}

wxUint64 CBSLHost::GetProcessorMemoryBandwidth()
{
    return m_ullProcessorMemoryBandwidth;
}

wxUint64 CBSLHost::GetMemoryTotal()
{
    return m_ullMemoryTotal;
}

wxUint64 CBSLHost::GetMemorySwap()
{
    return m_ullMemorySwap;
}

wxUint64 CBSLHost::GetDiskTotal()
{
    return m_ullDiskTotal;
}

wxUint64 CBSLHost::GetDiskFree()
{
    return m_ullDiskFree;
}

wxString& CBSLHost::GetPrimaryPlatform()
{
    return m_strPrimaryPlatform;
}

std::vector<CBSLHostCoprocAMD>& CBSLHost::GetAMDCoprocs()
{
    return m_oAMDCoprocs;
}

std::vector<CBSLHostCoprocNvidia>& CBSLHost::GetNvidiaCoprocs()
{
    return m_oNvidiaCoprocs;
}

std::vector<wxString>& CBSLHost::GetSupportedPlatforms()
{
    return m_oSupportedPlatforms;
}

BSLERRCODE CBSLHost::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;
    CBSLHostCoprocAMD oAMDCoproc;
    CBSLHostCoprocNvidia oNvidiaCoproc;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_HOST == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        if (BSLXMLTAGHASH_COPROCS == oElement.GetNameHash())
        {
            while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
            {
                if (BSLXMLTAGHASH_COPROCS == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
                if (BSLXMLTAGHASH_HOSTCOPROCAMD == oElement.GetNameHash())
                {
                    oAMDCoproc.ParseEx(oDocument);
                    m_oAMDCoprocs.push_back(oAMDCoproc);
                }
                else if (BSLXMLTAGHASH_HOSTCOPROCNVIDIA == oElement.GetNameHash())
                {
                    oNvidiaCoproc.ParseEx(oDocument);
                    m_oNvidiaCoprocs.push_back(oNvidiaCoproc);
                }
            }
        }
        else
        {
            switch(oElement.GetNameHash())
            {
                case 0xb14e7cd5:    // domain_name
                    m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiNameHash = oElement.GetValueHash();
                    break;
                case 0x69e53ef4:    // host_cpid
                    m_strCrossProjectID = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiCrossProjectIDHash = oElement.GetValueHash();
                    break;
                case 0x7ee547ac:    // ip_addr
                    m_strIPAddress = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiIPAddressHash = oElement.GetValueHash();
                    break;
                case 0x15997920:    // timezone
                    m_iTimezone = CBSLXMLConverterEx::ConvertToI32(oElement.GetValue());
                    break;
                case 0xa0aed4fa:    // p_calculated
                    m_dtLastProcessorBenchmark = CBSLXMLConverterEx::ConvertToDateTime(oElement.GetValue());
                    break;
                case 0x144956c3:    // os_name
                    m_strOSName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiOSNameHash = oElement.GetValueHash();
                    break;
                case 0xe73f184a:    // os_version
                    m_strOSVersion = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiOSVersionHash = oElement.GetValueHash();
                    break;
                case 0x6c4be7d1:    // p_ncpus
                    m_uiProcessorCount = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                    break;
                case 0xa703e4fc:    // p_vendor
                    m_strProcessorVendor = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiProcessorVendorHash = oElement.GetValueHash();
                    break;
                case 0x6d347361:    // p_model
                    m_strProcessorModel = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiProcessorModelHash = oElement.GetValueHash();
                    break;
                case 0x6fb1316b:    // p_features
                    m_strProcessorFeatures = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                    m_uiProcessorFeaturesHash = oElement.GetValueHash();
                    break;
                case 0x786f26e5:    // m_cache
                    m_ullProcessorCache = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x33011eb4:    // p_fpops
                    m_ullProcessorFLOPS = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x705f80a1:    // p_iops
                    m_ullProcessorIOPS = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0xf849d444:    // p_membw
                    m_ullProcessorMemoryBandwidth = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0xb31796ce:    // m_nbytes
                    m_ullMemoryTotal = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x1aea0eb4:    // m_swap
                    m_ullMemorySwap = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0x6db46b1c:    // d_total
                    m_ullDiskTotal = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                case 0xf48e0fd0:    // d_free
                    m_ullDiskFree = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                    break;
                default:
#ifdef __WXDEBUG__
                    wxLogTrace(
                        wxT("BSLCommon Parser"),
                        wxT("CBSLHost::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLHost::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLHost::SetCrossProjectID(wxString strCrossProjectID)
{
    m_strCrossProjectID = strCrossProjectID;
    m_uiCrossProjectIDHash = bslXMLStrHash32(m_strCrossProjectID.c_str(), m_strCrossProjectID.size());
}

void CBSLHost::SetIPAddress(wxString strIPAddress)
{
    m_strIPAddress = strIPAddress;
    m_uiIPAddressHash = bslXMLStrHash32(m_strIPAddress.c_str(), m_strIPAddress.size());
}

void CBSLHost::SetTimezone(wxInt32 iTimezone)
{
    m_iTimezone = iTimezone;
}

void CBSLHost::SetLastProcessorBenchmark(wxDateTime dtLastProcessorBenchmark)
{
    m_dtLastProcessorBenchmark = dtLastProcessorBenchmark;
}

void CBSLHost::SetOSName(wxString strOSName)
{
    m_strOSName = strOSName;
    m_uiOSNameHash = bslXMLStrHash32(m_strOSName.c_str(), m_strOSName.size());
}

void CBSLHost::SetOSVersion(wxString strOSVersion)
{
    m_strOSVersion = strOSVersion;
    m_uiOSVersionHash = bslXMLStrHash32(m_strOSVersion.c_str(), m_strOSVersion.size());
}

void CBSLHost::SetClientVersionMajor(wxUint32 uiClientVersionMajor)
{
    m_uiClientVersionMajor = uiClientVersionMajor;
}

void CBSLHost::SetClientVersionMinor(wxUint32 uiClientVersionMinor)
{
    m_uiClientVersionMinor = uiClientVersionMinor;
}

void CBSLHost::SetClientVersionRelease(wxUint32 uiClientVersionRelease)
{
    m_uiClientVersionRelease = uiClientVersionRelease;
}

void CBSLHost::SetProcessorCount(wxUint32 uiProcessorCount)
{
    m_uiProcessorCount = uiProcessorCount;
}

void CBSLHost::SetProcessorVendor(wxString strProcessorVendor)
{
    m_strProcessorVendor = strProcessorVendor;
    m_uiProcessorVendorHash = bslXMLStrHash32(m_strProcessorVendor.c_str(), m_strProcessorVendor.size());
}

void CBSLHost::SetProcessorModel(wxString strProcessorModel)
{
    m_strProcessorModel = strProcessorModel;
    m_uiProcessorModelHash = bslXMLStrHash32(m_strProcessorModel.c_str(), m_strProcessorModel.size());
}

void CBSLHost::SetProcessorFeatures(wxString strProcessorFeatures)
{
    m_strProcessorFeatures = strProcessorFeatures;
    m_uiProcessorFeaturesHash = bslXMLStrHash32(m_strProcessorFeatures.c_str(), m_strProcessorFeatures.size());
}

void CBSLHost::SetProcessorCache(wxUint64 ullProcessorCache)
{
    m_ullProcessorCache = ullProcessorCache;
}

void CBSLHost::SetProcessorFLOPS(wxUint64 ullProcessorFLOPS)
{
    m_ullProcessorFLOPS = ullProcessorFLOPS;
}

void CBSLHost::SetProcessorIOPS(wxUint64 ullProcessorIOPS)
{
    m_ullProcessorIOPS = ullProcessorIOPS;
}

void CBSLHost::SetProcessorMemoryBandwidth(wxUint64 ullProcessorMemoryBandwidth)
{
    m_ullProcessorMemoryBandwidth = ullProcessorMemoryBandwidth;
}

void CBSLHost::SetMemoryTotal(wxUint64 ullMemoryTotal)
{
    m_ullMemoryTotal = ullMemoryTotal;
}

void CBSLHost::SetMemorySwap(wxUint64 ullMemorySwap)
{
    m_ullMemorySwap = ullMemorySwap;
}

void CBSLHost::SetDiskTotal(wxUint64 ullDiskTotal)
{
    m_ullDiskTotal = ullDiskTotal;
}

void CBSLHost::SetDiskFree(wxUint64 ullDiskFree)
{
    m_ullDiskFree = ullDiskFree;
}

void CBSLHost::SetPrimaryPlatform(wxString strPrimaryPlatform)
{
    m_strPrimaryPlatform = strPrimaryPlatform;
    m_uiPrimaryPlatformHash = bslXMLStrHash32(m_strPrimaryPlatform.c_str(), m_strPrimaryPlatform.size());
}

void CBSLHost::SetAMDCoprocs(std::vector<CBSLHostCoprocAMD>& oAMDCoprocs)
{
    m_oAMDCoprocs = oAMDCoprocs;
}

void CBSLHost::SetNvidiaCoprocs(std::vector<CBSLHostCoprocNvidia>& oNvidiaCoprocs)
{
    m_oNvidiaCoprocs = oNvidiaCoprocs;
}

void CBSLHost::SetSupportedPlatforms(std::vector<wxString>& oSupportedPlatforms)
{
    m_oSupportedPlatforms = oSupportedPlatforms;
}
