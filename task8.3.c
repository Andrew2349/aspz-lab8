#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 100000

int cmp_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void fill_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void fill_reverse_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void fill_all_equal(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = 42;
}

void fill_random(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
}

double time_qsort(int *arr, int n) {
    clock_t start = clock();
    qsort(arr, n, sizeof(int), cmp_int);
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i-1] > arr[i]) return 0;
    }
    return 1;
}

void run_test(const char *name, void (*fill)(int *, int), int n) {
    int *arr = malloc(sizeof(int) * n);
    fill(arr, n);

    printf("Test: %s (%d elements)\n", name, n);
    double t = time_qsort(arr, n);
    printf("Time: %.4f sec | Sorted: %s\n\n", t, is_sorted(arr, n) ? "Yes" : "No");

    free(arr);
}

int main() {
    srand(time(NULL));

    int n = 50000;

    run_test("Sorted", fill_sorted, n);
    run_test("Reverse Sorted", fill_reverse_sorted, n);
    run_test("All Equal", fill_all_equal, n);
    run_test("Random", fill_random, n);

    return 0;
}

