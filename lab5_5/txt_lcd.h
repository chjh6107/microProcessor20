#define LCD_CS (*(volatile unsigned char*) 0x6400)
#define LCD_DATA (*(volatile unsigned char*) 0x6800)


void lcd_busy(void)
{
	_delay_ms(50);	
}

void lcd_command(unsigned char cmd)
{
	lcd_busy();

	LCD_DATA = cmd;			// 포트 A에 명령어 출력
	LCD_CS = 0b00000001;	// RW=0, RS=0, E=1
	LCD_CS = 0b00000000;	// E=1
	_delay_us(1);	
}

void lcd_init()
{

	lcd_command(0b00111000); // 8-bit mode, 2행
	lcd_command(0b00001000); // (문자표시, 커서표시, 블링크)? off 
	lcd_command(0b00000001); // clear
	lcd_command(0b00000110); // 커서 자동증가
	lcd_command(0b00001111); // (문자표시, 커서표시, 블링크)? on 
}

void lcd_data(unsigned char byte)
{
	lcd_busy();

	LCD_DATA = byte;	// 포트 A에 명령어 출력
	LCD_CS = 0b00000011;	// RW=0 
	LCD_CS = 0b00000010;	// RS=1, E=1
	_delay_us(50);	
}

void lcd_string(char* str)
{
	int i=0;

	while(1) {
		if(str[i]=='\0') break;
		lcd_data(str[i++]);
	}
}

void lcd_clear()
{
	lcd_command(0b00000001);
}

void lcd_cursor_home()
{
	lcd_command(0b00000010);
}

void lcd_entry_mode(int ID, int S)
{
	unsigned char cmd = 0b00000100;	
	if(ID==1) cmd = cmd | 0b00000010;
	if(S==1) cmd = cmd | 0b00000001;
	// cmd = (1<<2)  | (ID<<1) | S;
	lcd_command(cmd);
}

void lcd_cursordisplay_shift(int SC, int RL)
{
	unsigned char cmd = 0b00010000;	
	if(SC==1) cmd = cmd | 0b00001000;
	if(RL==1) cmd = cmd | 0b00000100;
	// cmd = (1<<4)  | (SC<<3) | (RL<<2);
	lcd_command(cmd);
}

void lcd_display_position(unsigned char row, unsigned char col)
{
	unsigned char cmd = 0b10000000 | ((row-1)*0x40 +(col-1));	
	lcd_command(cmd);
}
