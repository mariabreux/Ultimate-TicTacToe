
#include "tabuleiro.h"

void libertaTab(char*** mat, int nLin, int nMiniTabs){

    int i, j;

    for(i=0; i<nMiniTabs; i++) {
        for (j = 0; j < nLin; j++)
            free(mat[i][j]);
        free(mat[i]);
    }
    free(mat);
}

char*** criaTab(int nLin, int nCol, int nMiniTabs){

    char ***mat = NULL;
    int miniTab, i, j;

    mat = malloc(sizeof(char**) * nMiniTabs);
    if(mat == NULL)
        return NULL;

    for(miniTab=0; miniTab<nMiniTabs; miniTab++){

        mat[miniTab] = malloc(sizeof(char*) * nLin);
        if(mat[miniTab] == NULL){
            libertaTab(mat, 0, miniTab - 1);
            return NULL;
        }
        for(i=0; i<nLin; i++){
            mat[miniTab][i] = malloc(sizeof(char) * nCol);

            if(mat[miniTab][i] == NULL){
                libertaTab(mat, i - 1, miniTab - 1);
                return NULL;
            }

            for(j=0; j<nCol; j++)
                mat[miniTab][i][j] = '_';
        }
    }

    return mat;
}

void mostraTabuleiro(char*** mat, int nLin, int nCol, int nMiniTabs) {
    int miniTab, l, c;

    for (int i=0; i <3; i++) {
        for (l=0; l<nLin; l++) {
            if (i == 0) {
                for (miniTab=0; miniTab<3; miniTab++) {
                    for (c=0; c<nCol; c++) {
                        printf(" %c ", mat[miniTab][l][c]);
                    }

                    if (miniTab !=2 )
                        printf(" | ");
                    else
                        printf("\n");
                }
            } else if (i == 1) {
                for (miniTab=3; miniTab<6; miniTab++) {
                    for (c=0; c<nCol; c++) {
                        printf(" %c ", mat[miniTab][l][c]);
                    }

                    if (miniTab != 5)
                        printf(" | ");
                    else
                        printf("\n");
                }
            } else {
                for (miniTab=6; miniTab<nMiniTabs; miniTab++) {
                    for (c=0; c<nCol; c++) {
                        printf(" %c ", mat[miniTab][l][c]);
                    }

                    if (miniTab != 8)
                        printf(" | ");
                    else
                        printf("\n");
                }
            }
        }

        if (i==0 || i==1)
            printf("---------------------------------\n");
    }

}

void setPos(char ***p, int miniTab, int x, int y, char c){
    p[miniTab][x][y] = c;
}
