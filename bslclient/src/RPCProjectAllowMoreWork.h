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
/// \defgroup RPCProtocol RPC Protocol
/// \{

#ifndef _RPCPROJECTALLOWMOREWORK_H_
#define _RPCPROJECTALLOWMOREWORK_H_

class CRPCProjectAllowMoreWork: public CRPCProjectOperation
{
    DECLARE_DYNAMIC_CLASS(CRPCProjectAllowMoreWork)

public:
    CRPCProjectAllowMoreWork();
    ~CRPCProjectAllowMoreWork();
};

#endif

///
/// \}
