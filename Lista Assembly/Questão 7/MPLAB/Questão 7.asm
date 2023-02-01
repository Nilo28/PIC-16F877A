; Discente: Nilo Rodrigues Alves Filho
; Questão 7:
; Com base na página 36 do datasheet do microcontrolador (Seção 3.5): 
; -> elabore um programa que faça a leitura de cada posição da memória de programa (do tipo Flash) e some o conteúdo de cada posição, 
; -> levando em conta apenas a parte menos significativa (ou seja, os 8 bits menos significativos, para facilitar, ao invés dos 14 bits). 
; Considere que o programa a ser lido começa do endereço PROG _INICIO igual a 0x00 e vai até o endereço PROG _FIM igual a 0x08. 
; 0x20 armazenará a parte baixa da soma
; 0x21 armazenará a parte alta da soma

#INCLUDE <P16F877A.INC>								; Inclui biblioteca do PIC 16F877A

cblock H'20'
L
H
endc

ORG 0x00											; Armazena o código a partir do endereço 0x00

INICIO												; Marca o inicio do código

	 BANKSEL	EEADR								; Seleciona o Banco 2
	 MOVLW 		0x00 								; 
	 MOVWF 		EEADR 								; Endereço do byte menos significativo
	 CLRF 		L									; Limpa o endereço 0x20
	 CLRF 		H 									; Limpa o endereço 0x21
	 
	 REPETE
		BANKSEL	 	EECON1							; Seleciona o Banco 3
		BSF 		EECON1, EEPGD 				
		BSF 		EECON1, RD 			
		NOP	
		NOP
		
		BANKSEL 	EEADR							; Seleciona o Banco 2
		MOVF		EEDATA, W						; Move o valor para W
		ADDWF 		L, F							; Soma o valor do oprando para W
		BTFSC		STATUS, C						; Verifica se há carry na soma
		INCF		H, F							; Se sim, soma um para o próximo registrador
		INCF 		EEADR							; Aumenta para o proximo endereço
		BTFSS 		EEADR, 3						; Verifica se o endereço é 0x08
	 	GOTO 		REPETE							; Repete
	
	FIM												; Marca o fim do código


END ; Fim do programa