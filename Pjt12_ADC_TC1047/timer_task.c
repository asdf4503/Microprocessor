#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include "timer_task.h"
#include "prime.h"
#include "uart.h"
#include "ADC.h"

struct timer *get_timer() {
	struct timer *tp;

	tp = (struct timer *)malloc(sizeof(*tp));
	return(tp);
}

struct timer *Thead = NULL;
void insert_timer(struct task *tskp, int ms) {
	int 			total;
	struct timer 	*tp, *cp, *pp;

	tp = get_timer();
	tp->task = *tskp;
	tp->time = ms;

	if(Thead == NULL) {
		Thead = tp, tp->link = NULL;
		return;
	}

	pp = NULL, total = 0;

	for(cp = Thead;cp;cp = cp->link) {
		total += cp->time;
		if(total >= ms)
			break;
		pp = cp;
	}

	if(pp == NULL) {
		cp->time -= tp->time;
		tp->link = cp, Thead = tp;
	}
	else if(cp == NULL) {
		tp->time -= total;
		pp->link = tp;
		tp->link = NULL;
	}
	else {
		total -= cp->time;
		tp->time -= total;
		cp->time -= tp->time;
		pp->link = tp;
		tp->link = cp;
	}
}

void tour_timer() {
	struct timer *cp;
	int total = 0;

	printf("\n");
	for(cp = Thead;cp != NULL;cp = cp->link) {
		total += cp->time;
		printf("-->%d(%d) ", cp->time, total);
	}
	printf("\n");
}

void free_timer() {
	struct timer *cp;

	for( ;Thead != NULL; ) {
		cp = Thead;
		Thead = cp->link;
		free(cp);
	}
}

void timer_init() {
	TCNT2 = 0;
	sbi(ASSR, AS2);
	sbi(TIMSK2, TOIE2);
	sbi(TCCR2B, CS20);	sbi(TCCR2B, CS21);
}

void timer_expire(void) {
	struct timer *tp;

	for( ;Thead != NULL && !Thead->time;) {
		tp = Thead, Thead = tp->link;
		task_insert(&tp->task);
		free(tp);
	}
}

ISR(TIMER2_OVF_vect) {
	if(!Thead)
		return;
	if(--Thead->time == 0)
		timer_expire();
}

#define MAX_TASK	16

struct task Task_q[MAX_TASK];
volatile int Task_f, Task_r;

void task_init() {
	Task_f = Task_r = 0;
}

int task_insert(struct task *tskp) {
	if((Task_r + 1) % MAX_TASK == Task_f)
		return(0);
	Task_r = (Task_r + 1) % MAX_TASK;
	Task_q[Task_r] = *tskp;
	return(1);
}

int task_delete(struct task *tskp) {
	if(Task_r == Task_f)
		return(0);
	Task_f = (Task_f + 1) % MAX_TASK;
	*tskp = Task_q[Task_f];
	return(1);
}

void task_cmd(char *arg) {
	char buf[64], *cp0, *cp1, *cp2, *cp3;
	struct task task;
	int ms;
	if(!uart_peek())	return;
	if(gets(buf) == NULL) {
		printf("logout, good bye !!!\n");
		while(1);
	}

	cp0 = strtok(buf, 	" \t\n\r");
	cp1 = strtok(NULL, 	" \t\n\r");
	cp2 = strtok(NULL, 	" \t\n\r");
	cp3 = strtok(NULL, 	" \t\n\r");

	if(cp0 == NULL) {
		printf("$ "); return;
	}
	if(!strcmp(cp0, "prime"))
		task_prime(cp1);
	else if(!strcmp(cp0, "watch")) {
		int i;
		for(i = 0;i < 10;i++) {
			printf("%d ", i);
			int s;
			s = 2000 / 256;
			cli();
			insert_timer(&task, s);
			sei();
		}	
	}
	else if(!strcmp(cp0,"on")) {
		task_led_on();
	} else if(!strcmp(cp0,"off"))
		task_led_off();
	else if(!strcmp(cp0, "timer")) {
		if(cp1 == NULL) {
			printf("!!!-222\n");
			printf("$ ");
			return;
		}
		ms = atoi(cp1) / 256;
		if(!strcmp(cp2, "prime")) {
			task.fun = task_prime;
			if(cp3)	strcpy(task.arg, cp3);
			else	strcpy(task.arg, "");
			cli();
			insert_timer(&task, ms);
			sei();
		} else if(!strcmp(cp2, "tc1047")) {
			task.fun = task_tc1047;
			if(cp3)	strcpy(task.arg, cp3);
			else	strcpy(task.arg, "");
			cli();
			insert_timer(&task, ms);
		}
		else printf("!!!-333\n");
	}
	else if(!strcmp(cp0, "tc1047"))
		task_tc1047("");
	else printf("Unknown command...\n");
	printf("$ ");
}

void task_tc1047(char *arg) {
	static int	value;
	static int	volatile in_adc = 0;

	if(!strcmp(arg, "")) {
		adc_start(); in_adc = 1; while(in_adc);
		printf("Current temperature is %d degree.\n", value);
	}
	else {
		value = atoi(arg) * (1.1/1023) * 1000;
		value = (value - 500) / 10;
		in_adc = 0;
	}
}
