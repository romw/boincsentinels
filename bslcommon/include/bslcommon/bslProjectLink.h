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

#ifndef _BSLCOMMONPROJECTLINK_H_
#define _BSLCOMMONPROJECTLINK_H_

#define BSLXMLTAGHASH_PROJECTLINK \
    0xcf0fffd8

class CBSLProjectLink: public wxObject
{
    DECLARE_DYNAMIC_CLASS(CBSLProjectLink)

public:
    CBSLProjectLink();
    virtual ~CBSLProjectLink();

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLProjectLink&) const;
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLProjectLink&) const;

    /// \brief Initialize CBSLProjectLink state.
    void Clear();

    /// \brief Returns the name of the link.
    wxString& GetName();
    /// \brief Returns the description of the link.
    wxString& GetDescription();
    /// \brief Returns the URL of the link.
    wxString& GetLink();

    /// \brief
    BSLERRCODE ParseEx(CBSLXMLDocumentEx& oDocument);

    /// \brief Sets the name of the link.
    void SetName(wxString strName);
    /// \brief Sets the description of the link.
    void SetDescription(wxString strDescription);
    /// \brief Sets the URL of the link.
    void SetLink(wxString strLink);

private:
    wxString m_strName;
    wxUint32 m_uiNameHash;
    wxString m_strDescription;
    wxUint32 m_uiDescriptionHash;
    wxString m_strLink;
    wxUint32 m_uiLinkHash;
};

#endif

///
/// \}
