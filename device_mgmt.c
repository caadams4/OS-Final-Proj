#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "device_mgmt.h"

// device request
void device_request(char *device_req) {

    // Q   
  char *parsed_job = strtok(device_req, " ");
  
    // int arrival time
  parsed_job = strtok(NULL, " ");
  int time_arrival = atoi(parsed_job);
  
    // Job number
  parsed_job = strtok(NULL, " J=");
  int job_number = atoi(parsed_job);
  
    // Number of devices
  parsed_job = strtok(NULL, " D=");
  int devices_requested = atoi(parsed_job);

  printf("Job %i requests %i devices!!!\n", job_number, devices_requested);  
}


// release devices
void release_device(char *release_req) {

    // Q   
  char *parsed_job = strtok(release_req, " ");
  
    // int arrival time
  parsed_job = strtok(NULL, " ");
  int time_arrival = atoi(parsed_job);
  
    // Job number
  parsed_job = strtok(NULL, " J=");
  int job_number = atoi(parsed_job);
  
    // Number of devices
  parsed_job = strtok(NULL, " D=");
  int devices_released = atoi(parsed_job);

  printf("Job %i releases %i devices!!!\n", job_number, devices_released);
}

// configure device
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

// display status 
void display_status() {

  puts("system status HERE!!!!!!!!!!!!!!!!!!");

}

