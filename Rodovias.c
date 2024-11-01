#include "Rodovias.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//TODO: MODULARIZAR MAIS AS FUNÇÕES!!!!
int IniciaListaRodoviaVazia(lista_rodovia *li) {
    *li = malloc(sizeof(lista_rodovia));
    if(*li == NULL) {
        printf("Erro de alocacao!\n");
        return 0;
    }
    *li = NULL;
    return 1;
}

int InicializaCidades(lista_cidade *lc) {
    *lc = malloc(sizeof (lista_cidade));
    if(*lc == NULL) {
        printf("Erro de alocacao!\n");
        return 0;
    }
    *lc = NULL;
    return 1;
}


int BuscaBinariaRodovia(int codigo, lista_rodovia lr[], int tam) {
    if(lr == NULL) return 0;
    auto val = lr[(int)tam/2]->estrada.codigo;
    if(val == codigo) return 1;
    if(tam == 1) return 0;
    if(val < codigo) return BuscaBinariaRodovia(codigo, lr + tam/2 + 1, tam/2);
    if(val > codigo) return BuscaBinariaRodovia(codigo, lr, tam/2);
}



void LiberaListaCidade(lista_cidade *lc) {
    if(lc == NULL) return;
    if(*lc == NULL) return;
    nodeC *aux = *lc, *freeAux;
    while(aux != NULL) {
        freeAux = aux;
        aux = aux->prox;
        free(freeAux);
    }
    *lc = NULL;
    //lc = NULL;
    free(*lc);

}

void LiberaListaRodovia(lista_rodovia *lr) {
    nodeR *aux = *lr, *freeAux;
    while(aux != NULL) {
        freeAux = aux;
        LiberaListaCidade(&(freeAux->cidades));
        aux = aux->prox;
        free(freeAux);
    }
    free(*lr);
    *lr = NULL;
}

int RemoveCidade(lista_cidade lc, char* nomeCidade) {
    //TODO
}

int RemoveRodovia(lista_rodovia *lr, int codigo) {
    //TODO
}


//Acha rodovias que contem uma cidade e armazena em codes, retornando o tamanho
int AchaCidade(char* cidade, lista_rodovia lr, nodeR *codes[]) {
    int i = 0;
    lista_rodovia auxR = lr;
    while(auxR != NULL) {
        lista_cidade auxC = auxR->cidades;
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
 * @return 0 -> Erro; 1 -> Sucesso
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
        return 0;
    }
    if(*li == NULL) { //Primeira rodovia da lista
        *li = novo;
        return 1;
    }
    novo->prox = *li;
    *li = novo;
    return 1;
}

int InsereRodoviaOrdenado(lista_rodovia *lr, rodovia rod) {
    /* Insere ordenado pra poder fazer busca binaria */
    nodeR *novo = malloc(sizeof(nodeR));
    if(novo == NULL) return 0;
    novo->estrada = rod;
    novo->prox = NULL;
    novo->cidades = NULL;
    if (InicializaCidades(&(novo->cidades)) == 0) return 0;
    if(lr == NULL) return 0;
    if(*lr == NULL) {
        *lr = novo;
        return 1;
    }
    nodeR *aux = *lr, *ant = NULL;
    while(aux != NULL && aux->estrada.codigo < rod.codigo) {
        ant = aux;
        aux = aux->prox;
    }

    if(ant == NULL) {
        novo->prox = *lr;
        *lr = novo;
        return 1;
    }

    if(aux == NULL) {
        ant->prox = novo;
        novo->prox = NULL;
        return 1;
    }

    ant->prox = novo;
    novo->prox = aux;
    return 1;
}


/**
 * Insere uma cidade na rodovia especificada pelo codigo
 * @param lista rodovia
 * @param codigoRodovia codigo da rodovia
 * @param cidade cidade a inserir
 * @return 0 = falha 1 = sucesso
 */
int InsereCidadeEmRodovia(lista_rodovia lista, int codigoRodovia, city cidade) {
    if(lista == NULL) {
        printf("Rodovia nao encontrada!\n");
        return 0;
    }
    if(lista->estrada.codigo == codigoRodovia) { //Achada a rodovia para inserir a cidade
        nodeC *novo = malloc(sizeof(nodeC));
        if(novo == NULL) {
            printf("Erro de alocacao!\n");
            return 0;
        }
        novo->cidade = cidade;
        novo->prox = NULL;
        novo->ant = NULL;
        if(lista->cidades == NULL) { //Primeira cidade da rodovia, inserindo na cabeça
            lista->cidades = novo;
            return 1;
        }
        lista->cidades->ant = novo;
        novo->prox = lista->cidades;
        lista->cidades = novo;
        return 1;
    }
    return InsereCidadeEmRodovia(lista->prox, codigoRodovia, cidade);
}




