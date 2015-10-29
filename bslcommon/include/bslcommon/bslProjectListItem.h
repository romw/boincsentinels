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

#ifndef _BSLCOMMONPROJECTLISTITEM_H_
#define _BSLCOMMONPROJECTLISTITEM_H_

#define BSLXMLTAGHASH_PROJECTLISTITEM \
    0xe2447c34

class CBSLProjectListItem: public CBSLProjectListItemEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLProjectListItem)

public:
    CBSLProjectListItem();
    virtual ~CBSLProjectListItem();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLProjectListItem&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLProjectListItem&) const;

    /// \brief Initialize CBSLProjectListItem state.
    void Clear();

    /// \brief Returns the URL of the project.
    wxString& GetMasterURL();
    /// \brief
    wxUint32 GetMasterURLHash();
    /// \brief Returns the name of the project.
    wxString& GetName();
    /// \brief Returns the description of the project.
    wxString& GetDescription();
    /// \brief Returns the general area of research for the project.
    wxString& GetGeneralArea();
    /// \brief Returns the specific area of research for the project.
    wxString& GetSpecificArea();
    /// \brief Returns the organization hosting the project.
    wxString& GetOrganization();
    /// \brief Returns the link to a logo image for the project.
    wxString& GetLogo();
    /// \brief Returns the supported platforms for the project.
    std::vector<wxString>& GetSupportedPlatforms();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the URL of the link.
    void SetMasterURL(wxString strMasterURL);
    /// \brief Sets the name of the link.
    void SetName(wxString strName);
    /// \brief Sets the description of the link.
    void SetDescription(wxString strDescription);
    /// \brief Returns the general area of research for the project.
    void SetGeneralArea(wxString strGeneralArea);
    /// \brief Returns the specific area of research for the project.
    void SetSpecificArea(wxString strSpecificArea);
    /// \brief Returns the organization hosting the project.
    void SetOrganization(wxString strOrganization);
    /// \brief Returns the link to a logo image for the project.
    void SetLogo(wxString strLogo);
    /// \brief Returns the supported platforms for the project.
    void SetSupportedPlatforms(std::vector<wxString>& oSupportedPlatforms);

private:
    wxString m_strMasterURL;
    wxUint32 m_uiMasterURLHash;
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strDescription;
    wxUint32 m_uiDescriptionHash;
    wxString m_strGeneralArea;
    wxUint32 m_uiGeneralAreaHash;
    wxString m_strSpecificArea;
    wxUint32 m_uiSpecificAreaHash;
    wxString m_strOrganization;
    wxUint32 m_uiOrganizationHash;
    wxString m_strLogo;
    wxUint32 m_uiLogoHash;
    std::vector<wxString> m_oSupportedPlatforms;
};

#endif

///
/// \}
