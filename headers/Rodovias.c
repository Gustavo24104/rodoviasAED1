#include "Rodovias.h"
#include "cidades.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//TODO: Funções de menu




int EscreveArquivo(lista_rodovia cabeca, char* caminhoArquivo) {
    //As rodovias devem estar listadas do modo CODIGO-PEDAGIO-TAMANHO-VELOCIDADE
    //As cidades deverão estar do modo "NOME CIDADE"-DISTANCIA
    //Números fracionais devem estar separados com vírgula (Ex: 2,4)
    FILE* arq = fopen(caminhoArquivo, "w");
    if(arq == NULL) return 1;
    nodeR *rodovias = cabeca;
    while(rodovias != NULL) {
        fprintf(arq, "%03d-%.2lf-%.2lf-%.2lf\n", rodovias->estrada.codigo, rodovias->estrada.pedagio,
                rodovias->estrada.tamanho, rodovias->estrada.velMedia);
        nodeC *cidades = rodovias->cidades;
        while(cidades != NULL) {
            fprintf(arq,"%s-%.2lf\n", cidades->cidade.nome, cidades->cidade.distanciaProx);
            cidades = cidades->prox;
        }
        fprintf(arq, "\n");
        rodovias = rodovias->prox;
    }

    fclose(arq);
    return 0;
}

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
    if(lr == NULL) return 1;
    if((*lr)->estrada.codigo == codigo){
        *lr = (*lr)->prox;
        return 0;
    }
    return RemoveRodovia(&(*lr)->prox, codigo);
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

////Encontra a primeira rodovia que tem uma certa cidade
//lista_rodovia AchaRodoviaPorNome(char* cid, lista_rodovia lr) {
//    lista_rodovia aux = lr;
//    while(aux != NULL){
//        lista_cidade aux2 = aux->cidades;
//        while(aux2 != NULL) {
//            if(strcmpi(cid, aux2->cidade.nome) == 0) return aux;
//            aux2 = aux2->prox;
//        }
//        aux = aux->prox;
//    }
//    return NULL;
//}

//lista_rodovia AchaCidadePorNome(char* cid, lista_rodovia lr) {
//    lista_rodovia aux = lr;
//    while(aux != NULL){
//        lista_cidade aux2 = aux->cidades;
//        while(aux2 != NULL) {
//            if(strcmpi(cid, aux2->cidade.nome) == 0) return aux;
//            aux2 = aux2->prox;
//        }
//        aux = aux->prox;
//    }
//    return NULL;
//}

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
int CruzamentoNaCidade(lista_rodovia lr, int codigo1, int codigo2, char *cidade) {
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

nodeC* AchaCruzamento(int cod1, int cod2, lista_rodovia cabeca) {
    if(cabeca == NULL) return NULL;
    nodeR *r1 = cabeca, *r2 = cabeca;
    while(r1->estrada.codigo != cod1) r1 = r1->prox;
    while(r2->estrada.codigo != cod2) r2 = r2->prox;
    nodeC *cid1 = r1->cidades;

    while(cid1 != NULL) {
        nodeC *cid2 = r2->cidades;
        while(cid2 != NULL) {
            if(strcmpi(cid1->cidade.nome, cid2->cidade.nome) == 0) {
                //printf("Cruzamento de %d e %d em: %s\n", cod1, cod2, cid2->cidade.nome);
                return cid2;
            }
            cid2 = cid2->prox;
        }
        cid1 = cid1->prox;
    }
    return NULL;
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






