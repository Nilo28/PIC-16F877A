/*
Discente: Nilo Rodrigues Alves Filho
Quest�o 10:
Utilizando a interrup��o do TIMER2, fa�a um programa para comutar o estado do pino RD7 a cada 800 us. 
*/

#include <16f877a.h>
#include<regs_pic16f877a.h> 

#use fast_io(B)
#use fast_io(D)
#use delay(clock = 4M) 
#int_timer2

void main () {

	enable_interrupts(GLOBAL | INT_TIMER2);//
	tmr2ie  = 1;
	INTCON  = 0xC0;
	setup_timer_2(T2_DIV_BY_1, 199, 4);
	set_tris_b(0b00000000);      
	bit_clear(OPTION_REG,7);
	
	while(TRUE){
		if (tmr2if){ 
			tmr2if = 0;
			output_toggle(pin_d7);
		}
	}
}
   

