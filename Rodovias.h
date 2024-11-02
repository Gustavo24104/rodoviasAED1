#ifndef RODOVIAS_AED1_RODOVIAS_H

#define RODOVIAS_AED1_RODOVIAS_H

#include "cidades.h"

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
int Cruzamento(lista_rodovia lr,int codigo1, int codigo2, nodeC *codesR1[], nodeC *codesR2[]); //Força bruta
void ImprimeRodovias(lista_rodovia l);
lista_cidade EncontraRota(char *cidade1, char *cidade2, lista_rodovia rod1, lista_rodovia rod2);
void ImprimeCidades(lista_cidade l);
void LiberaListaRodovia(lista_rodovia *lr);
int RodoviasDaCidade(char* cidade, lista_rodovia lr, nodeR *codes[]);
int CruzamentoPorPonteiro(lista_rodovia l1, lista_rodovia l2, nodeC *codesR1[], nodeC *codesR2[]);
lista_rodovia AchaRodoviaCodigo(int cod, lista_rodovia lr);
lista_rodovia AchaRodoviaPorNome(char* cid, lista_rodovia lr);




#endif //RODOVIAS_AED1_RODOVIAS_H
