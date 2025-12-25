#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long countBit(unsigned long m){

    unsigned long count = 0;

    while(m > 0){
        if(m & 1)
            count++;
        m = m >> 1;
    }

    return count;
}

unsigned long powLong(unsigned long a, unsigned long b){
    unsigned long i, result = 1;
    for(i = 1; i <= b; i++){
        result *= a;
    }
    return result;
}

unsigned long change(unsigned long m, unsigned long n){ // returns the change in binary bits between m to n
    return countBit(m ^ n);
}

void printBin(unsigned long b, unsigned long bits){

    char *bin = (char*)malloc(bits+1 * sizeof(char));
    bin[bits] = '\0';
    while(bits > 0){
        bin[--bits] = (b & 1) ? '1' : '0';
        b = b >> 1;
    }

    printf("%s", bin);
    free(bin);
}

int main(){

    unsigned long i, bits;

    unsigned long ti, ci, ai, ci_1, sum;

    for(bits = 1; bits <= 8; bits++){

        printf("\n");
        ci_1 = 0, sum = 0;

        printf("Step i\t\tInteger\t\tti\tci\tai\n");
        printf("---------------------------------------------------------\n");
        for(i = 1; i <= powLong(2, bits); i++){

            printf("  %lu\t\t", i);
            printBin(i, bits);

            ti = change( ((i-1) & (powLong(2,bits)-1)) , (i & (powLong(2, bits)-1)) );
            printf("\t\t%lu\t", ti);

            ci = countBit( i & (powLong(2,bits)-1) );
            printf("%lu\t", ci);

            ai = (ti + ci - ci_1);
            printf("%lu", ai);

            sum += ai;

            ci_1 = ci;
            
            printf("\n");

        }

        printf("\nAmortized cost when bits = %lu is %f\n", bits, round( sum / (double)(i-1)) );
        
        printf("\n");

    }
    
}