#include <stdio.h>

#include "jogo.h"
#include "utils.h"
#include "menus.h"
#include "tabuleiro.h"
#include "interromperJogo.h"


void iniciaJogo(int tipoJogo, pjogada p, int numJogada, char ***mat, int jogadorAtual, jogador j[2]){

    initRandom();

    int opcao;
    int continua = 1;
    int miniTabVencedor[3][3] = {{0,0,0,}, {0,0,0},{0,0,0}};


    do{
            //se for um jogo contra o computador e for a vez do computador (jogador 1) jogar
        if(tipoJogo == 1 && jogadorAtual == 1){

            //escolhe mini tabuleiro, linha e coluna aleatoriamente
            int nMiniTab = escolheMiniTab(p, 1);
            int linha = intUniformRnd(1, 3);
            int coluna = intUniformRnd(1, 3);

            //se a jogada estiver de acordo com as verificações, escreve a peça respetiva ao jogador
            if(verificaJogada(mat,nMiniTab,&linha,&coluna)) {
                setPos(mat, nMiniTab, linha, coluna, j[jogadorAtual].peca);
                p = adicionaJogada(p,nMiniTab+1,linha+1,coluna+1,j[jogadorAtual].numJogador,numJogada);
                verificaVitoriaMini(mat,nMiniTab,j[jogadorAtual], miniTabVencedor);
                if (verificaVitoriaMini(mat, nMiniTab, j[jogadorAtual], miniTabVencedor)) {
                    // Aqui você pode chamar a função de verificação de vitória final
                    int vencedorFinal = verificaVitoriaFinal(miniTabVencedor);
                    if (vencedorFinal != 0) {
                        printf("O jogador %d ganhou o jogo completo!\n", vencedorFinal);
                        continua = 0; // Finaliza o jogo
                    }
                }
                //faz a alternancia de jogadores e passa para o 2
                jogadorAtual = (jogadorAtual + 1) % 2;

                //incrementa o numero de jogadas
                numJogada++;
            }
        }
        //se for o jogador 2 a começar ou se for um jogo entre dois jogadores
        printf("\n----------------------------------------\n");
        printf("Jogada %d\n\n", numJogada);
        printf("Jogador %d\n\n", j[jogadorAtual].numJogador);
        mostraTabuleiro(mat,3,3,9);
        printf("\n");

        //apresenta um menu
        menuJogo();

        do{
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
        } while(opcao<1 || opcao>4);

        switch (opcao) {
            case 1:
                if(fazJogada(&p, mat, j[jogadorAtual], numJogada, miniTabVencedor)) {
                    jogadorAtual = (jogadorAtual + 1) % 2;
                    numJogada++;
                }
                break;
            case 2:
                interrompeJogo(tipoJogo, p,numJogada,mat,jogadorAtual,j);
                break;
            case 3:
                mostraJogadasAnteriores(p, numJogada);
                break;
            default:
                continua = 0;
                break;
        }

    }while(continua);
}

int escolheMiniTab(pjogada p, int aleatorio) {

    int linha, coluna, nMiniTab;

    //se a lista estiver vazia (é a primeira jogada)
    if(p == NULL){
        //se estiver contra o computador e for a vez dele, escolhe um mini tabuleiro aeatoriamente
        if(aleatorio){
            nMiniTab = intUniformRnd(1, 9);
        }else{
            printf("Escolha o mini tabuleiro: ");
            scanf("%d", &nMiniTab);
        }
        return nMiniTab-1;
    }
    //se não for a primeira jogada, procura as coordenadas da ultima jogada feita, para indicar ao jogador em que mini tabuleiro deve jogar
    else{
        pjogada ultima = procuraJogadaAnterior(p);
        linha = ultima->linha-1;
        coluna = ultima->coluna-1;
    }

    //indica o mini tabuleiro a partir das coordenadas
    p->nMiniTab = linha*3+coluna;

    return p->nMiniTab;
}

//pede ao jogador a linha e a coluna do mini tabuleiro
void pedeCoordenadas(int* linha, int* coluna){

    do {
        printf("Linha: ");
        scanf("%d", linha);
    } while(*linha<1 || *linha>3);

    do {
        printf("Coluna: ");
        scanf("%d", coluna);
    } while((*coluna)<1 || (*coluna)>3);
}

int fazJogada(pjogada *p, char ***mat, jogador j, int numJogada, int vencedores[3][3]){

    int linha, coluna;
    int nMiniTab = escolheMiniTab(*p, 0);

    //verifica se o mini tabuleiro está terminado; se sim, apresenta mensagem e manda o jogador jogar no mesmo que o jogador anterior
    if(verificaVitoriaMini(mat,nMiniTab,j, vencedores)) {
        printf("Este mini tabuleiro foi bloqueado! Vai jogar no mesmo!\n\n");
        nMiniTab = procuraJogadaAnterior(*p)->nMiniTab - 1;
    }

    pedeCoordenadas(&linha, &coluna);

    //se estiver tudo de acordo com as verificações, escreve a peça do jogador atual no tabuleiro e adiciona a jogada à lista
    if(verificaJogada(mat,nMiniTab,&linha,&coluna)) {

        setPos(mat, nMiniTab, linha, coluna, j.peca);
        *p = adicionaJogada(*p,nMiniTab+1,linha+1,coluna+1,j.numJogador,numJogada);
        verificaVitoriaMini(mat,nMiniTab,j, vencedores);
        return 1;
    }
    return 0;
}

