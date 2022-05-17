#include "prototypes.h"


int bankers(int num_procs, struct Job *ready_q_head,int max_table[][2],int process_table[][6],int resource_table[2]){

    int num_resources = 1; // devices 
    int index = 0, flag = 0;
 
    int fals[num_procs], safe[num_procs];
    for (int k = 0; k < num_procs; k++) { // initialize array
        fals[k] = 0;
    }
    int need[num_procs][num_resources];
    for (int i = 0; i < num_procs; i++) {
            need[i][0] = max_table[i][1] - process_table[i][3];
    }
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < num_procs; i++) {
          if (fals[i] == 0) {
            flag = 0;
            if (need[i][0] > resource_table[1]){
              flag = 1;
                break;
            }
            if (flag == 0) {
              safe[index++] = i;
              resource_table[1] += process_table[i][3];
              fals[i] = 1;
            }
          }
      }
    }
    flag = 1;
    for(int i=0;i<num_procs;i++){
      if(fals[i]==0){
        flag=0;
        printf("unsafe :");
        break;
      }
    }
    if(flag==1){
      printf("safe:");
      for (int i = 0; i < num_procs-1; i++)
        printf(" Job_num: %i ->", safe[i]);
      printf(" Job_num: %i", safe[num_procs-1]);
    }
    return (0);
}
