#include <stdio.h>
#include <stdlib.h>
#include "Rodovias.h"
#include "string.h"

int main() {
    lista_rodovia cabeca; //<- PONTEIRO PRA RODOVIA
    IniciaListaRodoviaVazia(&cabeca);
    FILE *arq;
    arq = fopen("rodovias.txt", "r");
    if( CarregaRodovias(&cabeca, arq) == 0) {
        printf("Algo deu errado!\n");
        exit(-1);
    }
    ImprimeRodovias(cabeca);
    fclose(arq);
}
