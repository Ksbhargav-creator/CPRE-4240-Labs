#include <stdio.h>
#include <math.h>

double factorial(int n){
    // Base case
    if (n <= 1) {
        return 1;
    }else {
        return n*factorial(n - 1);
    }
}

double expo(double x){
    double e = 2.718281828459;
    
    double x0 = 0;
    double z = 0;
    double sum = 0;
    x0 = floor(x);

    z = x - x0;
    for (int i = 0; i < 20; i++){
       sum += pow(z,i)/factorial(i);
    }

    return pow(e,x0)*sum;
}

int main(){
    double arr[51];
    double arr_exp[51];

    for (int i = 0; i < 51; i++){
        arr[i] = (i)*0.02;
    }
    for (int i = 0; i < 51; i++){
        arr_exp[i] = expo(arr[i]);
    }

    FILE* outfile = fopen("out.data","w");
    
    for (int i = 0; i < 51; i++){
        fprintf(outfile, "%f\t%f\n",arr[i], arr_exp[i]);
    }

    fclose(outfile);

    return 0;
}
