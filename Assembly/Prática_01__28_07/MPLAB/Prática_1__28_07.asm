; GRUPO:
; Antônio Gustavo da Silva Moura
; Manoel Barroso da Silva Moura
; Nilo Rodrigues Alves Filho
;
; Diminuir o tempo do código original para utilizar um fator de correção depois
;
; Programa para mudar o estado do pino RA0 baseando-se no ciclo de máquina
; Clock: 4MHz
; Ciclo de máquina = 1 / (Clock /4) = 1us
; MCU: PIC16F877A

 #include <p16f877a.inc>
; CONFIGURAR OS FUSES DO PROCESSADOR
	__CONFIG _WDT_OFF & _LVP_OFF & _XT_OSC & _PWRTE_ON & _CP_OFF

; MAPEAMENTO DE MEMÓRIA (RP1 fixo 1)
 #define	bank0	bcf	STATUS,RP0	;Cria um mnemônico para selecionar o banco 0 de memória
 #define	bank1	bsf	STATUS,RP0	;Cria um mnemônico para selecionar o banco 1 de memória

; SAÍDA
 #define	output		PORTB,0		;RB0 será chamado de saída (output)
 
 
; VETOR DE RESET
	org	0x00		;Origem no endereço 00h
	nop
	nop
	goto inicio		;Vai para a label inicio
	nop

; VETOR DE INTERRUPÇÃO
	org	0x04			;Origem da interrupção
	retfie				;Retorna da interrupção

; VARIÁVEIS
	cblock	0x20		;Endereço para variáveis
	tempo0				;Variável de temporização
	tempo1				;Variável de temporização
	tempo2
	endc				;Final da memória do usuário

inicio:
	bank1				;Seleciona o banco1 de memória
	
	movlw	0x00		;Move literal 00h para work. W = 00h
	movwf	TRISB		;TRISB = 0 (Todo PORTB é saída digital)
 
 	movlw   H'06'		; (0b0000 011x)
   	movwf   ADCON1		;Desabilita  A/D do PIC16F877A

	bank0				;Seleciona o banco0 de memória
	
	movlw	0x00		;Move 00h para W.
	movwf	PORTB		;Todo PORTB inicio em nível LOW

loop:
	bsf		output		;RB0 em nível HIGH set 1
	call	delay500ms	;Chama a sub rotina de delay
	bcf		output		;RB0 em nível LOW clear 0
	call	delay500ms	;Chama a sub rotina de delay
	goto	loop		;Loop infinito

delay500ms:
	movlw	.195		
	movwf	tempo0		;Inicializa a variável tempo0 
						; 4 ciclos de máquina
	aux1:
	movlw	.256		
	movwf	tempo1		;Inicializa a variável tempo1
						; 2 ciclos de máquina   
						;6

 	aux2:
	nop					;Gastar 1 ciclo de máquina
	nop
	nop
	nop
	nop
	nop
	nop
	decfsz	tempo1		;Decrementa tempo1 até que seja igual a zero
	goto	aux2		;Vai para a label aux2 
						;9 ciclos
											
	decfsz	tempo0		;Decrementa tempo0 até que seja igual a zero
	goto	aux1		;Vai para a label aux1

						; 3 ciclos de máquina
	;Fator de correção 16us	
	movlw	.4
	movwf	tempo2	
	nop
						;3ciclos
	loop2:
	decfsz tempo2		
	goto loop2
	nop
	return				;Retorna após a chamada da sub rotina

	end					;Final do Programa
