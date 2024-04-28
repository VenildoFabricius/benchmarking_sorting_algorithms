#include "introsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void selection(int* vet, int tam, tdados *dados, int j){
    // Implementa o algoritmo de ordenação Selection
    int marcador = 0, menor, aux, k;


    while(marcador < tam - 1){                  // Percorre cada elemento do vetor
        menor = marcador;
        for(k = marcador + 1; k < tam; k++){    // Verifica qual o menor elemento da parte desordenada (à direita)
            dados->mediaCmp[j]++;
            if(vet[k] < vet[menor]){
                menor = k;
            }
        }
        dados->mediaCmp[j]++;
        if(vet[menor] < vet[marcador]){         // Se o marcador for maior que o menor elemento
            aux = vet[marcador];                // Marcador troca de posição com o menor elemento
            vet[marcador] = vet[menor];
            vet[menor] = aux;
            dados->mediaTrc[j]++;
        }
        marcador ++;                            // Avança o marcador para a próxima comparação
    }
}

void insertion(int* vet, int tam, tdados *dados, int j){
    // Implementa o algoritmo de ordenação Insertion Sort
    int marcador, aux, pos;

    for(marcador = 1; marcador < tam; marcador++){      // Percorre cada elemento do vetor
        aux = vet[marcador];                            // Armazena o valor do elemento atual do vetor em "aux", para poder ser inserido na posição correta posteriormente.
        pos = marcador - 1;                             // Define a posição inicial da comparação para o elemento atual.
        dados->mediaCmp[j]++;
        while(pos >= 0 && aux < vet[pos]){              // Enquanto houver elementos a comparar e 'aux' for menor que o elemento atual
            dados->mediaCmp[j]++;
            vet[pos + 1] = vet[pos];                    // Move o elemento do vetor na posição "pos" para a próxima posição.
            pos --;                                     // Decrementa o marcador de posição
        }
        if(vet[pos + 1] != aux)
            dados->mediaTrc[j]++;
        vet[pos + 1] = aux;                             // Insere o valor "aux" na posição correta no vetor.
    }
}

void mergeSort(int *v, int inicio, int fim, tdados *dados, int j) {
    // Implementa o algoritmo de ordenação MergeSort
    int meio;

    if(inicio < fim){
        meio = (inicio + fim) / 2;
        mergeSort(v, inicio, meio, dados, j);
        mergeSort(v, meio + 1, fim, dados, j);
        merge(v, inicio, meio, fim, dados, j);
    }
}

void merge(int *v, int inicio, int meio, int fim, tdados *dados, int j) {
    // Ordena os vetores resultantes do particionamento feito pela função 'merge'
    int *aux;
    int v1, v2, tam, fim1 = 0, fim2 = 0, h, i, k;
    tam = fim - inicio + 1;
    v1 = inicio;
    v2 = meio + 1;

    aux = (int*)malloc(tam * sizeof (int));     // Alocação dinâmica do vetor auxiliar
    if(!aux){
        printf("\nErro ao alocar memoria");
        return;
    }

    for(i = 0; i < tam; i++) {
        if (!fim1 && !fim2) {           // Se ainda existem posições a percorrer nos dois vetores,
            dados->mediaCmp[j]++;
            if (v[v1] < v[v2]) {        // Verifica quais são os menores valores e
                aux[i] = v[v1++];       // os coloca em ordem no vetor auxiliar
            }
            else {
                aux[i] = v[v2++];
                dados->mediaTrc[j]++;
            }
            if (v1 > meio)              // Se o vetor 1 chegou ao fim,
                fim1 = 1;               // Altera a variável fim1 para indicar essa situação
            if (v2 > fim)               // O mesmo para o vetor 2
                fim2 = 1;
        } else {                        // Se não existem mais posições a percorrer em um dos vetores,
            if (!fim1) {
                aux[i] = v[v1++];       // Copia o restante do outro vetor para o vetor auxiliar
            }
            else {
                aux[i] = v[v2++];
            }
        }
    }

    for(h = 0, k = inicio; h < tam; h++, k++)
        v[k] = aux[h];                  // Copia o vetor auxiliar para o vetor principal

    free(aux);                  // Libera a memória alocada dinamicamente
}

