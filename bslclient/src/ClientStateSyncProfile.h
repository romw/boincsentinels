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

#ifndef _CLIENTSTATESYNCPROFILE_H_
#define _CLIENTSTATESYNCPROFILE_H_

class CSyncProfile: public CObject, public wxObject
{
    DECLARE_DYNAMIC_CLASS(CSyncProfile)

public:
    CSyncProfile();
    CSyncProfile(CBSLClient::AUTOSYNCPROPERTY uiID);
    virtual ~CSyncProfile();

    /// \brief
    virtual void Dispose();
    /// \brief Returns a unique key describing this sync property.
    wxUint32 GetDatabaseKey();
    /// \brief
    wxUint32 GetValue();
    /// \brief
    CBSLClient::AUTOSYNCPROPERTY GetID();
    /// \brief
    wxDateTime GetLastQueuedTime();

    /// \brief
    void SetValue(wxUint32 uiValue);
    /// \brief
    void SetLastQueuedTime(wxDateTime dtLastQueuedTime);

private:
    CBSLClient::AUTOSYNCPROPERTY m_uiID;
    wxUint32 m_uiValue;
    wxDateTime m_dtLastQueuedTime;
};

#endif

///
/// \}
