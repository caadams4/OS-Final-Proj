#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "read_input.h"


int start_time = 0;

struct Event_arrival *event_list_head;
  // ^ this is the head of the event-arrival-linked-list  


int main(void) {
  int finished = 0;
  event_list_head = read_input(); 

  

  while (finished == 0){
    printf("Arrived at %i", event_list_head->time_arrival);
    event_list_head = event_list_head->next;

    if (  event_list_head == NULL) finished = 1;
    
  }

  
  return 0;
}
