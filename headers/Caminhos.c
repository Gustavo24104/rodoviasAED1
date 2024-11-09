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
    return 0; //
}

//Encontra a posição da rodovia de código _cod_ na lista (ou seja, ja foi visitado)
int EncontraIndice(lista_rodovia cabeca, int cod){
    int i = 0;
    for(nodeR *aux = cabeca; aux->estrada.codigo != cod; aux = aux->prox, i++);
    return i;
}

//Verifica se o codigo da rodovia ja esta na lista
int CodigoMarcado(int cod, nodeR listaMarcados[], int qtd) {
    for(int i = 0; i < qtd; i++) {
        if(listaMarcados[i].estrada.codigo == cod) return 1;
    }
    return 0;
}
//Retorna a rodovia de N° _count_  na lista
nodeR* IndexaRodovias(lista_rodovia cabeca, int count) {
    int i = 0;
    nodeR *aux = cabeca;
    for(; i < count; aux = aux->prox, i++);
    return aux;
}

//Realiza uma busca em largura nas rodovias
int bfs(nodeR *rod1, nodeR *rod2, lista_rodovia cabeca, int caminho[]) {
    if (rod1 == NULL || rod2 == NULL) return 0;
    int qtdRods = ContaRodovias(cabeca);
    //Usaremos um vetor de lista de adjacencias para representar o grafo
    lista_rodovia listaAdj[qtdRods];
    for (int i = 0; i < qtdRods; i++) {
        listaAdj[i] = NULL;
    }

    nodeR *aux = cabeca;
    for(int i = 0; i < qtdRods; i++, aux = aux->prox) {
        nodeR *listaAux[MAX];
        int v = CriaListaAdjacencia(aux, listaAux, cabeca);
        for(int j = 0; j < v; j++){ //Insere as adjacencias, criando a verdadeira lista encadeada
            InsereRodoviaFinal(&listaAdj[i], listaAux[j]->estrada);
        }
    }
    //Busca em largura ---------------------------------------------------------------------------------------
    /*As rodovias sao representadas por um vetor de lista de ajdacencia e "indexadas" pois estão em ordem, então:
     * 010 = indice 0
     * 050 = indice 1
     * 123 = indice 2
     * etc...
     * Dessa forma, podemos achar a lista que corresponde ao vetor percorrendo a lista e procurando a de código adequado
     */

    //marcados é o vetor que armazena as rodovias ja visitadas, numVisitados a qtidade
    nodeR marcados[MAX]; int numVisitados = 0;
    //Usaremos uma fila simples para saber quais rodovias devemos visitar em qual ordem
    nodeR *fila[MAX]; int inicio = 0, fim = 0;
    //Usado para verificar se um caminho foi encontrado
    int ach = 0;
    //Armazena os códigos dos "pais" das rodovias encontradas, usado para encontrar o caminho depois
    //funciona similar ao vetor de adjacencia, onde cada indice representa a posição da rodovia na lista
    int anteriores[qtdRods];
    for(int i = 0; i < qtdRods; i++) anteriores[i] = -1; //-1 para representar que não foi visitado.
    marcados[numVisitados++] = *IndexaRodovias(cabeca, EncontraIndice(cabeca, rod1->estrada.codigo)); //Marca a primeira rodovia
    fila[fim++] = IndexaRodovias(cabeca, EncontraIndice(cabeca, rod1->estrada.codigo)); //Insere a primeira rodovia na fila
    while(inicio < fim) { //Enquanto a fila estiver vazia
        nodeR *at = fila[inicio++]; //Visita o nó no inicio da fila
        //Usamos a lista de adjacencia para encontrar os vizinhos da rodovia e percorre-lá
        nodeR *vizinhos = listaAdj[EncontraIndice(cabeca,at->estrada.codigo)];
        while(vizinhos != NULL){ //percorre os vizinhos
            if(!CodigoMarcado(vizinhos->estrada.codigo, marcados, numVisitados)){
                //Marca que visitou o vizinho e coloca ele na fila
                marcados[numVisitados++] = *vizinhos;
                fila[fim++] = vizinhos;
                //Armazena o "pai" do nó visitado para percorrer o caminho depois
                anteriores[EncontraIndice(cabeca, vizinhos->estrada.codigo)] = at->estrada.codigo;
                if(vizinhos->estrada.codigo == rod2->estrada.codigo) { //Se ele encontrar a rota
                    inicio = fim + 1; //Usado para parar o laço de cima
                    ach = 1;
                    break; //para de procurar
                }
            }
            vizinhos = vizinhos->prox; //passa pro proximo vizinho na lista
        }
    }
    //----------------------------------------------------------------------------------------------------------------
    if(ach == 0) return 0;

    //anda pra trás por meio dos anteriores de cada nó para encontrar o caminho certo
    int c = EncontraIndice(cabeca, rod2->estrada.codigo);
    int qtdCaminho = 0;
    caminho[qtdCaminho++] = rod2->estrada.codigo;
    while (anteriores[c] != -1) {
        caminho[qtdCaminho++] = anteriores[c];
        c = EncontraIndice(cabeca, anteriores[c]);
    }

    //inverto o caminho, pois encontramos o caminho "de tras pra frente"
    for (int i = 0; i < qtdCaminho / 2; i++) {
        int swap = caminho[i];
        caminho[i] = caminho[qtdCaminho - i - 1];
        caminho[qtdCaminho - i - 1] = swap;
    }

    //libera a memória alocada na função
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

//usado para encontrar a rota entre duas cidades na mesma rodovia
lista_cidade EncontraRotaLocal(nodeC *c1, char* destino) {
    //printf("%s", destino);
    if(c1 == NULL) return NULL;
    lista_cidade percorrePraFrente = c1, percorrePraTras = c1;
    lista_cidade praFrente, praTras;
    InicializaCidades(&praTras);
    InicializaCidades(&praFrente);
    //tem um funcionamento simples, procura pra tras e pra frente ate achar uma cidade com o nome requisitado
    //Armazenando o caminho em variaveis diferentes para depois retornar o apropriado
    while(1) {
        if(percorrePraFrente == NULL && percorrePraTras == NULL) break;
        if(percorrePraFrente != NULL) {
            InsereCidadeFinal(&praFrente, percorrePraFrente->cidade, c1->pai);
            percorrePraFrente = percorrePraFrente->prox;
        }
        if(percorrePraTras != NULL) {
            InsereCidadeFinal(&praTras, percorrePraTras->cidade, c1->pai);
            percorrePraTras = percorrePraTras->ant;
        }
        if(percorrePraFrente != NULL && strcmpi(percorrePraFrente->cidade.nome, destino) == 0) {
            InsereCidadeFinal(&praFrente, percorrePraFrente->cidade, c1->pai);
            LiberaListaCidade(&praTras);
            return praFrente;
        }
        if(percorrePraTras != NULL && strcmpi(percorrePraTras->cidade.nome, destino) == 0){
            InsereCidadeFinal(&praTras, percorrePraTras->cidade, c1->pai);
            LiberaListaCidade(&praFrente);
            return praTras;
        }
    }
    return NULL;
}


void ImprimeRota(lista_cidade rota) {
    if(rota == NULL) return;
    double dist = 0;
    double vMediaT = 0;
    int qtd = 0;
    double pr = 0;
    nodeC *carro = rota;
    int lineBreak = 1;
    while(carro != NULL) {
        pr += carro->pai->estrada.pedagio;
        vMediaT += carro->pai->estrada.velMedia;
        dist += carro->cidade.distanciaProx;
        if(carro->prox != NULL) printf("%s -> ", carro->cidade.nome);
        else printf("%s\n", carro->cidade.nome);
        if(lineBreak % 8 == 0) printf("\n-> ");
        lineBreak++;
        qtd++;
        carro = carro->prox;
    }
    double tempo = dist/(vMediaT/qtd);
    if(tempo < 0) tempo = 0; //correção caso algum dos valores seja 0
    printf("Preço esperado:R$%.2lf. Distância esperada: %.2lfKm. Tempo de viagem esperado: %02d:%02d horas\n",
           pr, dist, (int)tempo, (int)((tempo - (int)tempo)*60));

    LiberaListaCidade(&rota);
}

//encontra as cidade (caminho) entre as duas rodovias
lista_cidade
CaminhoEntreRodovias(int qtd, int rodovias[qtd], char *origem, char *destino, lista_rodovia cabeca) {
    if(qtd == 0) return 0;
    lista_cidade cmc = AchaRodoviaCodigo(rodovias[0], cabeca)->cidades, final = AchaRodoviaCodigo(rodovias[qtd-1], cabeca)->cidades;

    while(strcmpi(cmc->cidade.nome, origem) != 0) {
        cmc = cmc->prox;
        if(cmc == NULL) return NULL;
    }
    while(strcmpi(final->cidade.nome, destino) != 0) {
        final = final->prox;
        if(final == NULL) return NULL;
    }

    nodeC *atual = cmc, *roteia = NULL;
    InsereCidadeFinal(&roteia, cmc->cidade, cmc->pai);
    for(int i = 0; i < qtd - 1; i++) {
        nodeC *intersecc = AchaCruzamento(rodovias[i], rodovias[i + 1], cabeca);
        if(intersecc == NULL) return NULL;
        //*preco += intersecc->pai->estrada.pedagio;
        lista_cidade rotaTemp = EncontraRotaLocal(atual, intersecc->cidade.nome);
        if(rotaTemp == NULL) return NULL;
        atual = intersecc;
        for(nodeC *add = rotaTemp->prox; add != NULL; add = add->prox) {
            InsereCidadeFinal(&roteia, add->cidade, add->pai);
        }
        LiberaListaCidade(&rotaTemp);
    }
    lista_cidade rotaF = EncontraRotaLocal(atual, destino);
    if(rotaF != NULL) rotaF = rotaF->prox;
    while(rotaF != NULL) {
        InsereCidadeFinal(&roteia, rotaF->cidade, rotaF->pai);
        auto f = rotaF;
        rotaF = rotaF->prox;
        free(f);
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
        printf("A Cidade %s não foi encontrada!\n", destino);
        return NULL;
    }
    if(qtdRodoviasC1 == 0) {
        printf("A Cidade %s não foi encontrada!\n", origem);
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
        //double preco = 0;
        for(int j = 0; j < qtdRodoviasC2; j++) {
            desvios = bfs(rodoviasC1[i], rodoviasC2[j], cabeca, caminhoRodovia);
            if(desvios) { //retorna o primeiro caminho encontrado
                auto cam = CaminhoEntreRodovias(desvios, caminhoRodovia, origem,
                                                destino,cabeca);
                if(cam != NULL) return cam;
            }
        }
    }

    return NULL;
}

