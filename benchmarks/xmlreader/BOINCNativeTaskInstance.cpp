// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#include "stdwx.h"
#include "bslxml/bslXMLTypes.h"
#include "bslcommon/bslCommonTypes.h"
#include "BOINCXMLStream.h"
#include "BOINCNativeParsers.h"
#include "BOINCNativeTaskInstance.h"
#include "BOINCParsers.h"

TASKINSTANCE::TASKINSTANCE()
{
    clear();
}

TASKINSTANCE::~TASKINSTANCE()
{
    clear();
}

void TASKINSTANCE::clear()
{
    wxStrcpy(name, wxT(""));
    wxStrcpy(wu_name, wxT(""));
    wxStrcpy(plan_class, wxT(""));
    wxStrcpy(project_url, wxT(""));
    wxStrcpy(graphics_exec_path, wxT(""));
    wxStrcpy(slot_path, wxT(""));
    wxStrcpy(resources, wxT(""));
    version_num = 0;
    report_deadline = 0;
    received_time = 0;
    ready_to_report = false;
    got_server_ack = false;
    final_cpu_time = 0;
    final_elapsed_time = 0;
    state = 0;
    scheduler_state = 0;
    exit_status = 0;
    signal = 0;
    suspended_via_gui = false;
    project_suspended_via_gui = false;
    coproc_missing = false;
    gpu_mem_wait = false;
    active_task = false;
    active_task_state = 0;
    app_version_num = 0;
    slot = -1;
    pid = 0;
    checkpoint_cpu_time = 0;
    current_cpu_time = 0;
    fraction_done = 0;
    elapsed_time = 0;
    swap_size = 0;
    working_set_size_smoothed = 0;
    estimated_cpu_time_remaining = 0;
    supports_graphics = false;
    graphics_mode_acked = 0;
    too_large = false;
    needs_shmem = false;
    edf_scheduled = false;
}

void TASKINSTANCE::Parse(CBOINCXMLStream& oXML)
{
    wxChar* pszBuffer;
    double d;
    while (oXML.ReadNextLine())
    {
        if (oXML.CurrentLineMatchesTag(wxT("</result>"))) break;

        pszBuffer = oXML.GetCurrentLine();

        if (parse_str(pszBuffer, wxT("<name>"), name, sizeof(name))) continue;
        if (parse_str(pszBuffer, wxT("<wu_name>"), wu_name, sizeof(wu_name))) continue;
        if (parse_int(pszBuffer, wxT("<version_num>"), version_num)) continue;
        if (parse_str(pszBuffer, wxT("<plan_class>"), plan_class, sizeof(plan_class))) continue;
        if (parse_str(pszBuffer, wxT("<project_url>"), project_url, sizeof(project_url))) continue;
        if (parse_double(pszBuffer, wxT("<report_deadline>"), report_deadline)) continue;
        if (parse_double(pszBuffer, wxT("<received_time>"), received_time)) continue;
        if (parse_bool(pszBuffer, wxT("ready_to_report"), ready_to_report)) continue;
        if (parse_bool(pszBuffer, wxT("got_server_ack"), got_server_ack)) continue;
        if (parse_bool(pszBuffer, wxT("suspended_via_gui"), suspended_via_gui)) continue;
        if (parse_bool(pszBuffer, wxT("project_suspended_via_gui"), project_suspended_via_gui)) continue;
        if (parse_bool(pszBuffer, wxT("coproc_missing"), coproc_missing)) continue;
        if (parse_bool(pszBuffer, wxT("gpu_mem_wait"), gpu_mem_wait)) continue;
        if (match_tag(pszBuffer, wxT("<active_task>"))) {
            active_task = true;
            continue;
        }
        if (parse_bool(pszBuffer, wxT("supports_graphics"), supports_graphics)) continue;
        if (parse_int(pszBuffer, wxT("<graphics_mode_acked>"), graphics_mode_acked)) continue;
        if (parse_double(pszBuffer, wxT("<final_cpu_time>"), final_cpu_time)) continue;
        if (parse_double(pszBuffer, wxT("<final_elapsed_time>"), final_elapsed_time)) continue;
        if (parse_int(pszBuffer, wxT("<state>"), state)) continue;
        if (parse_int(pszBuffer, wxT("<scheduler_state>"), scheduler_state)) continue;
        if (parse_int(pszBuffer, wxT("<exit_status>"), exit_status)) continue;
        if (parse_int(pszBuffer, wxT("<signal>"), signal)) continue;
        if (parse_int(pszBuffer, wxT("<active_task_state>"), active_task_state)) continue;
        if (parse_int(pszBuffer, wxT("<app_version_num>"), app_version_num)) continue;
        if (parse_int(pszBuffer, wxT("<slot>"), slot)) continue;
        if (parse_int(pszBuffer, wxT("<pid>"), pid)) continue;
        if (parse_double(pszBuffer, wxT("<checkpoint_cpu_time>"), checkpoint_cpu_time)) continue;
        if (parse_double(pszBuffer, wxT("<current_cpu_time>"), current_cpu_time)) continue;
        if (parse_double(pszBuffer, wxT("<elapsed_time>"), elapsed_time)) continue;
        if (parse_double(pszBuffer, wxT("<swap_size>"), swap_size)) continue;
        if (parse_double(pszBuffer, wxT("<working_set_size>"), d)) continue;
        if (parse_double(pszBuffer, wxT("<page_fault_rate>"), d)) continue;
        if (parse_double(pszBuffer, wxT("<working_set_size_smoothed>"), working_set_size_smoothed)) continue;
        if (parse_double(pszBuffer, wxT("<fraction_done>"), fraction_done)) continue;
        if (parse_double(pszBuffer, wxT("<estimated_cpu_time_remaining>"), estimated_cpu_time_remaining)) continue;
        if (parse_bool(pszBuffer, wxT("too_large"), too_large)) continue;
        if (parse_bool(pszBuffer, wxT("needs_shmem"), needs_shmem)) continue;
        if (parse_bool(pszBuffer, wxT("edf_scheduled"), edf_scheduled)) continue;
        if (parse_str(pszBuffer, wxT("graphics_exec_path"), graphics_exec_path, sizeof(graphics_exec_path))) continue;
        if (parse_str(pszBuffer, wxT("slot_path"), slot_path, sizeof(slot_path))) continue;
        if (parse_str(pszBuffer, wxT("resources"), resources, sizeof(resources))) continue;
    }
}

