#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "read_input.h"


/*
typedef struct Event_arrival {    ***STRUCTS DEFINIED IN: read_inputs.h***

  int time_arrival;

  struct Event_arrival *next;-----------------------------> pointer to next event

  struct Job *job; ----------------------------------\
  struct Request_devices *request_devices;            \_________ Depending on event type, will point to one of these structs. Others will be null. 
  struct Release_devices *release_devices;            /
  struct System_config *system_config; --------------/

} Event_arrival;
*/ 


/*

Write a file to conduct operations on linked list: Add node (sorted), Add node (unsorted), remove node 

*/





int main(void) {
  int finished = 0;
  struct Event_arrival *event_list_head = read_input(); // builds a linked list of event
  
  struct System_config *system_config = event_list_head->system_config;


  while (event_list_head->next != NULL) { // successfully iterates through each event!
    
    if (event_list_head->job) {
      if (event_list_head->job->memory_required > system_config->memory_available) {
        printf("Rejecting job number %i\n\n",event_list_head->job->job_number);
      } else {
        printf("Inducting job number %i\n\n",event_list_head->job->job_number);
      }
    } else if (event_list_head->request_devices) {
      printf("Request %i devices for job %i\n\n",event_list_head->request_devices->devices_requested,event_list_head->request_devices->job_number);
    } else if (event_list_head->release_devices) {
      printf("Release %i devices from job %i\n\n",event_list_head->release_devices->devices_released,event_list_head->release_devices->job_number);
    }


    event_list_head = event_list_head->next;
  }

  
  return 0;
}