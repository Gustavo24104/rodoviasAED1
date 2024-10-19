#ifndef RODOVIAS_AED1_RODOVIAS_H

/* Sugestão de structs:
Rodovia:
 Cidades conectadas
 Pedagios
 Tamanho
 Nome

Cidade:
 Proxima cidade
 Cidade anterior
 População
 Distancia ate proxima

No mais, por enquanto pensei na cidade serem elementos e as rodovias as listas, a rodovia começa e termina em cidades
 especificas (no descritor), e cada rodovia eh uma lista encadeada com cada cidade

 */
#define RODOVIAS_AED1_RODOVIAS_H

struct Cidade {
    char nome[100];
    int distanciaProx;
    struct Cidade *prox;
    struct Cidade *ant;
};

typedef struct Cidade city;

typedef struct Rodovia {
    int codigo;
    int Pedagio; //0 caso nao tenha
} rodovia;

typedef struct noRodoviario {
    rodovia estrada;
    struct noRodoviario *prox;
} nodeR; //No para lista de rodovias

typedef struct noCidade {
    struct noCidade *prox;
    city cidade;
    struct noCidade *ant;
} nodeC; //No para lista de cidades

typedef nodeR *lista_rodovia;
typedef nodeC *lista_cidade;

int IniciaListaRodoviaVazia(lista_rodovia *li);



#endif //RODOVIAS_AED1_RODOVIAS_H
