#define MAX 200

#include <stdio.h>

void zere_tabuleiro(int tabuleiro[MAX][MAX], int nlin, int ncol){
    int i;
    int j;

    for (i = 0; i < nlin; i++)
        for (j = 0; j < ncol; j++)
            tabuleiro[i][j] = 0;
}


void imprima_tabuleiro(int tabuleiro[][MAX], int nlin, int ncol) {
    int i , j;
 
    for (i = 0; i < nlin; i++) {
        for (j = 0; j < ncol; j++)
            printf("%2d", tabuleiro[i][j]);
        printf("\n");
    }
}

void leia_configuracao_inicial(int tabuleiro[MAX][MAX], int *nlin, int *ncol){
    int i, j, tantodeareia;
    scanf("%d %d", nlin, ncol);
    /*printf("%d %d\n", *nlin, *ncol);*/
    scanf("%d %d %d", &i, &j, &tantodeareia);
    tabuleiro[i][j] = tantodeareia;
    while(i >= 0) {
        /*printf ("%d %d %d\n", i, j, tantodeareia);*/
        tabuleiro[i][j] = tantodeareia;
        scanf("%d %d %d", &i, &j, &tantodeareia);
   }
imprima_tabuleiro(tabuleiro, *nlin, *ncol);
}

int main() {
    int matriz[MAX][MAX];

    int i, j, m, n, nlin, ncol;

    m = n = 3;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            matriz[i][j] = i + 2*j;
    
    imprima_tabuleiro(matriz, m, n);
    zere_tabuleiro(matriz, m, n);
    printf("\n");
    imprima_tabuleiro(matriz, m, n);
   
    leia_configuracao_inicial(matriz, &nlin, &ncol);   
    
    return 0;
}
