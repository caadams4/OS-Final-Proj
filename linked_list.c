#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"



void induct_process(struct Job *hold_q_1_head, struct Job *hold_q_2_head, struct Job *job) {
    if (job->priority == 1) {
        send_to_h_q_1(hold_q_1_head, job);
    } else {
        send_to_h_q_2(hold_q_2_head, job);
    }
}


// add a node

void send_to_h_q_1(struct Job *hold_q_1_head, struct Job *job) {
    // SJF
    if (hold_q_1_head == NULL) {
        hold_q_1_head = job;
    } else {
        while (hold_q_1_head->next != NULL) {
            
            // TODO insert HQ1 Job SJF sorted

            hold_q_1_head = hold_q_1_head->next;
        }
    }
}

void send_to_h_q_2(struct Job *hold_q_2_head, struct Job *job) {
    // SJF
    if (hold_q_2_head == NULL) {
        hold_q_2_head = job;
    } else {
        while (hold_q_2_head->next != NULL) {
            hold_q_2_head = hold_q_2_head->next;
        }
        hold_q_2_head->next = job; // add Job to end of the Hold Queue 2 list
    }
}
