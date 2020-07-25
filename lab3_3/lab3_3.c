#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int counter = 0; //처리루틴 진입 시 카운트를 위해 global 선언
ISR(INT4_vect){
	int i = 0;
	counter++;

	if(counter % 2 == 1){ //첫번째 기능
		while(1){
			SREG = 0x80; //전역 Interrupt enable
			for(i = 0; i < 8; i++){ //LED 0->7
				PORTB = 0x01;
				PORTB = PORTB<<i;
				_delay_ms(125);
			}
		}
	}else{
		while(1){
			SREG = 0x80; //전역 Interrupt enable
			for(i = 0; i < 8; i++){ //LED 7->0
				PORTB = 0x80;
				PORTB = PORTB>>i;
				_delay_ms(125);
			}
		}
	}
}

int main(){
	DDRE = 0x00;
	DDRB = 0xff;

    EIFR = 0x80; //외부 Interrupt INT4 Enable
	EIMSK = 0b00010000; //INT4 Interrupt Enable
	SREG = 0x80; //전역 Interrupt Enable
	EICRB = 0b00000010; //하강 에지

	while(1);
}
