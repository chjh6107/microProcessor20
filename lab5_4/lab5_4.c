#include <avr/io.h>
#include <util/delay.h>
#include "txt_lcd.h"
#define F_CPU 8000000UL

int main(){
    int ADval;
    float temp;
	char msg[16];

    MCUCR = 0x80;
    XMCRA = 0x44;
    XMCRB = 0x80;

    lcd_init();
	lcd_command(0x0e); //blank off

	ADMUX = 0b00000010; //VREF = AREF,ADLAR=0하여 LSB로 10bit 사용, ADC2 단극성입력
	ADCSRA = 0b10000111; //A/D인에이블, 분주비128
	
	lcd_string("Temp(C):");

	while(1) {
		ADCSRA |= 0b01000000;			//conversion 시작
		while(!(ADCSRA & 0b00010000));  //ADIF 플래그가 1이될때까지대기
        
	    //ADval = (int)ADCL + ((int)ADCH << 8);
        ADval = ADCL | ADCH<<8;
		temp = (((float)ADval/1024*3.3) -0.5) * 100;
        
		lcd_display_position(1, 10);
		sprintf(msg, "%02.1f", temp);
        lcd_string(msg);
		_delay_ms(5);
	}
}
