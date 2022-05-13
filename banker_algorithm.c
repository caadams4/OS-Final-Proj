// Banker's Algorithm
#include "prototypes.h"
int p_count;

int banker(struct Job *job, struct Request_devices *dev_req, struct Release_devices *dev_rel, struct System_status *sys_status)
{	
	int process = job->job_number;
	int available_resources = sys_status->memory_available;
	//int need = job->memory_required;
	int resources = job->devices_required;
	//int max_memory = sys_status->memory_available;
	printf("pcount =%d\n", p_count);
	printf("process =%d\n", process);
	printf("available resources =%d\n", available_resources);
	printf("need =%d\n", job->memory_required);
	printf("resources =%d\n", resources);


//There must be a better way to count how many processes there are (attention needed)
	if(process != 0 && p_count == 0){
		p_count++;
		//printf("test1\n");
	}
	else if(process != 0 && p_count > 0){
		p_count ++;
		//printf("test2\n");
	}
	else{
		printf("Fatal Error\n");
	}

	int alloc[p_count][resources];//allocation matrix 


printf("Allocation =%d\n", alloc[p_count][resources]);
	
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
