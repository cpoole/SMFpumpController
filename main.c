/*************************************************************
 * Sustainable Microfarms GrowBox Pump control
 * LED pinout
 - LED 0 = PB4
 - LED 1 = PB3
 - LED 2 = PA1
 - LED 3 = PA0
 - LED 4 = PD4
 - LED 5 = PD5
 * Pump pins:
 - Pump one: PB2 (NMOS pump)
 - Pump two: PB1 (relay pump)
 * External push button:
 - PD2
 * Serial pins:
 - RX = PD0
 - TX = PD1 
 **************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <stdbool.h>

#define BAUD 9600               // UART0 baud rate
#define MYUBRR FOSC/16/BAUD-1   // Value for UBRR0 register

void setup();

volatile uint8_t select;
volatile uint8_t scrollIndex = 0;

bool pump_on = true;

int main(void)
{
    ///////////////THE MAIN BODY OF CODE//////////////////
	while(1){
		if(scrollIndex ==0){
			// on for five seconds off for 40
			PORTB |= 1 << PB4;
			PORTB &= (0<<PB3);
			PORTA &= (0<<PA1), (0<<PA0);
			PORTD &= (0<<PD4), (0<<PD5);	
			PORTB |= 1 << PB2;
			_delay_ms(5000);
			PORTB &= (0<< PB2);
			_delay_ms(40000);
		}
		else if(scrollIndex == 1){
			PORTB |= 1 << PB3;
			PORTB |= 1 << PB2;
			_delay_ms(10000);
			PORTB &= (0<< PB2);
			_delay_ms(30000);
		}
		else if(scrollIndex == 2){
			PORTA |= 1 << PA1;
			PORTB |= 1 << PB2;
			_delay_ms(15000);
			PORTB &= (0<< PB2);
			_delay_ms(25000);
		}
		else if(scrollIndex == 3){
			PORTA |= 1 << PA0;
			PORTB |= 1 << PB2;
			_delay_ms(20000);
			PORTB &= (0<< PB2);
			_delay_ms(20000);
		}
		else if(scrollIndex == 4){
			PORTD |= 1<< PD4;
			PORTB |= 1 << PB2;
			_delay_ms(25000);
			PORTB &= (0<< PB2);
			_delay_ms(15000);
		}
		else if(scrollIndex == 5){
			//always on
			PORTD |= 1<< PD5;
			PORTB |= 1<< PB2;
		}
	}
	
	return 0;
}

void setup()
{
	////////////////LED SETUP/////////////////////////////////////////
	// set led pins to outputs
	DDRB |= (1<<DDB4), (1<<DDB3);
	DDRA |= (1<<DDA1), (1<<DDA0);
	DDRD |= (1<<DDD4), (1<<DDD5);
	// initialize them to 5 seconds on 
	PORTB |= (1<<PB4);
	PORTB &= (0<<PB3);
	PORTA &= (0<<PA1), (0<<PA0);
	PORTD &= (0<<PD4), (0<<PD5);
	/////////////////BUTTON INTERRUPT SETUP///////////////////////////
	DDRD &= ~(1<<DDD2);
	PORTD |= (1<<PORTD2);
	EICRA |= (1 << ISC01);	// trigger on any logic change (01: We want to trigger INT0 on the falling edge.)
	EIMSK |= (1 << INT0);
}

ISR(INT0_vect)
{
	scrollIndex = (++scrollIndex) % 5;
}