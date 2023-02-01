; GRUPO:
; Ant�nio Gustavo da Silva Moura
; Manoel Barroso da Silva Moura
; Nilo Rodrigues Alves Filho
;
; Diminuir o tempo do c�digo original para utilizar um fator de corre��o depois
;
; Programa para mudar o estado do pino RA0 baseando-se no ciclo de m�quina
; Clock: 4MHz
; Ciclo de m�quina = 1 / (Clock /4) = 1us
; MCU: PIC16F877A

 #include <p16f877a.inc>
; CONFIGURAR OS FUSES DO PROCESSADOR
	__CONFIG _WDT_OFF & _LVP_OFF & _XT_OSC & _PWRTE_ON & _CP_OFF

; MAPEAMENTO DE MEM�RIA (RP1 fixo 1)
 #define	bank0	bcf	STATUS,RP0	;Cria um mnem�nico para selecionar o banco 0 de mem�ria
 #define	bank1	bsf	STATUS,RP0	;Cria um mnem�nico para selecionar o banco 1 de mem�ria

; SA�DA
 #define	output		PORTB,0		;RB0 ser� chamado de sa�da (output)
 
 
; VETOR DE RESET
	org	0x00		;Origem no endere�o 00h
	nop
	nop
	goto inicio		;Vai para a label inicio
	nop

; VETOR DE INTERRUP��O
	org	0x04			;Origem da interrup��o
	retfie				;Retorna da interrup��o

; VARI�VEIS
	cblock	0x20		;Endere�o para vari�veis
	tempo0				;Vari�vel de temporiza��o
	tempo1				;Vari�vel de temporiza��o
	tempo2
	endc				;Final da mem�ria do usu�rio

inicio:
	bank1				;Seleciona o banco1 de mem�ria
	
	movlw	0x00		;Move literal 00h para work. W = 00h
	movwf	TRISB		;TRISB = 0 (Todo PORTB � sa�da digital)
 
 	movlw   H'06'		; (0b0000 011x)
   	movwf   ADCON1		;Desabilita  A/D do PIC16F877A

	bank0				;Seleciona o banco0 de mem�ria
	
	movlw	0x00		;Move 00h para W.
	movwf	PORTB		;Todo PORTB inicio em n�vel LOW

loop:
	bsf		output		;RB0 em n�vel HIGH set 1
	call	delay500ms	;Chama a sub rotina de delay
	bcf		output		;RB0 em n�vel LOW clear 0
	call	delay500ms	;Chama a sub rotina de delay
	goto	loop		;Loop infinito

delay500ms:
	movlw	.195		
	movwf	tempo0		;Inicializa a vari�vel tempo0 
						; 4 ciclos de m�quina
	aux1:
	movlw	.256		
	movwf	tempo1		;Inicializa a vari�vel tempo1
						; 2 ciclos de m�quina   
						;6

 	aux2:
	nop					;Gastar 1 ciclo de m�quina
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz	tempo1		;Decrementa tempo1 at� que seja igual a zero
	goto	aux2		;Vai para a label aux2 
						;9 ciclos
											
	decfsz	tempo0		;Decrementa tempo0 at� que seja igual a zero
	goto	aux1		;Vai para a label aux1

						; 3 ciclos de m�quina
	;Fator de corre��o 16us	
	movlw	.4
	movwf	tempo2	
	nop
						;3ciclos
	loop2:
	decfsz tempo2		
	goto loop2
	nop
	return				;Retorna ap�s a chamada da sub rotina

	end					;Final do Programa
