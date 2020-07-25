#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "txt_lcd.h"
//timer0, 비반전고속PWM, 122Hz, 12~24% duty cycle
double ocrDouble = 29.72;
double val = 0.0;
ISR(INT4_vect){

    val+=0.1;
    ocrDouble += 2.56; // 1% 증가
    OCR0 = (int)ocrDouble;
    //OCR1A = OCR0;
    char msg[20];
    lcd_display_position(2,1);

    	sprintf(msg, "H:%.1lfms ", val);
	lcd_string(msg);
    if(ocrDouble>63){ //duty cycle이 약 24%일때 되돌림
        ocrDouble = 29.72; //약 12%
        val = 0.0;
    }
    _delay_ms(100);
}

int main(){
    DDRB = 0x20; //PB5(OC1A)출력

    TCCR0 = 0b01101110; //FastPWM모드, 비반전비교출력모드, 분주비256
                        //Foc0 = 8MHz / 256 * 256 = 122Hz;
    OCR0 = 0;
    TCNT0 = 0x00;

    // TCCR1A = 0b01000011;
    // TCCR1B = 0b00011100; 
    // OCR1A=0;
    
    EIMSK = 0b00010000; //INT4 인에이블
    EICRB = 0x00;       //INT4 Low레벨에서 인터럽트요구
    SREG = 0x80;        //전역 인터럽트 인에이블

    lcd_init();
	lcd_string("ATmega128_PWM_Servo");
	PORTB = 0x20; //PB5(OC1A)출력
	while(1);
}