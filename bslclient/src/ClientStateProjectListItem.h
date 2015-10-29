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

#ifndef _CLIENTSTATEPROJECTLISTITEM_H_
#define _CLIENTSTATEPROJECTLISTITEM_H_

class CProjectListItem: public CObject, public CBSLProjectListItem
{
    DECLARE_DYNAMIC_CLASS(CProjectListItem)

public:
    CProjectListItem();
    CProjectListItem(const CBSLProjectListItem&);
    virtual ~CProjectListItem();

    /// \brief Assignment Operator
    virtual CProjectListItem& operator= (const CBSLProjectListItem&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLProjectListItem&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLProjectListItem&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLProjectListItem&);
};


class CProjectListItemIndex
{
public:
    CProjectListItemIndex();
    CProjectListItemIndex(CProjectListItem* pProjectListItem);
    CProjectListItemIndex(wxUint32 uiMasterURLHash);
    virtual ~CProjectListItemIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CProjectListItemIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CProjectListItemIndex&);

    /// \brief
    CProjectListItem* GetRecord();
    /// \brief
    wxUint32 GetMasterURLHash();

private:
    CProjectListItem* m_pProjectListItem;
    wxUint32 m_uiMasterURLHash;
};

#endif

///
/// \}
