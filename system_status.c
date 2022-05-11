#include <stdio.h>
#include <stdlib.h>

#include "prototypes.h"


void print_system_status() {

    print_system_resources();

    print_process_table();

    print_hold_queues();

    print_ready_queue();

    print_process_on_CPU();
    print_wait_queue();
   

}


void print_system_resources() {
    printf("At time 9999:\nCurrent Available Main Memory=200\nCurrent Devices=12\nCompleted Jobs:\n");
}

void print_process_table () {
    puts("--------------------------------------------------------\n");
    puts("Job ID    Arrival Time    Finish Time    Turnaround Time\n");
    puts("========================================================\n");

    /*
    TODO: print each COMPLETED process in its own line
    printf("  %i           %i              %i              %i       \n");
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

