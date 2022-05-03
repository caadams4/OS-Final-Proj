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


typedef struct System_config {
  int time_arrival;
  int memory_available;
  int serial_devices_available;
  int time_quantum;
} System_config;

  

typedef struct Event_arrival {
  int time_arrival;
  struct Event_arrival *next;
  struct Job *job;
  struct Request_devices *request_devices;
  struct Release_devices *release_devices;
  struct System_config *system_config;
} Event_arrival;


Event_arrival *read_input();

int parse_arrival_time(char *job);

void submit_job(Job *newJob, char *op);

// device request
void device_request(Request_devices *request_devices, char *job);

// release devices
void device_release
(Release_devices *release_devices, char *job);

// configure device
void sys_config(System_config *system_config, char *sys_specs);

// display status 
void display_status();



