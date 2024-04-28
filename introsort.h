#include <windows.h>

typedef struct dados{
    long long int comp[5][4];
    int troca[5][4];
    long long int mediaCmp[5];
    int mediaTrc[5];
} tdados;


void selection(int *vet, int tam, tdados *dados, int j);

void insertion(int *vet, int tam, tdados *dados, int j);

void mergeSort(int *vet, int inicio, int fim, tdados *dados, int j);

void merge(int *vet, int inicio, int meio, int fim, tdados *dados, int j);

void quickSort(int *vet, int inicio, int fim, tdados *dados, int j);

int particiona(int *vet, int inicio, int fim, tdados *dados, int j);

void heapSort(int *vet, int tam, tdados *dados, int j);

void criaHeap(int *vet, int ini, int fim, tdados *dados, int j);

void insertionIntro(int* vet, int ini, int fim, tdados *dados, int j);

void introSort(int *vet, int ini, int fim, int prof_max, tdados *dados, int j);

int* geraAleatorios(int tam, int semente);

int* geraQuaseOrdenados(int tam, int porcentagem);

int* geraOrdenados(int tam, int ordem);

double calculaTempo(LARGE_INTEGER t_ini, LARGE_INTEGER t_fim, LARGE_INTEGER freq);

double calculaMedia(const double tempo[]);

int calculaMediaTroca(tdados *dados);

long long int calculaMediaComp(tdados *dados);

void iniciaVetor(tdados *dados);

int menu();

void imprimeCabTempo(int op);

void imprimeCabComp();

void imprimeCabTroca();

void imprimeTempos(int teste, double t_alt, double t_cres, double t_decres, double t_qse_ord, int tam);

void imprimeComps(tdados dados, int tam);

void imprimeTrocas(tdados dados, int tam);

#ifndef TRABALHO_INTROSORT_H
#define TRABALHO_INTROSORT_H

#endif //TRABALHO_INTROSORT_H
