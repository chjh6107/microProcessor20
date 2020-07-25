#include <avr/io.h>
#include <avr/interrupt.h>

int loop;

ISR(TIMER2_OVF_vect){
	if(loop < 1000) loop++;
	else{
		loop = 0;						//loop가 한계에 다다르면 0으로 돌아옴
		PORTE = ~PORTE & 0b00000100;	//점멸할 수 있도록 0, 1을
	}									//번갈아가면서 저장
	TCNT2 = 225;
}

int main(void){
	DDRE = 0x04; //PE2 출력
	TCCR2 = 0b00000100; // normal 모드, OC2 차단, 분주비 256
	TCNT2 = 225;
	TIMSK = 0b01000000;	//TOIE2=1, 오버플로우 인터럽트인에이블
	SREG = 0x80;		//전역 인터럽트 인에이블
	PORTE = 0x04;
	while(1);
}
