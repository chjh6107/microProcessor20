#include <avr/io.h>
#include <avr/interrupt.h>



int loop1 =0, loop2 =0;

int main(void){
    DDRB = 0x01;
	DDRE = 0xff; //PE2 출력
    TCCR0 = 0b00011110;
	TCCR2 = 0b00011100; //CTC 모드, OC2 토글, 분주비 256
    OCR0 = 31;
	OCR2 = 31; //클럭 31개 2s00번
				//반복하여 200msec가 나오도록 함
    TCNT0 = 0x00;            
	TCNT2 = 0x00;

    PORTB = 0x01;
    PORTE = 0x04;
	while(1){
		// for(loop=1; loop<=200; loop++){ //31개 200번 반복 시 0.2초
		// 	while(!(TIFR & 0x80));
		// 	TIFR |= 0x80;
		// 	TCNT2 = 0x00; 
		// }
		// PORTE ^= 0x04;
		// for(loop=1; loop<=100; loop++){ //31개 100번 반복 시 0.1초
		// 	while(!(TIFR & 0x02));
		// 	TIFR |= 0x02;
		// 	TCNT0 = 0x00; 
		// }
		// PORTB ^= 0x01;
        if(TIFR & 0x02){
            loop2++;
            if(loop2 == 100){
                PORTB ^= 0x01;
                loop2=0;
            }
            // TCNT0=0x00;
            TIFR |= 0x02;
        }else if(TIFR & 0x80){
            loop1++;
            if(loop1 == 200){
                PORTE ^= 0x04;
                loop1=0;
            }
            // TCNT2=0x00;
            TIFR |= 0x80;
        }
	}		
}

// int main(void){
//     int loop1= 0, loop2 = 0;
// 	DDRE = 0xff; //PE2 출력
// 	DDRB = 0xff; //PB0 출력 설정
//     TCCR0 = 0b00011110; //CTC 모드, OC0 토글, 분주비 256
//     TCCR2 = 0b00011100; //CTC 모드, OC2 토글, 분주비 256
//     OCR2 = 31;
// 	TCNT0 = 0;
// 	TCNT2 = 0;

// 	while(1){
//         OCR2 = 31;
//         for(loop1=1;loop1<=200;loop1++){
//             TCCR2 = 0b00011100; //CTC 모드, OC2 토글, 분주비 256

//             while(!(TIFR & 0b01000000));
//             TIFR |= 0b01000000;
//             // TCNT2 = 0x00;
//         }
//         PORTE ^= 0x04;
//         // TCCR0 = 0b00011110; //CTC 모드, OC0 토글, 분주비 256

//         // OCR0 = 31;

//         // if(TIFR & 0b01000000){ //led 0.2초 간격으로 점멸
//         //     loop1++;
//         //     if(loop1 == 200){

//     	// 	while(!(TIFR & 0b01000000));
//         //     TIFR |= 0b01000000;
//         //         loop1=0;
//         //     }
//         //     PORTE ^= 0x04;
//         //     TCNT2 = 0x00;

//         // }
//         // else if(TIFR & 0b00000001){
//         //     loop2++;
//         //     if(loop2 == 100){
//     	// 	while(!(TIFR & 0b00000001));
//         //     TIFR |= 0b00000001;
//         //     }
//         //     PORTB ^= 0x01;
//         //     TCNT0 = 0x00;
 
//         // } 

//         // for(loop1=1; loop1<=200; loop1++){//31개 200번 반복 시 0.2초 //부저
//         //     while(!(TIFR & 0b01000000)){
//         //         TIFR |= 0b01000000; //OCF2를 1로 라이트하여
//         //                             //출력비교매치 인터럽트 처리 루틴 실행
//         //         // TCNT2 = 0x00;
//         //     }
//         //     if(PORTB == 0x00) PORTB = 0x01;
//         //     else PORTB = 0x00;
//         // }
//         // for(loop2=1; loop2<=100; loop2++){//31개 100번 반복 시 0.1초 //LED
//         //     while(!(TIFR & 0b00000001)){
//         //         TIFR |= 0b00000001; //TOV0을 1로 라이트하여
//         //                             //출력비교매치 인터럽트 처리 루틴 실행
//         //         // TCNT0 = 0x00;
//         //     }
//         //     PORTE ^= 0x04;
//         // }
//     }
// }
