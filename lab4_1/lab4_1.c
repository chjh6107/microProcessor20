#include <avr/io.h>

int loop;

int main(void){
	DDRE = 0x04; // PE2 출력
	TCCR0 = 0b00000110; // normal 모드, OC0 차단(범용IO포트동작), 분주비 256
	TCNT0 = 225; //31250개 카운트가 1초이므로 1000을 나누어 클럭 31개라고 
				//가정 후 100번 반복하여 100msec가 나오도록 함

	while(1){
		for(loop=1; loop<=100; loop++){ //31개 100번 반복 시 0.1초
			while(!(TIFR & 0b00000001));
			TIFR |= 0b00000001; //TOV0을 1로 라이트하여
								//다음 번 오버플로우 체크 대비
			TCNT0 = 225; //256-225 = 31
		}
		if(PORTE == 0x04) PORTE = 0x00; //점등 상태이면 소등
		else //소등 상태이면 다시 점등
		PORTE = 0x04;
	}		
}
