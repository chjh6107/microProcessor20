#include <avr/io.h>
#define F_CPU 8000000UL
#define MYUBRR (8000000 / 16 / 9600 - 1) //Fosc = 8MHz Baud = 9600

void USART_Init(unsigned int burr);
void USART_Transmit(unsigned char  *data);

int main(){
	unsigned char str[20] = "1234567890 abc ";

	USART_Init(MYUBRR);

	for(int i = 0; i<20; i++)
		USART_Transmit(str[i]);
	while(1);
}

void USART_Init(unsigned int ubrr){
	UBRR0H = 0; 
	UBRR0L = (unsigned char)ubrr; //51
	UCSR0A = 0x00;			
	UCSR0B = 0b00001000; 	//TXEN0 = 1 USART0 송신부 인에이블
	UCSR0C = 0b10000110;	//비동기, 패리티없음, 정지비트=1, 8비트
}

void USART_Transmit(unsigned char  *data){
	while(!(UCSR0A & (0b00100000))); //UDRE0=1?,전송데이터레지스터빔발생까지반복

	UDR0 = data; //데이터 송신
}

