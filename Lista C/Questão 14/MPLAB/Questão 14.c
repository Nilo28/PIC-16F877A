/*
Discente: Nilo Rodrigues Alves Filho
Questão 14:
Faça um programa para colocar em nível alto o estado do pino RC2/CCP1 toda vez que a contagem do TIMER1 for 10. 
Após, isso o estado deverá estar em nível baixo. 
*/


#include <16f877a.h>
#include <regs_pic16f877a.h>

void InitTimer1(){
  t1con = 0x01;
  tmr1if = 0;
  tmr1h = 0xFF;
  tmr1l = 0xF6;
  tmr1ie = 1;
  intcon = 0xC0;
}
 
void main(){
	unsigned int cont = 0;
	set_tris_c(0x00);
	
	while(1){
		
		if (tmr1if){ 
			tmr1if = 0;
			tmr1h = 0xFF;
			tmr1l = 0xF6;
			cont++;
		}
		
		if(cont == 10000000)
		{
			output_toggle(pin_c2);
		}
	}
	
	
	
		
	
}
