#include <avr/io.h>
#include <util/delay.h>
#include "txt_lcd.h"

unsigned char SPI_slave(){
    while(!(SPSR & 0x80));          //데이터전송완료까지대기
    return SPDR;                    //수신데이터변환
}

int main(){
    unsigned char data;
    int i;

    lcd_init();

    DDRB = 0b00001000; //MISO출력, MOSI입력, SCK입력, SS입력
    PORTB = 0x00;
    SPCR = 0x4c;        //SPI인에이블, 슬레이브모드설정
    SPSR = 0x00;

    lcd_string("SPI Slave ...");
    lcd_display_position(2, 1);
    for(i = 0; i < 14; i++){
        data = SPI_slave();
        lcd_data(data);
    }
}
