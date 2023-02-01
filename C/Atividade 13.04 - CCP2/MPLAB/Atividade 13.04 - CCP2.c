/*Discente: Nilo Rodrigues Alves Filho 
Fazer um c�digo em C para fazer com que o CCP2 opere no modo de captura para medir o per�odo de um sinal de 100 us. 
Se este per�odo de 100 us for detectado, o estado do pino RC0 da porta C, que estava inicialmente em n�vel baixo, � colocado em n�vel alto.
Vale como presen�a do dia 13.

Considera��es:
CCP2 -> RC1
*/

#include <16F877A.h>
#include "regs_pic16F877A.h"

unsigned int Cont = 0;		// Vari�vel para indentificar se j� foi detectada borda de subida
unsigned int Tempo = 0;		// Vari�vel para armazenar o tempo


void main(){
   // Configurando Porta C
	TRISC = 0x02;					// Habilita RC1 como entrada e RC0 como sa�da
	PORTC = 0x00;					// Inicializa os pinos de sa�da em n�vel l�gico baixo

   // Configurando CCP2
	CCP2CON = 0x05;					// Modo de captura; 1 transi��o de sub.
	CCP2IE = 1;						// Habilita interrup��o	do CCP2	
	PIR2 = 0x00;					// Limpa a flag
	
   // Configurando Timer1
	INTCON = 0x90;					// Habilita as interrup��es globais; Desabilita interrup��o RB0
	T1CON = 0x10;					// Modo Temporizador; Timer desligado ; prescaler 1:2
	TMR1IE = 0;						// Desabilita interrup��o do Timer0
	TMR1L = 0x00; 					// Inicializa a contagem no zero;
	TMR1H = 0x00;					// Inicializa a contagem no zero;


	while(1){	// LOOP infinito (in�cio)

		if(CCP2IF){				// Condi��o detec��o da borda de subida
			if(Cont == 0){			// Primeira borda de subida										
				TMR1ON = 1;			// Inicia o Timer		
				CCP2IF = 0;			// Limpa a flag
				Cont++;				// Contabiliza a borda de subida				
			}
			else if(Cont == 1){					// Segunda borda de subida
				TMR1ON = 0;							// Desliga o timer
				Tempo = TMR1L + (TMR1H << 8);		// Armazena na vari�vel o valor do Timer
				CCP2IF = 0;							// Limpa a flag
				TMR1H = 0;							// Reinicia a contagem do tempo
				TMR1L = 0;							// Reinicia a contagem do tempo
				Cont = 0;							// Reinicia a contagem da borda de subida
			   // 250 equivale a 100us
				if(Tempo == 250){					// Condi��o igual a 100us
					portc0 = 1;							// Pino RC0 n�vel alto
				}
				if(Tempo != 250){					// Condi��o diferente de 100us
					portc0 = 0;							// Pino RC0 n�vel baixo
				}
			}
					
		}
	
	}	// LOOP infinito (fim)
}