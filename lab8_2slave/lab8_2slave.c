#include <avr/io.h>
#include <util/delay.h>
#include "txt_lcd.h"

void TWI_slave_transmit(unsigned char addr, unsigned char data){
    TWAR = addr << 1;
    TWCR = 0x44;
    while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0xa8));
	TWDR = data;
	TWCR = 0xc4;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0xc0));
	TWCR = 0xc4;
}

unsigned char TWI_slave_receive(unsigned char addr){
	unsigned char data;	

	TWAR = addr << 1;
	TWCR = 0x44;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x60));
	TWCR = 0xc4;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0x80));
	data = TWDR;
	TWCR = 0xc4;
	while(!(TWCR & 0x80) || ((TWSR & 0xf8) != 0xa0));
	TWCR = 0xc4;

	return data;
}

int main(){
    unsigned char data[16];
    unsigned char trans;
    int i;

    lcd_init();

    TWSR = 0x00;

    while(1){
        for(i=0;i<20;i++){
            data[i] = TWI_slave_receive(0x0b);  //슬레이브 수신
            lcd_data(data[i]);
        }

        lcd_display_position(2, 1);

        for(i=0;i<20;i++){
            if(data[i] >= 'a' && data[i] <= 'z') trans = data[i]-'a'+'A';
            else trans = data[i];

            TWI_slave_transmit(0x0b,trans);     //슬레이브 전송
            lcd_data(trans);
        }
    }


}
