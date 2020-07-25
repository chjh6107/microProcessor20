#include <avr/io.h>
#include <util/delay.h>

int main(void){
//	int hexToFND[16] = {0xC0, 0xF9, 0xA4, 0xB0,
//						0x99, 0x92, 0x82, 0xF8,
//						0x80, 0x90, 0x88, 0x83,
//						0xC6, 0xA1, 0x86, 0x8E};//CA type 8bit, included dot 
	int hexToFND[16] = {0x40, 0x79, 0x24, 0x30,
						0x19, 0x12, 0x02, 0x78,
						0x00, 0x10, 0x08, 0x03,
						0x46, 0x21, 0x06, 0x0E};//CA type 7bit, not included dot

	unsigned char a, b, res;
	DDRA = 0x00; // op. A
	DDRB = 0x00; // op. B
	DDRC = 0xFF; // Upper nibble seg.
	DDRD = 0xFF; // Lower nibble seg.
	DDRE = 0x00; // Calc dipsw.

	while(1){
		a = ~PINA;
		b = ~PINB;

		switch(~PINE & 0x0F){ // + - x % and or not xor nor nand
			case 0x0 : // +
				res = a + b;
				PORTC = hexToFND[res >> 4];
				PORTD = hexToFND[res & 0x0F];
				break;
			case 0x1 : // -
				res = a - b;
				PORTC = hexToFND[res >> 4];
				PORTD = hexToFND[res & 0x0F];
				break;
			case 0x2 : // *
				res = a * b;
				PORTC = hexToFND[res >> 4];
				PORTD = hexToFND[res & 0x0F];
				break;
			case 0x3 : // %
				res = a / b;
				PORTC = hexToFND[res >> 4];
				PORTD = hexToFND[res & 0x0F];
				break;
			case 0x4 : //and
				PORTC = hexToFND[(a & b) >> 4];
				PORTD = hexToFND[(a & b) & 0x0F];
				break;
			case 0x5 : //or
				PORTC = hexToFND[(a | b) >> 4];
				PORTD = hexToFND[(a | b) & 0x0F];
				break;
			case 0x6 : //not
				PORTC = hexToFND[(~ a) & 0x0F]; //calc. the lower 4bit of a
				PORTD = hexToFND[(~ b) & 0x0F]; //calc. the lower 4bit of b
				break;
			case 0x7 : //xor
				PORTC = hexToFND[(a ^ b) >> 4];
				PORTD = hexToFND[(a ^ b) & 0x0F];
				break;
			case 0x8 : //nor
				PORTC = hexToFND[((~(a | b)) & 0xF0) >> 4];
				PORTD = hexToFND[(~(a | b)) & 0x0F];
				break;
			case 0x9 : //nand
				PORTC = hexToFND[((~(a & b)) & 0xF0) >> 4];
				PORTD = hexToFND[(~(a & b)) & 0x0F];
				break;
			default:
				;
		}
	}
}
