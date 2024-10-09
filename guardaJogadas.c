#include <stdio.h>
#include <stdlib.h>

#include "guardaJogadas.h"


pjogada adicionaJogada(pjogada p, int nMiniTab, int linha, int coluna, int jogador, int numJogada){

    pjogada novo, aux;

    novo = malloc(sizeof(jogada));
    if(novo == NULL){
        return p;
    }
    novo->nMiniTab = nMiniTab;
    novo->linha = linha;
    novo->coluna = coluna;
    novo->jogador = jogador;
    novo->numJogada = numJogada;
    novo->prox = NULL;
    novo->ant = NULL;

    if(p == NULL){
        p = novo;
    }
    else {
        aux = p;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }
    return p;
}

void mostraJogadaKJogadasAnteriores(pjogada p, int k){

    pjogada fim = p;

    while (fim->prox != NULL)
        fim=fim->prox;

    for (int i = k; i>0 ; i--) {

        printf("\n-----------Jogada %d---------\n", fim->numJogada);
        printf("Jogador: %d \nMini Tabuleiro: %d\nLinha: %d\nColuna: %d\n",fim->jogador,fim->nMiniTab,fim->linha,fim->coluna);

        fim=fim->ant;
    }
}

pjogada procuraJogadaAnterior(pjogada p){

    pjogada atual = p;

    while(atual->prox != NULL){
        atual = atual->prox;
    }

    return atual;
}