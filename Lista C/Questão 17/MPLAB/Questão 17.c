/*
Discente: Nilo Rodrigues Alves Filho
Questão 17:
Implemente um PWM com frequência de 20kHz cujo duty cycle varie de forma senoidal com o tempo em 100Hz de frequência. 
O duty central deve ser de 50%. Utilize um dos módulos CCP. 
*/

#include <16f877a.h>
#include <math.h>
#include<regs_pic16f877a.h>

void main(){ 
	float32 Duty_Cycle = 0;
	int aux;

	setup_timer_2(T2_DIV_BY_1,49,2);
   	setup_ccp2(CCP_PWM);  
   	set_pwm2_duty(Duty_Cycle);
   	
   	while(1){
		if(tmr2if == 1){
        	aux++;
        	tmr2if=0;
        	if(aux >= 101){
        		Duty_Cycle = 100 * sin(6.28 * (float)aux/100) + 100;   
         		aux=0;
         		set_pwm2_duty(Duty_Cycle);
      		}
    	}
	}
}