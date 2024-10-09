
#include "interromperJogo.h"
#include "jogo.h"
#include "tabuleiro.h"

void interrompeJogo(int tipoJogo, pjogada p, int numJogadas, char ***mat, int jogadorAtual, jogador j[2]){

    pjogada aux = p;
    FILE *f;

    f = fopen("jogo.bin", "wb");

    if(f == NULL){
        printf("Erro no acesso ao ficheiro!\n");
        return;
    }

    fwrite(&tipoJogo, sizeof(int), 1, f);
    fwrite(&numJogadas, sizeof(int), 1, f);     //numero da jogada atual
    fwrite(&jogadorAtual, sizeof(int), 1, f);

    for (int i = 0; i < 2; ++i) {
        fwrite(&j[i], sizeof(jogador), 1, f);
    }

// Escrever tabuleiro no ficheiro
/*
    for (int k = 0; k < 9; ++k) {
        for (int l = 0; l < 3; ++l) {
            for (int m = 0; m < 3; ++m) {
                fwrite(&mat[k][l][m], sizeof(char), 1, f);
            }
        }
    }
*/

    for(int k=0; k<numJogadas-1; k++){
        fwrite(&aux->jogador, sizeof(int), 1, f);
        fwrite(&aux->numJogada, sizeof(int), 1, f);
        fwrite(&aux->nMiniTab, sizeof(int), 1, f);
        fwrite(&aux->linha, sizeof(int), 1, f);
        fwrite(&aux->coluna, sizeof(int), 1, f);

        aux = aux->prox;
    }
    fclose(f);

    printf("\n\nO jogo foi guardado com sucesso! Volte mais tarde para continuar\n\n");

    exit(0);
}

void retomaJogo(){

    FILE *f;
    pjogada p = NULL;
    int numJogada, tipoJogo;
    char ***mat;
    int jogadorAtual;
    jogador j[2];
    pjogada aux;

    f = fopen("jogo.bin", "rb");
    if(f == NULL){
        printf("Erro ao aceder ao ficheiro!\n");
        return;
    }

    fread(&tipoJogo, sizeof(int), 1, f);
    fread(&numJogada, sizeof(int), 1, f);     //numero da jogada atual
    fread(&jogadorAtual, sizeof(int), 1, f);

    for (int k = 0; k < 2; ++k) {
        fread(&j[k], sizeof(jogador), 1, f);
    }

// Ler tabuleiro do ficheiro
/*
    mat = malloc(sizeof(char**)*9);
    if(mat == NULL)
        exit(1);

    for (int k = 0; k < 9; ++k) {
        mat[k] = malloc(sizeof(char*)*3);
        if(mat[k] == NULL) {
            libertaTab(mat, 0, k - 1);
            exit(1);
        }
        for (int l = 0; l < 3; ++l) {
            mat[k][l] = malloc(sizeof(char)*3);
            if(mat[k][l] == NULL){
                libertaTab(mat, l-1, k-1);
                exit(1);
            }
            for (int m = 0; m < 3; ++m) {
                fread(&mat[k][l][m], sizeof(char), 1, f);
            }
        }
    }
*/

    // Cria o tabuleiro vazio
    mat = criaTab(3, 3, 9);

    for(int i=0; i < numJogada - 1; i++){
        aux = malloc(sizeof(jogada));
        if(aux == NULL){
            exit(1);
        }
        fread(&aux->jogador,sizeof(int), 1, f);
        fread(&aux->numJogada, sizeof(int), 1, f);
        fread(&aux->nMiniTab, sizeof(int), 1, f);
        fread(&aux->linha, sizeof(int), 1, f);
        fread(&aux->coluna, sizeof(int), 1, f);

        p = adicionaJogada(p, aux->nMiniTab, aux->linha, aux->coluna, aux->jogador, aux->numJogada);

        // Adiciona jogada segundo o histórico de jogadas
        setPos(mat, aux->nMiniTab-1, aux->linha-1, aux->coluna-1, j[aux->jogador-1].peca);
    }
    fclose(f);

    iniciaJogo(tipoJogo, p, numJogada, mat, jogadorAtual, j);
}