/*
Discente: Nilo Rodrigues Alves Filho
Questão 19:
Faça um programa para gerar três ondas quadradas de 60 Hz de frequência cada, defasados entre si de 120º com duty de 50 %. 
*/

#include <16f877a.h>
#include <math.h>
#include "regs_pic16f877a.h"

float32 duty = 0;
int aux;

void main(){ 
	setup_timer_2(T2_DIV_BY_1,49,2);
	setup_ccp2(CCP_PWM);  
	set_pwm2_duty(duty);
	while(1){
		if(tmr2if==1){
			aux++;
			tmr2if=0;
			if(aux>=101){
				duty = 100 * sin(6.28 * (float)aux/100) + 100;   
				aux=0;
				set_pwm2_duty(duty);
			}
		}
	}
}
