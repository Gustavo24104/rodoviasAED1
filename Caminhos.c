#include "Caminhos.h"
#include <stdlib.h>
#include <stdio.h>
#include "Rodovias.h"
#include "cidades.h"
#include <string.h>


int BuscaBinariaRodovia(int codigo, lista_rodovia lr[], int tam) {
    if(lr == NULL || tam == 0) return 0;

    auto val = lr[(int)tam/2]->estrada.codigo;
    if(val == codigo) return 1;
    if(tam == 1) return 0;
    if(val < codigo) return BuscaBinariaRodovia(codigo, lr + tam/2 + 1, tam/2);
    if(val > codigo) return BuscaBinariaRodovia(codigo, lr, tam/2);
}


lista_cidade RotaAux(lista_rodovia rod1, char* cidade1, char* cidade2) { //Cruzamento para cidades na mesma rodovia.
    lista_cidade c1 = rod1->cidades;
    while (strcmpi(c1->cidade.nome, cidade1) != 0) c1 = c1->prox;
    lista_cidade percorrePraFrente = c1, percorrePraTras = c1;
    lista_cidade praFrente, praTras;
    InicializaCidades(&praTras);
    InicializaCidades(&praFrente);
    while (percorrePraFrente != NULL && percorrePraTras != NULL) { //n
        //if (percorrePraFrente != NULL) {
        InsereCidade(&praFrente, percorrePraFrente->cidade);
        percorrePraFrente = percorrePraFrente->prox;
        // }
        //if (percorrePraTras != NULL) {
        InsereCidade(&praTras, percorrePraTras->cidade);
        percorrePraTras = percorrePraTras->ant;
        //}
        if (percorrePraFrente != NULL && strcmpi(percorrePraFrente->cidade.nome, cidade2) == 0) {
            InsereCidade(&praFrente, percorrePraFrente->cidade);
            LiberaListaCidade(&praTras);
            return praFrente;
        }
        if (percorrePraTras != NULL && strcmpi(percorrePraTras->cidade.nome, cidade2) == 0) {
            InsereCidade(&praTras, percorrePraTras->cidade);
            LiberaListaCidade(&praFrente);
            return praTras;
        }
    }
    return NULL;
}

//int Busca(char *destino, lista_rodovia r) {
//    lista_cidade aux = r->cidades;
//    while(aux != NULL) {
//        if(strcmpi(aux->cidade.nome, destino) == 0) return 1;
//        aux = aux->prox;
//    }
//    return 0;
//}


int EncontraIndice(lista_rodovia cabeca, int cod){
    int i = 0;
    for(nodeR *aux = cabeca; aux->estrada.codigo != cod; aux = aux->prox, i++);
    return i;
}

int CodigoMarcado(int cod, nodeR *listaMarcados[], int qtd) {
    for(int i = 0; i < qtd; i++) {
        if(listaMarcados[i]->estrada.codigo == cod) return 1;
    }
    return 0;
}

