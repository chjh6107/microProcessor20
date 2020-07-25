#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"txt_lcd.h"

ISR(SPI_STC_vect){
	lcd_data(SPDR);
}

int main(void){

	lcd_init();
	DDRB = 0b00001000;  //MISO출력, MOSI입력, SCK입력, SS입력
	PORTB = 0x00;
	SPCR = 0xcc;        //SPI인에이블,슬레이브모드설정
	SPSR = 0x00;
	SREG = 0x80;        //전역 인터럽트 인에이블

	lcd_string("SPI Slave ...");
	lcd_display_position(2,1);
	while(1);

}
