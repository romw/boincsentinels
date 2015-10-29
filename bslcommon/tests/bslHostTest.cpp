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
#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "bslHostTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(HostTestCase);

void HostTestCase::CreateDelete()
{
    CBSLHost* pHost = new CBSLHost();
    CPPUNIT_ASSERT(pHost != NULL);
    delete pHost;
}

void HostTestCase::Equality()
{
    CBSLHost* pHost = new CBSLHost();
    CBSLHost* pHost2 = new CBSLHost();
    CPPUNIT_ASSERT(*pHost == *pHost2);
    delete pHost;
    delete pHost2;
}

void HostTestCase::Inequality()
{
    CBSLHost* pHost = new CBSLHost();
    CBSLHost* pHost2 = new CBSLHost();
    pHost->SetName(wxT("blah"));
    CPPUNIT_ASSERT(*pHost != *pHost2);
    delete pHost;
    delete pHost2;
}

void HostTestCase::AssignmentOperator()
{
    CBSLHost* pHost = new CBSLHost();
    CBSLHost* pHost2 = new CBSLHost();
    pHost->SetName(wxT("blah"));
    *pHost2 = *pHost;
    CPPUNIT_ASSERT(pHost->GetName() == pHost2->GetName());
    delete pHost;
    delete pHost2;
}

void HostTestCase::GetSetConnectionState()
{
    CBSLHost* pHost = new CBSLHost();
    CPPUNIT_ASSERT(CBSLHost::ConnectionStateUnknown == pHost->GetConnectionState());
    delete pHost;
}

void HostTestCase::GetSetName()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strName = wxT("rick.example.com");
    pHost->SetName(strName);
    CPPUNIT_ASSERT(strName == pHost->GetName());
    delete pHost;
}

void HostTestCase::GetSetCrossProjectID()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");
    pHost->SetCrossProjectID(strCrossProjectId);
    CPPUNIT_ASSERT(strCrossProjectId == pHost->GetCrossProjectID());
    delete pHost;
}

void HostTestCase::GetSetIPAddress()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strIPAddress = wxT("192.168.1.1");
    pHost->SetIPAddress(strIPAddress);
    CPPUNIT_ASSERT(strIPAddress == pHost->GetIPAddress());
    delete pHost;
}

void HostTestCase::GetSetTimezone()
{
    CBSLHost* pHost = new CBSLHost();
    wxInt32 iTimezone = 31416;
    pHost->SetTimezone(iTimezone);
    CPPUNIT_ASSERT(iTimezone == pHost->GetTimezone());
    delete pHost;
}

void HostTestCase::GetSetLastProcessorBenchmark()
{
    CBSLHost* pHost = new CBSLHost();
    wxDateTime dtNow = wxDateTime::Now();
    pHost->SetLastProcessorBenchmark(dtNow);
    CPPUNIT_ASSERT(dtNow == pHost->GetLastProcessorBenchmark());
    delete pHost;
}

void HostTestCase::GetSetOSName()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strOSName = wxT("Microsoft Windows");
    pHost->SetOSName(strOSName);
    CPPUNIT_ASSERT(strOSName == pHost->GetOSName());
    delete pHost;
}

void HostTestCase::GetSetOSVersion()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strOSVersion = wxT(" XP");
    pHost->SetOSVersion(strOSVersion);
    CPPUNIT_ASSERT(strOSVersion == pHost->GetOSVersion());
    delete pHost;
}

void HostTestCase::GetSetProcessorCount()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint32 uiProcessorCount = 4;
    pHost->SetProcessorCount(uiProcessorCount);
    CPPUNIT_ASSERT(uiProcessorCount == pHost->GetProcessorCount());
    delete pHost;
}

void HostTestCase::GetSetProcessorVendor()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strProcessorVendor = wxT("Intel");
    pHost->SetProcessorVendor(strProcessorVendor);
    CPPUNIT_ASSERT(strProcessorVendor == pHost->GetProcessorVendor());
    delete pHost;
}

void HostTestCase::GetSetProcessorModel()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strProcessorModel = wxT("Pentium");
    pHost->SetProcessorModel(strProcessorModel);
    CPPUNIT_ASSERT(strProcessorModel == pHost->GetProcessorModel());
    delete pHost;
}

