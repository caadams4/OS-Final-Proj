#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
typedef struct Job {
  int time_arrival;
  int job_number;
  int memory_required;
  int devices_required;
  int run_time;
  int priority;
  struct Job *next;
} Job;

typedef struct Request_devices {
  struct Request_devices *next;
  int time_arrival;
  int job_number;
  int devices_requested;
} Request_devices;

typedef struct Release_devices {
  struct Release_devices *next;
  int time_arrival;
  int job_number;
  int devices_released;
} Release_devices;

typedef struct System_status {
  int memory_available;
  int serial_devices_available;
  int time_quantum;
  int number_processes;
  struct Job *whos_on_the_cpu;
  int *process_table[100][6];
} System_status;

typedef struct Event_arrival {
  int time_arrival;  
  int display_status;
  struct Event_arrival *next;
  struct Job *job;
  struct Request_devices *request_devices;
  struct Release_devices *release_devices;
  struct System_status *system_status;
} Event_arrival;


Event_arrival *read_input();

int parse_arrival_time(char *job);

void submit_job(Job *newJob, char *op);

// device request
void device_request(Request_devices *request_devices, char *job);

// release devices
void device_release
(Release_devices *release_devices, char *job);

// configure device
void sys_config(System_status *system_config, char *sys_specs);

// display status 
void display_status();

Event_arrival *add_event_to_end(struct Event_arrival* head);


// --------------------- Fucntion Prototypes for linked_list.c -------------------- //

struct Job *induct_process(struct Job *hold_q_1_head, struct Job *hold_q_2_head, struct Job *job);

struct Job *send_to_h_q_1(struct Job *hold_q_1_head, struct Job *job);

struct Job *send_to_h_q_2(struct Job *hold_q_2_head, struct Job *job);

struct Job *compare_job_lengths(struct Job *incoming_job, struct Job *this_job, struct Job *next_job);

// --------------------- Fucntion Prototypes for internal_events.c -------------------- //


struct Request_devices *send_to_requests(struct Request_devices *request_device_head, struct Request_devices *req);

struct Release_devices *send_to_releases(struct Release_devices *release_device_head, struct Release_devices *req);

struct Job *send_to_ready_q(struct Job *job, struct Job *req,struct System_status *system_status);

struct Job *send_to_complete_q(struct Job *complete_q, struct Job *out_going_job,struct System_status *system_status,int process_table[][6],int resource_table[]);

void resource_allocation(struct System_status *system_status,int process_table[][6],int resource_table[]);

// --------------------- Fucntion Prototypes for system_status.c -------------------- //

void update_resource_table(int memory_update, int devices_update,int resource_table[]);

void print_system_status(struct System_status *system_status);

void print_system_resources(void);

void print_process_table (struct System_status *system_status, int process_table[][6]);

void print_hold_queues(void);

void print_ready_queue(void);

void print_process_on_CPU(void);

void print_wait_queue(void);

// --------------------- Fucntion Prototypes for bankers_algorithm.c -------------------- //

int banker(struct Job *job, struct Request_devices *dev_req, struct Release_devices *dev_rel, struct System_status *sys_status);



// --------------------- Fucntion Prototypes for cpu.c -------------------- //

struct Job *ready_q_to_CPU(struct Job *ready_queue_head, struct System_status *system_status);

struct Job *start_job(struct System_status *system_status, struct Job *ready_q_head, int process_table[][6]);

void finished_job(struct System_status *system_status, struct Job *complete_q_head, int process_table[][6]);

struct Job *context_switch(struct Job *ready_q_head, struct Job *off_going,struct System_status *system_status, int process_table[][6],int resource_table[]);

// --------------------- Fucntion Prototypes for main.c -------------------- //

struct Event_arrival *process_external_event(struct Event_arrival *event_list_head);