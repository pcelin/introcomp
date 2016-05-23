#include <stdio.h>

#define EPSILON 1e-14
#define PI 3.14159265358979323846

/* DEFINES DA PROFESSORA */

/* Outros parametros relativos `a codificacao de audio */
#define NUM_BITS 16
#define NUM_CANAIS 2
/* A maior amplitude representavel e' 2^(NUM_BITS-1)-1 */
#define MAX_AMPLITUDE 32767

/* O deslocamento é usado para mapear valores negativos
 * no intervalo 2^(NUM_BITS-1)...2^NUM_BITS-1
 * (representação usando complemento de 2)
 */
#define DESLOCAMENTO 65536

/* Taxa de amostragem na codificacao do audio: voce pode usa-lo no seu programa se quiser! */
#define TAXA_AMOSTRAGEM 44100

/* FIM DEFINES DA PROFESSORA */


/* PROTÓTIPOS DA PROFESSORA */

/* Função escreve_cabecalho_wav (saida_wav,numero_total_de_amostras)
 * Escreve um cabeçalho no arquivo saida_wav seguindo a especificação RIFF Wave
 * (http://sox.sourceforge.net/AudioFormats.html#ss11.6)
 * 
 * O único argumento é um inteiro contendo o número total de amostras.
 * O restante do cabeçalho usará parâmetros constantes, como codificação
 * PCM, taxa de amostragem de 44100 Hz, amostras inteiras de 16 bits
 * (com sinal usando complemento de 2), e 2 canais.
 *
 */
void escreve_cabecalho_wav(FILE *saida_wav, int numero_total_de_amostras);

/* Função escreve_amostra(saida_wav, amostra)
 * Converte a amostra (double entre -1 e 1) linearmente para o 
 * intervalo -32767 ... +32767, correspondente `a representacao
 * de inteiro em 16 bits, arredonda o resultado para um inteiro
 * e escreve no arquivo arqsaida o codigo (em formato little
 * endian) correspondente.
 *
 */
int escreve_amostra(FILE *saida_wav, double amostra);

/* FIM PROTÓTIPOS DA PROFESSORA */

double sen(double x);
double exp(double x);
double ln(double x);
double modulo(double x);

double modulo(double x) {
    if (x < 0) 
        return -x;
    else 
        return x;     
}

double sen(double x) {
    long double termo;
    long double soma;
    int sinal;
    int n;
    long double num, den;

    soma = 0;
    sinal = 1;
    num = x;   
    den = 1;
    n = 1;
    termo = EPSILON;
    while (modulo(termo) >= EPSILON) {
        
        termo = sinal * num/den;        
        num = num * x * x;
        den = den * (2*n) * (2*n + 1);
        soma += termo;    
        sinal = -sinal;
        n = n + 1;
    }
    
    return soma;

}

double exp(double x) {
    long double termo;
    long double soma;
    int n;
    long double num, den;

    num = x;   
    den = 1;
    n = 1;
    soma = 0;
    
    termo = EPSILON;
    
    while (modulo(termo) >= EPSILON) {
        
        termo = num/den;
        num = num * x;
        den = den * (n + 1);
        soma = 1 + termo;
    }
   
    return soma;

}

double ln(double x) {
    return x;
}


double pot(double x, double y) {
    return exp(y*ln(x));
}

double F(int altura_mus) {
    return 27.5 * pot(2, altura_mus/12.0);
}

double A(double volume) {
    return pot(2, 10*volume - 10);
}

int main() {
    char nomesaida[60];
    FILE *arq_saida;
    double duracao;
    double soma_duracao;
    double cur_dur, cur_amp;
    int cur_altura;


    printf("Exp 40=%lf\n", exp(3.5));

    scanf("%s", nomesaida);
    printf("nomesaida: %s\n", nomesaida); 
    
    scanf("%lf", &duracao);
    printf("duracao: %lf\n", duracao);
    
    arq_saida = fopen(nomesaida, "wb");
    
    soma_duracao = 0;
    while (soma_duracao < duracao) {
        scanf("%lf %d %lf\n", &cur_dur, &cur_altura, &cur_amp);
        soma_duracao += cur_dur;
        printf("Lido: %lf, %d, %lf\n", cur_dur, cur_altura, cur_amp);
    }

    fprintf(arq_saida, "Oi, Marcelo!\n");
    fclose(arq_saida);

    return 0;
}

/*************** Não mexer a partir desta linha ------------------------------*/

