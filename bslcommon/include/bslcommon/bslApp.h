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

#ifndef _BSLCOMMONAPP_H_
#define _BSLCOMMONAPP_H_

#define BSLXMLTAGHASH_APP \
    0x359c196e

class CBSLApp: public CBSLAppEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLApp)

public:
    CBSLApp();
    virtual ~CBSLApp();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLApp&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLApp&) const;

    /// \brief Initialize CBSLApp state.
    void Clear();

    /// \brief Returns the URL of the project that generated the application.
    wxString& GetProject();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief Returns the name of the application.
    wxString& GetName();
    /// \brief
    wxUint32 GetNameHash();
    /// \brief Returns the user friendly name of the application.
    wxString& GetUserFriendlyName();
    /// \brief Returns whether or not the application is CPU intensive.
    bool IsNonCPUIntensive();

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
    /// \brief Sets the user friendly name of the application.
    void SetUserFriendlyName(wxString strUserFriendlyName);
    /// \brief
    void SetUserFriendlyName(wxString strUserFriendlyName, wxUint32 uiHash);
    /// \brief Sets the non CPU intensive flag.
    void SetNonCPUIntensive(bool bNonCPUIntensive);

private:
    wxString m_strProject;
    wxUint32 m_uiProjectHash;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strUserFriendlyName;
    wxUint32 m_uiUserFriendlyNameHash;
    bool m_bNonCPUIntensive;
};

#endif

///
/// \}
