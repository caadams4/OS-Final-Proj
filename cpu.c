#include "prototypes.h"


struct Job *ready_q_to_CPU(struct Job *ready_q_head, struct System_status *system_status) {
    // brings ready queue head on to CPU
    if (ready_q_head == NULL) {
        system_status->whos_on_the_cpu = NULL;
    } else {
        system_status->whos_on_the_cpu = ready_q_head;
        ready_q_head = ready_q_head->next;
        system_status->whos_on_the_cpu->next = NULL;
    }
    return ready_q_head;
}

struct Job *start_job(struct System_status *system_status, struct Job *ready_q_head, int process_table[][6], int start_time){

    system_status->serial_devices_available -= 1;
    system_status->memory_available -= ready_q_head->memory_required;

    process_table[ready_q_head->job_number-1][4] = start_time;
    update_resource_table(0,-1,process_table);

    ready_q_head = ready_q_to_CPU(ready_q_head,system_status);
    add_to_process_table(system_status,process_table);

    printf("whos_on_the_cpu = %i",system_status->whos_on_the_cpu->job_number);
    return ready_q_head;
}

 void finished_job(struct System_status *system_status, struct Job *complete_q_head, int process_table[][6], int finish_time) {

    // release devices and memory 
    system_status->serial_devices_available += 1;
    system_status->memory_available += system_status->whos_on_the_cpu->memory_required;

    // TODO send job to complete function
    update_resource_table(system_status->whos_on_the_cpu->memory_required,1,process_table);

    // update run times/ start/ finish
    process_table[system_status->whos_on_the_cpu->job_number-1][5] = finish_time;
    system_status->whos_on_the_cpu == NULL;

}

struct Job *completed_job(struct Job *ready_q_head, struct Job *off_going_from_CPU,struct System_status *system_status, struct Job *complete_q_head,int *process_table[][6],int resource_table[]) {

    // mount job on CPU 
    
    update_resource_table(0, process_table[system_status->whos_on_the_cpu->job_number-1][3],resource_table); 

    system_status->whos_on_the_cpu = ready_q_head;
    system_status->whos_on_the_cpu->next = NULL;

    ready_q_head = ready_q_head->next;

    if (ready_q_head == NULL) {
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

    int devices_required_4_next_job = process_table[system_status->whos_on_the_cpu->job_number-1][3];
    update_resource_table(0, devices_required_4_next_job *-1,resource_table); // Take devices away from CPU


    return ready_q_head;
}