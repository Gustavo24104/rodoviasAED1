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
    printf("    %s | Distancia ate a proxima: %.2fkm\n", l->cidade.nome, l->cidade.distanciaProx);
    ImprimeCidades(l->prox);
}

/**
 * Imprime as rodovias e suas respectivas cidades
 * @param l Rodovia a imprimir
 */
void ImprimeRodovias(lista_rodovia l) {
    if(l == NULL) return;
    printf("Codigo: BR-%03d. Pedagio: R$%03.2f\n", l->estrada.codigo, l->estrada.pedagio);
    ImprimeCidades(l->cidades);
    ImprimeRodovias(l->prox);
}

/**
 * Lê as rodovias e respectivas cidades por meio de um arquivo, adicionando-os
 * No arquivo, um inicio de rodovia é indicado por um número (codigo da rodovia, seguido pelo preço do pedagio)
 * Cada linha seguinte é constituida de uma string de caracteres e um numero de ponto flutuante (Nome da cidade
 * e distancia ate a proxima)
 * Os preços sao separados por '-'
 * @param cabeca cabeça da lista de rodovias
 * @param arq arquivo que será feita a leitura
 * @return 1 = Sucesso, 0 = Erro
 */

int CarregaRodovias(lista_rodovia *cabeca, FILE* arq) {
    if(cabeca == NULL) {
        printf("Lista nao incializada!\n");
        return 0;
    }
    if(arq == NULL) {
        printf("Erro no arquivo!");
        return 0;
    }
    char buffer[200];
    int cod = 0;
    double ped = 0;
    while(fgets(buffer, sizeof(buffer), arq)) { //Vai ate o EOF
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0'; //Remove o '\n' ao final da string
        }
        char *tok, *tok2;
        double n1, n2;
        tok = strtok(buffer,"-"); //Separa as linhas
        tok2 = strtok(NULL, "-");
        if(tok == NULL || tok2 == NULL) continue;
        n1 = strtod(tok, NULL); //Converte o valor para numero, retorna 0 se nao consegue
        n2 = strtod(tok2, NULL);
        if (n1 != 0) {
            rodovia rod;
            rod.codigo = (int)n1;
            rod.pedagio = n2;
            InsereRodoviaInicio(cabeca, rod);
            cod = (int)n1; //Se nao for 0, entao o que ele econtrou foi um codigo de rodovia.
            ped = n2;
            continue;
        }
        city c;
        strcpy(c.nome, tok);
        c.distanciaProx = n2;
        if (InsereCidadeEmRodovia(*cabeca, cod, c) == 0) return 0;
    }
    return 1;
}


