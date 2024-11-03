#include "Rodovias.h"
#include "cidades.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>



//TODO: MODULARIZAR MAIS AS FUNÇÕES!!!!
//TODO: Função de imprimir rota
//TODO: Funções de remover
//TODO: Funções de menu

nodeR* InsereRodoviaOrdenado(lista_rodovia *lr, rodovia rod) { //retorna a adicionada
    /* Insere ordenado pra poder fazer busca binaria */
    nodeR *novo = malloc(sizeof(nodeR));
    if(novo == NULL) return NULL;
    if(lr == NULL) return NULL;
    novo->estrada = rod;
    novo->prox = NULL;
    novo->cidades = NULL;
    if (InicializaCidades(&(novo->cidades)) == 1) return NULL;
    if(*lr == NULL) {
        *lr = novo;
        return novo;
    }
    nodeR *aux = *lr, *ant = NULL;
    while(aux != NULL && aux->estrada.codigo < rod.codigo) {
        ant = aux;
        aux = aux->prox;
    }

    if(ant == NULL) {
        novo->prox = *lr;
        *lr = novo;
        return novo;
    }

    if(aux == NULL) {
        ant->prox = novo;
        novo->prox = NULL;
        return novo;
    }

    ant->prox = novo;
    novo->prox = aux;
    return novo;
}


int ContaRodovias(lista_rodovia c) {
    lista_rodovia aux = c;
    int i = 0;
    while(c != NULL) {
        c = c->prox;
        i++;
    }
    return i;
}

int IniciaListaRodoviaVazia(lista_rodovia *li) {
    *li = malloc(sizeof(lista_rodovia));
    if(*li == NULL) {
        printf("Erro de alocacao!\n");
        return 1;
    }
    *li = NULL;
    return 0;
}



int BuscaBinariaRodovia(int codigo, lista_rodovia lr[], int tam) {
    if(lr == NULL || tam == 0) return 0;

    auto val = lr[(int)tam/2]->estrada.codigo;
    if(val == codigo) return 1;
    if(tam == 1) return 0;
    if(val < codigo) return BuscaBinariaRodovia(codigo, lr + tam/2 + 1, tam/2);
    if(val > codigo) return BuscaBinariaRodovia(codigo, lr, tam/2);
}


void LiberaListaRodovia(lista_rodovia *lr) {
    nodeR *aux = *lr, *freeAux;
    while(aux != NULL) {
        freeAux = aux;
        LiberaListaCidade(&(freeAux->cidades));
        aux = aux->prox;
        free(freeAux);
    }
    *lr = NULL;
}

int RemoveRodovia(lista_rodovia *lr, int codigo) {
    //TODO
}

int ElementoNaLista(nodeR *elem, nodeR *r1[], int t){
    for(int i = 0; i < t; i++){
        if(r1[i] == elem) {
            return 1;
        }
    }
    return 0;
}

/**
 * Encontra a lista de adjacencia de uma rodovia qualquer armazenando em adj
 * @param lr
 * @param adj
 * @return tamanho da lista
 */
int CriaListaAdjacencia(lista_rodovia lr, nodeR *adj[150], lista_rodovia cabeca) {

    //return qtdRodovias;
    int count = 0, tamanhoLimpa = 0;
    nodeR *suja[MAX];
    lista_cidade aux = lr->cidades;
    while(aux != NULL) {
        count += RodoviasDaCidade(aux->cidade.nome, cabeca, suja + count);
        aux = aux->prox;
    }

    for(int i = 0; i < count; i++){
        if(!ElementoNaLista(suja[i], adj, tamanhoLimpa) && suja[i]->estrada.codigo != lr->estrada.codigo) {
            adj[tamanhoLimpa++] = suja[i];
        }
    }
    return tamanhoLimpa;
}

