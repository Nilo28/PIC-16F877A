; Discente: Nilo Rodrigues Alves Filho
; Questão 6:
; Faça um programa para multiplicar dois operandos de 8 bits sem sinal, ou seja, considerando apenas valores positivos. 
; O resultado da multiplicação terá a sua parte alta no endereço 0x21 e a parte baixa estará no endereço 0x20. 
; Os operandos de 8 bits estarão no endereço 0x30 e 0x31 da memória de dados. 
; Considere todos os endereços mencionados no banco 0. 
; 2^8 = 256. Número máx é 255.


#INCLUDE <P16F877A.INC>									; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF							; Clock interno de 4MHz e WDT desligado
ORG 0x00											; Armazena o código a partir do endereço 0x00

INICIO

BANKSEL TMR0											; Seleciona o Banco 0

	MOVLW 	D'2'										; Valor do primeiro operando
	MOVWF 	0x30										; Endereço do primeiro operando
	MOVLW	D'4'										; Valor do segundo operando
	MOVWF	0x31										; Endereço do segundo operando
	CALL	mult
	GOTO FIM											; Finaliza o código
	
mult:
			MOVLW	D'0'									; Limpa o resultado
			MOVWF	0x20									; Limpa a parte baixa 
			MOVWF	0x21									; Limpa a parte alta
			MOVF 	0x30, W								
			MOVWF	0x20									; Primeiro operando para o Resultado										
	REPETE
			DECF 	0x31,F									; Decrementa o segundo operando(uma soma a menos)
			BTFSC	STATUS, Z								; Verifica se o segundo operando é zero(finalizou a soma?)
			RETURN											; Se sim, retorna
			MOVF	0x30, W									; Move o primeiro operando para W
			ADDWF 	0x20, F									; Soma o valor do oprando para W
			BTFSC	STATUS, C								; Verifica se há carry na soma
			INCF	0x21, F									; Se houver, adiciona 1 ao próximo registrador
			GOTO 	REPETE								; Volta para REPETE
FIM
 
END ; Fim do programa