void HostTestCase::GetSetProcessorFeatures()
{
    CBSLHost* pHost = new CBSLHost();
    wxString strProcessorFeatures = wxT("fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss htt tm pni ssse3 cx16 sse4_1 syscall nx lm vmx smx tm2 pbe");
    pHost->SetProcessorFeatures(strProcessorFeatures);
    CPPUNIT_ASSERT(strProcessorFeatures == pHost->GetProcessorFeatures());
    delete pHost;
}

void HostTestCase::GetSetProcessorCache()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullCache = 31416;
    pHost->SetProcessorCache(ullCache);
    CPPUNIT_ASSERT(ullCache == pHost->GetProcessorCache());
    delete pHost;
}

void HostTestCase::GetSetProcessorFLOPS()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullFLOPS = 31416;
    pHost->SetProcessorFLOPS(ullFLOPS);
    CPPUNIT_ASSERT(ullFLOPS == pHost->GetProcessorFLOPS());
    delete pHost;
}

void HostTestCase::GetSetProcessorIOPS()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullIOPS = 31416;
    pHost->SetProcessorIOPS(ullIOPS);
    CPPUNIT_ASSERT(ullIOPS == pHost->GetProcessorIOPS());
    delete pHost;
}

void HostTestCase::GetSetProcessorMemoryBandwidth()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullProcessorMemoryBandwidth = 31416;
    pHost->SetProcessorMemoryBandwidth(ullProcessorMemoryBandwidth);
    CPPUNIT_ASSERT(ullProcessorMemoryBandwidth == pHost->GetProcessorMemoryBandwidth());
    delete pHost;
}

void HostTestCase::GetSetMemoryTotal()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullMemoryTotal = 31416;
    pHost->SetMemoryTotal(ullMemoryTotal);
    CPPUNIT_ASSERT(ullMemoryTotal == pHost->GetMemoryTotal());
    delete pHost;
}

void HostTestCase::GetSetMemorySwap()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullMemorySwap = 31416;
    pHost->SetMemorySwap(ullMemorySwap);
    CPPUNIT_ASSERT(ullMemorySwap == pHost->GetMemorySwap());
    delete pHost;
}

void HostTestCase::GetSetDiskTotal()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullDiskTotal = 31416;
    pHost->SetDiskTotal(ullDiskTotal);
    CPPUNIT_ASSERT(ullDiskTotal == pHost->GetDiskTotal());
    delete pHost;
}

void HostTestCase::GetSetDiskFree()
{
    CBSLHost* pHost = new CBSLHost();
    wxUint64 ullDiskFree = 31416;
    pHost->SetDiskFree(ullDiskFree);
    CPPUNIT_ASSERT(ullDiskFree == pHost->GetDiskFree());
    delete pHost;
}