//Encontra a primeira rodovia que tem uma certa cidade
lista_rodovia AchaRodoviaPorNome(char* cid, lista_rodovia lr) {
    lista_rodovia aux = lr;
    while(aux != NULL){
        lista_cidade aux2 = aux->cidades;
        while(aux2 != NULL) {
            if(strcmpi(cid, aux2->cidade.nome) == 0) return aux;
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
    return NULL;

}
lista_rodovia AchaCidadePorNome(char* cid, lista_rodovia lr) {
    lista_rodovia aux = lr;
    while(aux != NULL){
        lista_cidade aux2 = aux->cidades;
        while(aux2 != NULL) {
            if(strcmpi(cid, aux2->cidade.nome) == 0) return aux;
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
    return NULL;
}

//Acha rodovias que contem uma cidade e armazena em codes, retornando o tamanho
int RodoviasDaCidade(char* cidade, lista_rodovia lr, nodeR *codes[]) {
    int i = 0;
    lista_rodovia auxR = lr;
    while(auxR != NULL) {
        lista_cidade auxC = auxR->cidades;
        while(auxC != NULL) {
            //printf("Cidade: %s, de: %d\n", auxC->cidade.nome, auxR->estrada.codigo);
            if(strcmpi(auxC->cidade.nome, cidade) == 0) {
                if(codes == NULL) return 0;
                codes[i++] = auxR;
                //printf("Amigo pro %d em %d\n", auxR->estrada.codigo, codes[i - 1]->estrada.codigo);
            }
            auxC = auxC->prox;
        }
        auxR = auxR->prox;
    }
    return i;
}

/**
 * Insere uma rodovia na lista encadeada no inicio
 * @param li cabeça da lista
 * @param rod rodovia a inserir
 * @return 0 -> Sucesso; 1 -> Erro
 */
int InsereRodoviaInicio(lista_rodovia *li, rodovia rod) {
    nodeR *novo = malloc(sizeof(nodeR));
    if(novo == NULL) return 0;
    novo->estrada = rod;
    novo->prox = NULL;
    novo->cidades =  NULL;
    if (InicializaCidades(&(novo->cidades)) == 1) return 1;
    if(li == NULL) {
        printf("Lista nao inicializada!\n");
        return 1;
    }
    if(*li == NULL) { //Primeira rodovia da lista
        *li = novo;
        return 0;
    }
    novo->prox = *li;
    *li = novo;
    return 0;
}




lista_rodovia AchaRodoviaCodigo(int cod, lista_rodovia lr) {
    lista_rodovia aux = lr;
    while(aux != NULL) {
        if(aux->estrada.codigo == cod) return aux;
        aux = aux->prox;
    }
    return NULL;
}

/**
 * Insere uma cidade na rodovia especificada pelo codigo
 * @param lista rodovia
 * @param codigoRodovia codigo da rodovia
 * @param cidade cidade a inserir
 * @return 0 = sucesso 1 = falha
 */
int InsereCidadeEmRodovia(lista_rodovia lista, city cidade) {
    if(lista == NULL) {
        printf("Rodovia nao encontrada!\n");
        return 1;
    }

        nodeC *novo = malloc(sizeof(nodeC));
        if(novo == NULL) {
            printf("Erro de alocacao!\n");
            return 1;
        }
        novo->cidade = cidade;
        novo->prox = NULL;
        novo->ant = NULL;
        novo->pai = lista;
        if(lista->cidades == NULL) { //Primeira cidade da rodovia, inserindo na cabeça
            lista->cidades = novo;
            return 0;
        }
        lista_cidade aux = lista->cidades;
        while(aux->prox != NULL) {
            aux = aux->prox;
        }
        novo->ant = aux;
        aux->prox = novo;
//        lista->cidades->ant = novo;
//        novo->prox = lista->cidades;
//        lista->cidades = novo;
        return 0;
}


int InsereRodoviaFinal(lista_rodovia *lr, rodovia rod){
    if(lr == NULL) return 1;
    if(*lr == NULL) {
        nodeR *novo = malloc(sizeof(nodeR));
        if(novo == NULL) return 1;
        novo->prox = NULL;
        novo->estrada = rod;
        *lr = novo;
        return 0;
    }
    if((*lr)->prox != NULL) return InsereRodoviaFinal(&(*lr)->prox, rod);
    nodeR *novo = malloc(sizeof(nodeR));
    if(novo == NULL) return 1;
    novo->prox = NULL;
    novo->estrada = rod;
    (*lr)->prox = novo;
    return 0;
}

/**
 * Imprime as rodovias e suas respectivas cidades
 * @param l Rodovia a imprimir
 */
void ImprimeRodovias(lista_rodovia l) {
    if(l == NULL) return;
    printf("Código: BR-%03d. Pedagio: R$%03.2f. Tamanho: %.2lfKm, Velócidade média: %.2lfKm/h\n",
           l->estrada.codigo, l->estrada.pedagio, l->estrada.tamanho, l->estrada.velMedia);
    ImprimeCidades(l->cidades);
    ImprimeRodovias(l->prox);
}

/**
 * Lê as rodovias e respectivas cidades por meio de um arquivo, adicionando-os
 * No arquivo, um inicio de rodovia é indicado por um número (codigo da rodovia, seguido pelo preço do pedagio)
 * Cada linha seguinte é constituida de uma string de caracteres e um numero de ponto flutuante (Nome da cidade
 * e distancia ate a proxima)
 * Os preços sao separados por '-'
 * @param cabeca cabeça da lista de rodovias
 * @param arq arquivo que será feita a leitura
 * @return 1 = Erro, 0 = Sucesso
 */
int CarregaRodovias(lista_rodovia *cabeca, void* arq) {
    if(cabeca == NULL) {
        printf("Lista nao incializada!\n");
        return 1;
    }
    if(arq == NULL) {
        printf("Erro no arquivo!");
        return 1;
    }
    char buffer[200];
    //int cod = 0;
    //double ped = 0;
    nodeR *at;
    while(fgets(buffer, sizeof(buffer), arq)) { //Vai ate o EOF
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0'; //Remove o '\n' ao final da string
        }
        char *tok, *tok2, *tok3, *tok4;
        double n1, n2, n3, n4;
        //As rodovias devem estar listadas do modo CODIGO-PEDAGIO-TAMANHO-VELOCIDADE
        //As cidades deverão estar do modo "NOME CIDADE"-DISTANCIA
        //Números fracionais devem estar separados com vírgula (Ex: 2,4)
        tok = strtok(buffer,"-"); //Separa as linhas
        tok2 = strtok(NULL, "-");
        tok3 = strtok(NULL, "-");
        tok4 = strtok(NULL, "-");
        if(tok == NULL || tok2 == NULL) continue;
        //Converte o valor para numero, retorna 0 se nao consegue
        n1 = strtod(tok, NULL); //codigo rodovia
        n2 = strtod(tok2, NULL); //pedagio
        n3 = strtod(tok3, NULL); //tamanho
        n4 = strtod(tok4, NULL); //Velocidade media
        if (n1 != 0) {
            rodovia rod;
            rod.codigo = (int)n1;
            rod.pedagio = n2;
            rod.tamanho = n3;
            rod.velMedia = n4;
            at = InsereRodoviaOrdenado(cabeca, rod);
            //cod = (int)n1; //Se nao for 0, entao o que ele econtrou foi um codigo de rodovia.
            //ped = n2;
            continue;
        }
        city c;
        strcpy(c.nome, tok);
        c.distanciaProx = n2;
        if (InsereCidadeEmRodovia(at, c)) return 1;
    }
    return 0;
}

/**
 * Verifica se duas rodovias passam pela mesma cidade.
 * @param codigo1 codigo da primeira rodovia
 * @param codigo2 codigo da segunda rodovia
 * @return 1 se sim. 0 se não
 */
int Cruzamento(lista_rodovia lr, int codigo1, int codigo2, char *cidade) {
    if(lr == NULL) return -1;
    if(codigo1 == codigo2) return 0;
    lista_rodovia aux = lr;
    lista_cidade lc1 = NULL, lc2 = NULL;
    while(aux != NULL) { //acha rodovias pelo codigo
        if(aux->estrada.codigo == codigo1) {
            lc1 = aux->cidades;
        }
        if(aux->estrada.codigo == codigo2) {
            lc2 = aux->cidades;
        }
        if(lc1 != NULL && lc2 != NULL) break;
        aux = aux->prox;
    }
    if(lc1 == NULL || lc2 == NULL) return -1; //alguma rodovia nao foi encontrada

    while(lc1 != NULL) {
        lista_cidade aux2 = lc2;
        while(aux2 != NULL) {
            if(strcmpi(lc1->cidade.nome, aux2->cidade.nome) == 0
            && strcmpi(aux2->cidade.nome, cidade) == 0) {
                return 1;
            }
            aux2 = aux2->prox;
        }
        lc1 = lc1->prox;
    }
    return 0;
}

int CruzamentoPorPonteiro(lista_rodovia l1, lista_rodovia l2, nodeC *codesR1[], nodeC *codesR2[]) {
    int count = 0;
    lista_cidade lc1 = l1->cidades;
    while(lc1 != NULL) {
        lista_cidade aux2 = l2->cidades;
        while(aux2 != NULL) {
            if(strcmpi(lc1->cidade.nome, aux2->cidade.nome) == 0) {
                if(codesR1 != NULL) codesR1[count] = lc1;
                if(codesR2 != NULL) codesR2[count] = aux2;
                count++;
            }
            aux2 = aux2->prox;
        }
        lc1 = lc1->prox;
    }
    return count;
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






