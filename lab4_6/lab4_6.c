#include <avr/io.h>
#include <avr/interrupt.h>

int loop;

ISR(TIMER0_COMP_vect){ //부저 출력비교매치 인터럽트 처리루틴
	if(loop < 100)
		loop++;
	else{
		loop = 0;
		PORTB ^= 0b00000001;
	}
    TCNT0 = 0;
}

ISR(TIMER2_COMP_vect){ //LED 출력비교매치 인터럽트 처리루틴
	if(loop < 200)
		loop++;
	else{
		loop = 0;
		PORTE ^= 0b00000100;
	}
    TCNT2 = 0;
}
int main(void){
	DDRE = 0x04; //PE2 출력
	DDRB = 0xff; //PB0 출력 설정

	TCCR0 = 0b00011110; //CTC 모드, OC0 토글, 분주비 256
	TCCR2 = 0b00011100; //CTC 모드, OC2 토글, 분주비 256
	OCR0 = 31; OCR2 = 31;

	TCNT0 = 0; TCNT2 = 0;
	TIMSK = 0x82; // OCIE0,2 =1, 출력비교매치 인터럽트 인에이블
	SREG = 0x80;
	PORTB = 0x00;
	PORTE = 0x00;

	while(1);

}