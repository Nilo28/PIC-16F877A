; Discente: Nilo Rodrigues Alves Filho
; Questão 3:
; Que implemente um somador completo de 1 bit. 
; Sendo o RD0 o "carry in", RD1 é o bit do primeiro operando, RD2 é o bit do segundo operando e RD3 o "carry out". .
;
; OBSERVAÇÕES:
; -> Quando Cin = 0 a saída é igual a saída AND entre A e B
; -> Quando Cin = 1 a saída é igual a saída OR entre A e B
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
ORG 0x00										; Armazena o código a partir do endereço 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------

	; Configurando TRISD
	BANKSEL 		TRISD							; Seleciona o Banco 1
	MOVLW 		B'00000111'						
	MOVWF 		TRISD								; Define RD0, RD1 e RD2 como entradas e define RD3 como saída
	
	; Configurando PORTD
	BANKSEL 	PORTD								; Seleciona o Banco 0							
	CLRF 		PORTD								; Limpa a porta D

; ----------------------------------------------------------------------------------------------------------



LOOP; ---------------------------------------- LOOP INFINITO ----------------------------------------------

	INICIO										;Marca o início do código principal
	
	
	BTFSC 		PORTD, 0						; Pula se RD0 for 0
	CALL		cin_um							; Executa a sub-rotina cin_um quando RD0 for 1
	CALL 		cin_zero						; Executa a sub-rotina cin_zero quando RD0 for 0
	
	
	FIM											; Marca o fim do código

GOTO LOOP; ------------------------------   FIM LOOP INFINITO ----------------------------------------------



; ------------------------------------------ SUB-ROTINAS ---------------------------------------------------

cin_zero:										; Lógica AND
			BTFSS 		PORTD, 1				; Pula se RD1 for 1
			CALL 		pino_zero				; Executa a sub-rotina pino_zero quando RD0 for 0
			BTFSS 		PORTD, 2				; Pula se RD2 for 1
			CALL 		pino_zero				; Executa a sub-rotina pino_zero quando RD1 for 0
			BSF 		PORTD, 3				; Pino RD3 será 1
			GOTO 		FIM						; Retorna para o FIM
			
cin_um:           								; Lógica OR
			BTFSC 		PORTD, 1				; Pula se RD1 for 0
			CALL 		pino_um					; Executa a sub-rotina pino_zero quando RD0 for 1
			BTFSC 		PORTD, 2				; Pula se RD2 for 0
			CALL 		pino_um					; Executa a sub-rotina pino_zero quando RD1 for 1
			BCF 		PORTD, 3				; Pino RD3 será 0
			GOTO 		FIM						; Retorna para o FIM
			
pino_zero:
			BCF 		PORTD,3					; Pino RD3 será 0
			GOTO 		FIM						; Retorna para o FIM
			
			
pino_um:
			BSF 		PORTD,3					; Pino RD3 será 1
			GOTO 		FIM						; Retorna para o FIM		

; ----------------------------------------------------------------------------------------------------------



END ; Fim do programa
