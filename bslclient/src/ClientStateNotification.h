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

#ifndef _CLIENTSTATENOTIFICATION_H_
#define _CLIENTSTATENOTIFICATION_H_

class CNotification: public CObject, public CBSLNotification
{
    DECLARE_DYNAMIC_CLASS(CNotification)

public:
    CNotification();
    CNotification(const CBSLNotification&);
    virtual ~CNotification();

    /// \brief Assignment Operator
    virtual CNotification& operator= (const CBSLNotification&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLNotification&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLNotification&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLNotification&);
};


class CNotificationIndex
{
public:
    CNotificationIndex();
    CNotificationIndex(CNotification* pNotification);
    CNotificationIndex(wxInt32 iSeqNo);
    virtual ~CNotificationIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CNotificationIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CNotificationIndex&);

    /// \brief
    CNotification* GetRecord();
    /// \brief
    wxInt32 GetSequenceNumber();

private:
    CNotification* m_pNotification;
    wxInt32 m_iSeqNo;
};

#endif

///
/// \}
