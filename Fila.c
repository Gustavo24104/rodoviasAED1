#include "Fila.h"
#include "Rodovias.h"
#include "cidades.h"
#include <stdlib.h>

int CriaFila(fila *f) {
    f->tamanho = 0;
    f->inicio = NULL;
    f->fim = NULL;
    return 1;
}

int InsereFila(fila *f, city elem) {
    nodeC *novo = malloc(sizeof(nodeC*));
    if(novo == NULL) return 0;
    novo->cidade = elem;
    novo->ant = NULL;
    novo->prox = NULL;
    if(FilaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
        f->tamanho++;
        return 1;
    }
    f->fim->prox = novo;
    f->fim = novo;
    f->tamanho++;
    return 1;
}


nodeC* RemoveFila(fila *f){
    if(FilaVazia(f)) return NULL;
}

int FilaVazia(fila *f) {
    return ((f->inicio == NULL) || (f->tamanho == 0));
}

