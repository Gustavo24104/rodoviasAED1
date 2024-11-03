

#ifndef RODOVIAS_AED1_FILA_H
#include "cidades.h"
#include "Rodovias.h"
#define RODOVIAS_AED1_FILA_H

typedef struct {
    lista_cidade inicio, fim;
    int tamanho;
} fila;


int CriaFila(fila *f);
int InsereFila(fila *f, city elem);
nodeC* RemoveFila(fila *f);
int FilaVazia(fila *f);

#endif //RODOVIAS_AED1_FILA_H
