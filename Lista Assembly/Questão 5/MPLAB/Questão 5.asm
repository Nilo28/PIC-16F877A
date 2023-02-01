; Discente: Nilo Rodrigues Alves Filho
; Quest�o 5:
; Fa�a um programa em assembly que zere a mem�ria de dados do banco 0 nos endere�os de 0x20 a 0x7f e para facilitar utilize os registradores INDF e FSR. 
; Dica: P�gina 31 do datasheet

; OBSERVA��ES:
; FSR � o ponteiro que indica o endere�o a ser alterado;
; INDF � o registrador que alterar� o valor presente no endere�o indicado por FSR;
; O endere�o 0x20 corresponde ao 0b00100000 e o endere�o 0x7F corresponde ao 0b01111111;
; Logo quando o ponteiro FSR indicar o endere�o seguinte 0x80 (0b10000000) dever� cessar a limpeza;
; O endere�o 0x80 pertence ao banco 1.


#INCLUDE <P16F877A.INC>						; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF					; Clock interno de 4MHz e WDT desligado
ORG 0x00									; Armazena o c�digo a partir do endere�o 0x00

BANKSEL TMR0								; Seleciona o banco 0


INICIO										; Marca o in�cio do c�digo principal	
	
	MOVLW 		0x20 							
	MOVWF 		FSR 						; FSR est� com endere�o 0x20
	REPETE									; Marca o local onde a repeti��o deve come�ar
	CLRF 		INDF 						; Limpa o espa�o que possui o endere�o indicado por FSR  
	INCF 		FSR 						; Incrementar o ponteiro FSR
	BTFSS 		FSR,7   					; Verifica se o endere�o � 0x80, se sim pula a pr�xima linha.
	GOTO 		REPETE						; Retorna para REPETE

FIM											; Marca o fim do c�digo principal




END ; Fim do programa
