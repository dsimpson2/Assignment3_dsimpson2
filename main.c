#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void output_array(Array *a) {
    if (a == NULL || a->data == NULL) { // Check if the array pointer or its data is NULL
        printf("Array is empty.\n"); // Print a message indicating the array is empty
        return;
    }

    for (int i = 0; i < a->size; i++) { // Loop through each element of the array and print it with two decimal places
        printf("%.2f ", a->data[i]); 
    }
    printf("\n");
}

void shift_array(Array *a) { // Function to shift the elements of the array to the left by one position
    if (a == NULL || a->data == NULL || a->size <= 1) {
        return;
    }

    double first = a->data[0]; // Store the first element to be moved to the end
    for (int i = 1; i < a->size; i++) {
        a->data[i - 1] = a->data[i];  // Shift each element to the left by one position
    }
    a->data[a->size - 1] = first; // Place the first element at the end of the array
}

Array *average_adjacent(Array *a) { // Function to create a new array containing the averages of adjacent pairs from the original array
    if (a == NULL || a->data == NULL || a->size <= 0) {
        return NULL; // Return NULL if the input array is invalid or empty
    }

    int new_size = a->size / 2; // Calculate the size of the new array (half of the original size)
    if (a->size % 2 != 0) {
        new_size = (a->size - 1) / 2; // If the original size is odd, we ignore the last element for averaging
    }

    Array *result = malloc(sizeof(Array)); // Allocate memory for the new array structure
    if (result == NULL) {
        return NULL;
    }

    result->size = new_size;
    result->data = malloc(sizeof(double) * new_size); // Allocate memory for the new array's data
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < new_size; i++) { // Loop through the new array size to calculate averages of adjacent pairs
        int index = 2 * i;
        result->data[i] = (a->data[index] + a->data[index + 1]) / 2.0;
        // Calculate the average of adjacent pairs and store in the new array
    }

    return result;
}

int main(int argc, char *argv[]) { // Main function to demonstrate the usage of the Array structure and its associated functions
    if (argc != 2) {
        printf("Usage: ./main <array_size>\n"); // Check if the user provided the correct number of command-line arguments
        return 1;
    }

    int size = atoi(argv[1]); // Convert the command-line argument to an integer to determine the size of the array
    if (size <= 0) {
        printf("Array size must be a positive integer.\n"); // Validate that the provided size is a positive integer
        return 1;
    }

    Array *a = malloc(sizeof(Array)); // Allocate memory for the Array structure
    if (a == NULL) {
        printf("Memory allocation failed.\n"); // Check if memory allocation for the structure was successful
        return 1;
    }

    a->size = size;
    a->data = malloc(sizeof(double) * size);
    if (a->data == NULL) {
        printf("Memory allocation failed.\n"); // Free the allocated memory for the structure before returning
        free(a);
        return 1;
    }

    for (int i = 0; i < size; i++) { // Initialize the array with sequential floating-point values starting from 1.5
        a->data[i] = i + 1.5;
        // Initialize array with sequential floating values starting at 1.5
    }

    printf("Original array:\n"); // Display the array before performing any operations  
    output_array(a); // Print each element of the array

    shift_array(a); // Shift array elements (likely rotates or moves values left/right)
    printf("After shift:\n"); // Show the array after the shift operation
    output_array(a);

    Array *avg = average_adjacent(a); // Create a new array containing averages of adjacent pairs
    if (avg != NULL) { // Ensure the operation succeeded before printing
        printf("Averaged adjacent pairs:\n");
        output_array(avg);
        free(avg->data);
        free(avg);
    }

    free(a->data); //free the allocated memory for the original array's data
    free(a); //free the allocated memory for the original array structure
    return 0;
}

