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
#include "app.h"

int main() {
	char cmd[128], *cp, *ap;
	int n = 0;	

	uart_init();
	sei();
	while(1) {
		printf("$ ");
		if(fgets(cmd, sizeof(cmd), stdin) == NULL)	break;

		if((cp = strtok(cmd, "\n\r\t  ")) == NULL)	continue;
		ap = strtok(NULL, "");
		if		(!strcmp(cp, "prime"))				app_prime(ap);
		else if	(!strcmp(cp, "list"))				app_list(ap);
		else if (!strcmp(cp, "timer"))				app_timer(ap);
		else if	(!strcmp(cp, "add"))				app_add(ap);
		else										printf("Unknown command...\n");
	}
	printf("logout, good bye !!!\n");
	while(1); return(0);
}
