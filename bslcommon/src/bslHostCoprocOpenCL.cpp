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


IMPLEMENT_DYNAMIC_CLASS(CBSLHostCoprocOpenCL, wxObject);

CBSLHostCoprocOpenCL::CBSLHostCoprocOpenCL() :
wxObject()
{
    Clear();
}

CBSLHostCoprocOpenCL::~CBSLHostCoprocOpenCL()
{
}

bool CBSLHostCoprocOpenCL::operator== (const CBSLHostCoprocOpenCL& bslHostCoprocOpenCL) const
{
    if (m_uiVendorID != bslHostCoprocOpenCL.m_uiVendorID) return false;
    if (m_bAvailable != bslHostCoprocOpenCL.m_bAvailable) return false;
    if (m_ullHalfFloatConfig != bslHostCoprocOpenCL.m_ullHalfFloatConfig) return false;
    if (m_ullSingleFloatConfig != bslHostCoprocOpenCL.m_ullSingleFloatConfig) return false;
    if (m_ullDoubleFloatConfig != bslHostCoprocOpenCL.m_ullDoubleFloatConfig) return false;
    if (m_bLittleEndian != bslHostCoprocOpenCL.m_bLittleEndian) return false;
    if (m_ullExecutionCapabilities != bslHostCoprocOpenCL.m_ullExecutionCapabilities) return false;
    if (m_ullGlobalMemorySize != bslHostCoprocOpenCL.m_ullGlobalMemorySize) return false;
    if (m_ullLocalMemorySize != bslHostCoprocOpenCL.m_ullLocalMemorySize) return false;
    if (m_uiMaximumClockFrequency != bslHostCoprocOpenCL.m_uiMaximumClockFrequency) return false;
    if (m_uiMaximumComputeUnits != bslHostCoprocOpenCL.m_uiMaximumComputeUnits) return false;
    if (m_uiNameHash != bslHostCoprocOpenCL.m_uiNameHash) return false;
    if (m_uiVendorHash != bslHostCoprocOpenCL.m_uiVendorHash) return false;
    if (m_uiExtensionsHash != bslHostCoprocOpenCL.m_uiExtensionsHash) return false;
    if (m_uiPlatformVersionHash != bslHostCoprocOpenCL.m_uiPlatformVersionHash) return false;
    if (m_uiDeviceVersionHash != bslHostCoprocOpenCL.m_uiDeviceVersionHash) return false;
    if (m_uiDriverVersionHash != bslHostCoprocOpenCL.m_uiDriverVersionHash) return false;
    return true;
}

bool CBSLHostCoprocOpenCL::operator!= (const CBSLHostCoprocOpenCL& bslHostCoprocOpenCL) const
{
    return !(*this == bslHostCoprocOpenCL);
}

void CBSLHostCoprocOpenCL::Clear()
{
    m_strName.clear();
    m_uiNameHash = 0;
    m_strVendor.clear();
    m_uiVendorHash = 0;
    m_uiVendorID = 0;
    m_bAvailable = 0;
    m_ullHalfFloatConfig = 0;
    m_ullSingleFloatConfig = 0;
    m_ullDoubleFloatConfig = 0;
    m_bLittleEndian = 0;
    m_ullExecutionCapabilities = 0;
    m_strExtensions.empty();
    m_uiExtensionsHash = 0;
    m_ullGlobalMemorySize = 0;
    m_ullLocalMemorySize = 0;
    m_uiMaximumClockFrequency = 0;
    m_uiMaximumComputeUnits = 0;
    m_strPlatformVersion.clear();
    m_uiPlatformVersionHash = 0;
    m_strDeviceVersion.clear();
    m_uiDeviceVersionHash = 0;
    m_strDriverVersion.clear();
    m_uiDriverVersionHash = 0;
}

wxString& CBSLHostCoprocOpenCL::GetName()
{
    return m_strName;
}

wxString& CBSLHostCoprocOpenCL::GetVendor()
{
    return m_strVendor;
}

wxUint32 CBSLHostCoprocOpenCL::GetVendorID()
{
    return m_uiVendorID;
}

