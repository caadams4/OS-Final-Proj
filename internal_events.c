#include "prototypes.h"


struct Request_devices *send_to_requests(struct Request_devices *request_device_head, struct Request_devices *req) {
    // SJF
    if (request_device_head == NULL) {
        request_device_head = req;
    } else {
        struct Request_devices *tmp_request_device_head = request_device_head;
        while (tmp_request_device_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_request_device_head = tmp_request_device_head->next;
        }
        tmp_request_device_head->next = req; // add req to end of the Hold Queue 2 list
    }
    return request_device_head;
}

struct Release_devices *send_to_releases(struct Release_devices *release_device_head, struct Release_devices *req) {
    // SJF
    if (release_device_head == NULL) {
        release_device_head = req;
    } else {
        struct Release_devices *tmp_release_device_head = release_device_head;
        while (tmp_release_device_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_release_device_head = tmp_release_device_head->next;
        }
        tmp_release_device_head->next = req; // add req to end of the Hold Queue 2 list
    }
    return release_device_head;
}


struct Job *send_to_ready_q(struct Job *ready_q_head, struct Job *incoming_job,struct System_status *system_status) {
    // SJF
    if (ready_q_head == NULL) {
        ready_q_head = incoming_job;
    } else {
        struct Job *tmp_ready_q_head = ready_q_head;
        while (tmp_ready_q_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_ready_q_head = tmp_ready_q_head->next;
        }
        tmp_ready_q_head->next = incoming_job; // add req to end of the ready q
    }
    system_status->memory_available -= ready_q_head->memory_required;
    return ready_q_head;
}

struct Job *context_switch(struct Job *ready_q_head, struct Job *off_going_from_CPU,struct System_status *system_status, int process_table[][6],int resource_table[]) {


        if (ready_q_head == NULL && process_table[system_status->whos_on_the_cpu->job_number-1][1] == 0) {
            puts("iz null");
            return NULL;
        } if (ready_q_head == NULL && system_status->whos_on_the_cpu != NULL) {
            return NULL;
        }
        
        system_status->whos_on_the_cpu = ready_q_head;
        system_status->whos_on_the_cpu->next = NULL;
        ready_q_head = ready_q_head->next;

        if (ready_q_head == NULL) { // Ready queue empty with time remaining on off going job. re mount to cpu
            ready_q_head = off_going_from_CPU;
            ready_q_head->next = NULL;
        } else {
            struct Job *tmp_ready_q_head = ready_q_head;
            while (tmp_ready_q_head->next != NULL) {    //sends CPU mounted job to the end of the ready queue
                tmp_ready_q_head = tmp_ready_q_head->next;
            }
            tmp_ready_q_head->next = off_going_from_CPU; // add job to end of the ready q
            off_going_from_CPU->next = NULL;
        }

        system_status->memory_available -= ready_q_head->memory_required;

        if (process_table[system_status->whos_on_the_cpu->job_number-1][0] != system_status->whos_on_the_cpu->job_number) {
            add_to_process_table(system_status, process_table);
        }

        int devices_required_4_next_job = process_table[system_status->whos_on_the_cpu->job_number-1][3];
        update_resource_table(0, devices_required_4_next_job *-1,resource_table); // Take devices away from CPU

    

    return ready_q_head;
}



struct Job *send_to_complete_q(struct Job *complete_q, struct Job *out_going_job,struct System_status *system_status,int process_table[][6],int resource_table[]) {
  
    int devices_back_to_CPU = process_table[system_status->whos_on_the_cpu->job_number-1][3];
    int memory_back_to_CPU =  process_table[system_status->whos_on_the_cpu->job_number-1][2];
    update_resource_table(memory_back_to_CPU, devices_back_to_CPU , resource_table); // Gives devices and memory back to CPU

    if (complete_q == NULL) {
        complete_q = out_going_job;
    } else {
        struct Job *tmp_complete_q = complete_q;
        while (tmp_complete_q->next != NULL) {    
            tmp_complete_q = tmp_complete_q->next;
        }
        tmp_complete_q->next = out_going_job; 
    }
    out_going_job->next = NULL;
    system_status->memory_available += complete_q->memory_required;
    return complete_q;
}

void resource_allocation(struct System_status *system_status,int process_table[][6],int resource_table[]) {

    if (process_table[system_status->whos_on_the_cpu->job_number-1][0] != system_status->whos_on_the_cpu->job_number) {
        add_to_process_table(system_status, process_table);
    }

    int devices_required_4_next_job = process_table[system_status->whos_on_the_cpu->job_number-1][3];
    update_resource_table(0, devices_required_4_next_job *-1,resource_table); // Take devices away from CPU
    
}