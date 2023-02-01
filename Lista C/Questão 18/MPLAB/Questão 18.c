/*
Discente: Nilo Rodrigues Alves Filho
Questão 18:
Faça o mesmo da questão 17, desde que a frequência do PWM senoidal possa variar na frequência de um sinal conectado em um dos pinos relacionados ao módulo CCP.

*/


#include <16f877a.h>
#include <regs_pic16f877a.h>
#use delay(clock = 20000000)


double Vetor_X[] = {2.5, 3.456708581, 4.267766953, 4.809698831, 5, 4.809698831, 4.267766953, 3.456708581, 2.5, 1.543291419, 0.732233047, 0.190301169, 0, 0.190301169, 0.732233047, 1.543291419, 2.5};
void main(){
	setup_ccp1(CCP_PWM);
    setup_timer_2(T2_DIV_BY_1, 249, 8);
    setup_ccp2(CCP_CAPTURE_RE);
    set_timer1(T1_INTERNAL||T1_DIV_BY_1);
    set_timer1(0);
    set_timer2(0);
    set_pwm1_duty(512);
    ADCON0 = 0x01;
    ADCON1 = 0x4e;   
    TRISC = 0x00;
    PORTC = 0x00;
    int capt1 = 1, x = 0;
    int16 Tempo_1, Tempo_F;

    while (TRUE){
       set_pwm1_duty(Vetor_X[x]*205);
       x = x+1;
       if(x == 16){
 	    	x = 1;
	   }

       if (ccp2if == 1){
             capt1++;
             if (capt1 == 1){
                Tempo_1 = CCP_2;
                ccp2if = 0;
             }

             if (capt1 == 2){
                Tempo_F = CCP_2 - Tempo_1;
                ccp2if = 0;
                capt1 = 0;
             }
       }
       delay_ms(Tempo_F*0.2);   
    }      
}