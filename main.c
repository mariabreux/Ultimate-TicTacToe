#include <stdio.h>

#include "tabuleiro.h"
#include "menus.h"
#include "jogo.h"
#include "guardaJogadas.h"
#include "interromperJogo.h"
#include "utils.h"

int main() {

    pjogada p = NULL;
    jogador j[2];

    j[0].numJogador = 1;
    j[0].peca = 'X';

    j[1].numJogador = 2;
    j[1].peca = 'O';

    char ***mat = criaTab(3,3,9);
    int jogadorAtual = intUniformRnd(0,1);
    int numJogada = 1;

    int opcao;

        menuPrincipal();
    do {
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
    }while(opcao<0 || opcao>3);

    switch(opcao){
        case 0:
            retomaJogo();
            break;
        case 1:
            iniciaJogo(1, p, numJogada, mat, jogadorAtual, j);
            break;
        case 2:
            iniciaJogo(2, p, numJogada, mat, jogadorAtual, j);
            break;
        default:
            break;
    }


    return 0;
}
