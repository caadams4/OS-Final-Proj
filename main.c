#include "prototypes.h" // ** all functions and structs protyped in protopytes.h

#define PROC_TABLE_SIZE 100
void print_status(struct Job *hold_q_1_head,struct Job *hold_q_2_head,struct Job *ready_q_head,struct Job *complete_q,struct System_status *system_status);

/*
typedef struct Event_arrival {    

  int time_arrival;
  int display_status;

  struct Event_arrival *next;-----------------------------> pointer to next event
  
                    ------------------------------ \
  struct Job *job;                                  \
  struct Request_devices *request_devices;           \_________ Depending on event type, will point to one of these structs. Others will be null. 
  struct Release_devices *release_devices;           /
  struct System_config *system_config;              /
                    -------------------------------/
} Event_arrival;
*/ 

/*
           _____________________PROCESS TABLE_____________________________
  index   |   [0]     [1]      [2]        [3]        [4]         [5]      |
  data    |   pid   runtime   memory    devices   timestart   timefinish  |
  example |    1      5         3          4          1           6       |
  example |    2      5         3          4          6           11      |
          |_______________________________________________________________|
*/



int main(void) {
  int proc_table[PROC_TABLE_SIZE][6] = {{0,0,0,0,0,0}};
  int resource_table[2] = {0,0}; // {mem,devs}
  int max_table[PROC_TABLE_SIZE][2] = {0,0}; // {mem,devs}
  clock_t start_t, end_t, total_t;
  int process_on_the_cpu = 0;
  int clock_to_seconds = 0, time_ticker;
  int quantum_interupt_system_baseline = 0, max_memory, max_devices;
  struct Event_arrival *event_list_head = read_input(); // builds a linked list of event
  struct Job *hold_q_1_head = NULL;
  struct Job *hold_q_2_head = NULL;
  struct Job *ready_q_head = NULL;
  struct Job *wait_q = NULL;
  struct Job *complete_q = NULL;
  struct Request_devices *request_device_head = NULL;
  struct Release_devices *release_device_head = NULL;
  struct System_status *system_status = event_list_head->system_status; // creates a struct system config
  max_devices = system_status->serial_devices_available;
  max_memory = system_status->memory_available;
  update_resource_table(max_memory,max_devices,resource_table);
  quantum_interupt_system_baseline = system_status->time_quantum;
  int num_jobs = 0;
  int time_interval;
  start_t = clock();
  while (event_list_head != NULL) { // iterates through each event!

    time_ticker = clock()%100000;
    time_interval = 0;
    if (time_ticker == 0) {
      time_interval = 1;
      if (system_status->whos_on_the_cpu != NULL) {
        system_status->time_quantum -= 1;
        if (proc_table[system_status->whos_on_the_cpu->job_number-1][1] > 0) proc_table[system_status->whos_on_the_cpu->job_number-1][1] -= 1;
      }
      clock_to_seconds++;
      printf("%i",clock_to_seconds);
    /* --------- CPU ----------- */

      // TODO job complete 
        // Condition: system_status->run_time == 0
                    // aka job is complete, on to the next one

        // 1. Take job off CPU and place into complete queue
        // 2. Release memory and/or devices
        // 3. Use bankers algorithm to determine next job from ready queue ( using device allocation )
        // 4. Check hold queue 1 and 2 for jobs and put them into the ready queue
      if (system_status->whos_on_the_cpu != NULL){
        if (proc_table[system_status->whos_on_the_cpu->job_number-1][1] == 0) {

          printf("finished job %i\n\n",system_status->whos_on_the_cpu->job_number);
          
          proc_table[system_status->whos_on_the_cpu->job_number-1][5] = clock_to_seconds;
          complete_q = send_to_complete_q(complete_q, system_status->whos_on_the_cpu, system_status,proc_table,resource_table);
          //realease devices

          if (ready_q_head) {
            system_status->memory_available -= ready_q_head->memory_required;
            update_resource_table(0,-1,proc_table);
            ready_q_head = ready_q_to_CPU(ready_q_head,system_status);
            system_status->time_quantum = quantum_interupt_system_baseline;
          } else {
            system_status->whos_on_the_cpu = NULL;
          }

          if (hold_q_1_head) { 
            int mem = hold_q_1_head->memory_required;
            if (mem < resource_table[0]) {
              ready_q_head = send_to_ready_q(ready_q_head, hold_q_1_head, system_status); // process moving into ready queue, add to process table
              proc_table[hold_q_1_head->job_number-1][0] = hold_q_1_head->job_number;
              proc_table[hold_q_1_head->job_number-1][1] = hold_q_1_head->run_time;
              proc_table[hold_q_1_head->job_number-1][2] = hold_q_1_head->memory_required;
              proc_table[hold_q_1_head->job_number-1][3] = 1;
              proc_table[hold_q_1_head->job_number-1][5] = 0;

              max_table[hold_q_1_head->job_number-1][0] = hold_q_1_head->memory_required;
              max_table[hold_q_1_head->job_number-1][1] = hold_q_1_head->devices_required;

              hold_q_1_head = hold_q_1_head->next;
            }
            update_resource_table(mem*-1,0,proc_table);
          } 
          if (hold_q_2_head) {
            int mem = hold_q_2_head->memory_required;
            if (mem < resource_table[0]) {
              ready_q_head = send_to_ready_q(ready_q_head, hold_q_2_head, system_status); // process moving into ready queue, add to process table
              proc_table[hold_q_2_head->job_number-1][0] = hold_q_2_head->job_number;
              proc_table[hold_q_2_head->job_number-1][1] = hold_q_2_head->run_time;
              proc_table[hold_q_2_head->job_number-1][2] = hold_q_2_head->memory_required;
              proc_table[hold_q_2_head->job_number-1][3] = 1;
              proc_table[hold_q_2_head->job_number-1][5] = 0;

              max_table[hold_q_2_head->job_number-1][0] = hold_q_2_head->memory_required;
              max_table[hold_q_2_head->job_number-1][1] = hold_q_2_head->devices_required;

              hold_q_2_head = hold_q_2_head->next;
            } 
            update_resource_table(mem*-1,0,proc_table);
          }
        } else if (system_status->time_quantum == 0) {
          
          ready_q_head = context_switch(ready_q_head, system_status->whos_on_the_cpu,system_status, proc_table,resource_table);
        }     
      }

      if (system_status->time_quantum == 0) system_status->time_quantum = quantum_interupt_system_baseline;

    /* --------- Internal events ----------- */

      // TODO if job is on CPU, check request queue and release queue for internal events

        // Condition: system_status->whos_on_the_cpu != NULL
                    // aka a job is on the cpu

        // Why? device requests and release only occures when the specified job has request pending
        // 1. Check release list for job num of whos on the CPU
        // 2. Check request list for job num of whos on the CPU
        // 3. If found, perform the action

    /* --------- External events ----------- */
      if (clock_to_seconds == event_list_head->time_arrival) {
        if (event_list_head->job) {
          struct Job *job = event_list_head->job;
          system_status->number_processes+=1;
          proc_table[job->job_number-1][4] = clock_to_seconds;
          //banker(job, request_device_head, release_device_head, system_status);
          if (job->memory_required > max_memory || job->devices_required > max_devices) {
            printf("Rejecting job number %i\n\n",job->job_number); // reject event -- requires too much memory
          } else {

            if (job->memory_required < resource_table[0]) {
              num_jobs += 1;
              proc_table[job->job_number-1][0] = job->job_number;
              proc_table[job->job_number-1][1] = job->run_time;
              proc_table[job->job_number-1][2] = job->memory_required;
              proc_table[job->job_number-1][3] = 1;
              proc_table[job->job_number-1][5] = 0;

              max_table[job->job_number-1][0] = job->memory_required;
              max_table[job->job_number-1][1] = job->devices_required;

              ready_q_head = send_to_ready_q(ready_q_head,job,system_status);
              update_resource_table(job->memory_required *-1,0,resource_table); // subtracts required memory from resource pool

            } else {

              if (event_list_head->job->priority == 1) {
                hold_q_1_head = send_to_h_q_1(hold_q_1_head, job); // add job to hold queue 1 ( defined in linked_list.c )
              } else {
                hold_q_2_head = send_to_h_q_2(hold_q_2_head, job); // add job to hold queue 2 ( defined in linked_list.c )
              }
            }
          }
        } else if (event_list_head->request_devices) {  
          request_device_head = send_to_requests(request_device_head, event_list_head->request_devices);
        } else if (event_list_head->release_devices) {  
          release_device_head = send_to_releases(release_device_head, event_list_head->release_devices);
        } else if (event_list_head->display_status == 1) {

          print_process_table(system_status,proc_table);
          //print_system_status(system_status);
          // TODO make the display status pretty
        }

        if (process_on_the_cpu == 0 && ready_q_head != NULL) { // if no process on CPU, bring process from ready queue on to CPU
          // add bankers alg here, call start_job from there
          ready_q_head = start_job(system_status, ready_q_head, proc_table); // should be called from bankers
          process_on_the_cpu = 1;
        }

      event_list_head = event_list_head->next;  // iterator changes to next evet for while loop
      }
    }

    if (system_status->whos_on_the_cpu == NULL && ready_q_head != NULL) system_status->whos_on_the_cpu = ready_q_head;

  }

  print_status(hold_q_1_head,hold_q_2_head,ready_q_head,complete_q,system_status);

  return 0;
}

