#ifndef RODOVIAS_AED1_RODOVIAS_H

#define RODOVIAS_AED1_RODOVIAS_H

#include "cidades.h"

#define MAX 150
typedef struct Rodovia {
    int codigo;
    double pedagio; //0 caso nao tenha
    double tamanho;
    double velMedia;
} rodovia;

typedef struct noRodoviario {
    rodovia estrada;
    struct noRodoviario *prox;
    lista_cidade cidades;
} nodeR; //No para lista de rodovias

typedef nodeR *lista_rodovia;

int IniciaListaRodoviaVazia(lista_rodovia *li);
int CarregaRodovias(lista_rodovia *cabeca, void* arq);
lista_rodovia AchaCidadePorNome(char* cid, lista_rodovia lr);
void ImprimeRodovias(lista_rodovia l);
lista_cidade EncontraRota(char *origem, char *destino, lista_rodovia cabeca);
void ImprimeCidades(lista_cidade l);
void LiberaListaRodovia(lista_rodovia *lr);
int RodoviasDaCidade(char* cidade, lista_rodovia lr, nodeR *codes[]);
int InsereRodoviaInicio(lista_rodovia *li, rodovia rod);
int InsereRodoviaFinal(lista_rodovia *lr, rodovia rod);
int ContaRodovias(lista_rodovia c);
int CriaListaAdjacencia(lista_rodovia lr, nodeR *adj[150], lista_rodovia cabeca);
nodeC * AchaCruzamento(int cod1, int cod2, lista_rodovia cabeca);
int CruzamentoPorPonteiro(lista_rodovia l1, lista_rodovia l2, nodeC *codesR1[], nodeC *codesR2[]);






#endif //RODOVIAS_AED1_RODOVIAS_H
