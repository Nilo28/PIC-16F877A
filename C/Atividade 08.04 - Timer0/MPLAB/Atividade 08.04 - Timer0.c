/* Discente: Nilo Rodrigues Alves Filho
Tarefa: Fazer um c�digo em C para fazer com que o timer0 opere como contador por borda de descida. 
A cada 10 contagens o estado do pino RA0 da porta A � invertido de estado.

Vale como presen�a para o dia 08.
*/

#include <16F877A.h>
#include "regs_pic16F877A.h"

void main(){
	
   //Configurando PortA
   	TRISA = 0x10; 				// Habilita RA4 como entrada e os demais pinos como sa�da
   	PORTA = 0x00;				// Inicializa todos os pinos de sa�da em n�vel baixo 
   
   //Configurando o Timer0	
	OPTION_REG = 0x38;          // Modo Contador; Borda de desc.; Presc. Desabililitado 
	INTCON = 0x20;              // Habilita interrup��o por estouro
	TMR0 = 0xF6;                // Inicia a contagem em 246 (10 contagens para o estouro)

   //LOOP infinito
	while(1){

		if(T0IF){                    // Condi��o flag de estouro
			output_toggle(pin_a0);   // Muda o estado do pino RA0
			TMR0 = 0xF6;             // Retorna a contagem para 246
			T0IF = 0;				 // Limpa a flag de estouro
		
		}
	}
}