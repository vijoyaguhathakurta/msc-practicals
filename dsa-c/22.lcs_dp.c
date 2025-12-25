#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

// Function to find the LCS and its length
void LCS(char* X, char* Y, int m, int n) {
    
    int** L = (int**)malloc(m+1 * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        L[i] = (int*)malloc(n+1 * sizeof(int));
    }
    int i, j;

    // Building the L[m+1][n+1] table 
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            } 
            else if (X[i - 1] == Y[j - 1]) 
                L[i][j] = L[i - 1][j - 1] + 1;
             
            else 
                L[i][j] = MAX(L[i - 1][j] , L[i][j - 1]); 
        }
    }

    // Length of LCS
    int lcs_length = L[m][n];
    printf("Length of LCS: %d\n", lcs_length);

    // Recover the LCS from the table
    char * LCS = (char*)malloc(lcs_length * sizeof(char));
    
    LCS[lcs_length] = '\0'; // Null-terminate the LCS string

    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            LCS[--lcs_length] = X[i - 1];
            i--;
            j--;
        } 
        else if (L[i - 1][j] > L[i][j - 1]) 
            i--;
        else 
            j--;
    }
    printf("LCS: %s\n", LCS);
}

// Main function to test the LCS function
void main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);
    printf("String 1:%s\n",X);
    printf("String 2:%s\n",Y);
    LCS(X, Y, m, n);
}
