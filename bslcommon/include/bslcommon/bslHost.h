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

#ifndef _BSLCOMMONHOST_H_
#define _BSLCOMMONHOST_H_

#include "bslHostCoprocAMD.h"
#include "bslHostCoprocNvidia.h"
#include "bslHostCoprocOpenCL.h"

#define BSLXMLTAGHASH_HOST \
    0x98f5d37e

class CBSLHost: public CBSLHostEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLHost)

public:

    enum CONNECTIONSTATE
    {
        ConnectionStateUnknown,
        ConnectionStateConnecting,
        ConnectionStateConnected,
        ConnectionStateDisconnecting,
        ConnectionStateDisconnected,
        ConnectionStateReconnecting,
        ConnectionStateConnectFailure,
        ConnectionStateAuthenticationFailure,
        ConnectionStateVersionIncompatibleFailure
    };

    CBSLHost();
    virtual ~CBSLHost();

    /// \brief Assignment Operator
    virtual CBSLHost& operator= (const CBSLHost&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLHost&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLHost&) const;

    /// \brief Initialize CBSLHost state.
    void Clear();

    /// \brief Returns the connection state of the host.
    CONNECTIONSTATE GetConnectionState();
    /// \brief Returns the name of the host.
    wxString& GetName();
    /// \brief Returns the cross project identifier of the host.
    wxString& GetCrossProjectID();
    /// \brief Returns the IP address of the host.
    wxString& GetIPAddress();
    /// \brief Returns the time zone(local standard time - UTC time (in seconds)) of the host.
    wxInt32 GetTimezone();
    /// \brief Returns the time stamp of the last time the benchmarks were ran for the host.
    wxDateTime GetLastProcessorBenchmark();
    /// \brief Returns the name of the operating system for the host.
    wxString& GetOSName();
    /// \brief Returns the version of the operating system for the host.
    wxString& GetOSVersion();
    /// \brief Returns the version of the BOINC Client (Major part) for the host.
    wxUint32 GetClientVersionMajor();
    /// \brief Returns the version of the BOINC Client (Minor part) for the host.
    wxUint32 GetClientVersionMinor();
    /// \brief Returns the version of the BOINC Client (Release part) for the host.
    wxUint32 GetClientVersionRelease();
    /// \brief Returns the processor count for the host.
    wxUint32 GetProcessorCount();
    /// \brief Returns the processor vendor name for the host.
    wxString& GetProcessorVendor();
    /// \brief Returns the processor model name for the host.
    wxString& GetProcessorModel();
    /// \brief Returns the processor feature list for the host.
    wxString& GetProcessorFeatures();
    /// \brief Returns the processor cache size (in bytes) for the host.
    wxUint64 GetProcessorCache();
    /// \brief Returns the processor floating point operation count for the host.
    wxUint64 GetProcessorFLOPS();
    /// \brief Returns the processor integer operation count for the host.
    wxUint64 GetProcessorIOPS();
    /// \brief Returns the processor to memory bus bandwidth for the host.
    wxUint64 GetProcessorMemoryBandwidth();
    /// \brief Returns the total physical memory (in bytes) for the host.
    wxUint64 GetMemoryTotal();
    /// \brief Returns the total swap space (in bytes) for the host.
    wxUint64 GetMemorySwap();
    /// \brief Returns the total disk space (in bytes) for the host.
    wxUint64 GetDiskTotal();
    /// \brief Returns the free disk space (in bytes) for the host.
    wxUint64 GetDiskFree();
    /// \brief
    wxString& GetPrimaryPlatform();
    /// \brief
    std::vector<CBSLHostCoprocAMD>& GetAMDCoprocs();
    /// \brief
    std::vector<CBSLHostCoprocNvidia>& GetNvidiaCoprocs();
    /// \brief
    std::vector<wxString>& GetSupportedPlatforms();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the name of the host.
    void SetName(wxString strName);
    /// \brief Sets the cross project identifier of the host.
    void SetCrossProjectID(wxString strCrossProjectID);
    /// \brief Sets the IP address of the host.
    void SetIPAddress(wxString strIPAddress);
    /// \brief Sets the time zone(local standard time - UTC time (in seconds)) of the host.
    void SetTimezone(wxInt32 uiiTimezone);
    /// \brief Sets the time stamp of the last time the benchmarks were ran for the host.
    void SetLastProcessorBenchmark(wxDateTime dtLastProcessorBenchmark);
    /// \brief Sets the name of the operating system for the host.
    void SetOSName(wxString strOSName);
    /// \brief Sets the version of the operating system for the host.
    void SetOSVersion(wxString strOSVersion);
    /// \brief Sets the version of the BOINC Client (Major part) for the host.
    void SetClientVersionMajor(wxUint32 m_uiClientVersionMajor);
    /// \brief Sets the version of the BOINC Client (Minor part) for the host.
    void SetClientVersionMinor(wxUint32 m_uiClientVersionMinor);
    /// \brief Sets the version of the BOINC Client (Release part) for the host.
    void SetClientVersionRelease(wxUint32 m_uiClientVersionRelease);
    /// \brief Sets the processor count for the host.
    void SetProcessorCount(wxUint32 iProcessorCount);
    /// \brief Sets the processor vendor name for the host.
    void SetProcessorVendor(wxString strProcessorVendor);
    /// \brief Sets the processor model name for the host.
    void SetProcessorModel(wxString strProcessorModel);
    /// \brief Sets the processor feature list for the host.
    void SetProcessorFeatures(wxString strProcessorFeatures);
    /// \brief Sets the processor cache size (in bytes) for the host.
    void SetProcessorCache(wxUint64 ullProcessorCache);
    /// \brief Sets the processor floating point operation count for the host.
    void SetProcessorFLOPS(wxUint64 ullProcessorFLOPS);
    /// \brief Sets the processor integer operation count for the host.
    void SetProcessorIOPS(wxUint64 ullProcessorIOPS);
    /// \brief Sets the total physical memory (in bytes) for the host.
    void SetProcessorMemoryBandwidth(wxUint64 ullProcessorMemoryBandwidth);
    /// \brief Sets the total physical memory (in bytes) for the host.
    void SetMemoryTotal(wxUint64 ullMemoryTotal);
    /// \brief Sets the total swap space (in bytes) for the host.
    void SetMemorySwap(wxUint64 ullMemorySwap);
    /// \brief Sets the total disk space (in bytes) for the host.
    void SetDiskTotal(wxUint64 ullDiskTotal);
    /// \brief Sets the free disk space (in bytes) for the host.
    void SetDiskFree(wxUint64 ullDiskFree);
    /// \brief
    void SetPrimaryPlatform(wxString strPrimrayPlatform);
    /// \brief
    void SetAMDCoprocs(std::vector<CBSLHostCoprocAMD>& oAMDCoprocs);
    /// \brief
    void SetNvidiaCoprocs(std::vector<CBSLHostCoprocNvidia>& oNvidiaCoprocs);
    /// \brief
    void SetSupportedPlatforms(std::vector<wxString>& oSupportedPlatforms);

