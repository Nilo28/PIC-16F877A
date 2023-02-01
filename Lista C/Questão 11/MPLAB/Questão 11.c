/*
Discente: Nilo Rodrigues Alves Filho
Questão 11:
Utilizando as interrupções dos três timers, configure o TIMER0 para gerar uma interrupção a cada 100 us, o TIMER1 a cada 200 us e o TIMER2 a cada 300 us. 
A ordem de prioridade das interrupções é: TIMER0, TIMER1 e TIMER2, sendo a interrupção do TIMER0, a interrupção de maior prioridade e a do TIMER2, a de menor prioridade. 
A rotina de tratamento de interrupção do TIMER0 comuta o estado do pino RD7, a do TIMER1 comuta o estado do pino RD6 e por fim a do TIMER2 comuta o estado do pino RD5. 
Nesse caso, é possível duas dessas interrupções ocorrerem ao mesmo tempo? Se sim, quais? É possível também a ocorrência dessas três interrupções ao mesmo tempo? Se sim, quais e por que? 
*/

#include <16f877a.h>
#include "regs_pic16f877a.h"     

#use fast_io(B)
#use fast_io(D)
#use delay(clock = 4M)    
#priority INT_TIMER0, INT_TIMER1, INT_TIMER2 

// Interrupção do Timer0
#int_timer0
void Interrupt0(){
	if (T0IF){ 
    	T0IF = 0;
    	set_timer0(156);
     	output_toggle(pin_d7);    
	}
} 

// Interrupção do Timer1
#int_timer1
void Interrupt1(){
	if (TMR1IF){ 
    	TMR1IF = 0;
    	TMR1H = 0xFF;
    	TMR1L = 0x38;
     	output_toggle(pin_d6);    
  	}
}

// Interrupção do Timer2  
#int_timer2
void Interrupt2(){
	if (tmr2if){ 
    	tmr2if = 0;
 		output_toggle(pin_d5);                                        
  	}
}       


void main(){
	// Interrupções
	T1CON = 0x01;   
	gie  = 1;
 	peie  =1;
  	t0ie = 1;
	tmr1ie=1;
	tmr2ie=1;
 	t0if = 1;   
    T2CON = 0x0C;

	// Configurando Timer's
    setup_timer_2(T2_DIV_BY_1, 149, 2);
	setup_timer_1(T1_DIV_BY_1| T1_INTERNAL);
	set_timer1(65336);
	setup_timer_0(RTCC_INTERNAL | RTCC_DIV_1);
	set_timer0(156);
    set_tris_b(0x01); 
	bit_clear(OPTION_REG,7);
                
    while(1){
    }
        
}
   