/* Função fwrite_little_endian(arqsaida,valor,nbytes)
 * Escreve um valor (inteiro positivo) no arquivo arqsaida
 * usando a codificacao little endian ocupando nbytes.
 *
 * Little endian se refere à ordem como os bytes que
 * representam um número inteiro são dispostos num
 * arquivo ou na memória: primeiro vem o byte menos
 * significativo, depois o segundo byte menos significativo,
 * e assim por diante.
 *
 */
void fwrite_little_endian(FILE *arqsaida, int valor, int nbytes)
{
  int i;

  for (i=0;i<nbytes;i++) {
    fprintf(arqsaida,"%c",valor%256);
    valor = valor/256;
  }

  return;
}



/* Escreve o cabecalho de um arquivo RIFF/WAVE a partir das
 * informacoes R=taxa de amostragem, B=numero de bits por
 * amostra e C=numero de canais, alem do numero de amostras
 * total.
 *
 */

void escreve_cabecalho_wav_completo(FILE *arqsaida, int R, int B, int C,
                                    int num_amostras_total)
{
  int tam_bloco_amostras; /* numero total de bytes do bloco de amostras */

  /* cada amostra ocupa (B/8) bytes e cada canal possui uma amostra independente */
  tam_bloco_amostras=num_amostras_total*C*(B/8);

  fprintf(arqsaida,"RIFF");                               /* identificador do bloco RIFF */
  fwrite_little_endian(arqsaida,tam_bloco_amostras+36,4); /* tamanho do bloco RIFF */
  fprintf(arqsaida,"WAVEfmt ");                           /* identificador dos blocos WAVE e de formato */
  fwrite_little_endian(arqsaida,16,4);                    /* tamanho do bloco de formato */
  fwrite_little_endian(arqsaida,1,2);                     /* esquema de codificacao das amostras (1=PCM) */
  fwrite_little_endian(arqsaida,C,2);                     /* numero de canais */
  fwrite_little_endian(arqsaida,R,4);                     /* frequencia de amostragem */
  fwrite_little_endian(arqsaida,R*C*(B/8),4);             /* numero de bytes por segundo */
  fwrite_little_endian(arqsaida,C*(B/8),2);               /* numero de bytes por amostra */
  fwrite_little_endian(arqsaida,B,2);                     /* numero de bits por amostra */
  fprintf(arqsaida,"data");                               /* identificador do bloco de amostras */
  fwrite_little_endian(arqsaida,tam_bloco_amostras,4);    /* num. de bytes das amostras */

  return;

}



/* Função escreve_cabecalho_wav (saida_wav, numero_total_de_amostras) 
 * Encapsula a chamada da função escreve_cabecalho_wav_completo
 * complementando os parâmetros de codificação de áudio fixados
 * pelo enunciado.
 */

void escreve_cabecalho_wav (FILE *saida_wav, int numero_total_de_amostras) 
{
    escreve_cabecalho_wav_completo (saida_wav, TAXA_AMOSTRAGEM, NUM_BITS, NUM_CANAIS, 
                                    numero_total_de_amostras);
}



/* Função escreve_amostra(saida_wav, amostra)
 * Converte a amostra (double entre -1 e 1) linearmente para o 
 * intervalo -32767 ... +32767, correspondente `a representacao
 * de inteiro em 16 bits, arredonda o resultado para um inteiro
 * e escreve no arquivo arqsaida o codigo (em formato little
 * endian) correspondente.
 *
 */

int escreve_amostra(FILE *saida_wav, double amostra)
{

  int iamostra,     /* armazena o valor inteiro da amostra       */
    codigo;         /* codigo escrito por fwrite_little_endian() */

  /* converte linearmente para o intervalo -MAX_AMPLITUDE...+MAX_AMPLITUDE */
  amostra = amostra*MAX_AMPLITUDE;

  /* corrige valores fora do intervalo (por robustez, contra amostras inválidas) */
  if (amostra>MAX_AMPLITUDE)
    amostra = MAX_AMPLITUDE;
  if (amostra<-MAX_AMPLITUDE)
    amostra = -MAX_AMPLITUDE;

  /* arredonda valor da amostra */
  iamostra = (amostra>=0)? amostra+0.5 : amostra-0.5;

  /* a codificacao usa somente valores positivos,
     os valores negativos são espelhados no intervalo 
     MAX_AMPLITUDE...DESLOCAMENTO (complemento de 2) */
  codigo = (iamostra>=0)? iamostra : iamostra+DESLOCAMENTO;

  /* escreve o codigo correspondente usando NUM_BITS/8 bytes/amostra */
  fwrite_little_endian(saida_wav, codigo, NUM_BITS/8);

  return iamostra;

}