wxUint64 CBSLHostCoprocOpenCL::GetHalfFloatConfig()
{
    return m_ullHalfFloatConfig;
}

wxUint64 CBSLHostCoprocOpenCL::GetSingleFloatConfig()
{
    return m_ullSingleFloatConfig;
}

wxUint64 CBSLHostCoprocOpenCL::GetDoubleFloatConfig()
{
    return m_ullDoubleFloatConfig;
}

wxUint64 CBSLHostCoprocOpenCL::GetExecutionCapabilities()
{
    return m_ullExecutionCapabilities;
}

wxString& CBSLHostCoprocOpenCL::GetExtensions()
{
    return m_strExtensions;
}

wxUint64 CBSLHostCoprocOpenCL::GetGlobalMemorySize()
{
    return m_ullGlobalMemorySize;
}

wxUint64 CBSLHostCoprocOpenCL::GetLocalMemorySize()
{
    return m_ullLocalMemorySize;
}

wxUint32 CBSLHostCoprocOpenCL::GetMaximumClockFrequency()
{
    return m_uiMaximumClockFrequency;
}

wxUint32 CBSLHostCoprocOpenCL::GetMaximumComputeUnits()
{
    return m_uiMaximumComputeUnits;
}

wxString& CBSLHostCoprocOpenCL::GetPlatformVersion()
{
    return m_strPlatformVersion;
}

wxString& CBSLHostCoprocOpenCL::GetDeviceVersion()
{
    return m_strDeviceVersion;
}

wxString& CBSLHostCoprocOpenCL::GetDriverVersion()
{
    return m_strDriverVersion;
}

wxUint32 CBSLHostCoprocOpenCL::IsAvailable()
{
    return m_bAvailable;
}

wxUint32 CBSLHostCoprocOpenCL::IsLittleEndian()
{
    return m_bLittleEndian;
}

