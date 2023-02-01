/* Discente: Nilo Rodrigues Alves Filho
Tarefa: Fazer um código em C para fazer com que o CCP1 opere no modo de captura para medir o período de um sinal de 50 us. 
Se este período de 50 us for detectado, o estado do pino RC0 da porta C, que estava inicialmente em nível baixo, é colocado em nível alto. 
Além disso, fazer com o que o CCP2 opere no modo PWM com frequência de 20 kHz e razão cíclica de 10%.

Vale como frequência para o dia 15.
*/

#include <16F877A.h>
#include "regs_pic16f877a.h"

unsigned int Cont = 0;		// Variável para indentificar se já foi detectada borda de subida
unsigned int Tempo = 0;		// Variável para armazenar o tempo

void main(){
   // Configurando Porta C
	TRISC = 0x04;					// Habilita RC2 como entrada e os demais pinos como saída
	PORTC = 0x00;					// Inicializa os pinos de saída em nível lógico baixo

   // Configurando CCP1
	CCP1CON = 0x05;					// Modo de captura; 1 transição de sub.
	CCP1IE = 1;						// Habilita interrupção	do CCP2	
	PIR1 = 0x00;					// Limpa a flag
	
   // Configurando Timer1
	INTCON = 0x90;					// Habilita as interrupções globais; Desabilita interrupção RB0
	T1CON = 0x10;					// Modo Temporizador; Timer desligado; prescaler 1:2
	TMR1IE = 0;						// Desabilita interrupção do Timer1
	TMR1L = 0x00; 					// Inicializa a contagem no zero;
	TMR1H = 0x00;					// Inicializa a contagem no zero;
	
   // Configurando CCP2
   	PR2 = 0xF9;						// Valor para 20Khz
   	CCP2CON = 0x3C;					// CCPx = 1 e CCPy = 1; Modo PWM;
   	CCPR2L = 0x18; 					// CCPx + CCPy + CCPR2L = 11 0001 1000 (10% DC) 
   	
   		
   // Configurando Timer2
	T2CON = 0b0000100;    			// Modo Temporizador; Timer ligado; prescaler 1:1
	TMR2 = 0x00;
	

	while(1){	// LOOP infinito (início)
		
		// Código Módulo CCP1
		if(CCP1IF){				// Condição detecção da borda de subida
			if(Cont == 0){			// Primeira borda de subida										
				TMR1ON = 1;			// Inicia o Timer		
				CCP1IF = 0;			// Limpa a flag
				Cont = 1;				// Contabiliza a borda de subida				
			}
			else if(Cont == 1){					// Segunda borda de subida
				TMR1ON = 0;							// Desliga o timer
				Tempo = TMR1L + (TMR1H << 8);		// Armazena na variável o valor do Timer
				CCP1IF = 0;							// Limpa a flag
				TMR1H = 0;							// Reinicia a contagem do tempo
				TMR1L = 0;							// Reinicia a contagem do tempo
				Cont = 0;							// Reinicia a contagem da borda de subida
			   // 125 equivale a 50us
				if(Tempo == 125){					// Condição igual a 50us
					portc0 = 1;							// Pino RC0 nível alto
				}
				if(Tempo != 125){					// Condição diferente de 50us
					portc0 = 0;							// Pino RC0 nível baixo
				}
				
				Tempo = 0;							//Reseta a variável tempo
			}
					
		}
		
	}	// LOOP infinito (fim)

}