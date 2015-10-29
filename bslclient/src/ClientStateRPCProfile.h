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

#ifndef _CLIENTSTATERPCPROFILE_H_
#define _CLIENTSTATERPCPROFILE_H_

class CRPCProfile: public CObject, public wxObject
{
    DECLARE_DYNAMIC_CLASS(CRPCProfile)

public:
    CRPCProfile();
    CRPCProfile(wxString strRPCName);
    virtual ~CRPCProfile();

    /// \brief
    virtual void Dispose();

    /// \brief
    wxString GetRPCName();
    /// \brief
    wxUint64 GetExecutionCount();
    /// \brief
    wxDateTime GetLastRequestTime();
    /// \brief
    wxTimeSpan GetRequestDuration();
    /// \brief
    wxUint64 GetRequestSize();
    /// \brief
    wxTimeSpan GetResponseDuration();
    /// \brief
    wxUint64 GetResponseSize();
    /// \brief
    wxTimeSpan GetParseDuration();
    /// \brief
    wxTimeSpan GetTotalDuration();
    /// \brief
    wxUint64 GetTotalBytesSent();
    /// \brief
    wxUint64 GetTotalBytesReceived();
    /// \brief
    void Update(
        wxDateTime& dtLastRequestTime,
        wxUint64& ullRequestSize,
        wxUint64& ullResponseSize
    );

#ifdef __WXDEBUG__
    /// \brief
    void Update(
        wxDateTime& dtLastRequestTime,
        wxTimeSpan& tsRequestDuration,
        wxUint64& ullRequestSize,
        wxTimeSpan& tsResponseDuration,
        wxUint64& ullResponseSize,
        wxTimeSpan& tsParseDuration,
        wxTimeSpan& tsTotalDuration
    );
#endif

private:
    wxString m_strRPCName;
    wxUint64 m_ullExecutionCount;
    wxDateTime m_dtLastRequestTime;
    wxTimeSpan m_tsRequestDuration;
    wxUint64 m_ullRequestSize;
    wxTimeSpan m_tsResponseDuration;
    wxUint64 m_ullResponseSize;
    wxTimeSpan m_tsParseDuration;
    wxTimeSpan m_tsTotalDuration;
    wxUint64 m_ullTotalBytesSent;
    wxUint64 m_ullTotalBytesReceived;
};

#endif

///
/// \}
