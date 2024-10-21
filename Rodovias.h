#ifndef RODOVIAS_AED1_RODOVIAS_H

#define RODOVIAS_AED1_RODOVIAS_H

struct Cidade {
    char nome[100];
    int distanciaProx;
};

typedef struct Cidade city;

typedef struct Rodovia {
    int codigo;
    int pedagio; //0 caso nao tenha
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




#endif //RODOVIAS_AED1_RODOVIAS_H
