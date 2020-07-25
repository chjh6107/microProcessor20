#include <avr/interrupt.h>
#include <util/delay.h>
#include "txt_lcd.h"

unsigned char rxd(void)
{
	while(!(UCSR0A & 0b10000000)) ; // ������ ���� ���
	return UDR0;
}

void txd(unsigned char ch)
{
	while(!(UCSR0A & 0b00100000)) ; // UDR empty ���
	UDR0 = ch;
}

int main(void)
{
	unsigned char ch;

	lcd_init();  			// LCD �ʱ�ȭ
	lcd_display_position(1,1);
	lcd_string("UART test");

	UCSR0A = 0x00;  	// RXCIE0=TXEN= RXEN=1
	UCSR0B = 0b00011000;	
	// �񵿱� ���, �и�Ƽ ����, ������ ��Ʈ : 8��Ʈ, ������Ʈ : 1��Ʈ
	UCSR0C = 0b00000110; 	
	UBRR0H = 0;
	UBRR0L = 51;	// fosc=8MHz, BAUD=9600bps

	lcd_display_position(2,1);
	while(1) {
		ch = rxd();
		lcd_data(ch);
		txd(ch);
	}
}
