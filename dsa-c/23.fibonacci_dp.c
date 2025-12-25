# include <stdio.h>
# include <stdlib.h>

int fibonacci_dp( int n, int *a) {
    if (n==1 || n==2)
        return n-1;
    if (a[n] != 0)
        return a[n];
    a[n] = fibonacci_dp(n-1 , a) + fibonacci_dp(n-2 , a);
    return a[n];
}

void main() {
    int i, n = 8;
    int *a = (int *)malloc(n+1 * sizeof(int));
    for (i=1; i<=n; i++)
        a[i] = 0;
    printf("The %dth Fibonacci number is %d.",n,fibonacci_dp(n,a));
}