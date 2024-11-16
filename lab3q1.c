#include <stdio.h>
#include <stdbool.h>

#define SIZE 24
#define nROWS 8
#define nCOLS 3

// Function to check if index is within array limits
bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

// Remove element at a given index
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid index %d\n", pos);
        return;
    }

    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }

    arr[length - 1] = 0; 

    printf("Array after removing element at index %d: ", pos);
    for (int i = 0; i < length; i++) printf("%d ", arr[i]);
    printf("\n");
}

// Insert new element at a given index
void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid index %d\n", pos);
        return;
    }
    for (int i = length - 1; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = value;

    printf("Array after inserting %d at index %d: ", value, pos);
    for (int i = 0; i < length; i++) printf("%d ", arr[i]);
    printf("\n");
}

// Reshape  1-D array into a 2-D array
void reshape(const int arr[], int length, int Rows, int Cols, int arr2D[Rows][Cols]) {
    if (length != Rows * Cols) {
        printf("Error: Length of the array does not match dimensions.\n");
        return;
    }
    int index = 0;
    for (int col = 0; col < Cols; col++) {
        for (int row = 0; row < Rows; row++) {
            arr2D[row][col] = arr[index++];
        }
    }
}

// Transpose matrix
void trans_matrix(int Rows, int Cols, const int mat[Rows][Cols], int mat_transp[Cols][Rows]) {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

// Check for duplicate element in the array
bool found_duplicate(const int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40};
    int arr2D[nROWS][nCOLS];

    // Test remove_element
    printf("Original array: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");
    remove_element(arr, SIZE, 2);

    // Test  insert_element
    insert_element(arr, SIZE, 2, 80);

    // Test reshape
    reshape(arr, SIZE, nROWS, nCOLS, arr2D);
    printf("Reshaped array: \n");
    for (int i = 0; i < nROWS; i++) {
        for (int j = 0; j < nCOLS; j++) {
            printf("%d ", arr2D[i][j]);
        }
        printf("\n");
    }

    // Test trans_matrix
    int mat_transp[nCOLS][nROWS];
    trans_matrix(nROWS, nCOLS, arr2D, mat_transp);
    printf("Transposed matrix: \n");
    for (int i = 0; i < nCOLS; i++) {
        for (int j = 0; j < nROWS; j++) {
            printf("%d ", mat_transp[i][j]);
        }
        printf("\n");
    }

    // Test found_duplicate
    printf("Array with duplicates found: %s\n", found_duplicate(arr, SIZE) ? "true" : "false");

    return 0;
}