void quickSort(int *vet, int inicio, int fim, tdados *dados, int j) {
    // Implementa o algoritmo de ordenação QuickSort
    int pivo;

    if (inicio < fim) {
        pivo = particiona(vet, inicio, fim, dados, j);
        quickSort(vet, inicio, pivo - 1, dados, j);
        quickSort(vet, pivo + 1, fim, dados, j);
    }
}

int particiona(int *vet, int inicio, int fim, tdados *dados, int j) {
    // Retorna a posição do pivô do vetor, apó o seu particionamento
    int pivo, pos, i, aux;

    pivo = vet[inicio];
    pos = inicio;

    // Coloca os valores menores que o pivô à esquerda e os maiores à direita
    for (i = inicio + 1; i <= fim; i++) {
        dados->mediaCmp[j]++;
        if (vet[i] <= pivo) {
            pos++;
            if (i != pos) {
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux;
                dados->mediaTrc[j]++;
            }
        }
    }

    // Coloca o pivô na posição correta e retorna a posição
    if(vet[inicio] != vet[pos])
        dados->mediaTrc[j]++;
    aux = vet[inicio];
    vet[inicio] = vet[pos];
    vet[pos] = aux;

    return pos;
}

void heapSort(int *vet, int tam, tdados *dados, int j){
    // Implementa o algoritmo de ordenação HeapSort
    int i, aux;

    // Construir um heap máximo
    for (i = (tam - 1) / 2; i >= 0; i--)
        criaHeap(vet, i, tam - 1, dados, j);

    // Extrair elementos um por um do heap
    for (i = tam - 1; i >= 1; i--){
        // Move a raiz atual para o final do array
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        dados->mediaTrc[j]++;
        // Chama criaHeap no heap reduzido
        criaHeap(vet, 0, i - 1, dados, j);
    }
}

void criaHeap(int *vet, int ini, int fim, tdados *dados, int j){
    // Cria o Heap máximo para o algoritmo HeapSort
    int aux, i;

    aux = vet[ini];                 // Inicializa a variável aux com o primeiro valor da partição de vet (pai)
    i = ini * 2 + 1;                // Cálculo do primeiro filho de i

    while(i <= fim){                // Enquanto o filho for menor que índice do fim do vetor
        if(i < fim) {                 // Se o filho for menor que o índice do fim do vetor
            dados->mediaCmp[j]++;
            if (vet[i] < vet[i + 1]) // Verifica qual dos filhos é maior
                i++;
        }
        dados->mediaCmp[j]++;
        if(aux < vet[i]){           // Se o filho for maior que o pai
            vet[ini] = vet[i];      // Filho se torna pai
            ini = i;
            i = 2 * ini + 1;        // Calcula o primeiro filho dele
            dados->mediaTrc[j]++;
        }
        else                        // Se o filho não for maior que o pai
            i = fim + 1;            // i termina
    }
    vet[ini] = aux;                 // Retorna o valor inicial do vetor
}

void insertionIntro(int* vet, int ini, int fim, tdados *dados, int j){
    // Implementa o algoritmo de ordenação Insertion Sort
    int marcador, aux, pos;

    for(marcador = ini + 1; marcador <= fim; marcador++){
        aux = vet[marcador];
        pos = marcador - 1;
        dados->mediaCmp[j]++;
        while(pos >= 0 && aux < vet[pos]){
            vet[pos + 1] = vet[pos];
            pos --;
        }
        if(vet[pos + 1] != aux)
            dados->mediaTrc[j]++;
        vet[pos + 1] = aux;
    }
}

void introSort(int *vet, int ini, int fim, int prof_max, tdados *dados, int j){
    // Implementa o algoritmo de ordenação 'IntroSort'
    int pivo, tam;

    tam = (fim - ini) + 1;

    // Se o tamanho do vetor for menor ou igual a 16, ordena pelo Insertion
    if(tam <= 16) {
        insertionIntro(vet, ini, fim, dados, j);
        return;
    }

    // Se a pilha de recursão atingir o valor máximo, ordena pelo HeapSort
    if(prof_max == 0) {
        heapSort(vet, tam, dados, j);
        return;
    }

    // Senão, ordena o vetor com o QuickSort e faz as chamadas recursivas para cada metade do vetor
    else{
        pivo = particiona(vet, ini, fim, dados, j);
        introSort(vet, ini, pivo - 1, prof_max - 1, dados, j);
        introSort(vet, pivo + 1, fim, prof_max - 1, dados, j);
    }
}

