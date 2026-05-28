#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void linear(int *array, int size, int target) {
    clock_t st = clock();

    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            break;
        }
    }

    clock_t stop = clock();
    double time_taken = (double)(stop - st) / CLOCKS_PER_SEC;

    printf("%-15d | %lf  for linear\n", size, time_taken);
}


void binary(int *array, int size, int target, int left, int right) {
    clock_t st = clock();

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == target)
            break;
        else if (target > array[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }

    clock_t sp = clock();
    double time_taken = (double)(sp - st) / CLOCKS_PER_SEC;

    printf("%-15d | %lf  for binary\n", size, time_taken);
}


void bubble(int *array, int size) {
    clock_t st = clock();

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    clock_t sp = clock();
    double time_taken = (double)(sp - st) / CLOCKS_PER_SEC;

    printf("%-15d | %lf  for bubble\n", size, time_taken);
}

int main() {
    int sizes[] = {500, 1000, 2000, 4000, 8000};
    int n = sizeof(sizes) / sizeof(sizes[0]);
    int target = -1;

    for (int i = 0; i < n; i++) {
        int *ar = malloc(sizes[i] * sizeof(int));

        for (int j = 0; j < sizes[i]; j++)
            ar[j] = j;

        linear(ar, sizes[i], target);
        bubble(ar, sizes[i]);
        binary(ar, sizes[i], target, 0, sizes[i] - 1);
        printf("\n");
        free(ar);
    }

    return 0;
}

