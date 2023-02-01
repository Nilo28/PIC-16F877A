/* Discente: Nilo Rodrigues Alves Filho
Tarefa: Fazer um c�digo em C para fazer com que o CCP1 opere no modo de captura para medir o per�odo de um sinal de 50 us. 
Se este per�odo de 50 us for detectado, o estado do pino RC0 da porta C, que estava inicialmente em n�vel baixo, � colocado em n�vel alto. 
Al�m disso, fazer com o que o CCP2 opere no modo PWM com frequ�ncia de 20 kHz e raz�o c�clica de 10%.

Vale como frequ�ncia para o dia 15.
*/

#include <16F877A.h>
#include "regs_pic16f877a.h"

unsigned int Cont = 0;		// Vari�vel para indentificar se j� foi detectada borda de subida
unsigned int Tempo = 0;		// Vari�vel para armazenar o tempo

void main(){
   // Configurando Porta C
	TRISC = 0x04;					// Habilita RC2 como entrada e os demais pinos como sa�da
	PORTC = 0x00;					// Inicializa os pinos de sa�da em n�vel l�gico baixo

   // Configurando CCP1
	CCP1CON = 0x05;					// Modo de captura; 1 transi��o de sub.
	CCP1IE = 1;						// Habilita interrup��o	do CCP2	
	PIR1 = 0x00;					// Limpa a flag
	
   // Configurando Timer1
	INTCON = 0x90;					// Habilita as interrup��es globais; Desabilita interrup��o RB0
	T1CON = 0x10;					// Modo Temporizador; Timer desligado; prescaler 1:2
	TMR1IE = 0;						// Desabilita interrup��o do Timer1
	TMR1L = 0x00; 					// Inicializa a contagem no zero;
	TMR1H = 0x00;					// Inicializa a contagem no zero;
	
   // Configurando CCP2
   	PR2 = 0xF9;						// Valor para 20Khz
   	CCP2CON = 0x3C;					// CCPx = 1 e CCPy = 1; Modo PWM;
   	CCPR2L = 0x18; 					// CCPx + CCPy + CCPR2L = 11 0001 1000 (10% DC) 
   	
   		
   // Configurando Timer2
	T2CON = 0b0000100;    			// Modo Temporizador; Timer ligado; prescaler 1:1
	TMR2 = 0x00;
	

	while(1){	// LOOP infinito (in�cio)
		
		// C�digo M�dulo CCP1
		if(CCP1IF){				// Condi��o detec��o da borda de subida
			if(Cont == 0){			// Primeira borda de subida										
				TMR1ON = 1;			// Inicia o Timer		
				CCP1IF = 0;			// Limpa a flag
				Cont = 1;				// Contabiliza a borda de subida				
			}
			else if(Cont == 1){					// Segunda borda de subida
				TMR1ON = 0;							// Desliga o timer
				Tempo = TMR1L + (TMR1H << 8);		// Armazena na vari�vel o valor do Timer
				CCP1IF = 0;							// Limpa a flag
				TMR1H = 0;							// Reinicia a contagem do tempo
				TMR1L = 0;							// Reinicia a contagem do tempo
				Cont = 0;							// Reinicia a contagem da borda de subida
			   // 125 equivale a 50us
				if(Tempo == 125){					// Condi��o igual a 50us
					portc0 = 1;							// Pino RC0 n�vel alto
				}
				if(Tempo != 125){					// Condi��o diferente de 50us
					portc0 = 0;							// Pino RC0 n�vel baixo
				}
				
				Tempo = 0;							//Reseta a vari�vel tempo
			}
					
		}
		
	}	// LOOP infinito (fim)

}