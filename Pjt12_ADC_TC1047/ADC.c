#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>
#include "timer_task.h"
#include "ADC.h"

void adc_init() {
	cbi(DDRF, PF0);
	ADMUX = 0x80 | 0x00;
}

void adc_start() {
	sbi(ADCSRA, ADEN);
	_delay_us(120);
	sbi(ADCSRA, ADIE);
	sbi(ADCSRA, ADSC);
}

ISR(ADC_vect) {
	uint16_t	data;
	char		arg[8];

	data = ADCW & 0x03ff;
	//data = 640;
	cbi(ADCSRA, ADEN);

	sprintf(arg, "%d", data);

	task_tc1047(arg);
}
