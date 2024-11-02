#include <stdio.h>
#include <stdlib.h>
#include "Rodovias.h"
#include <string.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "pt_br.UTF-8");
    lista_rodovia cabeca; //<- PONTEIRO PRA RODOVIA
    IniciaListaRodoviaVazia(&cabeca);
    FILE *arq;
    arq = fopen("rodovias.txt", "r");
    if( CarregaRodovias(&cabeca, arq) == 1) {
        printf("Algo deu errado!\n");
        exit(-1);
    }
    fclose(arq);

    //ImprimeRodovias(cabeca);

    nodeR *ub = AchaRodoviaPorNome("Uberlândia", cabeca);
    nodeR *ba = AchaRodoviaPorNome("MPGP house", cabeca);

//     = EncontraRota("Uberlândia", "Barretos", cabeca);
    lista_cidade aa = EncontraRota("Uberlândia", "California", cabeca);

    lista_cidade teste[100], t2[100];
    int qtd = CruzamentoPorPonteiro(ub, ba, teste, t2);
    ImprimeCidades(aa);
    LiberaListaRodovia(&cabeca);
}



