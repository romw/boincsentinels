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

#ifndef BOINCNATIVETASKINSTANCE_H_
#define BOINCNATIVETASKINSTANCE_H_

class TASKINSTANCE
{
public:
    wxChar name[256];
    wxChar wu_name[256];
    wxChar project_url[256];
    int version_num;
    wxChar plan_class[64];
    double report_deadline;
    double received_time;
    bool ready_to_report;
    bool got_server_ack;
    double final_cpu_time;
    double final_elapsed_time;
    int state;
    int scheduler_state;
    int exit_status;
    int signal;
    bool suspended_via_gui;
    bool project_suspended_via_gui;
    bool coproc_missing;
    bool gpu_mem_wait;

    // the following defined if active
    bool active_task;
    int active_task_state;
    int app_version_num;
    int slot;
    int pid;
    double checkpoint_cpu_time;
    double current_cpu_time;
    double fraction_done;
    double elapsed_time;
    double swap_size;
    double working_set_size_smoothed;
    double estimated_cpu_time_remaining;
    // actually, estimated elapsed time remaining
    bool supports_graphics;
    int graphics_mode_acked;
    bool too_large;
    bool needs_shmem;
    bool edf_scheduled;
    wxChar graphics_exec_path[512];
    wxChar slot_path[512];
    // only present if graphics_exec_path is
    wxChar resources[256];

    TASKINSTANCE();
    ~TASKINSTANCE();

    void Parse(CBOINCXMLStream& oXML);
    void ParseV2(XML_PARSER& xp);
    void clear();
};

#endif /* BOINCNATIVETASKINSTANCE_H_ */
