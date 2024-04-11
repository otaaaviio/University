#include <time.h>
#include <stdlib.h>
#include "docs.h"

#define MAX_SIZE 1000000

int *read_file(FILE *file, int *n, int *is_reading, double *read_time) {
    clock_t start, end;

    start = clock();
    int *arr = NULL, val, i = 0;
    while (!feof(file) && i < MAX_SIZE) {
        if (fscanf(file, "%d", &val) == 1) {
            arr = realloc(arr, (i + 1) * sizeof(int));
            if (arr == NULL) {
                printf("Error allocating memory.\n");
                return NULL;
            }
            arr[i] = val;

            (*n) ++;
            i++;
        } else {
            *is_reading = 0;
        }
    }
    end = clock();
    *read_time += ((double)(end - start)) / CLOCKS_PER_SEC;

    return arr;
}

void write_ord_file(int quantity_files, double *ord_file_time) {
    FILE *input_files[quantity_files];
    int i, num_files = 0, values[quantity_files], active_files = 0;

    for (i = 0; i < quantity_files; i++) {
        char filename[20];
        sprintf(filename, "temp-%d.txt", i + 1);
        input_files[i] = fopen(filename, "r");
        if (input_files[i] != NULL) {
            if (fscanf(input_files[i], "%d", &values[i]) == 1) {
                active_files++;
            }
            num_files++;
        } else {
            break;
        }
    }

    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error opening output file.\n");
        return;
    }

    clock_t start, end;
    while (active_files > 0) {
        start = clock();

        int min_index = -1;
        for (i = 0; i < num_files; i++) {
            if (input_files[i] != NULL && (min_index == -1 || values[i] < values[min_index])) {
                min_index = i;
            }
        }

        fprintf(output_file, "%d\n", values[min_index]);

        if (fscanf(input_files[min_index], "%d", &values[min_index]) != 1) {
            fclose(input_files[min_index]);
            input_files[min_index] = NULL;
            active_files--;
        }

        end = clock();

        *ord_file_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    fclose(output_file);
}

void remove_temp_file(int quantity_files) {
    int i;
    for (i = 0; i < quantity_files; i++) {
        char filename[20];
        sprintf(filename, "temp-%d.txt", i + 1);
        remove(filename);
    }
}

void write_temp_file(int *arr, int size, int *i_files) {
    FILE *temp_file;
    char filename[20];
    sprintf(filename, "temp-%d.txt", *i_files);
    (*i_files) ++;
    temp_file = fopen(filename, "w");

    int i;
    for (i = 0; i < size; i++) {
        fprintf(temp_file, "%d\n", arr[i]);
    }

    if (arr != NULL) free(arr);

    if (temp_file != NULL) fclose(temp_file);
}