#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart.h"

int main() {
	int i;
	uart_init();
	sei();

	for(i = 0;i < 10;i++) {
		uart_putstart("I love you.\n");
		uart_putstart("I love me.\n");
		uart_putstart("he loves her.\n");
	}

	uart_putstart("End !!!\n");
	while(1); return 0;
}
