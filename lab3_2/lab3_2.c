#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT4_vect){ //INT4 인터럽트 처리 루틴
    PORTB=0xFF; //모든 LED 점등
}

int main(){
    DDRE = 0x00;
    DDRB = 0xFF;

    EIFR = 0x80; //외부 Interrupt INT4 Enable
    EIMSK = 0b00010000; //INT4 Interrupt Enable
    SREG = 0x80; ////전역 Interrupt Enable
    EICRB = 0x00; //INT4가 low 신호 입력 시 Interrupt request

    while(1){
        PORTB = 0x00; //모든 LED 소등
        }
}