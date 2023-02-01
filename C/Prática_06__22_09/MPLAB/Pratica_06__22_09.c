/* Prática 06 - 22/09
Grupo:
- Antônio Gustavo da Silva Moura 
- Manoel Barroso da Silva Moura
- Nilo Rodrigues Alves Filho

	=> O botões controle a largura do pulso PWM
		Botão 1 -> Botão de incremento
		Botão 2 -> Botão de decremento
		Botão 3 -> Botão para ler valor na memória
		Botão 4 -> Botão para salvar valor na memória
	
	=> Módulos
		Timer0  ->  Calcula o tempo de 1 seg
		Timer1  ->  Conta as oscilações do ventilador
		Timer2  ->  Utilizado para o módulo CCP2	
		CCP2 -> Gera o pulso PWM para controlar as oscilações do ventilidador	

	=> No display LCD será mostrado: 
	 -> o número de oscilações por segundo de uma palheta do ventilador;
	 -> a porcentagem da largura do pulso PWM;

*/

#include <16f877A.h>

#fuses xt,wdt,noprotect,put,brownout,nolvp,nocpd,nowrt
#use delay(clock=4000000, RESTART_WDT) 

#define t_filtro 200
#define turbo_tecla 5

float duty_cycle = 0;
long int duty_cycle1 = 0;
long int periodo_pulso = 0; // 
long int rotacao = 0; 		// rps do ventilador 
int end = 0; 				// variável para endereçamento da eeprom 
int flags1 = 0; 			// flags 
int filtro = t_filtro; 		// inicia filtro dos botões 
int temp1 = 125; 			// variável aux para int de tmr0 
int turbo = 1; 				// inicia turbo das teclas 
int dado; 					// variável de dados para eeprom 
  
#use fast_io(a) 
#use fast_io(b) 
#use fast_io(c) 
#use fast_io(d) 
#use fast_io(e)
#byte porta=0x05 
#byte portb=0x06 
#byte portc=0x07 
#byte portd=0x08 
#byte porte=0x09 

#bit atualiza_lcd = flags1.0 
#bit botao1 = portb.0 
#bit botao2 = portb.1
#bit botao3 = portb.2
#bit botao4 = portb.3
 
#bit rs = porte.0 			// via do lcd que sinaliza recepção de dados ou comando 
#bit enable = porte.1 		// enable do lcd 
#bit ventilador = portc.1 	// pino de I/O para controle do ventilador (PWM) 

void comando_lcd(int caracter){ 
	rs = 0; 
	portd = caracter;
	enable = 1 ;
	delay_us(1); 
	enable = 0;
	delay_us(40);
}

void escreve_lcd(int caracter){ 
	rs = 1;
	portd = caracter;
	enable = 1;
	delay_us(1);
	enable = 0; 
	delay_us(40);
} 

void limpa_lcd() { 
	comando_lcd(0x01); 
	delay_ms (2); 
} 

void inicializa_lcd(){ 
	comando_lcd(0x30); 	// envia comando para inicializar display 
	delay_ms(4); 		// espera 4 milisengundos 
	comando_lcd(0x30); 	// envia comando para inicializar display 
	delay_us(100); 		// espera 100 microsengundos 
	comando_lcd(0x30); 	// envia comando para inicializar display 
	comando_lcd(0x38); 	// liga o display, sem cursor e sem blink 
	limpa_lcd(); 		// limpa lcd 
	comando_lcd(0x0c); 	// display sem cursor 
	comando_lcd(0x06);	// desloca cursor para a direita 
} 

void tela_principal(){ 
	comando_lcd(0x80);								// posiciona o cursor na linha 0, coluna 0 
	printf (escreve_lcd, "Duty cycle RPS"); 		// imprime mensagem no lcd 
	comando_lcd(0xc3); 								// posiciona o cursor na linha 1, coluna 3 
	printf (escreve_lcd,"%" "3Lu%%", duty_cycle1); 	// envia dados para o display de LCD 
	comando_lcd(0xcb); 								// posiciona o cursor na linha 1, coluna 11 
	printf (escreve_lcd,"%" "3Lu", rotacao); 		// envia dados para o display de LCD 
}

void salva_dados(){ 
	write_eeprom (end,dado); 
} 

void le_dados(end){ 
	dado = read_eeprom (end); 
} 

