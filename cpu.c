#include "prototypes.h"


struct Job *ready_q_to_CPU(struct Job *ready_q_head, struct System_status *system_status) {
    // brings ready queue head on to CPU
    if (ready_q_head == NULL) {
        puts("11123211");
        system_status->whos_on_the_cpu = NULL;
    } else {
        puts("223331112233");
        system_status->whos_on_the_cpu = ready_q_head;

        ready_q_head = ready_q_head->next;
                system_status->whos_on_the_cpu->next = NULL;
    }
    return ready_q_head;
}

struct Job *wait_q_to_CPU(struct Job *wait_q_head, struct System_status *system_status) {
    // brings wait queue head on to CPU
    if (wait_q_head == NULL) {
        system_status->whos_on_the_cpu = NULL;
    } else {
        system_status->whos_on_the_cpu = wait_q_head;
        wait_q_head = wait_q_head->next;
        system_status->whos_on_the_cpu->next = NULL;
    }
    return wait_q_head;
}

struct Job *start_job(struct System_status *system_status, struct Job *ready_q_head, int process_table[][6]){

    system_status->serial_devices_available -= 1;

    ready_q_head = ready_q_to_CPU(ready_q_head,system_status);

    return ready_q_head;
}
