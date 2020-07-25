#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void ex1_1();
void ex1_2();
void ex1_3();

ISR(INT4_vect){
PORTB += 0x1; //1을 더함
}

int main(){
    DDRB = 0xFF;
    DDRE = 0x00; //PORTE의 INT4~INT7 input

    PORTB = 0x00;

    EIFR = 0x80; //외부 Interrupt INT4 Enable
    EIMSK = 0b00010000; //INT4 Interrupt Enable
    SREG = 0x80; //전역 Interrupt Enable

     ex1_1();
    // ex1_2();
    //ex1_3();
    while(1);

}

void ex1_1(){
    EICRB = 0b00000011; //INT4 상승에지에서 비동기적으로 인터럽트 요구
}

void ex1_2(){
    EICRB = 0b00000010; //INT4 하강에지에서 비동기적으로 인터럽트 요구
}

void ex1_3(){
    EICRB = 0b00000001; //INT4의 논리적 변경 시 인터럽트 요구
}
