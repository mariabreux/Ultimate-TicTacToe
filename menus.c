
#include "menus.h"

void menuPrincipal(){

    FILE *f = fopen("jogo.bin", "rb");

    //verifica se existe um jogo guardado no ficheiro "jogo.bin"; se sim, apresenta a opção de o retomar
    if(f != NULL)
        printf("0 - Retomar Jogo\n");
    fclose(f);

    printf("1 - Iniciar Jogo (1 Jogador)\n");
    printf("2 - Iniciar Jogo - 2 Jogadores\n");
    printf("3 - Sair\n");
}

void menuJogo(){

    printf("1 - Fazer Jogada\n");
    printf("2 - Interromper Jogo\n");
    printf("3 - Mostrar Jogadas Anteriores\n");
    printf("4 - Desistir\n");
}