#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

void count_sort(int a[], int n) {
    int* temp = (int*)malloc(n * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

#pragma omp parallel for shared(a, temp, n) schedule(static)
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] < a[i] || (a[j] == a[i] && j < i)) {
                count++;
            }
        }
        temp[count] = a[i];
    }

#pragma omp parallel for shared(a, temp, n) schedule(static)
    for (int i = 0; i < n; i++) {
        a[i] = temp[i];
    }

    free(temp);
}

int main() {
    int n = 1000000;  // Adjust this value for large array size testing
    int* a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize random number generator
    srand(time(NULL));

    // Initialize array with random values
    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
    }

    double start_time = omp_get_wtime();
    count_sort(a, n);
    double end_time = omp_get_wtime();

    printf("Time taken: %f seconds\n", end_time - start_time);

    free(a);
    return 0;
}