void TASKINSTANCE::ParseV2(XML_PARSER& xp)
{
    double d;
    while (!xp.get_tag()) {
        if (!xp.is_tag) {
            _ftprintf(stderr, wxT("unexpected text: %s\n"), xp.parsed_tag);
            continue;
        }
        if (xp.match_tag(wxT("/result"))) {
            return;
        }
        if (xp.match_tag(wxT("/active_task"))) continue;
        if (xp.parse_str(wxT("name"), name, sizeof(name))) continue;
        if (xp.parse_str(wxT("wu_name"), wu_name, sizeof(wu_name))) continue;
        if (xp.parse_int(wxT("version_num"), version_num)) continue;
        if (xp.parse_str(wxT("plan_class"), plan_class, sizeof(plan_class))) continue;
        if (xp.parse_str(wxT("project_url"), project_url, sizeof(project_url))) continue;
        if (xp.parse_double(wxT("report_deadline"), report_deadline)) continue;
        if (xp.parse_double(wxT("received_time"), received_time)) continue;
        if (xp.parse_bool(wxT("ready_to_report"), ready_to_report)) continue;
        if (xp.parse_bool(wxT("got_server_ack"), got_server_ack)) continue;
        if (xp.parse_bool(wxT("suspended_via_gui"), suspended_via_gui)) continue;
        if (xp.parse_bool(wxT("project_suspended_via_gui"), project_suspended_via_gui)) continue;
        if (xp.parse_bool(wxT("coproc_missing"), coproc_missing)) continue;
        if (xp.parse_bool(wxT("gpu_mem_wait"), gpu_mem_wait)) continue;
        if (xp.match_tag(wxT("active_task"))) {
            active_task = true;
            continue;
        }
        if (xp.parse_bool(wxT("supports_graphics"), supports_graphics)) continue;
        if (xp.parse_int(wxT("graphics_mode_acked"), graphics_mode_acked)) continue;
        if (xp.parse_double(wxT("final_cpu_time"), final_cpu_time)) continue;
        if (xp.parse_double(wxT("final_elapsed_time"), final_elapsed_time)) continue;
        if (xp.parse_int(wxT("state"), state)) continue;
        if (xp.parse_int(wxT("scheduler_state"), scheduler_state)) continue;
        if (xp.parse_int(wxT("exit_status"), exit_status)) continue;
        if (xp.parse_int(wxT("signal"), signal)) continue;
        if (xp.parse_int(wxT("active_task_state"), active_task_state)) continue;
        if (xp.parse_int(wxT("app_version_num"), app_version_num)) continue;
        if (xp.parse_int(wxT("slot"), slot)) continue;
        if (xp.parse_int(wxT("pid"), pid)) continue;
        if (xp.parse_double(wxT("checkpoint_cpu_time"), checkpoint_cpu_time)) continue;
        if (xp.parse_double(wxT("current_cpu_time"), current_cpu_time)) continue;
        if (xp.parse_double(wxT("elapsed_time"), elapsed_time)) continue;
        if (xp.parse_double(wxT("swap_size"), swap_size)) continue;
        if (xp.parse_double(wxT("working_set_size"), d)) continue;
        if (xp.parse_double(wxT("page_fault_rate"), d)) continue;
        if (xp.parse_double(wxT("working_set_size_smoothed"), working_set_size_smoothed)) continue;
        if (xp.parse_double(wxT("fraction_done"), fraction_done)) continue;
        if (xp.parse_double(wxT("estimated_cpu_time_remaining"), estimated_cpu_time_remaining)) continue;
        if (xp.parse_bool(wxT("too_large"), too_large)) continue;
        if (xp.parse_bool(wxT("needs_shmem"), needs_shmem)) continue;
        if (xp.parse_bool(wxT("edf_scheduled"), edf_scheduled)) continue;
        if (xp.parse_str(wxT("graphics_exec_path"), graphics_exec_path, sizeof(graphics_exec_path))) continue;
        if (xp.parse_str(wxT("slot_path"), slot_path, sizeof(slot_path))) continue;
        if (xp.parse_str(wxT("resources"), resources, sizeof(resources))) continue;
        xp.skip_unexpected(true, wxT("task instance"));
    }
}
