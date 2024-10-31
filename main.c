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
    if( CarregaRodovias(&cabeca, arq) == 0) {
        printf("Algo deu errado!\n");
        exit(-1);
    }
    ImprimeRodovias(cabeca);
//    int a[100];
//    int tam = AchaCidade("Uberlândia", cabeca, a);
//    for(int i = 0; i < tam; i++) {
//        printf("%03d\n", a[i]);
//    }


    fclose(arq);
}
