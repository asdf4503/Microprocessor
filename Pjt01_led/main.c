#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main() {
	led_init();

	while(1) {
		PORTL = 0x7f;
      	_delay_ms(150);
		PORTL = 0xbf;
      	_delay_ms(150);
      	PORTL = 0xdf;
      	_delay_ms(150);
      	PORTL = 0xef;
      	_delay_ms(150);
      	PORTL = 0xf7;
      	_delay_ms(150);
      	PORTL = 0xfb;
      	_delay_ms(150);
      	PORTL = 0xfd;
      	_delay_ms(150);
      	PORTL = 0xfe;
      	_delay_ms(150);
      	
		PORTL = 0xff;
      	_delay_ms(150);
		
		PORTL = 0xfe;
      	_delay_ms(150);
		PORTL = 0xfd;
      	_delay_ms(150);
		PORTL = 0xfb;
      	_delay_ms(150);
		PORTL = 0xf7;
      	_delay_ms(150);
		PORTL = 0xef;
      	_delay_ms(150);
		PORTL = 0xdf;
      	_delay_ms(150);
		PORTL = 0xbf;
      	_delay_ms(150);
		PORTL = 0x7f;
      	_delay_ms(150);
	}	
	
	return 0;
}
