#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "txt_lcd.h"
//timer0, 비반전고속PWM, 30Hz, 10~100% duty cycle
double ocrDouble = 0.0;
int i = 0;
ISR(INT4_vect){
	i++;
	ocrDouble += 25.55;
	OCR0 = (int)ocrDouble;

	char msg[20];
	lcd_display_position(2,1);

	sprintf(msg, "H:%02dms/10ms [%3d] ", i, i*10);
	lcd_string(msg);

	if(ocrDouble>255){
		ocrDouble=0.0;
		i = 0;
	}
	_delay_ms(100);
}
int main(){
	DDRB = 0xFF;
	
	TCCR0 = 0b01101111; //FastPWM모드,비반전비교출력모드,분주비1024
                        //Foc0 = Fclk / N * 256
						//foc0 = 8MHz / 1024 * 256 = 30.5 Hz
	OCR0 = 0;
	TCNT0 = 0x00;

	EIMSK = 0b00010000; //INT4 인에이블
    EICRB = 0x00;       //INT4 Low레벨에서 인터럽트요구
    SREG = 0x80;        //전역 인터럽트 인에이블

	lcd_init();
	lcd_string("ATmega128_PWM_Servo");
	PORTB = 0x10; //PB4(OC0)출력
	while(1);
}