void HostTestCase::ParseEx()
{
    CBSLHost* pHost = new CBSLHost();
    CBSLXMLDocumentEx oDocument;
    CBSLXMLElementEx oElement;

    wxString strHost;

    wxString strName = wxT("rick.example.com");
    wxString strIPAddr = wxT("127.0.0.1");
    wxInt32 iTimezone = 31416;
    wxString strCrossProjectId = wxT("2ebd1e3fd6a66f46ed706f04f61fefb7");
    wxUint32 uiProcessorCount = 4;
    wxString strProcessorVendor = wxT("Intel");
    wxString strProcessorModel = wxT("Pentium");
    wxString strProcessorFeatures = wxT("fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss htt tm pni ssse3 cx16 sse4_1 syscall nx lm vmx smx tm2 pbe");
    wxUint32 ulProcessorFLOPS = 31416;
    wxUint32 ulProcessorIOPS = 31416;
    wxUint32 ulProcessorMemoryBandwidth = 31416;
    wxDateTime dtProcessorLastBenchmark = wxDateTime::Now();
    wxUint32 ulMemoryTotal = 31416;
    wxUint32 ulMemoryCache = 31416;
    wxUint32 ulMemorySwap = 31416;
    wxUint32 ulDiskTotal = 31416;
    wxUint32 ulDiskFree = 31416;
    wxString strOSName = wxT("Microsoft Windows 7");
    wxString strOSVersion = wxT("Ultimate x64 Edition, (06.01.7600.00)");

    strHost.Printf(
        wxT("<host_info>\n")
        wxT("    <domain_name>%s</domain_name>\n")
        wxT("    <ip_addr>%s</ip_addr>\n")
        wxT("    <timezone>%d</timezone>\n")
        wxT("    <host_cpid>%s</host_cpid>\n")
        wxT("    <p_ncpus>%d</p_ncpus>\n")
        wxT("    <p_vendor>%s</p_vendor>\n")
        wxT("    <p_model>%s</p_model>\n")
        wxT("    <p_features>%s</p_features>\n")
        wxT("    <p_fpops>%d</p_fpops>\n")
        wxT("    <p_iops>%d</p_iops>\n")
        wxT("    <p_membw>%d</p_membw>\n")
        wxT("    <p_calculated>%d</p_calculated>\n")
        wxT("    <m_nbytes>%d</m_nbytes>\n")
        wxT("    <m_cache>%d</m_cache>\n")
        wxT("    <m_swap>%d</m_swap>\n")
        wxT("    <d_total>%d</d_total>\n")
        wxT("    <d_free>%d</d_free>\n")
        wxT("    <os_name>%s</os_name>\n")
        wxT("    <os_version>%s</os_version>\n")
        wxT("</host_info>\n"),
        strName.c_str(),
        strIPAddr.c_str(),
        iTimezone,
        strCrossProjectId.c_str(),
        uiProcessorCount,
        strProcessorVendor.c_str(),
        strProcessorModel.c_str(),
        strProcessorFeatures.c_str(),
        ulProcessorFLOPS,
        ulProcessorIOPS,
        ulProcessorMemoryBandwidth,
        (wxUint32)dtProcessorLastBenchmark.GetTicks(),
        ulMemoryTotal,
        ulMemoryCache,
        ulMemorySwap,
        ulDiskTotal,
        ulDiskFree,
        strOSName.c_str(),
        strOSVersion.c_str()
    );

    oDocument.SetDocument(strHost);

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_HOST == oElement.GetNameHash())
        {
            pHost->ParseEx(oDocument);
        }
    }

    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetName().mb_str(), strName, pHost->GetName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetIPAddress().mb_str(), strIPAddr, pHost->GetIPAddress());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Timezone", iTimezone, pHost->GetTimezone());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetCrossProjectID().mb_str(), strCrossProjectId, pHost->GetCrossProjectID());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Processor Count", uiProcessorCount, pHost->GetProcessorCount());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetProcessorVendor().mb_str(), strProcessorVendor, pHost->GetProcessorVendor());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetProcessorModel().mb_str(), strProcessorModel, pHost->GetProcessorModel());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetProcessorFeatures().mb_str(), strProcessorFeatures, pHost->GetProcessorFeatures());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Processor FLOPS", (wxUint64)ulProcessorFLOPS, pHost->GetProcessorFLOPS());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Processor IOPS", (wxUint64)ulProcessorIOPS, pHost->GetProcessorIOPS());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Processor/Memory Bandwidth", (wxUint64)ulProcessorMemoryBandwidth, pHost->GetProcessorMemoryBandwidth());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Processor Last Benchmark", dtProcessorLastBenchmark.Format(), pHost->GetLastProcessorBenchmark().Format());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Memory Total", (wxUint64)ulMemoryTotal, pHost->GetMemoryTotal());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Processor Cache", (wxUint64)ulMemoryCache, pHost->GetProcessorCache());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Memory Swap", (wxUint64)ulMemorySwap, pHost->GetMemorySwap());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Disk Total", (wxUint64)ulDiskTotal, pHost->GetDiskTotal());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Disk Free", (wxUint64)ulDiskFree, pHost->GetDiskFree());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetOSName().mb_str(), strOSName, pHost->GetOSName());
    CPPUNIT_ASSERT_EQUAL_MESSAGE((const char*)pHost->GetOSVersion().mb_str(), strOSVersion, pHost->GetOSVersion());

    delete pHost;
}
