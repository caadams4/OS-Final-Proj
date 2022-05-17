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
  resource_table[0] = max_memory;
  resource_table[1] = max_devices;
  quantum_interupt_system_baseline = system_status->time_quantum;
  int num_jobs = 0, completed_jobs = 0;
  int time_interval;
  while (event_list_head != NULL) { // iterates through each event!

    time_ticker = clock()%100000;
    time_interval = 0;
    if (time_ticker == 0) {
      time_interval = 1;
      if (system_status->whos_on_the_cpu != NULL) {
        system_status->time_quantum -= 1;
        if (proc_table[system_status->whos_on_the_cpu->job_number][1] > 0) proc_table[system_status->whos_on_the_cpu->job_number][1] -= 1;
      }
      clock_to_seconds++;
      printf("%i\n",clock_to_seconds);

      if (system_status->whos_on_the_cpu != NULL){

        if (system_status->whos_on_the_cpu && proc_table[system_status->whos_on_the_cpu->job_number][1] == 0) { // process finished, unmount
          proc_table[system_status->whos_on_the_cpu->job_number][5] = clock_to_seconds;
          resource_table[0] += proc_table[system_status->whos_on_the_cpu->job_number][2];
          system_status->number_processes-=1;
          completed_jobs += 1;
          complete_q = send_to_complete_q(complete_q, system_status->whos_on_the_cpu, system_status,proc_table,resource_table);

          // check wait queue before ready
          if (wait_q) {
            wait_q = ready_q_to_CPU(wait_q,system_status);
            printf("mounting %i on cpu\nmemory now: %i FROM WAIT QUEUE!!!!!!!!!!\n",system_status->whos_on_the_cpu->job_number,resource_table[0]);
            system_status->time_quantum = quantum_interupt_system_baseline;
          } else if (ready_q_head) { // bankers in ready_q_to_cpu
            //bankers(system_status->number_processes, ready_q_head,max_table,proc_table,resource_table);
            ready_q_head = ready_q_to_CPU(ready_q_head,system_status);
            printf("mounting %i on cpu\nmemory now: %i\n",system_status->whos_on_the_cpu->job_number,resource_table[0]);
            system_status->time_quantum = quantum_interupt_system_baseline;
          } else {
            system_status->whos_on_the_cpu = NULL;
          }

          if (hold_q_1_head) { 
            system_status->number_processes+=1;
            int mem = hold_q_1_head->memory_required;
            if (mem < resource_table[0]) {
              ready_q_head = send_to_ready_q(ready_q_head, hold_q_1_head, system_status); // process moving into ready queue, add to process table
              proc_table[hold_q_1_head->job_number][0] = hold_q_1_head->job_number;
              proc_table[hold_q_1_head->job_number][1] = hold_q_1_head->run_time;
              proc_table[hold_q_1_head->job_number][2] = hold_q_1_head->memory_required;
              proc_table[hold_q_1_head->job_number][3] = 1;
              proc_table[hold_q_1_head->job_number][5] = 0;

              max_table[hold_q_1_head->job_number][0] = hold_q_1_head->memory_required;
              max_table[hold_q_1_head->job_number][1] = hold_q_1_head->devices_required;

              resource_table[0] -= proc_table[hold_q_1_head->job_number][2];

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

              max_table[hold_q_2_head->job_number][0] = hold_q_2_head->memory_required;
              max_table[hold_q_2_head->job_number][1] = hold_q_2_head->devices_required;

              resource_table[0] -= proc_table[hold_q_2_head->job_number][2];

              hold_q_2_head = hold_q_2_head->next;
            } 
            
          }
        } else if (system_status->time_quantum == 0) {
          
          resource_table[0] += proc_table[system_status->whos_on_the_cpu->job_number][2];
          ready_q_head = context_switch(ready_q_head, system_status->whos_on_the_cpu,system_status, proc_table,resource_table);
          resource_table[0] -= proc_table[system_status->whos_on_the_cpu->job_number][2];
        }     
      }          
      if (wait_q) {
        wait_q = ready_q_to_CPU(wait_q,system_status);
        printf("mounting %i on cpu\nmemory now: %i FROM WAIT QUEUE!!!!!!!!!!\n",system_status->whos_on_the_cpu->job_number,resource_table[0]);
        system_status->time_quantum = quantum_interupt_system_baseline;
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
          proc_table[job->job_number][4] = clock_to_seconds;
          bankers(system_status->number_processes, ready_q_head,max_table,proc_table,resource_table);
          if (job->memory_required > max_memory || job->devices_required > max_devices) {
            printf("Rejecting job number %i\n\n",job->job_number); // reject event -- requires too much memory
          } else {

            if (job->memory_required < resource_table[0]) {
              num_jobs += 1;
              proc_table[job->job_number][0] = job->job_number;
              proc_table[job->job_number][1] = job->run_time;
              proc_table[job->job_number][2] = job->memory_required;
              proc_table[job->job_number][3] = 1;
              proc_table[job->job_number][5] = 0;

              max_table[job->job_number][0] = job->memory_required;
              max_table[job->job_number][1] = job->devices_required;

              ready_q_head = send_to_ready_q(ready_q_head,job,system_status);
              resource_table[0] -= proc_table[job->job_number][2];
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
          printf("req_dev_head = %i\n",request_device_head->job_number);
        } else if (event_list_head->release_devices) {  
          release_device_head = send_to_releases(release_device_head, event_list_head->release_devices);
        } else if (event_list_head->display_status == 1) {
          print_system_status(completed_jobs, system_status,clock_to_seconds,hold_q_1_head,hold_q_2_head,ready_q_head,resource_table,proc_table,wait_q);

          // TODO make the display status pretty
        }

        if (process_on_the_cpu == 0 && ready_q_head != NULL) { // if no process on CPU, bring process from ready queue on to CPU
          // add bankers alg here, call start_job from there

          ready_q_head = start_job(system_status, ready_q_head, proc_table); 
          process_on_the_cpu = 1;
        }

      event_list_head = event_list_head->next;  // iterator changes to next evet for while loop
      }
    }

    // check request queue for job on cpu
    if (system_status->whos_on_the_cpu && request_device_head) {
      if (request_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
        // devie alloc ****************************************************8
        max_table[system_status->whos_on_the_cpu->job_number][1] = request_device_head->devices_requested;
        wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
        system_status->whos_on_the_cpu = NULL;
        request_device_head = request_device_head->next;
      } else {
        struct Request_devices *tmp_request_device_head = request_device_head;
        if (request_device_head->next) {
        struct Request_devices *tmp2_request_device_head = tmp_request_device_head->next;
        while (tmp2_request_device_head != NULL) {
          if (tmp2_request_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
            // devie alloc ****************************************************8
            max_table[system_status->whos_on_the_cpu->job_number][1] = tmp2_request_device_head->devices_requested;
            wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
            system_status->whos_on_the_cpu = NULL;
            tmp_request_device_head->next = tmp2_request_device_head->next;
          } else {
            tmp_request_device_head = tmp2_request_device_head;
            tmp2_request_device_head = tmp2_request_device_head->next;
          }
        }
      }
      }
     
    }   

    if (system_status->whos_on_the_cpu && release_device_head) {
      if (release_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
        // devie alloc ****************************************************8
        max_table[system_status->whos_on_the_cpu->job_number][1] -= release_device_head->devices_released;
        wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
        system_status->whos_on_the_cpu = NULL;
        release_device_head = release_device_head->next;
      } else {
        struct Release_devices *tmp_release_device_head = release_device_head;
        if (release_device_head->next) {
        struct Release_devices *tmp2_release_device_head = tmp_release_device_head->next;
        while (tmp2_release_device_head != NULL) {
          if (tmp2_release_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
            // devie alloc ****************************************************8
            max_table[system_status->whos_on_the_cpu->job_number][1] -= release_device_head->devices_released;
            wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
            system_status->whos_on_the_cpu = NULL;
            tmp_release_device_head->next = tmp2_release_device_head->next;
          } else {
            tmp_release_device_head = tmp2_release_device_head;
            tmp2_release_device_head = tmp2_release_device_head->next;
          }
        }
      }
      }
     
    }
    if (system_status->whos_on_the_cpu == NULL && ready_q_head != NULL) system_status->whos_on_the_cpu = ready_q_head;

  }
  return 0;
}


