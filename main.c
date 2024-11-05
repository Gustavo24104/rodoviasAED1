#include <stdio.h>
#include <stdlib.h>
#include "headers/Rodovias.h"
#include <string.h>
#include <locale.h>
#include "headers/Caminhos.h"

#define MAX 150



int main() {
    setlocale(LC_ALL, "pt_br.UTF-8");
    lista_rodovia cabeca; //<- PONTEIRO PRA RODOVIA
    IniciaListaRodoviaVazia(&cabeca);
    FILE *arq;
    arq = fopen("rodovias.txt", "r");
    if( CarregaRodovias(&cabeca, arq) == 1) {
        printf("Algo deu errado!\n");
        exit(-1);
    }
    fclose(arq);

    //ImprimeRodovias(cabeca);

    printf("\n");



    lista_cidade acaba = EncontraRota("Ibiá", "Uberlândia", cabeca);
    if(acaba != NULL) ImprimeRota(acaba);


}



