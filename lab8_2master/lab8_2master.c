#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "txt_lcd.h"

void TWI_master_transmit(unsigned char addr, unsigned char data){
	TWCR = 0xa4;	                        //TWI 시작
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x08));
	TWDR = addr <<1;	                    //SLA+W: 슬레이브 주소 + 라이트(0)
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x18));
	TWDR = data;	                        //데이터 전송
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x28));
	TWCR = 0x94;	                        //TWI 종료
}

unsigned char TWI_master_receive(unsigned char addr){
	unsigned char data;

	TWCR = 0xa4;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x08));
	TWDR = (addr << 1) | 1;	//SLA+R : 슬레이브 주소 + 리드(1)
	TWCR = 0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x40));
	TWCR=0x84;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x58));
	data = TWDR;
	TWCR = 0x94;

	return data;
}

ISR(INT4_vect){	
    unsigned char data[20] = "abc123 xYz(#$) Ulsan";
    int i;

    lcd_display_position(1,1);
    for(i=0; i<20; i++){
        TWI_master_transmit(0x0b,data[i]);	//마스터 전송
        lcd_data(data[i]);
        _delay_ms(10);
    }

    lcd_display_position(2,1);

    for(i=0; i<20; i++){
        data[i] = TWI_master_receive(0x0b);	//마스터 수신
        lcd_data(data[i]);
        _delay_ms(10);
    }
}

int main(void){
	DDRE = 0x00;

	lcd_init();	

	TWBR = 2;
	EIMSK = 0b00010000; //INT4 enable
	EICRB = 0b00000000;
	SREG = 0x80;

	while(1);
}
