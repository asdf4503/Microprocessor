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

static uint8_t Leds;

void led(int n) {
	DDRL = PORTL = 0xff;

	if(n == 1)
		Leds = PORTL = 0x00;

	if(n == 2)
		Leds = PORTL = 0xff;

	if(n == 3) {
		Leds &= ~(1 << 1);
		PORTL = Leds;
	}

	if(n == 4) {
		Leds |= ~(1 << 1);
		PORTL = Leds;
	}
}


int main() {
	char cmd[128], *cp;
	
	uart_init();
	sei();
	while(1) {
		printf("$ ");
		if(fgets(cmd, sizeof(cmd), stdin) == NULL)	break;
		if((cp = strtok(cmd, "\n\r\t ")) == NULL)	continue;
		if(!strcmp(cmd, "prime"))					app_prime(2000);
		/*
		if(!strcmp(cmd, "led"))			
			if(!strcmp(cmd, "on"))
				if(!strcmp(cmd, "all"))
						led(1);
		else if(!strcmp(cmd, "led off all"))		led(2);
		else if(!strcmp(cmd, "led on 1"))			led(3);
		else if(!strcmp(cmd, "led off 1"))			led(4);
		//else if(!strcmp(cmd, "led"))				printf("Led = %x\n", Leds);*/
		else										printf("Unknown command...\n");
	}
	printf("logout, good bye !!!\n");
	while(1); return(0);
}
