// © 2011. Ravi Teja Gudapati. All rights reserved.

#include <driv/uart0/uart0.h>
#include "driv/cpu/cpu.h"
#include <driv/rs485/rs485.h>
#include <driv/rs4851/rs4851.h>
#include <driv/delay/delay.h>

int main(void) {
	cpu_init();

	uart0_init(Uart_Baudrate_4800);
	delay_init();

	// Print start
	uart0_putc('s');
	uart0_print_newline();

	rs485_init(1000000);
	// TODO rs4851_init(1000000);

	// Print finish
	uart0_putc('k');
	uart0_print_newline();

	while(1) {
		// rs485_putc('x');
		// TODO rs4851_putc('y');
		delay_ms_workhorse(500);

		int16_t ch = rs485_getc();
		if(ch > 0 && ch < 0xFF) {
			uart0_putc(ch);
		} else {
			uart0_putc('t');
		}
	}
}
