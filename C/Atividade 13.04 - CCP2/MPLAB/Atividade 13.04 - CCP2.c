/*Discente: Nilo Rodrigues Alves Filho 
Fazer um código em C para fazer com que o CCP2 opere no modo de captura para medir o período de um sinal de 100 us. 
Se este período de 100 us for detectado, o estado do pino RC0 da porta C, que estava inicialmente em nível baixo, é colocado em nível alto.
Vale como presença do dia 13.

Considerações:
CCP2 -> RC1
*/

#include <16F877A.h>
#include "regs_pic16F877A.h"

unsigned int Cont = 0;		// Variável para indentificar se já foi detectada borda de subida
unsigned int Tempo = 0;		// Variável para armazenar o tempo


void main(){
   // Configurando Porta C
	TRISC = 0x02;					// Habilita RC1 como entrada e RC0 como saída
	PORTC = 0x00;					// Inicializa os pinos de saída em nível lógico baixo

   // Configurando CCP2
	CCP2CON = 0x05;					// Modo de captura; 1 transição de sub.
	CCP2IE = 1;						// Habilita interrupção	do CCP2	
	PIR2 = 0x00;					// Limpa a flag
	
   // Configurando Timer1
	INTCON = 0x90;					// Habilita as interrupções globais; Desabilita interrupção RB0
	T1CON = 0x10;					// Modo Temporizador; Timer desligado ; prescaler 1:2
	TMR1IE = 0;						// Desabilita interrupção do Timer0
	TMR1L = 0x00; 					// Inicializa a contagem no zero;
	TMR1H = 0x00;					// Inicializa a contagem no zero;


	while(1){	// LOOP infinito (início)

		if(CCP2IF){				// Condição detecção da borda de subida
			if(Cont == 0){			// Primeira borda de subida										
				TMR1ON = 1;			// Inicia o Timer		
				CCP2IF = 0;			// Limpa a flag
				Cont++;				// Contabiliza a borda de subida				
			}
			else if(Cont == 1){					// Segunda borda de subida
				TMR1ON = 0;							// Desliga o timer
				Tempo = TMR1L + (TMR1H << 8);		// Armazena na variável o valor do Timer
				CCP2IF = 0;							// Limpa a flag
				TMR1H = 0;							// Reinicia a contagem do tempo
				TMR1L = 0;							// Reinicia a contagem do tempo
				Cont = 0;							// Reinicia a contagem da borda de subida
			   // 250 equivale a 100us
				if(Tempo == 250){					// Condição igual a 100us
					portc0 = 1;							// Pino RC0 nível alto
				}
				if(Tempo != 250){					// Condição diferente de 100us
					portc0 = 0;							// Pino RC0 nível baixo
				}
			}
					
		}
	
	}	// LOOP infinito (fim)
}