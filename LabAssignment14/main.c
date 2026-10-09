#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "pow_iter.c"
#include "shift_inv_pow_iter.c"
#include "rayleigh_quot_iter.c"

int main(){
    const double tol = 1.0e-10;
    double lambda = 0;
    //Make matrix K
    matrix K = new_matrix(4,4);
    for (int i = 1; i <= 4; i++){
        mget(K,i,i) = 2.0;
        if(i > 1){
            mget(K,i,i-1) = -1.0;
        }
        if(i < 4){
            mget(K,i,i+1) = -1.0;
        }
    }
    print_matrix(&K);

    //Task 1
    vector x = new_vector(4);
    //Initial guess
    for(int i = 1; i <= 4; i++){vget(x, i) = 1.0;}
    lambda = shift_inv_pow_iter(&K, &x, tol, 0.0, 100);
    printf("Task_1: lambda = %.6f\n", lambda);
    delete_vector(&x);

    // Task 2
    x = new_vector(4);
    //Initial guess
    vget(x, 1) = 1.0;
    vget(x, 2) = 0.5;
    vget(x, 3) = -0.5;
    vget(x, 4) = -1.0;
    lambda = shift_inv_pow_iter(&K, &x, tol, 2.5, 100);
    printf("Task_2: lambda = %.6f\n", lambda);
    delete_vector(&x);

    // Task 3
    x = new_vector(4);
    //Initial guess
    vget(x, 1) = 1.0;
    vget(x, 2) = 0.5;
    vget(x, 3) = -0.5;
    vget(x, 4) = -1.0;
    lambda = ray_quot_iter(&K, &x, tol, 100);
    printf("Task_3: lambda = %.6f\n", lambda);
    delete_vector(&x);
}