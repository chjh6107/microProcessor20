#include<avr/io.h>
#include<util/delay.h>
#include"txt_lcd.h"
#include<avr/interrupt.h>
#define F_CPU 8000000UL

unsigned char str[10];
unsigned char inbuf[100];
volatile int n=0;
unsigned int val = 0;
volatile int EndOfLine = 0;

void usart_init(void)
{
	UBRR0H = 0x00;
	UBRR0L = 51;
	UCSR0A = 0x00;
	UCSR0B = 0b10110000;
	UCSR0C = 0b00000110;
	_delay_ms(300);
}

ISR(USART0_RX_vect)
{
	inbuf[n] = UDR0; 
	inbuf[n+1] = 0;
	if(inbuf[n]==0x0D) EndOfLine = 1;
	UDR0 = inbuf[n++];
}

int main()
{
	usart_init();
	lcd_init();
	
	DDRB = 0b11110111;
	PORTB = 0x10;
	SPCR = 0x50;
	SPSR = 0x00;
	SREG = 0x80;

while(1){
    if(EndOfLine) {

		sscanf(inbuf,"%d",&val);
		sprintf(str,"%4d",val);
		
		PORTB &= 0b11101111;	//cs=0
		
		SPDR = (val>>8)|0x30;
		while(!(SPSR & (1<< SPIF)));
		SPDR = val&0xFF;
		while(!(SPSR & (1<< SPIF)));
		
		PORTB |= 0b00010000;	//cs=1
		PORTB &= 0b11011111;	//ldac=0
		PORTB |= 0b00100000;	//ldac=1
		
		lcd_string(str);
		lcd_cursor_home();
		lcd_display_position(1,1);
       
	    EndOfLine = 0; n=0;
    }
	}
}
