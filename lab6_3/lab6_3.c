#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcdFunc.h"
#define MYUBRR (8000000 / 16 / 9600 - 1) //Fosc = 8MHz Baud = 9600

void USART_Init(unsigned int burr);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char  *data);

unsigned char ch;
unsigned char buf[16], num1[5],num2[5];
char op, op_idx, equal_idx, res_str;
int i = 0,res;
ISR(USART0_RX_vect){ //수신 완료 인터럽트 서비스 루틴
 
    ch = UDR0;
    // UCSR0B |= 0b00100000;
    while(1){
        if(buf[i] == '\0'){//buf해당index가null일때
            buf[i] = ch; //데이터 삽입
            break;
        }
        if(buf[i]=='+'||'-'||'*'){
            op = buf[i];
            op_idx = i;

        }
        if(buf[i]=='='){
            equal_idx = i;
            UCSR0B |= 0b00100000;

        }
        i++;
    }
    lcd_display_clear();
    lcd_string(buf);

    i = 0;
}

ISR(USART0_UDRE_vect){ //전송 데이터 레지스터 빔 인터럽트 서비스 루틴
    lcd_display_clear();
    for(int i=0; i<op_idx;i++)
        num1[i]=buf[i];
    // num1[op_idx]='\0';

    for(i = op_idx+1; i < equal_idx; i++)
        num2[i] = buf[i];
    // num2[i+1]='\0';

    if(op=='+') res = atoi(num1) + atoi(num2);
    else if(op == '-') res = atoi(num1)-atoi(num2);
    else if(op == '*') res = atoi(num1)*atoi(num2);

    sprintf(res_str,"%d",res);
    lcd_string(res_str);


    buf[0]='\0';
    // UDR0 = buf;
    UCSR0B &= 0b11011111;
}

int main(){
    SREG = 0x80; //전역인터럽트 인에이블
    lcd_init();
	USART_Init(MYUBRR);

	while(1);
}

void USART_Init(unsigned int ubrr){
	UBRR0H = 0; 
	UBRR0L = (unsigned char)ubrr; //51
	UCSR0A = 0x00;			
	UCSR0B = 0b10011000; 	//RXCIE=0, RXEN0 = 1, TXEN0 = 1 USART0 송수신부 인에이블
	UCSR0C = 0b10000110;	//비동기, 패리티없음, 정지비트=1, 8비트
}

// unsigned char USART_Receive(void){
// 	while(!(UCSR0A & (0b10000000))); //RXC0=1?,수신완료시까지반복
    
// }

// void USART_Transmit(unsigned char  *data){
// 	while(!(UCSR0A & (0b00100000))); //UDRE0=1?,전송데이터레지스터빔발생까지반복
// 	UDR0 = data; //데이터 송신
// }

// #include <avr/io.h>
// #include "lcdFunc.h"
// #include <avr/interrupt.h>
// #include <util/delay.h>

// int i=0;
// int j=0;
// unsigned char re;
// unsigned char buffer[4];

// void usart_init(void)
// {
// 	UBRR0H = 0x00;
// 	UBRR0L = 51;
// 	UCSR0A = 0x00;
// 	UCSR0B = 0b11111000;
// 	UCSR0C = (3<<UCSZ1);

// }
// ISR(USART0_RX_vect){	//수신
// 	buffer[i++] = UDR1;
// 	UCSR1B |= 0b00100000;
// 	if(i==2){
// 		if(buffer[1]=='+'){
// 			re=buffer[0]+buffer[2];
// 		}
// 		else if(buffer[1]=='-'){
// 			re=buffer[0]-buffer[2];
// 		}
// 		else if(buffer[1]=='*'){
// 			re=buffer[0]*buffer[2];
// 		}
// 	}
// }

// ISR(USART0_UDRE_vect){	//
// 	UDR1 = re;
// 	UCSR1B = 0b11011111;
// }
// ISR(USART0_TX_vect){	//전송
// 	UCSR1B |= 0b10000000;
// 	for(j=0; j<4; j++){
// 	UDR1 = buffer[j];
// 	}
// 	if(j==4){
// 		UDR1 = re;
// 	}
// }
// int main(void)
// {
// 	SREG = 0x80;
// 	usart_init();
// 	while(1);
// }
