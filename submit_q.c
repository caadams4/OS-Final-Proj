#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "submit_q.h"

// struct job i~n~t~e~r~f~a~c~e ... does c even work like that? lol
typedef struct Job {
  int time_arrival;
  int job_number;
  int memory_required;
  int devices_required;
  int run_time;
  char priority;
  struct job *next;
} Job;

//struct Jobs head;


void *submit_job(char *job) {

  Job *newJob = (Job*)malloc(sizeof(Job));

  // A   
  char *parsed_job = strtok(job, " ");
  
  // int arrival time
  parsed_job = strtok(NULL, " ");
  int time_arrival = atoi(parsed_job);
  newJob->time_arrival = time_arrival;

  // Job number
  parsed_job = strtok(NULL, " J=");
  int job_number = atoi(parsed_job);
  newJob->job_number = job_number;

  // mem_required
  parsed_job = strtok(NULL, " M=");
  int memory_required = atoi(parsed_job);
  newJob->memory_required = memory_required;
  
  // devices_req
  parsed_job = strtok(NULL, " S=");
  int devices_required = atoi(parsed_job);
  newJob->devices_required = devices_required;
  
  // run_time
  parsed_job = strtok(NULL, " R=");
  int run_time = atoi(parsed_job);
  newJob->run_time = run_time;
  
  // priority
  parsed_job = strtok(NULL, " P=");
  int priority = atoi(parsed_job);
  newJob->priority = priority;
  
  printf("Job # %i arrives at: %i\nmemory required: %i\ndevices requested: %i\nrun time: %i\npriority: %i\n", newJob->job_number,newJob->time_arrival,newJob->memory_required,newJob->devices_required,newJob->run_time, newJob->priority);

  

}