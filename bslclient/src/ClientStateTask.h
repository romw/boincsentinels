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

#ifndef _CLIENTSTATETASK_H_
#define _CLIENTSTATETASK_H_

class CTask: public CObject, public CBSLTask
{
    DECLARE_DYNAMIC_CLASS(CTask)

public:
    CTask();
    CTask(const CBSLTask&);
    virtual ~CTask();

    /// \brief Assignment Operator
    virtual CTask& operator= (const CBSLTask&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLTask&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLTask&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLTask&);
};


class CTaskIndex
{
public:
    CTaskIndex();
    CTaskIndex(CTask* pTask);
    CTaskIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash);
    virtual ~CTaskIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CTaskIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CTaskIndex&);

    /// \brief
    CTask* GetRecord();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief
    wxUint32 GetNameHash();

private:
    CTask* m_pTask;
    wxUint32 m_uiProjectHash;
    wxUint32 m_uiNameHash;
};

#endif

///
/// \}