nodeR* IndexaRodovias(lista_rodovia cabeca, int count) {
    int i = 0;
    nodeR *aux = cabeca;
    for(; i < count; aux = aux->prox, i++);
    return aux;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"
int RoteiaRodovias(nodeR *rod1, nodeR *rod2, lista_rodovia cabeca, nodeR *caminho[]) {
    if (rod1 == NULL || rod2 == NULL) return -1;
    int qtdRods = ContaRodovias(cabeca);
    lista_rodovia listaAdj[qtdRods];
    for (int i = 0; i < qtdRods; i++) {
        IniciaListaRodoviaVazia(&listaAdj[i]);
        listaAdj[i] = NULL;
    }

    nodeR *aux = cabeca;
    for(int i = 0; i < qtdRods; i++, aux = aux->prox) {
        nodeR *listaAux[MAX];
        int v = CriaListaAdjacencia(aux, listaAux, cabeca);
        for(int j = 0; j < v; j++){
            InsereRodoviaFinal(&listaAdj[i], listaAux[j]->estrada);
        }
    }


//    for(int i = 0; i < qtdRods; i++){
//        nodeR *r = listaAdj[i];
//        printf("%d: ", IndexaRodovias(cabeca, i)->estrada.codigo);
//        for(; r != NULL; r = r->prox) printf("%d -> ", r->estrada.codigo);
//        printf("\n");
//    }

    nodeR *marcados[MAX]; int numVisitados = 0;
    nodeR *fila[MAX]; int inicio = 0, fim = 0;

    marcados[numVisitados++] = IndexaRodovias(cabeca, EncontraIndice(cabeca, rod1->estrada.codigo));
    fila[fim++] = IndexaRodovias(cabeca, EncontraIndice(cabeca, rod1->estrada.codigo));

    while(inicio < fim) {
        nodeR *at = fila[inicio++];
        printf("Percorrido: %d\n", at->estrada.codigo);
        nodeR *vizinhos = listaAdj[EncontraIndice(cabeca,at->estrada.codigo)];
        while(vizinhos != NULL){
            if(!CodigoMarcado(vizinhos->estrada.codigo, marcados, numVisitados)){
                marcados[numVisitados++] = vizinhos;
                fila[fim++] = vizinhos;
            }
            vizinhos = vizinhos->prox;
        }
    }

    printf("fim da função.\n");


    for(int i = 0; i < qtdRods; i++) {
        LiberaListaRodovia(&listaAdj[i]);
    }
    free(*listaAdj);
}
#pragma clang diagnostic pop


/**
 * Encontra uma rota da cidade1 para cidade2
 * @param origem Cidade inicial
 * @param destino Cidade final
 * @param lr Rodovia que se localiza a primeira cidade
 * @param rod2 Rodovia que se localiza a segunda cidade
 * @return rota como uma lista encadeada de cidades (?)
 * @return NULL caso nao exista caminho.
 */
lista_cidade EncontraRota(char *origem, char *destino, lista_rodovia lr) {
    /* TODO: Ideia ate agora:
     * Primeiro passo: Verifica se não tao na mesma rodovia (se tiverem o caminho é trivial)
     * Caso contrário, usa a função RodoviasDaCidades pra ter uma visão geral de quais rodovias olhar e verifica uma a uma
     * Algo desse nível
     */
    nodeR *rodoviasC1[MAX],  *rodoviasC2[MAX], *caminho[MAX];
    int qtdRodoviasC1, qtdRodoviasC2;
    lista_cidade c1;
    qtdRodoviasC1 = RodoviasDaCidade(origem, lr, rodoviasC1);
    qtdRodoviasC2 = RodoviasDaCidade(destino, lr, rodoviasC2);
    //caso as cidades estejam na mesma rodovia:
    for(int i = 0; i < qtdRodoviasC1; i++) { //TRIVIAL!!!!!!!!!!!!!!
        if(BuscaBinariaRodovia(rodoviasC1[i]->estrada.codigo, rodoviasC2, qtdRodoviasC2)) {
            //estao na mesma rodovia!
            c1 = rodoviasC1[i]->cidades;
            while(strcmpi(c1->cidade.nome, origem) != 0) c1 = c1->prox;
            lista_cidade percorrePraFrente = c1, percorrePraTras = c1;
            lista_cidade praFrente, praTras;
            InicializaCidades(&praTras);
            InicializaCidades(&praFrente);
            while(1) {
                if(percorrePraFrente == NULL && percorrePraTras == NULL) break; //Isso aqui n eh pra acontecer nunca KKKKKKKK
                if(percorrePraFrente != NULL) {
                    InsereCidade(&praFrente, percorrePraFrente->cidade);
                    percorrePraFrente = percorrePraFrente->prox;
                }
                if(percorrePraTras != NULL) {
                    InsereCidade(&praTras, percorrePraTras->cidade);
                    percorrePraTras = percorrePraTras->ant;
                }
                if(percorrePraFrente != NULL && strcmpi(percorrePraFrente->cidade.nome, destino) == 0) {
                    InsereCidade(&praFrente, percorrePraFrente->cidade);
                    LiberaListaCidade(&praTras);
                    return praFrente;
                }
                if(percorrePraTras != NULL && strcmpi(percorrePraTras->cidade.nome, destino) == 0){
                    InsereCidade(&praTras, percorrePraTras->cidade);
                    LiberaListaCidade(&praFrente);
                    return praTras;
                }
            }
        }
    }



    c1 = AchaCidadePorNome(origem, lr)->cidades;
    while(strcmpi(c1->cidade.nome, origem) != 0) c1 = c1->prox;
    RoteiaRodovias(c1->pai, rodoviasC2[0], lr, caminho);
    //printf("%d\n", c1->pai->estrada.codigo);
//    for(int i = 0; i < qtdRodoviasC2; i++){
//        //printf("%d\n", rodoviasC2[i]->estrada.codigo);
//        //RoteiaRodovias(rodoviasC2[i], c1->pai);
//        RoteiaRodovias(c1->pai, rodoviasC2[i], lr);
//        //CruzamentoPorPonteiro(rodoviasC2[i], c1->pai->estrada, );
//    }



//    nodeR *rodoviasC1[100],  *rodoviasC2[100];
//    int qtdRodoviasC1, qtdRodoviasC2;
//    qtdRodoviasC1 = RodoviasDaCidade(cidade1, rod1, rodoviasC1);
//    qtdRodoviasC2 = RodoviasDaCidade(cidade2, rod1, rodoviasC2);
//    if(qtdRodoviasC1 == 0 || qtdRodoviasC2 == 0) {
//        return NULL;
//    }
//    lista_cidade c1 = rodoviasC1[0]->cidades;
//    //caso as cidades estejam na mesma rodovia: vai andando pra frente e pra tras ate achar o caminho
//    for(int i = 0; i < qtdRodoviasC1; i++) {
//        if(BuscaBinariaRodovia(rodoviasC1[i]->estrada.codigo, rodoviasC2, qtdRodoviasC2)) { //logn
//            return RotaAux(cidade1, cidade2, rodoviasC1[i]);
//        }
//    }






    //caso contrário:
    //Eh meio q uma busca em largura se ela fosse MUITO ruim
//    for(int i = 0; i < qtdRodoviasC1; i++) {
//        for(int j = 0; j < qtdRodoviasC2; j++) {
//            nodeC *cs1[100], *cs2[100];
//            int a = CruzamentoPorPonteiro(rodoviasC1[i], rodoviasC2[j], cs1, cs2);
//
//        }
//        //int qnt = RodoviasDaCidade(c1->prox->cidade.nome, lr, aux);
//    }

    //return
    //return EncontraRota(c1->prox->cidade.nome, cidade2, lr); //so preciso dar um jeito de encadear isso com o resto
    //mais proximo q cheguei foi com essa recursao meia boca

    return NULL;
}

