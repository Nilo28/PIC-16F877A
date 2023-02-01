; Discente: Nilo Rodrigues Alves Filho
; Quest�o 6:
; Fa�a um programa para multiplicar dois operandos de 8 bits sem sinal, ou seja, considerando apenas valores positivos. 
; O resultado da multiplica��o ter� a sua parte alta no endere�o 0x21 e a parte baixa estar� no endere�o 0x20. 
; Os operandos de 8 bits estar�o no endere�o 0x30 e 0x31 da mem�ria de dados. 
; Considere todos os endere�os mencionados no banco 0. 
; 2^8 = 256. N�mero m�x � 255.


#INCLUDE <P16F877A.INC>									; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF							; Clock interno de 4MHz e WDT desligado
ORG 0x00											; Armazena o c�digo a partir do endere�o 0x00

INICIO

BANKSEL TMR0											; Seleciona o Banco 0

	MOVLW 	D'2'										; Valor do primeiro operando
	MOVWF 	0x30										; Endere�o do primeiro operando
	MOVLW	D'4'										; Valor do segundo operando
	MOVWF	0x31										; Endere�o do segundo operando
	CALL	mult
	GOTO FIM											; Finaliza o c�digo
	
mult:
			MOVLW	D'0'									; Limpa o resultado
			MOVWF	0x20									; Limpa a parte baixa 
			MOVWF	0x21									; Limpa a parte alta
			MOVF 	0x30, W								
			MOVWF	0x20									; Primeiro operando para o Resultado										
	REPETE
			DECF 	0x31,F									; Decrementa o segundo operando(uma soma a menos)
			BTFSC	STATUS, Z								; Verifica se o segundo operando � zero(finalizou a soma?)
			RETURN											; Se sim, retorna
			MOVF	0x30, W									; Move o primeiro operando para W
			ADDWF 	0x20, F									; Soma o valor do oprando para W
			BTFSC	STATUS, C								; Verifica se h� carry na soma
			INCF	0x21, F									; Se houver, adiciona 1 ao pr�ximo registrador
			GOTO 	REPETE								; Volta para REPETE
FIM
 
END ; Fim do programa