BSLERRCODE CBSLHostCoprocOpenCL::ParseEx(CBSLXMLDocumentEx& oDocument)
{
    CBSLXMLElementEx oElement;

    while (BSLXMLERR_SUCCESS == oDocument.GetNextElement(oElement))
    {
        if (BSLXMLTAGHASH_HOSTCOPROCOPENCL == oElement.GetNameHash() && CBSLXMLElementEx::ElementTypeContainerEnd == oElement.GetType()) break;
        switch(oElement.GetNameHash())
        {
            case 0x2f8b3bf4:    // name
                m_strName = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiNameHash = oElement.GetValueHash();
                break;
            case 0x0d89e1c7:    // vendor
                m_strVendor = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiVendorHash = oElement.GetValueHash();
                break;
            case 0x014b333a:    // available
                m_bAvailable = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0xa1a218e1:    // vendor_id
                m_uiVendorID = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0xab509534:    // half_fp_config
                m_ullHalfFloatConfig = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x39bc6d6b:    // single_fp_config
                m_ullSingleFloatConfig = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x45a175a4:    // double_fp_config
                m_ullDoubleFloatConfig = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x9eddf85f:    // endian_little
                m_bLittleEndian = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0x12819f8a:    // execution_capabilities
                m_ullExecutionCapabilities = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x51b2805b:    // extensions
                m_strExtensions = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiExtensionsHash = oElement.GetValueHash();
                break;
            case 0x823705d2:    // global_mem_size
                m_ullGlobalMemorySize = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x2be0a4cc:    // local_mem_size
                m_ullLocalMemorySize = CBSLXMLConverterEx::ConvertToUI64(oElement.GetValue());
                break;
            case 0x84a73249:    // max_clock_frequency
                m_uiMaximumClockFrequency = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0xcd81097f:    // max_compute_units
                m_uiMaximumComputeUnits = CBSLXMLConverterEx::ConvertToUI32(oElement.GetValue());
                break;
            case 0x3fba2697:    // opencl_platform_version
                m_strPlatformVersion = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiPlatformVersionHash = oElement.GetValueHash();
                break;
            case 0x14770614:    // opencl_device_version
                m_strDeviceVersion = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiDeviceVersionHash = oElement.GetValueHash();
                break;
            case 0x4c5dca28:    // opencl_driver_version
                m_strDriverVersion = CBSLXMLConverterEx::ConvertToString(oElement.GetValue(), oElement.GetValueLength());
                m_uiDriverVersionHash = oElement.GetValueHash();
                break;
            default:
#ifdef __WXDEBUG__
                wxLogTrace(
                    wxT("BSLCommon Parser"),
                    wxT("CBSLHostCoprocOpenCL::ParseEx: Hash: '0x%x', Name: '%s'"),
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

void CBSLHostCoprocOpenCL::SetName(wxString strName)
{
    m_strName = strName;
    m_uiNameHash = bslXMLStrHash32(m_strName.c_str(), m_strName.size());
}

void CBSLHostCoprocOpenCL::SetVendorID(wxUint32 uiVendorID)
{
    m_uiVendorID = uiVendorID;
}

void CBSLHostCoprocOpenCL::SetVendor(wxString strVendor)
{
    m_strVendor = strVendor;
    m_uiVendorHash = bslXMLStrHash32(m_strVendor.c_str(), m_strVendor.size());
}

void CBSLHostCoprocOpenCL::SetHalfFloatConfig(wxUint64 ullHalfFloatConfig)
{
    m_ullHalfFloatConfig = ullHalfFloatConfig;
}

void CBSLHostCoprocOpenCL::SetSingleFloatConfig(wxUint64 ullSingleFloatConfig)
{
    m_ullSingleFloatConfig = ullSingleFloatConfig;
}

void CBSLHostCoprocOpenCL::SetDoubleFloatConfig(wxUint64 ullDoubleFloatConfig)
{
    m_ullDoubleFloatConfig = ullDoubleFloatConfig;
}

void CBSLHostCoprocOpenCL::SetExecutionCapabilities(wxUint64 ullExecutionCapabilities)
{
    m_ullExecutionCapabilities = ullExecutionCapabilities;
}

void CBSLHostCoprocOpenCL::SetExtensions(wxString strExtensions)
{
    m_strExtensions = strExtensions;
    m_uiExtensionsHash = bslXMLStrHash32(m_strExtensions.c_str(), m_strExtensions.size());
}

void CBSLHostCoprocOpenCL::SetGlobalMemorySize(wxUint64 ullGlobalMemorySize)
{
    m_ullGlobalMemorySize = ullGlobalMemorySize;
}

void CBSLHostCoprocOpenCL::SetLocalMemorySize(wxUint64 ullLocalMemorySize)
{
    m_ullLocalMemorySize = ullLocalMemorySize;
}

void CBSLHostCoprocOpenCL::SetMaximumClockFrequency(wxUint32 uiMaximumClockFrequency)
{
    m_uiMaximumClockFrequency = uiMaximumClockFrequency;
}

void CBSLHostCoprocOpenCL::SetMaximumComputeUnits(wxUint32 uiMaximumComputeUnits)
{
    m_uiMaximumComputeUnits = uiMaximumComputeUnits;
}

void CBSLHostCoprocOpenCL::SetPlatformVersion(wxString strPlatformVersion)
{
    m_strPlatformVersion = strPlatformVersion;
    m_uiPlatformVersionHash = bslXMLStrHash32(m_strPlatformVersion.c_str(), m_strPlatformVersion.size());
}

void CBSLHostCoprocOpenCL::SetDeviceVersion(wxString strDeviceVersion)
{
    m_strDeviceVersion = strDeviceVersion;
    m_uiDeviceVersionHash = bslXMLStrHash32(m_strDeviceVersion.c_str(), m_strDeviceVersion.size());
}

void CBSLHostCoprocOpenCL::SetDriverVersion(wxString strDriverVersion)
{
    m_strDriverVersion = strDriverVersion;
    m_uiDriverVersionHash = bslXMLStrHash32(m_strDriverVersion.c_str(), m_strDriverVersion.size());
}

void CBSLHostCoprocOpenCL::SetAvailable(wxUint32 bAvailable)
{
    m_bAvailable = bAvailable;
}

void CBSLHostCoprocOpenCL::SetLittleEndian(wxUint32 bLittleEndian)
{
    m_bLittleEndian = bLittleEndian;
}
