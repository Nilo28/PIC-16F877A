; Discente: Nilo Rodrigues Alves Filho
; Quest�o 1:
; Que implemente uma porta l�gica "and" com duas entradas correspondentes aos pinos RD0 e RD1 e sa�da em RD7.


#INCLUDE <P16F877A.INC>						; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF					; Clock interno de 4MHz e WDT desligado
ORG 0x00									; Armazena o c�digo a partir do endere�o 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------
	; Configurando TRISD
	BANKSEL 	TRISD								; Seleciona o Banco 1
	MOVLW 		B'00000011'							
	MOVWF 		TRISD								; Define RD0 e RD1 como entradas e RD7 como sa�da
	
	; Configurando PORTD
	BANKSEL 	PORTD								; Seleciona o Banco 0						
	CLRF 		PORTD								; Limpa a porta D
; ----------------------------------------------------------------------------------------------------------


LOOP; ----------- INICIO LOOP INFINITO ---------------------------------------------------------------------

	INICIO										; Marca o in�cio do c�digo

	BTFSS	PORTD, 0							; Pula se RD0 for 1
	CALL 	pino_zero							; Executa a sub-rotina pino_zero quando RD0 for 0
	BTFSS 	PORTD, 1							; Pula se RD1 for 1
	CALL 	pino_zero							; Executa a sub-rotina pino_zero quando RD1 for 0
	BSF 	PORTD, 7							; Pino RD7 ser� 1

	FIM											; Marca o fim do c�digo
	
GOTO LOOP; ------- FIM LOOP INFINITO -----------------------------------------------------------------------



; -----------------  SUB-ROTINAS  ---------------------------------------------------------------------------

pino_zero:
			BCF PORTD,7						; Pino RD7 ser� 0
			GOTO FIM						; Retorna para o fim do programa
			
;------------------------------------------------------------------------------------------------------------

END ; Fim do programa
