/*
Discente: Nilo Rodrigues Alves Filho
Altere a solução da quarta questão para utilizar a interrupção do TIMER0 no intuito de gerar a temporização de 4 ms para a multiplexação de cada display. 
*/


#include <16f877a.h>
#include "regs_pic16f877a.h"

#use delay(clock = 4M) 
#define ajustar 50  

int milhar, centena, dezena, unidade;  
unsigned int16 aux=0;
unsigned int16 cont = 0;  


int valores[] = {0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X67}; 

#INT_TIMER0
void interrupcao(){

	if (t0if){
		t0if = 0;
		cont++;
		if(cont>9999){
			cont=0;
		}

		milhar = cont / 1000;
		aux = cont % 1000;
		centena = aux / 100;
		aux = cont%100;
		dezena = aux / 10;
		unidade = cont % 10;
		
		
		output_d(~valores[milhar]);
		output_high(PIN_B7);
		delay_ms(ajustar);
		output_low(PIN_B7);
		
		output_d(~valores[centena]);
		output_high(PIN_B6);
		delay_ms(ajustar);
		output_low(PIN_B6);
		
		output_d(~valores[dezena]);
		output_high(PIN_B5);
		delay_ms(ajustar);
		output_low(PIN_B5);
		
		output_d(~valores[unidade]);
		output_high(PIN_B4);
		delay_ms(ajustar);
		output_low(PIN_B4);
		
		TMR0 = 6;  
	}
}                 
void main()
{
	OPTION_REG = 0x83;
	TMR0 = 6;
	INTCON = 0xA0;
	
	set_tris_c(0x01);
	set_tris_d(0x00);
	
	while(1){
	
	}
}