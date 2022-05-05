#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_input.h"


// add a node

struct Job *send_to_h_q_1(struct Job *hold_q_1_head, struct Job *job) {
    // SJF
    puts("12");
    struct Job *tmp_hold_q_1_head = hold_q_1_head;

    if (hold_q_1_head == NULL) {
        hold_q_1_head = job;
    } else if (hold_q_1_head->next == NULL) {
        hold_q_1_head->next = job;
    } else {
        while (hold_q_1_head->next != NULL) {    //hold_q_1_head->next removed
            
            // TODO insert HQ1 Job SJF sorted
            tmp_hold_q_1_head = compare_job_lengths(hold_q_1_head,hold_q_1_head->next,job);
            hold_q_1_head = hold_q_1_head->next;
        }
    }
}

struct Job *send_to_h_q_2(struct Job *hold_q_2_head, struct Job *job) {
    // SJF
    puts("30");
    if (hold_q_2_head == NULL) {
        puts("33");
        hold_q_2_head = job;
        printf("HQ2 head: %p\n\n",hold_q_2_head);
    } else {
        puts("37");
        struct Job *tmp_hold_q_2_head = hold_q_2_head;
        while (tmp_hold_q_2_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_hold_q_2_head = hold_q_2_head->next;
        }
        tmp_hold_q_2_head->next = job; // add Job to end of the Hold Queue 2 list
    }
    puts("42");
    return hold_q_2_head;
}

struct Job *compare_job_lengths(struct Job *incoming_job, struct Job *this_job, struct Job *next_job) {
    /* Return hold_g_2_head pointer
    
    ----> [this job] -----------> [next job] -------->
              
              >=    [incoming job]     <=

    */
    puts("53");

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
