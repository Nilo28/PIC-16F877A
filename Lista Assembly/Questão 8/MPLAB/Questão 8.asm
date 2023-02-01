; Discente: Nilo Rodrigues Alves Filho
; Quest�o :
; Um cabo el�trico possui 4 fios. 
; De um lado do cabo, cada fio � numerado de 1 a 4. 
; Do outro lado do cabo, cada fio � ligado a um fio apenas, para formar um par com ele. 
; Fa�a um programa para detectar os pares de fios. 
; A sa�da do programa vai corresponder aos pares. 
; Se sorte que a informa��o de um par estar� na porta C e do outro par na porta D. 
; Ex: Fio 1 ligado no 4 e o fio 2 ligado no 3. 
; Ent�o: Teremos o par 1-4 e o par 2-3. 
; Ent�o: PORTC = 14 e PORTD igual a 23. 

; OBSERVA��ES
; RB1 -> Fio 1 (SA�DA)
; RB2 -> Fio 2 (ENTRADA)
; RB3 -> Fio 3 (ENTRADA)
; RB4 -> Fio 4 (ENTRADA)
;
; O fio conectado ao fio 1, receber� no pino de entrada o sinal de sa�da RA0. Assim ser� poss�vel identificar os pares


#INCLUDE <P16F877A.INC>						; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF					; Clock interno de 4MHz e WDT desligado
ORG 0x00									; Armazena o c�digo a partir do endere�o 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------

	; Configurando TRISD
	BANKSEL 		TRISD								; Seleciona o Banco 1
	MOVLW 		B'00011100'							
	MOVWF 		TRISB
	MOVLW 		B'00000000'							
	MOVWF 		TRISC									; Define RD0 e RD1 como entradas e RD7 como sa�da							
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
	
	FIM											; Marca o fim do c�digo

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
