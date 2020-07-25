#include <avr/io.h>
//timer0, 비반전고속PWM, 30Hz, 25% duty cycle
int main(){
	DDRB = 0x10; //PB4(OC0)출력

	TCCR0 = 0b01101111; //FastPWM모드,비반전비교출력모드,분주비1024
                        //Foc0 = Fclk / N * 256
						//foc0 = 8MHz / 1024 * 256 = 30.5 Hz

                        //duty cycle = ((OCR0 + 1) / 256) * 100
	OCR0 = 63;			//duty cycle = 25/100 = (OCR0+1)/256 -> 63
	TCNT0 = 0x00;

	PORTB = 0x10;

	while(1);
}
