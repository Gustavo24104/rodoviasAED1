

#ifndef RODOVIAS_AED1_CIDADES_H
#define RODOVIAS_AED1_CIDADES_H

struct Cidade {
    char nome[100];
    double distanciaProx;
};

typedef struct Cidade city;

typedef struct noCidade {
    struct noCidade *prox;
    city cidade;
    struct noCidade *ant;
} nodeC; //No para lista de cidades

typedef nodeC *lista_cidade;


int InsereCidade(lista_cidade *lc, city c);
int InicializaCidades(lista_cidade *lc);
void LiberaListaCidade(lista_cidade *lc);

#endif //RODOVIAS_AED1_CIDADES_H
