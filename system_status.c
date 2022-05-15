#include "prototypes.h"


void print_system_status(struct System_status *system_status) {

    print_system_resources();

    print_process_table(system_status);

    print_hold_queues();

    print_ready_queue();

    print_process_on_CPU();
    print_wait_queue();
}


void add_to_process_table(struct System_status *system_status) {


    printf("Who is on the CPU: %i\n",system_status->whos_on_the_cpu->job_number);
        printf("Who is on the CPU: %i\n",system_status->whos_on_the_cpu->run_time);
            printf("Who is on the CPU: %i\n",system_status->whos_on_the_cpu->memory_required);
                printf("Who is on the CPU: %i\n",system_status->whos_on_the_cpu->devices_required);


    system_status->process_table[system_status->number_processes][0] = system_status->whos_on_the_cpu->job_number;
    system_status->process_table[system_status->number_processes][1] = system_status->whos_on_the_cpu->run_time;
    system_status->process_table[system_status->number_processes][2] = system_status->whos_on_the_cpu->memory_required;
    system_status->process_table[system_status->number_processes][3] = system_status->whos_on_the_cpu->devices_required;
    system_status->process_table[system_status->number_processes][4] = 0;
    system_status->process_table[system_status->number_processes][5] = 0;

    system_status->number_processes += 1;
    
    //printf("pid: %i | runtime: %i | memory_req: %i | devices_req %i ",system_status->process_table[system_status->number_processes-1][0],system_status->process_table[system_status->number_processes][1],system_status->process_table[system_status->number_processes][2],system_status->process_table[system_status->number_processes][3]);

}



void print_system_resources() {
    printf("At time 9999:\nCurrent Available Main Memory=200\nCurrent Devices=12\nCompleted Jobs:\n");
}

void print_process_table (struct System_status *system_status) {
    puts("--------------------------------------------------------\n");
    puts("Job ID    Arrival Time    Finish Time    Turnaround Time\n");
    puts("========================================================\n");
    for (int i = 0; i<system_status->number_processes;i++) {
        for (int j = 0;j<6;j++) {
            printf("  %i         ",system_status->process_table[i][j]);
        }
        printf("\n");
    }

    printf("  %i         ",system_status->number_processes);
    /*
    TODO: print each COMPLETED process in its own line
    
    */
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



