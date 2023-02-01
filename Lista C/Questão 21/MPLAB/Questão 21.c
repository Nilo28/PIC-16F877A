/*
Discente: Nilo Rodrigues Alves Filho
Questão 21:
Aproveitando o programa anterior e o alterando, faça um programa para enviar e receber dados do 
PIC a partir do terminal serial do computador1
. Da seguinte forma: 
	I. O PIC ao receber a letra 'a' e em seguida a letra 'n', os quatro bytes de V2 serão transmitidos do PIC ao computador.  
	   Como mostrado na aula, utilize também a função printf("%u, ",V2[i]). 
	II. Ao receber a letra 'b' e '0', nessa sequência, o vetor V1 é preenchido com o valor 0x81 e 0xAA 	nesta ordem, ou seja, V1 = {0x81 , 0xAA}. 
	Se receber a letra 'b' e '1', nessa sequência, o vetor 	V1 fica V1 = {0x81 , 0x55}. 
	III. Ao receber a letra 'c' e um caracter qualquer (x), nessa sequência, o vetor V1 é V1 = {0x82, x.

*/

#include <16f877a.h>
#include <regs_pic16f877a.h>

#use delay (clock = 20000000)
#use rs232(baud = 9600, BITS = 8, PARITY = N, STOP = 1, xmit = PIN_C6,rcv = PIN_C7)

void main(){ unsigned int8 Vetor_n1[2], Vetor_n2[4];
	char *X;
   	int i;

   	while (TRUE){
       X = getc();
       if (X[0] == 'a' && X[1] == 'n'){
          for (i = 0; i<=3; i++){
             printf("%u /n", Vetor_n2[i]);
          }
          delay_ms(1000);
       }

       if (X[0] == 'b' && X[1] == '0'){
          Vetor_n1[0] = 0x81;
          Vetor_n1[1] = 0xAA;
          delay_ms(1000);
       }

       if (X[0]== 'b' && X[1] == '1'){
          Vetor_n1[0] = 0x81;
          Vetor_n1[1] = 0x55;
          delay_ms(1000);
       }

       if (X[0]== 'c'){
          Vetor_n1[0] = 0x82;
          Vetor_n1[1] = X[1];
          delay_ms(1000);
       }
    }
}