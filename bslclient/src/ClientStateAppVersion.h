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
/// \defgroup LibraryState Library State
/// \{

#ifndef _CLIENTSTATEAPPVERSION_H_
#define _CLIENTSTATEAPPVERSION_H_

class CAppVersion: public CObject, public CBSLAppVersion
{
    DECLARE_DYNAMIC_CLASS(CAppVersion)

public:
    CAppVersion();
    CAppVersion(const CBSLAppVersion&);
    virtual ~CAppVersion();

    /// \brief Assignment Operator
    virtual CAppVersion& operator= (const CBSLAppVersion&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLAppVersion&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLAppVersion&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLAppVersion&);
};


class CAppVersionIndex
{
public:
    CAppVersionIndex();
    CAppVersionIndex(CAppVersion* pAppVersion);
    CAppVersionIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash, wxUint32 uiVersion, wxUint32 uiPlanClassHash);
    virtual ~CAppVersionIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CAppVersionIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CAppVersionIndex&);

    /// \brief
    CAppVersion* GetRecord();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief
    wxUint32 GetVersion();
    /// \brief
    wxUint32 GetPlanClassHash();
    /// \brief
    wxUint32 GetNameHash();

private:
    CAppVersion* m_pAppVersion;
    wxUint32 m_uiProjectHash;
    wxUint32 m_uiVersion;
    wxUint32 m_uiPlanClassHash;
    wxUint32 m_uiNameHash;
};

#endif

///
/// \}
