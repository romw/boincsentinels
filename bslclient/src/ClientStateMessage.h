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

#ifndef _CLIENTSTATEMESSAGE_H_
#define _CLIENTSTATEMESSAGE_H_

class CMessage: public CObject, public CBSLMessage
{
    DECLARE_DYNAMIC_CLASS(CMessage)

public:
    CMessage();
    CMessage(const CBSLMessage&);
    virtual ~CMessage();

    /// \brief Assignment Operator
    virtual CMessage& operator= (const CBSLMessage&);

    /// \brief Comparison Operator
    virtual bool operator== (const CBSLMessage&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CBSLMessage&);

    virtual void Dispose();

    BSLERRCODE Update(CBSLMessage&);
};


class CMessageIndex
{
public:
    CMessageIndex();
    CMessageIndex(CMessage* pMessage);
    CMessageIndex(wxInt32 iSeqNo);
    virtual ~CMessageIndex();

    /// \brief Comparison Operator
    virtual bool operator== (const CMessageIndex&);
    /// \brief Comparison Operator
    virtual bool operator!= (const CMessageIndex&);

    /// \brief
    CMessage* GetRecord();
    /// \brief
    wxInt32 GetSequenceNumber();

private:
    CMessage* m_pMessage;
    wxInt32 m_iSeqNo;
};

#endif

///
/// \}
