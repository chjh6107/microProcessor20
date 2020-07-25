#include<avr/io.h>
#include<util/delay.h>
#include"txt_lcd.h"

int main(void){
	
	unsigned char str[5];
	int val = 0;
	
	lcd_init();
	DDRB = 0b00111111;
	SPCR = 0x50;
	lcd_string("Hello AVR");

	while(1){
		if(val > 4095) val= 0;
		lcd_display_position(2,1);

		sprintf(str,"%04x",val);
		lcd_string(str);


		PORTB &= 0b11101111;	//cs=0
		SPDR = 0x30 | (val>>8);
		while(!(SPSR & (1<< SPIF)));
		SPDR = val&0xFF;
		while(!(SPSR & (1<< SPIF)));
		PORTB |= 0b00010000;	//cs=1
		PORTB &= 0b11011111;	//ldac=0
		PORTB |= 0b00100000;	//ldac=1
		val += 0x200;		
		_delay_ms(100);
	}

}
