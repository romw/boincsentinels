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
/// \defgroup BSLXML BOINC Sentinels XML Library Interface
/// \{

#ifndef _LOOKUPTABLES_H_
#define _LOOKUPTABLES_H_

/// \brief End of Line (\\n \\r \\0)
extern const bool lookup_eol[256];

/// \brief Whitespace (space \\n \\r \\t \\0)
extern const bool lookup_whitespace[256];

/// \brief Node name (anything but space \\n \\r \\t / > ? \\0)
extern const bool lookup_node_name[256];

/// \brief Text (i.e. PCDATA) (anything but < \\0)
extern const bool lookup_text[256];

/// \brief Text (i.e. PCDATA) that does not require processing when whitespace
/// normalization is disabled (anything but < \\0 &)
extern const bool lookup_text_pure_no_ws[256];

/// \brief Text (i.e. PCDATA) that does not require processing when whitespace
/// normalizations is enabled (anything but < \\0 & space \\n \\r \\t)
extern const bool lookup_text_pure_with_ws[256];

/// \brief Attribute block (anything but \\n \\r \\t / < > = ? ! \\0)
extern const bool lookup_attributes[256];

/// \brief Attribute name (anything but space \\n \\r \\t / < > = ? ! \\0)
extern const bool lookup_attribute_name[256];

/// \brief Attribute data with single quote (anything but ' \\0)
extern const bool lookup_attribute_data_1[256];

/// \brief Attribute data with single quote that does not require processing (anything but ' \\0 &)
extern const bool lookup_attribute_data_1_pure[256];

/// \brief Attribute data with double quote (anything but " \\0)
extern const bool lookup_attribute_data_2[256];

/// \brief Attribute data with double quote that does not require processing (anything but " \\0 &)
extern const bool lookup_attribute_data_2_pure[256];

/// <
extern const wxChar xml_node_begin[1];

/// >
extern const wxChar xml_node_end[1];

/// </
extern const wxChar xml_node_closing_tag[2];

/// <!--
extern const wxChar xml_comment_begin[4];

/// -->
extern const wxChar xml_comment_end[3];

/// <![CDATA[
extern const wxChar xml_cdata_begin[8];

/// ]]>
extern const wxChar xml_cdata_end[3];

/// >
extern const wxChar xml_container_begin[1];

/// </
extern const wxChar xml_container_end[2];

/// />
extern const wxChar xml_bool_node[2];

///
extern const wxChar preset_true_string[2];

///
extern const wxUint32 preset_true_string_hash;

///
extern const wxChar preset_empty_string[2];

///
extern const wxUint32 preset_empty_string_hash;

#endif

///
/// \}
