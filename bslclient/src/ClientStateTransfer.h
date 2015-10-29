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

#ifndef _CLIENTSTATETRANSFER_H_
#define _CLIENTSTATETRANSFER_H_

class CTransfer: public CObject, public CBSLTransfer
{
    DECLARE_DYNAMIC_CLASS(CTransfer)

public:
    CTransfer();
    CTransfer(const CBSLTransfer&);
    virtual ~CTransfer();

    /// \brief Assignment Operator
    virtual CTransfer& operator= (const CBSLTransfer&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLTransfer&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLTransfer&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLTransfer&);
};


class CTransferIndex
{
public:
    CTransferIndex();
    CTransferIndex(CTransfer* pTransfer);
    CTransferIndex(wxUint32 uiProjectHash, wxUint32 uiNameHash);
    virtual ~CTransferIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CTransferIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CTransferIndex&);

    /// \brief
    CTransfer* GetRecord();
    /// \brief
    wxUint32 GetProjectHash();
    /// \brief
    wxUint32 GetNameHash();

private:
    CTransfer* m_pTransfer;
    wxUint32 m_uiProjectHash;
    wxUint32 m_uiNameHash;
};

#endif

///
/// \}
