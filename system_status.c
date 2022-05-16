#include "prototypes.h"


void print_system_status(struct System_status *system_status) {

    print_system_resources();

    print_hold_queues();

    print_ready_queue();

    print_process_on_CPU();
    print_wait_queue();
}

void update_resource_table(int memory_update, int devices_update,int resource_table[]) {
    resource_table[0] += memory_update;
    resource_table[1] += devices_update;
}






void print_system_resources() {
    printf("At time 9999:\nCurrent Available Main Memory=200\nCurrent Devices=12\nCompleted Jobs:\n");
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
        printf("  %i      %i          %i\n",process_table[i][0],max_table[0],max_table[1]);
    }
    
}

void print_resources(struct System_status *system_status,int resource_table[2]) {
            puts("-----------------\n");
            puts("memory    devices\n");
            puts("=================\n");

          printf(" %i         %i\n",resource_table[0],resource_table[1]);
}

void print_hold_queues() {
    puts("\nHold Queue 1:\n");
    puts("-------------------------\n");
    puts("Job ID    Run Time");
    puts("=========================\n");

    /*
    TODO: print each HQ1 node in its own line
    printf("  %i        %i\n");
    */

    // for each hold queue 2 node
    puts("\nHold Queue 2:\n");
    puts("-------------------------\n");
    puts("Job ID    Run Time");
    puts("=========================\n");

    /*
    TODO: print each HQ2 node in its own line
    printf("  %i        %i\n");
    */
}

void print_ready_queue(){
    puts("\nReady Queue:\n");
    puts("----------------------------------\n");
    puts("Job ID    Run Time Time    Accrued\n");
    puts("==================================\n");

    /*
    TODO: print each Ready queue node in its own line
    printf("  %i           %i          %i\n");
    */
}

void print_process_on_CPU(){
    puts("\nProcess running on CPU:\n");
    puts("----------------------------------\n");
    puts("Job ID    Run Time Time    Accrued\n");
    puts("==================================\n");

    /*
    TODO: print process info in its own line
    printf("  %i           %i          %i\n");
    */
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



