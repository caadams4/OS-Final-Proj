#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Incoming input will be:

  // System config 'C'

  // Job Arrival 'A'

  // Req 4 devices 'Q'

  // Release devices 'L'

  // Display sys status 'D'


//char line[255];

void read_file() {
    char op[30];
    
    // open input file
    FILE *input = fopen("./input.txt", "r");
    
    /* Get each op until there are none left */
    while (fgets(op, 30, input)) {
        // print each op 
        
        char opCode = op[0];

        switch (opCode){
          case 'C':
            puts("Configuration");
            printf("%s", op);
            break;
          case 'A':
            puts("Job Arrival");
            break;
          case 'Q':
            puts("Req for Devices");
            printf("%s", op);
            break;
          case 'L':
            puts("Release Deivces");
            printf("%s", op);
            break;
          case 'D':
            puts("Display Status");
            printf("%s", op);
            break;
          
        }
      
        if (op[strlen(op) - 1] != '\n')
            printf("\n");
      
    }
}