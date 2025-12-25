#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long max (long a,long b)
{      return (a > b)  ? a : b;
}

int countDigits(long n) {
    int c = 0;
    while (n > 0)
    {   c++;
        n /= 10;
    }    
    return c;
}

int char_to_no(char c)
{   if (c>=48 && c<=57)
        return c-48;
    else if(c>=65 && c<=90)
        return (c-65)+10;
    return -1;
}

char no_to_char(int n)
{   if (n>=0 && n<=9)
        return n+48;
    else if(n>=10 && n<=35)
        return (n-10) + 65;
    return -1;
}
 
long toDecimal(char *x, int r)
{   int n = strlen(x);
    int i;
    long s = 0;
    for (i=0; i<n; i++)
        s += char_to_no(x[i]) * (long)pow(r,n-i-1);
    return s;
}

void reverseString(char str[], int start, int end) {
    if (start >= end) {
        return;
    }
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    reverseString(str, start + 1, end - 1);
}

char * fromDecimal(long x, int r)
{   char *s = (char *)malloc(floor(log2(x)) * sizeof(char)); 
    int k = 0;
    while (x>0)
    {   s[k++] = no_to_char( x % r);
        x /= r;
    }
    s[k] = '\0';
    reverseString(s,0,k-1);
    return s;

}
    
long karatsuba(long x, long y)
{   if ( x < 10 && y < 10)
        return x*y;
    
    long n = max( countDigits(x), countDigits(y));
    long half = n/2;
    long p = (long)pow(10,half);

    long a = x / p;
    long b = x % p;
    long c = y / p;
    long d = y % p;
    
    printf("Divide:\nX = %ld\n",x);
    printf("\ta = %ld\n",a);
    printf("\tb = %ld\n",b);
	
	printf("Y = %ld\n",y);
    printf("\tc = %ld\n",c);
    printf("\td = %ld\n\n",d);
	    
    long ac = karatsuba(a,c);
    long bd = karatsuba(b,d);
    long ad_bc = karatsuba( a+b , c+d);
    
    printf("\nX = %ld\n",x);
    printf("Y = %ld\n",y);
    printf("Conquer:\n\ta X c = %ld\n",ac);
	printf("\tb X d = %ld\n",bd);
	printf("\t(a+b) X (c+d) = %ld\n",ad_bc);
	
	long pr = (ac * (long)pow(10,2*half)) + (p * (ad_bc - ac - bd)) + bd;
	printf("Combine:\n\tX X Y = %ld\n\n",pr);
    return  pr;
}

void main()
{   char m[] = "12345";
    char n[] = "67899";
    int b = 10;
    printf("%s X %s\n-------------------\n",m,n);
    
    long x = toDecimal(m,b);
    long y = toDecimal(n,b);
    printf("X(%s) in decimal= %ld\n",m,x);
    printf("Y(%s) in decimal= %ld\n\n",n,y);
    
    printf("Result = %s", fromDecimal(karatsuba(x,y),b));
}
