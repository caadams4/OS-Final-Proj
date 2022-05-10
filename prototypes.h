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
  struct Request_devices *next;
  int time_arrival;
  int job_number;
  int devices_requested;
} Request_devices;

typedef struct Release_devices {
  struct Release_devices *next;
  int time_arrival;
  int job_number;
  int devices_released;
} Release_devices;

typedef struct System_status {
  int memory_available;
  int serial_devices_available;
  int time_quantum;
} System_status;

typedef struct Event_arrival {
  int time_arrival;
  struct Event_arrival *next;
  struct Job *job;
  struct Request_devices *request_devices;
  struct Release_devices *release_devices;
  struct System_status *system_status;
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
void sys_config(System_status *system_config, char *sys_specs);

// display status 
void display_status();

Event_arrival *add_event_to_end(struct Event_arrival* head);


// --------------------- Fucntion Prototypes for linked_list.c -------------------- //

struct Job *induct_process(struct Job *hold_q_1_head, struct Job *hold_q_2_head, struct Job *job);

struct Job *send_to_h_q_1(struct Job *hold_q_1_head, struct Job *job);

struct Job *send_to_h_q_2(struct Job *hold_q_2_head, struct Job *job);

struct Job *compare_job_lengths(struct Job *incoming_job, struct Job *this_job, struct Job *next_job);

// --------------------- Fucntion Prototypes for internal_events.c -------------------- //


struct Request_devices *send_to_requests(struct Request_devices *request_device_head, struct Request_devices *req);

struct Release_devices *send_to_releases(struct Release_devices *release_device_head, struct Release_devices *req);
