
typedef struct Job {
  int time_arrival;
  int job_number;
  int memory_required;
  int devices_required;
  int run_time;
  int priority;
  struct Job *next;
} Job;

void induct_process(struct Job *hold_q_1_head, struct Job *hold_q_2_head, struct Job *job);

void send_to_h_q_1(struct Job *hold_q_1_head, struct Job *job);

void send_to_h_q_2(struct Job *hold_q_2_head, struct Job *job);
