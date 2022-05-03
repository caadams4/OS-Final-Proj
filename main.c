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

  printf("Time quantum = %i\n",event_list_head->system_config->time_quantum);
  printf("Memory available = %i\n",event_list_head->system_config->memory_available);
  printf("Serial devices available = %i\n",event_list_head->system_config->serial_devices_available);
  
  return 0;
}