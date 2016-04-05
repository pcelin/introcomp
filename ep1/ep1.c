#include <stdio.h>

int main() {

    int tabuleiro;
    int a9;
    int a8;
    int a7;
    int a6;
    int a5;
    int a4;
    int a3;
    int a2;
    int a1;
    int ganhou1=0;
    int ganhou2=0;
    int jogada=0;
    int jog=1;
    int curjog=0;
    int i;
    int aux;
    int aux2;
    printf("Jogo da Velha Dancarina\n");
    printf("Tabuleiro inicial: ");
    scanf("%d", &tabuleiro);

    a9=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a8=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a7=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a6=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a5=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a4=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a3=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a2=tabuleiro%10;
    tabuleiro=tabuleiro/10;
    a1=tabuleiro%10;
    tabuleiro=tabuleiro/10;

    printf("%d|%d|%d\n",a1,a2,a3);
    printf("-+-+-\n");
    printf("%d|%d|%d\n",a4,a5,a6);
    printf("-+-+-\n");
    printf("%d|%d|%d\n",a7,a8,a9);
    
    if (a1!=0&&a2!=0&&a3!=0&&a4!=0&&a5!=0&&a6!=0&&a7!=0&&a8!=0&&a9!=0){
        printf("O jogo terminou empatado\n");
    }
    else { 
        while (ganhou1==0&&ganhou2==0) {
            printf("(Jogador %d) Proxima jogada: ", jog);
            scanf("%d", &jogada);
            curjog=jog;
            if (jog==1) jog=2;
            else jog=1;

            if (jogada==11&&a1!=0) printf("Perdeu a vez!\n");
            if (jogada==11&&a1==0) a1=curjog;
            if (jogada==12&&a2!=0) printf("Perdeu a vez!\n"); 
            if (jogada==12&&a2==0) a2=curjog;
            if (jogada==13&&a3!=0) printf("Perdeu a vez!\n");
            if (jogada==13&&a3==0) a3=curjog;
            if (jogada==21&&a4!=0) printf("Perdeu a vez!\n"); 
            if (jogada==21&&a4==0) a4=curjog;
            if (jogada==22&&a5!=0) printf("Perdeu a vez!\n");
            if (jogada==22&&a5==0) a5=curjog;
            if (jogada==23&&a6!=0) printf("Perdeu a vez!\n"); 
            if (jogada==23&&a6==0) a6=curjog;
            if (jogada==31&&a7!=0) printf("Perdeu a vez!\n");
            if (jogada==31&&a7==0) a7=curjog;
            if (jogada==32&&a8!=0) printf("Perdeu a vez!\n"); 
            if (jogada==32&&a8==0) a8=curjog;
            if (jogada==33&&a9!=0) printf("Perdeu a vez!\n");
            if (jogada==33&&a9==0) a9=curjog;
           
            if (1<=jogada&&jogada<=9) {
                for (i=0;i<jogada;i++) {               
                    aux=a1;
                    a1=a9;
                    a9=a8;
                    a8=a7;
                    a7=a6;
                    a6=a5;
                    a5=a4;
                    a4=a3;
                    a3=a2;
                    a2=aux;                
                }            
            }
            if (jogada==0) {
                aux2=a1;
                a1=a4;
                a4=a7;
                a7=a8;
                a8=a9;
                a9=a6;
                a6=a3;
                a3=a2;
                a2=aux2;      
            }    

            printf("%d|%d|%d\n",a1,a2,a3);
            printf("-+-+-\n");
            printf("%d|%d|%d\n",a4,a5,a6);
            printf("-+-+-\n");
            printf("%d|%d|%d\n",a7,a8,a9);

            if (a1==a2&&a2==a3&&a3==1) {
                printf("O jogador 1 completou a 1a linha!\n");           
                ganhou1=1;
            }
            if (a1==a4&&a4==a7&&a7==1) {
                printf("O jogador 1 completou a 1a coluna!\n");
                ganhou1=1;
            }
            if (a4==a5&&a5==a6&&a6==1) {
                printf("O jogador 1 completou a 2a linha!\n");
                ganhou1=1;
            }
            if (a2==a5&&a5==a8&&a8==1) {
                printf("O jogador 1 completou a 2a coluna!\n");
                ganhou1=1;
            }
            if (a7==a8&&a8==a9&&a9==curjog) {
                printf("O jogador 1 completou a 3a linha!\n");
                ganhou1=1;
            }
            if (a3==a6&&a6==a9&&a9==curjog) {
                printf("O jogador 1 completou a 3a coluna!\n");
                ganhou1=1;
            }
            if (a1==a5&&a5==a9&&a9==curjog) {
                printf("O jogador 1 completou a diagonal principal!\n");
                ganhou1=1;
            }
            if (a3==a5&&a5==a7&&a7==curjog) {
                printf("O jogador 1 completou a diagonal secundaria!\n");
                ganhou1=1;
            }                    
            if (a1==a2&&a2==a3&&a3==2) {
                printf("O jogador 2 completou a 1a linha!\n");           
                ganhou2=1;
            }
            if (a1==a4&&a4==a7&&a7==2) {
                printf("O jogador 2 completou a 1a coluna!\n");
                ganhou2=1;
            }
            if (a4==a5&&a5==a6&&a6==2) {
                printf("O jogador 2 completou a 2a linha!\n");
                ganhou2=1;
            }
            if (a2==a5&&a5==a8&&a8==2) {
                printf("O jogador 2 completou a 2a coluna!\n");
                ganhou2=1;
            }
            if (a7==a8&&a8==a9&&a9==2) {
                printf("O jogador 2 completou a 3a linha!\n");
                ganhou2=1;
            }
            if (a3==a6&&a6==a9&&a9==2) {
                printf("O jogador 2 completou a 3a coluna!\n");
                ganhou2=1;
            }
            if (a1==a5&&a5==a9&&a9==2) {
                printf("O jogador 2 completou a diagonal principal!\n");
                ganhou2=1;
            }
            if (a3==a5&&a5==a7&&a7==2) {
                printf("O jogador 2 completou a diagonal secundaria!\n");
                ganhou2=1;
            }                    
        
            if (ganhou1==1&&ganhou2==1) printf ("Os dois ganharam!\n");
        
        }           
    }
    return 0;
}

