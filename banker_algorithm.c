#include "prototypes.h"
int banker(struct Job *job, struct Request_devices *dev_req, struct Release_devices *dev_rel, struct System_status *sys_status){	
	int process = job->job_number;
	int available_resources = sys_status->memory_available;
  int resources = job->devices_required;
	int alloc[process][resources];//allocation matrix 	
  int max[process][resources]; //max resources matrix
  int available[available_resources]; //available resources
  int need[process][resources]; //resources needed
	int k,j,i;
  int y = 0;
    int f[process], ans[process], ind = 0;
    for (k = 0; k < process; k++){
        f[k] = 0;
    }
    for (i = 0; i < process; i++){
        for (j = 0; j < resources; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    for (k = 0; k < process; k++){
        for (i = 0; i < process; i++){
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > available[j]){
                        flag = 1;
                         break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < resources; y++)
                        available[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
      int flag = 1;
      for(int i=0;i<process;i++){
        if(f[i]==0){
          flag=0;
          printf("The system is not safe\n");
          break;
        }
      }
      if(flag==1){
        printf("This sequence is safe\n");
        for (i = 0; i < process - 1; i++){
          printf(" P%d ->", ans[i]);
          printf(" P%d\n", ans[process - 1]);
        }
      }
return (0);
}

/*
#include <stdio.h>
