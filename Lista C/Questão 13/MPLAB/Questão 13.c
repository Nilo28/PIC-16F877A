/*
Discente: Nilo Rodrigues Alves Filho
Questão 13:
Faça um programa para gerar um sinal PWM em 20kHz de frequência no pino RC1, no qual o seu duty varie conforme a largura de um pulso, conectado no pino RC2 do microcontrolador.

*/

#include <16f877a.h>
#include<regs_pic16f877a.h>

void main(){ 
	unsigned int16 captura = 1, Tempo, Tamanho;

	setup_timer_2(T2_DIV_BY_1, 49,16);  
  	setup_ccp2(CCP_PWM);                
  	set_pwm2_duty(0);  
  	setup_timer_1(T1_INTERNAL|T1_DIV_BY_1 ); 
  	setup_ccp1(CCP_CAPTURE_RE); 
  	set_tris_c(0b00000100);  
 
  	while(1){ 

		if(ccp1if == 1 && captura == 1){ 
        	 Tempo = ccp_1;
           	 ccp1if = 0;
             captura++;
        }
        if(ccp1if == 1 && captura == 2){
        	Tamanho = ccp_1-Tempo;
            ccp1if = 0;
            captura = 1; 
            set_pwm2_duty(Tamanho);
        }
    }       
}