protected:
    CONNECTIONSTATE m_iConnectionState;

private:
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strCrossProjectID;
    wxUint32 m_uiCrossProjectIDHash;
    wxString m_strIPAddress;
    wxUint32 m_uiIPAddressHash;
    wxInt32 m_iTimezone;
    wxDateTime m_dtLastProcessorBenchmark;
    wxString m_strOSName;
    wxUint32 m_uiOSNameHash;
    wxString m_strOSVersion;
    wxUint32 m_uiOSVersionHash;
    wxUint32 m_uiClientVersionMajor;
    wxUint32 m_uiClientVersionMinor;
    wxUint32 m_uiClientVersionRelease;
    wxUint32 m_uiProcessorCount;
    wxString m_strProcessorVendor;
    wxUint32 m_uiProcessorVendorHash;
    wxString m_strProcessorModel;
    wxUint32 m_uiProcessorModelHash;
    wxString m_strProcessorFeatures;
    wxUint32 m_uiProcessorFeaturesHash;
    wxUint64 m_ullProcessorCache;
    wxUint64 m_ullProcessorFLOPS;
    wxUint64 m_ullProcessorIOPS;
    wxUint64 m_ullProcessorMemoryBandwidth;
    wxUint64 m_ullMemoryTotal;
    wxUint64 m_ullMemorySwap;
    wxUint64 m_ullDiskTotal;
    wxUint64 m_ullDiskFree;
    wxString m_strPrimaryPlatform;
    wxUint32 m_uiPrimaryPlatformHash;
    std::vector<CBSLHostCoprocAMD> m_oAMDCoprocs;
    std::vector<CBSLHostCoprocNvidia> m_oNvidiaCoprocs;
    std::vector<wxString> m_oSupportedPlatforms;
};

#endif

///
/// \}
