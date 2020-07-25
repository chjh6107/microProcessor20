#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<stdio.h>
#define MYUBRR (115200 / 16 / 9600 - 1) //Fosc = 115.2KHz Baud = 9600
unsigned int count = 0;
unsigned char msg[];

void USART_init(unsigned int ubrr);
unsigned char usart_send(unsigned char ch);
ISR(USART0_RX_vect);
ISR(USART0_UDRE_vect);
ISR(INT4_vect);
void USART_String(unsigned char *str);

int main(void){
	unsigned char a[20] = "no people ";
	
	DDRE = 0x00;
	PORTE = 0x10; 
	EIMSK = 0x10;
	EICRB = 0x03; 
    SREG = 0x80; 

	USART_init();
	USART_String(a);

   while(1);
}

void USART_init(unsigned int ubrr){
	UBRR0H = 0;
	UBRR0L = (unsigned char)ubrr;
	UCSR0A = 0x00;
	UCSR0B = 1<<TXEN;
	UCSR0C = 0B00000110;
}

ISR(USART0_RX_vect){

}

ISR(USART0_UDRE_vect){

}
unsigned char usart_send(unsigned char ch){
	while(!(UCSR0A&(1<<UDRE)));
	UDR0 = ch;
}

ISR(INT4_vect){    
	usart_init();
	_delay_ms(50);
	int i = 0;
	count++;
	sprintf(msg, "%d people", count);

	while(1){
		if(msg[i] == '\0')break;
        usart_send(msg[i++]);
       }
}

void USART_String(unsigned char *str){
	int i=0;
	while(1){
		if(str[i] == '\0') break;
		
		usart_send(str[i++]);
	}
}