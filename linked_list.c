#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_input.h"


// add a node

struct Job *send_to_h_q_1(struct Job *hold_q_1_head, struct Job *job) {
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

struct Job *send_to_h_q_2(struct Job *hold_q_2_head, struct Job *job) {
    // SJF
    if (hold_q_2_head == NULL) {
        hold_q_2_head = job;
        printf("HQ2 head: %p\n\n",hold_q_2_head);
    } else {
        struct Job *tmp_hold_q_2_head = hold_q_2_head;
        while (tmp_hold_q_2_head->next != NULL) {
            tmp_hold_q_2_head = hold_q_2_head->next;
        }
        tmp_hold_q_2_head->next = job; // add Job to end of the Hold Queue 2 list
    }
    return hold_q_2_head;
}
