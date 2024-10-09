
#ifndef TRABALHOPRATICO1_JOGO_H
#define TRABALHOPRATICO1_JOGO_H


#include "guardaJogadas.h"

typedef struct jogadores{
    int numJogador;
    char peca;
} jogador;


void iniciaJogo(int tipoJogo, pjogada p, int numJogada, char ***mat, int jogadorAtual, jogador j[2]);
int fazJogada(pjogada *p, char ***mat, jogador j, int numJogada, int pInt[3][3]);
int verificaJogada(char ***mat, int nMiniTab, int *linha, int *coluna);
int verificaLinhasMini(char ***mat, int nMiniTab);
int verificaColunasMini(char ***mat, int nMiniTab);
int verificaDiagonaisMini(char ***mat, int nMiniTab);
int verificaVitoriaMini(char ***mat, int nMiniTab, jogador j, int pInt[3][3]);
void mostraJogadasAnteriores(pjogada p, int numJogada);
int escolheMiniTab(pjogada p, int aleatorio);
int verificaVitoriaFinal(int vencedores[3][3]);


#endif //TRABALHOPRATICO1_JOGO_H
