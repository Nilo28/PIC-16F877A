/*
Discente: Nilo Rodrigues Alves Filho 
Questão 5:
Utilizando o TIMER0 como temporizador com clock interno, faça um programa para verificar constantemente se o pino RD7, configurado como entrada, se mantém em nível alto em pelo menos 50 ms. 
Caso afirmativo, o estado do RD6 é colocado em nível alto, caso contrário, o seu estado é baixo. 
*/


#include <16f877a.h>
#include "regs_pic16f877a.h"      

int c1 = 0;
	
void InitTimer0(){
	setup_timer_0(RTCC_INTERNAL | RTCC_DIV_1);
	set_timer0(0);
	output_high(pin_d6);
	}  
void main(){
	enable_interrupts(GLOBAL | INT_TIMER0);
	InitTimer0();
	
	set_tris_d(0x80);
	ext_int_edge(H_TO_L);
	
	while(1){
		if(portd7 == 1 && c1 == 0){
			TMR0 = 0;
			c1 = 1;
		}
		else if (portd7 == 0 && c1 == 1){
			c1 = 0;
		}
		
		if(TMR0 >= 50){
			portd6 = 1;
		}
		else{
			portd6 = 0;
		}
		
	}

} 