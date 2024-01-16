#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <compat/deprecated.h>
#include "prime.h"

int is_prime(int n) {
	int i;
	for(i = 2;i <= n/2;i++)
		if((n % i) == 0)
			return(0);
	return(1);
}

void app_prime(char *ap) {
	int t = 300, n, count = 0;
	if(ap) t = atoi(ap);
	for(n = 2;n <= t;n++) {
		if(is_prime(n)) {
			count++;
			printf("%d is a prime number !!! \n", n);
		}
	}
	printf("count = %d\n", count);
}

void task_prime(char *ap) {
	int n, t = 300, count = 0;
	if(ap && *ap) t = atoi(ap);
	for(n = 2;n <= t;n++) {
		if(is_prime(n)) {
			count++;
			printf("%d is a prime number !!! \n", n);
		}
	}
	printf("count = %d\n", count);
}

static uint8_t Leds;

void led_init() {
	DDRL = PORTL = 0xff;
}

void task_led_on() {
	Leds = PORTL = 0x00;
	
}

void task_led_off() {
	Leds = PORTL = 0xff;
}
