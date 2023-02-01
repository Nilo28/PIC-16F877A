/*
Discente: Nilo Rodrigues Alves Filho
Questão 6:
Utilizando o TIMER0, faça um programa para ler o estado do pino RD7 a cada 26 us durante 10 vezes. 
A primeira leitura estará armazenada numa flag (Ex: #bit flag1 = 0x20.0). 
A segunda leitura estará no bit menos significativo de uma variável de 8 bits, 
enquanto que a terceira leitura estará no segundo bit menos significativo e assim seguindo essa lógica até o oitavo bit mais significativo da variável (Sugestão: Utilize o comando >> da linguagem C). 
A décima leitura do pino estará em uma outra flag (Ex: #bit flag10 = 0x20.1). 
Essas 10 leituras serão sempre realizadas após o pino RD7 estiver em nível alto durante 50 ms. 

*/


#include <16f877a.h>
#include "regs_pic16f877a.h"


int flag10 = 0b00000001;
int flag1 = 0b00000001;
int aux2 = 0b00000001;
int aux = 0b00000001;           
int varprincipal = 0b00000000;    
int varbitdeslc, bit_lido; 
int cont1 = 0;           
int cont2 = 7;         
int x = 0b00000000;     

void var_byte(){   
	bit_lido = 0b00000000;
	int estado_pino = input(PIN_D7);
	
	aux2 = (estado_pino  & 1);
	varbitdeslc = aux<<cont1;
	
	int bit_deslc = (x >> cont2);
	
	varbitdeslc = (varbitdeslc ^ bit_deslc);
	varprincipal += varbitdeslc;   
	cont1++;
	cont2--;
	
	if(cont1==8){
		bit_lido = ~varprincipal;
		varbitdeslc = aux;
		varprincipal = 0;
	}
}
void leitura(contleitura){
	OPTION_REG = 0X88;
	TMR0 = 230;
	t0if = 0;
	
	while(1) {
		if(t0if == 1){
			if(contleitura==0){
				break;
			}
			if(contleitura == 1){
				flag1 = input(PIN_D7);
			}
			if(contleitura >= 2 && contleitura <=9){
				var_byte();
			}
			if(contleitura == 10){   
				flag10 = input(PIN_D7); 
			}
			contleitura = contleitura>10?0:contleitura+1;
			t0if = 0;
			TMR0 = 230;
		}            
	}      
}

void main(){

	int contleitura = 1;
	OPTION_REG    = 0x87;
	TMR0       = 61;
	INTCON    = 0xA0;
	
	while(1){   
		if (t0if == 1){
			int botao = input(PIN_D7);
			if(botao == 1){   
				leitura(contleitura);
			}
			t0if = 0;
			TMR0 = 61;
		} 
	}
}