void print_status(struct Job *hold_q_1_head,struct Job *hold_q_2_head,struct Job *ready_q_head,struct Job *complete_q,struct System_status *system_status) {

  while (hold_q_2_head != NULL) {   // prints Hold queue 2 contents
    printf("FIFO Queue (hold Q 2) Runtime: %i - Job No. %i\n",hold_q_2_head->run_time,hold_q_2_head->job_number);
    hold_q_2_head = hold_q_2_head->next;  // iterates through entire hold queue 2. sorted
  }               
  while (hold_q_1_head != NULL) {   // prints Hold queue 1 contents
    printf("SJF Queue (hold Q 1) Runtime: %i - Job No. %i\n",hold_q_1_head->run_time,hold_q_1_head->job_number);
    hold_q_1_head = hold_q_1_head->next;  // iterates through entire hold queue 2. sorted
  }                 
  while (ready_q_head != NULL){
    printf("Ready queue Runtime: %i - Job No. %i\n",ready_q_head->run_time,ready_q_head->job_number);
    ready_q_head = ready_q_head->next;  // iterates through entire hold queue 2. sorted
  }
    while (complete_q != NULL){
    printf("complete queue: Job No. %i\n",complete_q->job_number);
    complete_q = complete_q->next;  // iterates through entire hold queue 2. sorted
  }

  
}