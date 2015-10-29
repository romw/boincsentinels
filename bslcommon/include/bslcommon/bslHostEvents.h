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

#ifndef _BSLCOMMONHOSTEVENTS_H_
#define _BSLCOMMONHOSTEVENTS_H_

class CBSLHostEventData: public wxObject, public CBSLEventData
{
    DECLARE_DYNAMIC_CLASS(CBSLHostEventData)

public:
    CBSLHostEventData();
    CBSLHostEventData(const CBSLHostEventData& data);
    ~CBSLHostEventData();

    /// \brief Returns a handle to the associated host.
    BSLHOST GetHostHandle();

    /// \brief Sets the associated host handle.
    void SetHostHandle(BSLHOST hHost);

private:
    BSLHOST m_hHost;
};

#endif

///
/// \}
