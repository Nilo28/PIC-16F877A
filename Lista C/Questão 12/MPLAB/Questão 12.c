/*
Discente: Nilo Rodrigues Alves Filho
Questão 12:
Escreva um programa em C para o PIC16F877A a fim de gerar um sinal PWM na frequência de 20 kHz. 
A cada 0,1 segundos, a razão cíclica é aumentada em 10 %. 
Quando for atingido o duty no tempo de 100 %, o duty reinicia em zero, repetindo o ciclo até 100%. 
No mesmo programa, faça a medição do tempo em nível alto do sinal PWM. 
Se este tempo for superior a 25 us, o estado do pino RD0 permanece em nível alto, caso contrário em nível baixo.
*/

#include <16f877a.h>
#include<regs_pic16f877a.h>

#bit TMR2IF = 0x0c.1
#bit CCP2IF = 0x0d.0

void main (){unsigned int8 cont = 0; int1 p_cap; unsigned int16 Duty_Cycle, Tempo, Tempo_2;      
	Duty_Cycle = 0;
	p_cap = 1;
	
	SETUP_TIMER_2(T2_DIV_BY_1,249,8,);  
	SETUP_CCP1(CCP_PWM);
	SETUP_CCP2(CCP_CAPTURE_RE);
	SET_PWM1_DUTY(Duty_Cycle);
	
	while(1){
		if(TMR2IF == 1){
			TMR2IF = 0; 
			cont++;
			if (cont == 400){
				cont = 0; 
				Duty_Cycle = Duty_Cycle + 100;
				if(Duty_Cycle > 1000){
					Duty_Cycle = 0;
				} 
				SET_PWM1_DUTY(Duty_Cycle);       
			}
		}     
		if(CCP2IF == 1){
			if(p_cap == 1){
				Tempo = CCP_2;
				SETUP_CCP2(CCP_CAPTURE_FE);
			}      
			else{
				Tempo_2 = CCP_2 - Tempo;
				SETUP_CCP2(CCP_CAPTURE_RE);
			}
			CCP2IF = 0;
			p_cap = p_cap ^ 1;      
			if(Tempo_2 > 25){
				output_high(pin_d0);
			}
			else{
				output_low(pin_d0);
			}         
		}       
	}       
}