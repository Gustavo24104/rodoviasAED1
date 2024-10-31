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
    double tamanho;
    double velMedia;
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
int CarregaRodovias(lista_rodovia *cabeca, FILE* arq);
char* Cruzamento(lista_rodovia lr,int codigo1, int codigo2); //Força bruta
void ImprimeRodovias(lista_rodovia l);
lista_cidade EncontraRota(char* cidade1, char* cidade2, lista_rodovia lr);



#endif //RODOVIAS_AED1_RODOVIAS_H
