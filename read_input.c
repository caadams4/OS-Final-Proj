#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_input.h"

int event_list_length = 0;

Event_arrival *read_input() {
  // Read input of input.txt and build tasks and requests
  // Will return pointer to the first event (head)
    struct Event_arrival* head = NULL;
    char op[30];
    char opCopy[30];
    FILE *input = fopen("./input.txt", "r");

    /* Get each op-line until there arerm none left */
  
    while (fgets(op, 30, input)) { // iterates through each line of input
      
      strcpy(opCopy,op);
      char opCode = op[0];
        
      Event_arrival *newEvent = add_event_to_end(head); 
        
      if (event_list_length == 0){  // if no events, make this event the head the head
        head = newEvent;
      }       
       
      newEvent->time_arrival = parse_arrival_time(op);
      newEvent->next = NULL;
      newEvent->job = NULL;
      newEvent->request_devices = NULL;
      newEvent->release_devices = NULL;
      newEvent->system_config = NULL;
      
      event_list_length++;
      
      switch (opCode){  // calls to configure event based on opCode from input
          
        case 'C':;
          System_config *system_config = (System_config*)malloc(sizeof(System_config));
          newEvent->system_config = system_config;
          sys_config(system_config, opCopy); 
          break;          
        case 'A':; 
          Job *newJob = (Job*)malloc(sizeof(Job));
          newEvent->job = newJob;
          submit_job(newJob,opCopy);
          break;
          
        case 'Q':;
          Request_devices *request_devices = (Request_devices*)malloc(sizeof(Request_devices));
          device_request(request_devices, opCopy);
          newEvent->request_devices = request_devices;
          break;
          
        case 'L':;
          Release_devices *release_devices = (Release_devices*)malloc(sizeof(Release_devices)); 
          device_release(release_devices, opCopy);
          newEvent->release_devices = release_devices;
          break;
              
        case 'D':;

          break;
      }
      
  }

  return head;
}


int parse_arrival_time(char *job) {
  // parses arrival time for each event. This is to know when to induct the event in the driving code

  Job *newJob = (Job*)malloc(sizeof(Job));
  char *parsed_job = strtok(job, " ");
  parsed_job = strtok(NULL, " ");
  int time_arrival = atoi(parsed_job);
  return time_arrival;  
}


void submit_job(Job *newJob, char *job) {
  // configures job 

  char *parsed_job = strtok(job, " ");
  
  parsed_job = strtok(NULL, " "); // int arrival time
  newJob->time_arrival = atoi(parsed_job);
  
  parsed_job = strtok(NULL, " J="); // Job number
  newJob->job_number = atoi(parsed_job);
  
  parsed_job = strtok(NULL, " M="); // mem_required
  newJob->memory_required = atoi(parsed_job);
  
  parsed_job = strtok(NULL, " S="); // devices_req
  newJob->devices_required = atoi(parsed_job);

  parsed_job = strtok(NULL, " R="); // run_time
  newJob->run_time = atoi(parsed_job);
  
  parsed_job = strtok(NULL, " P="); // priority
  newJob->priority = atoi(parsed_job);
}



  // request device based on input
void device_request(Request_devices *request_devices, char *job) {
  // configures request devices event

  char *parsed_input = strtok(job, " ");
    
  parsed_input = strtok(NULL, " "); // int arrival time
  request_devices->time_arrival = atoi(parsed_input);
    
  parsed_input = strtok(NULL, " J="); // Job number
  request_devices->job_number = atoi(parsed_input);
    
  parsed_input = strtok(NULL, " D="); // Number of devices
  request_devices->devices_requested = atoi(parsed_input);

}

  // release device based on input
void device_release(Release_devices *release_devices, char *job) {
  // configures release devices event

  char *parsed_input = strtok(job, " ");
    
  parsed_input = strtok(NULL, " "); // int arrival time
  release_devices->time_arrival = atoi(parsed_input);
    
  parsed_input = strtok(NULL, " J="); // Job number
  release_devices->job_number = atoi(parsed_input);
    
  parsed_input = strtok(NULL, " D="); // Number of devices
  release_devices->devices_released = atoi(parsed_input);
}

  // configure device based on input
void sys_config(System_config *system_config, char *sys_specs) {
  // configures system_config struct with mem, devices, time quantum

  printf("%s",sys_specs);
  char *parsed_job = strtok(sys_specs, " ");
  
  parsed_job = strtok(NULL, " "); // int arrival time
  system_config->time_arrival = atoi(parsed_job);
    
  parsed_job = strtok(NULL, " M="); // Memory available
  system_config->memory_available = atoi(parsed_job);
  
  parsed_job = strtok(NULL, " S="); // Serial Devices Availalbe
  system_config->serial_devices_available = atoi(parsed_job);
  
  parsed_job = strtok(NULL, " Q="); // Time quantum
  system_config->time_quantum = atoi(parsed_job);
}

  // display status based on input 
void display_status() {

  puts("system status HERE!!!!!!!!!!!!!!!!!!");

}

Event_arrival *add_event_to_end(struct Event_arrival* head) {
    // takes in pointer to the head of the linked list
    // returns pointer to the added newEvent
    Event_arrival *newEvent = (struct Event_arrival*)malloc(sizeof(struct Event_arrival)); // malloc new struct

    struct Event_arrival *last = head; 

    if (head == NULL) {
       head = newEvent;
       return newEvent;
    }
  
    while (last->next != NULL) { // iterates to the last element and appends the newEvent to the linked list
        last = last->next;       // of events
    }

    last->next = newEvent;
    return newEvent;  
}