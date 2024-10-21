#include <stdio.h>
#include <stdlib.h>
#include "Rodovias.h"
#include "string.h"

int main() {
    lista_rodovia cabeca; //<- PONTEIRO PRA RODOVIA
    IniciaListaRodoviaVazia(&cabeca);
    rodovia teste;
    teste.codigo = 123;
    teste.pedagio = 2400;
    rodovia teste2;
    teste2.codigo = 69;
    teste2.pedagio = 420;
    city itumbiara;
    strcpy(itumbiara.nome, "Itumbiara");
    itumbiara.distanciaProx = 1000;
    city uberlandia = { "Uberlandia", 240};
    InsereRodoviaInicio(&cabeca, teste);
    InsereRodoviaInicio(&cabeca, teste2);
    InsereCidadeEmRodovia(cabeca, 69, uberlandia);
    InsereCidadeEmRodovia(cabeca, 69, itumbiara);
    ImprimeRodovias(cabeca);






}
