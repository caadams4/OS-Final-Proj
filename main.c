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

  int time_interval;
  start_t = clock();

  while (event_list_head != NULL) { // iterates through each event!

    time_ticker = clock()%100000;
    time_interval = 0;
    if (time_ticker == 0) {
      time_interval = 1;
      if (system_status->whos_on_the_cpu != NULL) {
        system_status->time_quantum -= 1;
        system_status->whos_on_the_cpu->run_time -= 1;
      }
      clock_to_seconds++;

    /* --------- CPU ----------- */

      // TODO job complete 

        // Condition: system_status->run_time == 0
                    // aka job is complete, on to the next one

        // 1. Take job off CPU and place into complete queue
        // 2. Release memory and/or devices
        // 3. Use bankers algorithm to determine next job from ready queue ( using device allocation )
        // 4. Check hold queue 1 and 2 for jobs and put them into the ready queue
      if (system_status->whos_on_the_cpu){
      if (system_status->whos_on_the_cpu->run_time == 0) {
        finished_job(system_status, complete_q, proc_table, clock_to_seconds);
        // replace cpu 
        if (ready_q_head) {
        system_status->whos_on_the_cpu = ready_q_head;
        add_to_process_table(system_status,proc_table);
        }
        if (ready_q_head) ready_q_head = ready_q_head->next;
      }
      }


      // TODO context switch

        // Condition: system_status->time_quantum == 0
                    // aka job has been processed for the alloted time and needs to switch

        // 1. Take job off CPU, then add to end of ready queue. 
        // 2. Release memory and/or devices
        // 3. Use bankers algorithm to determine next job from ready queue ( using device allocation )

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
          //banker(job, request_device_head, release_device_head, system_status);
          if (job->memory_required > max_memory || job->devices_required > max_devices) {
            printf("Rejecting job number %i\n\n",job->job_number); // reject event -- requires too much memory
          } else {

            // -------------------- //

            if (job->memory_required < resource_table[0]) {
              printf("Inducting job with priority %i at time: %i\n\n",job->priority, job->time_arrival);
              ready_q_head = send_to_ready_q(ready_q_head,job,system_status);
              update_resource_table(job->memory_required *-1,0,resource_table); // subtracts required memory from resource pool
              puts("0");
            // -------------------- //

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
          //print_system_status(system_status);
          // TODO make the display status pretty
        }

        if (process_on_the_cpu == 0 && ready_q_head != NULL) { // if no process on CPU, bring process from ready queue on to CPU
          // add bankers alg here, call start_job from there

          puts("____________");
          start_job(system_status, ready_q_head, proc_table, clock_to_seconds); // should be called from bankers

          puts("00000000");
          process_on_the_cpu = 1;
          puts("123123");
        }

      event_list_head = event_list_head->next;  // iterator changes to next evet for while loop
      }
    }

    if (system_status->whos_on_the_cpu == NULL && ready_q_head != NULL) system_status->whos_on_the_cpu = ready_q_head;

  }









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
  print_process_table(system_status,proc_table);
  return 0;
}

