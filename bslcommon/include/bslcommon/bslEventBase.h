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

#ifndef _BSLCOMMONEVENTBASE_H_
#define _BSLCOMMONEVENTBASE_H_

class CBSLEventData
{
public:
    CBSLEventData();
    CBSLEventData(const CBSLEventData& data);
    ~CBSLEventData();

    /// \brief
    wxUIntPtr GetData();

    /// \brief
    void SetData(wxUIntPtr pData);

private:
    wxUIntPtr m_pData;
};


class CBSLAuditLogEventData
{
public:
    CBSLAuditLogEventData();
    CBSLAuditLogEventData(const CBSLAuditLogEventData& data);
    ~CBSLAuditLogEventData();

    /// \brief
    bool IsAdded();
    /// \brief
    bool IsDeleted();
    /// \brief
    bool IsUpdated();

    /// \brief
    void SetAdded(bool bValue);
    /// \brief
    void SetDeleted(bool bValue);
    /// \brief
    void SetUpdated(bool bValue);

private:
    bool m_bAdded;
    bool m_bDeleted;
    bool m_bUpdated;
};

#endif

///
/// \}
