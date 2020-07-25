#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
    int loop1 = 0, loop2 = 0;
	DDRE = 0x04; //PE2 출력
	DDRB = 0x01; //PB0 출력 설정

	TCCR0 = 0b00000110; // normal 모드, OC0 차단(범용IO포트동작), 분주비 256
	TCCR2 = 0b00000100; // normal 모드, OC2 차단(범용IO포트동작), 분주비 256
	TCNT0 = 225;
	TCNT2 = 225;

	while(1){
        if(TIFR & 0b01000000){ //31개 200번 반복 시 0.2초 //LED
            loop1++;
            if(loop1==200){ //0.2초가 되면 점등 밑 소등
                PORTE ^= 0x04;
                loop1=0;
            }
            TCNT2 = 225;
            TIFR |= 0b01000000;
        }
        else if(TIFR & 0b00000001){ //31개 100번 반복 시 0.1초
            loop2++;
            if(loop2==100){ //0.1초가 되면 소리 키고 끔
                PORTB ^= 0x01;
                loop2=0;
            }
            TCNT0 = 225;
            TIFR |= 0b00000001;
        }        
	}	
}
