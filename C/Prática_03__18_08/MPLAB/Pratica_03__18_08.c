/* Prática 03 - 18/08
Grupo:
- Antônio Gustavo da Silva Moura 
- Manoel Barroso da Silva Moura
- Nilo Rodrigues Alves Filho

Botão S1 -> Incrementa o valor
Botão S2 -> Decrementa o valor
% Botões de pull-up {Pressionado -> 0, Liberado -> 1} %

PORTD -> Display de 7 segmentos
RD0 -> a  RD1 -> b  RD2 -> c  RD3 -> d  RD4 -> e  RD5 -> f  RD6 -> g  RD7 -> h 
*/

#include <16f877a.h>
#include "regs_pic16f877a.h"

#use delay(clock=4000000)
#bit chaveS1 = PORTB.0	 	
#bit chaveS2 = PORTB.1		
#Define press 0			//Valor na porta quando botão pressionado
#Define liber 1			//Valor na porta quando botão liberado

void main(){
	//Variáveis
	unsigned int controleS1 = 0;	//Variável do controle do botão RB0
	unsigned int controleS2 = 0;	//Variável do controle do botão RB1
	unsigned int valor = 0;			//Variável para armazenar o valor a ser apresentado
	
	//Entradas
	trisb0 = 1;	//Botão S1 como entrada
	trisb1 = 1;	//Botão S2 como entrada
	
	//Saídas 
	set_tris_d(0x00);	//Saída para o display
	
	
	output_high(pin_b4);	// Seleciona o Diplay ds4
	
	while(true){	//LOOP Infinito
		//Botão S1
		if(chaveS1 == press && controleS1 == 0){
			controleS1 = 1;							
			if(valor < 9)	//Define valor máximo do display
				valor++;
			Delay_ms(200);	//Delay para tratar bouncing
		}
		else if(chaveS1 == liber && controleS1 == 1){
			controleS1 = 0;
		}
		
		//Botão S2	
		if(chaveS2 == press && controleS2 == 0){
			controleS2 = 1;
			if(valor > 0) 	//Define valor mínimo do display
				valor--;
			Delay_ms(200);	//Delay para tratar bouncing
		}
		else if(chaveS2 == liber && controleS2 == 1){
			controleS2 = 0;
		}
		
		//Alterando o valor do display	
		switch(valor){
			case 0x00:
				output_d(0b00111111);		//Imprime 0 no display 
				break;
			case 0x01:
				output_d(0b00000110);		//Imprime 1 no display
				break;
			case 0x02:
				output_d(0b01011011);		//Imprime 2 no display
				break;
			case 0x03:
				output_d(0b01001111);		//Imprime 3 no display
				break;
			case 0x04:
				output_d(0b01100110);		//Imprime 4 no display
				break;
			case 0x05:
				output_d(0b01101101);		//Imprime 5 no display
				break;
			case 0x06:
				output_d(0b01111101);		//Imprime 6 no display
				break;
			case 0x07:
				output_d(0b00000111);		//Imprime 7 no display
				break;
			case 0x08:
				output_d(0b01111111);		//Imprime 8 no display
				break;
			case 0x09:
				output_d(0b01101111);		//Imprime 9 no display
				break;
		}
	}
}