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

#ifndef _CLIENTSTATETASKINSTANCE_H_
#define _CLIENTSTATETASKINSTANCE_H_

class CTaskInstance: public CObject, public CBSLTaskInstance
{
    DECLARE_DYNAMIC_CLASS(CTaskInstance)

public:
    CTaskInstance();
    CTaskInstance(const CBSLTaskInstance&);
    virtual ~CTaskInstance();

    /// \brief Assignment Operator
    virtual CTaskInstance& operator= (const CBSLTaskInstance&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLTaskInstance&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLTaskInstance&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLTaskInstance&);
};


class CTaskInstanceIndex
{
public:
    CTaskInstanceIndex();
    CTaskInstanceIndex(CTaskInstance* pTaskInstance);
    CTaskInstanceIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash);
    virtual ~CTaskInstanceIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CTaskInstanceIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CTaskInstanceIndex&);

    /// \brief
    CTaskInstance* GetRecord();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief
    wxUint32 GetNameHash();

private:
    CTaskInstance* m_pTaskInstance;
    wxUint32 m_uiProjectHash;
    wxUint32 m_uiNameHash;
};

#endif

///
/// \}
