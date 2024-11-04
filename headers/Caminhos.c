#include "Caminhos.h"
#include <stdlib.h>
#include <stdio.h>
#include "Rodovias.h"
#include "cidades.h"
#include <string.h>


int BuscaBinariaRodovia(int codigo, lista_rodovia lr[], int tam) {
    if(lr == NULL || tam == 0 || lr[1] == NULL) return 0;
    //if(tam == 1) return 0;
    auto val = lr[(int)tam/2]->estrada.codigo;
    if(val == codigo) return 1;
    if(val < codigo) return BuscaBinariaRodovia(codigo, lr + tam/2 + 1, tam/2);
    if(val > codigo) return BuscaBinariaRodovia(codigo, lr, tam/2);
}


//
//lista_cidade RotaAux(lista_rodovia rod1, char* cidade1, char* cidade2) { //Cruzamento para cidades na mesma rodovia.
//    lista_cidade c1 = rod1->cidades;
//    while (strcmpi(c1->cidade.nome, cidade1) != 0) c1 = c1->prox;
//    lista_cidade percorrePraFrente = c1, percorrePraTras = c1;
//    lista_cidade praFrente, praTras;
//    InicializaCidades(&praTras);
//    InicializaCidades(&praFrente);
//    while (percorrePraFrente != NULL && percorrePraTras != NULL) { //n
//        //if (percorrePraFrente != NULL) {
//        InsereCidade(&praFrente, percorrePraFrente->cidade);
//        percorrePraFrente = percorrePraFrente->prox;
//        // }
//        //if (percorrePraTras != NULL) {
//        InsereCidade(&praTras, percorrePraTras->cidade);
//        percorrePraTras = percorrePraTras->ant;
//        //}
//        if (percorrePraFrente != NULL && strcmpi(percorrePraFrente->cidade.nome, cidade2) == 0) {
//            InsereCidade(&praFrente, percorrePraFrente->cidade);
//            LiberaListaCidade(&praTras);
//            return praFrente;
//        }
//        if (percorrePraTras != NULL && strcmpi(percorrePraTras->cidade.nome, cidade2) == 0) {
//            InsereCidade(&praTras, percorrePraTras->cidade);
//            LiberaListaCidade(&praFrente);
//            return praTras;
//        }
//    }
//    return NULL;
//}

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

int CodigoMarcado(int cod, nodeR listaMarcados[], int qtd) {
    for(int i = 0; i < qtd; i++) {
        if(listaMarcados[i].estrada.codigo == cod) return 1;
    }
    return 0;
}

nodeR* IndexaRodovias(lista_rodovia cabeca, int count) {
    int i = 0;
    nodeR *aux = cabeca;
    for(; i < count; aux = aux->prox, i++);
    return aux;
}


