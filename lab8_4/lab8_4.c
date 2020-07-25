#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "txt_lcd.h"

void clock_write(unsigned char addr, unsigned char data)
{
	TWCR = 0xa4;	//TWI 시작
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x08));
	TWDR = 0xD0;
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x18));
	TWDR = addr;
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x28));
	TWDR = data;	//데이터 전송
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x28));
	TWCR = 0x94;	//TWI 종료
	_delay_ms(10);
}

unsigned char clock_read(unsigned char addr)
{
	unsigned char data;

	TWCR = 0xa4;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x08));
	TWDR = 0xD0;
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x18));
	TWDR = addr;
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x28));
	TWCR = 0xa4;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x10));
	TWDR = 0xD1;
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x40));
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x58));
	data = TWDR;

	TWCR = 0x94;
	_delay_ms(10);

	return data;
}

void Clock_set(int yy, int mm, int dd, int hh, int min, int ss, int h12h24)
{
	unsigned char data;

	tbuf[0] = (ss/10) << 4 | (ss%10);
	tbuf[1] = (min/10) << 4 | (min%10);
	tbuf[2] = (hh/10) << 4 | (hh%10);
	tbuf[3] = 0;
	tbuf[4] = (dd/10) << 4 | (dd%10);
	tbuf[5] = (mm/10) << 4 | (mm%10);
	tbuf[6] = (yy/10) << 4 | (yy%10);
	ds1307_SetTime(SlaveAddr);
}

void Clock_read()
{
	int n, yy, mm, dd, hh, min, ss, day;

	ds1307_ReadTime(SlaveAddr);
	ss = (tbuf[0]>> 4)*10 + (tbuf[0] & 0x0F) ;
	min = (tbuf[1]>> 4)*10 + (tbuf[1] & 0x0F);
	hh = (tbuf[2]>> 4)*10 + (tbuf[2] & 0x0F);
	day = tbuf[3] ;
	dd = (tbuf[4]>> 4)*10 + (tbuf[4] & 0x0F) ;
	mm = (tbuf[5]>> 4)*10 + (tbuf[5] & 0x0F) ;
	yy = (tbuf[6]>> 4)*10 + (tbuf[6] & 0x0F) ;
}

int main(){


	return 0;
}