#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "txt_lcd.h"

void at24c16_write(unsigned char addr, unsigned char data){
	TWCR = 0xa4;		//TWI 시작
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x08));
	TWDR = 0xa0;//at24c16 주소 (라이트 주소)
	TWCR = 0x84;		//전송
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x18));
	TWDR = addr;		//라이트할 데이터 주소
	TWCR = 0x84;		//전송
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x28));
	TWDR = data;		//라이트할 데이터
	TWCR = 0x84;		//전송
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x28));
	TWCR = 0x94;		//TWI 종료
	_delay_ms(10);
}

unsigned char at24c16_read(unsigned char addr){
	unsigned char data;

	TWCR = 0xa4;		//TWI 시작
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x08));
	TWDR = 0xa0;		//at24c16 주소 (라이트 주소)
	TWCR = 0x84;		//전송
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x18));
	TWDR = addr;		//리드할 데이터 주소
	TWCR = 0x84;		//전송	
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x28));
	TWCR = 0xa4;		//TWI 시작
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x10));
	TWDR = 0xa1;		//at24c16 주소 (리드 주소)
	TWCR = 0x84;		//전송	
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x40));
	TWCR = 0x84;		//전송	(at24c16로부터 데이터 리드)
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x58));
	data = TWDR;
	TWCR = 0x94;		//TWI 종료

	return data;
}

int main(void){
	unsigned char dataW=0,dataR;
	char msgW[16], msgR[16];
	int i;

	lcd_init();

	TWBR = 32; // 8MHz / 16 + 2 * 32 * 1 = 100KHz
	TWSR = 0x00;

	for(i=0; i< 2048; i++){
		lcd_string("Write EEPROM");
		lcd_display_position(2, 1);
		at24c16_write(i, dataW);	//at24c16  
		sprintf(msgW, "%04x: %x",i,dataW++);

		lcd_string(msgW);

		_delay_ms(100);
		lcd_clear();
		lcd_string("Read EEPROM");
		lcd_display_position(2, 1);
		dataR = at24c16_read(i);
		sprintf(msgR, "%04x: %x",i,dataR);

		lcd_string(msgR);
		_delay_ms(100);
		lcd_clear();
	}
}

