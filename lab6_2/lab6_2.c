#include <avr/io.h>
#include <util/delay.h>
#include "lcdFunc.h"
#define MYUBRR (8000000 / 16 / 9600 - 1) //Fosc = 8MHz Baud = 9600

void USART_Init(unsigned int burr);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char  *data);

int main(){
	unsigned char ch;
    char msg[20];

    lcd_init();
	USART_Init(MYUBRR);

    ch = USART_Receive();
    sprintf(msg,"I RECEIVED %c!",ch);
    lcd_string(msg);
    USART_Transmit(ch);
	while(1);
}

void USART_Init(unsigned int ubrr){
	UBRR0H = 0; 
	UBRR0L = (unsigned char)ubrr; //51
	UCSR0A = 0x00;			
	UCSR0B = 0b00011000; 	//RXEN0 = 1, TXEN0 = 1 USART0 송수신부 인에이블
	UCSR0C = 0b10000110;	//비동기, 패리티없음, 정지비트=1, 8비트
}

unsigned char USART_Receive(void){
	while(!(UCSR0A & (0b10000000))); //RXC0=1?,수신완료시까지반복
    return UDR0; //입력받은 데이터 반환
}

void USART_Transmit(unsigned char  *data){
	while(!(UCSR0A & (0b00100000))); //UDRE0=1?,전송데이터레지스터빔발생까지반복
	UDR0 = data; //데이터 송신
}

