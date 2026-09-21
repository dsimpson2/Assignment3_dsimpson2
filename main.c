#include <stdio.h>
#include <stdlib.h>
// Keep the array definition local so this file does not depend on an
// unavailable header search path.
typedef struct {
    int size;
    double *data;
} Array;

int main() {
    Array myArray;
    myArray.size = 5;
    myArray.data = (double *)malloc(myArray.size * sizeof(double));

    for (int i = 0; i < myArray.size; i++) {
        myArray.data[i] = i * 1.0; // Initialize with some values
    }

    for (int i = 0; i < myArray.size; i++) {
        printf("Element %d: %f\n", i, myArray.data[i]);
    }

    free(myArray.data);
    return 0;
}

