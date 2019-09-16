#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double tempoSimulacao;
double massaPlaneta;
double raioPlaneta;
double tempoVidaProjeteis;

typedef struct{
    double x;
    double y;
}vetor;

typedef struct {
    vetor velObj;
    vetor posObj;
}objeto;

typedef struct {
    char *nome;
    double massa;
    objeto valor;
}nave;

typedef struct {
    objeto valor;
}projetil;

typedef struct {
    double massa;
    double raio;
    objeto valor;
}planeta;

void draw(nave *nave1, nave *nave2, planeta planeta1);
void addVetorAB(vetor *a, vetor b);
double normaVetor(vetor A);
void versorVetor(vetor *A);
void printVetor(vetor A);
void distanciaAB(vetor *V, vetor A, vetor B);
void carregarArquivos(nave *nave1, nave *nave2, planeta *planeta, projetil *projetilX);
void *mallocSafe(int nbytes);
void string_copy(char *a, char *b);

int main(int argc, char *argv[]){
    nave nave1;
    nave nave2;
    vetor velAux;
    vetor acelAux;
    planeta planeta1;
    projetil projetil1X;

    int i;

    planeta1.valor.posObj.x = 0;
    planeta1.valor.posObj.y = 0;


    carregarArquivos(&nave1, &nave2, &planeta1, &projetil1X);


    for(i=0; i<1000; i++)
        draw(&nave1, &nave2, planeta1);

    return 0;
}

void draw(nave *nave1, nave *nave2, planeta planeta1)
{

    addVetorAB(&nave1->valor.posObj, nave1->valor.velObj);
    addVetorAB(&nave2->valor.posObj, nave2->valor.velObj);

    printVetor(nave1->valor.posObj);
    printVetor(nave2->valor.posObj);
    printf("\n");
}

void addVetorAB(vetor *A, vetor B){
    A->x = A->x + B.x;
    A->y = A->y + B.y;
}

double normaVetor(vetor A){
    return (sqrt(A.x * A.x + A.y * A.y));
}

void versorVetor(vetor *A){
    double norma = normaVetor(*A);
    A->x = A->x/norma;
    A->y = A->y/norma;
}

void printVetor(vetor A)
{
    printf("%.2lf\t%.2lf\t", A.x, A.y);
}

void distanciaAB(vetor *V, vetor A, vetor B)
{
    V->x = (A.x - B.x);
    V->y = (A.y - B.y);
}

void carregarArquivos(nave *nave1, nave *nave2, planeta *planeta, projetil *projetilX)
{
    double quantidadeProjeteis;
    char auxiliar[80];

    FILE *arquivoDeEntrada;
    char nomeArquivo[80] = "arquivo.txt";

    arquivoDeEntrada = fopen(nomeArquivo, "r");
    if(!arquivoDeEntrada){
        printf("Error opening entry file\n");
        exit(EXIT_FAILURE);
    }

    //CONVERTER O NUMERO ANTES DE REGISTRAR, FSCANF NÃO MOSTRA ERROS

    fscanf(arquivoDeEntrada, "%le %le %lf", &planeta->raio, &planeta->massa, &tempoSimulacao);

    fscanf(arquivoDeEntrada, "%s %lf %lf %lf %lf %lf", auxiliar, &nave1->massa, &nave1->valor.posObj.x,
            &nave1->valor.posObj.y, &nave1->valor.velObj.x, &nave1->valor.velObj.y);

    printVetor(nave1->valor.posObj);

    nave1->nome = mallocSafe((1+strlen(auxiliar))*sizeof(char));
    string_copy(auxiliar , nave1->nome);


    fscanf(arquivoDeEntrada, "%s %lf %lf %lf %lf %lf", auxiliar, &nave2->massa,
           &nave2->valor.posObj.x, &nave2->valor.posObj.y, &nave2->valor.velObj.x, &nave2->valor.velObj.y);

    nave2->nome = mallocSafe((1+strlen(auxiliar))*sizeof(char));
    string_copy(auxiliar , nave2->nome);


    fscanf(arquivoDeEntrada, "%lf %lf", &quantidadeProjeteis, &tempoVidaProjeteis);

    //LOOPING PARA REGISTRAR OS PROJETEIS

    fclose(arquivoDeEntrada);
}

void *mallocSafe(int nbytes)
{
    void *pointer;
    pointer = malloc(nbytes);
    if( pointer == NULL ){
        printf("Malloc failed\n");
        exit(EXIT_FAILURE);
    }
    return pointer;
}

void string_copy(char *a, char *b)
{
    int i;
    for( i=0 ; i<strlen(a) ; i++ )
        b[i] = a[i];
    b[i] = '\0';
    return;
}