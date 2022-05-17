#include "prototypes.h"

struct Job *send_to_wait_1(struct Job *wait_q, struct Job *job) {
    // send job to wait queue
    if (wait_q == NULL) {
        wait_q = job;
        wait_q->next = NULL;
    } else {
        struct Job *tmp_wait_q = wait_q;
        while (tmp_wait_q->next != NULL) {    //wait_q->next removed
 
            tmp_wait_q = wait_q->next;
        }
        tmp_wait_q->next = job; // add Job to end of the Hold Queue 2 list
        job->next = NULL;
    }
    return wait_q;
}