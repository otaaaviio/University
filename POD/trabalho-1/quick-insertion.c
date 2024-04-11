#include "docs.h"

void insertion_sort(int arr[], int low, int high) {
    int i, key, j;
    for (i = low + 1; i <= high; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int median_of_three(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])
        swap( &arr[low], &arr[mid]);
    if (arr[low] > arr[high])
        swap( &arr[low], &arr[high]);
    if (arr[mid] > arr[high])
        swap( &arr[mid], &arr[high]);
    swap( &arr[mid], &arr[high]);
    return arr[high];
}

int partition(int arr[], int low, int high) {
    int pivot = median_of_three(arr, low, high);
    int i = (low - 1);

    int j;
    for (j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap( &arr[i], &arr[j]);
        }
    }
    swap( &arr[i + 1], &arr[high]);
    return (i + 1);
}

void hybrid_quick_sort(int arr[], int low, int high) {
    while (low < high) {
        if (high - low + 1 < 100) {
            insertion_sort(arr, low, high);
            break;
        } else {
            int pivot = partition(arr, low, high);
            if (pivot - low < high - pivot) {
                hybrid_quick_sort(arr, low, pivot - 1);
                low = pivot + 1;
            } else {
                hybrid_quick_sort(arr, pivot + 1, high);
                high = pivot - 1;
            }
        }
    }
}