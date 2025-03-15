#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "docs.h"

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void hybrid_bucket_sort(int arr[], int n, double *ord_time) {
    clock_t start, end;

    int max_val = arr[0], i;

    start = clock();
    for (i = 1; i < n; i++)
        if (arr[i] > max_val)
            max_val = arr[i];
    end = clock();

    *ord_time -= ((double)(end - start)) / CLOCKS_PER_SEC;

    int *buckets = calloc(max_val + 1, sizeof(int));

    for (i = 0; i < n; i++)
        buckets[arr[i]]++;

    i = 0;
    int j, k;
    for (j = 0; j <= max_val; j++)
        for (k = buckets[j]; k > 0; k--)
            arr[i++] = j;

    heap_sort(arr, n);

    free(buckets);
}