int* geraAleatorios(int tam, int semente){
    // Gera um vetor de números aleatórios de tamanho 'tam'
    int *vetor, i;

    // Aloca memória para o vetor de inteiros
    vetor = (int*) malloc(tam * sizeof(int));
    if(!vetor){
        printf("\nErro ao alocar memória");
        return NULL;
    }

    // Define a semente para a função rand()
    srand(semente);

    // Preenche o vetor com números aleatórios
    for(i = 0; i < tam; i++)
        vetor[i] = rand();

    return vetor;
}

int* geraQuaseOrdenados(int tam, int porcentagem){
    // Gera um vetor quase ordenado, com porcentagem de ordenação definida pelo usuário
    int *vetor, i, desordenados, pos1, pos2, aux;

    // Aloca memória para o vetor de inteiros
    vetor = (int*) malloc(tam * sizeof(int));
    if(!vetor){
        printf("\nErro ao alocar memória");
        return NULL;
    }

    // Preenche o vetor com números ordenados
    for(i = 0; i < tam; i++){
        vetor[i] = i;
    }

    // Calcula a quantidade de elementos a serem desordenados
    desordenados = (tam * porcentagem) / 100;

    // Faz trocas aleatórias para desordenar o vetor
    srand(time(NULL));
    for (i = 0; i < desordenados; i++) {
        pos1 = rand() % tam;
        pos2 = rand() % tam;

        // Troca os elementos
        aux = vetor[pos1];
        vetor[pos1] = vetor[pos2];
        vetor[pos2] = aux;
    }

    return vetor;
}

int* geraOrdenados(int tam, int ordem) {
    // Gera um vetor ordenado crescente (ordem = 0) ou decrescente (ordem = 1), de tamanho 'tam'
    int *vetor;

    vetor = (int*)malloc(tam * sizeof(int));
    if (vetor == NULL) {
        printf("\nErro ao alocar memória");
        return NULL;
    }

    // Preenche o vetor em ordem crescente
    if (ordem == 0) {
        for (int i = 0; i < tam; i++) {
            vetor[i] = i;
        }
    }
    // Preenche o vetor em ordem decrescente
    else if (ordem == 1) {
        for (int i = 0; i < tam; i++) {
            vetor[i] = tam - 1 - i;
        }
    }
        // Valor de ordem inválido
    else {
        printf("Erro: Valor de ordem inválido.\n");
        free(vetor);
        return NULL;
    }

    return vetor;
}

double calculaTempo(LARGE_INTEGER t_ini, LARGE_INTEGER t_fim, LARGE_INTEGER freq){
    // Calcula o tempo gasto pelo algoritmo para ordenar o vetor
    return (double)((t_fim.QuadPart - t_ini.QuadPart) * 1000.0) / freq.QuadPart;
}

double calculaMedia(const double tempo[]){
    // Calcula a média de tempo gasto pelo algoritmo para ordenar o vetor
    int j;
    double soma = 0, media;

    for (j = 0; j < 5; j++) {
        soma = soma + tempo[j];
    }
    media = soma / 5;

    return media;
}

int calculaMediaTroca(tdados *dados){
    // Calcula a média de trocas realizadas pelo algoritmo para ordenar o vetor
    int i, soma = 0, media;

    for (i = 0; i < 5; i++) {
        soma = soma + dados->mediaTrc[i];
    }
    media = (soma / 5);

    return media;
}

long long int calculaMediaComp(tdados *dados){
    // Calcula a média de comparações realizadas pelo algoritmo para ordenar o vetor
    int i;
    long long int soma = 0, media;

    for (i = 0; i < 5; i++) {
        soma = soma + dados->mediaCmp[i];
    }
    media = soma / 5;

    return media;
}

