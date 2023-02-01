/*
Discente: Nilo Rodrigues Alves Filho
Questão 8:
Utilizando a interrupção do TIMER0, faça um programa para gerar uma onda quadrada de 10 kHz, 1kHz, 100 Hz, 10 Hz e 1 Hz respectivamente nos pinos RD7, RD6, RD5, RD4 e RD3. 

*/

#include <16f877a.h>
#include "regs_pic16f877a.h"

#use delay(clock = 4000000)
#bit ponto = PORTD.1
#INT_TIMER0
int cont;

void InitTimer0(){
	setup_timer_0(T0_INTERNAL | T0_DIV_2);
	set_timer0(256-250);
}

void main(){

cont = 0;

set_tris_b(0x01);
set_tris_d(0x00);
ext_int_edge(L_TO_H);
bit_clear(OPTION_REG,7);
InitTimer0();
enable_interrupts(GLOBAL | INT_TIMER0);
	while(1){
		cont++;
		if (cont == 10){
			output_toggle(pin_d7);
			cont = 0;
		}
	}
}