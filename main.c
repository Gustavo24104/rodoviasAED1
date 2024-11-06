#include <stdio.h>
#include <stdlib.h>
#include "headers/Rodovias.h"
#include <string.h>
#include <locale.h>
#include "headers/Caminhos.h"
#include <unistd.h>

#define MAX 150



int main() {
    //-----------------------------------------Inicialização------------------------------------------------------------
    setlocale(LC_ALL, "pt_br.UTF8");
    lista_rodovia cabeca; //<- PONTEIRO PRA RODOVIA
    IniciaListaRodoviaVazia(&cabeca);
    //-----------------------------------------Inicialização------------------------------------------------------------


    //-------------------------------------------Menu-------------------------------------------------------------------
    printf("Bem vindo ao gerenciador de rodovias virtuais!\n");
    printf("                                                         _________________________   \n"
           "                           _____          _____       |   |     |     |    | |  \\  \n"
           "     ,-----,          ____/__|__\\_    ___/__|__\\___   |___|_____|_____|____|_|___\\ \n"
           "  ,--'---:---`--,    |  _     |     `| |      |      `| |                    | |    \\\n"
           " ==(o)-----(o)==J    `(o)-------(o)=   `(o)------(o)'   `--(o)(o)--------------(o)--'  \n"
           "`````````````````````````````````````````````````````````````````````````````````````");

    int escolha = 0;
    while(1) {
        printf("\n Faça sua seleção:\n"
               "-1: Sair\n"
               "1: Ler cidades e rodovias de um arquivo\n"
               "2: Inserir rodovia\n"
               "3: Inserir cidade em rodovia\n"
               "4: Encontrar rota entre duas cidades\n"
               "5: Remover rodovia\n"
               "6: Remover cidade de rodovia\n"
               "7: Imprimir rodovias carregadas\n"
               "8: Grava rodovias e cidades em um arquivo\n");
        scanf("%d", &escolha);
        getchar();
        if(escolha == -1) break;

        switch (escolha) {
            default : {
                continue;
            }
            case -1:
                break;
            case 1: {
                int carregar = 1;
                if(cabeca != NULL) {
                    printf("Um arquivo ja foi carregado, deseja carregar outro?[S/N]\n"
                           "(isso ira sobreescrever as rodovias carregadas!\n");
                    char e;
                    while (1) {
                        scanf("%c", &e);
                        getchar();
                        if (e == 'S' || e == 's') {
                            LiberaListaRodovia(&cabeca);
                            break;
                        }
                        if(e == 'n' || e == 'N') {
                            carregar = 0;
                            break;
                        }
                    }
                }
                if(carregar == 0) continue;
                char nomeArquivo[150];
                printf("Insira nome do arquivo (incluindo extensão) que você deseja ler:\n");
                fgets(nomeArquivo, 150, stdin);
                nomeArquivo[strlen(nomeArquivo) - 1] = '\0';
                FILE *arq = fopen(nomeArquivo, "r");
                if(arq == NULL) {
                    printf("Falha na abertura do arquivo!\n");
                    break;
                }
                if(CarregaRodovias(&cabeca, arq) == 0) {
                    printf("Arquivo %s lido com sucesso!\n", nomeArquivo);
                    fclose(arq);
                    continue;
                }
                else {
                    printf("Algo deu errado na leitura do arquivo!\n");
                    continue;
                }
            }
            case 2: {
                printf("Insira codigo da rodovia que deseja inserir:\n");
                int code;
                scanf("%d", &code);
                getchar();
                if(AchaRodoviaCodigo(code, cabeca) != NULL) {
                    printf("Rodovia ja existente!\n");
                    continue;
                }
                rodovia r;
                double p, t, v;
                printf("Insira pedagio (0 caso nao tenha), tamanho, e velocidade da rodovia:\n");
                scanf("%lf %lf %lf", &p, &t, &v);
                r.codigo = code; r.pedagio = p; r.tamanho = t; r.velMedia = v;
                InsereRodoviaOrdenado(&cabeca, r);
                continue;
            }
            case 3: {
                printf("Insira código da rodovia a qual deseja inserir:\n");
                int code;
                scanf("%d", &code);
                getchar();
                printf("Agora insira nome da cidade a qual deseja inserir:\n");
                char nome[100];
                fgets(nome, 100, stdin);
                nome[strlen(nome) - 1] = '\0';
                city c;
                strcpy(c.nome, nome);
                printf("Agora insira distância da proxima cidade (pode ser 0):\n");
                float dist = 0;
                scanf("%f", &dist);
                getchar();
                c.distanciaProx = dist;
                lista_rodovia rodAInserir = AchaRodoviaCodigo(code, cabeca);
                if(rodAInserir == NULL) {
                    printf("Rodovia de numero %d nao encontrada!\n", code);
                    continue;
                }
                if(InsereCidadeFinal(&rodAInserir->cidades, c) == 0) {
                    printf("Inserido com sucesso!\n");
                } else printf("Algo deu errado!\n");
                continue;
            }
            case 4: {
                if(cabeca == NULL) {
                    printf("Rodovias nao carregadas!\n");
                    continue;
                }
                char c1[100], c2[100];
                printf("Insira nome da primeira cidade:\n");
                fgets(c1, 100, stdin);
                printf("Insira nome da segunda cidade:\n");
                fgets(c2, 100, stdin);
                c1[strlen(c1) - 1] = '\0';
                c2[strlen(c2) - 1] = '\0';
                lista_cidade rota = EncontraRota(c1, c2, cabeca);
                if(rota == NULL) {
                    printf("Nao foi possível encontrar rota!\n");
                    continue;
                }
                printf("Caminho desejado:\n");
                printf("   -           __\n"
                       " --          ~( @\\   \\\n"
                       "---   _________]_[__/_>________\n"
                       "     /  ____ \\ <>     |  ____  \\\n"
                       "    =\\_/ __ \\_\\_______|_/ __ \\__D\n"
                       "________(__)_____________(__)____\n");
                ImprimeRota(rota);
                continue;
            }
            case 5: {
                if(cabeca == NULL) {
                    printf("Lista de rodovias nao carregada!\n");
                    continue;
                }
                printf("Insira codigo da rodovia a remover:\n");
                int code;
                scanf("%d", &code);
                getchar();
                if(AchaRodoviaCodigo(code, cabeca) == NULL) {
                    printf("Rodovia nao encontrada!\n");
                    continue;
                }
                RemoveRodovia(&cabeca, code);
                printf("Rodovia removida!\n");
                continue;
            }
            case 6: {
                if(cabeca == NULL) {
                    printf("Rodovias nao carregadas!\n");
                    continue;
                }
                int code;
                printf("Remover de qual rodovia?\n");
                scanf("%d", &code);
                getchar();
                printf("Qual cidade?\n");
                char cid[100];
                fgets(cid, 100, stdin);
                cid[strlen(cid) - 1] = '\0';
                int retorno = RemoveCidade(cabeca, code, cid);
                if(retorno == 2) {
                    printf("Rodovia nao encontrada!\n");
                    continue;
                }
                if(retorno == 1) {
                    printf("Cidade nao encontrada na rodovia!\n");
                    continue;
                } else {
                    printf("Cidade removida!\n");
                    continue;
                }
            }
            case 7: {
                if(cabeca == NULL) {
                    printf("Lista de rodovias vazia!\n");
                    continue;
                }
                ImprimeRodovias(cabeca);
                continue;
            }
            case 8: {
                if(cabeca == NULL) {
                    printf("Nao há rodovia carregada!\n");
                    continue;
                }
                printf("Insira nome do arquivo (incluindo extensao):\n");
                char caminhoArq[100];
                fgets(caminhoArq, 100, stdin);
                caminhoArq[strlen(caminhoArq) - 1] = '\0';
                int write = 1;
                if(access(caminhoArq, F_OK) == 0) { //checa se o arquivo existe
                    while(1) {
                        printf("Arquivo %s ja existente! Deseja sobreescreve-lo? [S/N]\n", caminhoArq);
                        char op;
                        scanf("%c", &op);
                        if(op == 'N' || op == 'n') {
                            write = 0;
                            break;
                        }
                        else if(op == 'S' || op == 's') {
                            write = 1;
                            break;
                        }
                    }
                }
                if(write == 0) continue;
                if (EscreveArquivo(cabeca, caminhoArq) == 0) {
                    printf("Arquivo escrito com sucesso!\n");
                    continue;
                } else printf("Algo deu errado na escrita no arquivo\n");
                continue;
            }
        }

    }
    //-------------------------------------------Menu-------------------------------------------------------------------



    return 0;
}



