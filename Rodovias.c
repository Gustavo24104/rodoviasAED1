#include "Rodovias.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int IniciaListaRodoviaVazia(lista_rodovia *li) {
    *li = malloc(sizeof(lista_rodovia));
    if(*li == NULL) {
        printf("Erro de alocacao!\n");
        return 0;
    }
    *li = NULL;
    return 1;
}


int InsereRodoviaInicio(lista_rodovia *li, rodovia rod) {
    nodeR *novo = malloc(sizeof(nodeR));
    novo->estrada = rod;

    if(li == NULL) {
        printf("Lista nao inicializada!\n");
        return 0;
    }
    if(*li == NULL) { //Primeira rodovia da lista

    }
}
