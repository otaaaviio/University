#include <stdio.h>

#ifndef DOCS_H
#define DOCS_H

/**
 * @brief Sorts a portion of an array using the insertion sort algorithm.
 * @param arr The array to sort.
 * @param low The starting index of the portion to sort.
 * @param high The ending index of the portion to sort.
 */
void insertion_sort(int arr[], int low, int high);

/**
 * @brief Swaps the values of two integers.
 * @param a A pointer to the first integer.
 * @param b A pointer to the second integer.
 */
void swap(int* a, int* b);

/**
 * @brief Finds the median of three integers.
 * @param arr The array that contains the integers.
 * @param low The index of the first integer.
 * @param high The index of the second integer.
 * @return The median of the three integers.
 */
int median_of_three(int arr[], int low, int high);

/**
 * @brief Partitions a portion of an array around a pivot.
 * @param arr The array to partition.
 * @param low The starting index of the portion to partition.
 * @param high The ending index of the portion to partition.
 * @return The index of the pivot after partitioning.
 */
int partition(int arr[], int low, int high);

/**
 * @brief Sorts an array using the hybrid quick sort algorithm.
 * @param arr The array to sort.
 * @param low The starting index of the portion to sort.
 * @param high The ending index of the portion to sort.
 */
void hybrid_quick_sort(int arr[], int low, int high);

/**
 * @brief The main function of the program.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return 0 if the program executed successfully, 1 otherwise.
 */
int main(int argc, char *argv[]);

/**
 * @brief Reads integers from a file and stores them in an array.
 * @param file The file to read from.
 * @param n A pointer to an integer that will hold the number of integers read.
 * @param is_reading A pointer to an integer that indicates whether the file is still being read.
 * @param read_time A pointer to a double that will hold the time taken to read the file.
 * @return A pointer to the array of integers read from the file.
 */
int* read_file(FILE *file, int *n, int *is_reading, double *read_time);

/**
 * @brief Writes the sorted integers to a file.
 * @param quantity_files The number of temporary files created during sorting.
 * @param ord_file_time A pointer to a double that will hold the time taken to write the final file.
 */
void write_ord_file(int quantity_files, double *ord_file_time);

/**
 * @brief Removes the temporary files created during sorting.
 * @param quantity_files The number of temporary files created during sorting.
 */
void remove_temp_file(int quantity_files);

/**
 * @brief Displays the results of the sorting process.
 * @param read_time The time taken to read the integers from the file.
 * @param ord_time The time taken to sort the integers.
 * @param ord_file_time The time taken to write the final file.
 * @param type The selected algorithm.
 */
void show_results(double read_time, double ord_time, double ord_file_time, int type);

/**
 * @brief Writes the sorted integers to a temporary file.
 * @param arr The array of integers to write to the file.
 * @param size The number of integers in the array.
 * @param i_files A pointer to an integer that holds the current file number.
 */
void write_temp_file(int *arr, int size, int *i_files);

/**
 * @brief Displays the menu and allows the user to select an algorithm.
 * @return The selected algorithm.
 */
int select_algorithm();

/**
 * @brief Clears the terminal display.
 */
void clear_display();

/**
 * @brief Sorts an array using the heap sort algorithm.
 * @param arr The array to sort.
 * @param n The number of elements in the array.
 */
void heapify(int arr[], int n, int i);

/**
 * @brief Sorts an array using the heap sort algorithm.
 * @param arr The array to sort.
 * @param n The number of elements in the array.
 */
void heap_sort(int arr[], int n);

/**
 * @brief Sorts an array using the hybrid bucket sort algorithm.
 * @param array The array to sort.
 * @param n The number of elements in the array.
 * @param ord_time A pointer to a double that will hold the time taken to sort the integers.
 */
void hybrid_bucket_sort(int array[], int n, double *ord_time);

#endif