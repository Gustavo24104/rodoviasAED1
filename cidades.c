#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include "Rodovias.h"


int InsereCidade(lista_cidade *lc, city c) {
    if(lc == NULL) return 1;

    nodeC *novo = malloc(sizeof(nodeC));
    novo->cidade = c;
    novo->pai = NULL;
    novo->prox = NULL;
    novo->ant = NULL;
    if(*lc == NULL) {
        *lc = novo;
        return 0;
    }
    (*lc)->ant = novo;
    novo->prox = *lc;
    (*lc) = novo;
    return 0;
}


void ImprimeCidades(lista_cidade l) {
    if(l == NULL) return;
    if(l->prox == NULL) {
        printf("    %s\n", l->cidade.nome);
        return;
    }
    //lista_rodovia pai = (lista_rodovia)l->pai;
    printf("    %s | Distancia ate a proxima: %.2fkm.\n", l->cidade.nome, l->cidade.distanciaProx);
    ImprimeCidades(l->prox);
}


int InicializaCidades(lista_cidade *lc) {
    *lc = malloc(sizeof (lista_cidade));
    if(*lc == NULL) {
        printf("Erro de alocacao!\n");
        return 1;
    }
    *lc = NULL;
    return 0;
}

void LiberaListaCidade(lista_cidade *lc) {
    if(lc == NULL) return;
    if(*lc == NULL) return;
    nodeC *aux = *lc, *freeAux;
    while(aux != NULL) {
        freeAux = aux;
        aux = aux->prox;
        free(freeAux);
    }
    *lc = NULL;
    //lc = NULL;
    free(*lc);
}


int RemoveCidade(lista_cidade lc, char* nomeCidade) {
    //TODO
}




