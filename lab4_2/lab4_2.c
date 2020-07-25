#include <avr/io.h>
#include <avr/interrupt.h>

int loop;

int main(void){
	DDRE = 0x04; //PE2 출력
	TCCR2 = 0b00011100; //CTC 모드, OC2 토글, 분주비 256
	OCR2 = 31; //클럭 31개 2s00번
				//반복하여 200msec가 나오도록 함
	TCNT2 = 0x00;
    PORTE = 0x04;
	while(1){
		for(loop=1; loop<=200; loop++){ //31개 200번 반복 시 0.2초
			while(!(TIFR & 0x80));
			TIFR |= 0x80;
            TCNT2 = 0x00;
		}
        PORTE ^= 0x04;
	}	
}