int InsereCidade(lista_cidade *lc, city c) {
    if(lc == NULL) return 0;

    nodeC *novo = malloc(sizeof(nodeC));
    novo->cidade = c;
    novo->prox = NULL;
    novo->ant = NULL;
    if(*lc == NULL) {
        *lc = novo;
        return 1;
    }
    (*lc)->ant = novo;
    novo->prox = *lc;
    (*lc) = novo;
    return 1;
}






void ImprimeCidades(lista_cidade l) {
    if(l == NULL) return;
    if(l->prox == NULL) {
        printf("    %s\n", l->cidade.nome);
        return;
    }
    printf("    %s | Distancia ate a proxima: %.2fkm\n", l->cidade.nome, l->cidade.distanciaProx);
    ImprimeCidades(l->prox);
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
 * @return 1 = Sucesso, 0 = Erro
 */
int CarregaRodovias(lista_rodovia *cabeca, FILE* arq) {
    if(cabeca == NULL) {
        printf("Lista nao incializada!\n");
        return 0;
    }
    if(arq == NULL) {
        printf("Erro no arquivo!");
        return 0;
    }
    char buffer[200];
    int cod = 0;
    double ped = 0;
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
            InsereRodoviaOrdenado(cabeca, rod);
            cod = (int)n1; //Se nao for 0, entao o que ele econtrou foi um codigo de rodovia.
            ped = n2;
            continue;
        }
        city c;
        strcpy(c.nome, tok);
        c.distanciaProx = n2;
        if (InsereCidadeEmRodovia(*cabeca, cod, c) == 0) return 0;
    }
    return 1;
}

/**
 * Encontra a primeira cidade de intersecção entre 2 rodovias
 * @param codigo1 codigo da primeira rodovia
 * @param codigo2 codigo da segunda rodovia
 * @return "ERR" caso haja algum erro.
 * @return 0 caso nao haja interseccao.
 * @return Nome da cidade caso exista
 */
char* Cruzamento(lista_rodovia lr,int codigo1, int codigo2) {
    if(lr == NULL) return "ERR";
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
    if(lc1 == NULL || lc2 == NULL) return "ERR"; //alguma rodovia nao foi encontrada

    while(lc1 != NULL) {
        lista_cidade aux2 = lc2;
        while(aux2 != NULL) {
            if(strcmpi(lc1->cidade.nome, aux2->cidade.nome) == 0) return lc1->cidade.nome;
            aux2 = aux2->prox;
        }
        lc1 = lc1->prox;
    }
    return 0;
}


/**
 * Encontra uma rota da cidade1 para cidade2
 * @param cidade1 Cidade inicial
 * @param cidade2 Cidade final
 * @param lr Lista de rodovias
 * @return rota como uma lista encadeada de cidades (?)
 * @return NULL caso nao exista caminho.
 */
lista_cidade EncontraRota(char* cidade1, char* cidade2, lista_rodovia lr) {
    /* TODO: Ideia ate agora:
     * Primeiro passo: Verifica se não tao na mesma rodovia (se tiverem o caminho é trivial)
     * Caso contrário, usa a função AchaCidades pra ter uma visão geral de quais rodovias olhar e verifica uma a uma
     * Algo desse nível
     */

    nodeR *rodoviasC1[100],  *rodoviasC2[100];
    int qtdRodoviasC1, qtdRodoviasC2;
    qtdRodoviasC1 = AchaCidade(cidade1, lr, rodoviasC1);
    qtdRodoviasC2 = AchaCidade(cidade2, lr, rodoviasC2);
    //caso as cidades estejam na mesma rodovia:
    for(int i = 0; i < qtdRodoviasC1; i++) { //TRIVIAL!!!!!!!!!!!!!!
        if(BuscaBinariaRodovia(rodoviasC1[i]->estrada.codigo, rodoviasC2, qtdRodoviasC2)) {
            //estao na mesma rodovia!
            lista_cidade c1 = rodoviasC1[i]->cidades;
            while(strcmpi(c1->cidade.nome, cidade1) != 0) c1 = c1->prox;
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
                if(percorrePraFrente != NULL && strcmpi(percorrePraFrente->cidade.nome, cidade2) == 0) {
                    InsereCidade(&praFrente, percorrePraFrente->cidade);
                    LiberaListaCidade(&praTras);
                    LiberaListaCidade(&c1); //n precisa liberar o q aponta pra c1
                    return praFrente;
                }
                if(percorrePraTras != NULL && strcmpi(percorrePraTras->cidade.nome, cidade2) == 0){
                    InsereCidade(&praTras, percorrePraTras->cidade);
                    LiberaListaCidade(&praFrente);
                    LiberaListaCidade(&c1); //n precisa liberar o q aponta pra c1
                    return praTras;
                }
            }
        }
    }
    //caso contrário:
    printf("QUE?!\n"); //TODO: Não tenho a **menor** ideia do q fazer aqui!!!!
    lista_rodovia aux = lr;




    //return NULL;
}

