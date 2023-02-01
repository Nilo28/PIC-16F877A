/*
Discente: Nilo Rodrigues Alves Filho
Questão 2:
Utilizando a porta B e a porta D, elabore um programa em C para acionar quatro displays de anodo comum com quatro transistores, tal como mostrado no slide de página 24. 
Nos displays serão apresentados os algarismos da contagem de 0 a 9999, sendo esta contagem considerada para cada borda de subida de um sinal externo conectado no pino RB0/INT. 
*/
   
   
#include <16f877a.h>
#include "regs_pic16f877a.h"

#define tempo 5
#define milhar_on pin_d1
#define centena_on pin_d2
#define dezena_on pin_d3
#define unidade_on pin_d4

#use fast_io(B)
#use fast_io(D)
#use delay(clock = 4M)
#bit ponto = PORTD.0

byte const display_7seg [10] = {0x80,0xF2,0x49,0x61,0x32,0x25,0x04,0xF0,0x00,0x20}; 
int display = 0;
unsigned int16 cont = 0;
unsigned int16 aux;

void main () {
	int milhar = 0, centena = 0, dezena = 0, unidade = 0;
	set_tris_b(0x01);
	set_tris_d(0x00);
	ext_int_edge(L_TO_H);
	bit_clear(OPTION_REG,7);
	
	intf = 0;
	while(1){
		if(intf == 1){
			cont++;
			intf=0;
		}     
		if(cont > 9999){
			display++;
			if(display>4)
				display=0;          
		}
		
		milhar = cont / 1000;  
		aux = cont % 1000; 
		
		centena = aux / 100;  
		aux = aux % 100;    
		
		dezena = aux / 10;   
		unidade = aux % 10;
		
		
		output_b(display_7seg[milhar]);
		output_high(milhar_on);
		delay_ms(tempo);
		output_low(milhar_on);
		
		output_b(display_7seg[centena]);
		output_high(centena_on);
		delay_ms(tempo);
		output_low(centena_on);
		
		
		output_b(display_7seg[dezena]);
		output_high(dezena_on);
		delay_ms(tempo);
		output_low(dezena_on);
		
		output_b(display_7seg[unidade]);
		output_high(unidade_on);
		delay_ms(tempo);
		output_low(unidade_on);
		
	}  
}