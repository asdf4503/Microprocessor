#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "prime.h"
#include "queue.h"

int main() {
	char cmd[128], ch;
	int n = 0;
	
	
	uart_init();
	sei();
	printf("$ ");
	while(1) {
		cli();
		ch = qi_delete();
		sei();
		if(ch) {
			if(ch == '\r')	continue;
			if(ch == '\n') {
				cmd[n] = 0;
				if(!strncmp(cmd, "app", 3)) {
					int i = atoi(cmd + 3);
					if(i != 0)
						 app_prime(i * 100);
					else if (strlen(cmd) == 3)
						app_prime(2000);
					else printf("Unknown command... \n");
				}
				
				else					printf("Unknown command... \n");
				n = 0;
				printf("$ ");
			}
			else
				cmd[n++] = ch;
		}
	}	
	return(0);
}
