#include "prototypes.h"


void print_system_status(int completed_jobs, struct System_status *system_status,int time,struct Job *hold_q_1_head,struct Job *hold_q_2_head,struct Job *ready_q_head,int resource_table[],int process_table[][6]) {

    printf("\n\nAt time %i:\nCurrent Available Main Memory=%i\nCurrent Devices=%i\nCompleted Jobs:%i\n",time,resource_table[0],resource_table[1],completed_jobs);
    print_job_stats(system_status,process_table);
    print_hold_queues(hold_q_1_head,hold_q_2_head);

    print_ready_queue(ready_q_head,process_table);

    print_process_on_CPU(system_status,process_table);
    print_wait_queue();
}



void print_job_stats(struct System_status *system_status,int process_table[][6]) {
    puts("--------------------------------------------------------");
    puts("Job ID    Arrival Time    Finish Time    Turnaround Time");
    puts("========================================================");
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
            puts("-----------------------");
            puts(" pid   memory   devices");
            puts("=======================");
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
            puts("------------------------");
            puts(" pid   memory    devices");
            puts("========================");
    
    for (int i = 1; i<system_status->number_processes+1;i++) {
        printf(" %i       %i        %i\n",process_table[i][0],max_table[i][0],max_table[i][1]);
    }
}

void print_resources(struct System_status *system_status,int resource_table[2]) {
            puts("-----------------");
            puts("memory    devices");
            puts("=================");
          printf(" %i         %i\n",resource_table[0],resource_table[1]);
}

void print_hold_queues(struct Job *hold_q_1_head,struct Job *hold_q_2_head) {
       puts("\nHold Queue 1:");
       puts("-------------------------");
       puts("Job ID    Run Time");
       puts("=========================");

    struct Job *tmp_hold_q_1_head = hold_q_1_head;
    while (tmp_hold_q_1_head != NULL) {   // prints Hold queue 1 contents
        printf(" %i       %i\n",tmp_hold_q_1_head->job_number,tmp_hold_q_1_head->run_time);
        tmp_hold_q_1_head = tmp_hold_q_1_head->next;  // iterates through entire hold queue 2. sorted
    }  

    // for each hold queue 2 node
    puts("\nHold Queue 2:");
    puts("-------------------------");
    puts("Job ID    Run Time");
    puts("=========================");

    struct Job *tmp_hold_q_2_head = hold_q_2_head;
    while (tmp_hold_q_2_head != NULL) {   // prints Hold queue 2 contents
   printf(" %i         %i\n",tmp_hold_q_2_head->job_number,tmp_hold_q_2_head->run_time);
        tmp_hold_q_2_head = tmp_hold_q_2_head->next;  // iterates through entire hold queue 2. sorted
    }  
}

             
    

void print_ready_queue(struct Job *ready_q_head,int process_table[][6]){
    puts("\nReady Queue:");
    puts("----------------------------------");
    puts("Job ID    Run Time Time    Accrued");
    puts("==================================");

    struct Job *tmp_ready_q_head = ready_q_head;
    while (tmp_ready_q_head != NULL){
printf(" %i         %i         %i\n",tmp_ready_q_head->job_number,tmp_ready_q_head->run_time,tmp_ready_q_head->run_time-process_table[tmp_ready_q_head->job_number][1]);
        tmp_ready_q_head = tmp_ready_q_head->next;  // iterates through entire hold queue 2. sorted
    }
}

void print_process_on_CPU(struct System_status *system_status,int process_table[][6]){
      puts("\nProcess running on CPU:");
      puts("-----------------------------");
      puts("Job ID    Run Time    Accrued");
      puts("=============================");
      if (system_status->whos_on_the_cpu)
    printf(" %i         %i         %i\n",system_status->whos_on_the_cpu->job_number,system_status->whos_on_the_cpu->run_time,system_status->whos_on_the_cpu->run_time-process_table[system_status->whos_on_the_cpu->job_number][1]);
    
}

void print_wait_queue(){
    puts("\nWait Queue:");
    puts("----------------------------------");
    puts("Job ID    Run Time Time    Accrued");
    puts("==================================");

    /*
    TODO: print each wait queue node in its own line
    printf("  %i           %i          %i\n");
    */
    puts("\n");
}



