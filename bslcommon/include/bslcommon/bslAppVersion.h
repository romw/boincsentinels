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

#ifndef _BSLCOMMONAPPVERSION_H_
#define _BSLCOMMONAPPVERSION_H_

#define BSLXMLTAGHASH_APPVERSION \
    0x74ee5a2b

class CBSLAppVersion: public CBSLAppVersionEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLAppVersion)

public:
    CBSLAppVersion();
    virtual ~CBSLAppVersion();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLAppVersion&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLAppVersion&) const;

    /// \brief Initialize CBSLAppVersion state.
    void Clear();

    /// \brief Returns the URL of the project that generated the application.
    wxString& GetProject();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief Returns the name of the application.
    wxString& GetName();
    /// \brief
    wxUint32 GetNameHash();
    /// \brief Returns the plan class of the application.
    wxString& GetPlanClass();
    /// \brief
    wxUint32 GetPlanClassHash();
    /// \brief Returns the version of the application.
    wxUint32 GetVersion();
    /// \brief Returns the major version of the application.
    wxUint32 GetVersionMajor();
    /// \brief Returns the minor version of the application.
    wxUint32 GetVersionMinor();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the URL of the project that generated the application.
    void SetProject(wxString strProject);
    /// \brief
    void SetProject(wxString strProject, wxUint32 uiHash);
    /// \brief Sets the name of the application.
    void SetName(wxString strName);
    /// \brief
    void SetName(wxString strName, wxUint32 uiHash);
    /// \brief Sets the plan class of the application.
    void SetPlanClass(wxString strPlanClass);
    /// \brief
    void SetPlanClass(wxString strPlanClass, wxUint32 uiHash);
    /// \brief Sets the version of the application.
    void SetVersion(wxUint32 uiVersion);

private:
    wxString m_strProject;
    wxUint32 m_uiProjectHash;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strPlanClass;
    wxUint32 m_uiPlanClassHash;
    wxUint32 m_uiVersion;
};

#endif

///
/// \}