void iniciaVetor(tdados *dados){
    // Inicializa os vetores usados para guardar a quantidade de trocas e de comparações
    int i;

    for(i = 0; i < 5; i++){
        dados->mediaTrc[i] = 0;
        dados->mediaCmp[i] = 0;
    }
}

int menu(){
    // Imprime o menu de opções para o usuário selecionar o algoritmo a ser testado
    int op;

    printf("\n%s\n%5s%s%5s\n%s","==============","","MENU","","==============");
    printf("\n1 - Insertion\n2 - Selection\n3 - MergeSort\n4 - QuickSort\n5 - IntroSort\n"
           "\nEscolha um algoritmo para a realizacao do teste: ");
    scanf("%d", &op);

    return op;
}

void imprimeCabTempo(int op){
    // Imprime os títulos da tabela de tempo de execução
    int i;

    switch(op){
        case 1:
            printf("\n%35s%s\n%32s%s\n", "", "INSERTION SORT", "", "Tempo de Execucao (ms)");
            break;
        case 2:
            printf("\n%35s%s\n%32s%s\n", "", "SELECTION SORT", "", "Tempo de Execucao (ms)");
            break;
        case 3:
            printf("\n%35s%s\n%32s%s\n", "", "MERGESORT", "", "Tempo de Execucao (ms)");
            break;
        case 4:
            printf("\n%35s%s\n%32s%s\n", "", "QUICKSORT", "", "Tempo de Execucao (ms)");
            break;
        case 5:
            printf("\n%35s%s\n%32s%s\n", "", "INTROSORT", "", "Tempo de Execucao (ms)");
            break;
        default:
            return;
    }

    for(i = 0; i < 88; i++)
        printf("-");
    printf("\nTeste\tTam. Entrada\tAleatorio\tCrescente\tDecrescente\tQuase Ordenado\n");
    for(i = 0; i < 88; i++)
        printf("-");
    printf("\n");
}

void imprimeCabComp(){
    // Imprime os títulos da tabela de comparações
    int i;

    printf("\n%30s%s\n", "", "Quantidade de Comparacoes");
    for(i = 0; i < 88; i++)
        printf("-");
    printf("\nTeste\tTam. Entrada\tAleatorio\tCrescente\tDecrescente\tQuase Ordenado\n");
    for(i = 0; i < 88; i++)
        printf("-");
    printf("\n");
}

void imprimeCabTroca(){
    // Imprime os títulos da tabela de trocas
    int i;

    printf("\n\n%32s%s\n", "", "Quantidade de Trocas");
    for(i = 0; i < 88; i++)
        printf("-");
    printf("\nTeste\tTam. Entrada\tAleatorio\tCrescente\tDecrescente\tQuase Ordenado\n");
    for(i = 0; i < 88; i++)
        printf("-");
    printf("\n");
}

void imprimeTempos(int teste, double t_alt, double t_cres, double t_decres, double t_qse_ord, int tam){
    // Imprime os tempos gastos pelo algoritmo para ordenar um vetor
    printf("%d\t%-16d%-16.5f%-16.5f%-16.5f%-16.5f\n", teste, tam, t_alt, t_cres, t_decres, t_qse_ord);
}

void imprimeComps(tdados dados, int tam){
    // Imprime a quantidade de comparações realizadas pelo algoritmo de ordenação
    int i, j;

    for(i = 0; i < 5; i++){
        tam = tam * 10;
        if(i != 0)
            printf("\n");
        printf("%d\t%-16d", i + 1, tam);
        for(j = 0; j < 4; j++){
            printf("%-16lld", dados.comp[i][j]);
        }
    }
}

void imprimeTrocas(tdados dados, int tam){
    // Imprime a quantidade de trocas realizadas pelo algoritmo de ordenação
    int i, j;

    for(i = 0; i < 5; i++){
        tam = tam * 10;
        if(i != 0)
            printf("\n");
        printf("%d\t%-16d", i + 1, tam);
        for(j = 0; j < 4; j++){
            printf("%-16d", dados.troca[i][j]);
        }
    }
}
