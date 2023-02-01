; Discente: Nilo Rodrigues Alves Filho
; Questão :
; Um cabo elétrico possui 4 fios. 
; De um lado do cabo, cada fio é numerado de 1 a 4. 
; Do outro lado do cabo, cada fio é ligado a um fio apenas, para formar um par com ele. 
; Faça um programa para detectar os pares de fios. 
; A saída do programa vai corresponder aos pares. 
; Se sorte que a informação de um par estará na porta C e do outro par na porta D. 
; Ex: Fio 1 ligado no 4 e o fio 2 ligado no 3. 
; Então: Teremos o par 1-4 e o par 2-3. 
; Então: PORTC = 14 e PORTD igual a 23. 

; OBSERVAÇÕES
; RB1 -> Fio 1 (SAÍDA)
; RB2 -> Fio 2 (ENTRADA)
; RB3 -> Fio 3 (ENTRADA)
; RB4 -> Fio 4 (ENTRADA)
;
; O fio conectado ao fio 1, receberá no pino de entrada o sinal de saída RA0. Assim será possível identificar os pares


#INCLUDE <P16F877A.INC>						; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF					; Clock interno de 4MHz e WDT desligado
ORG 0x00									; Armazena o código a partir do endereço 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------

	; Configurando TRISD
	BANKSEL 		TRISD								; Seleciona o Banco 1
	MOVLW 		B'00011100'							
	MOVWF 		TRISB
	MOVLW 		B'00000000'							
	MOVWF 		TRISC									; Define RD0 e RD1 como entradas e RD7 como saída							
	MOVWF 		TRISD	
	
	; Configurando PORTD
	BANKSEL 	PORTD									; Seleciona o Banco 0
	MOVLW 		B'00000010'
	MOVWF 		PORTB
	MOVLW 		B'00000000'
	MOVWF 		PORTC								
	MOVWF 		PORTD									; Limpa a porta D
	

; ----------------------------------------------------------------------------------------------------------




LOOP; ---------------------------------------- LOOP INFINITO ----------------------------------------------

	INICIO

	BTFSC 		PORTB, 2
	CALL 		port_dois
	BTFSC 		PORTB, 3
	CALL 		port_tres
	BTFSC 		PORTB, 4
	CALL 		port_quatro
	
	FIM											; Marca o fim do código

GOTO LOOP; ------------------------------   FIM LOOP INFINITO ----------------------------------------------






; ------------------------------------------ SUB-ROTINAS ---------------------------------------------------

	port_dois:	
				MOVLW 		D'12'
			  	MOVWF 		PORTC
			  	MOVLW 		D'34'
			  	MOVWF 		PORTD
			  	GOTO FIM	
	
	port_tres:
				MOVLW 		D'13'
			  	MOVWF 		PORTC
			  	MOVLW 		D'24'
			  	MOVWF 		PORTD
			  	GOTO FIM
				
	port_quatro:
			  	MOVLW 		D'14'
			  	MOVWF 		PORTC
			  	MOVLW 		D'23'
			  	MOVWF 		PORTD
			  	GOTO FIM			

; ----------------------------------------------------------------------------------------------------------



END ; Fim do programa
