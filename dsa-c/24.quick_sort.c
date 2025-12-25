#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int* comparisons, int* exchanges) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            (*exchanges)++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    (*exchanges)++;
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int* comparisons, int* exchanges) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, exchanges);
        quickSort(arr, low, pi - 1, comparisons, exchanges);
        quickSort(arr, pi + 1, high, comparisons, exchanges);
    }
}

int randomPivot(int low, int high) {
    return (rand() % (high - low + 1)) + low;
}

int randomizedPartition(int arr[], int low, int high, int* comparisons, int* exchanges) {
    int pivotIndex = randomPivot(low, high);
    swap(&arr[pivotIndex], &arr[high]);
    (*exchanges)++;
    return partition(arr, low, high, comparisons, exchanges);
}

void randomizedQuickSort(int arr[], int low, int high, int* comparisons, int* exchanges) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high, comparisons, exchanges);
        randomizedQuickSort(arr, low, pi - 1, comparisons, exchanges);
        randomizedQuickSort(arr, pi + 1, high, comparisons, exchanges);
    }
}

void main() {
    //int arr1[] = {10, 7, 8, 9, 1, 5, 6, 2};
    //int arr2[] = {10, 7, 8, 9, 1, 5, 6, 2};
    
    // worst case
    //int arr1[] = {1,2,3,4,5,6,7,8};
    //int arr2[] = {1,2,3,4,5,6,7,8};

    int arr1[] = {1,5,7,8,10,9};
    int arr2[] = {1,5,7,8,10,9};

    int n = 6;
    int comparisons1 = 0, exchanges1 = 0;
    int comparisons2 = 0, exchanges2 = 0;

    quickSort(arr1, 0, n - 1, &comparisons1, &exchanges1);
    srand(time(0));
    randomizedQuickSort(arr2, 0, n - 1, &comparisons2, &exchanges2);
    
    printf("\nQuick Sort : \nComparisons: %d\nExchanges: %d\nSorted Array: ", comparisons1, exchanges1);
    for (int i=0; i<n; i++)
        printf("%d , ",arr1[i]);
    
    printf("\n\nRandomized Quick Sort : \nComparisons: %d\nExchanges: %d\nSorted Array: ", comparisons2, exchanges2);
    for (int i=0; i<n; i++)
        printf("%d , ",arr2[i]);

}
