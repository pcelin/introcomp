#define MAX 200

#include <stdio.h>

void zere_tabuleiro(int tabuleiro[MAX][MAX], int nlin, int ncol){
    int i;
    int j;

    for (i = 0; i < nlin; i++)
        for (j = 0; j < ncol; j++)
            tabuleiro[i][j] = 0;
}



void copie_matriz(int origem[MAX][MAX], int destino[MAX][MAX],int nlin, int ncol){
}


void imprima_tabuleiro(int tabuleiro[][MAX], int nlin, int ncol) {
    int i , j;
 
    for (i = 0; i < nlin; i++) {
        for (j = 0; j < ncol; j++)
            printf("%3d", tabuleiro[i][j]);
        printf("\n");
    }
}


void leia_configuracao_inicial(int tabuleiro[MAX][MAX], int *nlin, int *ncol){
    int i, j, tantodeareia;
        
    scanf("%d %d", nlin, ncol);
    /*printf("%d %d\n", *nlin, *ncol);*/
    zere_tabuleiro(tabuleiro, *nlin + 2, *ncol + 2);
    /*imprima_tabuleiro(tabuleiro, *nlin+2, *ncol+2);*/
    scanf("%d %d %d", &i, &j, &tantodeareia);
    tabuleiro[i + 1][j + 1] = tantodeareia;
    while(i >= 0) {
        /*printf ("%d %d %d\n", i, j, tantodeareia);*/
        tabuleiro[i + 1][j + 1] = tantodeareia;
        scanf("%d %d %d", &i, &j, &tantodeareia);
   }

}

int espalhe(int tabuleiro[MAX][MAX], int ativacao[MAX][MAX], int nlin, int ncol, int instante, int *novosativados){
    int i;
    int j;
    int copia[MAX][MAX];
 
    for(i = 0; i < nlin; i++)
        for(j = 0; j < ncol; j++)
            copia[i][j] = tabuleiro[i][j];

    for(i = 0; i < nlin; i++)
        for(j = 0; j < ncol; j++){
            /*canto superior esquerdo*/
            if (i == 0 && j == 0){
                if (copia[i][j] >= 2 ){
                    tabuleiro[i][j] -= 2;
                    tabuleiro[i+1][j] += 1;
                    tabuleiro[i][j+1] += 1;
                }            
            }    
            /*canto superior direito*/
            if (i == 0 && j == ncol - 1){
               if (copia[i][j] >= 2 ){
                    tabuleiro[i][j] -= 2;
                    tabuleiro[i+1][j] += 1;
                    tabuleiro[i][j-1] += 1;
               }
            }
            /*canto inferior esquerdo*/
            if (i == nlin - 1 && j == 0){
               if (copia[i][j] >= 2 ){
                    tabuleiro[i][j] -= 2;
                    tabuleiro[i-1][j] += 1;
                    tabuleiro[i][j+1] += 1;
               }
            }
            /*canto inferior direito*/
            if (i == nlin - 1 && j == ncol - 1){
               if (copia[i][j] >= 2 ){
                    tabuleiro[i][j] -= 2;
                    tabuleiro[i-1][j] += 1;
                    tabuleiro[i][j-1] += 1;
               }
            }
            /*borda da esquerda*/
            if (0 < i < nlin-1 && j == 0){
               if (copia[i][j] >= 3 ){
                    tabuleiro[i][j] -= 3;
                    tabuleiro[i-1][j] += 1;
                    tabuleiro[i+1][j] += 1;
                    tabuleiro[i][j+1] += 1;
               }
            }
            /*borda da direita*/
            if (0 < i < nlin-1 && j == ncol - 1){
               if (copia[i][j] >= 3 ){
                    tabuleiro[i][j] -= 3;
                    tabuleiro[i-1][j] += 1;
                    tabuleiro[i+1][j] += 1;
                    tabuleiro[i][j-1] += 1;
               }
            }
            /*borda superior*/
            if (i = 0 && 0 < j < ncol - 1){
               if (copia[i][j] >= 3 ){
                    tabuleiro[i][j] -= 3;
                    tabuleiro[i][j-1] += 1;
                    tabuleiro[i+1][j] += 1;
                    tabuleiro[i][j+1] += 1;
               }
            }
            /*borda inferior*/
            if (i = nlin - 1 && 0 < j < ncol - 1){
               if (copia[i][j] >= 3 ){
                    tabuleiro[i][j] -= 3;
                    tabuleiro[i][j+1] += 1;
                    tabuleiro[i][j-1] += 1;
                    tabuleiro[i-1][j] += 1;
               }
            }
            /*meio*/
            if (0 < i < nlin - 1 && 0 < j < ncol - 1){
               if (copia[i][j] >= 4 ){
                    tabuleiro[i][j] -= 4;
                    tabuleiro[i-1][j] += 1;
                    tabuleiro[i+1][j] += 1;
                    tabuleiro[i][j-1] += 1;
                    tabuleiro[i][j+1] += 1;
               }
            }
        }
}

int main() {
    int matriz[MAX][MAX];
    int ativacao[MAX][MAX];
    int i, j, nlin, ncol;
    int novosativados = 0;
    
    leia_configuracao_inicial(matriz, &nlin, &ncol);
    printf("\n"); 
    imprima_tabuleiro(matriz, nlin + 2, ncol + 2);
    printf("\n");
       

    for (i = 0; i < nlin ; i++){
        for (j = 0; j < ncol; j++){
            ativacao[i][j] = -1;
            printf("%3d", ativacao[i][j]);
        }
            printf("\n");
    }



    return 0;
}
