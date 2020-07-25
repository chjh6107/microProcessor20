#include <avr/io.h>
#include <util/delay.h>
#include "txt_lcd.h"

void SPI_master(unsigned char data){
    PORTB &= 0xfe;          //SS=0, 슬레이브 선택
    SPDR = data;
    while(!(SPSR & 0x80));  //SPI 전송 완료 대기
    PORTB |= 0x01;          //SS=1 전송 종료
}

int main(){
    unsigned char data[14]="1234567890abc ";
    int i;

    lcd_init();

    DDRB = 0b00000111;      //MISO입력, MOSI출력, SCK출력, SS출력

    PORTB = 0x00;           
    SPCR = 0x5c;            //SPI인에이블,마스터모드설정,SCK fosc/4

    SPSR = 0x00;

    lcd_string("SPI Master ...");
    lcd_display_position(2,1);
    for(i = 0; i < 14; i++){
        SPI_master(data[i]);
        lcd_data('>');
    }
}
