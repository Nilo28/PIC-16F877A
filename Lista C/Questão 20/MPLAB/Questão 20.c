/*
Discente: Nilo Rodrigues Alves Filho
Quest�o 20:
Fa�a um programa para configurar a porta serial do microcontrolador com os seguintes par�metros: 
Baud rate: 9600 bps, 8 bits de dado, sem paridade e 1 stop bit, pino de transmiss�o RC6 e de recep��o o RC7. 
Em seguida, crie uma fun��o que receba dois vetores de inteiros, sendo os inteiros de 8 bits.
O primeiro vetor, V1, tem sempre 2 bytes e o segundo vetor, V2, tem sempre 4 bytes. 
Na fun��o, os dois bytes do vetor V1 s�o transmitidos pela porta serial e logo em seguida do envio desses bytes, a mesma fun��o preenche o vetor V2 com os 4 primeiros bytes recebidos. 
Ap�s isso, se a primeira posi��o do vetor 1 for igual a do vetor 2, ent�o a fun��o retorna 1, sen�o 0. 
Dica: Utilize ponteiro para apontar para cada vetor, ou vejam https://www.youtube.com/watch?v=SAhR1h3LpDY

*/

#include <16f877a.h>
#include <regs_pic16f877a.h>

#use delay (clock = 20000000)
#use rs232(baud = 9600, BITS = 8, PARITY = N, STOP = 1, xmit = PIN_C6,rcv = PIN_C7)

int Recb_Vet(unsigned int8 *Vetor_n1, int8 *Vetor_n2){
   
	int i, j, Valor;
    for (i=0; i<=1; i++){
       printf("%u /n", Vetor_n1[i]);
    }

    for (j = 0; j<=3;j++){
       Vetor_n2[j] = getc(); 
    }

    if (Vetor_n1[0] == Vetor_n2 [0]){
     	Valor = 1;
    }

    else{
     	Valor = 0;
    }
   
    return Valor;
}

void main(){

	while (TRUE){
    }
}