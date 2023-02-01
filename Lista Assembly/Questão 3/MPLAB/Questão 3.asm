; Discente: Nilo Rodrigues Alves Filho
; Quest�o 3:
; Que implemente um somador completo de 1 bit. 
; Sendo o RD0 o "carry in", RD1 � o bit do primeiro operando, RD2 � o bit do segundo operando e RD3 o "carry out". .
;
; OBSERVA��ES:
; -> Quando Cin = 0 a sa�da � igual a sa�da AND entre A e B
; -> Quando Cin = 1 a sa�da � igual a sa�da OR entre A e B
;
; CIN A  B   COUT
;  0  0  0    0
;  0  0  1    0
;  0  1  0    0
;  0  1  1    1 
;
;  1  0  0    0
;  1  0  1    1
;  1  1  0    1
;  1  1  1    1


#INCLUDE <P16F877A.INC>							; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF						; Clock interno de 4MHz e WDT desligado
ORG 0x00										; Armazena o c�digo a partir do endere�o 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------

	; Configurando TRISD
	BANKSEL 		TRISD							; Seleciona o Banco 1
	MOVLW 		B'00000111'						
	MOVWF 		TRISD								; Define RD0, RD1 e RD2 como entradas e define RD3 como sa�da
	
	; Configurando PORTD
	BANKSEL 	PORTD								; Seleciona o Banco 0							
	CLRF 		PORTD								; Limpa a porta D

; ----------------------------------------------------------------------------------------------------------



LOOP; ---------------------------------------- LOOP INFINITO ----------------------------------------------

	INICIO										;Marca o in�cio do c�digo principal
	
	
	BTFSC 		PORTD, 0						; Pula se RD0 for 0
	CALL		cin_um							; Executa a sub-rotina cin_um quando RD0 for 1
	CALL 		cin_zero						; Executa a sub-rotina cin_zero quando RD0 for 0
	
	
	FIM											; Marca o fim do c�digo

GOTO LOOP; ------------------------------   FIM LOOP INFINITO ----------------------------------------------



; ------------------------------------------ SUB-ROTINAS ---------------------------------------------------

cin_zero:										; L�gica AND
			BTFSS 		PORTD, 1				; Pula se RD1 for 1
			CALL 		pino_zero				; Executa a sub-rotina pino_zero quando RD0 for 0
			BTFSS 		PORTD, 2				; Pula se RD2 for 1
			CALL 		pino_zero				; Executa a sub-rotina pino_zero quando RD1 for 0
			BSF 		PORTD, 3				; Pino RD3 ser� 1
			GOTO 		FIM						; Retorna para o FIM
			
cin_um:           								; L�gica OR
			BTFSC 		PORTD, 1				; Pula se RD1 for 0
			CALL 		pino_um					; Executa a sub-rotina pino_zero quando RD0 for 1
			BTFSC 		PORTD, 2				; Pula se RD2 for 0
			CALL 		pino_um					; Executa a sub-rotina pino_zero quando RD1 for 1
			BCF 		PORTD, 3				; Pino RD3 ser� 0
			GOTO 		FIM						; Retorna para o FIM
			
pino_zero:
			BCF 		PORTD,3					; Pino RD3 ser� 0
			GOTO 		FIM						; Retorna para o FIM
			
			
pino_um:
			BSF 		PORTD,3					; Pino RD3 ser� 1
			GOTO 		FIM						; Retorna para o FIM		

; ----------------------------------------------------------------------------------------------------------



END ; Fim do programa
