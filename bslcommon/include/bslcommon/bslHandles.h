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

#ifndef _BSLHANDLES_H_
#define _BSLHANDLES_H_

/// \brief A generic handle to a BOINC Sentinels object.
typedef void* BSLHANDLE;

/// \brief A handle to a application.
typedef BSLHANDLE BSLAPP;
/// \brief A handle to a application version.
typedef BSLHANDLE BSLAPPVERSION;
/// \brief A handle to a host.
typedef BSLHANDLE BSLHOST;
/// \brief A handle to a host status.
typedef BSLHANDLE BSLHOSTSTATUS;
/// \brief A handle to a message.
typedef BSLHANDLE BSLMESSAGE;
/// \brief A handle to a notification.
typedef BSLHANDLE BSLNOTIFICATION;
/// \brief A handle to a project.
typedef BSLHANDLE BSLPROJECT;
/// \brief A handle to a project statistic.
typedef BSLHANDLE BSLPROJECTSTATISTIC;
/// \brief A handle to a project list item.
typedef BSLHANDLE BSLPROJECTLISTITEM;
/// \brief A handle to a task.
typedef BSLHANDLE BSLTASK;
/// \brief A handle to a task instance.
typedef BSLHANDLE BSLTASKINSTANCE;
/// \brief A handle to a transfer.
typedef BSLHANDLE BSLTRANSFER;

#endif

///
/// \}
