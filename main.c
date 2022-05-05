#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "read_input.h" // ** all functions and structs protyped in read_input.h



/*
typedef struct Event_arrival {    

  int time_arrival;

  struct Event_arrival *next;-----------------------------> pointer to next event
      
                    ------------------------------ \
  struct Job *job;                                  \
  struct Request_devices *request_devices;           \_________ Depending on event type, will point to one of these structs. Others will be null. 
  struct Release_devices *release_devices;           /
  struct System_config *system_config;              /
                    -------------------------------/
} Event_arrival;
*/ 



int main(void) {
  int finished = 0;
  struct Event_arrival *event_list_head = read_input(); // builds a linked list of event
  struct Job *hold_q_1_head = NULL;
  struct Job *hold_q_2_head = NULL;

  struct System_config *system_config = event_list_head->system_config; // creates a struct system config


  while (event_list_head->next != NULL) { // iterates through each event!
    
    if (event_list_head->job) {

      if (event_list_head->job->memory_required > system_config->memory_available) {
        printf("Rejecting job number %p\n\n",event_list_head->job); // reject event -- requires too much memory

      } else {
        printf("Inducting job with priority %i\n\n",event_list_head->job->priority);

        if (event_list_head->job->priority == 1) {
          hold_q_1_head = send_to_h_q_1(hold_q_1_head, event_list_head->job); // add job to hold queue 1 ( defined in linked_list.c )
        } else {
          hold_q_2_head = send_to_h_q_2(hold_q_2_head, event_list_head->job); // add job to hold queue 2 ( defined in linked_list.c )
        }
      }

    } else if (event_list_head->request_devices) {  // TODO Device request
      printf("Request %i devices for job %i\n\n",event_list_head->request_devices->devices_requested,event_list_head->request_devices->job_number);

    } else if (event_list_head->release_devices) {  // TODO Device release
      printf("Release %i devices from job %i\n\n",event_list_head->release_devices->devices_released,event_list_head->release_devices->job_number);
    }

    event_list_head = event_list_head->next;  // iterator changes to next evet for while loop
  }


  while (hold_q_2_head != NULL) {

    printf("FIFO Queue (hold Q 2) Runtime: %i - Job No. %i\n",hold_q_2_head->run_time,hold_q_2_head->job_number);
    hold_q_2_head = hold_q_2_head->next;  // iterates through entire hold queue 2. sorted
                                          // fifo. head was first in. last is last out
  }

  puts("\n");
  
  while (hold_q_1_head != NULL) {

    printf("SJF Queue (hold Q 1) Runtime: %i - Job No. %i\n",hold_q_1_head->run_time,hold_q_1_head->job_number);
    hold_q_1_head = hold_q_1_head->next;  // iterates through entire hold queue 2. sorted
                                          // sjf. head is shortest job, tail is longest
  }

  return 0;
}

