#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//timer2, 반전PCPWM, 1.96KHz, 75% duty cycle ***PB7***
//OCR2 = 25(10%)->76(30%)->127(50%)->178(70%)->229(90%)
ISR(INT4_vect){
    OCR2 += 51; //인터럽트 발생 시 마다 duty cycle 약 20% 씩 증가

    if(OCR2 > 229) OCR2 = 25; //duty cycle이 약 90%일 시 10%로 되돌림
    _delay_ms(200); 
}

int main(){
	DDRB = 0x80; //PB7(OC2)출력

	TCCR2 = 0b01110010; //PCPWM모드,반전비교출력모드,분주비 8
						//foc2 = 8MHz / 2 * 8 * 255 = 1.96 Hz
	OCR2 = 25;			//duty cycle = 25 약 10%
	TCNT2 = 0x00;

    EIMSK = 0b00010000; //INT4 인에이블
    EICRB = 0x00;       //INT4 Low레벨에서 인터럽트요구
    SREG = 0x80;        //전역 인터럽트 인에이블

	PORTB = 0x80;

	while(1);
}
