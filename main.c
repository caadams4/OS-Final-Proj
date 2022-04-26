#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "submit_q.c"
#include "device_mgmt.c"


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
          case 'A':
            submit_job(op); // device_mgmt.c
            break;
          case 'Q':
            device_request(op); // submit_q.c
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