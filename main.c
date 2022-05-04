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


int main(void) {
  int finished = 0;
  struct Event_arrival *event_list_head = read_input(); // builds a linked list of event

  while (event_list_head->next != NULL) { // successfully iterates through each event!
    printf("Time arrival = %i\n",event_list_head->time_arrival);
    event_list_head = event_list_head->next;
  }

  
  return 0;
}