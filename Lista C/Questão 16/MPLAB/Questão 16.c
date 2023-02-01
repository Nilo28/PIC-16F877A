/*
Discente: Nilo Rodrigues Alves Filho
Questão 16:
Faça o mesmo do item anterior, modificando apenas o tipo de evento a ser medido. 
No caso deste, para medir o tempo em nível alto do sinal ao invés do período. 

*/

#include <16f877a.h>
#include <regs_pic16f877a.h>

unsigned int16 cont = 0;
int Tempo_1 = 0, Tempo_F, capt1;


#int_timer1
void interrupcao_TMR1(void){ 
   set_timer1(65036);
   cont++;
   if(cont > 500){
	 cont = 0;
   } 
}

void main(){   
	setup_ccp1(CCP_CAPTURE_RE);
    set_timer1(T1_INTERNAL|T1_DIV_BY_1);
    set_timer1(65036);
    INTCON = 0x80;
    PIE1 = 0x01;
    TRISC = 0x04;      
    PORTC = 0x00;
    capt1 = 1;
    while(1){
       if(cont > 0 || cont <=500){
          if (ccp1if == 1){
             if (capt1 == 1){
                Tempo_1 = CCP_1;
                setup_ccp1(CCP_CAPTURE_FE);
             }

             else
             {
                Tempo_F = CCP_1 - Tempo_1;
                setup_ccp1(CCP_CAPTURE_RE);
             }
             ccp1if = 0;
             capt1 = capt1 ^ 1;
          }
       }
         
    }      
}