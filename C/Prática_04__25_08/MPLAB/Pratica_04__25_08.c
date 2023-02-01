/* Pr�tica 04 - 25/08
Grupo:
- Ant�nio Gustavo da Silva Moura 
- Manoel Barroso da Silva Moura
- Nilo Rodrigues Alves Filho

Bot�o S1 -> Incrementa o valor
Bot�o S2 -> Decrementa o valor
% Bot�es de pull-up {Pressionado -> 0, Liberado -> 1} %

PORTD -> Display de 7 segmentos
RD0 -> a  RD1 -> b  RD2 -> c  RD3 -> d  RD4 -> e  RD5 -> f  RD6 -> g  RD7 -> h 
*/

#include <16f877a.h>
#include "regs_pic16f877a.h"

#use delay(clock=4000000)
#bit chaveS1 = PORTB.0	 	
#bit chaveS2 = PORTB.1		
#Define press 0			//Valor na porta quando bot�o pressionado
#Define liber 1			//Valor na porta quando bot�o liberado

void AlteraDisplay(unsigned int valor){
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

void main(){
	//Vari�veis
	unsigned int controleS1 = 0;	//Vari�vel do controle do bot�o RB0
	unsigned int controleS2 = 0;	//Vari�vel do controle do bot�o RB1
	unsigned int unidade = 0;		//Vari�vel para armazenar o valor das unidades
	unsigned int dezena = 0;		//Vari�vel para armazenar o valor das dezenas
	
	//Entradas
	trisb0 = 1;	//Bot�o S1 como entrada
	trisb1 = 1;	//Bot�o S2 como entrada
	
	//Sa�das 
	set_tris_d(0x00);	//Sa�da para o display
		
	while(true){	//LOOP Infinito
		//Bot�o S1
		if(chaveS1 == press && controleS1 == 0){
			controleS1 = 1;	
			if(!(dezena == 9 && unidade == 9)){
				if(unidade == 9){
					unidade = 0;
					dezena++;
				}
				else{
					unidade++;
				}
			}						
			
			Delay_ms(100);	//Delay para tratar bouncing
		}
		else if(chaveS1 == liber && controleS1 == 1){
			controleS1 = 0;
		}
		
		//Bot�o S2	
		if(chaveS2 == press && controleS2 == 0){
			controleS2 = 1;
			if(!(dezena == 0 && unidade == 0)){
				if(unidade == 0){
					unidade = 9;
					dezena--;
				}
				else{
					unidade--;
				}
			}
			
			Delay_ms(100);	//Delay para tratar bouncing
		}
		else if(chaveS2 == liber && controleS2 == 1){
			controleS2 = 0;
		}
		
		//Alterando o valor do display		
		AlteraDisplay(unidade);	
		output_high(pin_b4);
		Delay_ms(10); 			
		output_low(pin_b4);
		
		AlteraDisplay(dezena);		
		output_high(pin_b5);		
		Delay_ms(10);		
		output_low(pin_b5);
		
	}
}

//#org	0x1E80, 0x1FF7 {}