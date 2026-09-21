#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void output_array(Array *a) {
    if (a == NULL || a->data == NULL) {
        printf("Array is empty.\n");
        return;
    }

    for (int i = 0; i < a->size; i++) {
        printf("%.2f ", a->data[i]);
    }
    printf("\n");
}

void shift_array(Array *a) {
    if (a == NULL || a->data == NULL || a->size <= 1) {
        return;
    }

    double first = a->data[0];
    for (int i = 1; i < a->size; i++) {
        a->data[i - 1] = a->data[i];
    }
    a->data[a->size - 1] = first;
}

Array *average_adjacent(Array *a) {
    if (a == NULL || a->data == NULL || a->size <= 0) {
        return NULL;
    }

    int new_size = a->size / 2;
    if (a->size % 2 != 0) {
        new_size = (a->size - 1) / 2;
    }

    Array *result = malloc(sizeof(Array));
    if (result == NULL) {
        return NULL;
    }

    result->size = new_size;
    result->data = malloc(sizeof(double) * new_size);
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < new_size; i++) {
        int index = 2 * i;
        result->data[i] = (a->data[index] + a->data[index + 1]) / 2.0;
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./main <array_size>\n");
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        printf("Array size must be a positive integer.\n");
        return 1;
    }

    Array *a = malloc(sizeof(Array));
    if (a == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    a->size = size;
    a->data = malloc(sizeof(double) * size);
    if (a->data == NULL) {
        printf("Memory allocation failed.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < size; i++) {
        a->data[i] = i + 1.5;
    }

    printf("Original array:\n");
    output_array(a);

    shift_array(a);
    printf("After shift:\n");
    output_array(a);

    Array *avg = average_adjacent(a);
    if (avg != NULL) {
        printf("Averaged adjacent pairs:\n");
        output_array(avg);
        free(avg->data);
        free(avg);
    }

    free(a->data);
    free(a);
    return 0;
}

