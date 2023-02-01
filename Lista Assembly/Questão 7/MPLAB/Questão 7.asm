; Discente: Nilo Rodrigues Alves Filho
; Quest�o 7:
; Com base na p�gina 36 do datasheet do microcontrolador (Se��o 3.5): 
; -> elabore um programa que fa�a a leitura de cada posi��o da mem�ria de programa (do tipo Flash) e some o conte�do de cada posi��o, 
; -> levando em conta apenas a parte menos significativa (ou seja, os 8 bits menos significativos, para facilitar, ao inv�s dos 14 bits). 
; Considere que o programa a ser lido come�a do endere�o PROG _INICIO igual a 0x00 e vai at� o endere�o PROG _FIM igual a 0x08. 
; 0x20 armazenar� a parte baixa da soma
; 0x21 armazenar� a parte alta da soma

#INCLUDE <P16F877A.INC>								; Inclui biblioteca do PIC 16F877A

cblock H'20'
L
H
endc

ORG 0x00											; Armazena o c�digo a partir do endere�o 0x00

INICIO												; Marca o inicio do c�digo

	 BANKSEL	EEADR								; Seleciona o Banco 2
	 MOVLW 		0x00 								; 
	 MOVWF 		EEADR 								; Endere�o do byte menos significativo
	 CLRF 		L									; Limpa o endere�o 0x20
	 CLRF 		H 									; Limpa o endere�o 0x21
	 
	 REPETE
		BANKSEL	 	EECON1							; Seleciona o Banco 3
		BSF 		EECON1, EEPGD 				
		BSF 		EECON1, RD 			
		NOP	
		NOP
		
		BANKSEL 	EEADR							; Seleciona o Banco 2
		MOVF		EEDATA, W						; Move o valor para W
		ADDWF 		L, F							; Soma o valor do oprando para W
		BTFSC		STATUS, C						; Verifica se h� carry na soma
		INCF		H, F							; Se sim, soma um para o pr�ximo registrador
		INCF 		EEADR							; Aumenta para o proximo endere�o
		BTFSS 		EEADR, 3						; Verifica se o endere�o � 0x08
	 	GOTO 		REPETE							; Repete
	
	FIM												; Marca o fim do c�digo


END ; Fim do programa