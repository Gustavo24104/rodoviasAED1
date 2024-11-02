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

//     = EncontraRota("Uberlândia", "Barretos", cabeca);
    lista_cidade aa = EncontraRota("California", "Uberlândia",
                 AchaRodoviaPorNome("California", cabeca), AchaRodoviaPorNome("Uberlândia", cabeca));
    ImprimeCidades(aa);
    LiberaListaRodovia(&cabeca);
}



