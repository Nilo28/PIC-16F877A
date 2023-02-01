; GRUPO:
; Ant�nio Gustavo da Silva Moura
; Manoel Barroso da Silva Moura
; Nilo Rodrigues Alves Filho

#include <P16F877A.INC>;inclui biblioteca do PIC a ser usado
	__CONFIG _WDT_OFF & _LVP_OFF & _XT_OSC & _PWRTE_ON & _CP_OFF
	org H'00' 
	nop
	nop
	goto inicio
	nop
   
;Etapa de configura��o
	
inicio:	
	
	; Muda o banco de registradores (Banco 1 - 01 )
	bsf STATUS, RP0		; Desliga bit STATUS,RP1.
	bcf STATUS, RP1
	; Os bot�es e os LEDs est�o conectados � porta B
	;
	; Configura ADCON1
	; O registrador ADCON1 possui oito bits, sendo que os quatros menos significativos definem os pinos como anal�gicos/digital 
	; 0000 0110 -> Todos os pinos como digitais.(xxxx 011x)
	;
    movlw H'06'
    movwf ADCON1
    
    ; Configura PORTB
    movlw B'11111110'	; Configura RB0 como sa�da e RB1 como entrada.
    movwf TRISB
    
    ; Muda o banco de registradores (Banco 0 - 00)
    bcf STATUS,RP0
    
; C�digo principal    
main: btfsc PORTB,1		; Pula se RB1 for zero 
     goto desliga		; Vai para 'desliga'
     
liga: bsf PORTB,0 		; Liga o LED	
     goto main			; Retorna para 'main'

desliga: bcf PORTB,0	; Desliga o LED
     goto main			; Retorna para 'main'
end