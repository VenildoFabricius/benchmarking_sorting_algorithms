#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "introsort.h"

int main() {

    // Declaração de variáveis
    LARGE_INTEGER t_ini, t_fim, freq;
    int op, i, j, tam = 10, semente, *vet, prof_max;
    double tempo[5], t_aleatorio, t_crescente, t_decrescente, t_qse_ordenado;
    tdados dados;


    op = menu();                                                        // Exibe o menu de opções para a escolha do algoritmo

    switch (op) {
        case 1:     // Insertion
            imprimeCabTempo(op);

            for (i = 0; i < 5; i++) {
                tam = tam * 10;                                         // Define o tamanho do vetor

                // Teste com vetor aleatório
                iniciaVetor(&dados);                                    // Inicializa os vetores que armazenam a quantidade de comparações e de trocas
                for (j = 0; j < 4; j++) {                               // Estrutura para calcular as métricas de cada teste
                    semente = rand();                                   // Define um valor aleatório para a semente
                    vet = geraAleatorios(tam, semente);                 // Aloca o vetor aleatório com a semente fornecida
                    QueryPerformanceFrequency(&freq);        // Obtém a frequência do contador de desempenho
                    QueryPerformanceCounter(&t_ini);   // Marca o tempo de início de execução
                    insertion(vet, tam, &dados, j);                     // Chama o algoritmo de ordenação
                    QueryPerformanceCounter(&t_fim);   // Marca o tempo final de execução
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);        // Calcula o tempo de execução considerando a frequência do contador de desempenho
                }
                t_aleatorio = calculaMedia(tempo);                      // Cálculo da média dos tempos de execução
                dados.troca[i][0] = calculaMediaTroca(&dados);          // Cálculo da média das trocas
                dados.comp[i][0] = calculaMediaComp(&dados);            // Cálculo da média das comparações
                                                                        // (Os mesmos procedimentos são feitos para todos os testes de todos os algoritmos)
                // Teste com vetor ordenado crescente
                iniciaVetor(&dados);                                    // Inicializa o vetor de comparações e de trocas
                vet = geraOrdenados(tam, 0);                     // Aloca o vetor dos dados a serem ordenados
                QueryPerformanceFrequency(&freq);            // Calcula o tempo de execução do algoritmo
                QueryPerformanceCounter(&t_ini);
                insertion(vet, tam, &dados, 1);
                QueryPerformanceCounter(&t_fim);
                t_crescente = calculaTempo(t_ini, t_fim, freq);         // Armazena os resultados
                dados.troca[i][1] = dados.mediaTrc[1];
                dados.comp[i][1] = dados.mediaCmp[1];


                // Teste com vetor ordenado decrescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 1);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                insertion(vet, tam, &dados, 2);
                QueryPerformanceCounter(&t_fim);
                t_decrescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][2] = dados.mediaTrc[2];
                dados.comp[i][2] = dados.mediaCmp[2];

                // Teste com vetor quase ordenado
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    vet = geraQuaseOrdenados(tam, 10);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    insertion(vet, tam, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_qse_ordenado = calculaMedia(tempo);
                dados.troca[i][3] = calculaMediaTroca(&dados);
                dados.comp[i][3] = calculaMediaComp(&dados);

                // Impressão dos tempos de execução
                imprimeTempos(i + 1, t_aleatorio, t_crescente, t_decrescente,t_qse_ordenado, tam);
            }
            // Impressão das quantidades de comparações
            imprimeCabComp();
            imprimeComps(dados, tam/100000);

            // Impressão das quantidades de trocas
            imprimeCabTroca();
            imprimeTrocas(dados, tam/100000);
            break;
        case 2:     // Selection
            imprimeCabTempo(op);

            for (i = 0; i < 5; i++) {
                tam = tam * 10;

                // Teste com vetor aleatório
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    semente = rand();
                    vet = geraAleatorios(tam, semente);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    selection(vet, tam, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_aleatorio = calculaMedia(tempo);
                dados.troca[i][0] = calculaMediaTroca(&dados);
                dados.comp[i][0] = calculaMediaComp(&dados);

                // Teste com vetor ordenado crescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 0);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                selection(vet, tam, &dados, 1);
                QueryPerformanceCounter(&t_fim);
                t_crescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][1] = dados.mediaTrc[1];
                dados.comp[i][1] = dados.mediaCmp[1];

                // Teste com vetor ordenado decrescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 1);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                selection(vet, tam, &dados, 2);
                QueryPerformanceCounter(&t_fim);
                t_decrescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][2] = dados.mediaTrc[2];
                dados.comp[i][2] = dados.mediaCmp[2];

                // Teste com vetor quase ordenado
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    vet = geraQuaseOrdenados(tam, 10);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    selection(vet, tam, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_qse_ordenado = calculaMedia(tempo);
                dados.troca[i][3] = calculaMediaTroca(&dados);
                dados.comp[i][3] = calculaMediaComp(&dados);

                // Impressão dos tempos de execução
                imprimeTempos(i + 1, t_aleatorio, t_crescente, t_decrescente,
                              t_qse_ordenado, tam);
            }

            // Impressão das quantidades de comparações
            imprimeCabComp();
            imprimeComps(dados, tam/100000);

            // Impressão das quantidades de trocas
            imprimeCabTroca();
            imprimeTrocas(dados, tam/100000);
            break;
        case 3:     // MergeSort
            imprimeCabTempo(op);

            for (i = 0; i < 5; i++) {
                tam = tam * 10;

                // Teste com vetor aleatório
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    semente = rand();
                    vet = geraAleatorios(tam, semente);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    mergeSort(vet, 0, tam - 1, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_aleatorio = calculaMedia(tempo);
                dados.troca[i][0] = calculaMediaTroca(&dados);
                dados.comp[i][0] = calculaMediaComp(&dados);

                // Teste com vetor ordenado crescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 0);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                mergeSort(vet, 0, tam - 1, &dados, 1);
                QueryPerformanceCounter(&t_fim);
                t_crescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][1] = dados.mediaTrc[1];
                dados.comp[i][1] = dados.mediaCmp[1];

                // Teste com vetor ordenado decrescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 1);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                mergeSort(vet, 0, tam - 1, &dados, 2);
                QueryPerformanceCounter(&t_fim);
                t_decrescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][2] = dados.mediaTrc[2];
                dados.comp[i][2] = dados.mediaCmp[2];

                // Teste com vetor quase ordenado
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    vet = geraQuaseOrdenados(tam, 10);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    mergeSort(vet, 0, tam - 1, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_qse_ordenado = calculaMedia(tempo);
                dados.troca[i][3] = calculaMediaTroca(&dados);
                dados.comp[i][3] = calculaMediaComp(&dados);

                // Impressão dos resultados
                imprimeTempos(i + 1, t_aleatorio, t_crescente, t_decrescente,
                              t_qse_ordenado, tam);
            }
            // Impressão das quantidades de comparações
            imprimeCabComp();
            imprimeComps(dados, tam/100000);

            // Impressão das quantidades de trocas
            imprimeCabTroca();
            imprimeTrocas(dados, tam/100000);
            break;
        case 4:     // QuickSort
            imprimeCabTempo(op);

            for (i = 0; i < 5; i++) {
                tam = tam * 10;

                // Teste com vetor aleatório
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    semente = rand();
                    vet = geraAleatorios(tam, semente);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    quickSort(vet, 0, tam - 1, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_aleatorio = calculaMedia(tempo);
                dados.troca[i][0] = calculaMediaTroca(&dados);
                dados.comp[i][0] = calculaMediaComp(&dados);

                // Teste com vetor ordenado crescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 0);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                quickSort(vet, 0, tam - 1, &dados, 1);
                QueryPerformanceCounter(&t_fim);
                t_crescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][1] = dados.mediaTrc[1];
                dados.comp[i][1] = dados.mediaCmp[1];

                // Teste com vetor ordenado decrescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 1);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                quickSort(vet, 0, tam - 1, &dados, 2);
                QueryPerformanceCounter(&t_fim);
                t_decrescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][2] = dados.mediaTrc[2];
                dados.comp[i][2] = dados.mediaCmp[2];

                // Teste com vetor quase ordenado
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    vet = geraQuaseOrdenados(tam, 10);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    quickSort(vet, 0, tam - 1, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_qse_ordenado = calculaMedia(tempo);
                dados.troca[i][3] = calculaMediaTroca(&dados);
                dados.comp[i][3] = calculaMediaComp(&dados);

                // Impressão dos resultados
                imprimeTempos(i + 1, t_aleatorio, t_crescente, t_decrescente,
                              t_qse_ordenado, tam);
            }
            // Impressão das quantidades de comparações
            imprimeCabComp();
            imprimeComps(dados, tam/100000);

            // Impressão das quantidades de trocas
            imprimeCabTroca();
            imprimeTrocas(dados, tam/100000);
            break;
        case 5:     // IntroSort
            imprimeCabTempo(op);

            for (i = 0; i < 5; i++) {
                tam = tam * 10;
                prof_max = 2 * log2(tam);

                // Teste com vetor aleatório
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    semente = rand();
                    vet = geraAleatorios(tam, semente);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    introSort(vet, 0, tam - 1, prof_max, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_aleatorio = calculaMedia(tempo);
                dados.troca[i][0] = calculaMediaTroca(&dados);
                dados.comp[i][0] = calculaMediaComp(&dados);

                // Teste com vetor ordenado crescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 0);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                introSort(vet, 0, tam - 1, prof_max, &dados, 1);
                QueryPerformanceCounter(&t_fim);
                t_crescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][1] = dados.mediaTrc[1];
                dados.comp[i][1] = dados.mediaCmp[1];

                // Teste com vetor ordenado decrescente
                iniciaVetor(&dados);
                vet = geraOrdenados(tam, 1);
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t_ini);
                introSort(vet, 0, tam - 1, prof_max, &dados, 2);
                QueryPerformanceCounter(&t_fim);
                t_decrescente = calculaTempo(t_ini, t_fim, freq);
                dados.troca[i][2] = dados.mediaTrc[2];
                dados.comp[i][2] = dados.mediaCmp[2];

                // Teste com vetor quase ordenado
                iniciaVetor(&dados);
                for (j = 0; j < 4; j++) {
                    vet = geraQuaseOrdenados(tam, 90);
                    QueryPerformanceFrequency(&freq);
                    QueryPerformanceCounter(&t_ini);
                    introSort(vet, 0, tam - 1, prof_max, &dados, j);
                    QueryPerformanceCounter(&t_fim);
                    tempo[j] = calculaTempo(t_ini, t_fim, freq);
                }
                t_qse_ordenado = calculaMedia(tempo);
                dados.troca[i][3] = calculaMediaTroca(&dados);
                dados.comp[i][3] = calculaMediaComp(&dados);

                // Impressão dos resultados
                imprimeTempos(i + 1, t_aleatorio, t_crescente, t_decrescente,
                              t_qse_ordenado, tam);
            }
            // Impressão das quantidades de comparações
            imprimeCabComp();
            imprimeComps(dados, tam/100000);

            // Impressão das quantidades de trocas
            imprimeCabTroca();
            imprimeTrocas(dados, tam/100000);
            break;
        default:
            printf("\nOpcao invalida.");
            }

    printf("\n\n");

    return 0;
}
