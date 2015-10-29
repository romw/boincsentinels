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

#ifndef _BSLERRORS_H_
#define _BSLERRORS_H_

/// \brief Return codes for various BOINC Sentinels Library functions.
enum BSLERRCODE
{
    /// \brief the requested operation completed successfully.
    BSLERR_SUCCESS = 0,
    /// \brief the requested operation failed.
    BSLERR_FAILURE = 1,
    /// \brief the requested operation has been denied.
    BSLERR_ACCESS_DENIED = 2,
    /// \brief one of the provided parameters is invalid.
    BSLERR_INVALID_PARAMETER = 3,
    /// \brief the specified object could not be found.
    BSLERR_OBJECT_NOT_FOUND = 4,
    /// \brief the specified object has already been created.
    BSLERR_OBJECT_ALREADY_CREATED = 5,
    /// \brief the operation is in progress.
    BSLERR_OPERATION_IN_PROGRESS = 6,
    /// \brief the specified application could not be found.
    BSLERR_APP_NOT_FOUND = 7,
    /// \brief the specified application version could not be found.
    BSLERR_APPVERSION_NOT_FOUND = 8,
    /// \brief the specified host could not be found.
    BSLERR_HOST_NOT_FOUND = 9,
    /// \brief the specified host status could not be found.
    BSLERR_HOSTSTATUS_NOT_FOUND = 10,
    /// \brief the specified message could not be found.
    BSLERR_MESSAGE_NOT_FOUND = 11,
    /// \brief the specified notification could not be found.
    BSLERR_NOTIFICATION_NOT_FOUND = 12,
    /// \brief the specified project could not be found.
    BSLERR_PROJECT_NOT_FOUND = 13,
    /// \brief the specified project list item could not be found.
    BSLERR_PROJECTLISTITEM_NOT_FOUND = 14,
    /// \brief the specified project statistic could not be found.
    BSLERR_PROJECTSTATISTIC_NOT_FOUND = 15,
    /// \brief the specified task could not be found.
    BSLERR_TASK_NOT_FOUND = 16,
    /// \brief the specified task instance could not be found.
    BSLERR_TASKINSTANCE_NOT_FOUND = 17,
    /// \brief the specified transfer could not be found.
    BSLERR_TRANSFER_NOT_FOUND = 18,
    /// \brief the attempt to connect with the BOINC core client failed.
    BSLERR_CONNECT_ERROR = 19,
    /// \brief the specified host is not connected to a BOINC core client.
    BSLERR_CONNECT_NOT_CONNECTED = 20,
    /// \brief the specified host could not be found, connection to the BOINC core client failed.
    BSLERR_CONNECT_HOST_NOT_FOUND = 21,
    /// \brief the specified port could not be found, connection to the BOINC core client failed.
    BSLERR_CONNECT_PORT_NOT_FOUND = 22,
    /// \brief the connection to the BOINC core client timed out.
    BSLERR_CONNECT_TIME_OUT = 23,
    /// \brief could not read/write to the requested socket.
    BSLERR_CONNECT_IO_ERROR = 24,
    /// \brief the specified password failed to authenticate with the BOINC core client.
    BSLERR_CONNECT_AUTHENTICATION_ERROR = 25,
    /// \brief the required RPC Protocol version is not supported by the BOINC core client.
    BSLERR_CONNECT_VERSIONINCOMPATIBILITY_ERROR = 26,
    /// \brief the URL is missing
    BSLERR_MISSING_URL = 27,
    /// \brief the authenticator is missing
    BSLERR_MISSING_AUTHENTICATOR = 28,
    /// \brief the specified identity is invalid or banned.
    BSLERR_MALFORMED_IDENTITY = 29,
    /// \brief the specified identity and password combination is invalid.
    BSLERR_BAD_IDENTITY_OR_PASSWORD = 30,
    /// \brief the specified project is already attached
    BSLERR_ALREADY_ATTACHED = 31,
    /// \brief account creation has been disabled for the project.
    BSLERR_ACCOUNT_CREATION_DISABLED = 32,
    /// \brief an invite code is required to create an account for this project.
    BSLERR_INVITE_CODE_REQUIRED = 33
};

#endif

///
/// \}
