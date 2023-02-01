/* Prática 02 - 11/08
Grupo:
- Antônio Gustavo da Silva Moura
- Manoel Barroso da Silva Moura
- Nilo Rodrigues Alves Filho

OBSERVAÇÕES:
- O Timer0 sinalizará estouro a cada 8ms, logo para 1s devem ser contabilizados 125 estouros

- Para estouro de 8ms temos: TMR0 = 250, presc. 1:32; clock interno de 4MHz 
*/

#include <16f877a.h>
#include "regs_pic16f877a.h"

void main(){
	unsigned int Estouro = 0;		//Variável para capaz de armazenar o número 125
	
	setup_timer_0(T0_INTERNAL|T0_DIV_32);		//Clock interno e presc. 1:32
	set_timer0(6);								//256-250
	output_low(PIN_B0);							//LED inicialmente desligado

	
	while (true){		//LOOP infinito
		
		if (t0if == 1){			//Verifica flag de estouro
			t0if = 0;			//Limpa flag de estouro
			set_timer0(6);		//Reseta valor do timer
			Estouro++;			//Contabiliza 1 estouro
	
			if (Estouro == 125){					//Verifica se há 125 estouros
				output_toggle(PIN_B0);				//Comuta o LED
				Estouro = 0;						//Reseta quantidade de estouros
			}
		}
	}
}
//#ORG 0x1E80, 0x1FF7 {}


//
//#ORG 0x1E80, 0x1EFF {}

//#ORG 0x1E80, 0x17FF {}
//#ORG 0x17FF,  0x1FF7 {}