int bfs(nodeR *rod1, nodeR *rod2, lista_rodovia cabeca, int caminho[]) {
    if (rod1 == NULL || rod2 == NULL) return 0;
    int qtdRods = ContaRodovias(cabeca);
    lista_rodovia listaAdj[qtdRods];
    for (int i = 0; i < qtdRods; i++) {
        //IniciaListaRodoviaVazia(&listaAdj[i]);
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
    //Busca em largua ---------------------------------------------------------------------------------------
    nodeR marcados[MAX]; int numVisitados = 0;
    nodeR *fila[MAX]; int inicio = 0, fim = 0;
    int ach = 0;
    int anteriores[qtdRods];
    for(int i = 0; i < qtdRods; i++) anteriores[i] = -1;
    marcados[numVisitados++] = *IndexaRodovias(cabeca, EncontraIndice(cabeca, rod1->estrada.codigo));
    fila[fim++] = IndexaRodovias(cabeca, EncontraIndice(cabeca, rod1->estrada.codigo));
    while(inicio < fim) {
        nodeR *at = fila[inicio++];
        nodeR *vizinhos = listaAdj[EncontraIndice(cabeca,at->estrada.codigo)];
        while(vizinhos != NULL){
            if(!CodigoMarcado(vizinhos->estrada.codigo, marcados, numVisitados)){
                marcados[numVisitados++] = *vizinhos;
                fila[fim++] = vizinhos;
                anteriores[EncontraIndice(cabeca, vizinhos->estrada.codigo)] = at->estrada.codigo;
                if(vizinhos->estrada.codigo == rod2->estrada.codigo) {
                    inicio = fim + 1;
                    ach = 1;
                    break;
                }
            }
            vizinhos = vizinhos->prox;
        }
    }
    //----------------------------------------------------------------------------------------------------------------
    if(ach == 0) return 0;

    //talvez os caminhos agora
    int c = EncontraIndice(cabeca, rod2->estrada.codigo);
    int qtdCaminho = 0;
    caminho[qtdCaminho++] = rod2->estrada.codigo;
    while (anteriores[c] != -1) {
        caminho[qtdCaminho++] = anteriores[c];
        c = EncontraIndice(cabeca, anteriores[c]);
    }
    for (int i = 0; i < qtdCaminho / 2; i++) {
        int swap = caminho[i];
        caminho[i] = caminho[qtdCaminho - i - 1];
        caminho[qtdCaminho - i - 1] = swap;
    }

    for(int i = 0; i < qtdRods; i++) {
        nodeR *destruidor = listaAdj[i];
        while(destruidor != NULL) {
            nodeR *limpa = destruidor;
            destruidor = destruidor->prox;
            free(limpa);
        }
    }

    return qtdCaminho;
}

lista_cidade EncontraRotaLocal(nodeC *c1, char* destino) {
    lista_cidade percorrePraFrente = c1, percorrePraTras = c1;
    lista_cidade praFrente, praTras;
    InicializaCidades(&praTras);
    InicializaCidades(&praFrente);
    while(1) {
        if(percorrePraFrente == NULL && percorrePraTras == NULL) break; //Isso aqui n eh pra acontecer nunca KKKKKKKK
        if(percorrePraFrente != NULL) {
            InsereCidadeFinal(&praFrente, percorrePraFrente->cidade);
            percorrePraFrente = percorrePraFrente->prox;
        }
        if(percorrePraTras != NULL) {
            InsereCidadeFinal(&praTras, percorrePraTras->cidade);
            percorrePraTras = percorrePraTras->ant;
        }
        if(percorrePraFrente != NULL && strcmpi(percorrePraFrente->cidade.nome, destino) == 0) {
            InsereCidadeFinal(&praFrente, percorrePraFrente->cidade);
            LiberaListaCidade(&praTras);
            return praFrente;
        }
        if(percorrePraTras != NULL && strcmpi(percorrePraTras->cidade.nome, destino) == 0){
            InsereCidadeFinal(&praTras, percorrePraTras->cidade);
            LiberaListaCidade(&praFrente);
            return praTras;
        }
    }
}


void ImprimeRota(lista_cidade rota) {
    if(rota == NULL) return;
    nodeC *carro = rota;
    int lineBreak = 1;
    printf("Caminho desejado:\n"); //Deixar isso mais bonito depois
    while(carro != NULL) {
        if(carro->prox != NULL) printf("%s -> ", carro->cidade.nome);
        else printf("%s\n", carro->cidade.nome);
        carro = carro->prox;
        if(lineBreak % 8 == 0) printf("\n");
        lineBreak++;
    }
}


lista_cidade CaminhoEntreRodovias(int qtd, int rodovias[qtd], char *origem, char *destino, lista_rodovia cabeca) {
    char inicio[100], fim[100];
    if(qtd == 0) return 0;
    lista_cidade cmc = AchaRodoviaCodigo(rodovias[0], cabeca)->cidades, final = AchaRodoviaCodigo(rodovias[qtd-1], cabeca)->cidades;
    while(strcmpi(cmc->cidade.nome, origem) != 0) cmc = cmc->prox;
    while(strcmpi(final->cidade.nome, destino) != 0) final = final->prox;
    int tamanhoRota = 0;
    nodeC *atual = cmc, *roteia = NULL;
    InsereCidadeFinal(&roteia, cmc->cidade);
    for(int i = 0; i < qtd - 1; i++) {
        nodeC *intersecc = AchaCruzamento(rodovias[i], rodovias[i + 1], cabeca);
        lista_cidade rotaTemp = EncontraRotaLocal(atual, intersecc->cidade.nome);
        atual = intersecc;
        for(nodeC *add = rotaTemp->prox; add != NULL; add = add->prox) {
            InsereCidadeFinal(&roteia, add->cidade);
        }
        //ImprimeCidades(rotaTemp);
    }
    lista_cidade rotaF = EncontraRotaLocal(atual, destino)->prox;
    while(rotaF != NULL) {
        InsereCidadeFinal(&roteia, rotaF->cidade);
        rotaF = rotaF->prox;
    }


    return roteia;
    //ImprimeCidades(rotaF);
}





/**
 * Encontra uma rota da cidade1 para cidade2
 * @param origem Cidade inicial
 * @param destino Cidade final
 * @param cabeca Rodovia que se localiza a primeira cidade
 * @param rod2 Rodovia que se localiza a segunda cidade
 * @return rota como uma lista encadeada de cidades (?)
 * @return NULL caso nao exista caminho.
 */
lista_cidade EncontraRota(char *origem, char *destino, lista_rodovia cabeca) {
    nodeR *rodoviasC1[MAX],  *rodoviasC2[MAX];
    int qtdRodoviasC1, qtdRodoviasC2, caminhoRodovia[MAX], desvios;
    lista_cidade c1;
    qtdRodoviasC1 = RodoviasDaCidade(origem, cabeca, rodoviasC1);
    qtdRodoviasC2 = RodoviasDaCidade(destino, cabeca, rodoviasC2);
    if(qtdRodoviasC2 == 0) {
        printf("A Cidade %s nao encontrada!\n", destino);
        return NULL;
    }
    if(qtdRodoviasC1 == 0) {
        printf("A Cidade %s não encontrada!\n", origem);
        return NULL;
    }

    //caso as cidades estejam na mesma rodovia:
    for(int i = 0; i < qtdRodoviasC1; i++) {
        if(BuscaBinariaRodovia(rodoviasC1[i]->estrada.codigo, rodoviasC2, qtdRodoviasC2)) {
            c1 = rodoviasC1[i]->cidades;
            while(strcmpi(c1->cidade.nome, origem) != 0) c1 = c1->prox;
            return EncontraRotaLocal(c1, destino);
        }
    }


    //rodovias separadas:
    for(int i = 0; i < qtdRodoviasC1; i++) {
        int a = 0;
        for(int j = 0; j < qtdRodoviasC2; j++) {
            desvios = bfs(rodoviasC1[i], rodoviasC2[j], cabeca, caminhoRodovia);
            if(desvios) {
                a = 1;
                break;
            }
        }
        if(a == 1) break;
    }

    return CaminhoEntreRodovias(desvios, caminhoRodovia, origem, destino, cabeca);
    //Agora, constroi a rota
}

