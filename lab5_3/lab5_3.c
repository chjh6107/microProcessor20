#include <avr/io.h>
#include <util/delay.h>
#include "lcdFunc.h"

int main(){
	int ADval;		
	float Vin, Vref = 4.0;
	char msg[16];

	lcd_init();

	DDRF &= 0xFE; //PF0입력
	ADMUX = 0b00000000; //VREF = AVCC,ADLAR=0하여 LSB로 10bit 사용, ADC0 단극성입력
	ADCSRA = 0b10000111;//A/D인에이블, 분주비128
	_delay_ms(5);

	while(1){
		// ADCSRA |= 0b01000000;				//conversion 시작
		// while((ADCSRA & 0b00010000) == 0);  //ADIF 플래그가 1이될때까지대기
		// // ADCSRA |= 0b00010000;           	//또 사용하기 위해 1을 써 ADIF=0으로 만듦
		// ADval = (int)ADCL + ((int)ADCH << 8);//ADCH 2bit를 ADC7의 상위비트로 맞출 수 있도록 8번 shift
		// Vref = PINF;						//DC전원에 인가된 값 저장
		// Vin = ((float)ADval * Vref) / 1023.0;	//아날로그 입력 VIN 연산 후 변수 Vin에 저장
		// lcd_display_position(1, 1);			//LCD커서위치를 1행1열로 위치
		// sprintf(msg, "ADC0 = %.2f[V]\0",Vin);
		// lcd_string(msg);					
		// _delay_ms(1000);
		// Vref = PINF;
		ADCSRA = ADCSRA | 0b01000000;
		while((ADCSRA & 0b00010000) == 0);
		ADval = (int)ADCL + ((int)ADCH << 8);
		Vin = (float)ADval * Vref / 1023.0;
		lcd_display_position(1, 1);
		sprintf(msg, "ADC = %.2f[V]", Vin);
		lcd_string(msg);
		_delay_ms(1000);
	}
}
