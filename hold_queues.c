#include "prototypes.h"



// add a node

struct Job *send_to_h_q_1(struct Job *hold_q_1_head, struct Job *job) {
    // SJF
    struct Job *tmp_hold_q_1_head = hold_q_1_head;
    struct Job *tmp2_hold_q_1_head;
    

    if (hold_q_1_head == NULL) {
        hold_q_1_head = job;
        tmp_hold_q_1_head = hold_q_1_head;
    } else if (hold_q_1_head->next == NULL) {
        if (hold_q_1_head->run_time <= job->run_time){ 
            tmp_hold_q_1_head->next = job;
        } else {
            tmp_hold_q_1_head = job;
            tmp_hold_q_1_head->next = hold_q_1_head;
        }
    } else {
        while (hold_q_1_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_hold_q_1_head = compare_job_lengths(job,hold_q_1_head,hold_q_1_head->next);
            if (tmp2_hold_q_1_head != tmp_hold_q_1_head) {
                break;
            }
            hold_q_1_head = hold_q_1_head->next;
        }
    }

    return tmp_hold_q_1_head;
}

struct Job *send_to_h_q_2(struct Job *hold_q_2_head, struct Job *job) {
    // SJF
    if (hold_q_2_head == NULL) {
        hold_q_2_head = job;
    } else {
        struct Job *tmp_hold_q_2_head = hold_q_2_head;
        while (tmp_hold_q_2_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_hold_q_2_head = hold_q_2_head->next;
        }
        tmp_hold_q_2_head->next = job; // add Job to end of the Hold Queue 2 list
    }
    return hold_q_2_head;
}

struct Job *compare_job_lengths(struct Job *incoming_job, struct Job *this_job, struct Job *next_job) {
    /* Return hold_g_2_head pointer
    
    ----> [this job] -----------> [next job] -------->
              
              >=    [incoming job]     <=

    */

    struct Job *hold_q_2_head = this_job;

    if (this_job->run_time <= incoming_job->run_time) {
        if (next_job->run_time <= incoming_job->run_time) {
            // keep moving right 
            if (next_job->next != NULL) { // recursive call with this/next jobs to the right. 
                this_job = this_job->next;
                next_job = next_job->next;
                hold_q_2_head = compare_job_lengths(incoming_job, this_job, next_job);
            } else { // add it on to the end of the queue
                next_job->next = incoming_job;
            }
        } else {
            // insert here, between this and next 
            this_job->next = incoming_job;
            incoming_job->next = next_job;
        } 
    } else {
            // insert as head of the list
            incoming_job->next = this_job;
            hold_q_2_head = incoming_job;
    }
    
    return hold_q_2_head;
}
