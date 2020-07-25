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

	ADMUX = 0b00000010; //VREF = AREF,ADLAR=0�Ͽ� LSB�� 10bit ���, ADC2 �ܱؼ��Է�
	ADCSRA = 0b10000111; //A/D�ο��̺�, ���ֺ�128
	
	lcd_string("Temp(C):");

	while(1) {
		ADCSRA |= 0b01000000;			//conversion ����
		while(!(ADCSRA & 0b00010000));  //ADIF �÷��װ� 1�̵ɶ��������
        
	    //ADval = (int)ADCL + ((int)ADCH << 8);
        ADval = ADCL | ADCH<<8;
		temp = (((float)ADval/1024*3.3) -0.5) * 100;
        
		lcd_display_position(1, 10);
		sprintf(msg, "%02.1f", temp);
        lcd_string(msg);
		_delay_ms(5);
	}
}
