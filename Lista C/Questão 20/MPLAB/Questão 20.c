/*
Discente: Nilo Rodrigues Alves Filho
Questão 20:
Faça um programa para configurar a porta serial do microcontrolador com os seguintes parâmetros: 
Baud rate: 9600 bps, 8 bits de dado, sem paridade e 1 stop bit, pino de transmissão RC6 e de recepção o RC7. 
Em seguida, crie uma função que receba dois vetores de inteiros, sendo os inteiros de 8 bits.
O primeiro vetor, V1, tem sempre 2 bytes e o segundo vetor, V2, tem sempre 4 bytes. 
Na função, os dois bytes do vetor V1 são transmitidos pela porta serial e logo em seguida do envio desses bytes, a mesma função preenche o vetor V2 com os 4 primeiros bytes recebidos. 
Após isso, se a primeira posição do vetor 1 for igual a do vetor 2, então a função retorna 1, senão 0. 
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