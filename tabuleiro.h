
#ifndef TRABALHOPRATICO1_TABULEIRO_H
#define TRABALHOPRATICO1_TABULEIRO_H

#include <stdio.h>
#include <stdlib.h>

void libertaTab(char*** p, int nlin, int nMiniTabs);
char*** criaTab(int nLin, int nCol, int nMiniTabs);
void mostraTabuleiro(char*** mat, int nLin, int nCol, int nMinis );
void setPos(char ***p, int miniTab, int x, int y, char c);
char getPos(char ***p, int miniTab, int x, int y);

#endif //TRABALHOPRATICO1_TABULEIRO_H
