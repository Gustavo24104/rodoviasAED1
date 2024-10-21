#ifndef RODOVIAS_AED1_RODOVIAS_H

#define RODOVIAS_AED1_RODOVIAS_H

#include <stdio.h>

struct Cidade {
    char nome[100];
    double distanciaProx;
};

typedef struct Cidade city;

typedef struct Rodovia {
    int codigo;
    double pedagio; //0 caso nao tenha
} rodovia;



typedef struct noCidade {
    struct noCidade *prox;
    city cidade;
    struct noCidade *ant;
} nodeC; //No para lista de cidades

typedef nodeC *lista_cidade;

typedef struct noRodoviario {
    rodovia estrada;
    struct noRodoviario *prox;
    lista_cidade cidades;
} nodeR; //No para lista de rodovias

typedef nodeR *lista_rodovia;



int IniciaListaRodoviaVazia(lista_rodovia *li);
int InsereRodoviaInicio(lista_rodovia *li, rodovia rod);
void ImprimeRodovias(lista_rodovia l);
int InsereCidadeEmRodovia(lista_rodovia lista, int codigoRodovia, city cidade);
int CarregaRodovias(lista_rodovia *cabeca, FILE* arq);




#endif //RODOVIAS_AED1_RODOVIAS_H
