#include "prototypes.h" // ** all functions and structs protyped in protopytes.h

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
  clock_t start_t, end_t, total_t;
  int process_on_the_cpu = 0;
  int clock_to_seconds = 0, time_ticker;
  int quantum_interupt_system_baseline = 0, max_memory, max_devices;
  struct Event_arrival *event_list_head = read_input(); // builds a linked list of event
  struct Job *hold_q_1_head = NULL;
  struct Job *hold_q_2_head = NULL;
  struct Job *ready_q_head = NULL;
  struct Job *wait_q = NULL;
  struct Request_devices *request_device_head = NULL;
  struct Release_devices *release_device_head = NULL;
  struct System_status *system_status = event_list_head->system_status; // creates a struct system config
  max_devices = system_status->serial_devices_available;
  max_memory = system_status->memory_available;
  quantum_interupt_system_baseline = system_status->time_quantum;

  int time_interval;
  start_t = clock();

  while (event_list_head != NULL) { // iterates through each event!

    //time_ticker = clock()%1000000;
    time_ticker = clock()%100000;
    time_interval = 0;
    if (time_ticker == 0) {
      time_interval = 1;
      if (system_status->whos_on_the_cpu != NULL) {
        system_status->time_quantum -= 1;
        system_status->whos_on_the_cpu->run_time -= 1;
      }
      clock_to_seconds++;
      printf("start_time + %i\n",clock_to_seconds);
    /* --------- CPU ----------- */
      // Tick down / is the current processed finish / context switch performed
      if (system_status->time_quantum == 0 || system_status->whos_on_the_cpu->run_time == 0) {
        printf("SWITCHING FROM %i (cpu) to %i (ready q)",ready_q_head->job_number,system_status->whos_on_the_cpu->job_number);
        ready_q_to_CPU(ready_q_head,system_status);
        //add_to_process_table(system_status);
        system_status->time_quantum = quantum_interupt_system_baseline;
      }
        

      // function for ready_queue to CPU
      
      //print_process_table(system_status);

    /* --------- Internal events ----------- */
      // Are there any device requests for the process currently on the cpu



    /* --------- External events ----------- */
      // Event arrivals

      if (clock_to_seconds == event_list_head->time_arrival) {

        if (event_list_head->job) {
          struct Job *job = event_list_head->job;

          //Not sure if this is the right place for this
          //banker(job, request_device_head, release_device_head, system_status);

        
          if (job->memory_required > max_memory && job->devices_required > max_devices) {
            printf("Rejecting job number %i\n\n",job->job_number); // reject event -- requires too much memory
          } else {



            if (job->memory_required < system_status->memory_available) {
              printf("Inducting job with priority %i at time: %i\n\n",job->priority, job->time_arrival);
              // TODO Enough available memory? send to ready queue
              system_status->number_processes += 1;

              ready_q_head = send_to_read_q(ready_q_head,job);



            } else {
              printf("Sending job with priority %i to hold queue at time: %i\n\n",job->priority, job->time_arrival);
              if (event_list_head->job->priority == 1) {
                hold_q_1_head = send_to_h_q_1(hold_q_1_head, job); // add job to hold queue 1 ( defined in linked_list.c )
              } else {
                hold_q_2_head = send_to_h_q_2(hold_q_2_head, job); // add job to hold queue 2 ( defined in linked_list.c )
              }
            }

          }

        } else if (event_list_head->request_devices) {  // TODO Device request
          puts("make request!");
          request_device_head = send_to_requests(request_device_head, event_list_head->request_devices);
        } else if (event_list_head->release_devices) {  // TODO Device release
          release_device_head = send_to_releases(release_device_head, event_list_head->release_devices);
        } else if (event_list_head->display_status == 1) {
          //print_system_status(system_status);
        }

      
      if (process_on_the_cpu == 0 && ready_q_head != NULL) {
        puts("why");
        ready_q_head = ready_q_to_CPU(ready_q_head,system_status);
        //add_to_process_table(system_status);
        printf("\n\n!!!%i!!!\n\n",system_status->whos_on_the_cpu->job_number);
        process_on_the_cpu = 1;
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

  print_process_table(system_status);

  return 0;
}

