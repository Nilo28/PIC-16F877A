/*
Discente: Nilo Rodrigues Alves Filho
Questão 15:
Escreva um programa generalizado capaz de medir o período de um sinal, podendo este possuir qualquer valor de período entre 100 us e 50000 us. 
O período deste sinal será armazenado sempre em uma variável do programa.
*/

#include <16f877a.h>
#include<regs_pic16f877a.h>

void main(){ unsigned int16 Tempo1, Tempo2, Periodo, cont;
	int Captura1 = 1;
   

  	setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);
   	setup_ccp1(CCP_CAPTURE_RE);
   	set_timer1(0);
   	set_tris_C(0b00000100);

   	while(1){
		if(ccp1if == 1){
        	if(Captura1 == 1){
            	Tempo1 = CCP_1;
            	setup_ccp1(CCP_CAPTURE_FE);
         	}
         	else{
            	Tempo2 = CCP_1 - Tempo1;
            	setup_ccp1(CCP_CAPTURE_RE);   
         	}  
         	ccp1if = 0;
         	Captura1 = Captura1 ^ 1;
         	if(Tempo2 >= 100 && Tempo2 <= 5000){
            	Periodo = Tempo2;
         	}   
      	}
	}
}