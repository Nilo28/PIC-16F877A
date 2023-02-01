;Programa em assembly analisado em sala de aula

#include <P16F877a.INC> 				;inclui biblioteca do PIC a ser usado
#define valor1 .250						; A palavra 'valor 1' ser� entendida como 250
#define valor2 .125						; A palavra 'valor 1' ser� entendida como 125
#define valor3 .16						; A palavra 'valor 1' ser� entendida como 16

cblock 0x20
 cont1									; Cria um espa�o no endere�o 0x20
 cont2									; Cria um espa�o no endere�o 0x21
 cont3									; Cria um espa�o no endere�o 0x22
endc

ORG 0x0000     							; Programa ser� armazenado a partir da mem�ria 0x00
nop										; Gasta um ciclo de m�quina
nop										; Gasta um ciclo de m�quina
goto inicio								; Vai para 'inicio'
nop										; Gasta um ciclo de m�quina

inicio									; Marca o in�cio do c�digo
	
bcf STATUS, RP1							; RP1 = 0
bsf STATUS, RP0							; RP0 = 1    A jun��o dos bits RP1 e RP0 � 01, acessando o banco 1

banksel TRISC							; Acessa o banco 1 (Banco do TRISC)
movlw 0x10								; Move para W o valor 0x10 em hexadecimal
movwf TRISC								; Determina RC4 como entrada e os demais pinos como sa�da 
bsf TRISC,0								; Zera o bit 0 do registrador TRIS. Definindo como sa�da
clrf TRISA								; Zera o registrador TRISA. Definindo a porta A inteira como sa�da
clrf TRISB								; Zera o registrador TRISB. Definindo a porta B inteira como sa�da
clrf TRISD								; Zera o registrador TRISD. Definindo a porta D inteira como sa�da
clrf TRISE								; Zera o registrador TRISE. Definindo a porta E inteira como sa�da
MOVLW D'255' ;							; Move para W o valor 255 em decimal
MOVWF OPTION_REG						; Determina todos os bits do registrador OPTION_REG em 1.
; Desabilita o pull-up da porta B
; Habilita a interrup��o do RB0 por borda de subida
; Habilita o clock externo, detec��o por borda de subida, prescaler pelo WDT, prescaler 1:128
 
bcf STATUS, RP0							; RP0 = 0	A jun��o dos bits RP1 e RP0 � 00, acessando o banco 0
movlw 0x00								; Move para W o valor zero
movwf PORTD								; Determina todos os pinos da porta D em n�vel baixo
movwf PORTA								; Determina todos os pinos da porta A em n�vel baixo
movwf PORTB								; Determina todos os pinos da porta B em n�vel baixo
movwf PORTC								; Determina todos os pinos da porta C em n�vel baixo
movwf PORTE								; Determina todos os pinos da porta E em n�vel baixo

banksel PORTB							; Acessa o banco 0 (Banco do PORTB)
swapf PORTB,F							; Inverte a ordem dos bits do PORTB, e guarda a nova ordem em f

le_botao								; Rotina le_botao
			btfsC PORTC,0				 
			goto apaga_led				; Retorna para rotina apaga_led 
			
ligar_led 	bsf PORTD,2
 			goto INVERTE				; Retorna para rotina INVERTE
 			
apaga_led 	bcf PORTD,2					; Determina o pino RD2 em nivel baixo

INVERTE		movlw B'00000001'			; Move o valor 0x01 para W
 			xorwf PORTD,F				; 
			call atraso					; Chama uma rotina de atraso
 			goto le_botao				; Retorna para rotina le_botao
 			
;===ROTINA DE ATRASO DE TEMPO=========
atraso 		movlw valor3				; Move .16 para W
 			movwf cont3					; Reseta a contagem
 			
recarga2 	movlw valor2 				; Move .125
 			movwf cont2					; Reseta o valor da contagem
 			
recarga1 	movlw valor1				; Move .250
 			movwf cont1					; Reseta o valor da contagem
 			
dec 		decfsz cont1				; Faz a contagem at� zerar
			goto dec					; Retorna para o in�cio da rotina
			decfsz cont2				; Faz a contagem at� zerar
			goto recarga1				; Reinicia o valor da vari�vel
			decfsz cont3				; Faz a contagem at� zerar
			goto recarga2				; Reinicia o valor da vari�vel
			return						; Sa� da rotina

end ; fim do programa