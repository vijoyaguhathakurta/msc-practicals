#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix
int** allocateMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to free the allocated memory for a matrix
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// prints a matrix
void printMatrix( int **C, int n)
{   for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
            printf("%d ", C[i][j]);
    printf("\n");
    }
}

// Function to add two matrices
int ** addMatrix(int** A, int** B, int size) {
    int **C = allocateMatrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Function to subtract two matrices
int ** subMatrix(int** A, int** B, int size) {
    int **C = allocateMatrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Function to multiply two matrices using Strassen's algorithm
int ** strassenMultiply(int** A, int** B, int size) {
    int **C = allocateMatrix(size);

    // Base case : matrix of single elements
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = size / 2;

    // Submatrices of matrix A
    int** a = allocateMatrix(newSize);
    int** b = allocateMatrix(newSize);
    int** c = allocateMatrix(newSize);
    int** d = allocateMatrix(newSize);

    // Submatrices of matrix B
    int** e = allocateMatrix(newSize);
    int** f = allocateMatrix(newSize);
    int** g = allocateMatrix(newSize);
    int** h = allocateMatrix(newSize);
    
    int i,j;
    // Splitting the matrices into quadrants
    for (i = 0; i < newSize; i++) {
        for ( j = 0; j < newSize; j++) {
            a[i][j] = A[i][j];
            b[i][j] = A[i][j + newSize];
            c[i][j] = A[i + newSize][j];
            d[i][j] = A[i + newSize][j + newSize];

            e[i][j] = B[i][j];
            f[i][j] = B[i][j + newSize];
            g[i][j] = B[i + newSize][j];
            h[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculating M1 to M7
    int ** t1, **t2;
    
    t1 = addMatrix(a, d, newSize);
    t2 = addMatrix(e, h, newSize);
    int ** M1 = strassenMultiply( t1, t2, newSize);
    
    t1 = addMatrix(c, d, newSize);
    int ** M2 = strassenMultiply( t1, e, newSize);

    t1 = subMatrix(f, h, newSize);
    int ** M3 = strassenMultiply( a, t1, newSize);

    t1 = subMatrix(g, e, newSize);
    int ** M4 = strassenMultiply( d, t1, newSize);

    t1 = addMatrix(a, b, newSize);
    int ** M5 = strassenMultiply( t1, h, newSize);

    t1 = subMatrix(c, a, newSize);
    t2 = addMatrix(e, f, newSize);
    int ** M6 = strassenMultiply( t1, t2, newSize);

    t1 = subMatrix(b, d, newSize);
    t2 = addMatrix(g, h, newSize);
    int ** M7 = strassenMultiply( t1, t2, newSize);

    // Combining M1 to M7 to get the final product matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] + M3[i][j] - M2[i][j] + M6[i][j];
        }
    }

    // Freeing allocated memory
    freeMatrix(a, newSize);
    freeMatrix(b, newSize);
    freeMatrix(c, newSize);
    freeMatrix(d, newSize);
    freeMatrix(e, newSize);
    freeMatrix(f, newSize);
    freeMatrix(g, newSize);
    freeMatrix(h, newSize);

    freeMatrix(M1, newSize);
    freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);
    freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);
    freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(t1, newSize);
    freeMatrix(t2, newSize);

    return C;
}

int main() {
    int n = 8; // Example size, should be a power of 2
    
    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    int** M = strassenMultiply(A,B,n);

    printf("\nMatrix A:\n");
    printMatrix(A,n);

    printf("\nMatrix B:\n");
    printMatrix(B,n);
    
    // Print the result matrix C
    printf("\nResult matrix C:\n");
    printMatrix(M,n);
    
}
    