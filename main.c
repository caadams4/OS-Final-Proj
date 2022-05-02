#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "submit_q.h"
#include "device_mgmt.h"

void read_input();

// submit queue


// hold queue 1


// hold queue 2

int main(void) {
  read_input();  
  return 0;
}

void read_input() {
  // Read input of input.txt and build tasks and requests
    char op[30];
    // open input file
    FILE *input = fopen("./input.txt", "r");
    /* Get each op until there are none left */
    while (fgets(op, 30, input)) {
        char opCode = op[0];
      
        switch (opCode){
          case 'C':
            sys_config(op); // device_mgmt.c
            break;
          case 'A':;  // intentially left a semicolon. Would give an error next line without it

            // Creates a job struct for each job read from input
            
            Job * job = submit_job(op); // submit_q.c

            // TODO send_2_hold_q(job)
                // Will add job node to linked list of HQ1 or HQ2 based on priority
            
            break;
          case 'Q':
            device_request(op); // device_mgmt.c 
            break;
          case 'L':
            release_device(op); // device_mgmt.c
            break;
          case 'D':
            puts("Display Status");
            printf("%s\n", op);
            break;
          
        }
        if (op[strlen(op) - 1] != '\n')
            printf("\n");
    }
}