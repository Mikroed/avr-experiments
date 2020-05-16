/*
 * attiny2313-timer-0-normal-mode-00.c
 *
 * Created: 16.05.2020 16:55:37
 * Author : mikroed
 * 
 * HF: 0xDF
 * LF: 0x42
 * EF: 0xFF
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

ISR (TIMER0_OVF_vect) {
	PORTD ^= (1 << PIND0);
}

ISR (TIMER0_COMPA_vect) {
	PORTD ^= (1 << PIND1);
}

ISR (TIMER0_COMPB_vect) {
	PORTD ^= (1 << PIND2);
}

int main(void)
{
	DDRD   = 0x17;
	DDRB   = 0x02;

	PORTD  = 0x00;
	PORTB  = 0x00;

	OCR0A  = 205;
	OCR0B  = 155;

	TCCR0B = (1 << CS02) | (1 << CS00);
	TIMSK  = (1 << TOIE0) | (1 << OCIE0A) | (1 << OCIE0B);

	sei();

	while (1)
	{
		sleep_mode();
	}
}

