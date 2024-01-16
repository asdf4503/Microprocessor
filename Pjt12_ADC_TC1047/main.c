#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "prime.h"
#include "queue.h"
#include "link.h"
#include "timer_task.h"
#include "ADC.h"

int main() {
	int 	tag;
	struct 	task task;

	uart_init();
	task_init();
	timer_init();
	adc_init();
	led_init();

	printf("$ ");

	while(1) {
	int i;
	for(i = 0;i < 3;i++) {
		cli();
		tag = task_delete(&task);
		sei();
		if(tag)
			(*(task.fun))(task.arg);
			}
	}
	return(0);
}
