#include <avr/io.h>
#include <stdio.h>
#include <compat/deprecated.h>
#include <util/delay.h>

#include "uart.h"

int is_prime(int n) {
	int i;
	for(i = 2; i <= n/2; i++)
		if ((n % i) == 0) return(0); /* FALSE */
	return(1);						 /* TRUE */
}

int main() {
	int i;
	
	uart_init();
	for(i = 3; i <= 2000; i++) {
		if (is_prime(i)) 
			printf("%d is a prime number !!!\n", i);
		else
			printf("%d is not a prime number !!!\n", i);
	}
	printf("The end !!!\n");
	
	while(1); //must not return !

	return 0;
		
}

