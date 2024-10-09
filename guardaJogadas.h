

#ifndef TRABALHOPRATICO1_GUARDAJOGADAS_H
#define TRABALHOPRATICO1_GUARDAJOGADAS_H

#include <stdio.h>

typedef struct jogadas jogada, *pjogada;
struct jogadas{

    int nMiniTab, linha, coluna;
    int jogador;
    int numJogada;

    pjogada ant;
    pjogada prox;
};

pjogada adicionaJogada(pjogada p, int nMiniTab, int linha, int coluna, int jogador, int numJogada);
void mostraJogadaKJogadasAnteriores(pjogada p, int k);
pjogada procuraJogadaAnterior(pjogada p);

#endif //TRABALHOPRATICO1_GUARDAJOGADAS_H
