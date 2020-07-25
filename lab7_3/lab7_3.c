#include<avr/io.h>
#include<avr/delay.h>

void sendmsg(unsigned char cmd, unsigned char data);
int main(){
	unsigned char n = 0;
	unsigned char ch1,ch2,ch3,ch4;

	DDRB = 0b00000111;
	SPCR = 0x5c;
	SPSR = 0x00;

	sendmsg(0x09, 0x0F);	
	sendmsg(0x0A, 0x0F);
	sendmsg(0x0B, 0x03);	
	sendmsg(0x0C, 0x01);	
	
	sendmsg(0x0F, 0x01);	
	_delay_ms(1000);
	sendmsg(0x0F, 0x00);	

	while(1){
		n++;
		ch1 = n/100;
		ch2 = (n%1000)/100;
		ch3 = (n%100)/10;
		ch4 = n%10;
		sendmsg(1,ch1);
		sendmsg(2,ch2);
		sendmsg(3,ch3);
		sendmsg(4,ch4);

		_delay_ms(500);
	}
	return 0;
}

void sendmsg(unsigned char cmd, unsigned char data){
	PORTB &= 0xfe;
	SPDR = cmd;
	while(!(SPSR&(1<<SPIF)));
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
	PORTB|=0x01;
}
