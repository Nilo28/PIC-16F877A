; Discente: Nilo Rodrigues Alves Filho
; Questão 5:
; Faça um programa em assembly que zere a memória de dados do banco 0 nos endereços de 0x20 a 0x7f e para facilitar utilize os registradores INDF e FSR. 
; Dica: Página 31 do datasheet

; OBSERVAÇÕES:
; FSR é o ponteiro que indica o endereço a ser alterado;
; INDF é o registrador que alterará o valor presente no endereço indicado por FSR;
; O endereço 0x20 corresponde ao 0b00100000 e o endereço 0x7F corresponde ao 0b01111111;
; Logo quando o ponteiro FSR indicar o endereço seguinte 0x80 (0b10000000) deverá cessar a limpeza;
; O endereço 0x80 pertence ao banco 1.


#INCLUDE <P16F877A.INC>						; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF					; Clock interno de 4MHz e WDT desligado
ORG 0x00									; Armazena o código a partir do endereço 0x00

BANKSEL TMR0								; Seleciona o banco 0


INICIO										; Marca o início do código principal	
	
	MOVLW 		0x20 							
	MOVWF 		FSR 						; FSR está com endereço 0x20
	REPETE									; Marca o local onde a repetição deve começar
	CLRF 		INDF 						; Limpa o espaço que possui o endereço indicado por FSR  
	INCF 		FSR 						; Incrementar o ponteiro FSR
	BTFSS 		FSR,7   					; Verifica se o endereço é 0x80, se sim pula a próxima linha.
	GOTO 		REPETE						; Retorna para REPETE

FIM											; Marca o fim do código principal




END ; Fim do programa
