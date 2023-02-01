; Discente: Nilo Rodrigues Alves Filho
; Quest�o 4:
; Que relacione a sa�da RD7 com as entradas RD2 a RD0 com base na tabela verdade abaixo. 
; Para facilitar, determine uma express�o l�gica booleana que relacione a sa�da RD7 com as entradas RD2, RD1 e RD0.
; Com base nessa express�o que voc� encontrar, escreva o programa, considerando que a entrada RD2 representa o bit mais significativo enquanto que a entrada RD0, o bit menos significativo. 
;
; OBSERVA��ES:
; -> Quando RD2 = 0 a sa�da RD7 � igual a sa�da OR entre RD0 e RD1
; -> Quando RD2 = 1 a sa�da RD7 � igual ao sinal de entrada RD0.
; -> Express�o de sa�da: d2'(d0d1) + d2d0
; -> dx: pino x normal | dx': pino x barrado
;
; RD2  RD1  RD0     RD7
;  0    0    0       0
;  0    0    1       1  
;  0    1    0       1
;  0    1    1       1
;  1    0    0       0
;  1    0    1       1
;  1    1    0       0
;  1    1    1       1    


#INCLUDE <P16F877A.INC>								; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF							; Clock interno de 4MHz e WDT desligado
ORG 0x00											; Armazena o c�digo a partir do endere�o 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------

	; Configurando TRISD
	BANKSEL		TRISD								; Seleciona o Banco 1
	MOVLW 		B'00000111'							
	MOVWF 		TRISD								; Define RD0, RD1, RD2 como entradas e RD7 como sa�da
	
	; Configurando PORTD
	BANKSEL 	PORTD								; Seleciona o Banco 0
	CLRF 		PORTD								; Limpa a porta D

; ----------------------------------------------------------------------------------------------------------



LOOP; ---------------------------------------- LOOP INFINITO ----------------------------------------------

	INICIO											; Marca o in�cio do c�digo principal
	
	BTFSS 		PORTD,2								; Pula a pr�xima linha se o RD2 for 1
	CALL 		rd2_zero							; Executa a rotina rd2_zero
	CALL 		rd2_um								; Executa a rotina rd2_um
		
	FIM												; Marca o fim do c�digo

GOTO LOOP; ------------------------------   FIM LOOP INFINITO ----------------------------------------------



; ------------------------------------------ SUB-ROTINAS ---------------------------------------------------

rd2_zero:											; L�gica OR
			BTFSC 		PORTD, 0					; Pula a pr�xima linha se RD0 for 0
			CALL 		pino_um						; Executa a sub-rotina pino_um
			BTFSC 		PORTD, 1					; Pula se RD1 for 0
			CALL 		pino_um						; Executa a sub-rotina pino_um
			CALL 		pino_zero					; Executa a sub-rotina pino_zero

rd2_um:												; Sa�da igual a RD0
			BTFSC 		PORTD, 0					; Pula a pr�xima linha se RD0 for 0
			CALL 		pino_um						; Executa a sub-rotina pino_um						
			CALL 		pino_zero					; Executa a sub-rotina pino_zero
	
pino_um:										
			BSF 		PORTD,7						; Pino RD7 ser� 1
			GOTO 		FIM							; Retorna para o FIM

pino_zero: 										
			BCF 		PORTD,7						; Pino RD7 ser� 0
			GOTO 		FIM							; Retorna para o FIM
			

; ----------------------------------------------------------------------------------------------------------



END ; Fim do programa
