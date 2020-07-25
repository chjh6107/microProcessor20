#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "txt_lcd.h"
#define F_CPU 8000000UL

ISR(ADC_vect){
    int ADval;
    float temp;
	char msg[16];


    ADval = ADCL | ADCH<<8;
    temp = (((float)ADval / 1024 * 3.3) -0.5 ) * 100;
    lcd_display_position(1, 10);
    sprintf( msg, "%02.1f", temp );

    lcd_string(msg);

}

int main(){
    MCUCR = 0x80;
    XMCRA = 0x44;
    XMCRB = 0x80;

    lcd_init();
    lcd_command(0x0e); //blank off
	ADMUX = 0b00000010; //VREF = AREF,ADLAR=0하여 LSB로 10bit 사용, ADC2 단극성입력
    ADCSRA = 0b11001111; //A/D인에이블, 분주비128
    SREG = 0x80;
    _delay_ms(5);
	
	lcd_display_position(1, 1);
    lcd_string("Temp(C):");
    while(1){
		ADCSRA |= 0b01000000;			//conversion 시작          
        _delay_ms(500);  
    }
}
