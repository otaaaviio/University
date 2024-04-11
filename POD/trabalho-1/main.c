#include "file-operations.c"
#include "quick-insertion.c"
#include "bucket-heap.c"

void show_results(double read_time, double ord_time, double ord_file_time, int type) {
    clear_display();

    if (type == 1)
        printf("QuickSort with InsertionSort:\n");
    else
        printf("BucketSort with HeapSort:\n");

    printf("Read time: %f\n", read_time);
    printf("Order time: %f\n", ord_time);
    printf("Order file time: %f\n", ord_file_time);
    printf("Total time: %f\n", read_time + ord_time + ord_file_time);
    printf("The file has been sorted and saved as 'output.txt'.\n");
}

int select_algorithm() {
    int t, r;
    printf("(1) QuickSort with InsertionSort\n(2) BucketSort with HeapSort\n(3) Sair\nSelect an option: ");
    r = scanf("%d", &t);
    while (t != 1 && t != 2 && t != 3) {
        printf("Invalid option. Please select a valid option: ");
        r = scanf("%d", &t);
    }

    return t;
}

void clear_display() {
    printf("\e[0;0H");
    printf("\e[2J");
}

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    clear_display();

    int type = select_algorithm();

    double ord_time = 0, read_time = 0, ord_file_time = 0;
    int n = 0, is_reading = 1, i_files = 1;
    while (is_reading == 1) {
        int mult = n;
        int *arr = read_file(file, &n, &is_reading, &read_time);

        if (arr != NULL) {
            clock_t start, end;
            start = clock();

            switch (type) {
            case 1:
                hybrid_quick_sort(arr, 0, n - mult - 1);
                break;
            case 2:
                hybrid_bucket_sort(arr, n - mult, &ord_time);
                break;
            case 3:
                return 0;
            }

            end = clock();

            ord_time += (double)(end - start) / CLOCKS_PER_SEC;

            write_temp_file(arr, n - mult, &i_files);
        }
    }
    write_ord_file(i_files, &ord_file_time);

    fclose(file);

    remove_temp_file(i_files);

    show_results(read_time, ord_time, ord_file_time, type);

    return 0;
}