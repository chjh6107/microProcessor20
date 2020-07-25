#include <avr/io.h>
//timer2, 반전PCPWM, 1.96KHz, 75% duty cycle ***PB7***
int main(){
	DDRB = 0x80; //PB7(OC2)출력

	TCCR2 = 0b01110010; //PCPWM모드,반전비교출력모드,분주비 8
						//foc2 = 8MHz / 2 * 8 * 255 = 1.96 Hz
	OCR2 = 191;			//duty cycle = 75/100 = (OCR2+1)/256 -> 191
	TCNT2 = 0x00;

	PORTB = 0x80;

	while(1);
}
