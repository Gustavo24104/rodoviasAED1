#include "Rodovias.h"
#include "cidades.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//TODO: MODULARIZAR MAIS AS FUNÇÕES!!!!
//TODO: Função de imprimir rota
//TODO: Funções de remover
//TODO: Funções de menu


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
    if(lr == NULL) return 0;
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

lista_rodovia AchaRodoviaPorNome(char* cid, lista_rodovia lr) {
    lista_rodovia aux = lr;
    while(lr != NULL){
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
        if(auxC->cidade.nome == ' ') return 0;
        while(auxC != NULL) {
            if(strcmpi(auxC->cidade.nome, cidade) == 0) {
                codes[i++] = auxR;
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
    if (InicializaCidades(&(novo->cidades)) == 0) return 0;
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
        lista->cidades->ant = novo;
        novo->prox = lista->cidades;
        lista->cidades = novo;
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
 * Encontra as cidades onde as rodovias se cruzam e armazena no vetor codes
 * @param codigo1 codigo da primeira rodovia
 * @param codigo2 codigo da segunda rodovia
 * @return retorna a qtidade de cruzamentos
 */
int Cruzamento(lista_rodovia lr,int codigo1, int codigo2, nodeC *codesR1[], nodeC *codesR2[]) {
    int count = 0;
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
            if(strcmpi(lc1->cidade.nome, aux2->cidade.nome) == 0) {
                codesR1[count] = lc1;
                codesR2[count] = aux2;
                count++;
            }
            aux2 = aux2->prox;
        }
        lc1 = lc1->prox;
    }
    return count;
}

int CruzamentoPorPonteiro(lista_rodovia l1, lista_rodovia l2, nodeC *codesR1[], nodeC *codesR2[]) {
    int count = 0;
    lista_cidade lc1 = l1->cidades;
    while(lc1 != NULL) {
        lista_cidade aux2 = l2->cidades;
        while(aux2 != NULL) {
            if(strcmpi(lc1->cidade.nome, aux2->cidade.nome) == 0) {
                codesR1[count] = lc1;
                codesR2[count] = aux2;
                count++;
            }
            aux2 = aux2->prox;
        }
        lc1 = lc1->prox;
    }
    return count;
}


lista_cidade RotaAux(char* cidade1, char *cidade2, lista_rodovia rodoviasC1) {
    //estao na mesma rodovia!

}

/**
 * Encontra uma rota da cidade1 para cidade2
 * @param cidade1 Cidade inicial
 * @param cidade2 Cidade final
 * @param rod1 Rodovia que se localiza a primeira cidade
 * @param rod2 Rodovia que se localiza a segunda cidade
 * @return rota como uma lista encadeada de cidades (?)
 * @return NULL caso nao exista caminho.
 */
lista_cidade EncontraRota(char *cidade1, char *cidade2, lista_rodovia rod1, lista_rodovia rod2) {
    /* TODO: Ideia ate agora:
     * Primeiro passo: Verifica se não tao na mesma rodovia (se tiverem o caminho é trivial)
     * Caso contrário, usa a função RodoviasDaCidades pra ter uma visão geral de quais rodovias olhar e verifica uma a uma
     * Algo desse nível
     */

    if(rod1 == rod2) {
        lista_cidade c1 = rod1->cidades;
        while (strcmpi(c1->cidade.nome, cidade1) != 0) c1 = c1->prox;
        lista_cidade percorrePraFrente = c1, percorrePraTras = c1;
        lista_cidade praFrente, praTras;
        InicializaCidades(&praTras);
        InicializaCidades(&praFrente);
        while (1) { //n
            if (percorrePraFrente == NULL && percorrePraTras == NULL) {

            } //Isso aqui n eh pra acontecer nunca KKKKKKKK
            if (percorrePraFrente != NULL) {
                InsereCidade(&praFrente, percorrePraFrente->cidade);
                percorrePraFrente = percorrePraFrente->prox;
            }
            if (percorrePraTras != NULL) {
                InsereCidade(&praTras, percorrePraTras->cidade);
                percorrePraTras = percorrePraTras->ant;
            }
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
    }

    nodeC *c1 = rod1->cidades, *c2 = rod2->cidades;
    while(strcmpi(cidade1, c1->cidade.nome) != 0) c1 = c1->prox;
    while(strcmpi(cidade2, c2->cidade.nome) != 0) c2 = c2->prox;

    //agora vai.


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




