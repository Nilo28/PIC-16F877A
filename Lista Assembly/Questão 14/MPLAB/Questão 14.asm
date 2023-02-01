; Discente: Nilo Rodrigues Alves Filho
; Questão 14:
; Faça um programa para configurar o TIMER0 como contador de eventos externos a cada borda de subida do clock.
; O resultado da contagem estará sempre na porta D. 



#INCLUDE <P16F877A.INC>						; Inclui biblioteca do PIC 16F877A

__CONFIG _XT_OSC & _WDT_OFF					; Clock interno de 4MHz e WDT desligado
ORG 0x00									; Armazena o código a partir do endereço 0x00

; REGISTRADORES --------------------------------------------------------------------------------------------

	; Configurando TRISD
	BANKSEL 	TRISD								; Seleciona o Banco 1
	MOVLW 		B'000000000'							
	MOVWF 		TRISD									; Define a porta D como saída
	MOVLW 		B'00010000'
	MOVWF 		TRISA									; Define RA4 como entrada

	; Configurando PORTD
	BANKSEL 	PORTD								; Seleciona o Banco 0							
	MOVLW 		B'00000000'
	MOVWF 		PORTD									; Limpa a porta D
	MOVWF 		PORTA									; Limpa a porta A
	MOVWF 		TMR0									; Limpa o TMR0
	
	; Configurando TIMER0
	BANKSEL 	OPTION_REG							; Seleciona o Banco 1
	MOVLW 		B'11100000'
	MOVWF 		INTCON								; Habilita interrupção do Timer0
	MOVLW 		B'10101000'
	MOVWF 		OPTION_REG							; Modo contador; borda de subida; sem prescaler;

; ----------------------------------------------------------------------------------------------------------

BANKSEL 	TMR0

LOOP; ---------- INICIO LOOP INFINITO ----------------------------------------------------------------------

	INICIO										; Marca o início do código
	
	MOVF 		TMR0, W
	MOVWF 		PORTD
	
	FIM											; Marca o fim do código

GOTO LOOP; ------ FIM LOOP INFINITO ------------------------------------------------------------------------


END ; Fim do programa