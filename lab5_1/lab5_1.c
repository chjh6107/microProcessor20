#include <avr/io.h>
#include <util/delay.h>


int main()
{
    unsigned char tmp;      //ADCH만 불러왔을때의 에러를 대비해 ADCL을 저장할 변수
	DDRB = 0xFF;            //PORTB 출력
	DDRF &= 0xFE;           //PF0입력
	ADMUX = 0b01100000;     //VREF = AVCC,ADLAR=1하여 MSB로 10bit 사용, ADC0 단극성입력
	ADCSRA = 0b10000111;    //A/D인에이블, 분주비128

	while(1) {
		ADCSRA |= 0b01000000;			//conversion 시작
		while(!(ADCSRA & 0b00010000));  //ADIF 플래그가 1이될때까지대기
		ADCSRA |= 0b00010000;           //또 사용하기 위해 1을 써 ADIF=0으로 만듦

        tmp = ADCL;         //혹시모를 에러를 대비해 ADCL 불러옴
		PORTB = ADCH;       //상위8비트를 LED에 출력
		_delay_ms(100);     
	}
}
