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

#ifndef _BSLCOMMONHOSTCOPROCOPENCL_H_
#define _BSLCOMMONHOSTCOPROCOPENCL_H_

#define BSLXMLTAGHASH_HOSTCOPROCOPENCL \
    0x334c76fb

class CBSLHostCoprocOpenCL: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CBSLHostCoprocOpenCL)

public:
    CBSLHostCoprocOpenCL();
    virtual ~CBSLHostCoprocOpenCL();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLHostCoprocOpenCL&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLHostCoprocOpenCL&) const;

    /// \brief Initialize CBSLHostCoprocOpenCL state.
    void Clear();

    /// \brief
    wxString& GetName();
    /// \brief
    wxString& GetVendor();
    /// \brief
    wxUint32 GetVendorID();
    /// \brief
    wxUint64 GetHalfFloatConfig();
    /// \brief
    wxUint64 GetSingleFloatConfig();
    /// \brief
    wxUint64 GetDoubleFloatConfig();
    /// \brief
    wxUint64 GetExecutionCapabilities();
    /// \brief
    wxString& GetExtensions();
    /// \brief
    wxUint64 GetGlobalMemorySize();
    /// \brief
    wxUint64 GetLocalMemorySize();
    /// \brief
    wxUint32 GetMaximumClockFrequency();
    /// \brief
    wxUint32 GetMaximumComputeUnits();
    /// \brief
    wxString& GetPlatformVersion();
    /// \brief
    wxString& GetDeviceVersion();
    /// \brief
    wxString& GetDriverVersion();
    /// \brief
    wxUint32 IsAvailable();
    /// \brief
    wxUint32 IsLittleEndian();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief
    void SetName(wxString strName);
    /// \brief
    void SetVendor(wxString strVendor);
    /// \brief
    void SetVendorID(wxUint32 uiVendorID);
    /// \brief
    void SetHalfFloatConfig(wxUint64 ullHalfFloatConfig);
    /// \brief
    void SetSingleFloatConfig(wxUint64 ullSingleFloatConfig);
    /// \brief
    void SetDoubleFloatConfig(wxUint64 ullDoubleFloatConfig);
    /// \brief
    void SetExecutionCapabilities(wxUint64 ullExecutionCapabilities);
    /// \brief
    void SetExtensions(wxString strExtensions);
    /// \brief
    void SetGlobalMemorySize(wxUint64 ullGlobalMemorySize);
    /// \brief
    void SetLocalMemorySize(wxUint64 ullLocalMemorySize);
    /// \brief
    void SetMaximumClockFrequency(wxUint32 uiMaximumClockFrequency);
    /// \brief
    void SetMaximumComputeUnits(wxUint32 uiMaximumComputeUnits);
    /// \brief
    void SetPlatformVersion(wxString strPlatformVersion);
    /// \brief
    void SetDeviceVersion(wxString strDeviceVersion);
    /// \brief
    void SetDriverVersion(wxString strDriverVersion);
    /// \brief
    void SetAvailable(wxUint32 bAvailable);
    /// \brief
    void SetLittleEndian(wxUint32 bLittleEndian);

private:
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strVendor;
    wxUint32 m_uiVendorHash;
    wxUint32 m_uiVendorID;
    wxUint32 m_bAvailable;
    wxUint64 m_ullHalfFloatConfig;
    wxUint64 m_ullSingleFloatConfig;
    wxUint64 m_ullDoubleFloatConfig;
    wxUint32 m_bLittleEndian;
    wxUint64 m_ullExecutionCapabilities;
    wxString m_strExtensions;
    wxUint32 m_uiExtensionsHash;
    wxUint64 m_ullGlobalMemorySize;
    wxUint64 m_ullLocalMemorySize;
    wxUint32 m_uiMaximumClockFrequency;
    wxUint32 m_uiMaximumComputeUnits;
    wxString m_strPlatformVersion;
    wxUint32 m_uiPlatformVersionHash;
    wxString m_strDeviceVersion;
    wxUint32 m_uiDeviceVersionHash;
    wxString m_strDriverVersion;
    wxUint32 m_uiDriverVersionHash;
};

#endif

///
/// \}
