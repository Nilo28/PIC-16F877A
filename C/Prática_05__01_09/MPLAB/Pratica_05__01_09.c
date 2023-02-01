/* Prática 05 - 01/09
Grupo:
- Antônio Gustavo da Silva Moura 
- Manoel Barroso da Silva Moura
- Nilo Rodrigues Alves Filho

RB0 - LED -> Indica cronômetro ligado
RB1 - Botão S1 -> Continue/Pause
RB2 - Botão S2 -> Reset

PORTD -> Display de 7 segmentos

Timer1 estouro a cada 250ms (clock interno; presc. 1:8)
*/

#include <16f877a.h>
#include "regs_pic16f877a.h"

#use delay(clock = 4000000)	//Valor do clock
#bit chaveS1 = PORTB.1		//Botão pause/continue 	
#bit chaveS2 = PORTB.2		//Botão reset
#Define press 0				//Valor na porta quando botão pressionado
#Define liber 1				//Valor na porta quando botão liberado

byte const Display[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  //Matriz com os números relativos aos segmentos

//Variáveis
unsigned int16 DisplayT = 0;			//Variável para o valor total
unsigned int16 aux = 0;					//Variável auxiliar para cálculo das unidades, dezenas, centenas e unidades de milhar
unsigned int UnidadeD = 0;				//Variável para a unidade
unsigned int DezenaD = 0;				//Variável para a dezena 
unsigned int CentenaD = 0;				//Variável para a centena
unsigned int MilharD = 0;				//Variável para a unidade de milhar

//Flags
int1 controleS1 = 0;					//Flag botão pause/continue
int1 controleS2 = 0;					//Flag botão reset
int1 button_mode = 0;					//Flag modo botão pause/continue	0 -> Pausado, 1 -> Rodando

//Interrupção Timer1
#INT_TIMER1
void IntTimer1(){
	set_timer1(34286);
	if(DisplayT < 9999){
		DisplayT++;
	}
	else if(DisplayT == 9999){
		DisplayT = 0;
	}	
}	

//FUNÇÃO PRINCIPAL
void main(){
	//Entradas e saídas
	trisb0 = 0;			//RB0 saída (LED)
	trisb1 = 1;			//RB1 entrada (Botão S1)
	trisb2 = 1;	 		//RB2 entrada (Botão S2)
	set_tris_d(0x00);	//PortD saída (Display)
	
	output_low(pin_b0);	//Valor inicial do LED de indicação
	
	//Habilitando interrupções
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_TIMER1);
	
	//Timer1	
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);	
	tmr1on = 0;									// Inicia desligado
	set_timer1(34286);
//Gustavo		
	while (true){		//LOOP infinito
		
	//Botão Pause/Continue	
		if(chaveS1 == press && controleS1 == 0){
			controleS1 = 1;			//Flag de botão ainda pressionado
			
			if(button_mode == 0){		//Continue
				tmr1on = 1;				//Liga o timer
			 	output_high(pin_b0);	//Liga o led de indicação
			 	button_mode = 1;		//Sinaliza na flag o modo 'continue'
			}
			else if(button_mode == 1){	//Pause
				tmr1on = 0;				//Desliga o timer
				output_low(pin_b0);		//Desliga o led de indicação
				button_mode = 0;		//Sinaliza na flag o modo 'pause'
			}					
			Delay_ms(100);	//Delay para tratar bouncing
		}
		else if(chaveS1 == liber && controleS1 == 1){
			controleS1 = 0;			//Flag de botão liberado
		}
		
	//Botão Reset
		if(chaveS2 == press && controleS2 == 0){
			controleS2 = 1;		//Flag de botão ainda pressionado
			DisplayT = 0;		//Reseta o valor do cronômetro
			Delay_ms(100);		//Delay para tratar bouncing
		}
		else if(chaveS2 == liber && controleS2 == 1){
			controleS2 = 0;		//Flag de botão liberado
		}
//Manoel
	//Calculando o valor de cada display
		MilharD = DisplayT / 1000;		//Valor das unidades de milhar
		aux = DisplayT % 1000;			
		CentenaD = aux / 100;			//Valor das centenas
		aux = aux % 100;
		DezenaD = aux / 10;		  		//Valor das dezenas
		aux = aux % 10;
		UnidadeD = aux;					//Valor das unidades
		
	//Alterando o valor do display		
		output_d(Display[UnidadeD]);	
		output_high(pin_b4);
		Delay_ms(5); 			
		output_low(pin_b4);
				
		output_d(Display[DezenaD]);
		output_high(pin_b5);		
		Delay_ms(5);		
		output_low(pin_b5);
				
		output_d(Display[CentenaD]);
		output_high(pin_b6);		
		Delay_ms(5);		
		output_low(pin_b6);
		
		output_d(Display[MilharD]);		
		output_high(pin_b7);		
		Delay_ms(5);		
		output_low(pin_b7);
	
	}	
}