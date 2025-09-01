#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXN 1000

long long comparacoes;

// Algoritmos 

void bubble_sort(int *v, int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

void insertion_sort(int *v, int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                j--;
            } else break;
        }
        v[j + 1] = chave;
    }
}

// Função de comparação para qsort

int cmp_qsort(const void *a, const void *b) {
    comparacoes++;
    int x = *(int*)a, y = *(int*)b;
    return (x > y) - (x < y);
}

// Medição
double medir_tempo(void (*sort)(int*, int), int *v, int n, long long *comps) {
    int *copia = malloc(n * sizeof(int));
    memcpy(copia, v, n * sizeof(int));

    comparacoes = 0;
    clock_t inicio = clock();
    sort(copia, n);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
    *comps = comparacoes;

    free(copia);
    return tempo;
}

double medir_qsort(int *v, int n, long long *comps) {
    int *copia = malloc(n * sizeof(int));
    memcpy(copia, v, n * sizeof(int));

    comparacoes = 0;
    clock_t inicio = clock();
    qsort(copia, n, sizeof(int), cmp_qsort);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
    *comps = comparacoes;

    free(copia);
    return tempo;
}

// Cenários

void gerar_vetor(int *v, int n, int tipo) {
    srand(42);
    if (tipo == 0) { // Aleatório
        for (int i = 0; i < n; i++) v[i] = rand() % 1001;
    }
    else if (tipo == 1) { // Crescente
        for (int i = 0; i < n; i++) v[i] = i % 1001;
    }
    else if (tipo == 2) { // Reverso
        for (int i = 0; i < n; i++) v[i] = (n - i) % 1001;
    }
    else if (tipo == 3) { // Quase ordenado (10%)
        for (int i = 0; i < n; i++) v[i] = i % 1001;
        int trocas = n/10;
        for (int i = 0; i < trocas; i++) {
            int a = rand() % n, b = rand() % n;
            int tmp = v[a]; v[a] = v[b]; v[b] = tmp;
        }
    }
}

// Exemplo
void exibir_exemplo(int *v, int n) {
    printf("Exemplo do vetor (primeiros 20 elementos): ");
    int limite = (n < 20 ? n : 20);
    for (int i = 0; i < limite; i++) {
        printf("%d ", v[i]);
    }
    printf("...\n");
}


int main() {
    int tamanhos[] = {1000}; 
    char *cenarios[] = {"Aleatório", "Crescente", "Reverso", "Quase Ordenado"};
    int nCenarios = 4;

    int *vet = malloc(MAXN * sizeof(int));

    for (int c = 0; c < nCenarios; c++) {
        for (int t = 0; t < 1; t++) { 
            int n = tamanhos[t];
            gerar_vetor(vet, n, c);

            printf("\n==============================\n");
            printf("Cenário: %s | N = %d\n", cenarios[c], n);
            exibir_exemplo(vet, n);

            printf("\n%-12s | %-12s | %-15s\n", "Algoritmo", "Tempo(ms)", "Comparações");
            printf("---------------------------------------------------\n");

            long long comps;
            double tempo;

            // Bubble Sort
            tempo = medir_tempo(bubble_sort, vet, n, &comps);
            printf("%-12s | %-12.3f   | %-15lld\n", "BubbleSort", tempo, comps);

            // Insertion Sort
            tempo = medir_tempo(insertion_sort, vet, n, &comps);
            printf("%-12s | %-12.3f   | %-15lld\n", "Insertion", tempo, comps);

            // qsort
            tempo = medir_qsort(vet, n, &comps);
            printf("%-12s | %-12.3f   | %-15lld\n", "qsort", tempo, comps);
        }
    }

    free(vet);
    return 0;
}