/*
#include "prototypes.h" // ** all functions and structs protyped in protopytes.h

#define PROC_TABLE_SIZE 100


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


/*
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
  resource_table[0] = max_memory;
  resource_table[1] = max_devices;
  quantum_interupt_system_baseline = system_status->time_quantum;
  int num_jobs = 0, completed_jobs = 0;
  int time_interval;
  while (event_list_head != NULL) { // iterates through each event!

    time_ticker = clock()%100000;
    time_interval = 0;
    if (time_ticker == 0) {
      time_interval = 1;
      if (system_status->whos_on_the_cpu != NULL) {
        system_status->time_quantum -= 1;
        if (proc_table[system_status->whos_on_the_cpu->job_number][1] > 0) proc_table[system_status->whos_on_the_cpu->job_number][1] -= 1;
      }
      clock_to_seconds++;
      printf("%i\n",clock_to_seconds);
      if (system_status->whos_on_the_cpu) printf("whos on %i\n",system_status->whos_on_the_cpu->job_number);

      if (system_status->whos_on_the_cpu != NULL){

        if (system_status->whos_on_the_cpu && proc_table[system_status->whos_on_the_cpu->job_number][1] == 0) { // process finished, unmount from CPU
          proc_table[system_status->whos_on_the_cpu->job_number][5] = clock_to_seconds; // finish time
          resource_table[0] += proc_table[system_status->whos_on_the_cpu->job_number][2]; // adjust system memory availability
          system_status->number_processes-=1;
          completed_jobs += 1;
          complete_q = send_to_complete_q(complete_q, system_status->whos_on_the_cpu, system_status,proc_table,resource_table);

          
          if (wait_q) { // check wait queue for job
            wait_q = ready_q_to_CPU(wait_q,system_status);
            system_status->time_quantum = quantum_interupt_system_baseline;
          } else if (ready_q_head) { // check ready queue for job
            //bankers(system_status->number_processes, ready_q_head,max_table,proc_table,resource_table);
            ready_q_head = ready_q_to_CPU(ready_q_head,system_status);
            system_status->time_quantum = quantum_interupt_system_baseline;
          } else {// no pending jobs, set current system job to null
            system_status->whos_on_the_cpu = NULL;
          }

          if (hold_q_1_head) { // induct job from hold queue 1 to ready queue
            system_status->number_processes+=1;
            int mem = hold_q_1_head->memory_required;
            if (mem < resource_table[0]) {
              ready_q_head = send_to_ready_q(ready_q_head, hold_q_1_head, system_status); // process moving into ready queue, add to process table
              proc_table[hold_q_1_head->job_number][0] = hold_q_1_head->job_number;
              proc_table[hold_q_1_head->job_number][1] = hold_q_1_head->run_time;
              proc_table[hold_q_1_head->job_number][2] = hold_q_1_head->memory_required;
              proc_table[hold_q_1_head->job_number][3] = 1;
              proc_table[hold_q_1_head->job_number][5] = 0;

              max_table[hold_q_1_head->job_number][0] = hold_q_1_head->memory_required; // add to max table
              max_table[hold_q_1_head->job_number][1] = hold_q_1_head->devices_required;

              resource_table[0] -= proc_table[hold_q_1_head->job_number][2]; // adjust system memory availability

              hold_q_1_head = hold_q_1_head->next;
            }
          } 
          if (hold_q_2_head) {// induct job from hold queue 2 to ready queue
            system_status->number_processes+=1;
            int mem = hold_q_2_head->memory_required;
            if (mem < resource_table[0]) {
              ready_q_head = send_to_ready_q(ready_q_head, hold_q_2_head, system_status); // process moving into ready queue, add to process table
              proc_table[hold_q_2_head->job_number][0] = hold_q_2_head->job_number;
              proc_table[hold_q_2_head->job_number][1] = hold_q_2_head->run_time;
              proc_table[hold_q_2_head->job_number][2] = hold_q_2_head->memory_required;
              proc_table[hold_q_2_head->job_number][3] = 1;
              proc_table[hold_q_2_head->job_number][5] = 0;

              max_table[hold_q_2_head->job_number][0] = hold_q_2_head->memory_required; // add to max table
              max_table[hold_q_2_head->job_number][1] = hold_q_2_head->devices_required;

              resource_table[0] -= proc_table[hold_q_2_head->job_number][2]; // adjust system memory availability

              hold_q_2_head = hold_q_2_head->next;
            } 
            
          }
        } else if (system_status->time_quantum == 0) { // quantum = 0, context switch round robin style!!
          resource_table[0] += proc_table[system_status->whos_on_the_cpu->job_number][2]; // adjust system memory availability
          ready_q_head = context_switch(ready_q_head, system_status->whos_on_the_cpu,system_status, proc_table,resource_table);
          resource_table[0] -= proc_table[system_status->whos_on_the_cpu->job_number][2]; // adjust system memory availability
        }     
        puts("PBH");
      }          
      if (wait_q) { // induct from wait queue, in this case, system did not have mounted process
      puts("PBH2");
        wait_q = ready_q_to_CPU(wait_q,system_status);
        system_status->time_quantum = quantum_interupt_system_baseline; // reset quantum for new process
      }

      if (system_status->time_quantum == 0) system_status->time_quantum = quantum_interupt_system_baseline;// reset quantum for new process

      if (clock_to_seconds == event_list_head->time_arrival) { // event arrived!
        if (event_list_head->job) { // event is job
          struct Job *job = event_list_head->job;
          proc_table[job->job_number][4] = clock_to_seconds; // set induction time
          //bankers(system_status->number_processes, ready_q_head,max_table,proc_table,resource_table);
          if (job->memory_required > max_memory || job->devices_required > max_devices) {
            printf("Rejecting job number %i\n\n",job->job_number); // reject event -- requires too much memory
          } else {

            if (job->memory_required < resource_table[0]) {
              num_jobs += 1;
              proc_table[job->job_number][0] = job->job_number; // process moving into ready queue, add to process table
              proc_table[job->job_number][1] = job->run_time;
              proc_table[job->job_number][2] = job->memory_required;
              proc_table[job->job_number][3] = 1;
              proc_table[job->job_number][5] = 0;

              max_table[job->job_number][0] = job->memory_required; // add to max table
              max_table[job->job_number][1] = job->devices_required;

              ready_q_head = send_to_ready_q(ready_q_head,job,system_status);
              resource_table[0] -= proc_table[job->job_number][2]; // adjust system memory availability
              system_status->number_processes+=1;

            } else {
              if (event_list_head->job->priority == 1) {
                hold_q_1_head = send_to_h_q_1(hold_q_1_head, job); // add job to hold queue 1
              } else {
                hold_q_2_head = send_to_h_q_2(hold_q_2_head, job); // add job to hold queue 2 
              }
            }
          }
        } else if (event_list_head->request_devices) {  // event is request for devices
          request_device_head = send_to_requests(request_device_head, event_list_head->request_devices);
        } else if (event_list_head->release_devices) {  // event is release of devices
          release_device_head = send_to_releases(release_device_head, event_list_head->release_devices);
        } else if (event_list_head->display_status == 1) {  // event is display status
          print_system_status(completed_jobs, system_status,clock_to_seconds,hold_q_1_head,hold_q_2_head,ready_q_head,resource_table,proc_table,wait_q);
        }
puts("PBH3");
        if (process_on_the_cpu == 0 && ready_q_head != NULL) { // if no process on CPU, bring process from ready queue on to CPU
          ready_q_head = start_job(system_status, ready_q_head, proc_table); 
          process_on_the_cpu = 1;
        }

      event_list_head = event_list_head->next;  // iterator changes to next event for while loop
      }
      puts("PBH9");
    }

    // check request queue for job on cpu
    if (system_status->whos_on_the_cpu && request_device_head) { // check requests for deivces for matching jobs 
      if (request_device_head->job_number == system_status->whos_on_the_cpu->job_number) { // match found, realloc devices and send to wait queue
        max_table[system_status->whos_on_the_cpu->job_number][1] = request_device_head->devices_requested;
        wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
        system_status->whos_on_the_cpu = NULL;
        request_device_head = request_device_head->next;
      } else {
        struct Request_devices *tmp_request_device_head = request_device_head;
        if (request_device_head->next) {
        struct Request_devices *tmp2_request_device_head = tmp_request_device_head->next;
        while (tmp2_request_device_head != NULL) {
          if (tmp2_request_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
            max_table[system_status->whos_on_the_cpu->job_number][1] = tmp2_request_device_head->devices_requested; // match found, realloc devices and send to wait queue
            wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
            system_status->whos_on_the_cpu = NULL;
            tmp_request_device_head->next = tmp2_request_device_head->next;
          } else {
            tmp_request_device_head = tmp2_request_device_head;
            tmp2_request_device_head = tmp2_request_device_head->next;
          }
        }
      }
      }
     
    }   

    if (system_status->whos_on_the_cpu && release_device_head) {  // check release of deivces for matching jobs 
    puts("PBH99");
      if (release_device_head->job_number == system_status->whos_on_the_cpu->job_number) { // match found, 0xd devices and send to wait queue

        max_table[system_status->whos_on_the_cpu->job_number][1] -= release_device_head->devices_released;
        wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
        system_status->whos_on_the_cpu = NULL;
        release_device_head = release_device_head->next;
      } else {
        struct Release_devices *tmp_release_device_head = release_device_head;
        if (release_device_head->next) {
        struct Release_devices *tmp2_release_device_head = tmp_release_device_head->next;
        while (tmp2_release_device_head != NULL) {
          if (tmp2_release_device_head->job_number == system_status->whos_on_the_cpu->job_number) {
            max_table[system_status->whos_on_the_cpu->job_number][1] -= release_device_head->devices_released;
            wait_q = send_to_wait_1(wait_q, system_status->whos_on_the_cpu);
            system_status->whos_on_the_cpu = NULL;
            tmp_release_device_head->next = tmp2_release_device_head->next;
          } else {
            tmp_release_device_head = tmp2_release_device_head;
            tmp2_release_device_head = tmp2_release_device_head->next;
          }
        }
      }
      }
     
    }
    
    if (system_status->whos_on_the_cpu == NULL && ready_q_head != NULL) system_status->whos_on_the_cpu = ready_q_head;

  }
  return 0;
}



*/