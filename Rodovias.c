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

int InicializaCidades(lista_cidade *lc) {
    *lc = malloc(sizeof (lista_cidade));
    if(*lc == NULL) {
        printf("Erro de alocacao!\n");
        return 0;
    }
    *lc = NULL;
    return 1;
}


/**
 * Insere uma rodovia na lista encadeada no inicio
 * @param li cabeça da lista
 * @param rod rodovia a inserir
 * @return 0 -> Erro; 1 -> Sucesso
 */
int InsereRodoviaInicio(lista_rodovia *li, rodovia rod) {
    nodeR *novo = malloc(sizeof(nodeR));
    novo->estrada = rod;
    novo->prox = NULL;
    novo->cidades =  NULL;
    if (InicializaCidades(&(novo->cidades)) == 0) return 0;
    if(li == NULL) {
        printf("Lista nao inicializada!\n");
        return 0;
    }
    if(*li == NULL) { //Primeira rodovia da lista
        *li = novo;
        return 1;
    }
    novo->prox = *li;
    *li = novo;
    return 1;
}

/**
 * Insere uma cidade na rodovia especificada pelo codigo
 * @param lista rodovia
 * @param codigoRodovia codigo da rodovia
 * @param cidade cidade a inserir
 * @return 0 = falha 1 = sucesso
 */
int InsereCidadeEmRodovia(lista_rodovia lista, int codigoRodovia, city cidade) {
    if(lista == NULL) {
        printf("Rodovia nao encontrada!\n");
        return 0;
    }
    if(lista->estrada.codigo == codigoRodovia) { //Achada a rodovia para inserir a cidade
        nodeC *novo = malloc(sizeof(nodeC));
        if(novo == NULL) {
            printf("Erro de alocacao!\n");
            return 0;
        }
        novo->cidade = cidade;
        novo->prox = NULL;
        novo->ant = NULL;
        if(lista->cidades == NULL) { //Primeira cidade da rodovia, inserindo na cabeça
            lista->cidades = novo;
            return 1;
        }
        lista->cidades->ant = novo;
        novo->prox = lista->cidades;
        lista->cidades = novo;
        return 1;
    }
    return InsereCidadeEmRodovia(lista->prox, codigoRodovia, cidade);
}



void ImprimeCidades(lista_cidade l) {
    if(l == NULL) return;
    printf("    %s Distancia ate a proxima: %d\n", l->cidade.nome, l->cidade.distanciaProx);
    ImprimeCidades(l->prox);
}

/**
 * Imprime as rodovias e suas respectivas cidades
 * @param l Rodovia a imprimir
 */
void ImprimeRodovias(lista_rodovia l) {
    if(l == NULL) return;
    printf("Codigo: BR-%d. Pedagio: R$%d\n", l->estrada.codigo, l->estrada.pedagio);
    ImprimeCidades(l->cidades);
    ImprimeRodovias(l->prox);
}


