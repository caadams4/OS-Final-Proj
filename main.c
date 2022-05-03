#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "read_input.h"


/*
typedef struct Event_arrival {
  int time_arrival;
  struct Event_arrival *next;
  struct Job *job;
  struct Request_devices *request_devices;
  struct Release_devices *release_devices;
  struct System_config *system_config;
} Event_arrival;

typedef struct System_config {
  int time_arrival;
  int memory_available;
  int serial_devices_available;
  int time_quantum;
} System_config;
*/


int start_time = 0;

  // ^ this is the head of the event-arrival-linked-list 





int main(void) {
  int finished = 0;
  struct Event_arrival *event_list_head = read_input(); 

  printf("Time quantum = %i\n",event_list_head->system_config->time_quantum);
  printf("Memory available = %i\n",event_list_head->system_config->memory_available);
  printf("Serial devices available = %i\n",event_list_head->system_config->serial_devices_available);
  
  return 0;
}