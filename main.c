#include "prototypes.h" // ** all functions and structs protyped in protopytes.h

#define PROC_TABLE_SIZE 100

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

               __RESOURCE TABLE___
  index       |   [0]      [1]    |
  resource    |   mem    devices  |
  config      |   200      12     |
              |___________________|

               _____MAX TABLE_____
  index       |   [0]     [1]     |
  resource    |   mem   devices   |
  example     |   20      8       |
  example     |   30     10       |
              |___________________|
*/

int main(void) {
  int proc_table[PROC_TABLE_SIZE][6] = {{0,0,0,0,0,0}}; // initialize tables for bankers alg
  int resource_table[2] = {0,0}; // {mem,devs}
  int max_table[PROC_TABLE_SIZE][2] = {0,0}; // {mem,devs}

  int process_on_the_cpu = 0;
  int clock_to_seconds = 0, time_ticker;
  int quantum_interupt_system_baseline = 0, max_memory, max_devices;
  struct Event_arrival *event_list_head = read_input(); // builds a linked list of event

  struct Job *hold_q_1_head = NULL; // create queue pointers
  struct Job *hold_q_2_head = NULL;
  struct Job *ready_q_head = NULL;
  struct Job *wait_q = NULL;
  struct Job *complete_q = NULL;
  struct Request_devices *request_device_head = NULL;
  struct Release_devices *release_device_head = NULL;

  struct System_status *system_status = event_list_head->system_status; // creates a struct system config
  max_devices = system_status->serial_devices_available; // config max table
  max_memory = system_status->memory_available;
  resource_table[0] = max_memory;
  resource_table[1] = max_devices;

  quantum_interupt_system_baseline = system_status->time_quantum; // set system quantum interupt

  int completed_jobs = 0;
  int time_interval;

  while (event_list_head != NULL) { // iterates through each event!

    time_ticker = clock()%10000;
    time_interval = 0;
    if (time_ticker == 0) {
      time_interval = 1;

      if (system_status->whos_on_the_cpu != NULL) {
        system_status->time_quantum -= 1; // tick down the quantum
        if (proc_table[system_status->whos_on_the_cpu->job_number][1] > 0) proc_table[system_status->whos_on_the_cpu->job_number][1] -= 1;  // tick down the runtime
      }
      clock_to_seconds++;

      if (system_status->whos_on_the_cpu != NULL){ // executes code block if there is a process mounted on CPU

        if (system_status->whos_on_the_cpu && proc_table[system_status->whos_on_the_cpu->job_number][1] == 0) { // process finished, unmount
          proc_table[system_status->whos_on_the_cpu->job_number][5] = clock_to_seconds;
          resource_table[0] += proc_table[system_status->whos_on_the_cpu->job_number][2]; // reallocate resources
          completed_jobs += 1;
          complete_q = send_to_complete_q(complete_q, system_status->whos_on_the_cpu, system_status,proc_table,resource_table); // send job to compelte queue

          
          if (wait_q) { // check wait queue before ready
            wait_q = ready_q_to_CPU(wait_q,system_status); // mount wait queue head on to CPU
            system_status->time_quantum = quantum_interupt_system_baseline;
          } else if (ready_q_head) { 
            //bankers(system_status->number_processes, ready_q_head,max_table,proc_table,resource_table);
            ready_q_head = ready_q_to_CPU(ready_q_head,system_status); // mount ready queue head on to CPU
            system_status->time_quantum = quantum_interupt_system_baseline;
          } else {
            system_status->whos_on_the_cpu = NULL; // no processes to mount
          }
          if (hold_q_1_head) { // check hold queues for memory space
            system_status->number_processes+=1;
            int mem = hold_q_1_head->memory_required;
            if (mem < resource_table[0]) {
              ready_q_head = send_to_ready_q(ready_q_head, hold_q_1_head, system_status); // process moving into ready queue, add to process table
              proc_table[hold_q_1_head->job_number][0] = hold_q_1_head->job_number;
              proc_table[hold_q_1_head->job_number][1] = hold_q_1_head->run_time;
              proc_table[hold_q_1_head->job_number][2] = hold_q_1_head->memory_required;
              proc_table[hold_q_1_head->job_number][3] = 1;
              proc_table[hold_q_1_head->job_number][5] = 0;

              max_table[hold_q_1_head->job_number][0] = hold_q_1_head->memory_required; // configure max table for incoming process
              max_table[hold_q_1_head->job_number][1] = hold_q_1_head->devices_required;

              resource_table[0] -= proc_table[hold_q_1_head->job_number][2]; // allocate memory

              hold_q_1_head = hold_q_1_head->next;
            }
          } 
          if (hold_q_2_head) {
            system_status->number_processes+=1;
            int mem = hold_q_2_head->memory_required;
            if (mem < resource_table[0]) {
              ready_q_head = send_to_ready_q(ready_q_head, hold_q_2_head, system_status); // process moving into ready queue, add to process table
              proc_table[hold_q_2_head->job_number][0] = hold_q_2_head->job_number;
              proc_table[hold_q_2_head->job_number][1] = hold_q_2_head->run_time;
              proc_table[hold_q_2_head->job_number][2] = hold_q_2_head->memory_required;
              proc_table[hold_q_2_head->job_number][3] = 1;
              proc_table[hold_q_2_head->job_number][5] = 0;

              max_table[hold_q_2_head->job_number][0] = hold_q_2_head->memory_required; // configure max table for incoming process
              max_table[hold_q_2_head->job_number][1] = hold_q_2_head->devices_required;

              resource_table[0] -= proc_table[hold_q_2_head->job_number][2]; // allocate memory

              hold_q_2_head = hold_q_2_head->next;
            } 
            
          }
        } else if (system_status->time_quantum == 0) { // Perform context switch, time quatum is up
          ready_q_head = context_switch(ready_q_head, system_status->whos_on_the_cpu,system_status, proc_table,resource_table);
        }     
      }          
      if (wait_q) { // induct from wait queue 
        wait_q = ready_q_to_CPU(wait_q,system_status);
        system_status->time_quantum = quantum_interupt_system_baseline;
      }
      if (system_status->time_quantum == 0) system_status->time_quantum = quantum_interupt_system_baseline;

      if (clock_to_seconds == event_list_head->time_arrival) {
        if (event_list_head->job) {
          struct Job *job = event_list_head->job;
          proc_table[job->job_number][4] = clock_to_seconds;
          //bankers(system_status->number_processes, ready_q_head,max_table,proc_table,resource_table);
          if (job->memory_required > max_memory || job->devices_required > max_devices) {
            printf("Rejecting job number %i\n\n",job->job_number); // reject event -- requires too much memory
          } else {

            if (job->memory_required < resource_table[0]) {
              proc_table[job->job_number][0] = job->job_number;// process moving into ready queue, add to process table
              proc_table[job->job_number][1] = job->run_time;
              proc_table[job->job_number][2] = job->memory_required;
              proc_table[job->job_number][3] = 1;
              proc_table[job->job_number][5] = 0;

              max_table[job->job_number][0] = job->memory_required;// configure max table for incoming process
              max_table[job->job_number][1] = job->devices_required;

              ready_q_head = send_to_ready_q(ready_q_head,job,system_status);
              resource_table[0] -= proc_table[job->job_number][2]; // allocate memory
              system_status->number_processes+=1;

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
          struct Request_devices *tmp_request_device_head = request_device_head;
          while (tmp_request_device_head != NULL) {
            tmp_request_device_head = tmp_request_device_head->next;
          }
        } else if (event_list_head->release_devices) {  
          release_device_head = send_to_releases(release_device_head, event_list_head->release_devices);
        } else if (event_list_head->display_status == 1) {
          print_system_status(completed_jobs, system_status,clock_to_seconds,hold_q_1_head,hold_q_2_head,ready_q_head,resource_table,proc_table,wait_q);
        }

        if (process_on_the_cpu == 0 && ready_q_head != NULL) { // if no process on CPU, bring process from ready queue on to CPU
          // add bankers alg here, call start_job from there
          ready_q_head = start_job(system_status, ready_q_head, proc_table); // mount job on cpu if no job mounted and somthing is waiting in ready q
          process_on_the_cpu = 1;
        }

      event_list_head = event_list_head->next;  // iterator changes to next evet for while loop
      }
          
    }

    if (system_status->whos_on_the_cpu && request_device_head) {// check for and process request
      if (request_device_head->job_number == system_status->whos_on_the_cpu->job_number) { // check request head for a req matching job on CPU
        wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
        max_table[system_status->whos_on_the_cpu->job_number][1] = request_device_head->devices_requested;
        system_status->whos_on_the_cpu = NULL;
        request_device_head = request_device_head->next;
        struct Request_devices *tmp_request_device_head = request_device_head;
      } else {
        if (request_device_head->next) {
          struct Request_devices *tmp_request_device_head = request_device_head;
          struct Request_devices *tmp2_request_device_head = tmp_request_device_head->next;
          while (tmp2_request_device_head != NULL) { // check the rest of request list for a req matching job on CPU
            if (tmp2_request_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
              wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
              max_table[system_status->whos_on_the_cpu->job_number][1] = tmp2_request_device_head->devices_requested;
              tmp_request_device_head->next = tmp2_request_device_head->next;
              tmp2_request_device_head = NULL;
            } else {
              tmp_request_device_head = tmp2_request_device_head;
              tmp2_request_device_head = tmp2_request_device_head->next;
          }
        }
      }
    }
  }  
    if (system_status->whos_on_the_cpu && release_device_head) { // check for and process release
      if (release_device_head->job_number == system_status->whos_on_the_cpu->job_number) { // check release head for a req matching job on CPU
        max_table[system_status->whos_on_the_cpu->job_number][1] -= release_device_head->devices_released;
        release_device_head = release_device_head->next;
      } else {
        struct Release_devices *tmp_release_device_head = release_device_head;
        if (release_device_head->next) {
        struct Release_devices *tmp2_release_device_head = tmp_release_device_head->next;
        while (tmp2_release_device_head != NULL) { // check the rest of release list for a req matching job on CPU
          if (tmp2_release_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
            max_table[system_status->whos_on_the_cpu->job_number][1] -= release_device_head->devices_released;
            tmp_release_device_head->next = tmp2_release_device_head->next;
          } else {
            tmp_release_device_head = tmp2_release_device_head;
            tmp2_release_device_head = tmp2_release_device_head->next;
          }
        }
      }
    }
  }
  }
  return 0;
}

sssssssssssssssssssssss