int verificaJogada(char ***mat, int nMiniTab,int *linha, int *coluna){

    *linha = *linha - 1;
    *coluna = *coluna - 1;

    if(mat[nMiniTab][*linha][*coluna] != '_'){
       return 0;
    }
    return 1;
}

//verifica se o mini tabuleiro tem uma linha feita
int verificaLinhasMini(char ***mat, int nMiniTab){
    int i, j, cont;

    for(i=0; i<3; i++){
        cont = 0;
        for(j=0; j<3; j++) {
            if(mat[nMiniTab][i][j] == '_')
                break;
            if (mat[nMiniTab][i][j] == mat[nMiniTab][i][0])
                cont++;
        }
        if(cont==3)
            return 1;

    }
    return 0;
}

//verifica se o mini tabuleiro tem uma coluna feita
int verificaColunasMini(char ***mat, int nMiniTab){
    int i, j, cont;

    for(j=0; j<3; j++){
        cont = 0;
        for(i=0; i<3; i++) {
            if(mat[nMiniTab][i][j] == '_')
                break;
            if (mat[nMiniTab][i][j] == mat[nMiniTab][0][j])
                cont++;
        }
        if(cont==3)
            return 1;

    }
    return 0;
}

//verifica se o mini tabuleiro tem uma diagonal feita
int verificaDiagonaisMini(char ***mat, int nMiniTab){
    int i, j;

    int cont = 0;

    for (i = 0; i < 3; i++) {
        if (mat[nMiniTab][i][i] == '_')
            break;
        if (mat[nMiniTab][i][i] == mat[nMiniTab][0][0])
            cont++;
    }

    if(cont==3)
        return 1;

    cont = 0;

    for (i = 0, j=2; i < 3; i++, j--) {
        if (mat[nMiniTab][i][j] == '_')
            break;
        if (mat[nMiniTab][i][j] == mat[nMiniTab][0][2])
            cont++;
    }

    if(cont==3)
        return 1;
    return 0;
}

int verificaVitoriaMini(char ***mat, int nMiniTab, jogador j, int vencedores[3][3]){

    if(verificaLinhasMini(mat, nMiniTab)) {
        printf("O jogador %d ganhou a linha do mini tabuleiro %d\n\n", j.numJogador, nMiniTab+1);
        vencedores[nMiniTab / 3][nMiniTab % 3] = j.numJogador;
        return 1;
    }
    if(verificaColunasMini(mat, nMiniTab)) {
        printf("O jogador %d ganhou a coluna do mini tabuleiro %d\n\n", j.numJogador, nMiniTab+1);
        vencedores[nMiniTab / 3][nMiniTab % 3] = j.numJogador;
        return 1;
    }
    if(verificaDiagonaisMini(mat, nMiniTab)) {
        printf("O jogador %d ganhou a diagonal do mini tabuleiro %d\n\n", j.numJogador, nMiniTab+1);
        vencedores[nMiniTab / 3][nMiniTab % 3] = j.numJogador;
        return 1;
    }

    return 0;
}

void mostraJogadasAnteriores(pjogada p, int numJogada){
    int k;

    do{
        printf("\nIndique as K jogadas anteriores que quer visualizar: ");
        scanf("%d", &k);
    }while(k<1 || k>10 || k > numJogada-1);

    mostraJogadaKJogadasAnteriores(p, k);
}

int verificaVitoriaFinal(int vencedores[3][3]) {
    // Verifica linhas
    for (int i = 0; i < 3; i++) {
        if (vencedores[i][0] != 0 && vencedores[i][0] == vencedores[i][1] && vencedores[i][1] == vencedores[i][2]) {
            return vencedores[i][0];
        }
    }

    // Verifica colunas
    for (int j = 0; j < 3; j++) {
        if (vencedores[0][j] != 0 && vencedores[0][j] == vencedores[1][j] && vencedores[1][j] == vencedores[2][j]) {
            return vencedores[0][j];
        }
    }

    // Verifica diagonais
    if (vencedores[0][0] != 0 && vencedores[0][0] == vencedores[1][1] && vencedores[1][1] == vencedores[2][2]) {
        return vencedores[0][0];
    }
    if (vencedores[0][2] != 0 && vencedores[0][2] == vencedores[1][1] && vencedores[1][1] == vencedores[2][0]) {
        return vencedores[0][2];
    }

    return 0;
}
