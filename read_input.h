typedef struct Job {
  int time_arrival;
  int job_number;
  int memory_required;
  int devices_required;
  int run_time;
  int priority;
  struct Job *next;
} Job;

typedef struct Request_devices {
  int time_arrival;
  int job_number;
  int devices_requested;
} Request_devices;

typedef struct Release_devices {
  int time_arrival;
  int job_number;
  int devices_released;
} Release_devices;

typedef struct Event_arrival {
  int time_arrival;
  struct Event_arrival *next;
  struct Job *job;
  struct Request_devices *request_devices;
  struct Release_devices *release_devices;
} Event_arrival;




void read_input();

int parse_arrival_time(char *job);

void submit_job(Job *newJob, char *op);

// device request
Request_devices *device_request(char *device_req);

// release devices
Release_devices *release_device(char *release_req);

// configure device
void sys_config(char *sys_specs);

// display status 
void display_status();



