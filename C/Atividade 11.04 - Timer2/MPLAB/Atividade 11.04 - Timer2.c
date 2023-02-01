/* Discente: Nilo Rodrigues Alves Filho

Fazer um código em C para fazer com que o timer2 opere como temporizador cujo o tempo de estouro desse timer seja de 50 us. 
A cada 100 us, o estado do pino RB0 da porta B é invertido de estado.
Vale como presença do dia 11.
*/

#include <16F877A.h>
#include "regs_pic16F877A.h"

void main(){
   unsigned int cont = 0;	// Variável que armazenará o número de estouros

   // Configurando o Timer2
	T2CON = 0x00;				// Temporizador; Postcaler 1:1; Prescaler 1:1
	PIE1 = 0x02;				// Habilita o estouro do Timer2
	TMR2 = 6;					// Valor de contagem para estouro com 50us (250 = 50us)

   // Configurando PORTB
	TRISB = 0x00;				// Habilita a Porta B como saída;
	PORTB = 0x00;           	// Inicializa a Porta B em nível lógico baixo
	
   // LOOP infinito (início)
	while(1){
		TMR2ON = 1; 			// Inicia o Timer
		if(TMR2IF){				// Verifica se houve estouro
			TMR2 = 6;			// Reseta o valor do timer
			TMR2IF = 0;			// Limpa a flag de estouro
			cont++;				// Contabiliza o estouro
			
			if(cont == 2){						// Verifica se houve 2 estouros
				output_toggle(pin_b0);			// Inverte o estado do pino RB0
				cont = 0;						// Reseta a variável para uma nova contagem de estouros
			}
		}
		
	} //LOOP infinito (fim)

}