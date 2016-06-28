#include <bits/stdc++.h>
#include <omp.h>
#include "matrix_helper.h"

#define db(a) \
cout << #a << " = "<< a << endl;
#define db2(a,b) \
cout << #a << " = " <<  a << " " << #b << " = " << b << endl;
#define db3(a,b,c) \
cout << #a << " = " <<  a << " " << #b << " = " << b \
<< " " << #c << " = " << c << endl;

#define dbl(i, a) cout << "[" << i << "]" << " = "<< a << ", ";
#define foreach(mapa, it) \
 for (typeof(mapa.begin()) it = mapa.begin(); it != mapa.end(); it++)
#define listar(lista) \
    for(int i = 0; i < lista.size(); i++) \
        { dbl(i, lista[i]);} cout << endl;

using namespace std;
int OMP_NUM_THREADS = 4;

int** matrix_multiplication_omp(int** A, int** B, const int rows, const int cols) {
    if (rows != cols) {
        puts("the number of rows should be the same as the number of columns");
        return NULL;
    }
    int n = rows;
    int** C;
    matrix_init(&C, n, n);
    int i, j;
    #pragma omp parallel for private(i, j) num_threads(OMP_NUM_THREADS)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}
int main(int argc, char** argv) {
    // #undef dennisbot
    #ifdef dennisbot
        freopen("mult_er_sec.in", "r", stdin);
        freopen("mult_er_sec.out", "w", stdout);
        clock_t _start = clock();
    #endif
    int n;
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            if (i == 0)
                printf("%s", argv[i]);
            else
                printf(" %s", argv[i]);
        }
        puts("");
        OMP_NUM_THREADS = atoi(argv[argc - 1]);
    }
    while (scanf("%d", &n) != EOF) {
        int **A, **B, **C;
        /* se inicializa / reserva memoria para las matrices */
        matrix_init(&A, n, n);
        matrix_init(&B, n, n);

        /* se hace lectura desde stdin de las matrices */
        matrix_read(&A, n, n);
        matrix_read(&B, n, n);

        /* se muestra en el stdout las matrices */
        // matrix_print(A, n, n);
        // matrix_print(B, n, n);

        // C = matrix_multiplication(A, B, n, n);
        C = matrix_multiplication_omp(A, B, n, n);

        matrix_readable_print(C, n, n);
    }

    #ifdef dennisbot
        printf("\ntime=%.3fs\n", (clock() - _start) * 1. / CLOCKS_PER_SEC);
    #endif
    return 0;
}