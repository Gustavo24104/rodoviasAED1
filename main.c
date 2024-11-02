#include <stdio.h>
#include <stdlib.h>
#include "Rodovias.h"
#include <string.h>
#include <locale.h>


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

    nodeC *cs[100];
    int t = Cruzamento(cabeca, 123, 290, cs);
    printf("%d\n", t);
    for(int i = 0; i < t; i++) {
        printf("%s\n", cs[i]->cidade.nome);
    }

    lista_cidade a = EncontraRota("Uberlândia", "Felixlândia", cabeca);
    //ImprimeCidades(a);


    LiberaListaRodovia(&cabeca);


}
