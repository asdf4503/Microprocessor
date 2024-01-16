struct task {
	void (*fun)(char *);
	char arg[8];
};

struct timer {
	int time;
	struct task		task;
	struct timer	*link;
};

extern struct timer *Thead;

struct timer *get_timer();

void 	insert_timer(struct task *tskp, int ms);
void	tour_timer(),
		free_timer();

void timer_init();
void timer_expire(void);

void task_init();
int task_insert(struct task *tskp);
int task_delete(struct task *tskp);
void task_cmd(char *arg);
void task_tc1047(char *arg);
