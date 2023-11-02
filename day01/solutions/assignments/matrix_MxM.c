#include <stdio.h>
#include <stdlib.h>
#include "time.h"

void init(int ***a, int n) {
    int i, j;
    
    *a = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        (*a)[i] = (int *)malloc(n * sizeof(int));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            (*a)[i][j] = 0;
        }
    }
}

void multiply_matrices(int **a, int **b, int **c, int n, int block_size) {
    int i, j, k, i_blk, j_blk, k_blk;

    for (i_blk = 0; i_blk < n; i_blk += block_size) {
        for (j_blk = 0; j_blk < n; j_blk += block_size) {
            for (k_blk = 0; k_blk < n; k_blk += block_size) {
                for (i = i_blk; i < i_blk + block_size && i < n; i++) {
                    for (j = j_blk; j < j_blk + block_size && j < n; j++) {
                        for (k = k_blk; k < k_blk + block_size && k < n; k++) {
                            c[i][j] += a[i][k] * b[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n = 500;
    int **a, **b, **c;
    int i, j, k;

    init(&a, n);
    init(&b, n);
    init(&c, n);

    printf("a[0][0] = %d\n", a[0][0]);

    double start =  (double)clock() / (double)CLOCKS_PER_SEC;
    double s = 0;
    int block_sizes[] = {32, 64, 128, 256, 512};
    int num_block_sizes = sizeof(block_sizes) / sizeof(block_sizes[0]);


    for (int bs = 0; bs < num_block_sizes; bs++) {
        int block_size = block_sizes[bs];
        
        clock_t start = clock();
        multiply_matrices(a, b, c, n, block_size);
        clock_t end = clock();
        double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;

        double bandwidth = (2.0 * n * n * n) / (cpu_time * 1024 * 1024); // in MB/s

        printf("Block size: %d, CPU time: %f seconds, Bandwidth: %f MB/s\n", block_size, cpu_time, bandwidth);
    }

    for (i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
