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

#ifndef _CLIENTSTATEAPP_H_
#define _CLIENTSTATEAPP_H_

class CApp: public CObject, public CBSLApp
{
    DECLARE_DYNAMIC_CLASS(CApp)

public:
    CApp();
    CApp(const CBSLApp&);
    virtual ~CApp();

    /// \brief Assignment Operator
    virtual CApp& operator= (const CBSLApp&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLApp&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLApp&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLApp&);
};


class CAppIndex
{
public:
    CAppIndex();
    CAppIndex(CApp* pApp);
    CAppIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash);
    virtual ~CAppIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CAppIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CAppIndex&);

    /// \brief
    CApp* GetRecord();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief
    wxUint32 GetNameHash();

private:
    CApp* m_pApp;
    wxUint32 m_uiProjectHash;
    wxUint32 m_uiNameHash;
};

#endif

///
/// \}
