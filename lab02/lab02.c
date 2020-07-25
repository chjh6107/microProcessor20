#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcdFunc.h"

void ex01();
void ex02();
void ex03();
void ex04();

int main(void){

	//ex01();
	//ex03();
	ex04();

	while(1){
		//ex02();
	}
}

void ex01(){ //학교 이름 및 영어 이름 출력
	lcd_init();  //LCD 초기화
	lcd_display_position(1, 1); //LCD 커서 및 위치를 1행1열로 맞춤
	lcd_string("University of Ulsan, IT Convergence"); //해당 string을 char형으로 바꾼 뒤 CGROM에 저장된 것으로 PORT에 출력
	lcd_display_position(2, 1); //LCD 커서 및 위치를 2행1열로 맞춤
	lcd_string("Jong_hun Choe"); //해당 string을 char형으로 바꾼 뒤 CGROM에 저장된 것으로 PORT에 출력ㅊ
}

void ex02(){ //LCD 스크린을 좌, 우로 shift
	int i;

	for(int i = 0; i<20; i++){ //총 20번 반복
		_delay_ms(100); //0.1초 delay
		lcd_cursordisplay_shift(1, 1); //출력된 문자열을 좌측으로 한 칸 shift
	}

	for(i = 0; i<20; i++){
		_delay_ms(100);
		lcd_cursordisplay_shift(1, 0); //출력된 문자열을 우측으로 한 칸 shift
	}
}

void ex03(){ //연산 계산기
	DDRA = 0x00; //PA, PB, PC를 입력으로 설정
	DDRB = 0x00;
	DDRE = 0x00;

	unsigned int a,b,e, chk_a, chk_b, chk_e; //무한으로 출력되는 것을 방지하기 위한 체크용 변수 선언
	char buf[40]; //출력하기 위해 버퍼 선언

	lcd_init(); //LCD 초기화

	while(1){ //계속 데이터를 받기 위해 무한루프
		a = PINA; //PA, PB 입력 값을 a, b에 각각 저장
		b = PINB;
		e = PINE; // PE의 입력 값은 연산자가 바뀌었는지 체크하기 위해 저장
		int divres; //나눈 값을 저장

		if(chk_a != a || chk_b != b || chk_e != e){ //계속 출력되는 것을 방지하기 위해 a, b, e 값이 바뀐 것이 확인이 되면 데이터를 바꿈
			switch(~PINE & 0x0F){ // 입력된 E 값이 해당 case에서 연산 수행
				case 0x0 : // +
					lcd_display_clear(); //LCD 스크린을 초기화
					sprintf(buf, "%d + %d = %d", a, b, a+b); //해당 값을 string으로 변환하여 버퍼에 저장
					lcd_string(buf); //그 후 버퍼에 저장된 string 값을 char형으로 쪼개어 출력
					break;
				case 0x1 : // - //이하 동일
					lcd_display_clear();
					sprintf(buf, "%d - %d = %d", a, b, a-b);
					lcd_string(buf);
					break;
				case 0x2 : // *
					lcd_display_clear();
					sprintf(buf, "%d * %d = %d", a, b, a*b);
					lcd_string(buf);
					break;
				case 0x3 : // %
					lcd_display_clear();
					divres = a/ b;
					sprintf(buf, "%d %% %d = %d.%02d", a, b, divres, a%b); // float형으로 변환 후 출력타입 %f로 할 시 '?'로 출력되어 몫과 나머지를 따로 출력
					lcd_string(buf);
					break;
											
				default:
					;
			}
		}
		chk_a = a; //이전값이 될 a, b, e를 체크용 변수에 저장
		chk_b = b;
		chk_e = e;
	}
}

void ex04(){
	#define SIZE 48

	unsigned char myName[SIZE] = {0x04, 0x1F, 0x04, 0x0A, 0x11, 0x04, 0x1F, 0x00,	//0x00 초
								0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00,		//0x01 ㅣ
								0x00, 0x1F, 0x04, 0x0A, 0x11, 0x04, 0x1F, 0x00,		//0x02 조
								0x04, 0x1F, 0x00, 0x0E, 0x11, 0x0E, 0x00, 0x00,		//0x03 ㅇ
								0x0E, 0x11, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 	//0x04 ㅎ
								0x1F, 0x04, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x00		/*0x05 ㅜㄴ*/};
	lcd_init();						// LCD를 초기화
	lcd_command(0x40);				// 0b00100000을 보내어서 데이터를 CGRAM으로 사용
	
	for(int i=0; i<SIZE; i++){ //CGRAM에 해당 array를 저장
		lcd_data(myName[i]);
		_delay_ms(1);
	}

	lcd_command(0x88); // LCD의 88번 주소(1행 중간 정도)에 커서 설정
	lcd_data(0x00);	   // CGRAM 주소 0번지에 저장된 값 출력 초
	lcd_command(0x89); // 이하 동일
	lcd_data(0x01);	   // CGRAM 각 주소 1,2,3,4,5 번지에 저장된 값 출력
	lcd_command(0x8A);
	lcd_data(0x02);
	lcd_command(0x8B);
	lcd_data(0x03);
	lcd_command(0xCA); // LCD의 CA번 주소(2행 중간 정도)에 커서 설정
	lcd_data(0x04);
	lcd_command(0xCB);
	lcd_data(0x05);
}
