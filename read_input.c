#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_input.h"

int event_list_length = 0;
struct Event_arrival *head;


void read_input() {
  // Read input of input.txt and build tasks and requests
    char op[30];
    // open input file
puts("im ugly33333333333")
    FILE *input = fopen("./input.txt", "r");
    /* Get each op until there are none left */
    while (fgets(op, 30, input)) {
        char opCode = op[0];
puts("im ugly222222222")
        // Build Event_arrival struct
        Event_arrival *newEvent = (Event_arrival*)malloc(sizeof(Event_arrival));
        newEvent->time_arrival = parse_arrival_time(op);
        newEvent->opString = op;        
        if (event_list_length === 0) { 
          head = newEvent; 
          puts("new head!")
        }
        puts("im ugly")
   
        switch (opCode){
          case 'C':
            //sys_config(op); // device_mgmt.c
            break;
          case 'A':;  
            puts("pelase");
            submit_job(op); // submit_q.c
            //Job * job = submit_job(op); // submit_q.c
            //newEvent->job = job;
//TODO!!!!            add_2_event_list(newEvent);
            break;
          case 'Q':;
            //Request_devices * req_devices = device_request(op); // device_mgmt.c 
//TODO!!!!            add_2_event_list(newEvent);
            break;
          case 'L':;
            //Release_devices * rel_devices = release_device(op); // device_mgmt.c
//TODO!!!!            add_2_event_list(newEvent);
            break;
          case 'D':
            puts("Display Status");
            printf("%s\n", op);
            break;
          
        }
        if (op[strlen(op) - 1] != '\n')
            printf("\n");
    }
}



int parse_arrival_time(char *job) {
  Job *newJob = (Job*)malloc(sizeof(Job));
  char *parsed_job = strtok(job, " ");
  parsed_job = strtok(NULL, " ");
  int time_arrival = atoi(parsed_job);
  return time_arrival;  
}

Job *submit_job(char *job) {
  
  puts('1');
  Job *newJob = (Job*)malloc(sizeof(Job));
  puts('2');
  // A   
  char *parsed_job = strtok(job, " ");
  puts('3');
  // int arrival time
  parsed_job = strtok(NULL, " ");
  newJob->time_arrival = atoi(parsed_job);
  puts('4');
  // Job number
  parsed_job = strtok(NULL, " J=");
  newJob->job_number = atoi(parsed_job);
  puts('5');
  // mem_required
  parsed_job = strtok(NULL, " M=");
  newJob->memory_required = atoi(parsed_job);
  
  // devices_req
  parsed_job = strtok(NULL, " S=");
  newJob->devices_required = atoi(parsed_job);
  
  // run_time
  parsed_job = strtok(NULL, " R=");
  newJob->run_time = atoi(parsed_job);
  
  // priority
  parsed_job = strtok(NULL, " P=");
  newJob->priority = atoi(parsed_job);
  
  printf("Job # %i arrives at: %i\nmemory required: %i\ndevices requested: %i\nrun time: %i\npriority: %i\n", newJob->job_number,newJob->time_arrival,newJob->memory_required,newJob->devices_required,newJob->run_time, newJob->priority);

  return newJob;

}


  // request device based on input
Request_devices * device_request(char *device_req) {

  
  Request_devices *request_devices = (Request_devices*)malloc(sizeof(Request_devices));
  
    // Q   
  char *parsed_input = strtok(device_req, " ");
  
    // int arrival time
  parsed_input = strtok(NULL, " ");
  request_devices->time_arrival = atoi(parsed_input);
  
  
    // Job number
  parsed_input = strtok(NULL, " J=");
  request_devices->job_number = atoi(parsed_input);
  
    // Number of devices
  parsed_input = strtok(NULL, " D=");
  request_devices->devices_requested = atoi(parsed_input);

  printf("Job %i requests %i devices!!!\n", request_devices->job_number, request_devices->devices_requested);  

  return request_devices;
}

  // release device based on input
Release_devices * release_device(char *release_req) {

  
  Release_devices *release_devices = (Release_devices*)malloc(sizeof(Release_devices));
  
    // Q   
  char *parsed_input = strtok(release_req, " ");
  
    // int arrival time
  parsed_input = strtok(NULL, " ");
  release_devices->time_arrival = atoi(parsed_input);
  
    // Job number
  parsed_input = strtok(NULL, " J=");
  release_devices->job_number = atoi(parsed_input);
  
    // Number of devices
  parsed_input = strtok(NULL, " D=");
  release_devices->devices_released = atoi(parsed_input);

  printf("Job %i releases %i devices!!!\n", release_devices->job_number, release_devices->devices_released);

  return release_devices;
}

  // configure device based on input
void sys_config(char *sys_specs) {

    // Q   
  char *parsed_job = strtok(sys_specs, " ");
  
    // int arrival time
  parsed_job = strtok(NULL, " ");
  int time_arrival = atoi(parsed_job);
  
    // Memory available
  parsed_job = strtok(NULL, " M=");
  int main_memory = atoi(parsed_job);
  
    // Serial Devices Availalbe
  parsed_job = strtok(NULL, " S=");
  int serial_devices = atoi(parsed_job);
  
    // Time quantum
  parsed_job = strtok(NULL, " Q=");
  int time_quantum = atoi(parsed_job);

  printf("System configured at %i with %i memory, %i serial devices, and %i time quatnum.\n", time_arrival, main_memory, serial_devices, time_quantum); 
}

  // display status based on input 
void display_status() {

  puts("system status HERE!!!!!!!!!!!!!!!!!!");

}

