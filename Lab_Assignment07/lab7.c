#include <stdio.h>
#include <math.h>

int main() {

    int n = 6;
    int nf = 1;
    int xe = 1;
    double xl = 1;

    if (n >= 0) {
        for(int i = 0; i < n; i++){
            nf = nf*(n - i);
        }
    }else {
        printf("Please enter a non-negative integer\n");
    }
    printf("n! is %d\n", nf);

    printf("Let's compute the exponent of a real number X\n");
    int x = 10;
    xe = pow(x,n);
    printf("The exponent of 10 to the power of 6 is %d\n", xe);

    printf("Let's compute the logarithm of a real number X \n");
    xl = log(x);
    printf("The logarithm of a real number x is %f \n", xl);
}
