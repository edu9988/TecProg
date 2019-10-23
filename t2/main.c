#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define G 6.67e-11

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
    double massa;
}objeto;

typedef struct {
    char *nome;
    objeto valor;
}nave;

typedef struct {
    objeto valor;
}projetil;

typedef struct {
    double raio;
    objeto valor;
}planeta;

void draw(nave *nave1, nave *nave2, planeta planeta1);
void addVetorAB(vetor *a, vetor b);
double normaVetor(vetor A);
void versorVetor(vetor *rVetor, vetor A, vetor B);
void printVetor(vetor A);
void distanciaAB(vetor *V, vetor A, vetor B);
void carregarArquivos(nave *nave1, nave *nave2, planeta *planeta, projetil *projetilX);
void *mallocSafe(int nbytes);
void string_copy(char *a, char *b);
void aceleracao(objeto *A, objeto B);

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

    nave1.valor.posObj.x = 6000000;
    nave1.valor.posObj.y = 6000000;
    nave1.valor.velObj.x = 0;
    nave1.valor.velObj.y = 0;

    for(i=0; i<1000; i++)
        draw(&nave1, &nave2, planeta1);

    return 0;
}

void draw(nave *nave1, nave *nave2, planeta planeta1)
{
    aceleracao(&nave1->valor, planeta1.valor);

    addVetorAB(&nave1->valor.posObj, nave1->valor.velObj);
    //printVetor(nave1->valor.velObj);
    //addVetorAB(&nave2->valor.velObj, );



    printVetor(nave1->valor.posObj);
    printf("\n");
}

void addVetorAB(vetor *A, vetor B){
    A->x = A->x + B.x;
    A->y = A->y + B.y;
}

double normaVetor(vetor A){
    return (sqrt(A.x * A.x + A.y * A.y));
}

void versorVetor(vetor *rVetor, vetor A, vetor B){
    double norma = normaVetor(A);

    distanciaAB(rVetor, B, A);
    rVetor->x = rVetor->x/norma;
    rVetor->y = rVetor->y/norma;
}

void printVetor(vetor A)
{
    printf("%.2lf %.2lf", A.x, A.y);
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

    fscanf(arquivoDeEntrada, "%le %le %lf", &planeta->raio, &planeta->valor.massa, &tempoSimulacao);

    fscanf(arquivoDeEntrada, "%s %lf %lf %lf %lf %lf", auxiliar, &nave1->valor.massa, &nave1->valor.posObj.x,
            &nave1->valor.posObj.y, &nave1->valor.velObj.x, &nave1->valor.velObj.y);

    nave1->nome = mallocSafe((1+strlen(auxiliar))*sizeof(char));
    string_copy(auxiliar , nave1->nome);


    fscanf(arquivoDeEntrada, "%s %lf %lf %lf %lf %lf", auxiliar, &nave2->valor.massa,
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

void aceleracao(objeto *A, objeto B){
    vetor rVetor;
    vetor distancia;
    versorVetor(&rVetor, A->posObj, B.posObj);
    distanciaAB(&distancia, A->posObj, B.posObj);

    if(distancia.x == 0 || distancia.y == 0){
        distancia.y = 10;
        distancia.x = 10;
    }

    A->velObj.x += G*(rVetor.x)*(B.massa)/(distancia.x * distancia.x);
    A->velObj.y += G*(rVetor.y)*(B.massa)/(distancia.y * distancia.y);

    //printVetor(rVetor);

}
