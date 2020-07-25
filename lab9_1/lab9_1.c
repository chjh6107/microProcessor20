#include <avr/io.h>
//timer0, CTC mode, 31,250Hz, 50% duty cycle
int main(){
	DDRB = 0x10; //PB4(OC0)출력

	TCCR0 = 0b00011011; //CTC모드,OC0토글,분주비32
						//foc0 = Fclk / (2 * N * (OCR0 + 1))
						//foc0 = 8MHz / (2 * 32 * (3 + 1)) = 31.25 KHz
	OCR0 = 3;			
	TCNT0 = 0x00;

	PORTB = 0x10;

	while(1);
}
