#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

int InsereCidadeFinal(lista_cidade *lc, city c) {
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
    nodeC *perc = *lc;
    while(perc->prox != NULL) perc = perc->prox;


    perc->prox = novo;
    novo->ant = perc;

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


/**
 * Remove cidade da rodovia de codigo _codigo_
 * @param cabeca cabeça da lista completa de rodovias
 * @param codigo codigo da rodovia que contém a cidade
 * @param nomeCidade nome da cidade a ser removida
 * @return 0 sucesso, 2: rodovia nao encontrada, 1: cidade nao encontrada na rodovia
 */
int RemoveCidade(lista_rodovia cabeca, int codigo, char *nomeCidade) {
    //Encontra cidade
    nodeR *percorre = cabeca;
    while(percorre != NULL && percorre->estrada.codigo != codigo) percorre = percorre->prox;
    if(percorre == NULL) return 2;
    nodeC *cidadeARemover = percorre->cidades;
    while(cidadeARemover != NULL &&
    strcasecmp(cidadeARemover->cidade.nome, nomeCidade) != 0) cidadeARemover = cidadeARemover->prox;
    if(cidadeARemover == NULL) return 1;

    //Remove cidade encontrada
    if(cidadeARemover->ant == NULL) { //primeira da rodovia
        percorre->cidades = cidadeARemover->prox;
        free(cidadeARemover);
        return 0;
    }

    if(cidadeARemover->prox == NULL) {
        cidadeARemover->ant->prox = NULL;
        free(cidadeARemover);
        return 0;
    }

    cidadeARemover->ant->prox = cidadeARemover->prox;
    cidadeARemover->prox->ant = cidadeARemover->ant;
    free(cidadeARemover);
    return 0;

}




