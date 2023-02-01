/*
Discente: Nilo Rodrigues Alves Filho
Questão 3:
Altere o programa anterior, utilizando o TIMER0 como contador externo via pino RA4.
*/

#include <16f877a.h>
#include "regs_pic16f877a.h"

#define hab_milhar pin_d1
#define hab_centena pin_d2
#define hab_dezena pin_d3
#define hab_unidade pin_d4

#use fast_io(B)
#use fast_io(D)
#use delay(clock = 4M)
#bit ponto = PORTD.0

byte const display [10] = {0x80, 0xF2, 0x49,0x61,0x32,0x25,0x04,0xF0,0x00,0x20};
#define ajustar 6 
int dp = 0;
int var = 0;
unsigned int16 cont=0, cont2=0;
unsigned int16 aux;

int mi=0, cen=0, dez=0, un=0;
void aciona_display(int algarismo, int posicao);

void main () {
	
	int posicao =1;
	set_tris_b(0x01);
	set_tris_d(0x00);
	ext_int_edge(L_TO_H);
	bit_clear(OPTION_REG,7);
	setup_timer_0(RTCC_EXT_L_TO_H | RTCC_DIV_1);
	set_timer0(0);
	intf=0;
	
	
	while(TRUE){
		
		if(t0if==1){
			cont2++;
		} 
		cont = 256 * cont2 + get_timer0();
		if(cont>9999){
			dp++;
			cont2=0;
		if(dp>4)
			dp=0;          
		}
		
		mi= cont / 1000; 
		aux = cont % 1000;   
		
		cen = aux / 100; 
		aux = aux % 100; 
		
		dez = aux / 10;  
		un = aux % 10;
		
		
		output_b(display[mi]);
		output_high(hab_milhar);
		delay_ms(ajustar);
		output_low(hab_milhar);
		
		output_b(display[cen]);
		output_high(hab_centena);
		delay_ms(ajustar);
		output_low(hab_centena);
		
		
		output_b(display[dez]);
		output_high(hab_dezena);
		delay_ms(ajustar);
		output_low(hab_dezena);
		
		
		output_b(display[un]);
		output_high(hab_unidade);
		delay_ms(ajustar);
		output_low(hab_unidade);
		
	}
}

