#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000 

int **A, **B, **C;
int NUM_THREAD;

typedef struct {
    int thread_id;
} ThreadData;

void* moltiplica_frazione(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int id = data->thread_id;

    int righe_per_thread = N / NUM_THREAD;
    int riga_inizio = id * righe_per_thread;
    int riga_fine = (id == NUM_THREAD - 1) ? N : riga_inizio + righe_per_thread;

    for (int i = riga_inizio; i < riga_fine; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Uso: %s <numero_di_thread>\n", argv[0]);
        return 1;
    }
    
    NUM_THREAD = atoi(argv[1]);


    A = malloc(N * sizeof(int*));
    B = malloc(N * sizeof(int*));
    C = malloc(N * sizeof(int*));
    
    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
    }

    // Popolamento con numeri casuali
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Misurazione del tempo di inizio
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t threads[NUM_THREAD];
    ThreadData thread_data[NUM_THREAD];

    for (int i = 0; i < NUM_THREAD; i++) {
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, moltiplica_frazione, (void*)&thread_data[i]);
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    // Misurazione del tempo di fine
    clock_gettime(CLOCK_MONOTONIC, &end);
    double tempo_impiegato = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;


    printf("%f\n", tempo_impiegato);

    // Liberazione memoria
    for (int i = 0; i < N; i++) {
        free(A[i]); 
        free(B[i]); 
        free(C[i]);
    }
    
    free(A); 
    free(B); 
    free(C);

    return 0;
}
