#include "prototypes.h"


void print_system_status(int completed_jobs, struct System_status *system_status,int time,struct Job *hold_q_1_head,struct Job *hold_q_2_head,struct Job *ready_q_head,int resource_table[],int process_table[][6]) {

    printf("At time %i:\nCurrent Available Main Memory=%i\nCurrent Devices=%i\nCompleted Jobs:%i\n",time,resource_table[0],resource_table[1],completed_jobs);
    print_job_stats(system_status,process_table);
    print_hold_queues(hold_q_1_head,hold_q_2_head);

    print_ready_queue(ready_q_head);

    print_process_on_CPU(system_status,process_table);
    print_wait_queue();
}



void print_job_stats(struct System_status *system_status,int process_table[][6]) {
    puts("--------------------------------------------------------\n");
    puts("Job ID    Arrival Time    Finish Time    Turnaround Time\n");
    puts("========================================================\n");
    for (int i = 1; i<system_status->number_processes+1;i++) {
        printf("  %i            %i             %i              %i         \n",process_table[i][0],process_table[i][4],process_table[i][5],process_table[i][5]-process_table[i][4]);
    }

/*
           _____________________PROCESS TABLE_____________________________
  index   |   [0]     [1]      [2]        [3]        [4]         [5]      |
  data    |   pid   runtime   memory    devices   timestart   timefinish  |
  example |    1      5         3          4          1           6       |
  example |    2      5         3          4          6           11      |
          |_______________________________________________________________|
*/
}
void print_process_table(struct System_status *system_status,int process_table[][6]) {
            puts("-----------------------\n");
            puts(" pid   memory   devices\n");
            puts("=======================\n");
    for (int i = 1; i<system_status->number_processes+1;i++) {
        printf("  %i      %i       %i       \n",process_table[i][0],process_table[i][2],process_table[i][3]);
    }
/*
           _____________________PROCESS TABLE_____________________________
  index   |   [0]     [1]      [2]        [3]        [4]         [5]      |
  data    |   pid   runtime   memory    devices   timestart   timefinish  |
  example |    1      5         3          4          1           6       |
  example |    2      5         3          4          6           11      |
          |_____________________________________________________+__________|
*/
}

void print_max(struct System_status *system_status,int max_table[][2],int process_table[][6]) {
            puts("------------------------\n");
            puts(" pid   memory    devices\n");
            puts("========================\n");
    
    for (int i = 1; i<system_status->number_processes+1;i++) {
        printf("  %i      %i        %i\n",process_table[i][0],max_table[i][0],max_table[i][1]);
    }
}

void print_resources(struct System_status *system_status,int resource_table[2]) {
            puts("-----------------\n");
            puts("memory    devices\n");
            puts("=================\n");
          printf(" %i         %i\n",resource_table[0],resource_table[1]);
}

void print_hold_queues(struct Job *hold_q_1_head,struct Job *hold_q_2_head) {
       puts("\nHold Queue 1:\n");
       puts("-------------------------\n");
       puts("Job ID    Run Time");
    puts("=========================\n");

    struct Job *tmp_hold_q_1_head = hold_q_1_head;
    while (tmp_hold_q_1_head != NULL) {   // prints Hold queue 1 contents
        printf("%i       %i\n",tmp_hold_q_1_head->job_number,tmp_hold_q_1_head->run_time);
        tmp_hold_q_1_head = tmp_hold_q_1_head->next;  // iterates through entire hold queue 2. sorted
    }  

    // for each hold queue 2 node
    puts("\nHold Queue 2:\n");
    puts("-------------------------\n");
    puts("Job ID    Run Time");
    puts("=========================\n");

    struct Job *tmp_hold_q_2_head = hold_q_2_head;
    while (tmp_hold_q_2_head != NULL) {   // prints Hold queue 2 contents
        printf("FIFO Queue (hold Q 2) Runtime: %i - Job No. %i\n",tmp_hold_q_2_head->run_time,tmp_hold_q_2_head->job_number);
        tmp_hold_q_2_head = tmp_hold_q_2_head->next;  // iterates through entire hold queue 2. sorted
    }  
}

             
    

void print_ready_queue(struct Job *ready_q_head){
    puts("\nReady Queue:\n");
    puts("----------------------------------\n");
    puts("Job ID    Run Time Time    Accrued\n");
    puts("==================================\n");

    struct Job *tmp_ready_q_head = ready_q_head;
    while (tmp_ready_q_head != NULL){
        printf("Ready queue Runtime: %i - Job No. %i\n",tmp_ready_q_head->run_time,tmp_ready_q_head->job_number);
        tmp_ready_q_head = tmp_ready_q_head->next;  // iterates through entire hold queue 2. sorted
    }
}

void print_process_on_CPU(struct System_status *system_status,int process_table[][6]){
      puts("\nProcess running on CPU:\n");
      puts("-----------------------------\n");
      puts("Job ID    Run Time    Accrued\n");
      puts("=============================\n");
      if (system_status->whos_on_the_cpu)
    printf("  %i         %i         %i\n",system_status->whos_on_the_cpu->job_number,system_status->whos_on_the_cpu->run_time,system_status->whos_on_the_cpu->run_time-process_table[system_status->whos_on_the_cpu->job_number][1]);
    
}

void print_wait_queue(){
    puts("\nWait Queue:\n");
    puts("----------------------------------\n");
    puts("Job ID    Run Time Time    Accrued\n");
    puts("==================================\n");

    /*
    TODO: print each wait queue node in its own line
    printf("  %i           %i          %i\n");
    */
}



