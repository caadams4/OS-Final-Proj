typedef struct Job {
  int time_arrival;
  int job_number;
  int memory_required;
  int devices_required;
  int run_time;
  char priority;
  struct Job *next;
} Job;

Job *submit_job(char *job);