/*
Discente: Nilo Rodrigues Alves Filho
Questão 9:
Utilizando a interrupção do TIMER1, faça um programa para implementar um relógio com segundos (variável segundos), minutos (variável minutos) e horas (variável horas que deve estar entre 0 a 23). 
Utilize um cristal de quartzo de 32768 Hz para conectar entre os pinos RC0 e RC1 para ser a fonte de clock para o TIMER1 e facilitar a temporização precisa de 1 segundo. 
*/
#use delay(clock=20000000) 
#include <16f877a.h>   

//#use delay(clock=20000000) 
#include "lcd.c"

//#use delay(clock=20000000) 
#fuses hs,put,wdt,noprotect,nobrownout,NOLVP,NOCPD,NOWRT 
#int_timer1

int segundos, minutos, horas;
  
void timer1(void){
	static int cont;
	set_timer1(3036 + get_timer1());
	cont++;
	if (cont == 10) { 
		segundos++;
		cont = 0;
	}
}

void main(){

	enable_interrupts(global); 
	enable_interrupts(int_timer1);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
	lcd_init();
	
	while(TRUE){ 
		delay_ms(100); 
		if (segundos==60){ 
			segundos=0;
			minutos++;
		}
		if (minutos==60){
			minutos=0;
			horas++;
		}
		if (horas == 24){
			horas = 0;
		}
		printf(lcd_putc,"\fHorario: %u:%u:%u",horas,minutos,segundos); 
	}
}