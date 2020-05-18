/*	Author: Dumitru Chiriac lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM (double frequency) {
	static double current_frequency;
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; }
		else {TCCR3B |= 0x03; }

		if (frequency < 0.954) {OCR3A = 0xFFFF; }

		else if (frequency > 31250)  {OCR3A = 0x0000;}
		else {OCR3A = (short) (8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}
void PWN_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    PWM_on();
    unsigned char temp;
    double c4 = 261.63;
    double d4 = 293.66;
    double e4 = 329.63;
    while (1) {
	temp = ~PINA;
	if (temp == 0x01)
		set_PWM(c4);
	else if (temp == 0x02)
		set_PWM(d4);
	else if (temp == 0x04)
		set_PWM(e4);
	else
		set_PWM(0);
    }    
    return 1;
}
