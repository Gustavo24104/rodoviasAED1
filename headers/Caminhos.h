//
// Created by gusta on 03/11/2024.
//

#ifndef RODOVIAS_AED1_CAMINHOS_H
#define RODOVIAS_AED1_CAMINHOS_H
#include "Rodovias.h"
#include "cidades.h"


lista_cidade EncontraRota(char *origem, char *destino, lista_rodovia cabeca, double *preco);

void ImprimeRota(lista_cidade rota, double preco);

#endif //RODOVIAS_AED1_CAMINHOS_H
