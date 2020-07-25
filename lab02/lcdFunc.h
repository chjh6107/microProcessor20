void lcd_busy(void)
{
/*
	DDRD = 0x00;
	do{
		PORTC &= 0b00000110; // RS = 0
		PORTC |= 0b00000010; // RW = 1
		PORTC |= 0b00000100; // E = 1
	} while(PIND & 0x80);

	DDRD = 0xff;
*/

	_delay_ms(50);
}

void lcd_command(unsigned char cmd)
{
	lcd_busy();

	PORTD = cmd;
	PORTC &= 0b00000110; // RS = 0
	PORTC &= 0b00000101; // RW = 0
	PORTC |= 0b00000100; // E = 1
	PORTC &= 0b00000011; // E = 0, Depending on LCD light timing, E=1 -> 0
	_delay_us(1);		 // constant time delay
}

void lcd_init()
{
	DDRD = 0xff;
	DDRC = DDRC | 0x0f;

	_delay_ms(15);		 // wait more than 15ms
	
	PORTD = 0b00110000;
	PORTC &= 0b00000000; // E,RW,RS = 0,0,0
	_delay_us(4100);	 // wait more than 4.1ms
	PORTC &= 0b00000000; // E,RW,RS = 0,0,0
	_delay_us(100);		 // wait more than 100us
	PORTC &= 0b00000000; // E,RW,RS = 0,0,0

	lcd_command(0b00111000); // function set : 8-bit mode
	lcd_command(0b00001000); // display off
	lcd_command(0b00000001); // display clear
	lcd_command(0b00000110); // entry mode

	lcd_command(0b00001111); // display on, cursor on, cursor blank
}

void lcd_data(unsigned char byte)
{
	lcd_busy();

	PORTC |= 0b00000001;	// RS=1
	PORTC &= 0b00000101;	// RW=0
	PORTC |= 0b00000100;	// E=1
	_delay_us(50);			// constant time delay
	PORTD = byte;
	_delay_us(50);			// constant time delay
	PORTC &= 0b00000011;	// E = 0, Depending on LCD light timing, E=1 -> 0
}

void lcd_string(char *str)
{
	int i = 0;

	while(1)
	{
		if(str[i] == '\0') break;
		lcd_data(str[i++]);
	}
}

void lcd_display_clear()
{
	lcd_command(0b00000001);
}

void lcd_cursor_home()
{
	lcd_command(0b00000010);
}

void lcd_entry_mode(int ID, int S)
{
	unsigned char cmd;

	cmd = 0b00000100;
	if (ID == 1) cmd = cmd | 0b00000010;
	if (S == 1) cmd = cmd | 0b00000001;
	lcd_command(cmd);
}

void lcd_display_OnOff(int D, int C, int B)
{
	unsigned cmd;

	cmd = 0b00001000;
	if (D == 1) cmd = cmd | 0b00000100;
	if (C == 1) cmd = cmd | 0b00000010;
	if (B == 1) cmd = cmd | 0b00000001;
	lcd_command(cmd);
}

void lcd_cursordisplay_shift(int SC, int RL)
{
	unsigned cmd;

	cmd = 0b00010000;
	if (SC == 1) cmd = cmd | 0b00001000;
	if (RL == 1) cmd = cmd | 0b00000100;
	lcd_command(cmd);
}

void lcd_display_position(unsigned char row, unsigned char col)
{
	unsigned cmd;

	cmd = 0b10000000 | ((row-1)*0x40+(col-1));
	lcd_command(cmd);
}
