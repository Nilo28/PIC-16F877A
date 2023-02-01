; Discente: Nilo Rodrigues Alves Filho
; Quest�o 2:
; Idem para uma porta "ou".


#INCLUDE <P16F877A.INC>							; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF						; Clock interno de 4MHz e WDT desligado
ORG 0x00										; Armazena o c�digo a partir do endere�o 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------
	; Configurando TRISD
	BANKSEL 	TRISD								; Seleciona o Banco 1
	MOVLW 		B'00000011'							
	MOVWF 		TRISD								; Define RD0 e RD1 como entradas e RD7 como sa�da
	
	; Configurando PORTD
	BANKSEL 	PORTD								; Seleciona o Banco 0							
	CLRF 		PORTD								; Limpa a porta D

; ----------------------------------------------------------------------------------------------------------


LOOP; ---------------------------------------- LOOP INFINITO ----------------------------------------------

	INICIO											; Marca o in�cio do c�digo
	
	BTFSC 		PORTD, 0							; Pula se RD0 for 0
	CALL		pino_um								; Executa a sub-rotina pino_zero quando RD0 for 1
	BTFSC 		PORTD, 1							; Pula se RD1 for 0
	CALL 		pino_um								; Executa a sub-rotina pino_zero quando RD1 for 1
	BCF 		PORTD, 7							; Pino RD7 ser� 0
	
	FIM												; Marca o fim do c�digo

GOTO LOOP; ------------------------------   FIM LOOP INFINITO ----------------------------------------------



; ------------------------------------------ SUB-ROTINAS ---------------------------------------------------

pino_um:
			BSF PORTD,7								; Pino RD7 ser� 1
			GOTO FIM								; Retorna para o fim do programa		

; ----------------------------------------------------------------------------------------------------------


END ; Fim do programa
