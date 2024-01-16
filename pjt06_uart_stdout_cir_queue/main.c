#include <avr/io.h>
#include <stdio.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "prime.h"

int main() {
	uart_init();
	sei();

	app_prime(2000);

	while(1);
	return 0;
}