void atualiza_pwm(){ 
 	set_pwm2_duty(periodo_pulso); // atualiza duty cicle do PWM 
} 
//Manoel
void main(){ 
	setup_adc_ports (no_analogs); 					// desliga as entradas analógicas 
	setup_counters (rtcc_internal, rtcc_div_64);	// tmr0 clock interno, ps: 1:64 
	setup_timer_1 (t1_external_sync | t1_div_by_1);	// tmr1 clock externo, ps: 1:1 
	setup_timer_2 (t2_div_by_16,255,1);				// tmr2 ps=1:16, pr2=255 e postscale: 1:1 
	setup_ccp2(ccp_pwm); 							// modo PWM ligado 
	set_pwm2_duty(periodo_pulso); 					// ajusta duty cycle em 0. 
	
	set_tris_a(0b11111111); 						// configuração da direção dos pinos de I/O 
	set_tris_b(0b11111111); 
	set_tris_c(0b11111101); 
	set_tris_d(0b00000000); 
	set_tris_e(0b00000100); 
	porta=0x00;			// limpa porta 
	portb=0x00; 		// limpa portb 
	portc=0x00; 		// limpa portc 
	portd=0x00; 		// limpa portd 
	porte=0x00; 		// limpa porte 
	
	inicializa_lcd(); 	// configura o lcd 
	tela_principal(); 	// imprime a tela principal no LCD 
	
	enable_interrupts(INT_RTCC); 
	enable_interrupts(GLOBAL); 
//Nilo
loop: 
		while(TRUE){ 
			RESTART_WDT(); // reinicia o watch-dog timer 
			if (atualiza_lcd != 0){ 
				duty_cycle = periodo_pulso; 			// carrega valor da rotação medida 
				duty_cycle = (duty_cycle / 1024); 		// efetua cálculo do duty cycle 
				duty_cycle = (duty_cycle * 100); 		// converte para porcentagem (%) 
				duty_cycle1 = (long int) duty_cycle; 
									// carrega os 16 bits menos significativos da parte inteira 
									// do resultado da converão 
				tela_principal(); 	// imprime a tela principal no LCD 
				atualiza_lcd = 0; 	// indica LCD atualizado 
			} 
			 
			if (!botao1){ 
				goto trata_up;
			} 
			if (!botao2){ 
				goto trata_dowm;
			} 
			if (!botao3){ 
				le_dados(1); 									// lê byte_low da eeprom 
				periodo_pulso = dado; 							// carrega valor lido em variável de 16 bits 
				le_dados(0); 									// lê byte_high da eeprom 
				periodo_pulso = make16(dado, periodo_pulso); 	// recompõe o dado de 16 bits 
				atualiza_pwm(); 								// Função para atualizar o PWM 
				atualiza_lcd = 1; 								// habilita atualização do LCD 
			} 
			if (!botao4){ 
				end = 0; 							// endereço do byte_high 
				dado = make8(periodo_pulso,1); 		// retorna byte_high 
				salva_dados(); 						// salva byte_high 
				end = 1; 							// endereço do byte_low 
				dado = make8(periodo_pulso,0); 		// retorna byte_low 
				salva_dados(); 						// salva byte_low 
			} 
			filtro = t_filtro; 						// carrega filtro dos botões 
			turbo = 1; 
		} 
	trata_up:
	{
		filtro --;  
		if (filtro == 0){
			turbo --;
			filtro = t_filtro; 
			if (turbo == 0){ 
				turbo = turbo_tecla; 
				if (periodo_pulso < 1023){ 
					periodo_pulso ++; 
					atualiza_pwm(); 		
					atualiza_lcd = 1;
				} 
			} 
		}  
	
	}
	goto loop;
	
	trata_dowm:  
	{ 
		filtro --;
		if (filtro == 0){ 
			turbo --;
			filtro = t_filtro; 
			if (turbo == 0){ 
				turbo = turbo_tecla; 
				if (periodo_pulso != 0){ 
					periodo_pulso --; 
					atualiza_pwm(); 
					atualiza_lcd = 1;
				} 
			} 
		} 
		
	}
	goto loop; 
}
//Gustavo
#int_rtcc 
void trata_int_tmr0(void){ 
	set_rtcc(256-125); 
	if (temp1 == 0 ){ 
		rotacao = get_timer1(); 	// le valor do timer 1 
		set_timer1 (0); 			// zera timer 1 
		rotacao = (rotacao / 7);	// divide por 7 (quantidade de palhetas do ventilador) 
		atualiza_lcd = 1; 			// habilita atualização do LCD 
		temp1 = 125; 				// re-inicia temp1 
	} 
	else{ 
		temp1 --; 					// decrementa temp1 
	} 
} 