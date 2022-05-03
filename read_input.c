#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_input.h"

int event_list_length = 0;
struct Event_arrival *head;


Event_arrival *read_input() {
  // Read input of input.txt and build tasks and requests
    char op[30];
    char opCopy[30];
    FILE *input = fopen("./input.txt", "r");
    /* Get each op-line until there arerm none left */
    while (fgets(op, 30, input)) {
      
        strcpy(opCopy,op);
        char opCode = op[0];
        // Build Event_arrival struct
        Event_arrival *newEvent = (Event_arrival*)malloc(sizeof(Event_arrival));
        newEvent->time_arrival = parse_arrival_time(op);
        
        if (event_list_length == 0) { 
          head = newEvent; 
          //printf("head -> %i",head->time_arrival);
        }
      
        event_list_length++;
      
        switch (opCode){
          
          case 'C':;
            System_config *system_config = (System_config*)malloc(sizeof(System_config));
            newEvent->system_config = system_config;
            sys_config(system_config, opCopy); // device_mgmt.c
            break;
          
          case 'A':; 
            Job *newJob = (Job*)malloc(sizeof(Job));
            newEvent->job = newJob;
            submit_job(newJob,opCopy);
            //printf("newEvent->job->priority = %i",newEvent->job->priority);
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
            display_status();
            break;
          
        }
        if (op[strlen(op) - 1] != '\n')
            printf("\n");
    }

  return head;
}


int parse_arrival_time(char *job) {
  Job *newJob = (Job*)malloc(sizeof(Job));
  char *parsed_job = strtok(job, " ");
  parsed_job = strtok(NULL, " ");
  int time_arrival = atoi(parsed_job);
  return time_arrival;  
}


void submit_job(Job *newJob, char *job) {
  
  char *parsed_job = strtok(job, " ");
  
  parsed_job = strtok(NULL, " "); // int arrival time
  int time_arrival = atoi(parsed_job);
  newJob->time_arrival = time_arrival;
  
  parsed_job = strtok(NULL, " J="); // Job number
  int job_number = atoi(parsed_job);
  newJob->job_number = job_number;
  
  parsed_job = strtok(NULL, " M="); // mem_required
  int memory_required = atoi(parsed_job);
  newJob->memory_required = memory_required;
  
  parsed_job = strtok(NULL, " S="); // devices_req
  int devices_required = atoi(parsed_job);
  newJob->devices_required = devices_required;
  
  parsed_job = strtok(NULL, " R="); // run_time
  int run_time = atoi(parsed_job);
  newJob->run_time = run_time;
  
  parsed_job = strtok(NULL, " P="); // priority
  int priority = atoi(parsed_job);
  newJob->priority = atoi(parsed_job);
}

  // request device based on input
void device_request(Request_devices *request_devices, char *job) {
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
  char *parsed_job = strtok(sys_specs, " ");
  
  parsed_job = strtok(NULL, " "); // int arrival time
  int time_arrival = atoi(parsed_job);
  system_config->time_arrival;
    
  parsed_job = strtok(NULL, " M="); // Memory available
  int main_memory = atoi(parsed_job);
  system_config->memory_available;
  
  parsed_job = strtok(NULL, " S="); // Serial Devices Availalbe
  int serial_devices = atoi(parsed_job);
  system_config->serial_devices_available;
  
  parsed_job = strtok(NULL, " Q="); // Time quantum
  int time_quantum = atoi(parsed_job);
  system_config->time_quantum;
}

  // display status based on input 
void display_status() {

  puts("system status HERE!!!!!!!!!!!!!!!!!!");

}

