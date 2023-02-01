/*
Discente: Nilo Rodrigues Alves Filho
Questão 1:
 Desenhe um circuito com o decodificador 7448 e um demultiplexador para acionar quatro displays de 7 segmentos de catodo comum, utilizando a porta D.
 A partir do desenho, faça o programa em C.

Observações:
- O código simulará um cronômetro digital no formato (00:00);
- Para o circuito, só poderá ser ligado um display por vez;
- O demultiplexador escolherá qual display será usado;
- Os valores serão mostrados na seguinte ordem:
	1º: Dezenas dos minutos	
	2º: Unidades dos minutos	
	3º: Dezenas dos segundos
	4º: Unidades dos Segundos
*/

#include <16f877a.h>

#use delay(clock = 4M) 
#define tempo 100		// Valor, em ms, do delay de atualização do cronômetro.

// Configurando as chaves enable do demultiplexador
#define Display_dezena_min  output_bit( PIN_D4, 1); output_bit( PIN_D5, 1);		// 11 -> Seleciona o display das dezenas dos minutos	
#define Display_unidade_min output_bit( PIN_D4, 0); output_bit( PIN_D5, 1);		// 01 -> Seleciona o display das unidades dos minutos	
#define Display_dezena_segundo output_bit(PIN_D4,1); output_bit(PIN_D5,0);     		// 10 -> Seleciona o display das dezenas dos segundos
#define Display_unidade_segundo output_bit(PIN_D4,0); output_bit(PIN_D5,0);			// 00 -> Seleciona o display das unidades dos segundos

byte display[10] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09}; 			// Valores a serem mostrados no display 

void main(){
	set_tris_d(0b00000000);
	ext_int_edge(L_TO_H);	
														
	while(1){
		int D_min = 0, U_min = 0, D_seg = 0, U_seg = 0;
		
	    for(D_min = 0; D_min < 3; D_min++){						// Valor da dezenas dos minutos			
			for(U_min = 0; U_min < 4; U_min++){					// Valor da unid3ades dos minutos	
		         for(D_seg = 0; D_seg < 6;D_seg++){					// Valor da dezena dos segundos
			         for(U_seg = 0; U_seg < 10;U_seg++){			// Valor das unidade dos segundos
				         
				         // Mostra o valor das dezenas dos minutos	
				         output_d(display[D_min]);
				         Display_dezena_min;
				         delay_ms(tempo);
				         
				         // Mostra o valor das unidades dos minutos	
				         output_d(display[U_min]);
				         Display_unidade_min;
				         delay_ms(tempo);
				         
				         // Mostra o valor das dezenas dos segundos
				         output_d(display[D_seg]);
				         Display_dezena_segundo;
				         delay_ms(tempo);
				         
				         // Mostra o valor das unidades dos segundos
				         output_d(display[U_seg]);
				         Display_unidade_segundo;
				         delay_ms(tempo);     
		             }          
	             }
	         }
	    }          
	    
	}
}
